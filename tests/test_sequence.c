#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "sequence.h"

#define NUM_FAST_TESTS 100000

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

int main(void) {
	// seed with current time
	// should only be done once
	srand( time(NULL) );
	
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestCreateRandomSequence);
	SUITE_ADD_TEST(suite, TestCreateEmptySequence);
	SUITE_ADD_TEST(suite, TestCreateNullSequence);
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}
