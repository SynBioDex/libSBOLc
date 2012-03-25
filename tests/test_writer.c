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

void TestRecreateValid05(CuTest *tc) {
	DNAComponent *com = createDNAComponent("http://example.com/dc1");
	// dc1 has an rdf:type node too, which libSBOL ignores
	setDNAComponentDisplayID(com, "DC1");
	setDNAComponentName(com, "DnaComponent1");
	setDNAComponentDescription(com, "A DnaComponent can optionally use multiple types from Sequence Ontology");
	DNASequence *seq = createDNASequence("http://example.com/ds1");
	setNucleotides(seq, "tccctatcagtgat");
	setDNAComponentSequence(com, seq);
}

void TestRecreateValid06(CuTest *tc) {
	DNAComponent *com = createDNAComponent("http://example.com/dc1");
	// dc1 has two rdf:type nodes, which libSBOL ignores
	setDNAComponentDisplayID(com, "DC1");
	setDNAComponentName(com, "DnaComponent1");
	setDNAComponentDescription(com, "A DnaComponent can optionally use a type from Sequence Ontology");
	DNASequence *seq = createDNASequence("http://example.com/ds1");
	setNucleotides(seq, "tccctatcagtgat");
	setDNAComponentSequence(com, seq);
}

void TestRecreateValid07(CuTest *tc) {
	// components
	DNAComponent *dc1 = createDNAComponent("http://example.com/dc1");
	DNAComponent *dc2 = createDNAComponent("http://example.com/dc2");
	// dc1 has a dc:creator node that libSBOLc ignores
	setDNAComponentDisplayID(dc1, "DC1");
	setDNAComponentDisplayID(dc2, "DC2");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	setDNAComponentDescription(dc1, "It is valid to have additional elements in any SBOL element as long as they appear after \n\t\tthe elements defined in SBOL core model. This example adds dc:creator annotations to SBOL elements");
	setDNAComponentDescription(dc2, "Another DNA component");
	// sequence
	DNASequence *ds1 = createDNASequence("http://example.com/ds1");
	setNucleotides(ds1, "tccctatcagtgat");
	setDNAComponentSequence(dc1, ds1);
	// annotation
	SequenceAnnotation *sa1 = createSequenceAnnotation("http://example.com/sa1");
	// sa1 has a dc:creator node that libSBOLc ignores
	setSubComponent(sa1, dc2);
	addSequenceAnnotation(dc1, sa1);
}

void TestRecreateValid08(CuTest *tc) {
	// components
	DNAComponent *dc1 = createDNAComponent("http://example.com/dc1");
	DNAComponent *dc2 = createDNAComponent("http://example.com/dc2");
	DNAComponent *dc3 = createDNAComponent("http://example.com/dc3");
	DNAComponent *dc4 = createDNAComponent("http://example.com/dc4");
	setDNAComponentDisplayID(dc1, "DC1");
	setDNAComponentDisplayID(dc2, "DC2");
	setDNAComponentDisplayID(dc3, "DC3");
	setDNAComponentDisplayID(dc4, "DC4");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	setDNAComponentName(dc3, "DnaComponent3");
	setDNAComponentName(dc4, "DnaComponent4");
	setDNAComponentDescription(dc1, "Various sequence annotations");
	setDNAComponentDescription(dc2, "Another DNA component");
	// sequences
	DNASequence *ds1 = createDNASequence("http://example.com/ds1");
	DNASequence *ds2 = createDNASequence("http://example.com/ds2");
	setNucleotides(ds1, "tccctatcagtgat");
	setNucleotides(ds2, "tc");
	setDNAComponentSequence(dc1, ds1);
	setDNAComponentSequence(dc2, ds2);
	// annotations
	SequenceAnnotation *sa1 = createSequenceAnnotation("http://example.com/sa1");
	SequenceAnnotation *sa2 = createSequenceAnnotation("http://example.com/sa2");
	SequenceAnnotation *sa3 = createSequenceAnnotation("http://example.com/sa3");
	addSequenceAnnotation(dc1, sa1);
	addSequenceAnnotation(dc1, sa2);
	addSequenceAnnotation(dc1, sa3);
	setBioStart(sa1, 1); setBioEnd(sa1, 2);
	setBioStart(sa2, 3); setBioEnd(sa2, 5);
	setSubComponent(sa1, dc2);
	setSubComponent(sa2, dc3);
	setSubComponent(sa3, dc4);
	addPrecedesRelationship(sa1, sa2);
	addPrecedesRelationship(sa1, sa3);
}

