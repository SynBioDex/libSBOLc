#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "core.h"

// TODO write equality test functions and use them to test that these are identical to originals
// TODO need a separate notion of displayID! (or really URI probably)
// TODO establish easy patterns for adding subparts ect.

void TestRecreateValid1(CuTest* tc) {
	char* filename = "valid1.xml";
	printf("recreating %s\n", filename);
	DNAComponent* com = createDNAComponent("http://example.com/dc1");
	setDNAComponentName(com, "DnaComponent1");
	setDNAComponentDescription(com, "Valid because only required field for a DNAComponent is displayId");
	writeSBOLCore(filename);
}

void TestRecreateValid2(CuTest* tc) {
	// dna components
	DNAComponent* dc1 = createDNAComponent("http://example.com/dc1");
	DNAComponent* dc2 = createDNAComponent("http://example.com/dc2");
	DNAComponent* dc3 = createDNAComponent("http://example.com/dc3");
	DNAComponent* dc4 = createDNAComponent("http://example.com/dc4");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	setDNAComponentName(dc3, "DnaComponent3");
	setDNAComponentName(dc4, "DnaComponent4");
	setDNAComponentDescription(dc1, "Various sequence annotations");
	setDNAComponentDescription(dc2, "Another DNA component");
	// dna sequences
	DNASequence* ds1 = createDNASequence("http://example.com/ds1");
	setNucleotides(ds1, "tccctatcagtgat");
	setDNAComponentSequence(dc1, ds1);
	// sa1
	SequenceAnnotation* sa1 = createSequenceAnnotation("http://example.com/sa1");
	setSubComponent(sa1, dc2);
	addSequenceAnnotation(dc1, sa1);
	// sa2
	SequenceAnnotation* sa2 = createSequenceAnnotation("http://example.com/sa2");
	setBioStart(sa2, 1);
	setBioEnd(sa2, 54);
	// TODO strand field
	setSubComponent(sa2, dc3);
	addSequenceAnnotation(dc1, sa2);
	// sa3
	SequenceAnnotation* sa3 = createSequenceAnnotation("http://example.com/sa3");
	addPrecedesRelationship(sa3, sa2);
	setSubComponent(sa3, dc4);
	// serialize
	char* filename = "valid2.xml";
	printf("recreating %s\n", filename);
	int result = writeSBOLCore(filename);
	CuAssertIntEquals(tc, 0, result);
}

CuSuite* WriterGetSuite() {
	CuSuite* writerTests = CuSuiteNew();
	SUITE_ADD_TEST(writerTests, TestRecreateValid1);
	SUITE_ADD_TEST(writerTests, TestRecreateValid2);
	return writerTests;
}
