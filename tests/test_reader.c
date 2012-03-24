#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"

// TODO replace with SBOL_DEBUG_ACTIVE
#define SBOL_TEST_DEBUG 0

#define NUM_INVALID_EXAMPLES 0

#define VALID_EXAMPLES_DIR   "../examples/valid"
#define INVALID_EXAMPLES_DIR "../examples/invalid"
#define TEST_OUTPUT_DIR      "./output"

// This verfies that there aren't any
// SBOL objects loaded. It's good to put
// at the beginning of each test to prevent
// contamination by earlier failed tests.
void TestNothingLoaded(CuTest *tc) {
	CuAssertIntEquals(tc, 0, getNumSBOLObjects());
	CuAssertIntEquals(tc, 0, getNumSBOLCompoundObjects());
	CuAssertIntEquals(tc, 0, getNumDNASequences());
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
	CuAssertIntEquals(tc, 0, getNumCollections());
}

/****************************************
 * These tests check that the content
 * of each example file was loaded into
 * memory correctly. They shouldn't be
 * run on their own, but called from
 * other tests that read example files.
 ****************************************/

void TestLoadedValid01(CuTest *tc) {
	// check how many objects of each type were created
	CuAssertIntEquals(tc, 1, getNumSBOLObjects());
	CuAssertIntEquals(tc, 1, getNumSBOLCompoundObjects());
	CuAssertIntEquals(tc, 0, getNumDNASequences());
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	CuAssertIntEquals(tc, 0, getNumCollections());
	// check dc1
	DNAComponent *dc1 = getNthDNAComponent(0);
	CuAssertStrEquals(tc, "http://example.com/dc1", getDNAComponentURI(dc1));
	CuAssertStrEquals(tc, "DC1", getDNAComponentDisplayID(dc1));
	CuAssertPtrEquals(tc, NULL, getDNAComponentName(dc1));
	CuAssertPtrEquals(tc, NULL, getDNAComponentDescription(dc1));
	CuAssertPtrEquals(tc, NULL, getDNAComponentSequence(dc1));
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotationsIn(dc1));
	CuAssertIntEquals(tc, 0, getNumCollectionsFor(dc1));
}

void TestLoadedValid02(CuTest *tc) {
	// check how many objects of each type were created
	CuAssertIntEquals(tc, 1, getNumSBOLObjects());
	CuAssertIntEquals(tc, 1, getNumSBOLCompoundObjects());
	CuAssertIntEquals(tc, 0, getNumDNASequences());
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	CuAssertIntEquals(tc, 0, getNumCollections());
	// check dc1
	DNAComponent *dc1 = getNthDNAComponent(0);
	CuAssertStrEquals(tc, "http://example.com/dc1", getDNAComponentURI(dc1));
	CuAssertStrEquals(tc, "DC1", getDNAComponentDisplayID(dc1));
	CuAssertStrEquals(tc, "DnaComponent1", getDNAComponentName(dc1));
	CuAssertStrEquals(tc, "DnaComponent with only name and description", getDNAComponentDescription(dc1));
	CuAssertPtrEquals(tc, NULL, getDNAComponentSequence(dc1));
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotationsIn(dc1));
	CuAssertIntEquals(tc, 0, getNumCollectionsFor(dc1));
}

void TestLoadedValid03(CuTest *tc) {
	// check how many objects of each type were created
	CuAssertIntEquals(tc, 2, getNumSBOLObjects());
	CuAssertIntEquals(tc, 1, getNumSBOLCompoundObjects());
	CuAssertIntEquals(tc, 1, getNumDNASequences());
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	CuAssertIntEquals(tc, 0, getNumCollections());
	// check dc1
	DNAComponent *dc1 = getNthDNAComponent(0);
	CuAssertStrEquals(tc, "http://example.com/dc1", getDNAComponentURI(dc1));
	CuAssertStrEquals(tc, "DC1", getDNAComponentDisplayID(dc1));
	CuAssertStrEquals(tc, "DnaComponent1", getDNAComponentName(dc1));
	CuAssertStrEquals(tc, "DnaComponent with sequence information", getDNAComponentDescription(dc1));
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotationsIn(dc1));
	CuAssertIntEquals(tc, 0, getNumCollectionsFor(dc1));
	// check ds1
	DNASequence *ds1 = getNthDNASequence(0);
	CuAssertStrEquals(tc, "http://example.com/ds1", getDNASequenceURI(ds1));
	CuAssertStrEquals(tc, "tccctatcagtgat", getNucleotides(ds1));
	// check pointers
	CuAssertPtrEquals(tc, ds1, getDNAComponentSequence(dc1));
}

