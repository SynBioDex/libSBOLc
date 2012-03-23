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

int isReferenceNode(xmlNode *node) {
	xmlChar *resource = NULL;
	if (node)
		// #define this
		resource = xmlGetNsProp(node, (const xmlChar *)"resource", (const xmlChar *)XMLNS_RDF);
	int result;
	if (resource)
		result = 1;
	else
		result = 0;
	xmlFree(resource);
	return result;
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
			free(content);
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
		
	// create sequence
	DNASequence *seq = createDNASequence((char *)uri);
	
	// add nucleotides
	xmlNode *child;
	char *content;
	for (child = node->children; child; child = child->next) {
		if (!child->name) continue;
		content = (char *)xmlNodeGetContent(child);
		if (!content) continue;
		// TODO #define this
		else if (nodeNameEquals(child, "nucleotides")) {
			setNucleotides(seq, content);
			break;
		}
		free(content);
	}
	
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
	
	// create annotation
	SequenceAnnotation *ann = createSequenceAnnotation((char *)uri);
	
	// configure it based on child nodes
	xmlNode *child;
	char *content;
	for (child = node->children; child; child = child->next) {
		if (!child->name) continue;
		content = (char *)xmlNodeGetContent(child);
		if (!content) continue;
		// TODO #define these
		else if (nodeNameEquals(child, "bioStart")) setBioStart(ann, strToInt(content));
		else if (nodeNameEquals(child, "bioEnd"))   setBioEnd(ann, strToInt(content));
		else if (nodeNameEquals(child, "strand"))   setStrandPolarity(ann, strToPolarity(content));
		// TODO read annotates, subComponent
		// TODO read precedes
	}
	
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

// read a node with an rdf:resource attribute
// and link up the appropriate SBOL objects
void readReference(xmlNode *node) {
	xmlNode *parent;
	xmlChar *node_uri;
	xmlChar *parent_uri;
	// TODO #define this
	node_uri = xmlGetNsProp(node, (const xmlChar *)"resource", (const xmlChar *)XMLNS_RDF);
	if (node_uri && isSBOLObjectURI((char *)node_uri)) {
		parent = node->parent;
		if (!parent) {
			#if SBOL_DEBUG_ACTIVE
			printf("NULL parent node while reading reference\n");
			#endif
			return;
		}
		parent_uri = getNodeURI(parent);
		if (!parent_uri) {
			#if SBOL_DEBUG_ACTIVE
			printf("NULL parent uri while reading reference\n");
			#endif
			return;
		}
		if (isSequenceAnnotationURI((char *)parent_uri)) {
			SequenceAnnotation *ann = getSequenceAnnotation((char *)parent_uri);
			if (!ann) {
				#if SBOL_DEBUG_ACTIVE
				printf("Failed to get SequenceAnnotation %s\n", (char *)node_uri);
				#endif
				return;
			}
			else if (nodeNameEquals(node, "annotates"))
				addSequenceAnnotation(getDNAComponent((char *)node_uri), ann);
			else if (nodeNameEquals(node, "subComponent"))
				setSubComponent(ann, getDNAComponent((char *)node_uri));
			// TODO read precedes
		
		} else if (isDNAComponentURI((char *)parent_uri)) {
			// TODO read annotations
			// TODO read collections
		
		} else if (isCollectionURI((char *)parent_uri)) {
			// TODO read components
			// TODO read collections
		}
	}
	#if SBOL_DEBUG_ACTIVE
	else
		printf("Tried to reference nonexistent object %s\n", node_uri);
	#endif
	xmlFree(node_uri);
}

/**************************
 * main parsing functions
 **************************/

// make a first pass through
// to create the SBOL objects
void readSBOLStructs(xmlNode *root) {
	xmlNode *node;
	for (node = root; node; node = node->next) {
		if      (nodeNameEquals(node, "Collection"))         readCollection(node);
		else if (nodeNameEquals(node, "SequenceAnnotation")) readSequenceAnnotation(node);
		else if (nodeNameEquals(node, "DnaComponent"))       readDNAComponent(node);
		else if (nodeNameEquals(node, "DnaSequence"))        readDNASequence(node);
		readSBOLStructs(node->children);
	}
}

// go back and link up the objects 
// according to rdf:resource nodes
void readSBOLPointers(xmlNode *root) {
	xmlNode *node;
	for (node = root; node; node = node->next) {
		if (isReferenceNode(node))
			readReference(node);
		readSBOLPointers(node->children);
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
	
	// clean up
	xmlFreeDoc(doc);
	xmlCleanupParser();
}
