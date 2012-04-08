#ifndef SBOL_TEST_EXAMPLES_HEADER
#define SBOL_TEST_EXAMPLES_HEADER

#include "CuTest.h"
#include "prototypes.h"

#define NUM_VALID_EXAMPLES   13
#define NUM_INVALID_EXAMPLES 13 /// @todo finish 14-19

#define VALID_EXAMPLES_DIR   SBOL_EXAMPLE_DIR "/xml/valid"
#define INVALID_EXAMPLES_DIR SBOL_EXAMPLE_DIR "/xml/invalid"
#define TEST_OUTPUT_DIR      SBOL_RELEASE_DIR "/tests"

struct _CuTest;

// arrays of filenames for reading
// and writing example tests
char   *VALID_EXAMPLE_FILENAMES[NUM_VALID_EXAMPLES];
char *INVALID_EXAMPLE_FILENAMES[NUM_INVALID_EXAMPLES+6];
char     *TEST_OUTPUT_FILENAMES[NUM_VALID_EXAMPLES];

// array of functions for checking that
// the example content was loaded correctly
void (*TEST_LOADED_FUNCTIONS[NUM_VALID_EXAMPLES])(CuTest* tc, Document* doc);

#endif
