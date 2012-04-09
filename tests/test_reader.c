#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

// Loads the example files and checks
// that each was interpreted correctly.
void TestReadValidExamples(CuTest *tc) {
	Document* doc;
	printf("\n");
	int n;
	for (n=0; n<NUM_VALID_EXAMPLES; n++) {
		doc = createDocument();
		TestNothingLoaded(tc, doc);
 		printf("reading %s\n", VALID_EXAMPLE_FILENAMES[n]);
		readDocument(doc, VALID_EXAMPLE_FILENAMES[n]);
		#ifdef SBOL_DEBUG_STATEMENTS
		printDocument(doc);
		#endif
		TEST_LOADED_FUNCTIONS[n](tc, doc);
		deleteDocument(doc);
	}
}

CuSuite* ReaderGetSuite() {
	CuSuite* readerTests = CuSuiteNew();
	SUITE_ADD_TEST(readerTests, TestReadValidExamples);
	return readerTests;
}
