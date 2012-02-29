#ifndef SBOL_CORE_DNASEQUENCE
#define SBOL_CORE_DNASEQUENCE

typedef struct _DNASequence {
	char* nucleotides;
} DNASequence;

DNASequence* createDNASequence(char* nucleotides); // TODO id?
void deleteDNASequence(DNASequence* seq);

int getNumDNASequences();
DNASequence* getNthDNASequence(int n);

void cleanupDNASequences();

#endif