void TestLoadedValid04(CuTest *tc) {
	// check overall numbers
	CuAssertIntEquals(tc, 4, getNumSBOLObjects());
	CuAssertIntEquals(tc, 2, getNumSBOLCompoundObjects());
	CuAssertIntEquals(tc, 1, getNumDNASequences());
	CuAssertIntEquals(tc, 1, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 2, getNumDNAComponents());
	CuAssertIntEquals(tc, 0, getNumCollections());
	// check sequences
	DNASequence *ds1 = getDNASequence("http://example.com/ds1");
	CuAssertStrEquals(tc, "tccctatcagtgat", getNucleotides(ds1));
	// check components
	DNAComponent *dc1 = getDNAComponent("http://example.com/dc1");
	DNAComponent *dc2 = getDNAComponent("http://example.com/dc2");
	CuAssertStrEquals(tc, "DC1", getDNAComponentDisplayID(dc1));
	CuAssertStrEquals(tc, "DC2", getDNAComponentDisplayID(dc2));
	CuAssertStrEquals(tc, "DnaComponent1", getDNAComponentName(dc1));
	CuAssertStrEquals(tc, "DnaComponent2", getDNAComponentName(dc2));
	CuAssertStrEquals(tc, "DnaComponent with one sequence annotation", getDNAComponentDescription(dc1));
	CuAssertStrEquals(tc, "Another DNA component", getDNAComponentDescription(dc2));
	CuAssertIntEquals(tc, 1, getNumSequenceAnnotationsIn(dc1));
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotationsIn(dc2));
	CuAssertIntEquals(tc, 0, getNumCollectionsFor(dc1));
	CuAssertIntEquals(tc, 0, getNumCollectionsFor(dc2));
	// check annotations
	SequenceAnnotation *sa1 = getSequenceAnnotation("http://example.com/sa1");
	CuAssertIntEquals(tc, -1, getBioStart(sa1));
	CuAssertIntEquals(tc, -1, getBioEnd(sa1));
	CuAssertIntEquals(tc, 1, getStrandPolarity(sa1));
	// check pointers
	CuAssertPtrEquals(tc, ds1, getDNAComponentSequence(dc1));
	CuAssertPtrEquals(tc, NULL, getDNAComponentSequence(dc2));
	CuAssertPtrEquals(tc, dc2, getSubComponent(sa1));
	CuAssertPtrEquals(tc, sa1, getNthSequenceAnnotationIn(dc1, 0));
	CuAssertPtrEquals(tc, dc2, getSubComponent(sa1));
}

#define NUM_VALID_EXAMPLES 4

// a list of all the valid example filenames
// so they can be retrieved by index in a loop
static char *VALID_EXAMPLE_FILENAMES[NUM_VALID_EXAMPLES] = {
	VALID_EXAMPLES_DIR "/valid01_dna_component_empty.xml",
	VALID_EXAMPLES_DIR "/valid02_dna_component.xml",
	VALID_EXAMPLES_DIR "/valid03_dna_component_sequence.xml",
	VALID_EXAMPLES_DIR "/valid04_dna_component_annotation.xml"
};

// a list of all the TestLoadedValid* functions
// so they can be retrieved by index in a loop
static void (*TEST_LOADED_FUNCTIONS[NUM_VALID_EXAMPLES])() = {
	TestLoadedValid01,
	TestLoadedValid02,
	TestLoadedValid03,
	TestLoadedValid04
};

// The main test function. It loads the example files
// and checks that each was interpreted correctly.
void TestReadValidExamples(CuTest *tc) {
	int n;
	for (n=0; n<NUM_VALID_EXAMPLES; n++) {
		cleanupSBOLCore();
		TestNothingLoaded(tc);
 		printf("reading %s\n", VALID_EXAMPLE_FILENAMES[n]);
		readSBOLCore(VALID_EXAMPLE_FILENAMES[n]);
		#if SBOL_TEST_DEBUG
		printSBOLCore();
		#endif
		TEST_LOADED_FUNCTIONS[n](tc);
		cleanupSBOLCore();
	}
}

CuSuite* ReaderGetSuite() {
	CuSuite* readerTests = CuSuiteNew();
	SUITE_ADD_TEST(readerTests, TestReadValidExamples);
	return readerTests;
}
