#ifndef SBOL_CORE_DEBUG
#define SBOL_CORE_DEBUG

#define TRUNCATE_LENGTH 30

struct _DNASequence;
struct _SequenceAnnotation;
struct _DNAComponent;
struct _Collection;

void printDNASequence(const struct _DNASequence* seq, int tabs);
void printSequenceAnnotation(const struct _SequenceAnnotation* ann, int tabs);
void printDNAComponent(const struct _DNAComponent* com, int tabs);
void printCollection(const struct _Collection* col, int tabs);

#endif