void TestRecreateValid09(CuTest *tc) {
	// components
	DNAComponent *dc1 = createDNAComponent("http://example.com/dc1");
	DNAComponent *dc2 = createDNAComponent("http://example.com/dc2");
	setDNAComponentDisplayID(dc1, "DC1");
	setDNAComponentDisplayID(dc2, "DC2");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	setDNAComponentDescription(dc1, "Multiple DNA components at the top level are allowed even without a collection");
	// sequence
	DNASequence *ds1 = createDNASequence("http://example.com/ds1");
	setNucleotides(ds1, "tccctatcagtgat");
	setDNAComponentSequence(dc1, ds1);
}

void TestRecreateValid10(CuTest *tc) {
	Collection *col = createCollection("http://example.com/collection1");
	setCollectionDisplayID(col, "Coll1");
	setCollectionName(col, "Collection1");
	setCollectionDescription(col, "A collection may be empty");
}

void TestRecreateValid11(CuTest *tc) {
	// collection
	Collection *col = createCollection("http://example.com/collection1");
	setCollectionDisplayID(col, "Coll1");
	setCollectionName(col, "Collection1");
	setCollectionDescription(col, "A collection may contain multiple components");
	// components
	DNAComponent *dc1 = createDNAComponent("http://example.com/dc1");
	DNAComponent *dc2 = createDNAComponent("http://example.com/dc2");
	setDNAComponentDisplayID(dc1, "DC1");
	setDNAComponentDisplayID(dc2, "DC2");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	addDNAComponentToCollection(dc1, col);
	addDNAComponentToCollection(dc2, col);
	// sequence
	DNASequence *ds1 = createDNASequence("http://example.com/ds1");
	setNucleotides(ds1, "tccctatcagtgat");
	setDNAComponentSequence(dc1, ds1);
}

void TestRecreateValid12(CuTest *tc) {
	// collections
	Collection *c1 = createCollection("http://example.com/collection1");
	Collection *c2 = createCollection("http://example.com/collection2");
	setCollectionDisplayID(c1, "Coll1");
	setCollectionDisplayID(c2, "Coll2");
	setCollectionName(c1, "Collection1");
	setCollectionName(c2, "Collection2");
	setCollectionDescription(c1, "This is the first collection in the document");
	setCollectionDescription(c2, "This is the second collection in the document");
	// components
	DNAComponent *dc1 = createDNAComponent("http://example.com/dc1");
	DNAComponent *dc2 = createDNAComponent("http://example.com/dc2");
	setDNAComponentDisplayID(dc1, "DC1");
	setDNAComponentDisplayID(dc2, "DC2");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	addDNAComponentToCollection(dc1, c1);
	addDNAComponentToCollection(dc2, c2);
	// sequence
	DNASequence *ds1 = createDNASequence("http://example.com/ds1");
	setNucleotides(ds1, "tccctatcagtgat");
	setDNAComponentSequence(dc1, ds1);
}

void TestRecreateValid13(CuTest *tc) {
	DNASequence *seq = createDNASequence("http://example.com/ds1");
	setNucleotides(seq, "tccctatcagtgat");
}

void (*TEST_RECREATE_FUNCTIONS[NUM_VALID_EXAMPLES])() = {
	TestRecreateValid01,
	TestRecreateValid02,
	TestRecreateValid03,
	TestRecreateValid04,
	TestRecreateValid05,
	TestRecreateValid06,
	TestRecreateValid07,
	TestRecreateValid08,
	TestRecreateValid09,
	TestRecreateValid10,
	TestRecreateValid11,
	TestRecreateValid12,
	TestRecreateValid13
};

void TestRecreateValidExamples(CuTest *tc) {
	printf("\n");
	int n;
	for (n=0; n<NUM_VALID_EXAMPLES; n++) {
		cleanupSBOLCore();
		TestNothingLoaded(tc);
		printf("recreating %s\n", TEST_OUTPUT_FILENAMES[n]);
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
