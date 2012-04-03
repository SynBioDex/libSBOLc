///////////////////////////////////////////////////////////
/// @file
/// 
/// Gathers together all the SBOL functions so
/// they can be easily #included. Although the SBOL core
/// is separated into files for easier maintenance,
/// those files are interdependent, so it's probably
/// best to #include them as a group from here.
/// 
/// @todo make a lot of the functions static
///////////////////////////////////////////////////////////

#ifndef SBOL_HEADER
#define SBOL_HEADER

// from other files
#include "constants.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"
#include "validator.h"
#include "reader.h"
#include "writer.h"

// from core.c

/// Print an outline of all the DNASequences, SequenceAnnotations,
/// DNAComponents, and Collections to stdout.
/// Mainly for debugging.
SBOLAPIEXPORTS void printSBOLCore();

/// Delete all the DNASequences, SequenceAnnotations,
/// DNAComponents, and Collections. Strings returned by querying
/// them need to be freed separately.
SBOLAPIEXPORTS void cleanupSBOLCore();

#endif
