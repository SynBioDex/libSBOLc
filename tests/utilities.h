#ifndef SBOL_TEST_UTILITIES_HEADER
#define SBOL_TEST_UTILITIES_HEADER

char  randomChar();
char* randomString();
char* randomUniqueURI(const Document* doc);
int randomNumber(int max);
char** getFilenames(char* dirname);

#endif
