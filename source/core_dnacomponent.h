#ifndef SBOL_CORE_DNACOMPONENT
#define SBOL_CORE_DNACOMPONENT
#include "core_common.h"

typedef struct _DNAComponent
{
	char* id;
	char* name;
	char* description;
	struct _DNASequence * dnaSequence;  //pointer to a single DNASequence
	struct _SequenceAnnotation ** annotations; //null terminated array
	struct _Collection ** collections; //null terminated array
    int numAnnotations;
    int numCollections;
} DNAComponent;

SBOLAPIEXPORTS void createComponent(const char* id);
//SBOLAPIEXPORTS void deleteComponent(DNAComponent* com);

SBOLAPIEXPORTS int getNumCollectionsFor(DNAComponent com);
SBOLAPIEXPORTS int getNumSequenceAnnotationsIn(DNAComponent com);

SBOLAPIEXPORTS Collection getNthCollectionFor(DNAComponent com, int n);
SBOLAPIEXPORTS SequenceAnnotation getNthSequenceAnnotationIn(DNAComponent com, int n);

SBOLAPIEXPORTS void setComponentID(DNAComponent * com, const char* id);
SBOLAPIEXPORTS void setComponentName(DNAComponent * com, const char* name);
SBOLAPIEXPORTS void setComponentDescription(DNAComponent * com, const char* desc);

SBOLAPIEXPORTS void addSequenceAnnotation(DNAComponent * com, _SequenceAnnotation * ann);
SBOLAPIEXPORTS void setSubComponent(SequenceAnnotation * ann, DNAComponent * com);

#endif
