#include <stdio.h>
#include <string.h>
#include <libxml/xmlwriter.h>
#include "core.h"
#include "writer.h"
#include "validator.h"
#include "types.h"
#include "utilities.h"
#include "core/genericarray.h" // TODO shouldn't break abstraction

/***************************************
 * avoid writing things multiple times
 ***************************************/

static GenericArray* WRITTEN;

void resetWritten() {
    if (WRITTEN)
        deleteGenericArray(WRITTEN);
    WRITTEN = createGenericArray();
}

void markWritten(const void* obj) {
    if (obj) {
        int address = (int) obj;
        insertIntoGenericArray(WRITTEN, (void*) address);
    }
}

int alreadyWritten(const void* obj) {
    if (obj) {
        int address = (int) obj;
        int index = indexByPtr(WRITTEN, (void*) address);
        if (index >= 0)
            printf("%i already written (index %i)\n", address, index);
        return (int) (index >= 0);
    } else
        return 0;
}

/************************
 * set up SBOL document
 ************************/

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
	resetWritten();
	createSBOLWriter();
	xmlTextWriterStartDocument(WRITER, NULL, NULL, NULL);
	xmlTextWriterStartElement(WRITER, "rdf:RDF");
	// TODO add newlines, indents for easier reading
	xmlTextWriterWriteAttribute(WRITER, "xmlns:rdf",  XMLNS_RDF);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:rdfs", XMLNS_RDFS);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:so",   XMLNS_SO);
	xmlTextWriterWriteAttribute(WRITER, "xmlns",      XMLNS_SBOL);
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

void writeDNASequence(const DNASequence* seq) {
	if (!seq)
		return;
	xmlTextWriterStartElement(WRITER, "DnaSequence");
	xmlTextWriterWriteAttribute(WRITER, "rdf:about", getDNASequenceURI(seq));

	// nucleotides
	if (!alreadyWritten(seq)) {
		xmlTextWriterWriteElement(WRITER, "nucleotides", getNucleotides(seq));
    }
	
	xmlTextWriterEndElement(WRITER);
	markWritten(&seq);
}

void writeSequenceAnnotation(const SequenceAnnotation* ann) {
	printf("writing %s\n", getSequenceAnnotationURI(ann));
	if (!ann)
		return;
	xmlTextWriterStartElement(WRITER, "SequenceAnnotation");
	xmlTextWriterWriteAttribute(WRITER, "rdf:about", getSequenceAnnotationURI(ann));
	
	// start, end
	int start = getBioStart(ann);
	int end   = getBioEnd(ann);
	if (start>0)
		xmlTextWriterWriteElement(WRITER, "bioStart", intToStr(start));
	if (end>0)
		xmlTextWriterWriteElement(WRITER, "bioEnd",   intToStr(end));
	
	// subComponent
	char* uri;
    indentMore();
    if (ann->subComponent) {
        uri = getDNAComponentURI(ann->subComponent);
        xmlTextWriterStartElement(WRITER, "subComponent");
        xmlTextWriterWriteAttribute(WRITER, "rdf:resource", uri);
        xmlTextWriterEndElement(WRITER);
    }
    indentLess();
	
	xmlTextWriterEndElement(WRITER);
	markWritten(ann);
}

void writeDNAComponent(const DNAComponent* com) {
	if (!com)
		return;
	xmlTextWriterStartElement(WRITER, "DnaComponent");
	if (!alreadyWritten(com)) {
	    printf("writing %s for the first time\n", getDNAComponentURI(com));
		markWritten(&com);
		xmlTextWriterWriteAttribute(WRITER, "rdf:about", getDNAComponentURI(com));
		
		// properties
		char* data;
		data = getDNAComponentDisplayID(com);
		if (data)
			xmlTextWriterWriteElement(WRITER, "displayId", data);
		data = getDNAComponentName(com);
		if (data)
			xmlTextWriterWriteElement(WRITER, "name", data);
		data = getDNAComponentDescription(com);
		if (data)
			xmlTextWriterWriteElement(WRITER, "description", data);
		
		// sequence
		if (com->dnaSequence) {
			xmlTextWriterStartElement(WRITER, "dnaSequence");
			indentMore();
			// TODO sometimes no contents?
			writeDNASequence(com->dnaSequence);
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
				writeSequenceAnnotation(ann);
				xmlTextWriterEndElement(WRITER);
				indentLess();
			}
		}
		indentLess();
		
	} else {
	    printf("writing %s again\n", getDNAComponentURI(com));
		xmlTextWriterWriteAttribute(WRITER, "rdf:resource", getDNAComponentURI(com));
    }
	xmlTextWriterEndElement(WRITER);
}

void writeCollection(const Collection* col) {
	if (!col)
		return;
	xmlTextWriterStartElement(WRITER, "Collection");
	if (!alreadyWritten(col)) {
		int n;
		int num;
		
		// properties
		xmlTextWriterWriteAttribute(WRITER, "rdf:about", getCollectionURI(col));
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
			    writeDNAComponent(com);
				indentLess();
				xmlTextWriterEndElement(WRITER);
			}
			indentLess();
		}
		
		// collections
		Collection* col2;
		num = getNumCollectionsIn(col);
		if (num>0) {
			for (n=0; n<num; n++) {
				indentMore();
				xmlTextWriterStartElement(WRITER, "collection");
				col2 = getNthCollectionIn(col, n);
				indentMore();
				// TODO sometimes don't include contents?
				writeCollection(col2);
				indentLess();
				xmlTextWriterEndElement(WRITER);
				indentLess();
			}
		}
		
	} else
		xmlTextWriterWriteAttribute(WRITER, "rdf:resource", getCollectionURI(col));
	xmlTextWriterEndElement(WRITER);
	markWritten(&col);
}

/***********************
 * main write function
 ***********************/

int writeSBOLCore(const char* filename) {
	int n;
	startSBOLDocument();

	// write collections
	Collection* col;
	for (n=0; n<getNumCollections(); n++) {
		col = getNthCollection(n);
		if (!alreadyWritten(col))
		    writeCollection(col);
	}

	// write components
	DNAComponent* com;
	for (n=0; n<getNumDNAComponents(); n++) {
		com = getNthDNAComponent(n);
		if (!alreadyWritten(com))
			writeDNAComponent(com);
	}
	
	// write sequences
	// (there shouldn't be any left at this point,
	// but better to write them and fail the schema validation
	// than just lose them silently)
	DNASequence* seq;
	for (n=0; n<getNumDNASequences(); n++) {
		seq = getNthDNASequence(n);
		if (!alreadyWritten(seq))
		    writeDNASequence(seq);
	}
	
	// write annotations
	// (there shouldn't be any left at this point,
	// but better to write them and fail the schema validation
	// than just lose them silently)
	SequenceAnnotation* ann;
	for (n=0; n<getNumSequenceAnnotations(); n++) {
		ann = getNthSequenceAnnotation(n);
		if (!alreadyWritten(ann))
		    writeSequenceAnnotation(ann);
	}

	endSBOLDocument();
	cleanupSBOLWriter;
	return saveSBOLDocument(filename);
}
