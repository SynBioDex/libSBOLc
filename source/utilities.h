///////////////////////////////////////////////////////////
/// @file utilities.h
/// This file defines SBOL utility functions that don't
/// really fit in anywhere else. Nothing in here should
/// need to be exported.
///////////////////////////////////////////////////////////

#ifndef SBOL_UTILITIES_HEADER
#define SBOL_UTILITIES_HEADER

#include "constants.h"
#include "prototypes.h"

#define BUFFER_CHARS 100

void indent(int tabs);

char *intToStr(int input);
int   strToInt(const char *input);

/// @todo move to polarityproperty, writer, or types?
int strToPolarity(const char *input);
char polarityToChar(int polarity);

void safeXmlInitParser();

#endif
