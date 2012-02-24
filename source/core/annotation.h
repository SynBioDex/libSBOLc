#ifndef SBOL_CORE_SEQUENCEANNOTATION
#define SBOL_CORE_SEQUENCEANNOTATION

struct _DNAComponent;

typedef struct _SequenceAnnotation
{
	char* id;
	struct DNAComponent* annotates;
	struct DNAComponent* subComponent;
	int genbankStart;
	int end;
	struct _SequenceAnnotation** precedes; //null terminated array
    int numPrecedes;
} SequenceAnnotation;

// create/destroy
void createSequenceAnnotation(const char* id);
void deleteSequenceAnnotation(SequenceAnnotation* ann);

// constrain order
void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
int getNumPrecedes(SequenceAnnotation ann);
SequenceAnnotation getNthPrecedes(SequenceAnnotation ann, int n);

// TODO is this one needed?
void setSequenceAnnotationID(SequenceAnnotation* ann, const char* id);

// TODO where should this go?
// attach to parent component
void setSubComponent(SequenceAnnotation* ann, struct _DNAComponent* com);

#endif
