#ifndef SBOL_CORE_DNACOMPONENT
#define SBOL_CORE_DNACOMPONENT
#include "object.h"

struct _SBOLCompoundObject;
struct _PointerArray;
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
DNAComponent* createDNAComponent(const char* uri);
void deleteDNAComponent(DNAComponent* com);

// work with storage
int isDNAComponentPtr(const void* pointer);
int isDNAComponentID(const char* uri);
int getNumDNAComponents();
DNAComponent* getNthDNAComponent(int n);

// tools for iteration
DNAComponent* getDNAComponent(const char* uri);
int getNumCollectionsFor(const DNAComponent* com);
int getNumSequenceAnnotationsIn(const DNAComponent* com);
struct _Collection* getNthCollectionFor(const DNAComponent* com, int n);
struct _SequenceAnnotation* getNthSequenceAnnotationIn(const DNAComponent* com, int n);

// get properties
char* getDNAComponentURI(const DNAComponent* com);
char* getDNAComponentDisplayID(const DNAComponent* com);
char* getDNAComponentName(const DNAComponent* com);
char* getDNAComponentDescription(const DNAComponent* com);
struct _DNASequence* getDNAComponentSequence(DNAComponent* com);

// set properties
void setDNAComponentURI(DNAComponent* com, const char* uri);
void setDNAComponentDisplayID(DNAComponent* com, const char* id);
void setDNAComponentName(DNAComponent* com, const char* name);
void setDNAComponentDescription(DNAComponent* com, const char* desc);
void setDNAComponentSequence(DNAComponent* com, struct _DNASequence* seq);

// TODO where should this go?
// work with annotations
void addSequenceAnnotation(DNAComponent* com, struct _SequenceAnnotation* ann);
void setSubComponent(struct _SequenceAnnotation* ann, DNAComponent* com);

void printDNAComponent(const DNAComponent* com, int tabs);
void printAllDNAComponents();
void cleanupDNAComponents();

#endif
