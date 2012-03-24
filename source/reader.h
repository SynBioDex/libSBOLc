#ifndef SBOL_READER_HEADER
#define SBOL_READER_HEADER
#include "api.h"
#include "object.h"

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

SBOLAPIEXPORTS void readSBOLCore(char* filename);

#endif
