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

xmlChar *getReferenceNodeURI(xmlNode *node) {
	return xmlGetNsProp(node, (const xmlChar *)"resource", (const xmlChar *)XMLNS_RDF);
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

DNASequence *readDNASequence(xmlNode *node, int pass) {
	xmlChar *uri = getNodeURI(node);
	if (isSBOLObjectURI(uri)) {
		if (pass > 1)
			return getDNASequence((char *)uri);
		#if SBOL_DEBUG_ACTIVE
		else {
			printf("Tried to read %s twice\n", uri);
			return NULL;
		}
		#endif
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

PointerArray *readPointerArray(xmlNode *node) {
	PointerArray *arr = createPointerArray();
	xmlNode *child;
	xmlChar *child_uri;
	for (child = node->children; child; child = child->next) {
		if (!isReferenceNode(child)) {
			#if SBOL_DEBUG_ACTIVE
			printf("Found non-reference node in array of references\n");
			#endif
			continue;
		}
		child_uri = getReferenceURI(child);
		if (!child_uri || !isSBOLObjectURI(child_uri)) {
			#if SBOL_DEBUG_ACTIVE
			printf("Found unknown node in array of references\n");
			#endif
			continue;
		}
		
		xmlFree(child_uri);
	}
}

SequenceAnnotation *readSequenceAnnotation(xmlNode *node, int pass) {
	xmlChar *node_uri = getNodeURI(node);
	if (!node_uri) {
		#if SBOL_DEBUG_ACTIVE
		printf("Failed to get URI for SequenceAnnotation\n");
		#endif
		return NULL;
	}
	
	SequenceAnnotation *ann;
	if (isSequenceAnnotationURI((char *)node_uri))
		ann = getSequenceAnnotation((char *)node_uri);
	#if SBOL_DEBUG_ACTIVE
	else if (isSBOLObjectURI((char *)node_uri))
		printf("%s not a SequenceAnnotation\n", (char *)node_uri);
	#endif
	else
		ann = createSequenceAnnotation((char *)node_uri);
	
	xmlChar *content;
	xmlNode *child;
	xmlChar *child_uri;
	xmlNode *grandchild;
	xmlChar *grandchild_uri;
	
	for (child = node->children; child; child = child->next) {
		if (!child->name)
			continue;
		
		// create annotation
		if (pass == 0) {
			content = xmlNodeGetContent(child);
			if (!content)
				continue;
			else if (nodeNameEquals(child, "bioStart"))
				setBioStart(ann, strToInt((char *)content));
			else if (nodeNameEquals(child, "bioEnd"))
				setBioEnd(ann, strToInt((char *)content));
			else if (nodeNameEquals(child, "strand"))
				setStrandPolarity(ann, strToPolarity((char *)content));
			xmlFree(content);
		} else {
		
			// add references to other SBOL objects
			for (grandchild = child->children; grandchild; grandchild = grandchild->next) {
				if (!isReferenceNode(grandchild)) {
					#if SBOL_DEBUG_ACTIVE
					printf("Got non-reference node by accident\n");
					#endif
					continue;
				}
				else if (nodeNameEquals(child, "annotates"))
					addSequenceAnnotation(getDNAComponent((char *)grandchild_uri), ann);
				else if (nodeNameEquals(child, "subComponent"))
					setSubComponent(ann, getDNAComponent((char *)grandchild_uri));
				else if (nodeNameEquals(child, "precedes"))
					addPrecedesRelationship(ann, getSequenceAnnotation((char *)grandchild_uri));
				#if SBOL_DEBUG_ACTIVE
				else
					printf("Unknown node referenced by %s\n", ann);
				#endif
				xmlFree(grandchild_uri);
			}
		}
		xmlFree(child_uri);
	}
	xmlFree(node_uri);
	return ann;
}

DNAComponent *readDNAComponent(xmlNode *node, int pass) {
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

Collection *readCollection(xmlNode *node, int pass) {
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

/**************************
 * main parsing functions
 **************************/

// make a first pass through to create the SBOL objects
// then go back and link them up according to rdf:resource nodes
void readSBOLObjects(xmlNode *root, int pass) {
	xmlNode *node;
	for (node = root; node; node = node->next) {
		if      (nodeNameEquals(node, "Collection"))         readCollection(node, pass);
		else if (nodeNameEquals(node, "SequenceAnnotation")) readSequenceAnnotation(node, pass);
		else if (nodeNameEquals(node, "DnaComponent"))       readDNAComponent(node, pass);
		else if (nodeNameEquals(node, "DnaSequence"))        readDNASequence(node, pass);
		readSBOLObjects(node->children, pass);
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
	readSBOLObjects(root, 0);
	readSBOLObjects(root, 1);
	
	// clean up
	xmlFreeDoc(doc);
	xmlCleanupParser();
}
