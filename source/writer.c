#include <stdio.h>
#include <string.h>
#include <libxml/xmlwriter.h>
#include "core.h"
#include "writer.h"
#include "validator.h"
#include "types.h"
#include "utilities.h"

/************************
 * set up SBOL document
 ************************/

#define INCLUDE_URI_ONLY 0
#define INCLUDE_CONTENTS 1

static int INDENT;
static xmlTextWriterPtr WRITER;
static xmlDocPtr OUTPUT;

void indentMore() { xmlTextWriterSetIndent(WRITER, ++INDENT); }
void indentLess() { xmlTextWriterSetIndent(WRITER, --INDENT); }

void createSBOLWriter() {
	INDENT = 0;
	WRITER = xmlNewTextWriterDoc(&OUTPUT, 0);
	xmlTextWriterSetIndentString(WRITER, "\t");
	xmlTextWriterSetIndent(WRITER, INDENT);
}

void cleanupSBOLWriter() {
	xmlFreeTextWriter(WRITER);
	xmlFreeDoc(OUTPUT);
	WRITER = NULL;
	OUTPUT = NULL;
	xmlCleanupParser();
}

void startSBOLDocument() {
	createSBOLWriter();
	xmlTextWriterStartDocument(WRITER, NULL, NULL, NULL);
	xmlTextWriterStartElement(WRITER, "rdf:RDF");
	// TODO add newlines, indents for easier reading
	xmlTextWriterWriteAttribute(WRITER, "xmlns:rdf",  XMLNS_RDF);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:rdfs", XMLNS_RDFS);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:so",   XMLNS_SO);
	xmlTextWriterWriteAttribute(WRITER, "xmlns",      XMLNS_SBOL);
	//xmlTextWriterWriteAttribute(WRITER, "xmlns:xsi",  XMLNS_XSI);
	//xmlTextWriterWriteAttribute(WRITER, "xsi:schemaLocation", SCHEMA_LOCATION);
	indentMore();
}

void endSBOLDocument() {
	indentLess();
	xmlTextWriterEndElement(WRITER);
	xmlTextWriterEndDocument(WRITER);
}

int saveSBOLDocument(const char* filename) {
	int invalid = 0;
	if (!isValidSBOL(OUTPUT)) {
		invalid = 1;
		printf("WARNING: %s is not valid SBOL. Saving anyway.\n", filename);
	}
	int written = xmlSaveFile(filename, OUTPUT);
	return (int) invalid || written == -1;
}

/***********************
 * serialize SBOL core
 ***********************/

// TODO move node names to types.h

void writeDNASequence(const DNASequence* seq, int includeContents) {
	if (!seq)
		return;
	xmlTextWriterStartElement(WRITER, "DnaSequence");
	xmlTextWriterWriteAttribute(WRITER, "rdf:about", getDNASequenceID(seq));

	// nucleotides
	if (includeContents)
		xmlTextWriterWriteElement(WRITER, "nucleotides", getNucleotides(seq));
	
	xmlTextWriterEndElement(WRITER);
}

void writeSequenceAnnotation(const SequenceAnnotation* ann, int includeContents) {
	if (!ann)
		return;
	xmlTextWriterStartElement(WRITER, "SequenceAnnotation");
	xmlTextWriterWriteAttribute(WRITER, "rdf:about", getSequenceAnnotationID(ann));
	
	// start, end
	int start = getBioStart(ann);
	int end   = getBioEnd(ann);
	if (start>0)
		xmlTextWriterWriteElement(WRITER, "bioStart", intToStr(start));
	if (end>0)
		xmlTextWriterWriteElement(WRITER, "bioEnd",   intToStr(end));
	
	// subComponent
	char* id;
	if (includeContents) {
		indentMore();
		if (ann->subComponent) {
			id = getDNAComponentID(ann->subComponent);
			xmlTextWriterStartElement(WRITER, "subComponent");
			xmlTextWriterWriteAttribute(WRITER, "rdf:resource", id);
			xmlTextWriterEndElement(WRITER);
		}
		indentLess();
	}
	
	xmlTextWriterEndElement(WRITER);
}

