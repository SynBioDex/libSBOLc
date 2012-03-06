#include <stdio.h>
#include <string.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include "core.h"
#include "writer.h"

/********************************
 * set up generic SBOL document
 ********************************/

//#define XML_ENCODING "ISO-8859-1"
#define XMLNS_RDF "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
#define XMLNS_RDFS "http://www.w3.org/2000/01/rdf-schema#"
#define XMLNS_SO "http://purl.obolibrary.org/obo/"
#define XMLNS_S "http://sbols.org/v1#"
#define XMLNS_XSI "http://www.w3.org/2001/XMLSchema-instance"
#define SCHEMA_LOCATION "http://sbols.org/v1# ../schema/sbol.xsd http://www.w3.org/1999/02/22-rdf-syntax-ns# ../schema/rdf.xsd"

static int INDENT;
static xmlTextWriterPtr WRITER;

void indentMore() { xmlTextWriterSetIndent(WRITER, ++INDENT); }
void indentLess() { xmlTextWriterSetIndent(WRITER, --INDENT); }

void createSBOLWriter(const char* filename) {
	INDENT = 0;
	WRITER = xmlNewTextWriterFilename(filename, 0);
	xmlTextWriterSetIndentString(WRITER, "\t");
	xmlTextWriterSetIndent(WRITER, INDENT);
}

void deleteSBOLWriter() {
	xmlFreeTextWriter(WRITER);
}

void startSBOLDocument(const char* filename) {
	createSBOLWriter(filename);
	xmlTextWriterStartDocument(WRITER, NULL, NULL, NULL);
	xmlTextWriterStartElement(WRITER, "rdf:RDF");
	xmlTextWriterWriteAttribute(WRITER, "xmlns:rdf",  XMLNS_RDF);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:rdfs", XMLNS_RDFS);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:so",   XMLNS_SO);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:s",    XMLNS_S);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:xsi",  XMLNS_XSI);
	xmlTextWriterWriteAttribute(WRITER, "xsi:schemaLocation", SCHEMA_LOCATION);
	indentMore();
}

void endSBOLDocument() {
	indentLess();
	xmlTextWriterEndElement(WRITER);
	xmlTextWriterEndDocument(WRITER);
	deleteSBOLWriter();
}

/***********************
 * serialize SBOL core
 ***********************/

void writeDNASequence(DNASequence* seq);
void writeSequenceAnnotation(SequenceAnnotation* ann);

void writeDNAComponent(DNAComponent* com) {
	if (!com)
		return;
	xmlTextWriterStartElement(WRITER, "s:DnaComponent");
	
	xmlTextWriterWriteAttribute(WRITER, "rdf:about", getDNAComponentID(com));
	xmlTextWriterWriteElement(WRITER, "s:displayId", getDNAComponentName(com));
	xmlTextWriterWriteElement(WRITER, "s:description", getDNAComponentDescription(com));
	
	// TODO write sequence
	//if (com->sequence)
	//	writeDNASequence(com->sequence);
	
	int n;
	SequenceAnnotation* ann;
	char* id;
	int num = getNumSequenceAnnotationsIn(com);
	if (num>0) {
		indentMore();
		xmlTextWriterStartElement(WRITER, "s:annotation");
		for (n=0; n<num; n++) {
			ann = getNthSequenceAnnotationIn(com, n);
			id  = getSequenceAnnotationID(ann);
			xmlTextWriterStartElement(WRITER, "s:SequenceAnnotation");
			xmlTextWriterWriteAttribute(WRITER, "rdf:about", id);
			xmlTextWriterEndElement(WRITER);
		}
		xmlTextWriterEndElement(WRITER);
		indentLess();
	}
	
	xmlTextWriterEndElement(WRITER);
}

void writeCollection(Collection* col);

/***********************
 * main write function
 ***********************/

void writeSBOLCore(const char* filename) {
	printf("writeSBOL(%s)\n", filename);
	startSBOLDocument(filename);
	
	// write components
	int n;
	DNAComponent* com;
	indentMore();
	for (n=0; n<getNumDNAComponents(); n++) {
		com = getNthDNAComponent(n);
		writeDNAComponent(com);
	}
	indentLess();
	
	endSBOLDocument();
    return;
}
