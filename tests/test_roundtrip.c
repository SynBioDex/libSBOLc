#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <libxml/parser.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"

#define VALID_EXAMPLES_DIR   "../examples/valid/"
#define INVALID_EXAMPLES_DIR "../examples/invalid/"
#define OUTPUT_FILE          "output.xml"

static char**   VALID_EXAMPLES;
static char** INVALID_EXAMPLES;

void TestRoundTripValidOne(CuTest* tc) {
	char* filename = "../examples/valid/valid1.xml";
	printf("testing %s\n", filename);
	readSBOLCore(filename);
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	DNAComponent* com = getNthDNAComponent(0);
	CuAssertStrEquals(tc, "Some display ID", getDNAComponentName(com));
	CuAssertStrEquals(tc,
			"Valid because only required field for a DNAComponent is displayId", 
			getDNAComponentDescription(com));
	int result = writeSBOLCore(OUTPUT_FILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
}

void TestRoundTripValidExamples(CuTest* tc) {
	if (!VALID_EXAMPLES)
		VALID_EXAMPLES = getFilenames(VALID_EXAMPLES_DIR);
	int i;
	char* filename;
	int result;
	i = 0;
	while (filename = VALID_EXAMPLES[i++]) {
		printf("testing %s\n", filename);
		readSBOLCore(filename);
		result = writeSBOLCore(OUTPUT_FILE);
		cleanupSBOLCore();
		CuAssertIntEquals(tc, 0, result);
	}
	cleanupSBOLCore();
}

CuSuite* RoundTripGetSuite() {
	CuSuite* roundTripTests = CuSuiteNew();
	//SUITE_ADD_TEST(roundTripTests, TestRoundTripValidOne);
	//SUITE_ADD_TEST(roundTripTests, TestRoundTripValidExamples);
	return roundTripTests;
}
