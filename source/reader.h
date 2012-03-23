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
DNASequence        *readDNASequence(xmlNode *node);
SequenceAnnotation *readSequenceAnnotation(xmlNode *node);
DNAComponent       *readDNAComponent(xmlNode *node);
Collection         *readCollection(xmlNode *node);
void readReference(xmlNode *node);

// TODO make static
void readSBOLStructs(xmlNode *root);
void readSBOLPointers(xmlNode *root);

// TODO rename
SBOLAPIEXPORTS void readSBOLCore_xml(char* filename);

#endif
