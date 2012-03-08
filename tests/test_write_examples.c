#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "core.h"
#include "writer.h"
#include <libxml/parser.h>

// TODO rename to test_roundtrip

#define NTRIPLES_INFILE  "../examples/valid/ntriples_simple.nt"
#define NTRIPLES_OUTFILE "ntriples_simple.xml"

#define VALID1_INFILE  "../examples/valid/valid1.xml"
#define VALID1_OUTFILE "valid1.xml"

#define VALID2_INFILE  "../examples/valid/valid2.xml"
#define VALID2_OUTFILE "valid2.xml"

void TestNTriplesSimple(CuTest* tc) {
	int result;
	readSBOLCore(NTRIPLES_INFILE);
	result = writeSBOLCore(NTRIPLES_OUTFILE);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, result);
}

void TestValid1(CuTest* tc) {
	int result;
	readSBOLCore(VALID1_INFILE);
	result = writeSBOLCore(VALID1_OUTFILE);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, result);
}

void TestValid2(CuTest* tc) {
	int result;
	readSBOLCore(VALID2_INFILE);
	result = writeSBOLCore(VALID2_OUTFILE);
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
