#ifndef SBOL_CORE_DNASEQUENCE
#define SBOL_CORE_DNASEQUENCE

struct _Property;

typedef struct _DNASequence {
	struct _Property* id;
	struct _Property* nucleotides;
} DNASequence;

DNASequence* createDNASequence(char* nucleotides); // TODO id?
void deleteDNASequence(DNASequence* seq);

int getNumDNASequences();
DNASequence* getNthDNASequence(int n);
DNASequence* getDNASequence(const char* id);
char* getNucleotides(const DNASequence* seq);
void setDNASequenceID(DNASequence* seq, const char* id);
void setNucleotides(DNASequence* seq, const char* nucleotides);
int isDNASequenceID(const char* id);
char* getDNASequenceID(DNASequence* seq);

void printDNASequence(const DNASequence* seq, int tabs);
void printAllDNASequences();

void cleanupDNASequences();

#endif
