#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "core.h"
#include "writer.h"
#include <libxml/parser.h>

#define SIMPLE_INFILE  "../examples/valid/ntriples_simple.nt"
#define SIMPLE_OUTFILE "ntriples_simple.xml"

void TestNTriplesSimple(CuTest* tc) {
	cleanupSBOLCore();
	readSBOLCore(SIMPLE_INFILE);
	//writeSBOLCore(SIMPLE_OUTFILE); // CAUSES SEGFAULT
	//cleanupSBOLCore();             // CAUSES SEGFAULT
    xmlDocPtr doc = xmlParseFile(SIMPLE_OUTFILE);
	CuAssertIntEquals(tc, 1, isValidSBOL(doc));
}

CuSuite* WriteExamplesGetSuite() {
	CuSuite* writeExamplesTests = CuSuiteNew();
	//SUITE_ADD_TEST(writeExamplesTests, TestNTriplesSimple);
	return writeExamplesTests;
}
