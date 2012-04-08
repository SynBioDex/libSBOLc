#include <stdio.h>
#include <string.h>

#include <libxml/xmlwriter.h>

#include "utilities.h"
#include "array.h"
#include "document.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"
#include "writer.h"

static int            INDENT;
static xmlTextWriter* WRITER;
static xmlDoc*        OUTPUT;
static PointerArray*  PROCESSED;

/************************
 * utility functions for
 * setting up, writing,
 * and tearing down
 ************************/

void indentMore() { xmlTextWriterSetIndent(WRITER, ++INDENT); }
void indentLess() { xmlTextWriterSetIndent(WRITER, --INDENT); }

static void createSBOLWriter() {
	INDENT = 0;
	WRITER = xmlNewTextWriterDoc(&OUTPUT, 0);
	xmlTextWriterSetIndentString(WRITER, "\t");
	xmlTextWriterSetIndent(WRITER, INDENT);
}

static void cleanupSBOLWriter() {
	xmlFreeTextWriter(WRITER);
	xmlFreeDoc(OUTPUT);
	WRITER = NULL;
	OUTPUT = NULL;
	deletePointerArray(PROCESSED);
	PROCESSED = NULL;
	xmlCleanupParser();
}

static void markPROCESSED(void *obj) {
	insertPointerIntoArray(PROCESSED, obj);
}

static int alreadyPROCESSED(void *obj) {
	return pointerContainedInArray(PROCESSED, obj); 
}

static void resetPROCESSED() {
	deletePointerArray(PROCESSED);
	PROCESSED = createPointerArray();
}

static void startSBOLDocument() {
	resetPROCESSED();
	createSBOLWriter();
	xmlTextWriterStartDocument(WRITER, NULL, NULL, NULL);
	xmlTextWriterStartElement(WRITER, NSPREFIX_RDF ":" NODENAME_RDF);
	// TODO add newlines, indents for easier reading
	xmlTextWriterWriteAttribute(WRITER, "xmlns:" NSPREFIX_RDF,  NSURL_RDF);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:" NSPREFIX_RDFS, NSURL_RDFS);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:" NSPREFIX_SO,   NSURL_SO);
	xmlTextWriterWriteAttribute(WRITER, "xmlns",                NSURL_SBOL);
	indentMore();
}

static void endSBOLDocument() {
	indentLess();
	xmlTextWriterEndElement(WRITER);
	xmlTextWriterEndDocument(WRITER);
}

static int saveSBOLDocument(const char* filename) {
	int invalid = 0;
	if (!isValidSBOL(OUTPUT)) {
		invalid = 1;
		printf("WARNING: %s is not valid SBOL. Saving anyway.\n", filename);
	}
	int written = xmlSaveFile(filename, OUTPUT);
	return (int) invalid || written == -1;
}

/************************************
 * functions for writing individual
 * SBOLObjects to the WRITER
 ************************************/

static void writeDNASequence(DNASequence* seq) {
	if (!seq)
		return;
	xmlTextWriterStartElement(WRITER, NODENAME_DNASEQUENCE);
	xmlTextWriterWriteAttribute(WRITER, NSPREFIX_RDF ":" NODENAME_ABOUT, getDNASequenceURI(seq));

	// nucleotides
	if (!alreadyPROCESSED((void *)seq)) {
		xmlTextWriterWriteElement(WRITER, NODENAME_NUCLEOTIDES , getDNASequenceNucleotides(seq));
		markPROCESSED((void *)seq);
	}
	
	xmlTextWriterEndElement(WRITER);
}

static void writeSequenceAnnotation(SequenceAnnotation* ann) {
	if (!ann)
		return;
	markPROCESSED((void *)ann);
	xmlTextWriterStartElement(WRITER, NODENAME_SEQUENCEANNOTATION);
	xmlTextWriterWriteAttribute(WRITER, NSPREFIX_RDF ":" NODENAME_ABOUT, getSequenceAnnotationURI(ann));
	
	// precedes
	int n;
	SequenceAnnotation* ann2;
	indentMore();
	for (n=0; n<getNumPrecedes(ann); n++) {
		ann2 = getNthPrecedes(ann, n);
		xmlTextWriterStartElement(WRITER, NODENAME_PRECEDES);
		xmlTextWriterWriteAttribute(WRITER, NSPREFIX_RDF ":" NODENAME_RESOURCE, getSequenceAnnotationURI(ann2));
		xmlTextWriterEndElement(WRITER);
	}
	indentLess();
	
	// start, end
	int start = getSequenceAnnotationStart(ann);
	int end   = getSequenceAnnotationEnd(ann);
	if (start>0)
		xmlTextWriterWriteElement(WRITER, NODENAME_BIOSTART, intToStr(start));
	if (end>0)
		xmlTextWriterWriteElement(WRITER, NODENAME_BIOEND,   intToStr(end));
	
	// subComponent
	char* uri;
	indentMore();
	if (ann->subComponent) {
		uri = getDNAComponentURI(ann->subComponent);
		xmlTextWriterStartElement(WRITER, NODENAME_SUBCOMPONENT);
		if (alreadyPROCESSED((void *)(ann->subComponent)))
			xmlTextWriterWriteAttribute(WRITER, NSPREFIX_RDF ":" NODENAME_RESOURCE, uri);
		else {
	 		indentMore();
	 		writeDNAComponent(ann->subComponent);
	 		indentLess();
	 	}
		xmlTextWriterEndElement(WRITER);
	}
	indentLess();
	
	xmlTextWriterEndElement(WRITER);
}

