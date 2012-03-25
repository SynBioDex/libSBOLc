#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <libxml/parser.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

void TestRoundTripValidExamples(CuTest* tc) {
	int n;
	for (n=0; n<1; n++) { // TODO NUM_VALID_EXAMPLES
		printf("round-tripping %s\n", VALID_EXAMPLE_FILENAMES[n]);
		
		// read an example
		cleanupSBOLCore();
		TestNothingLoaded(tc);
		readSBOLCore(VALID_EXAMPLE_FILENAMES[n]);
		
		// check that it worked
		TEST_LOADED_FUNCTIONS[n](tc);
		
		// write to a file
		writeSBOLCore(TEST_OUTPUT_FILENAMES[n]);
		
		// read that in again
		cleanupSBOLCore();
		TestNothingLoaded(tc);
		readSBOLCore(TEST_OUTPUT_FILENAMES[n]);
		
		// check that it worked again
		TEST_LOADED_FUNCTIONS[n](tc);
	}
}

CuSuite* RoundTripGetSuite() {
	CuSuite* roundTripTests = CuSuiteNew();
	SUITE_ADD_TEST(roundTripTests, TestRoundTripValidExamples);
	return roundTripTests;
}
