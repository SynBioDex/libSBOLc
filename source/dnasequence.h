#ifndef SBOL_DNASEQUENCE_HEADER
#define SBOL_DNASEQUENCE_HEADER
#include "api.h"

struct _SBOLObject;
struct _TextProperty;

typedef struct _DNASequence {
	struct _SBOLObject* base;
	struct _TextProperty* nucleotides;
} DNASequence;

SBOLAPIEXPORTS DNASequence* createDNASequence(char* uri);
SBOLAPIEXPORTS void deleteDNASequence(DNASequence* seq);

SBOLAPIEXPORTS int getNumDNASequences();
SBOLAPIEXPORTS DNASequence* getNthDNASequence(int n);
SBOLAPIEXPORTS DNASequence* getDNASequence(const char* uri);
SBOLAPIEXPORTS char* getNucleotides(const DNASequence* seq);
SBOLAPIEXPORTS void setDNASequenceURI(DNASequence* seq, const char* uri); // TODO remove?
SBOLAPIEXPORTS void setNucleotides(DNASequence* seq, const char* nucleotides);
SBOLAPIEXPORTS int isDNASequenceURI(const char* uri);
SBOLAPIEXPORTS char* getDNASequenceURI(const DNASequence* seq);

void printDNASequence(const DNASequence* seq, int tabs);
void printAllDNASequences();

void cleanupDNASequences();

#endif
