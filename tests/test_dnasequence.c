#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "document.h"
#include "dnasequence.h"

#define NUM_FAST_TESTS 10000

void TestCreateEmptyDNASequence(CuTest* tc) {
	Document* doc = createDocument();
	DNASequence* seq = createDNASequence(doc, "");
	setDNASequenceNucleotides(seq, "");
	CuAssertStrEquals(tc, "", getDNASequenceURI(seq));
	CuAssertStrEquals(tc, "", getDNASequenceNucleotides(seq));
	deleteDocument(doc);
}

void TestCreateNullDNASequence(CuTest* tc) {
	Document* doc = createDocument();
	DNASequence* seq = createDNASequence(doc, NULL);
	CuAssertStrEquals(tc, NULL, getDNASequenceURI(seq));
	CuAssertPtrEquals(tc, NULL, getDNASequenceNucleotides(seq));
	deleteDocument(doc);
}

void TestCreateRandomDNASequence(CuTest* tc) {
	Document* doc = createDocument();
	int repeat;
	char* uri;
	char* nt;
	DNASequence* seq;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		uri = randomUniqueURI(doc);
		nt = randomUniqueURI(doc);
		seq = createDNASequence(doc, uri);
		setDNASequenceNucleotides(seq, nt);
		CuAssertStrEquals(tc, uri, getDNASequenceURI(seq));
		CuAssertStrEquals(tc, nt, getDNASequenceNucleotides(seq));
		deleteDNASequence(seq);
	}
	deleteDocument(doc);
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
