///////////////////////////////////////////////////////////
/// @file utilities.h
/// This file defines SBOL utility functions that don't
/// really fit in anywhere else. Nothing in here should
/// need to be exported.
///////////////////////////////////////////////////////////

#ifndef SBOL_UTILITIES_HEADER
#define SBOL_UTILITIES_HEADER

#define BUFFER_CHARS 100

char* getExtension(char* filename);
int sameString(const char* string1, const char* string2);
char* intToStr(int input);
int sameContent(const char* filename1, const char* filename2);
void safeXmlInitParser();

#endif
