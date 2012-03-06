#include <stdio.h>
#include <string.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include "core.h"
#include "writer.h"

//#define XML_ENCODING "ISO-8859-1"
#define XMLNS_RDF "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
#define XMLNS_RDFS "http://www.w3.org/2000/01/rdf-schema#"
#define XMLNS_SO "http://purl.obolibrary.org/obo/"
#define XMLNS_S "http://sbols.org/v1#"
#define XMLNS_XSI "http://www.w3.org/2001/XMLSchema-instance"
#define SCHEMA_LOCATION "http://sbols.org/v1# ../schema/sbol.xsd http://www.w3.org/1999/02/22-rdf-syntax-ns# ../schema/rdf.xsd"

static xmlTextWriterPtr WRITER;

/********************************
 * set up generic SBOL document
 ********************************/

void startSBOLDocument(const char* filename) {
	WRITER = xmlNewTextWriterFilename(filename, 0);
	xmlTextWriterStartDocument(WRITER, NULL, NULL, NULL);
	xmlTextWriterStartElement(WRITER, "rdf:RDF");
	xmlTextWriterWriteAttribute(WRITER, "xmlns:rdf",  XMLNS_RDF);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:rdfs", XMLNS_RDFS);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:so",   XMLNS_SO);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:s",    XMLNS_S);
	xmlTextWriterWriteAttribute(WRITER, "xmlns:xsi",  XMLNS_XSI);
	xmlTextWriterWriteAttribute(WRITER, "xsi:schemaLocation", SCHEMA_LOCATION);
}

void endSBOLDocument() {
	int result;
	result = xmlTextWriterEndElement(WRITER);
	result = xmlTextWriterEndDocument(WRITER);
	xmlFreeTextWriter(WRITER);
}

/***********************
 * serialize SBOL core
 ***********************/

void writeDNASequence(DNASequence* seq);
void writeSequenceAnnotation(SequenceAnnotation* ann);
void writeDNAComponent(DNAComponent* com);
void writeCollection(Collection* col);

/***********************
 * main write function
 ***********************/

void writeSBOLCore(const char* filename) {
	printf("writeSBOL(%s)\n", filename);
	startSBOLDocument(filename);
	endSBOLDocument();
    return;
}
