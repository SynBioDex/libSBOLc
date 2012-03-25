#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>

#include "debug.h"
#include "object.h"
#include "types.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"

/*************************
 * functions for reading
 * node properties
 *************************/

xmlChar *getNodeURI(xmlNode *node) {
	xmlChar *uri = NULL;
	if (node) {
		if (isReferenceNode(node))
			uri = xmlGetNsProp(node, (const xmlChar *)"resource", (const xmlChar *)XMLNS_RDF);
		else
			uri = xmlGetNsProp(node, (const xmlChar *)"about", (const xmlChar *)XMLNS_RDF);
	}
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

//void readNamespaces(xmlNode *node); // TODO is this needed?

SBOLCompoundObject *readSBOLCompoundObject(SBOLCompoundObject *obj, xmlNode *node) {
	xmlNode *child;
	char *content;
	for (child = node->children; child; child = child->next) {
		if (child->name) {
			content = (char *)xmlNodeGetContent(child);
			if (!content) continue;
			// TODO #define these
			else if (nodeNameEquals(child, "displayId"))
				setSBOLCompoundObjectDisplayID(obj, content);
			else if (nodeNameEquals(child, "name"))
				setSBOLCompoundObjectName(obj, content);
			else if (nodeNameEquals(child, "description"))
				setSBOLCompoundObjectDescription(obj, content);
			free(content);
		}
	}
	return obj;
}

DNASequence *readDNASequence(xmlNode *node, int pass) {
	xmlChar *uri = getNodeURI(node);
	if (isSBOLObjectURI((char *)uri)) {
		if (pass > 0)
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
	xmlChar *content;
	for (child = node->children; child; child = child->next) {
		if (!child->name) continue;
		content = xmlNodeGetContent(child);
		if (!(char *)content) continue;
		// TODO #define this
		else if (nodeNameEquals(child, "nucleotides")) {
			setNucleotides(seq, (char *)content);
			break;
		}
		xmlFree(content);
	}
	
	xmlFree(uri);
	return seq;
}

SequenceAnnotation *readSequenceAnnotation(xmlNode *node, int pass) {
	xmlNode *ann_node = NULL;
	xmlNode *pro_node = NULL;
	xmlNode *ref_node = NULL;

	xmlChar *ann_uri = NULL;
	xmlChar *pro_uri = NULL;
	xmlChar *ref_uri = NULL;
	
	SequenceAnnotation *ann = NULL;
	xmlChar   *pro_contents = NULL;
	
	// get annotation uri
	ann_node = node;
	ann_uri = getNodeURI(ann_node);
	if (!ann_uri) {
		#if SBOL_DEBUG_ACTIVE
		printf("Failed to get URI for SequenceAnnotation\n");
		#endif
		return NULL;
	}
	
	if (pass == 0) {
		// create annotation
		if (isSBOLObjectURI((char *)ann_uri)) {
			#if SBOL_DEBUG_ACTIVE
			printf("Tried to create duplicate object %s\n", (char *)ann_uri);
			#endif
			return NULL;
		}
		ann = createSequenceAnnotation((char *)ann_uri);
	} else {
	
		// get annotation
		if (!isSBOLObjectURI(ann_uri)) {
			#if SBOL_DEBUG_ACTIVE
			printf("Failed to create SequenceAnnotation %s\n", (char *)ann_uri);
			#endif
			return NULL;
		} else if (!isSequenceAnnotationURI(ann_uri)) {
			#if SBOL_DEBUG_ACTIVE
			printf("%s not a SequenceAnnotation\n", (char *)ann_uri);
			#endif
			return NULL;
		}
		ann = getSequenceAnnotation((char *)ann_uri);
	}
	
	// add things to annotation
	for (pro_node = ann_node->children; pro_node; pro_node = pro_node->next) {
		if (!pro_node->name)
			continue;
		else if (pass == 0) {
		
			// add basic property
			pro_contents = xmlNodeGetContent(pro_node);
			if (!pro_contents)
				continue;
			else if (nodeNameEquals(pro_node, "bioStart"))
				setBioStart(ann, strToInt((char *)pro_contents));
			else if (nodeNameEquals(pro_node, "bioEnd"))
				setBioEnd(ann, strToInt((char *)pro_contents));
			else if (nodeNameEquals(pro_node, "strand"))
				setStrandPolarity(ann, strToPolarity((char *)pro_contents));
			xmlFree(pro_contents);
		} else {
		
			// objects have all been created;
			// time to link them together
			if (isReferenceNode(pro_node)) {
			
				//add single pointer to another SBOL object
				ref_node = pro_node;
				ref_uri = getNodeURI(ref_node);
				if (nodeNameEquals(pro_node, "annotates"))
					addSequenceAnnotation(getDNAComponent((char *)ref_uri), ann);
				else if (nodeNameEquals(pro_node, "subComponent")) {
					printf("subComponent: %s\n", (char *)getNodeURI(pro_node));
					setSubComponent(ann, getDNAComponent((char *)ref_uri));
				}
				else if (nodeNameEquals(pro_node, "precedes"))
					addPrecedesRelationship(ann, getSequenceAnnotation((char *)ref_uri));
				#if SBOL_DEBUG_ACTIVE
				else
					printf("Unknown reference node %s\n", ref_node->name);
				#endif
				xmlFree(ref_uri);
			} else {
				for (ref_node = pro_node->children; ref_node; ref_node = ref_node->next) {
					if (!ref_node->name || ref_node->type == XML_TEXT_NODE)
						continue;
					ref_uri = getNodeURI(ref_node);
					if (nodeNameEquals(ref_node, "DnaComponent"))
						setSubComponent(ann, getDNAComponent((char *)ref_uri));
					#if SBOL_DEBUG_ACTIVE
					else
						printf("Unknown reference node %s\n", ref_node->name);
					#endif
					xmlFree(ref_uri);
				}
			}
		}
	}
	xmlFree(ann_uri);
	return ann;
}

DNAComponent *readDNAComponent(xmlNode *node, int pass) {
	DNAComponent *com = NULL;
	
	xmlNode *com_node = NULL;
	xmlNode *pro_node = NULL;
	xmlNode *ref_node = NULL;
	
	xmlChar *com_uri = NULL;
	xmlChar *pro_uri = NULL;
	xmlChar *ref_uri = NULL;
	
	com_node = node;
	com_uri = getNodeURI(com_node);
	if (pass == 0) {
		// create component
		// and add basic properties
		if (isSBOLObjectURI(com_uri)) {
			#if SBOL_DEBUG_ACTIVE
			printf("Tried to read %s twice\n", com_uri);
			#endif
			return NULL;
		}
		com = createDNAComponent((char *)com_uri);
		readSBOLCompoundObject(com->base, com_node);
	} else {
	
		// get component
		if (!isDNAComponentURI((char *)com_uri)) {
			#if SBOL_DEBUG_ACTIVE
			printf("Failed to create DNAComponent %s\n", com_uri);
			#endif
			return NULL;
		}
		com = getDNAComponent((char *)com_uri);
		
		// add links to other SBOL objects
		for (pro_node = com_node->children; pro_node; pro_node = pro_node->next) {
			if (!pro_node->name || pro_node->type == XML_TEXT_NODE)
				continue;
			for (ref_node = pro_node->children; ref_node; ref_node = ref_node->next) {
					if (!ref_node->name || ref_node->type == XML_TEXT_NODE)
						continue;
					ref_uri = getNodeURI(ref_node);
					if (nodeNameEquals(ref_node, "DnaSequence"))
						setDNAComponentSequence(com, getDNASequence((char *)ref_uri));
					else if (nodeNameEquals(ref_node, "SequenceAnnotation"))
						addSequenceAnnotation(com, getSequenceAnnotation((char *)ref_uri));
					else if (nodeNameEquals(ref_node, "Collection"))
						addDNAComponentToCollection(com, getCollection((char *)ref_uri));
					#if SBOL_DEBUG_ACTIVE
					else
						printf("Unknown reference node %s\n", ref_node->name);
					#endif
					xmlFree(ref_uri);
			}
		}
	
	}
	
	xmlFree(com_uri);
	return com;
}

Collection *readCollection(xmlNode *node, int pass) {
	xmlNode *col_node;
	xmlNode *pro_node;
	xmlNode *ref_node;
	xmlChar *col_uri;
	//xmlChar *pro_uri;
	xmlChar *ref_uri;
	Collection *col;

	col_node = node;
	col_uri = getNodeURI(col_node);
	if (pass == 0) {
	
		// create collection with some basic properties
		if (isSBOLObjectURI(col_uri)) {
			#if SBOL_DEBUG_ACTIVE
			printf("Tried to read %s twice\n", col_uri);
			#endif
			return NULL;
		}
		col = createCollection((char *)col_uri);
		readSBOLCompoundObject(col->base, col_node);
	} else {

		// retrieve the collection
		if (!isCollectionURI(col_uri)) {
			#if SBOL_DEBUG_ACTIVE
			printf("Failed to create Collection %s\n", col_uri);
			#endif
			return NULL;
		}
		col = getCollection((char *)col_uri);
		
		// add links to other SBOL objects
		for (pro_node = col_node->children; pro_node; pro_node = pro_node->next) {
			if (!pro_node->name || pro_node->type == XML_TEXT_NODE)
				continue;
			// TODO find out if both cases are possible or just one...
			if (isReferenceNode(pro_node)) {
				ref_node = pro_node;
				ref_uri = getNodeURI(ref_node);
				if (nodeNameEquals(ref_node, "component"))
					addDNAComponentToCollection(getDNAComponent((char *)ref_uri), col);
				else if (nodeNameEquals(ref_node, "Collection"))
					addCollectionToCollection(getCollection((char *)ref_uri), col);
				xmlFree(ref_uri);
			} else {
				for (ref_node = pro_node->children; ref_node; ref_node = ref_node->next) {
						if (!ref_node->name || ref_node->type == XML_TEXT_NODE)
							continue;
						ref_uri = getNodeURI(ref_node);
						if (nodeNameEquals(ref_node, "DnaComponent"))
							addDNAComponentToCollection(getDNAComponent((char *)ref_uri), col);
						else if (nodeNameEquals(ref_node, "Collection"))
							 addCollectionToCollection(getCollection((char *)ref_uri), col);
						#if SBOL_DEBUG_ACTIVE
						else
							printf("Unknown reference node %s\n", ref_node->name);
						#endif
						xmlFree(ref_uri);
				}
			}
		}
	}
	xmlFree(col_uri);
	return col;
}

/**************************
 * main parsing functions
 **************************/

// this function should be called twice on every node:
// the first pass (pass == 0) creates SBOL objects,
// and the second (pass > 0) links them together with pointers
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
// this function parses an xml file, validates it,
// and creates matching SBOL objects in memory
void readSBOLCore(char* filename) {
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
