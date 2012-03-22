#include <stdio.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include "debug.h"
#include "sbol.h"

void readNamespaces();
void readDNASequence();
void readSequenceAnnotation();
void readDNAComponent();
void readCollection();
void readReference();

void readAttributes(xmlNode *node) {
	if (!node)
		return;
	
	xmlAttr *attr;
	xmlChar *namespace;
	xmlChar *name;
	for (attr = node->properties; attr; attr = attr->next) {
		name = xmlGetProp(node, attr->name);
		printf("attribute->name: %s\n", name);
		xmlFree(name);
	}
}

// make a first pass through
// to create the SBOL objects
void readSBOLStructs(xmlNode *root) {
	xmlNode *node;
	for (node = root; node; node = node->next) {
		readAttributes(node);
		if (!xmlStrcmp(node->name, (const xmlChar *)"RDF"))
			printf("found RDF: %s\n", node->name);
		readSBOLStructs(node->children);
	}
}

// go back and link up the objects 
// according to rdf:resource nodes
void readSBOLPointers(xmlNode *root) {
	xmlNode *node;
	for (node = root; node; node = node->next) {
		if (node->type == XML_ELEMENT_NODE)
			printf("%s\n", node->name);
		readSBOLStructs(node->children);
	}
}

// TODO return error codes
void readSBOLCore_xml(char* filename) {
	xmlDocPtr  doc;
	xmlNodePtr root;
	
	// this initializes the library and checks potential ABI mismatches
	// between the version it was compiled for and the actual shared
	// library used.
    LIBXML_TEST_VERSION
	
	// parse
	doc = xmlParseFile(filename);
	if (!doc) {
		printf("Error reading %s\n", filename);
		return;
	}
	
	// validate
	if (!isValidSBOL(doc)) {
		printf("%s is not a valid SBOL document.\n", filename);
		return;
	}
	
	// import
	root = xmlDocGetRootElement(doc);
	readSBOLStructs(root);
	readSBOLPointers(root);
	
	printSBOLCore();
	
	// clean up
	xmlFreeDoc(doc);
	xmlCleanupParser();
}
