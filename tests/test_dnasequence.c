#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "dnasequence.h"

#define NUM_FAST_TESTS 10000

void TestCreateEmptyDNASequence(CuTest* tc) {
	DNASequence* seq = createDNASequence("");
	CuAssertStrEquals(tc, "", seq->nucleotides);
}

void TestCreateNullDNASequence(CuTest* tc) {
	DNASequence* seq = createDNASequence(NULL);
	CuAssertStrEquals(tc, NULL, seq->nucleotides);
}

void TestCreateRandomDNASequence(CuTest* tc) {
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

CuSuite* DNASequenceGetSuite() {
	CuSuite* dnaSequenceTests = CuSuiteNew();
	SUITE_ADD_TEST(dnaSequenceTests, TestCreateEmptyDNASequence);
	SUITE_ADD_TEST(dnaSequenceTests, TestCreateNullDNASequence);
	SUITE_ADD_TEST(dnaSequenceTests, TestCreateRandomDNASequence);
	return dnaSequenceTests;
}
