#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include "CuTest.h"
#include "utilities.h"
#include "core.h"

#define OUTPUT_FILE "output.xml"

void TestMini1(CuTest* tc) {
	char* filename = "../examples/valid/mini1.nt";
	printf("reading %s\n", filename);
	readSBOLCore(filename);
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
	char* filename = "../examples/valid/mini2.nt";
	printf("reading %s\n", filename);
	readSBOLCore(filename);
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
	char* filename = "../examples/valid/mini3.nt";
	printf("reading %s\n", filename);
	readSBOLCore(filename);
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

void TestValid1(CuTest* tc) {
	char* filename = "../examples/valid/valid1.xml";
	printf("reading %s\n", filename);
	readSBOLCore(filename);
	printSBOLCore();
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	DNAComponent* com = getNthDNAComponent(0);
	CuAssertStrEquals(tc, "http://example.com/dc1", getDNAComponentID(com));
	CuAssertStrEquals(tc, "Some display ID", getDNAComponentName(com)); // TODO is this backward?
	CuAssertStrEquals(tc, "Valid because only required field for a DNAComponent is displayId",
			getDNAComponentDescription(com));
	int result = writeSBOLCore(OUTPUT_FILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
}

CuSuite* ReaderGetSuite() {
	CuSuite* readerTests = CuSuiteNew();
	SUITE_ADD_TEST(readerTests, TestMini1);
	SUITE_ADD_TEST(readerTests, TestMini2);
	SUITE_ADD_TEST(readerTests, TestMini3);
	//SUITE_ADD_TEST(readerTests, TestValid1);
	return readerTests;
}
