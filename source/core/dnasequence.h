#ifndef SBOL_CORE_DNASEQUENCE
#define SBOL_CORE_DNASEQUENCE

struct _Property;

typedef struct _DNASequence {
	struct _Property* uri;
	struct _Property* nucleotides;
} DNASequence;

DNASequence* createDNASequence(char* nucleotides); // TODO id?
void deleteDNASequence(DNASequence* seq);

int getNumDNASequences();
DNASequence* getNthDNASequence(int n);
DNASequence* getDNASequence(const char* uri);
char* getNucleotides(const DNASequence* seq);
void setDNASequenceURI(DNASequence* seq, const char* uri);
void setNucleotides(DNASequence* seq, const char* nucleotides);
int isDNASequenceURI(const char* uri);
char* getDNASequenceURI(const DNASequence* seq);

void printDNASequence(const DNASequence* seq, int tabs);
void printAllDNASequences();

void cleanupDNASequences();

#endif
