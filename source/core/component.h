#ifndef SBOL_CORE_COMPONENT
#define SBOL_CORE_COMPONENT

struct _DNASequence;
struct _SequenceAnnotation;
struct _Collection;

typedef struct _DNAComponent {
	char* id;
	char* name;
	char* description;
	int numAnnotations;
	int numCollections;
	struct _DNASequence* dnaSequence;
	struct _SequenceAnnotation** annotations; //null terminated array
	struct _Collection** collections; //null terminated array
} DNAComponent;

// create/destroy
DNAComponent* createComponent(const char* id);
void deleteComponent(DNAComponent* com);

// tools for iteration
int getNumCollectionsFor(const DNAComponent* com);
int getNumSequenceAnnotationsIn(const DNAComponent* com);
// TODO return pointers?
struct _Collection* getNthCollectionFor(const DNAComponent* com, int n);
struct _SequenceAnnotation* getNthSequenceAnnotationIn(const DNAComponent* com, int n);

// get properties
char* getComponentID(const DNAComponent* com);
char* getComponentName(const DNAComponent* com);
char* getComponentDescription(const DNAComponent* com);

// set properties
void setComponentID(DNAComponent* com, const char* id);
void setComponentName(DNAComponent* com, const char* name);
void setComponentDescription(DNAComponent* com, const char* desc);

// TODO where should this go?
// work with annotations
void addSequenceAnnotation(DNAComponent* com, struct _SequenceAnnotation* ann);
void setSubComponent(struct _SequenceAnnotation* ann, DNAComponent* com);

#endif
