#include <stdio.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include "debug.h"
#include "sbol.h"

void readDNASequences();
void readSequenceAnnotations();
void readDNAComponents();
void readCollections();
void readReferences();

// adapted from http://xmlsoft.org/tutorial/apd.html
xmlXPathObjectPtr getNodesMatchingPath(xmlDocPtr *doc, xmlChar *path) {
	xmlXPathContextPtr context;
	xmlXPathObjectPtr  result;
	
	// create context
	context = xmlXPathNewContext(*doc);
	if (!context) {
		#if SBOL_DEBUG_ACTIVE
		printf("Error in xmlXPathNewContext\n");
		#endif
		return NULL;
	}
	
	// get results
	result = xmlXPathEvalExpression(path, context);
	xmlXPathFreeContext(context);
	if (result == NULL) {
		#if SBOL_DEBUG_ACTIVE
		printf("Error in xmlXPathEvalExpression\n");
		#endif
		return NULL;
	}
	
	// if no results, clean up
	if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
		xmlXPathFreeObject(result);
		#if SBOL_DEBUG_ACTIVE
        printf("No result\n");
        #endif
		return NULL;
	}
	
	return result;
}

// TODO remove
void print_element_names(xmlNode * a_node) {
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n", cur_node->name);
        }
        print_element_names(cur_node->children);
    }
}

// make a first pass through
// to create the SBOL objects
void readSBOLStructs(xmlNode *node) {

}

// go back and link up the objects 
// according to rdf:resource nodes
void readSBOLPointers(xmlNode *node) {
	
}

// TODO return error codes
void readSBOLCore_xml(char* filename) {
	xmlDocPtr  doc;
	xmlNodePtr root;
	
	// this initialize the library and check potential ABI mismatches
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
	
	// import SBOL
	root = xmlDocGetRootElement(doc);
	print_element_names(root);
	readSBOLStructs(root);
	readSBOLPointers(root);
	printSBOLCore();
	
	// clean up
	xmlFreeDoc(doc);
	xmlCleanupParser();
}
