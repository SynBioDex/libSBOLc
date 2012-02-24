#ifndef SBOL_CORE_SEQUENCEANNOTATION
#define SBOL_CORE_SEQUENCEANNOTATION
#include "common.h"

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

// create/destroy
SBOLAPIEXPORTS void createSequenceAnnotation(const char* id);
SBOLAPIEXPORTS void deleteSequenceAnnotation(SequenceAnnotation* ann);

// constrain order
SBOLAPIEXPORTS void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
SBOLAPIEXPORTS int getNumPrecedes(SequenceAnnotation ann);
SBOLAPIEXPORTS SequenceAnnotation getNthPrecedes(SequenceAnnotation ann, int n);

// TODO is this one needed?
SBOLAPIEXPORTS void setSequenceAnnotationID(SequenceAnnotation* ann, const char* id);

// TODO where should this go?
// attach to parent component
SBOLAPIEXPORTS void setSubComponent(SequenceAnnotation* ann, DNAComponent* com);

#endif
