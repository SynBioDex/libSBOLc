#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"

// TODO also validate against schema before reading

#define OUTPUT_FILE "output.xml"

void TestMini1(CuTest* tc) {
	cleanupSBOLCore();
	char* filename = "../examples/ntriples/mini1.nt";
	printf("reading %s\n", filename);
	readSBOLCore(filename);
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	DNAComponent* com = getNthDNAComponent(0);
	CuAssertStrEquals(tc, "com1", getDNAComponentDisplayID(com));
	CuAssertStrEquals(tc, "com1 is a test component", 
			getDNAComponentDescription(com));
	int result = writeSBOLCore(OUTPUT_FILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
}

void TestMini2(CuTest* tc) {
	cleanupSBOLCore();
	char* filename = "../examples/ntriples/mini2.nt";
	printf("reading %s\n", filename);
	readSBOLCore(filename);
	CuAssertIntEquals(tc, 1, getNumDNASequences());
	DNASequence* seq = getNthDNASequence(0);
	CuAssertStrEquals(tc, "sequence1", getDNASequenceURI(seq));
	CuAssertStrEquals(tc, "acgtgacgtagctacgtacgtgtac", getNucleotides(seq));
	int result = writeSBOLCore(OUTPUT_FILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumDNASequences());
}

void TestMini3(CuTest* tc) {
	cleanupSBOLCore();
	char* filename = "../examples/ntriples/mini3.nt";
	printf("reading %s\n", filename);
	readSBOLCore(filename);
	CuAssertIntEquals(tc, 1, getNumSequenceAnnotations());
	SequenceAnnotation* ann = getNthSequenceAnnotation(0);
	CuAssertStrEquals(tc, "sa1", getSequenceAnnotationURI(ann));
	CuAssertIntEquals(tc, 1, getBioStart(ann));
	CuAssertIntEquals(tc, 1234, getBioEnd(ann));
	int result = writeSBOLCore(OUTPUT_FILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
}

void TestValid1(CuTest* tc) {
	cleanupSBOLCore();
	char* filename = "../examples/valid/valid1.xml";
	printf("reading %s\n", filename);
	readSBOLCore_xml(filename);
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	DNAComponent *com = getNthDNAComponent(0);
	CuAssertStrEquals(tc, "http://example.com/dc1", getDNAComponentURI(com));
	CuAssertStrEquals(tc, "Some display ID", getDNAComponentDisplayID(com));
	CuAssertStrEquals(tc, "Valid because only required field for a DNAComponent is displayId",
			getDNAComponentDescription(com));
	int result = writeSBOLCore(OUTPUT_FILE);
	CuAssertIntEquals(tc, 0, result);
	cleanupSBOLCore();
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
}

void TestValid2(CuTest* tc) {
	char* filename = "../examples/ntriples/valid2.nt";
	printf("reading %s\n", filename);
	readSBOLCore(filename);
	// components
	CuAssertIntEquals(tc, 4, getNumDNAComponents());
	CuAssertIntEquals(tc, 1, isDNAComponentURI("http://example.com/dc1"));
	CuAssertIntEquals(tc, 1, isDNAComponentURI("http://example.com/dc2"));
	CuAssertIntEquals(tc, 1, isDNAComponentURI("http://example.com/dc3"));
	CuAssertIntEquals(tc, 1, isDNAComponentURI("http://example.com/dc4"));
	DNAComponent* dc1 = getDNAComponent("http://example.com/dc1");
	DNAComponent* dc2 = getDNAComponent("http://example.com/dc2");
	DNAComponent* dc3 = getDNAComponent("http://example.com/dc3");
	DNAComponent* dc4 = getDNAComponent("http://example.com/dc4");
	CuAssertStrEquals(tc, "DC1", getDNAComponentDisplayID(dc1));
	CuAssertStrEquals(tc, "DC2", getDNAComponentDisplayID(dc2));
	CuAssertStrEquals(tc, "DC3", getDNAComponentDisplayID(dc3));
	CuAssertStrEquals(tc, "DC4", getDNAComponentDisplayID(dc4));
	CuAssertStrEquals(tc, "DnaComponent1", getDNAComponentName(dc1));
	CuAssertStrEquals(tc, "DnaComponent2", getDNAComponentName(dc2));
	CuAssertStrEquals(tc, "DnaComponent3", getDNAComponentName(dc3));
	CuAssertStrEquals(tc, "DnaComponent4", getDNAComponentName(dc4));
	CuAssertStrEquals(tc, "Various sequence annotations", getDNAComponentDescription(dc1));
	CuAssertStrEquals(tc, "Another DNA component", getDNAComponentDescription(dc2));
	CuAssertStrEquals(tc, NULL, getDNAComponentDescription(dc3));
	CuAssertStrEquals(tc, NULL, getDNAComponentDescription(dc4));
	// sequence annotations
	CuAssertIntEquals(tc, 3, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 1, isSequenceAnnotationURI("http://example.com/sa1"));
	CuAssertIntEquals(tc, 1, isSequenceAnnotationURI("http://example.com/sa2"));
	CuAssertIntEquals(tc, 1, isSequenceAnnotationURI("http://example.com/sa3"));
	SequenceAnnotation* sa1 = getSequenceAnnotation("http://example.com/sa1");
	SequenceAnnotation* sa2 = getSequenceAnnotation("http://example.com/sa2");
	SequenceAnnotation* sa3 = getSequenceAnnotation("http://example.com/sa3");
	CuAssertPtrEquals(tc, dc2, getSubComponent(sa1));
	CuAssertPtrEquals(tc, dc3, getSubComponent(sa2));
	CuAssertIntEquals(tc, 3, getNumSequenceAnnotationsIn(dc1));
	CuAssertIntEquals(tc, 1, getBioStart(sa2));
	CuAssertIntEquals(tc, 54, getBioEnd(sa2));
	CuAssertIntEquals(tc, 1, getStrandPolarity(sa2));
	CuAssertIntEquals(tc, 1, precedes(sa3, sa2));
	CuAssertIntEquals(tc, 0, precedes(sa1, sa2));
	CuAssertIntEquals(tc, 0, precedes(sa2, sa3));
	// sequences
	CuAssertIntEquals(tc, 1, getNumDNASequences());
	CuAssertIntEquals(tc, 1, isDNASequenceURI("http://example.com/ds1"));
	DNASequence* ds1 = getDNASequence("http://example.com/ds1");
	CuAssertPtrEquals(tc, ds1, getDNAComponentSequence(dc1));
	// collections
	CuAssertIntEquals(tc, 0, getNumCollections());
	cleanupSBOLCore();
}

CuSuite* ReaderGetSuite() {
	CuSuite* readerTests = CuSuiteNew();
	SUITE_ADD_TEST(readerTests, TestMini1);
	SUITE_ADD_TEST(readerTests, TestMini2);
	SUITE_ADD_TEST(readerTests, TestMini3);
	SUITE_ADD_TEST(readerTests, TestValid1);
	SUITE_ADD_TEST(readerTests, TestValid2);
	return readerTests;
}
