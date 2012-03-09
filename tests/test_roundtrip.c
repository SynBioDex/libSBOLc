#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <libxml/parser.h>
#include "CuTest.h"
#include "utilities.h"
#include "core.h"
#include "writer.h"

#define VALID_EXAMPLES_DIR   "../examples/valid/"
#define INVALID_EXAMPLES_DIR "../examples/invalid/"
#define OUTPUT_FILE          "output.xml"

static char**   VALID_EXAMPLES;
static char** INVALID_EXAMPLES;

void TestMini1(CuTest* tc) {
	readSBOLCore("../examples/valid/mini1.nt");
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	DNAComponent* com = getNthDNAComponent(0);
	CuAssertStrEquals(tc, "com1", getDNAComponentName(com));
	CuAssertStrEquals(tc, "com1 is a test component", 
			getDNAComponentDescription(com));
	int result = writeSBOLCore(OUTPUT_FILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
}

void TestMini2(CuTest* tc) {
	readSBOLCore("../examples/valid/mini2.nt");
	CuAssertIntEquals(tc, 1, getNumDNASequences());
	DNASequence* seq = getNthDNASequence(0);
	CuAssertStrEquals(tc, "sequence1", getDNASequenceID(seq));
	CuAssertStrEquals(tc, "acgtgacgtagctacgtacgtgtac", getNucleotides(seq));
	int result = writeSBOLCore(OUTPUT_FILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumDNASequences());
}

void TestMini3(CuTest* tc) {
	readSBOLCore("../examples/valid/mini3.nt");
	CuAssertIntEquals(tc, 1, getNumSequenceAnnotations());
	SequenceAnnotation* ann = getNthSequenceAnnotation(0);
	CuAssertStrEquals(tc, "sa1", getSequenceAnnotationID(ann));
	CuAssertIntEquals(tc, 1, getBioStart(ann));
	CuAssertIntEquals(tc, 1234, getBioEnd(ann));
	int result = writeSBOLCore(OUTPUT_FILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
}

void TestNTriplesSimple(CuTest* tc) {
	int result;
	readSBOLCore("../examples/valid/ntriples_simple.nt");
	result = writeSBOLCore(OUTPUT_FILE);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, result);
}

void TestRoundTripValidExamples(CuTest* tc) {
	if (!VALID_EXAMPLES)
		VALID_EXAMPLES = getFilenames(VALID_EXAMPLES_DIR);
	int i;
	char* filename;
	int result;
	int failures;
	i = 0;
	while (filename = VALID_EXAMPLES[i++]) {
		readSBOLCore(filename);
		result = writeSBOLCore(OUTPUT_FILE);
		cleanupSBOLCore();
		if (result != 0)
			failures++;
	}
	CuAssertIntEquals(tc, 0, failures);
}

CuSuite* RoundTripGetSuite() {
	CuSuite* roundTripTests = CuSuiteNew();
	SUITE_ADD_TEST(roundTripTests, TestMini1);
	SUITE_ADD_TEST(roundTripTests, TestMini2);
	//SUITE_ADD_TEST(roundTripTests, TestMini3);
	//SUITE_ADD_TEST(roundTripTests, TestNTriplesSimple);
	//SUITE_ADD_TEST(roundTripTests, TestRoundTripValidExamples);
	return roundTripTests;
}
