///////////////////////////////////////////////////////////
/// @file
/// Defines the DNASequence struct, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_DNASEQUENCE_HEADER
#define SBOL_DNASEQUENCE_HEADER

#include "constants.h"
#include "prototypes.h"

#define NUCLEOTIDES_TO_PRINT "50" ///< Cutoff for how much of a long sequence to print.

/// Implements the SBOL Core DNASequence object.
struct _DNASequence {
	SBOLObject* base;                 ///< uri
	NucleotidesProperty* nucleotides; ///< sequence
};

/// Create an empty DNASequence.
SBOLAPIEXPORTS DNASequence* createDNASequence(Document* doc, char* uri);

/// Delete a DNASequence.
/// Since DNASequences are self-contained,
/// no other freeing should be needed
SBOLAPIEXPORTS void deleteDNASequence(DNASequence* seq);

/// Get the total number of DNASequences in emory.
/// @todo rename to reflect doc
SBOLAPIEXPORTS int getNumDNASequences(const Document* doc);

/// Get the Nth DNASequnce in memory.
/// @todo rename to reflect doc
SBOLAPIEXPORTS DNASequence* getNthDNASequence(const Document* doc, int n);

/// Get the DNASequence associated with this URI.
/// Returns NULL on failure.
/// @todo rename to reflect doc
SBOLAPIEXPORTS DNASequence* getDNASequence(const Document* doc, const char* uri);

/// Get a copy of the nucleotides contained in this DNASequence.
/// @return A string that needs to be freed.
/// @todo rename to getDNASequenceNucleotides?
SBOLAPIEXPORTS char* getDNASequenceNucleotides(const DNASequence* seq);

/// Copy a string of nucleotides into this DNASequence.
/// So far, no validation is done to ensure that these are valid nucleotides.
/// @todo rename to setDNASequenceNucleotides?
SBOLAPIEXPORTS void setDNASequenceNucleotides(DNASequence* seq, const char* nucleotides);

/// Find out whether there's a DNASequence with this URI.
/// @todo rename to reflect doc
SBOLAPIEXPORTS int isDNASequenceURI(Document* doc, const char* uri);

/// Get the URI of a DNASequence.
/// Returns NULL on failure.
SBOLAPIEXPORTS char* getDNASequenceURI(const DNASequence* seq);

/// Print a DNASequence to stdout.
/// Mainly for debugging.
SBOLAPIEXPORTS void printDNASequence(const DNASequence* seq, int tabs);

/// Print all DNASequences to stdout.
/// Mainly for debugging.
/// @todo rename to reflect doc
SBOLAPIEXPORTS void printAllDNASequences(const Document* doc);

/// Delete all DNASequences from memory.
/// There shouldn't be anything left to free
/// because DNASequences are self-contained.
/// @todo rename to reflect doc
SBOLAPIEXPORTS void cleanupDNASequences(Document* doc);

#endif
