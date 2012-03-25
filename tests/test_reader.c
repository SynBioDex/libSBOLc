#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

// Loads the example files and checks
// that each was interpreted correctly.
void TestReadValidExamples(CuTest *tc) {
	int n;
	for (n=0; n<NUM_VALID_EXAMPLES; n++) {
		cleanupSBOLCore();
		TestNothingLoaded(tc);
 		printf("reading %s\n", VALID_EXAMPLE_FILENAMES[n]);
		readSBOLCore(VALID_EXAMPLE_FILENAMES[n]);
		#if SBOL_TEST_DEBUG
		printSBOLCore();
		#endif
		TEST_LOADED_FUNCTIONS[n](tc);
		cleanupSBOLCore();
	}
}

CuSuite* ReaderGetSuite() {
	CuSuite* readerTests = CuSuiteNew();
	SUITE_ADD_TEST(readerTests, TestReadValidExamples);
	return readerTests;
}
