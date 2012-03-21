#ifndef SBOL_CORE_DNACOMPONENT
#define SBOL_CORE_DNACOMPONENT
#include "api.h"

struct _PointerArray;
struct _SBOLCompoundObject;
struct _DNASequence;
struct _SequenceAnnotation;
struct _Collection;

typedef struct _DNAComponent {
	struct _SBOLCompoundObject* base;
	struct _DNASequence* dnaSequence;
	struct _PointerArray* annotations;
	struct _PointerArray* collections;
	int processed;
} DNAComponent;

// create/destroy
SBOLAPIEXPORTS DNAComponent* createDNAComponent(const char* uri);
SBOLAPIEXPORTS void deleteDNAComponent(DNAComponent* com);

// work with storage
int isDNAComponentPtr(const void* pointer); // TODO rename and export
SBOLAPIEXPORTS int isDNAComponentID(const char* uri);
SBOLAPIEXPORTS int getNumDNAComponents();
SBOLAPIEXPORTS DNAComponent* getNthDNAComponent(int n);

// tools for iteration
SBOLAPIEXPORTS DNAComponent* getDNAComponent(const char* uri);
SBOLAPIEXPORTS int getNumCollectionsFor(const DNAComponent* com);
SBOLAPIEXPORTS int getNumSequenceAnnotationsIn(const DNAComponent* com);
SBOLAPIEXPORTS struct _Collection* getNthCollectionFor(const DNAComponent* com, int n);
SBOLAPIEXPORTS struct _SequenceAnnotation* getNthSequenceAnnotationIn(const DNAComponent* com, int n);

// get properties
SBOLAPIEXPORTS char* getDNAComponentURI(const DNAComponent* com);
SBOLAPIEXPORTS char* getDNAComponentDisplayID(const DNAComponent* com);
SBOLAPIEXPORTS char* getDNAComponentName(const DNAComponent* com);
SBOLAPIEXPORTS char* getDNAComponentDescription(const DNAComponent* com);
SBOLAPIEXPORTS struct _DNASequence* getDNAComponentSequence(DNAComponent* com);

// set properties
SBOLAPIEXPORTS void setDNAComponentURI(DNAComponent* com, const char* uri);
SBOLAPIEXPORTS void setDNAComponentDisplayID(DNAComponent* com, const char* id);
SBOLAPIEXPORTS void setDNAComponentName(DNAComponent* com, const char* name);
SBOLAPIEXPORTS void setDNAComponentDescription(DNAComponent* com, const char* desc);
SBOLAPIEXPORTS void setDNAComponentSequence(DNAComponent* com, struct _DNASequence* seq);

// TODO where should this go?
// work with annotations
SBOLAPIEXPORTS void addSequenceAnnotation(DNAComponent* com, struct _SequenceAnnotation* ann);
SBOLAPIEXPORTS void setSubComponent(struct _SequenceAnnotation* ann, DNAComponent* com);

void printDNAComponent(const DNAComponent* com, int tabs);
void printAllDNAComponents();
void cleanupDNAComponents();

#endif
