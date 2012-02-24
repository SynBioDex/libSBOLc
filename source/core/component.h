#ifndef SBOL_CORE_DNACOMPONENT
#define SBOL_CORE_DNACOMPONENT
#include "sequence.h"
#include "annotation.h"
#include "collection.h"

// TODO move includes to implementation?

struct _DNASequence;
struct _SequenceAnnotation;
struct _Collection;

typedef struct _DNAComponent
{
	char* id;
	char* name;
	char* description;
	struct _DNASequence* dnaSequence;  //pointer to a single DNASequence
	struct _SequenceAnnotation** annotations; //null terminated array
	struct _Collection** collections; //null terminated array
    int numAnnotations;
    int numCollections;
} DNAComponent;

// create/destroy
void createComponent(const char* id);
void deleteComponent(DNAComponent* com);

// tools for iteration
int getNumCollectionsFor(DNAComponent* com);
int getNumSequenceAnnotationsIn(DNAComponent* com);
struct _Collection         getNthCollectionFor(DNAComponent* com, int n);
struct _SequenceAnnotation getNthSequenceAnnotationIn(DNAComponent* com, int n);

// set properties
void setComponentID(DNAComponent* com, const char* id);
void setComponentName(DNAComponent* com, const char* name);
void setComponentDescription(DNAComponent* com, const char* desc);

// TODO where should this go?
// work with annotations
void addSequenceAnnotation(DNAComponent* com, struct _SequenceAnnotation* ann);
void setSubComponent(struct _SequenceAnnotation* ann, DNAComponent* com);

#endif
