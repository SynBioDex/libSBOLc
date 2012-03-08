#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "core.h"

#define MINI1_INFILE  "../examples/valid/mini1.nt"
#define MINI1_OUTFILE "mini1.nt"
#define MINI2_INFILE  "../examples/valid/mini2.nt"
#define MINI2_OUTFILE "mini2.nt"
#define MINI3_INFILE  "../examples/valid/mini3.nt"
#define MINI3_OUTFILE "mini3.nt"

void TestMini1(CuTest* tc) {
	readSBOLCore(MINI1_INFILE);
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	DNAComponent* com = getNthDNAComponent(0);
	CuAssertStrEquals(tc, "com1", getDNAComponentName(com));
	CuAssertStrEquals(tc, "com1 is a test component", 
			getDNAComponentDescription(com));
	int result = writeSBOLCore(MINI1_OUTFILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
}

void TestMini2(CuTest* tc) {
	readSBOLCore(MINI2_INFILE);
	CuAssertIntEquals(tc, 1, getNumDNASequences());
	DNASequence* seq = getNthDNASequence(0);
	CuAssertStrEquals(tc, "sequence1", getDNASequenceID(seq));
	CuAssertStrEquals(tc, "acgtgacgtagctacgtacgtgtac", getNucleotides(seq));
	int result = writeSBOLCore(MINI2_OUTFILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumDNASequences());
}

void TestMini3(CuTest* tc) {
	readSBOLCore(MINI3_INFILE);
	CuAssertIntEquals(tc, 1, getNumSequenceAnnotations());
	SequenceAnnotation* ann = getNthSequenceAnnotation(0);
	CuAssertStrEquals(tc, "sa1", getSequenceAnnotationID(ann));
	CuAssertIntEquals(tc, 1, getBioStart(ann));
	CuAssertIntEquals(tc, 1234, getBioEnd(ann));
	int result = writeSBOLCore(MINI3_OUTFILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
}

CuSuite* RoundTripGetSuite() {
	CuSuite* roundTripTests = CuSuiteNew();
	SUITE_ADD_TEST(roundTripTests, TestMini1);
	SUITE_ADD_TEST(roundTripTests, TestMini2);
	SUITE_ADD_TEST(roundTripTests, TestMini3);
	return roundTripTests;
}
