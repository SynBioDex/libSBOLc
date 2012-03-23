#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include "debug.h"
#include "sbol.h"
#include "object.h"

/*************************
 * functions for reading
 * node properties
 *************************/

xmlChar *getNodeURI(xmlNode *node) {
	xmlChar *uri = NULL;
	if (node)
		// TODO #define "about"
		uri = xmlGetNsProp(node, (const xmlChar *)"about", (const xmlChar *)XMLNS_RDF);
	return uri;
}

// TODO warn that you need to xmlFree() this
xmlChar *getNodeNS(xmlNode *node) {
	xmlChar *ns = NULL;
	if (node && node->ns && node->ns->href) {
		ns = calloc(strlen(node->ns->href), sizeof(char));
		strcpy(ns, node->ns->href);
	}
	return ns;
}

// TODO also check namespace
int nodeNameEquals(xmlNode *node, char *name) {
	if (node && node->name)
		return (int) !xmlStrcmp(node->name, (const xmlChar *)name);
	else
		return 0;
}

/***************************
 * functions for reading
 * individual SBOL objects
 ***************************/
void readNamespaces(xmlNode *node); // TODO is this needed?

SBOLCompoundObject *readSBOLCompoundObject(SBOLCompoundObject *obj, xmlNode *node) {
	xmlNode *child;
	char *content;
	for (child = node->children; child; child = child->next) {
		if (child->name) {
			content = (char *)xmlNodeGetContent(child);
			if (!content) continue;
			// TODO #define these
			else if (nodeNameEquals(child, "displayId"))   setSBOLCompoundObjectDisplayID(obj, content);
			else if (nodeNameEquals(child, "name"))        setSBOLCompoundObjectName(obj, content);
			else if (nodeNameEquals(child, "description")) setSBOLCompoundObjectDescription(obj, content);
		}
	}
	return obj;
}

DNASequence *readDNASequence(xmlNode *node) {
	xmlChar *uri = getNodeURI(node);
	if (isSBOLObjectURI(uri)) {
		#if SBOL_DEBUG_ACTIVE
		printf("Tried to read %s twice\n", uri);
		#endif
		return NULL;
	}
	DNASequence *seq = createDNASequence((char *)uri);
	// TODO read nucleotides
	xmlFree(uri);
	return seq;
}

SequenceAnnotation *readSequenceAnnotation(xmlNode *node) {
	xmlChar *uri = getNodeURI(node);
	if (isSBOLObjectURI(uri)) {
		#if SBOL_DEBUG_ACTIVE
		printf("Tried to read %s twice\n", uri);
		#endif
		return NULL;
	}
	SequenceAnnotation *ann = createSequenceAnnotation((char *)uri);
	// TODO read start, end
	// TODO read strand
	// TODO read annotates, subComponent
	// TODO read precedes
	xmlFree(uri);
	return ann;
}

DNAComponent *readDNAComponent(xmlNode *node) {
	xmlChar *uri = getNodeURI(node);
	if (isSBOLObjectURI(uri)) {
		#if SBOL_DEBUG_ACTIVE
		printf("Tried to read %s twice\n", uri);
		#endif
		return NULL;
	}
	DNAComponent *com = createDNAComponent((char *)uri);
	readSBOLCompoundObject(com->base, node);
	// TODO read sequence
	// TODO read annotations
	// TODO read collections
	xmlFree(uri);
	return com;
}

Collection *readCollection(xmlNode *node) {
	xmlChar *uri = getNodeURI(node);
	if (isSBOLObjectURI(uri)) {
		#if SBOL_DEBUG_ACTIVE
		printf("Tried to read %s twice\n", uri);
		#endif
		return NULL;
	}
	Collection *col = createCollection((char *)uri);
	readSBOLCompoundObject(col->base, node);
	// TODO read components
	// TODO read collections
	xmlFree(uri);
	return col;
}

void readReference(xmlNode *node);

/**************************
 * main parsing functions
 **************************/

// make a first pass through
// to create the SBOL objects
void readSBOLStructs(xmlNode *root) {
	xmlNode *node;
	for (node = root; node; node = node->next) {
		if      (nodeNameEquals(node, "Collection"))   readCollection(node);
		else if (nodeNameEquals(node, "SequenceAnnotation")) readSequenceAnnotation(node);
		else if (nodeNameEquals(node, "DnaComponent")) readDNAComponent(node);
		else if (nodeNameEquals(node, "DnaSequence")) readDNASequence(node);
		readSBOLStructs(node->children);
	}
}

// go back and link up the objects 
// according to rdf:resource nodes
void readSBOLPointers(xmlNode *root) {
	xmlNode *node;
	for (node = root; node; node = node->next) {
		// TODO do stuff here
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
	//readSBOLPointers(root);
	
	// clean up
	xmlFreeDoc(doc);
	xmlCleanupParser();
}
