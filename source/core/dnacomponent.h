#ifndef SBOL_CORE_DNACOMPONENT
#define SBOL_CORE_DNACOMPONENT

struct _GenericArray;
struct _DNASequence;
struct _SequenceAnnotation;
struct _Collection;
struct _Property;

typedef struct _DNAComponent {
	struct _Property* uri;
	struct _Property* name;
	struct _Property* description;
	struct _DNASequence* dnaSequence;
	struct _GenericArray* annotations;
	struct _GenericArray* collections;
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
char* getDNAComponentID(const DNAComponent* com);
char* getDNAComponentName(const DNAComponent* com);
char* getDNAComponentDescription(const DNAComponent* com);
struct _DNASequence* getDNAComponentSequence(DNAComponent* com);

// set properties
void setDNAComponentID(DNAComponent* com, const char* uri);
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
