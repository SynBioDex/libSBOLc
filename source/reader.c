#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	uri = xmlGetNsProp(node, (const xmlChar *)"about", (const xmlChar *)XMLNS_RDF);
	if (!uri)
		// nope, hopefully it's a reference node then
		uri = xmlGetNsProp(node, (const xmlChar *)"resource", (const xmlChar *)XMLNS_RDF);
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
	xmlChar *content;

	// add displayID
	if (content = getContentsOfNodeMatchingXPath(node, BAD_CAST "./s:displayId")) {
		setSBOLCompoundObjectDisplayID(obj, (char *)content);
		xmlFree(content);
	}

	// add name
	if (content = getContentsOfNodeMatchingXPath(node, BAD_CAST "./s:name")) {
		setSBOLCompoundObjectName(obj, (char *)content);
		xmlFree(content);
	}

	// add description
	if (content = getContentsOfNodeMatchingXPath(node, BAD_CAST "./s:description")) {
		setSBOLCompoundObjectDescription(obj, (char *)content);
		xmlFree(content);
	}

	return obj;
}

void readDNASequenceContent(xmlNode *node) {
	xmlChar *uri;
	xmlChar *nt;
	DNASequence *seq;

	// create DNASequence
	uri = getNodeURI(node);
	seq = createDNASequence((char *)uri);

	// add nucleotides
	if (nt = getContentsOfNodeMatchingXPath(node, BAD_CAST "./s:nucleotides")) {
		setNucleotides(seq, (char *)nt);
		xmlFree(nt);
	}

	xmlFree(uri);
}

void readSequenceAnnotationContent(xmlNode *node) {
	SequenceAnnotation *ann;
	xmlChar *ann_uri;
	xmlChar *contents;

	// create SequenceAnnotation
	ann_uri = getNodeURI(node);
	ann = createSequenceAnnotation((char *)ann_uri);
	xmlFree(ann_uri);

	// add bioStart
	if (contents = getContentsOfNodeMatchingXPath(node, BAD_CAST "./s:bioStart")) {
		setBioStart(ann, strToInt((char *)contents));
		xmlFree(contents);
	}

	// add bioEnd
	if (contents = getContentsOfNodeMatchingXPath(node, BAD_CAST "./s:bioEnd")) {
		setBioEnd(ann, strToInt((char *)contents));
		xmlFree(contents);
	}

	// add strand
	if (contents = getContentsOfNodeMatchingXPath(node, BAD_CAST "./s:strand")) {
		setStrandPolarity(ann, strToPolarity((char *)contents));
		xmlFree(contents);
	}
}

void readSequenceAnnotationReferences(xmlNode *node) {
	SequenceAnnotation *ann;
	xmlChar *ann_uri;
	xmlChar *ref_uri;
	xmlNode *ref_node;
	PointerArray *results;
	int n;

 	// get SequenceAnnotation
	ann_uri = getNodeURI(node);
	ann = getSequenceAnnotation((char *)ann_uri);
	xmlFree(ann_uri);

	// add annotates
	if (ref_uri = getURIOfNodeMatchingXPath(node, BAD_CAST "./s:annotates/s:DnaComponent")) {
		addSequenceAnnotation(getDNAComponent((char *)ref_uri), ann);
		xmlFree(ref_uri);
	}

	// add subComponent
	if (ref_uri = getURIOfNodeMatchingXPath(node, BAD_CAST "./s:subComponent/s:DnaComponent")) {
		setSubComponent(ann, getDNAComponent((char *)ref_uri));
		xmlFree(ref_uri);
	}

	// add precedes
	if (results = getArrayOfNodesMatchingXPath(node, BAD_CAST "./s:precedes")) {
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
    if (ref_uri = getURIOfNodeMatchingXPath(node, BAD_CAST "./s:dnaSequence/s:DnaSequence")) {
        setDNAComponentSequence(com, getDNASequence((char *)ref_uri));
        xmlFree(ref_uri);
    }
    
    // add annotations
    if (ref_nodes = getArrayOfNodesMatchingXPath(node, BAD_CAST "./s:annotation/s:SequenceAnnotation")) {
        for (n=0; n<getNumPointersInArray(ref_nodes); n++) {
            ref_node = (xmlNode *) getNthPointerInArray(ref_nodes, n);
            ref_uri = getNodeURI(ref_node);
            addSequenceAnnotation(com, getSequenceAnnotation((char *)ref_uri));
            xmlFree(ref_uri);
        }
        deletePointerArray(ref_nodes);
    }
    
    // add collections
    if (ref_nodes = getArrayOfNodesMatchingXPath(node, BAD_CAST "./s:collections/s:Collection")) {
        for (n=0; n<getNumPointersInArray(ref_nodes); n++) {
            ref_node = (xmlNode *) getNthPointerInArray(ref_nodes, n);
            ref_uri = getNodeURI(ref_node);
            addDNAComponentToCollection(com, getCollection((char *)ref_uri));
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
    if (ref_nodes = getArrayOfNodesMatchingXPath(node, BAD_CAST "./s:component/s:DnaComponent")) {
        for (n=0; n<getNumPointersInArray(ref_nodes); n++) {
            ref_node = (xmlNode *) getNthPointerInArray(ref_nodes, n);
            ref_uri = getNodeURI(ref_node);
            addDNAComponentToCollection(getDNAComponent((char *)ref_uri), col);
            xmlFree(ref_uri);
        }
        deletePointerArray(ref_nodes);
    }
    
    // add collections
    if (ref_nodes = getArrayOfNodesMatchingXPath(node, BAD_CAST "./s:collections/s:Collection")) {
        for (n=0; n<getNumPointersInArray(ref_nodes); n++) {
            ref_node = (xmlNode *) getNthPointerInArray(ref_nodes, n);
            ref_uri = getNodeURI(ref_node);
            addCollectionToCollection(getCollection((char *)ref_uri), col);
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
	xmlXPathRegisterNs(CONTEXT, BAD_CAST "rdf", BAD_CAST XMLNS_RDF);
	xmlXPathRegisterNs(CONTEXT, BAD_CAST "s", BAD_CAST XMLNS_SBOL);

	// create all the SBOLObjects
	processNodes(readDNASequenceContent,        BAD_CAST "//s:DnaSequence");
	processNodes(readSequenceAnnotationContent, BAD_CAST "//s:SequenceAnnotation");
	processNodes(readDNAComponentContent,       BAD_CAST "//s:DnaComponent");
	processNodes(readCollectionContent,         BAD_CAST "//s:Collection");
	
	// link them together with pointers
	processNodes(readSequenceAnnotationReferences, BAD_CAST "//s:SequenceAnnotation");
	processNodes(readDNAComponentReferences,       BAD_CAST "//s:DnaComponent");
	processNodes(readCollectionReferences,         BAD_CAST "//s:Collection");
	
	// clean up
	xmlXPathFreeContext(CONTEXT);
	xmlFreeDoc(DOCUMENT);
	xmlCleanupParser();
}
