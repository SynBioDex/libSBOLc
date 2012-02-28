#ifndef SBOL_CORE_ANNOTATION
#define SBOL_CORE_ANNOTATION

struct _DNAComponent;

typedef struct _SequenceAnnotation {
	char* id;
	int genbankStart;
	int genbankEnd;
	int numPrecedes;
   	struct _DNAComponent* annotates;
	struct _DNAComponent* subComponent;
	struct _SequenceAnnotation** precedes;
} SequenceAnnotation;

// create/destroy
SequenceAnnotation* createSequenceAnnotation(const char* id);
void setSequenceAnnotationID(SequenceAnnotation* ann, const char* id);
void deleteSequenceAnnotation(SequenceAnnotation* ann);

// work with global arrays
void registerSequenceAnnotation(struct _SequenceAnnotation* ann);
void removeAnnotation(struct _SequenceAnnotation* ann);
int isAnnotationPtr(const void* pointer);
int isAnnotationID(const char* id);
int getNumSequenceAnnotations();
struct _SequenceAnnotation* getNthSequenceAnnotation(int n);

// constrain order
void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
int getNumPrecedes(SequenceAnnotation* ann);
SequenceAnnotation* getNthPrecedes(SequenceAnnotation* ann, int n);
// TODO removePrecedesRelationship?

void cleanupAnnotations();

#endif
