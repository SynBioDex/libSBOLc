#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/xpath.h>

#include "array.h"
#include "document.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"
#include "reader.h"
#include "object.h"

#include "sbol.h"

// these are static mainly to avoid passing them around constantly
static xmlDoc          *DOCUMENT;
static xmlXPathContext *CONTEXT;
static Document        *DESTINATION;

/*********************
 * utility functions
 *********************/

static xmlChar *getNodeURI(xmlNode *node) {
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

static PointerArray *getNodesMatchingXPath(xmlNode *node, xmlChar *path) {
    if (!path)
        return NULL;

	xmlXPathObject *results_set;
	PointerArray *results_array;
	xmlNode *result_node;
	int n;
	
	// get results
    if (node)
        CONTEXT->node = node;
	results_set = xmlXPathEvalExpression(path, CONTEXT);
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
	CONTEXT->node = NULL;
	return results_array;
}

static xmlNode *getSingleNodeMatchingXPath(xmlNode *node, xmlChar *path) {
	PointerArray *results_array = getNodesMatchingXPath(node, path);
	if (!results_array)
		return NULL;
	else if (getNumPointersInArray(results_array) == 0) {
		deletePointerArray(results_array);
		return NULL;
	} else {
		if (getNumPointersInArray(results_array) > 1) {
			#ifdef SBOL_DEBUG_STATEMENTS
			printf("Got too many nodes matching xpath %s\n", (char *)path);
			#endif
		}
		xmlNode *result = getNthPointerInArray(results_array, 0);
		deletePointerArray(results_array);
		return result;
	}
}

static xmlChar *getContentsOfNodeMatchingXPath(xmlNode *node, xmlChar *path) {
	xmlNode *result = getSingleNodeMatchingXPath(node, path);
	if (result)
		return xmlNodeGetContent(result);
	else
		return NULL;
}

static xmlChar *getURIOfNodeMatchingXPath(xmlNode *node, xmlChar *path) {
	xmlNode *result = getSingleNodeMatchingXPath(node, path);
	if (result)
		return getNodeURI(result);
	else
		return NULL;
}

static void applyFunctionToNodesMatchingXPath(void (*fn)(xmlNode *), xmlNode *node, xmlChar *path) {
	if (!path)
		return;
	PointerArray *results = getNodesMatchingXPath(node, path);
	if (results) {
        if (getNumPointersInArray(results) > 0) {
            int n;
            for (n=0; n<getNumPointersInArray(results); n++)
                fn(getNthPointerInArray(results, n));
        }
	deletePointerArray(results);
    }
}

static void processNodes(void (*read)(xmlNode *), xmlChar *path) {
	applyFunctionToNodesMatchingXPath(read, NULL, path);
}

/***************************
 * functions for reading
 * individual SBOL objects
 ***************************/

static void readSBOLCompoundObject(SBOLCompoundObject *obj, xmlNode *node) {
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
}

static void readDNASequenceContent(xmlNode *node) {
	xmlChar *uri;
	xmlChar *path;
	xmlChar *nt;
	DNASequence *seq;

	// create DNASequence
	uri = getNodeURI(node);
	seq = createDNASequence(DESTINATION, (char *)uri);

	// add nucleotides
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_NUCLEOTIDES;
	if (nt = getContentsOfNodeMatchingXPath(node, path)) {
		setDNASequenceNucleotides(seq, (char *)nt);
		xmlFree(nt);
	}

	xmlFree(uri);
}

static void readSequenceAnnotationContent(xmlNode *node) {
	SequenceAnnotation *ann;
	xmlChar *ann_uri;
	xmlChar *path;
	xmlChar *contents;

	// create SequenceAnnotation
	ann_uri = getNodeURI(node);
	ann = createSequenceAnnotation(DESTINATION, (char *)ann_uri);
	xmlFree(ann_uri);

	// add bioStart
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_BIOSTART;
	if (contents = getContentsOfNodeMatchingXPath(node, path)) {
		setSequenceAnnotationStart(ann, strToInt((char *)contents));
		xmlFree(contents);
	}

	// add bioEnd
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_BIOEND;
	if (contents = getContentsOfNodeMatchingXPath(node, path)) {
		setSequenceAnnotationEnd(ann, strToInt((char *)contents));
		xmlFree(contents);
	}

	// add strand
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_STRAND;
	if (contents = getContentsOfNodeMatchingXPath(node, path)) {
		setSequenceAnnotationStrand(ann, strToPolarity((char *)contents));
		xmlFree(contents);
	}
}

static void readSequenceAnnotationReferences(xmlNode *node) {
	SequenceAnnotation *ann;
	xmlChar *path;
	xmlChar *ann_uri;
	xmlChar *ref_uri;
	xmlNode *ref_node;
	PointerArray *results;
	int n;

 	// get SequenceAnnotation
	ann_uri = getNodeURI(node);
	ann = getSequenceAnnotation(DESTINATION, (char *)ann_uri);
	xmlFree(ann_uri);

	// add subComponent
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_SUBCOMPONENT
					 "/" NSPREFIX_SBOL ":" NODENAME_DNACOMPONENT;
	if (ref_uri = getURIOfNodeMatchingXPath(node, path)) {
		setSequenceAnnotationSubComponent(ann, getDNAComponent(DESTINATION, (char *)ref_uri));
		xmlFree(ref_uri);
	}

	// add precedes
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_PRECEDES;
	if (results = getNodesMatchingXPath(node, path)) {
		for (n=0; n<getNumPointersInArray(results); n++) {
			ref_node = (xmlNode *) getNthPointerInArray(results, n);
			ref_uri  = getNodeURI(ref_node);
			addPrecedesRelationship(ann, getSequenceAnnotation(DESTINATION, (char *)ref_uri));
			xmlFree(ref_uri);
		}
		deletePointerArray(results);
	}
}

static void readDNAComponentContent(xmlNode *node) {
    DNAComponent *com;
    xmlChar *com_uri;
	xmlChar *path;
	xmlChar *type_property;
	xmlNode *type_node;
	xmlNode *child_node;
	xmlNode *test_node;
	//xmlOutputBufferPtr buffer;
	PointerArray *results;
	int n;

    // create DNAComponent
    com_uri = getNodeURI(node);
    com = createDNAComponent(DESTINATION, (char *)com_uri);
    xmlFree(com_uri);

    // add displayID, name, description
    readSBOLCompoundObject(com->base, node);
    
    // add type
	path = NSPREFIX_RDF ":" NODENAME_TYPE;
	if (results = getNodesMatchingXPath(node, path)) {
		type_node = (xmlNode *)getNthPointerInArray(results, 0);
		type_property = xmlGetNsProp(type_node, BAD_CAST NODENAME_RESOURCE, BAD_CAST NSURL_RDF);
		setDNAComponentType(com, (char *)type_property);
		xmlFree(results);
	}

	//printf("%s\n", (char *)node->name);
	child_node = node->children;
	while (child_node) {
		//if ((char *)result->name == "text") {
		//	printf("Node content:%s\n", (char *)xmlNodeGetContent(result));
		//if (result->type == XML_TEXT_NODE) {
		//printf("Node content:%s\n", (char *)xmlNodeGetContent(result));
		//printf("Node content:%s\n", (char *)result->content);
		//}
		//printf("Node content:%s\n", (char *)xmlNodeGetContent(result));
		//printf("%s\n", (char *)child_node->name);
		if (child_node->ns &&
			strcmp((char*)child_node->ns->href, NSURL_RDF) != 0 &&
			strcmp((char*)child_node->ns->href, NSURL_RDFS) != 0 &&
			strcmp((char*)child_node->ns->href, NSURL_SO) != 0 &&
			strcmp((char*)child_node->ns->href, NSURL_SBOL) != 0) {
			printf("%s:\t%s\n", child_node->ns->prefix, child_node->ns->href);
			xmlBufferPtr buffer = xmlBufferCreate();
			xmlKeepBlanksDefault(0);
			int size = xmlNodeDump(buffer, DOCUMENT, child_node, 0, 0);
			printf("%s\n", buffer->content);
			//xmlNodeDumpOutput(buffer, DOCUMENT, child_node, 0, 1, "UTF-8");
			//xmlChar *s;
			//int size;

			//xmlDocDumpMemory((xmlDocPtr)child_node, &s, &size);

			//printf("%s\n", (char *)s);
			//xmlFree(s);
		}
	child_node = child_node->next;
	}
	xmlFree(test_node);
	//xmlFree(child_node);
}

static void readDNAComponentReferences(xmlNode *node) {
    DNAComponent *com;
	xmlChar *path;
    xmlChar *com_uri;
    xmlChar *ref_uri;
    PointerArray *ref_nodes;
    xmlNode *ref_node;
    int n;

    // get DNAComponent
    com_uri = getNodeURI(node);
    com = getDNAComponent(DESTINATION, (char *)com_uri);
    xmlFree(com_uri);

    // add sequence
    path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_DNASEQUENCE_REF
    				 "/" NSPREFIX_SBOL ":" NODENAME_DNASEQUENCE;
    if (ref_uri = getURIOfNodeMatchingXPath(node, path)) {
        setDNAComponentSequence(com, getDNASequence(DESTINATION, (char *)ref_uri));
        xmlFree(ref_uri);
    }
    
    // add annotations
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_ANNOTATION
					 "/" NSPREFIX_SBOL ":" NODENAME_SEQUENCEANNOTATION;
    if (ref_nodes = getNodesMatchingXPath(node, path)) {
        for (n=0; n<getNumPointersInArray(ref_nodes); n++) {
            ref_node = (xmlNode *) getNthPointerInArray(ref_nodes, n);
            ref_uri = getNodeURI(ref_node);
            addSequenceAnnotation(com, getSequenceAnnotation(DESTINATION, (char *)ref_uri));
            xmlFree(ref_uri);
        }
        deletePointerArray(ref_nodes);
    }
}

static void readCollectionContent(xmlNode *node) {
    Collection *col;
    xmlChar *col_uri;

    // create Collection
    col_uri = getNodeURI(node);
    col = createCollection(DESTINATION, (char *)col_uri);
    xmlFree(col_uri);

    // add displayID, name, description
    readSBOLCompoundObject(col->base, node);
}

static void readCollectionReferences(xmlNode *node) {
    Collection *col;
	xmlChar *path;
    xmlChar *col_uri;
    xmlChar *ref_uri;
    PointerArray *ref_nodes;
    xmlNode *ref_node;
    int n;

    // get Collection
    col_uri = getNodeURI(node);
    col = getCollection(DESTINATION, (char *)col_uri);
    xmlFree(col_uri);

    // add components
    path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_COMPONENT
    				 "/" NSPREFIX_SBOL ":" NODENAME_DNACOMPONENT;
    if (ref_nodes = getNodesMatchingXPath(node, path)) {
        for (n=0; n<getNumPointersInArray(ref_nodes); n++) {
            ref_node = (xmlNode *) getNthPointerInArray(ref_nodes, n);
            ref_uri = getNodeURI(ref_node);
            addDNAComponentToCollection(col, getDNAComponent(DESTINATION, (char *)ref_uri));
            xmlFree(ref_uri);
        }
        deletePointerArray(ref_nodes);
    }
}

/*************************
 * main parsing function
 *************************/

void readDocument(Document* destination, char* filename) {
	DESTINATION = destination;

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
	xmlXPathRegisterNs(CONTEXT, NSPREFIX_SBOL, NSURL_SBOL);
	xmlXPathRegisterNs(CONTEXT, NSPREFIX_RDF, NSURL_RDF);

	#define GLOBAL_XPATH BAD_CAST "//" NSPREFIX_SBOL ":"

	//xmlNode *result;
	//xmlAttr *attr;
	//xmlNs *ns;
	//namespaces = getContentsOfNodeMatchingXPath(NULL, BAD_CAST "//" NSPREFIX_RDF ":" NODENAME_RDF);
	//result = getSingleNodeMatchingXPath(NULL, BAD_CAST "//" NSPREFIX_RDF ":" NODENAME_RDF);
	//ns = result->nsDef;
	//while (ns)
	//{
	//	printf("%s:\t%s\n", ns->prefix, ns->href);
	//	ns = ns->next;
	//}

	//result = getSingleNodeMatchingXPath(NULL, GLOBAL_XPATH NODENAME_DNACOMPONENT);
	//printf("%s\n", (char *)result->name);
	//result = result->children;
	//while (result){
		//printf("%s\n", (char *)result->name);
		//if ((char *)result->name == "text") {
		//	printf("Node content:%s\n", (char *)xmlNodeGetContent(result));
		//if (result->type == XML_TEXT_NODE) {
			//printf("Node content:%s\n", (char *)xmlNodeGetContent(result));
			//printf("Node content:%s\n", (char *)result->content);
		//}
		//printf("Node content:%s\n", (char *)xmlNodeGetContent(result));
		//if (result->ns) {
			//printf("%s:\t%s\n", result->ns->prefix, result->ns->href);
		//}
		//result = result->next;
	//}

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
	DESTINATION = NULL;
	xmlCleanupParser();
}
