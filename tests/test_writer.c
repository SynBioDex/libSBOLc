#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

void TestRecreateValid01(CuTest *tc) {
	DNAComponent *com = createDNAComponent("http://example.com/dc1");
	setDNAComponentDisplayID(com, "DC1");
}

void (*TEST_RECREATE_FUNCTIONS[NUM_VALID_EXAMPLES])() = {
	TestRecreateValid01
};

void TestRecreateValidExamples(CuTest *tc) {
	int n;
	for (n=0; n<1; n++) { // TODO NUM_VALID_EXAMPLES
		cleanupSBOLCore();
		TestNothingLoaded(tc);
		printf("creating %s\n", TEST_OUTPUT_FILENAMES[n]);
		TEST_RECREATE_FUNCTIONS[n](tc);
		writeSBOLCore(TEST_OUTPUT_FILENAMES[n]);
		cleanupSBOLCore();
		TestNothingLoaded(tc);
		readSBOLCore(TEST_OUTPUT_FILENAMES[n]);
		TEST_LOADED_FUNCTIONS[n](tc);
		cleanupSBOLCore();
	}
}

CuSuite* WriterGetSuite() {
	CuSuite* writerTests = CuSuiteNew();
	SUITE_ADD_TEST(writerTests, TestRecreateValidExamples);
	return writerTests;
}