static void writeDNAComponent(DNAComponent* com) {
	if (!com)
		return;
	xmlTextWriterStartElement(WRITER, NODENAME_DNACOMPONENT);
	if (!alreadyPROCESSED((void *)com)) {
		markPROCESSED((void *)com);
		xmlTextWriterWriteAttribute(WRITER, NSPREFIX_RDF ":" NODENAME_ABOUT, getDNAComponentURI(com));
		
		// properties
		char* data;
		data = getDNAComponentDisplayID(com);
		if (data)
			xmlTextWriterWriteElement(WRITER, NODENAME_DISPLAYID, data);
		data = getDNAComponentName(com);
		if (data)
			xmlTextWriterWriteElement(WRITER, NODENAME_NAME, data);
		data = getDNAComponentDescription(com);
		if (data)
			xmlTextWriterWriteElement(WRITER, NODENAME_DESCRIPTION, data);
		
		// sequence
		if (com->dnaSequence) {
			xmlTextWriterStartElement(WRITER, NODENAME_DNASEQUENCE_REF);
			indentMore();
			// TODO sometimes no contents?
			writeDNASequence(com->dnaSequence);
			indentLess();
			xmlTextWriterEndElement(WRITER);
		}
		
		// annotations
		int n;
		int num = getNumSequenceAnnotationsFor(com);
		SequenceAnnotation* ann;
		indentMore();
		if (num>0) {
			for (n=0; n<num; n++) {
				ann = getNthSequenceAnnotationFor(com, n);
				indentMore();
				xmlTextWriterStartElement(WRITER, NODENAME_ANNOTATION);
				writeSequenceAnnotation(ann);
				xmlTextWriterEndElement(WRITER);
				indentLess();
			}
		}
		indentLess();
		
	} else
		xmlTextWriterWriteAttribute(WRITER, NSPREFIX_RDF ":" NODENAME_RESOURCE, getDNAComponentURI(com));
	xmlTextWriterEndElement(WRITER);
}

static void writeCollection(Collection* col) {
	if (!col)
		return;
	xmlTextWriterStartElement(WRITER, NODENAME_COLLECTION);
	if (!alreadyPROCESSED((void *)col)) {
		markPROCESSED((void *)col);
		int n;
		int num;
		
		// properties
		xmlTextWriterWriteAttribute(WRITER, NSPREFIX_RDF ":" NODENAME_ABOUT, getCollectionURI(col));
		xmlTextWriterWriteElement(WRITER,   NODENAME_DISPLAYID,              getCollectionDisplayID(col));
		xmlTextWriterWriteElement(WRITER,   NODENAME_NAME,                   getCollectionName(col));
		xmlTextWriterWriteElement(WRITER,   NODENAME_DESCRIPTION,            getCollectionDescription(col));
		
		// components
		DNAComponent* com;
		num = getNumDNAComponentsIn(col);
		if (num>0) {
			indentMore();
			for (n=0; n<num; n++) {
				xmlTextWriterStartElement(WRITER, NODENAME_COMPONENT);
				com = getNthDNAComponentIn(col, n);
				indentMore();
				writeDNAComponent(com);
				indentLess();
				xmlTextWriterEndElement(WRITER);
			}
			indentLess();
		}
	} else
		xmlTextWriterWriteAttribute(WRITER, NSPREFIX_RDF ":" NODENAME_RESOURCE, getCollectionURI(col));
	xmlTextWriterEndElement(WRITER);
}

/***********************
 * main write function
 ***********************/

int writeSBOLCore(Document* doc, const char* filename) {
	int n;
	startSBOLDocument();

	// write collections
	Collection* col;
	for (n=0; n<getNumCollections(doc); n++) {
		col = getNthCollection(doc, n);
		if (!alreadyPROCESSED((void *)col))
			writeCollection(col);
	}

	// write components
	DNAComponent* com;
	for (n=0; n<getNumDNAComponents(doc); n++) {
		com = getNthDNAComponent(doc, n);
		if (!alreadyPROCESSED((void *)com))
			writeDNAComponent(com);
	}

	// At this point there shouldn't be anything left.
	// But in case there are orphaned DNASequences or
	// SequenceAnnotations, SBOL will write them out anyway
	// and fail the schema validation.
	
	// write orphaned sequences
	DNASequence* seq;
	for (n=0; n<getNumDNASequences(doc); n++) {
		seq = getNthDNASequence(doc, n);
		if (!alreadyPROCESSED((void *)seq))
			writeDNASequence(seq);
	}
	
	// write orphaned sequence annotations
	SequenceAnnotation* ann;
	for (n=0; n<getNumSequenceAnnotations(doc); n++) {
		ann = getNthSequenceAnnotation(doc, n);
		if (!alreadyPROCESSED((void *)ann))
			writeSequenceAnnotation(ann);
	}

	endSBOLDocument();
	cleanupSBOLWriter;
	return saveSBOLDocument(filename);
}
