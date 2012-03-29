///////////////////////////////////////////////////////////
/// @file utilities.h
/// This file defines SBOL utility functions that don't
/// really fit in anywhere else. Nothing in here should
/// need to be exported.
///////////////////////////////////////////////////////////

#ifndef SBOL_UTILITIES_HEADER
#define SBOL_UTILITIES_HEADER

#define BUFFER_CHARS 100

char *intToStr(int input);
int   strToInt(const char *input);

/// @todo move to polarityproperty, writer, or types?
int strToPolarity(const char *input);
char polarityToChar(int polarity);

void safeXmlInitParser();

#endif
