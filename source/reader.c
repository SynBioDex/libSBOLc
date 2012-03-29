#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @todo remove some of these?
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>

#include "debug.h"
#include "utilities.h"
#include "object.h"
#include "types.h"
#include "array.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"

// these are static mainly to avoid passing them around constantly
static xmlDoc          *DOCUMENT;
static xmlXPathContext *CONTEXT;

/// @todo learn when to use BAD_CAST
//void readNamespaces(xmlNode *node); // TODO is this needed?

/*********************
 * utility functions
 *********************/

xmlChar *getNodeURI(xmlNode *node) {
	if (!node)
		return NULL;
	xmlChar *uri;
	// assume this is a normal node
	uri = xmlGetNsProp(node, BAD_CAST NODENAME_ABOUT, BAD_CAST NSURL_RDF);
	if (!uri)
		// nope, hopefully it's a reference node then
		uri = xmlGetNsProp(node, BAD_CAST NODENAME_RESOURCE, BAD_CAST NSURL_RDF);
	return uri;
}

// adapted from http://student.santarosa.edu/~dturover/?node=libxml2
/// @param node Optionally, search starting from a specific node
/// @return an xmlPathObjectPtr that must be freed with xmlXPathFreeObject()
xmlXPathObjectPtr getNodesMatchingXPath(xmlNode *node, xmlChar *path) {
	if (!path)
		return NULL;
	if (node)
		CONTEXT->node = node;
	xmlXPathObjectPtr result = xmlXPathEvalExpression(path, CONTEXT);
	CONTEXT->node = NULL;
	return result;
}

/// @return a PointerArray* that must freed with deletePointerArray()
PointerArray *getArrayOfNodesMatchingXPath(xmlNode *node, xmlChar *path) {
	xmlXPathObject *results_set;
	PointerArray *results_array;
	xmlNode *result_node;
	int n;
	
	// get results
	results_set = getNodesMatchingXPath(node, path);
	if (!results_set)
		return NULL;
	
	// put them in the array
	results_array = createPointerArray();
	if (results_set->nodesetval && results_set->nodesetval->nodeNr > 0) {
		for (n=0; n < results_set->nodesetval->nodeNr; n++) {
			result_node = results_set->nodesetval->nodeTab[n];
			insertPointerIntoArray(results_array, result_node);
		}
	}
	
	// finish up
	xmlXPathFreeObject(results_set);
	return results_array;
}

/// @return an xmlNode* that doesn't need to be separately freed
xmlNode *getSingleNodeMatchingXPath(xmlNode *node, xmlChar *path) {
	PointerArray *results_array = getArrayOfNodesMatchingXPath(node, path);
	if (!results_array)
		return NULL;
	else if (getNumPointersInArray(results_array) == 0) {
		deletePointerArray(results_array);
		return NULL;
	} else {
		if (getNumPointersInArray(results_array) > 1) {
			#if SBOL_DEBUG_ACTIVE
			printf("Got too many nodes matching xpath %s\n", (char *)path);
			#endif
		}
		xmlNode *result = getNthPointerInArray(results_array, 0);
		deletePointerArray(results_array);
		return result;
	}
}

xmlChar *getContentsOfNodeMatchingXPath(xmlNode *node, xmlChar *path) {
	xmlNode *result = getSingleNodeMatchingXPath(node, path);
	if (result)
		return xmlNodeGetContent(result);
	else
		return NULL;
}

xmlChar *getURIOfNodeMatchingXPath(xmlNode *node, xmlChar *path) {
	xmlNode *result = getSingleNodeMatchingXPath(node, path);
	if (result)
		return getNodeURI(result);
	else
		return NULL;
}

/// @todo put this at the core of the process
void applyFunctionToNodesMatchingXPath(void (*fn)(xmlNode *), xmlNode *node, xmlChar *path) {
	if (!path)
		return;
	xmlXPathObjectPtr results = getNodesMatchingXPath(node, path);
	if (!xmlXPathNodeSetIsEmpty(results->nodesetval)) {
		int n;
		for (n = 0; n < results->nodesetval->nodeNr; n++)
			fn(results->nodesetval->nodeTab[n]);
	}
	xmlXPathFreeObject(results);
}

void processNodes(void (*fn)(xmlNode *), xmlChar *path) {
	applyFunctionToNodesMatchingXPath(fn, NULL, path);
}

