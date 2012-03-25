#ifndef SBOL_TEST_EXAMPLES_HEADER
#define SBOL_TEST_EXAMPLES_HEADER
#include "CuTest.h"

// TODO replace with SBOL_DEBUG_ACTIVE
#define SBOL_TEST_DEBUG 0

#define NUM_VALID_EXAMPLES   9
#define NUM_INVALID_EXAMPLES 0

#define VALID_EXAMPLES_DIR   "../examples/valid/"
#define INVALID_EXAMPLES_DIR "../examples/invalid/"
#define TEST_OUTPUT_DIR      "./"

struct _CuTest;

// arrays of filenames for reading
// and writing example tests
char *VALID_EXAMPLE_FILENAMES[13];
char   *TEST_OUTPUT_FILENAMES[13];

// array of functions for checking that
// the example content was loaded correctly
void (*TEST_LOADED_FUNCTIONS[13])();

void TestNothingLoaded(CuTest *tc);

#endif
