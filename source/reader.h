///////////////////////////////////////////////////////////
/// @file reader.h
/// This file contains functions for importing SBOL objects
/// from an XML file. Only the readSBOLCore function is
/// meant to be exported; everything else supports it.
///////////////////////////////////////////////////////////

#ifndef SBOL_READER_HEADER
#define SBOL_READER_HEADER

struct _PointerArray;
struct _SBOLCompoundObject;

// utility functions for working with xmlNodes
static xmlChar *getNodeURI(xmlNode *node);
struct _PointerArray *getNodesMatchingXPath(xmlNode *node, xmlChar *path);
static xmlNode *getSingleNodeMatchingXPath(xmlNode *node, xmlChar *path);
static xmlChar *getContentsOfNodeMatchingXPath(xmlNode *node, xmlChar *path);
static xmlChar *getURIOfNodeMatchingXPath(xmlNode *node, xmlChar *path);
static void applyFunctionToNodesMatchingXPath(void (*fn)(xmlNode *), xmlNode *node, xmlChar *path);
static void processNodes(void (*fn)(xmlNode *), xmlChar *path);

/// @todo void readNamespaces(xmlNode *node)?

// functions for reading individual SBOLObjects from xmlNodes
static void *readSBOLCompoundObject(struct _SBOLCompoundObject *obj, xmlNode *node);

static void readDNASequenceContent(xmlNode *node);
static void readSequenceAnnotationContent(xmlNode *node);
static void readSequenceAnnotationReferences(xmlNode *node);
static void readDNAComponentContent(xmlNode *node);
static void readDNAComponentReferences(xmlNode *node);
static void readCollectionContent(xmlNode *node);
static void readCollectionReferences(xmlNode *node);

/// Parse an SBOL document from disk and create
/// matching structs in memory. Also validates
/// before parsing. Prints a message to stdout
/// if the document is invalid.
/// @todo Return an error code on invalid documents
void readSBOLCore(char* filename);

#endif