/***************************
 * functions for reading
 * individual SBOL objects
 ***************************/

/// @todo either rename or make it so you don't pass the object?
SBOLCompoundObject *readSBOLCompoundObject(SBOLCompoundObject *obj, xmlNode *node) {
	xmlChar *path;
	xmlChar *content;

	// add displayID
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_DISPLAYID;
	if (content = getContentsOfNodeMatchingXPath(node, path)) {
		setSBOLCompoundObjectDisplayID(obj, (char *)content);
		xmlFree(content);
	}

	// add name
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_NAME;
	if (content = getContentsOfNodeMatchingXPath(node, path)) {
		setSBOLCompoundObjectName(obj, (char *)content);
		xmlFree(content);
	}

	// add description
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_DESCRIPTION;
	if (content = getContentsOfNodeMatchingXPath(node, path)) {
		setSBOLCompoundObjectDescription(obj, (char *)content);
		xmlFree(content);
	}

	return obj;
}

void readDNASequenceContent(xmlNode *node) {
	xmlChar *uri;
	xmlChar *path;
	xmlChar *nt;
	DNASequence *seq;

	// create DNASequence
	uri = getNodeURI(node);
	seq = createDNASequence((char *)uri);

	// add nucleotides
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_NUCLEOTIDES;
	if (nt = getContentsOfNodeMatchingXPath(node, path)) {
		setNucleotides(seq, (char *)nt);
		xmlFree(nt);
	}

	xmlFree(uri);
}

void readSequenceAnnotationContent(xmlNode *node) {
	SequenceAnnotation *ann;
	xmlChar *ann_uri;
	xmlChar *path;
	xmlChar *contents;

	// create SequenceAnnotation
	ann_uri = getNodeURI(node);
	ann = createSequenceAnnotation((char *)ann_uri);
	xmlFree(ann_uri);

	// add bioStart
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_BIOSTART;
	if (contents = getContentsOfNodeMatchingXPath(node, path)) {
		setBioStart(ann, strToInt((char *)contents));
		xmlFree(contents);
	}

	// add bioEnd
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_BIOEND;
	if (contents = getContentsOfNodeMatchingXPath(node, path)) {
		setBioEnd(ann, strToInt((char *)contents));
		xmlFree(contents);
	}

	// add strand
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_STRAND;
	if (contents = getContentsOfNodeMatchingXPath(node, path)) {
		setStrandPolarity(ann, strToPolarity((char *)contents));
		xmlFree(contents);
	}
}

void readSequenceAnnotationReferences(xmlNode *node) {
	SequenceAnnotation *ann;
	xmlChar *path;
	xmlChar *ann_uri;
	xmlChar *ref_uri;
	xmlNode *ref_node;
	PointerArray *results;
	int n;

 	// get SequenceAnnotation
	ann_uri = getNodeURI(node);
	ann = getSequenceAnnotation((char *)ann_uri);
	xmlFree(ann_uri);

	// add subComponent
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_SUBCOMPONENT
					 "/" NSPREFIX_SBOL ":" NODENAME_DNACOMPONENT;
	if (ref_uri = getURIOfNodeMatchingXPath(node, path)) {
		setSubComponent(ann, getDNAComponent((char *)ref_uri));
		xmlFree(ref_uri);
	}

	// add precedes
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_PRECEDES;
	if (results = getArrayOfNodesMatchingXPath(node, path)) {
		for (n=0; n<getNumPointersInArray(results); n++) {
			ref_node = (xmlNode *) getNthPointerInArray(results, n);
			ref_uri  = getNodeURI(ref_node);
			addPrecedesRelationship(ann, getSequenceAnnotation((char *)ref_uri));
			xmlFree(ref_uri);
		}
		deletePointerArray(results);
	}
}

void readDNAComponentContent(xmlNode *node) {
    DNAComponent *com;
    xmlChar *com_uri;

    // create DNAComponent
    com_uri = getNodeURI(node);
    com = createDNAComponent((char *)com_uri);
    xmlFree(com_uri);

    // add displayID, name, description
    readSBOLCompoundObject(com->base, node);
}

