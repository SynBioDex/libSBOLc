#ifndef SBOL_CORE_SEQUENCEANNOTATION
#define SBOL_CORE_SEQUENCEANNOTATION

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

// constrain order
void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
int getNumPrecedes(SequenceAnnotation* ann);
SequenceAnnotation* getNthPrecedes(SequenceAnnotation* ann, int n);
// TODO removePrecedesRelationship?

#endif
