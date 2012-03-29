#include <stdio.h>
#include <string.h>
#include <libxml/xmlwriter.h>
#include "sbol.h"
#include "array.h"

/************************
 * set up SBOL document
 ************************/

static int INDENT;
static xmlTextWriterPtr WRITER;
static xmlDocPtr OUTPUT;
static PointerArray *processed; ///< @todo capitalize

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
	deletePointerArray(processed);
	processed = NULL;
	xmlCleanupParser();
}

void markProcessed(void *obj) {
	insertPointerIntoArray(processed, obj);
}

int alreadyProcessed(void *obj) {
	return pointerContainedInArray(processed, obj); 
}

void resetProcessed() {
	deletePointerArray(processed);
	processed = createPointerArray();
}

void startSBOLDocument() {
	resetProcessed();
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

void writeDNASequence(DNASequence* seq) {
	if (!seq)
		return;
	xmlTextWriterStartElement(WRITER, NODENAME_DNASEQUENCE);
	xmlTextWriterWriteAttribute(WRITER, NSPREFIX_RDF ":" NODENAME_ABOUT, getDNASequenceURI(seq));

	// nucleotides
	if (!alreadyProcessed((void *)seq)) {
		xmlTextWriterWriteElement(WRITER, NODENAME_NUCLEOTIDES , getNucleotides(seq));
		markProcessed((void *)seq);
	}
	
	xmlTextWriterEndElement(WRITER);
}

void writeSequenceAnnotation(SequenceAnnotation* ann) {
	if (!ann)
		return;
	markProcessed((void *)ann);
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
	int start = getBioStart(ann);
	int end   = getBioEnd(ann);
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
		if (alreadyProcessed((void *)(ann->subComponent)))
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

void writeDNAComponent(DNAComponent* com) {
	if (!com)
		return;
	xmlTextWriterStartElement(WRITER, NODENAME_DNACOMPONENT);
	if (!alreadyProcessed((void *)com)) {
		markProcessed((void *)com);
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
		int num = getNumSequenceAnnotationsIn(com);
		SequenceAnnotation* ann;
		indentMore();
		if (num>0) {
			for (n=0; n<num; n++) {
				ann = getNthSequenceAnnotationIn(com, n);
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

void writeCollection(Collection* col) {
	if (!col)
		return;
	xmlTextWriterStartElement(WRITER, NODENAME_COLLECTION);
	if (!alreadyProcessed((void *)col)) {
		markProcessed((void *)col);
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
		
		// collections
		Collection* col2;
		num = getNumCollectionsIn(col);
		if (num>0) {
			for (n=0; n<num; n++) {
				indentMore();
				xmlTextWriterStartElement(WRITER, NODENAME_COLLECTION_REF);
				col2 = getNthCollectionInCollection(col, n);
				indentMore();
				// TODO sometimes don't include contents?
				writeCollection(col2);
				indentLess();
				xmlTextWriterEndElement(WRITER);
				indentLess();
			}
		}
		
	} else
		xmlTextWriterWriteAttribute(WRITER, NSPREFIX_RDF ":" NODENAME_RESOURCE, getCollectionURI(col));
	xmlTextWriterEndElement(WRITER);
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
		if (!alreadyProcessed((void *)col))
			writeCollection(col);
	}

	// write components
	DNAComponent* com;
	for (n=0; n<getNumDNAComponents(); n++) {
		com = getNthDNAComponent(n);
		if (!alreadyProcessed((void *)com))
			writeDNAComponent(com);
	}
	
	// write sequences
	// (there shouldn't be any left at this point,
	// but better to write them and fail the schema validation
	// than just lose them silently)
	DNASequence* seq;
	for (n=0; n<getNumDNASequences(); n++) {
		seq = getNthDNASequence(n);
		if (!alreadyProcessed((void *)seq))
			writeDNASequence(seq);
	}
	
	// write annotations
	// (there shouldn't be any left at this point,
	// but better to write them and fail the schema validation
	// than just lose them silently)
	SequenceAnnotation* ann;
	for (n=0; n<getNumSequenceAnnotations(); n++) {
		ann = getNthSequenceAnnotation(n);
		if (!alreadyProcessed((void *)ann))
			writeSequenceAnnotation(ann);
	}

	endSBOLDocument();
	cleanupSBOLWriter;
	return saveSBOLDocument(filename);
}