void readDNAComponentReferences(xmlNode *node) {
    DNAComponent *com;
	xmlChar *path;
    xmlChar *com_uri;
    xmlChar *ref_uri;
    PointerArray *ref_nodes;
    xmlNode *ref_node;
    int n;

    // get DNAComponent
    com_uri = getNodeURI(node);
    com = getDNAComponent((char *)com_uri);
    xmlFree(com_uri);

    // add sequence
    path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_DNASEQUENCE_REF
    				 "/" NSPREFIX_SBOL ":" NODENAME_DNASEQUENCE;
    if (ref_uri = getURIOfNodeMatchingXPath(node, path)) {
        setDNAComponentSequence(com, getDNASequence((char *)ref_uri));
        xmlFree(ref_uri);
    }
    
    // add annotations
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_ANNOTATION
					 "/" NSPREFIX_SBOL ":" NODENAME_SEQUENCEANNOTATION;
    if (ref_nodes = getArrayOfNodesMatchingXPath(node, path)) {
        for (n=0; n<getNumPointersInArray(ref_nodes); n++) {
            ref_node = (xmlNode *) getNthPointerInArray(ref_nodes, n);
            ref_uri = getNodeURI(ref_node);
            addSequenceAnnotation(com, getSequenceAnnotation((char *)ref_uri));
            xmlFree(ref_uri);
        }
        deletePointerArray(ref_nodes);
    }
}

void readCollectionContent(xmlNode *node) {
    Collection *col;
    xmlChar *col_uri;

    // create Collection
    col_uri = getNodeURI(node);
    col = createCollection((char *)col_uri);
    xmlFree(col_uri);

    // add displayID, name, description
    readSBOLCompoundObject(col->base, node);
}

void readCollectionReferences(xmlNode *node) {
    Collection *col;
	xmlChar *path;
    xmlChar *col_uri;
    xmlChar *ref_uri;
    PointerArray *ref_nodes;
    xmlNode *ref_node;
    int n;

    // get Collection
    col_uri = getNodeURI(node);
    col = getCollection((char *)col_uri);
    xmlFree(col_uri);

    // add components
    path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_COMPONENT
    				 "/" NSPREFIX_SBOL ":" NODENAME_DNACOMPONENT;
    if (ref_nodes = getArrayOfNodesMatchingXPath(node, path)) {
        for (n=0; n<getNumPointersInArray(ref_nodes); n++) {
            ref_node = (xmlNode *) getNthPointerInArray(ref_nodes, n);
            ref_uri = getNodeURI(ref_node);
            addDNAComponentToCollection(getDNAComponent((char *)ref_uri), col);
            xmlFree(ref_uri);
        }
        deletePointerArray(ref_nodes);
    }
}

/*************************
 * main parsing function
 *************************/

// TODO return error codes
// this function parses an xml file, validates it,
// and creates matching SBOL objects in memory
void readSBOLCore(char* filename) {

	// parse
	safeXmlInitParser();
	DOCUMENT = xmlParseFile(filename);
	if (!DOCUMENT) {
		printf("Error reading %s\n", filename);
		return;
	}

	// validate
	if (!isValidSBOL(DOCUMENT)) {
		printf("%s is not a valid SBOL document.\n", filename);
		return;
	}
		
	// create XPath context
	CONTEXT = xmlXPathNewContext(DOCUMENT);
	xmlXPathRegisterNs(CONTEXT, "s", NSURL_SBOL);

	#define GLOBAL_XPATH BAD_CAST "//" NSPREFIX_SBOL ":"

	// create all the SBOLObjects
	processNodes(readDNASequenceContent,        GLOBAL_XPATH NODENAME_DNASEQUENCE);
	processNodes(readSequenceAnnotationContent, GLOBAL_XPATH NODENAME_SEQUENCEANNOTATION);
	processNodes(readDNAComponentContent,       GLOBAL_XPATH NODENAME_DNACOMPONENT);
	processNodes(readCollectionContent,         GLOBAL_XPATH NODENAME_COLLECTION);
	
	// link them together with pointers
	processNodes(readSequenceAnnotationReferences, GLOBAL_XPATH NODENAME_SEQUENCEANNOTATION);
	processNodes(readDNAComponentReferences,       GLOBAL_XPATH NODENAME_DNACOMPONENT);
	processNodes(readCollectionReferences,         GLOBAL_XPATH NODENAME_COLLECTION);

	#undef GLOBAL_XPATH
	
	// clean up
	xmlXPathFreeContext(CONTEXT);
	xmlFreeDoc(DOCUMENT);
	xmlCleanupParser();
}
