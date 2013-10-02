#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <libxml/parser.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

void TestRoundTripValidExamples(CuTest* tc) {
	printf("\n");
	int n;
	for (n=0; n<NUM_VALID_EXAMPLES; n++) {
		printf("roundtripping %s\n", VALID_EXAMPLE_FILENAMES[n]);
		
		// read an example
		Document* doc = createDocument();
		TestNothingLoaded(tc, doc);
		readDocument(doc, VALID_EXAMPLE_FILENAMES[n]);
		
		// check that it worked
		TEST_LOADED_FUNCTIONS[n](tc, doc);
		
		// write to a file
		writeDocumentToFile(doc, TEST_OUTPUT_FILENAMES[n]);
		
		// read that in again
		deleteDocument(doc);
		doc = createDocument();
		readDocument(doc, TEST_OUTPUT_FILENAMES[n]);
		
		// check that it worked again
		TEST_LOADED_FUNCTIONS[n](tc, doc);
	}
}

CuSuite* RoundTripGetSuite() {
	CuSuite* roundTripTests = CuSuiteNew();
	SUITE_ADD_TEST(roundTripTests, TestRoundTripValidExamples);
	return roundTripTests;
}
