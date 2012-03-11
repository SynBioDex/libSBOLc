#ifndef SBOL_CORE_SEQUENCEANNOTATION
#define SBOL_CORE_SEQUENCEANNOTATION

struct _DNAComponent;
struct _GenericArray;
struct _Property;

typedef struct _SequenceAnnotation {
	struct _Property* uri;
	int genbankStart;
	int genbankEnd;
   	struct _DNAComponent* annotates;
	struct _DNAComponent* subComponent;
	struct _GenericArray* precedes;
} SequenceAnnotation;

// create/destroy
SequenceAnnotation* createSequenceAnnotation(const char* uri);
char* getSequenceAnnotationURI(const SequenceAnnotation* ann);
void setSequenceAnnotationURI(SequenceAnnotation* ann, const char* uri);
void deleteSequenceAnnotation(SequenceAnnotation* ann);

SequenceAnnotation* getSequenceAnnotation(const char* uri);

// work with global arrays
int isSequenceAnnotationPtr(const void* pointer);
int isSequenceAnnotationURI(const char* uri);
int getNumSequenceAnnotations();
SequenceAnnotation* getNthSequenceAnnotation(int n);

int getBioStart(const SequenceAnnotation* ann);
int getBioEnd(const SequenceAnnotation* ann);
void setBioStart(SequenceAnnotation* ann, int start);
void setBioEnd(SequenceAnnotation* ann, int end);

// constrain order
void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
int getNumPrecedes(const SequenceAnnotation* ann);
SequenceAnnotation* getNthPrecedes(const SequenceAnnotation* ann, int n);
// TODO removePrecedesRelationship?

void printSequenceAnnotation(const SequenceAnnotation* seq, int tabs);
void printAllSequenceAnnotations();
void cleanupSequenceAnnotations();

#endif
