#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "dnasequence.h"

#define NUM_FAST_TESTS 10000

void TestCreateEmptyDNASequence(CuTest* tc) {
	cleanupDNASequences();
	DNASequence* seq = createDNASequence("");
	setDNASequenceNucleotides(seq, "");
	CuAssertStrEquals(tc, "", getDNASequenceURI(seq));
	CuAssertStrEquals(tc, "", getDNASequenceNucleotides(seq));
}

void TestCreateNullDNASequence(CuTest* tc) {
	DNASequence* seq = createDNASequence(NULL);
	CuAssertStrEquals(tc, NULL, getDNASequenceURI(seq));
	CuAssertPtrEquals(tc, NULL, getDNASequenceNucleotides(seq));
}

void TestCreateRandomDNASequence(CuTest* tc) {
	cleanupDNASequences();
	int repeat;
	char* uri;
	char* nt;
	DNASequence* seq;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		uri = randomUniqueURI();
		nt = randomUniqueURI();
		// avoid duplicates
		seq = createDNASequence(uri);
		setDNASequenceNucleotides(seq, nt);
		CuAssertStrEquals(tc, uri, getDNASequenceURI(seq));
		CuAssertStrEquals(tc, nt, getDNASequenceNucleotides(seq));
		deleteDNASequence(seq);
	}
}

void PrintDNASequenceTestInfo() {
	printf("testing dnasequences\n");
}

CuSuite* DNASequenceGetSuite() {
	CuSuite* dnaSequenceTests = CuSuiteNew();
	SUITE_ADD_TEST(dnaSequenceTests, PrintDNASequenceTestInfo);
	SUITE_ADD_TEST(dnaSequenceTests, TestCreateEmptyDNASequence);
	SUITE_ADD_TEST(dnaSequenceTests, TestCreateNullDNASequence);
	SUITE_ADD_TEST(dnaSequenceTests, TestCreateRandomDNASequence);
	return dnaSequenceTests;
}
