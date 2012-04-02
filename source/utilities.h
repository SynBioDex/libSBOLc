///////////////////////////////////////////////////////////
/// @file
/// This file defines SBOL utility functions that don't
/// really fit in anywhere else. Nothing in here should
/// need to be exported.
/// 
/// @todo Don't export this stuff with the library.
///////////////////////////////////////////////////////////

#ifndef SBOL_UTILITIES_HEADER
#define SBOL_UTILITIES_HEADER

#include "constants.h"
#include "prototypes.h"

#define BUFFER_CHARS 100

SBOLAPIIGNORES void indent(int tabs);

SBOLAPIIGNORES char *intToStr(int input);
SBOLAPIIGNORES int   strToInt(const char *input);

/// @todo move to polarityproperty, writer, or types?
SBOLAPIIGNORES int strToPolarity(const char *input);
SBOLAPIIGNORES char polarityToChar(int polarity);

/// @todo find a way not to export this?
SBOLAPIEXPORTS void safeXmlInitParser();

#endif
