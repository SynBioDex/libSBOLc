#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "CuTest.h"
#include "utilities.h"
#include "core.h"
#include "writer.h"
#include <libxml/parser.h>

// TODO rename to test_roundtrip

#define NTRIPLES_INFILE  "../examples/valid/ntriples_simple.nt"
#define NTRIPLES_OUTFILE "ntriples_simple.xml"

#define   VALID_EXAMPLES_DIR "../examples/valid/"
#define INVALID_EXAMPLES_DIR "../examples/invalid/"

#define OUTPUT_FILE "output.xml"

static char**   VALID_EXAMPLES;
static char** INVALID_EXAMPLES;

void TestNTriplesSimple(CuTest* tc) {
	int result;
	readSBOLCore(NTRIPLES_INFILE);
	result = writeSBOLCore(OUTPUT_FILE);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, result);
}

void TestValid1(CuTest* tc) {
	if (!VALID_EXAMPLES)
		VALID_EXAMPLES = getFilenames(VALID_EXAMPLES_DIR);
	int result;
	readSBOLCore(VALID_EXAMPLES[0]);
	printSBOLCore();
	result = writeSBOLCore(OUTPUT_FILE);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, result);
}

void TestValid2(CuTest* tc) {
	if (!VALID_EXAMPLES)
		VALID_EXAMPLES = getFilenames(VALID_EXAMPLES_DIR);
	int result;
	readSBOLCore(VALID_EXAMPLES[1]);
	result = writeSBOLCore(OUTPUT_FILE);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, result);
}

CuSuite* WriteExamplesGetSuite() {
	CuSuite* writeExamplesTests = CuSuiteNew();
	SUITE_ADD_TEST(writeExamplesTests, TestNTriplesSimple);
	//SUITE_ADD_TEST(writeExamplesTests, TestValid1);
	//SUITE_ADD_TEST(writeExamplesTests, TestValid2);
	return writeExamplesTests;
}
