#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "sequence.h"

#define NUM_FAST_TESTS 10000

void TestCreateEmptySequence(CuTest* tc) {
	DNASequence* seq = createDNASequence("");
	CuAssertStrEquals(tc, "", seq->nucleotides);
}

void TestCreateNullSequence(CuTest* tc) {
	DNASequence* seq = createDNASequence(NULL);
	CuAssertStrEquals(tc, NULL, seq->nucleotides);
}

void TestCreateRandomSequence(CuTest* tc) {
	char* nt;
	DNASequence* seq;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		nt = randomString();
		seq = createDNASequence(nt);
		CuAssertStrEquals(tc, nt, seq->nucleotides);
		deleteDNASequence(seq);
		// TODO check that delete worked?
	}
}

CuSuite* SequenceGetSuite() {
	CuSuite* sequenceTests = CuSuiteNew();
	SUITE_ADD_TEST(sequenceTests, TestCreateEmptySequence);
	SUITE_ADD_TEST(sequenceTests, TestCreateNullSequence);
	SUITE_ADD_TEST(sequenceTests, TestCreateRandomSequence);
	return sequenceTests;
}
