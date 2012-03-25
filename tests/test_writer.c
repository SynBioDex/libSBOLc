#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

void TestRecreateValid01(CuTest *tc) {
	DNAComponent *com = createDNAComponent("http://example.com/dc1");
	setDNAComponentDisplayID(com, "DC1");
}

void TestRecreateValid02(CuTest *tc) {
	DNAComponent *com = createDNAComponent("http://example.com/dc1");
	setDNAComponentDisplayID(com, "DC1");
	setDNAComponentName(com, "DnaComponent1");
	setDNAComponentDescription(com, "DnaComponent with only name and description");
}

void TestRecreateValid03(CuTest *tc) {
	DNAComponent *com = createDNAComponent("http://example.com/dc1");
	setDNAComponentDisplayID(com, "DC1");
	setDNAComponentName(com, "DnaComponent1");
	setDNAComponentDescription(com, "DnaComponent with sequence information");
	DNASequence *seq = createDNASequence("http://example.com/ds1");
	setNucleotides(seq, "tccctatcagtgat");
	setDNAComponentSequence(com, seq);
}

void TestRecreateValid04(CuTest *tc) {
	// components
	DNAComponent *dc1 = createDNAComponent("http://example.com/dc1");
	DNAComponent *dc2 = createDNAComponent("http://example.com/dc2");
	setDNAComponentDisplayID(dc1, "DC1");
	setDNAComponentDisplayID(dc2, "DC2");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	setDNAComponentDescription(dc1, "DnaComponent with one sequence annotation");
	setDNAComponentDescription(dc2, "Another DNA component");
	// sequence
	DNASequence *ds1 = createDNASequence("http://example.com/ds1");
	setNucleotides(ds1, "tccctatcagtgat");
	setDNAComponentSequence(dc1, ds1);
	// annotation
	SequenceAnnotation *sa1 = createSequenceAnnotation("http://example.com/sa1");
	setSubComponent(sa1, dc2);
	addSequenceAnnotation(dc1, sa1);
}

void (*TEST_RECREATE_FUNCTIONS[NUM_VALID_EXAMPLES])() = {
	TestRecreateValid01,
	TestRecreateValid02,
	TestRecreateValid03,
	TestRecreateValid04
};

void TestRecreateValidExamples(CuTest *tc) {
	printf("\n");
	int n;
	for (n=0; n<NUM_VALID_EXAMPLES; n++) {
		cleanupSBOLCore();
		TestNothingLoaded(tc);
		printf("creating %s\n", TEST_OUTPUT_FILENAMES[n]);
		TEST_RECREATE_FUNCTIONS[n](tc);
		writeSBOLCore(TEST_OUTPUT_FILENAMES[n]);
		cleanupSBOLCore();
		TestNothingLoaded(tc);
		readSBOLCore(TEST_OUTPUT_FILENAMES[n]);
		TEST_LOADED_FUNCTIONS[n](tc);
		cleanupSBOLCore();
	}
}

CuSuite* WriterGetSuite() {
	CuSuite* writerTests = CuSuiteNew();
	SUITE_ADD_TEST(writerTests, TestRecreateValidExamples);
	return writerTests;
}
