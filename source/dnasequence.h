///////////////////////////////////////////////////////////
/// @file dnasequence.h
/// This file defines the DNASequence struct, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_DNASEQUENCE_HEADER
#define SBOL_DNASEQUENCE_HEADER

#include "constants.h"
#include "prototypes.h"

/// Implements the SBOL Core DNASequence object.
typedef struct DNASequence {
	struct SBOLObject* base;
	struct NucleotidesProperty *nucleotides;
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
