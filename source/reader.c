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
	for (n=0; n < results_set->nodesetval->nodeNr; n++) {
		result_node = results_set->nodesetval->nodeTab[n];
		insertPointerIntoArray(results_array, result_node);
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

// just for trying out function passing
void printNodeName(xmlNode *node) {
	if (node)
		printf("%s\n", node->name);
}

/***********************************
 * XPath-based functions for
 * reading individual SBOL objects
 ***********************************/

void readDNAComponent_XPath(xmlNode *node) {
	if (!node)
		return;
	xmlChar *path = BAD_CAST "./s:annotation/s:SequenceAnnotation";
	applyFunctionToNodesMatchingXPath(printNodeName, node, path);
}

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

/// @todo either rename or make it so you don't pass the object?
SBOLCompoundObject *readSBOLCompoundObject(SBOLCompoundObject *obj, xmlNode *node) {
	xmlNode *result;
	char *content;

	// displayID
	if (result = getSingleNodeMatchingXPath(node, BAD_CAST "./s:displayId")) {
		content = xmlNodeGetContent(result);
		setSBOLCompoundObjectDisplayID(obj, (char *)content);
		xmlFree(content);
	}

	// name
	if (result = getSingleNodeMatchingXPath(node, BAD_CAST "./s:name")) {
		content = xmlNodeGetContent(result);
		setSBOLCompoundObjectName(obj, (char *)content);
		xmlFree(content);
	}

	// description
	if (result = getSingleNodeMatchingXPath(node, BAD_CAST "./s:description")) {
		content = xmlNodeGetContent(result);
		setSBOLCompoundObjectDescription(obj, (char *)content);
		xmlFree(content);
	}

	return obj;
}

DNASequence *readDNASequence(xmlNode *node, int pass) {
	// check that this uri is OK
	/// @todo remove this
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
	xmlNode *nt_node = getSingleNodeMatchingXPath(node, BAD_CAST "./s:nucleotides");
	if (nt_node) {
		xmlChar *nucleotides = xmlNodeGetContent(nt_node);
		setNucleotides(seq, (char *)nucleotides);
		xmlFree(nucleotides);
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
	//readDNAComponent_XPath(node);

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