void writeDNAComponent(const DNAComponent* com, int includeContents) {
	if (!com)
		return;
	xmlTextWriterStartElement(WRITER, "DnaComponent");
	if (includeContents) {
		xmlTextWriterWriteAttribute(WRITER, "rdf:about", getDNAComponentID(com));
		
		// properties
		char* data;
		data = getDNAComponentName(com);
		if (data)
			xmlTextWriterWriteElement(WRITER, "displayId", data);
		data = getDNAComponentDescription(com);
		if (data)
			xmlTextWriterWriteElement(WRITER, "description", data);
		
		// sequence
		if (com->dnaSequence) {
			xmlTextWriterStartElement(WRITER, "dnaSequence");
			indentMore();
			// TODO sometimes no contents?
			writeDNASequence(com->dnaSequence, INCLUDE_CONTENTS);
			indentLess();
			xmlTextWriterEndElement(WRITER);
		}
		
		// annotations
		int n;
		int num = getNumSequenceAnnotationsIn(com);
		SequenceAnnotation* ann;
		indentMore();
		if (num>0) {
			for (n=0; n<num; n++) {
				ann = getNthSequenceAnnotationIn(com, n);
				indentMore();
				xmlTextWriterStartElement(WRITER, "annotation");
				writeSequenceAnnotation(ann, INCLUDE_CONTENTS);
				xmlTextWriterEndElement(WRITER);
				indentLess();
			}
		}
		indentLess();
		
	} else
		xmlTextWriterWriteAttribute(WRITER, "rdf:resource", getDNAComponentID(com));
	xmlTextWriterEndElement(WRITER);
}

void writeCollection(const Collection* col, int includeContents) {
	if (!col)
		return;
	xmlTextWriterStartElement(WRITER, "Collection");
	if (includeContents) {
		int n;
		int num;
		
		// properties
		xmlTextWriterWriteAttribute(WRITER, "rdf:about", getCollectionID(col));
		xmlTextWriterWriteElement(WRITER, "displayId", getCollectionName(col));
		xmlTextWriterWriteElement(WRITER, "description", getCollectionDescription(col));
		
		// components
		DNAComponent* com;
		num = getNumDNAComponentsIn(col);
		if (num>0) {
			indentMore();
			for (n=0; n<num; n++) {
				xmlTextWriterStartElement(WRITER, "component");
				com = getNthDNAComponentIn(col, n);
				indentMore();
				if (getNumCollectionsFor(com) == 1)
					writeDNAComponent(com, INCLUDE_CONTENTS);
				else
					writeDNAComponent(com, INCLUDE_URI_ONLY);
				indentLess();
				xmlTextWriterEndElement(WRITER);
			}
			indentLess();
		}
		
		// collections
		Collection* col2;
		num = getNumCollectionsIn(col);
		if (num>0) {
			indentMore();
			for (n=0; n<num; n++) {
				xmlTextWriterStartElement(WRITER, "collection");
				col2 = getNthCollectionIn(col, n);
				indentMore();
				// TODO sometimes don't include contents?
				writeCollection(col2, INCLUDE_CONTENTS);
				indentLess();
				xmlTextWriterEndElement(WRITER);
			}
			indentLess();
		}
		
	} else
		xmlTextWriterWriteAttribute(WRITER, "rdf:resource", getCollectionID(col));
	xmlTextWriterEndElement(WRITER);
}

/***********************
 * main write function
 ***********************/

int writeSBOLCore(const char* filename) {
	int n;
	startSBOLDocument();

	// write collections
	// (and components in just one collection)
	Collection* col;
	for (n=0; n<getNumCollections(); n++) {
		col = getNthCollection(n);
		writeCollection(col, INCLUDE_CONTENTS);
	}
	
	// write sequences
	DNASequence* seq;
	for (n=0; n<getNumDNASequences(); n++) {
		seq = getNthDNASequence(n);
		writeDNASequence(seq, INCLUDE_CONTENTS);
	}
	
	// write components
	// (unless they were included in a collection above)
	DNAComponent* com;
	for (n=0; n<getNumDNAComponents(); n++) {
		com = getNthDNAComponent(n);
		if (getNumCollectionsFor(com) != 1)
			writeDNAComponent(com, INCLUDE_CONTENTS);
	}
	
	endSBOLDocument();
	cleanupSBOLWriter;
	return saveSBOLDocument(filename);
}
