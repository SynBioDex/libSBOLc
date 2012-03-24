#ifndef SBOL_READER_HEADER
#define SBOL_READER_HEADER
#include "api.h"

// forward declarations
struct _SBOLCompoundObject;
struct _SequenceAnnotation;
struct _DNASequence;
struct _Collection;

static xmlChar *getNodeURI(xmlNode *node);
static xmlChar *getNodeNS(xmlNode *node);
static int nodeNameEquals(xmlNode *node, char *name);

//void readNamespaces(xmlNode *node); // TODO needed?
static struct _SBOLCompoundObject *readSBOLCompoundObject(struct _SBOLCompoundObject *obj, xmlNode *node);
static struct _DNASequence        *readDNASequence(xmlNode *node, int pass);
static struct _SequenceAnnotation *readSequenceAnnotation(xmlNode *node, int pass);
static struct _DNAComponent       *readDNAComponent(xmlNode *node, int pass);
static struct _Collection         *readCollection(xmlNode *node, int pass);

SBOLAPIEXPORTS void readSBOLCore(char* filename);

#endif
