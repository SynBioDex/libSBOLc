#ifndef SBOL_CORE_DNASEQUENCE
#define SBOL_CORE_DNASEQUENCE

struct _URIProperty;
struct _TextProperty;

typedef struct _DNASequence {
	struct _URIProperty* uri;
	struct _TextProperty* nucleotides;
	int processed;
} DNASequence;

DNASequence* createDNASequence(char* nucleotides); // TODO id instead
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
