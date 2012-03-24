#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"

#define SBOL_TEST_DEBUG 1

#define NUM_VALID_EXAMPLES   1
#define NUM_INVALID_EXAMPLES 0

#define VALID_EXAMPLES_DIR   "../examples/valid"
#define INVALID_EXAMPLES_DIR "../examples/invalid"
#define TEST_OUTPUT_DIR      "./output"

// This verfies that there aren't any
// SBOL objects loaded. It's good to put
// at the beginning of each test to prevent
// contamination by earlier failed tests.
void TestNothingLoaded(CuTest *tc) {
	CuAssertIntEquals(tc, 0, getNumSBOLObjects());
	CuAssertIntEquals(tc, 0, getNumSBOLCompoundObjects());
	CuAssertIntEquals(tc, 0, getNumDNASequences());
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
	CuAssertIntEquals(tc, 0, getNumCollections());
}

/****************************************
 * These tests check that the content
 * of each example file was loaded into
 * memory correctly. They shouldn't be
 * run on their own, but called from
 * other tests that read example files.
 ****************************************/

void TestLoadedValid01(CuTest *tc) {
	// check how many objects of each type were created
	CuAssertIntEquals(tc, 1, getNumSBOLObjects());
	CuAssertIntEquals(tc, 1, getNumSBOLCompoundObjects());
	CuAssertIntEquals(tc, 0, getNumDNASequences());
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	CuAssertIntEquals(tc, 0, getNumCollections());
	// check dc1
	DNAComponent *dc1 = getNthDNAComponent(0);
	CuAssertStrEquals(tc, "http://example.com/dc1", getDNAComponentURI(dc1));
	CuAssertStrEquals(tc, "DC1", getDNAComponentDisplayID(dc1));
	CuAssertPtrEquals(tc, NULL, getDNAComponentName(dc1));
	CuAssertPtrEquals(tc, NULL, getDNAComponentDescription(dc1));
	CuAssertPtrEquals(tc, NULL, getDNAComponentSequence(dc1));
}

/******************************
 * The main test function.
 * It loads the example files
 * and checks that each was
 * interpreted correctly.
 ******************************/

// a list of all the valid example filenames
// so they can be retrieved by index in a loop
static char *VALID_EXAMPLE_FILENAMES[NUM_VALID_EXAMPLES] = {
	VALID_EXAMPLES_DIR "/valid01_dna_component_empty.xml"
};

// a list of all the TestLoadedValid* functions
// so they can be retrieved by index in a loop
static void (*TEST_LOADED_FUNCTIONS[NUM_VALID_EXAMPLES])() = {
	TestLoadedValid01
};

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
