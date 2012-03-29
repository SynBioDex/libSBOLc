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
#include "array.h"
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

/// @todo remove once XPath parser completed
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

/**************************
 * utility functions for
 * the XPath-based parser
 **************************/

static xmlDoc          *DOCUMENT;
static xmlXPathContext *CONTEXT;

/// @todo learn when to use BAD_CAST

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

/***************************
 * functions for reading
 * individual SBOL objects
 ***************************/

//void readNamespaces(xmlNode *node); // TODO is this needed?

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

DNASequence *readDNASequenceContent(xmlNode *node) {
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
	return seq;
}

SequenceAnnotation *readSequenceAnnotationContent(xmlNode *node) {
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

/// @todo don't need to return the annotation
SequenceAnnotation *readSequenceAnnotationReferences(xmlNode *node) {
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

/// @todo don't need to return the component
DNAComponent *readDNAComponentContent(xmlNode *node) {
    DNAComponent *com;
    xmlChar *com_uri;

    // create DNAComponent
    com_uri = getNodeURI(node);
    com = createDNAComponent((char *)com_uri);
    xmlFree(com_uri);

    // add displayID, name, description
    readSBOLCompoundObject(com->base, node);

    return com;
}

DNAComponent *readDNAComponentReferences(xmlNode *node) {
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

Collection *readCollectionContents(xmlNode *node) {
    Collection *col;
    xmlChar *col_uri;

    // create Collection
    col_uri = getNodeURI(node);
    col = createCollection((char *)col_uri);
    xmlFree(col_uri);

    // add displayID, name, description
    readSBOLCompoundObject(col->base, node);

    return col;
}

Collection *readCollectionReferences(xmlNode *node) {
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

/// @todo remove this
DNASequence *readDNASequence(xmlNode *node, int pass) {
    if (pass == 0)
        return readDNASequenceContent(node);
    else
        return getDNASequence( getNodeURI(node) );
}

/// @todo remove this
SequenceAnnotation *readSequenceAnnotation(xmlNode *node, int pass) {
	if (pass == 0)
		return readSequenceAnnotationContent(node);
	else
		return readSequenceAnnotationReferences(node);
}

/// @todo remove this
DNAComponent *readDNAComponent(xmlNode *node, int pass) {
    if (pass == 0)
        return readDNAComponentContent(node);
    else
        return readDNAComponentReferences(node);
}

/// @todo remove this
Collection *readCollection(xmlNode *node, int pass) {
    if (pass == 0)
        return readCollectionContents(node);
    else
        return readCollectionReferences(node);
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
	//xmlDocPtr  doc;

	// this initializes the library and checks potential ABI mismatches
	// between the version it was compiled for and the actual shared
	// library used.
	xmlInitParser();
	LIBXML_TEST_VERSION
	
	// parse
	DOCUMENT = xmlParseFile(filename);

	// create XPath context
	CONTEXT = xmlXPathNewContext(DOCUMENT);
	xmlXPathRegisterNs(CONTEXT, BAD_CAST "rdf", BAD_CAST XMLNS_RDF);
	xmlXPathRegisterNs(CONTEXT, BAD_CAST "s", BAD_CAST XMLNS_SBOL);

	// workaround for a problem with libxml2 and MinGW
	// google: "using libxml2 on MinGW - xmlFree crashes"
	/// @todo put this in a function along with LIBXML_TEST_VERSION
	if (!xmlFree)
		xmlMemGet( &xmlFree, &xmlMalloc, &xmlRealloc, NULL );

	if (!DOCUMENT) {
		printf("Error reading %s\n", filename);
		return;
	}
	
	// validate
	if (!isValidSBOL(DOCUMENT)) {
		printf("%s is not a valid SBOL document.\n", filename);
		return;
	}
	
	// import
	readSBOLObjects(xmlDocGetRootElement(DOCUMENT), 0);
	readSBOLObjects(xmlDocGetRootElement(DOCUMENT), 1);
	
	// clean up
	/// @todo cleanupSBOLParser
	xmlXPathFreeContext(CONTEXT); CONTEXT  = NULL;
	xmlFreeDoc(DOCUMENT);         DOCUMENT = NULL;
	xmlCleanupParser();
}
