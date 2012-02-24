#ifndef SBOL_CORE_SEQUENCEANNOTATION
#define SBOL_CORE_SEQUENCEANNOTATION
#include "core_common.h"

struct _SequenceAnnotation;
typedef struct _SequenceAnnotation
{
	char* id;
	struct _DNAComponent * annotates;
	struct _DNAComponent * subComponent;
	int genbankStart;
	int end;
	struct _SequenceAnnotation ** precedes; //null terminated array

    int numPrecedes;
} SequenceAnnotation;

SBOLAPIEXPORTS void createSequenceAnnotation(const char* id);
SBOLAPIEXPORTS void deleteSequenceAnnotation(SequenceAnnotation* ann);

SBOLAPIEXPORTS void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
SBOLAPIEXPORTS int getNumPrecedes(SequenceAnnotation ann);
SBOLAPIEXPORTS SequenceAnnotation getNthPrecedes(SequenceAnnotation ann, int n);

SBOLAPIEXPORTS void setSequenceAnnotationID(SequenceAnnotation* ann, const char * id);
SBOLAPIEXPORTS void setSequenceAnnotationID(SequenceAnnotation* ann, const char* id);

SBOLAPIEXPORTS void setSubComponent(SequenceAnnotation* ann, DNAComponent* com);

#endif
