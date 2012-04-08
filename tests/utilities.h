#ifndef SBOL_TEST_UTILITIES_HEADER
#define SBOL_TEST_UTILITIES_HEADER

#include "prototypes.h"

char  randomChar();
char* randomString();
char* randomUniqueURI(Document* doc);
int randomNumber(int max);
char** getFilenames(char* dirname);

#endif
