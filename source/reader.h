#ifndef SBOL_READER_HEADER
#define SBOL_READER_HEADER
#include "api.h"
#include "object.h"

// TODO remove
SBOLAPIEXPORTS void readSBOLCore(char* filename);

// TODO make static
xmlChar *getNodeURI(xmlNode *node);
xmlChar *getNodeNS(xmlNode *node);
int nodeNameEquals(xmlNode *node, char *name);

// TODO make static
void readNamespaces(xmlNode *node); // TODO needed?
SBOLCompoundObject *readSBOLCompoundObject(SBOLCompoundObject *obj, xmlNode *node);
DNASequence        *readDNASequence(xmlNode *node, int pass);
SequenceAnnotation *readSequenceAnnotation(xmlNode *node, int pass);
DNAComponent       *readDNAComponent(xmlNode *node, int pass);
Collection         *readCollection(xmlNode *node, int pass);

// TODO make static
void readSBOLObjects(xmlNode *root, int pass);

// TODO rename
SBOLAPIEXPORTS void readSBOLCore_xml(char* filename);

#endif
