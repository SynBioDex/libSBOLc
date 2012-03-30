///////////////////////////////////////////////////////////
/// @file sbol.h
/// This file gathers together all the SBOL functions so
/// they can be easily #included. Although the SBOL core
/// is separated into files for easier maintenance,
/// those files are fairly interdependent, so it's
/// probably best to #include them as a group from here.
///////////////////////////////////////////////////////////

#ifndef SBOL_HEADER
#define SBOL_HEADER

#include "constants.h"
#include "prototypes.h"

/// @todo document that you need to free strings gotten from sbol
/// @todo make a lot of the functions static to simplify things

// from other files
/// @todo remove?
#include "utilities.h"
#include "property.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"
#include "validator.h"
#include "reader.h"
#include "writer.h"

// from core.c
void printSBOLCore();
void cleanupSBOLCore();

#endif
