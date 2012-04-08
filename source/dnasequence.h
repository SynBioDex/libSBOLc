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
	Document* doc;                    ///< parent Document
	SBOLObject* base;                 ///< uri
	NucleotidesProperty* nucleotides; ///< sequence
};

/// Create an empty DNASequence.
SBOLAPIEXPORTS DNASequence* createDNASequence(Document* doc, const char* uri);

/// Delete a DNASequence.
/// Since DNASequences are self-contained,
/// no other freeing should be needed
SBOLAPIEXPORTS void deleteDNASequence(DNASequence* seq);

/// Get a copy of the nucleotides contained in this DNASequence.
/// @return A string that needs to be freed.
/// @todo rename to getDNASequenceNucleotides?
SBOLAPIEXPORTS char* getDNASequenceNucleotides(const DNASequence* seq);

/// Copy a string of nucleotides into this DNASequence.
/// So far, no validation is done to ensure that these are valid nucleotides.
/// @todo rename to setDNASequenceNucleotides?
SBOLAPIEXPORTS void setDNASequenceNucleotides(DNASequence* seq, const char* nucleotides);

/// Get the URI of a DNASequence.
/// Returns NULL on failure.
SBOLAPIEXPORTS char* getDNASequenceURI(const DNASequence* seq);

/// Print a DNASequence to stdout.
/// Mainly for debugging.
SBOLAPIEXPORTS void printDNASequence(const DNASequence* seq, int tabs);

#endif
