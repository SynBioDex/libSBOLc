#ifndef SBOL_CORE_SEQUENCE
#define SBOL_CORE_SEQUENCE

typedef struct _DNASequence {
	char* nucleotides;
} DNASequence;

DNASequence* createDNASequence(char* nucleotides); // TODO id?
void deleteDNASequence(DNASequence* seq);
void cleanupSequences();

#endif
