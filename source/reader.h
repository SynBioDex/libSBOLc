///////////////////////////////////////////////////////////
/// @file reader.h
/// This file contains functions for importing SBOL objects
/// from an XML file. Only the readSBOLCore function is
/// meant to be exported; everything else supports it.
///////////////////////////////////////////////////////////

#ifndef SBOL_READER_HEADER
#define SBOL_READER_HEADER
#include "api.h"

// forward declarations
struct _SBOLCompoundObject;
struct _SequenceAnnotation;
struct _DNASequence;
struct _Collection;

// utility functions for working with xmlNodes
static xmlChar *getNodeURI(xmlNode *node);
static xmlChar *getNodeNS(xmlNode *node);
static int nodeNameEquals(xmlNode *node, char *name);

/// @todo void readNamespaces(xmlNode *node)?

// functions for reading individual SBOLObjects from xmlNodes
static struct _SBOLCompoundObject *readSBOLCompoundObject(struct _SBOLCompoundObject *obj, xmlNode *node);
static struct _DNASequence        *readDNASequence(xmlNode *node, int pass);
static struct _SequenceAnnotation *readSequenceAnnotation(xmlNode *node, int pass);
static struct _DNAComponent       *readDNAComponent(xmlNode *node, int pass);
static struct _Collection         *readCollection(xmlNode *node, int pass);

/// Parse an SBOL document from disk and create
/// matching structs in memory. Also validates
/// before parsing. Prints a message to stdout
/// if the document is invalid.
/// @todo Return an error code on invalid documents
SBOLAPIEXPORTS void readSBOLCore(char* filename);

#endif
