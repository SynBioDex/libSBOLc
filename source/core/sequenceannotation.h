#ifndef SBOL_CORE_SEQUENCEANNOTATION
#define SBOL_CORE_SEQUENCEANNOTATION

struct _DNAComponent;
struct _GenericArray;
struct _Property;

typedef struct _SequenceAnnotation {
	struct _Property* id;
	int genbankStart;
	int genbankEnd;
   	struct _DNAComponent* annotates;
	struct _DNAComponent* subComponent;
	struct _GenericArray* precedes;
} SequenceAnnotation;

// create/destroy
SequenceAnnotation* createSequenceAnnotation(const char* id);
char* getSequenceAnnotationID(const SequenceAnnotation* ann);
void setSequenceAnnotationID(SequenceAnnotation* ann, const char* id);
void deleteSequenceAnnotation(SequenceAnnotation* ann);

SequenceAnnotation* getSequenceAnnotation(const char* id);

// work with global arrays
int isSequenceAnnotationPtr(const void* pointer);
int isSequenceAnnotationID(const char* id);
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
