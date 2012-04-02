#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

// declare functions from the sbol_create_valid* examples
void CreateValid01();
void CreateValid02();
void CreateValid03();
void CreateValid04();
void CreateValid05();
void CreateValid06();
void CreateValid07();
void CreateValid08();
void CreateValid09();
void CreateValid10();
void CreateValid11();
void CreateValid12();
void CreateValid13();

// put them in an array so they can be called by index
void (*CREATE_FUNCTIONS[NUM_VALID_EXAMPLES])() = {
	CreateValid01,
	CreateValid02,
	CreateValid03,
	CreateValid04,
	CreateValid05,
	CreateValid06,
	CreateValid07,
	CreateValid08,
	CreateValid09,
	CreateValid10,
	CreateValid11,
	CreateValid12,
	CreateValid13
};

// check that the xml they create is actually valid
void CreateValidExamples(CuTest *tc) {
	printf("\n");
	int n;
	for (n=0; n<NUM_VALID_EXAMPLES; n++) {
		cleanupSBOLCore();
		TestNothingLoaded(tc);
		printf("recreating %s\n", TEST_OUTPUT_FILENAMES[n]);
		CREATE_FUNCTIONS[n]();
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
	SUITE_ADD_TEST(writerTests, CreateValidExamples);
	return writerTests;
}
