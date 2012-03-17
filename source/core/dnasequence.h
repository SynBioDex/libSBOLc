#ifndef SBOL_CORE_DNASEQUENCE
#define SBOL_CORE_DNASEQUENCE
#include "object.h"

struct _SBOLObject;
struct _TextProperty;

typedef struct _DNASequence {
	struct _SBOLObject base;
	struct _TextProperty* nucleotides;
	int processed; // TODO remove
} DNASequence;

DNASequence* createDNASequence(char* uri);
void deleteDNASequence(DNASequence* seq);

int getNumDNASequences();
DNASequence* getNthDNASequence(int n);
DNASequence* getDNASequence(const char* uri);
char* getNucleotides(const DNASequence* seq);
void setDNASequenceURI(DNASequence* seq, const char* uri); // TODO remove?
void setNucleotides(DNASequence* seq, const char* nucleotides);
int isDNASequenceURI(const char* uri);
char* getDNASequenceURI(const DNASequence* seq);

void printDNASequence(const DNASequence* seq, int tabs);
void printAllDNASequences();

void cleanupDNASequences();

#endif
