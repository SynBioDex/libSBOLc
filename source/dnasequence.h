///////////////////////////////////////////////////////////
/// @file dnasequence.h
/// This file defines the DNASequence struct, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_DNASEQUENCE_HEADER
#define SBOL_DNASEQUENCE_HEADER

#include "constants.h"
#include "prototypes.h"

#define NUCLEOTIDES_TO_PRINT "50" ///< Cutoff for how much of a long sequence to print.

/// Implements the SBOL Core DNASequence object.
struct _DNASequence {
	SBOLObject* base;                 ///< uri, displayID, name, description
	NucleotidesProperty* nucleotides; ///< sequence
};

/// Create an empty DNASequence.
DNASequence* createDNASequence(char* uri);

/// Delete a DNASequence.
/// Since DNASequences are self-contained,
/// no other freeing should be needed
void deleteDNASequence(DNASequence* seq);

/// Get the total number of DNASequences in memory.
int getNumDNASequences();

/// Get the Nth DNASequnce in memory.
DNASequence* getNthDNASequence(int n);

/// Get the DNASequence associated with this URI.
/// Returns NULL on failure.
DNASequence* getDNASequence(const char* uri);

/// Get a copy of the nucleotides contained in this DNASequence.
/// @return A string that needs to be freed.
char* getNucleotides(const DNASequence* seq);

/// Copy a string of nucleotides into this DNASequence.
/// So far, no validation is done to ensure that these are valid nucleotides.
void setNucleotides(DNASequence* seq, const char* nucleotides);

/// Find out whether there's a DNASequence with this URI.
int isDNASequenceURI(const char* uri);

/// Get the URI of a DNASequence.
/// Returns NULL on failure.
char* getDNASequenceURI(const DNASequence* seq);

/// Print a DNASequence to stdout.
/// Mainly for debugging.
void printDNASequence(const DNASequence* seq, int tabs);

/// Print all DNASequences to stdout.
/// Mainly for debugging.
void printAllDNASequences();

/// Delete all DNASequences from memory.
/// There shouldn't be anything left to free
/// because DNASequences are self-contained.
void cleanupDNASequences();

#endif
