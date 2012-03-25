#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

// TODO learn macros to de-duplicate these

// a list of all the valid example filenames
// so they can be retrieved by index in a loop
char *VALID_EXAMPLE_FILENAMES[13] = {
	VALID_EXAMPLES_DIR "valid01_dna_component_empty.xml",
	VALID_EXAMPLES_DIR "valid02_dna_component.xml",
	VALID_EXAMPLES_DIR "valid03_dna_component_sequence.xml",
	VALID_EXAMPLES_DIR "valid04_dna_component_annotation.xml",
	VALID_EXAMPLES_DIR "valid05_dna_component_so_type.xml",
	VALID_EXAMPLES_DIR "valid06_dna_component_so_types.xml",
	VALID_EXAMPLES_DIR "valid07_dna_component_extension.xml",
	VALID_EXAMPLES_DIR "valid08_dna_component_detailed.xml",
	VALID_EXAMPLES_DIR "valid09_dna_component_multiple.xml",
	VALID_EXAMPLES_DIR "valid10_collection_empty.xml",
	VALID_EXAMPLES_DIR "valid11_collection_components.xml",
	VALID_EXAMPLES_DIR "valid12_collection_multiple.xml",
	VALID_EXAMPLES_DIR "valid13_dna_sequence.xml"
};

// a list of all the output filenames
// so they can be retrieved by index in a loop
char *TEST_OUTPUT_FILENAMES[13] = {
	TEST_OUTPUT_DIR "valid01_dna_component_empty.xml",
	TEST_OUTPUT_DIR "valid02_dna_component.xml",
	TEST_OUTPUT_DIR "valid03_dna_component_sequence.xml",
	TEST_OUTPUT_DIR "valid04_dna_component_annotation.xml",
	TEST_OUTPUT_DIR "valid05_dna_component_so_type.xml",
	TEST_OUTPUT_DIR "valid06_dna_component_so_types.xml",
	TEST_OUTPUT_DIR "valid07_dna_component_extension.xml",
	TEST_OUTPUT_DIR "valid08_dna_component_detailed.xml",
	TEST_OUTPUT_DIR "valid09_dna_component_multiple.xml",
	TEST_OUTPUT_DIR "valid10_collection_empty.xml",
	TEST_OUTPUT_DIR "valid11_collection_components.xml",
	TEST_OUTPUT_DIR "valid12_collection_multiple.xml",
	TEST_OUTPUT_DIR "valid13_dna_sequence.xml"
};

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

void TestLoadedValid05(CuTest *tc) {
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
	// dc1 should have an rdf:type node too, which libSBOLc ignores
	CuAssertStrEquals(tc, "DC1", getDNAComponentDisplayID(dc1));
	CuAssertStrEquals(tc, "DnaComponent1", getDNAComponentName(dc1));
	CuAssertStrEquals(tc, "A DnaComponent can optionally use multiple types from Sequence Ontology",
						getDNAComponentDescription(dc1));
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotationsIn(dc1));
	CuAssertIntEquals(tc, 0, getNumCollectionsFor(dc1));
	// check ds1
	DNASequence *ds1 = getNthDNASequence(0);
	CuAssertStrEquals(tc, "http://example.com/ds1", getDNASequenceURI(ds1));
	CuAssertStrEquals(tc, "tccctatcagtgat", getNucleotides(ds1));
	// check pointers
	CuAssertPtrEquals(tc, ds1, getDNAComponentSequence(dc1));
}

void TestLoadedValid06(CuTest *tc) {
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
	// dc1 should have two rdf:type nodes, which libSBOLc ignores
	CuAssertStrEquals(tc, "DC1", getDNAComponentDisplayID(dc1));
	CuAssertStrEquals(tc, "DnaComponent1", getDNAComponentName(dc1));
	CuAssertStrEquals(tc, "A DnaComponent can optionally use a type from Sequence Ontology",
						getDNAComponentDescription(dc1));
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotationsIn(dc1));
	CuAssertIntEquals(tc, 0, getNumCollectionsFor(dc1));
	// check ds1
	DNASequence *ds1 = getNthDNASequence(0);
	CuAssertStrEquals(tc, "http://example.com/ds1", getDNASequenceURI(ds1));
	CuAssertStrEquals(tc, "tccctatcagtgat", getNucleotides(ds1));
	// check pointers
	CuAssertPtrEquals(tc, ds1, getDNAComponentSequence(dc1));
}

void TestLoadedValid07(CuTest *tc) {
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
	// dc1 should have a dc:creator node that libSBOLc ignores
	CuAssertStrEquals(tc, "DC1", getDNAComponentDisplayID(dc1));
	CuAssertStrEquals(tc, "DC2", getDNAComponentDisplayID(dc2));
	CuAssertStrEquals(tc, "DnaComponent1", getDNAComponentName(dc1));
	CuAssertStrEquals(tc, "DnaComponent2", getDNAComponentName(dc2));
	CuAssertStrEquals(tc, "It is valid to have additional elements in any SBOL element as long as they appear after \n\t\tthe elements defined in SBOL core model. This example adds dc:creator annotations to SBOL elements", getDNAComponentDescription(dc1));
	CuAssertStrEquals(tc, "Another DNA component", getDNAComponentDescription(dc2));
	CuAssertIntEquals(tc, 1, getNumSequenceAnnotationsIn(dc1));
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotationsIn(dc2));
	CuAssertIntEquals(tc, 0, getNumCollectionsFor(dc1));
	CuAssertIntEquals(tc, 0, getNumCollectionsFor(dc2));
	// check annotations
	SequenceAnnotation *sa1 = getSequenceAnnotation("http://example.com/sa1");
	// sa1 should have a dc:creator node that libSBOLc ignores
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

void TestLoadedValid08(CuTest *tc) {
	// check overall numbers
	CuAssertIntEquals(tc, 2, getNumDNASequences());
	CuAssertIntEquals(tc, 3, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 4, getNumDNAComponents());
	CuAssertIntEquals(tc, 0, getNumCollections());
	CuAssertIntEquals(tc, 9, getNumSBOLObjects());
	CuAssertIntEquals(tc, 4, getNumSBOLCompoundObjects());
	// components
	DNAComponent *dc1 = getDNAComponent("http://example.com/dc1");
	DNAComponent *dc2 = getDNAComponent("http://example.com/dc2");
	DNAComponent *dc3 = getDNAComponent("http://example.com/dc3");
	DNAComponent *dc4 = getDNAComponent("http://example.com/dc4");
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
	// sequences
	DNASequence *ds1 = getDNASequence("http://example.com/ds1");
	DNASequence *ds2 = getDNASequence("http://example.com/ds2");
	CuAssertStrEquals(tc, "tccctatcagtgat", getNucleotides(ds1));
	CuAssertStrEquals(tc, "tc", getNucleotides(ds2));
	CuAssertPtrEquals(tc, ds1, getDNAComponentSequence(dc1));
	CuAssertPtrEquals(tc, ds2, getDNAComponentSequence(dc2));
	// annotations
	SequenceAnnotation *sa1 = getSequenceAnnotation("http://example.com/sa1");
	SequenceAnnotation *sa2 = getSequenceAnnotation("http://example.com/sa2");
	SequenceAnnotation *sa3 = getSequenceAnnotation("http://example.com/sa3");
	CuAssertIntEquals(tc, 3, getNumSequenceAnnotationsIn(dc1));
	CuAssertIntEquals(tc, 1, annotates(sa1, dc1));
	CuAssertIntEquals(tc, 1, annotates(sa2, dc1));
	CuAssertIntEquals(tc, 1, annotates(sa3, dc1));
	CuAssertIntEquals(tc, 1, getBioStart(sa1));
	CuAssertIntEquals(tc, 3, getBioStart(sa2));
	CuAssertIntEquals(tc, 2, getBioEnd(sa1));
	CuAssertIntEquals(tc, 5, getBioEnd(sa2));
	CuAssertPtrEquals(tc, dc2, getSubComponent(sa1));
	CuAssertPtrEquals(tc, dc3, getSubComponent(sa2));
	CuAssertPtrEquals(tc, dc4, getSubComponent(sa3));
	CuAssertIntEquals(tc, 1, precedes(sa1, sa2));
	CuAssertIntEquals(tc, 1, precedes(sa1, sa3));
}

void TestLoadedValid09(CuTest *tc) {
	// overall numbers
	CuAssertIntEquals(tc, 1, getNumDNASequences());
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 2, getNumDNAComponents());
	CuAssertIntEquals(tc, 0, getNumCollections());
	CuAssertIntEquals(tc, 3, getNumSBOLObjects());
	CuAssertIntEquals(tc, 2, getNumSBOLCompoundObjects());
	// components
	DNAComponent *dc1 = getDNAComponent("http://example.com/dc1");
	DNAComponent *dc2 = getDNAComponent("http://example.com/dc2");
	CuAssertStrEquals(tc, "DC1", getDNAComponentDisplayID(dc1));
	CuAssertStrEquals(tc, "DC2", getDNAComponentDisplayID(dc2));
	CuAssertStrEquals(tc, "DnaComponent1", getDNAComponentName(dc1));
	CuAssertStrEquals(tc, "DnaComponent2", getDNAComponentName(dc2));
	CuAssertStrEquals(tc, "Multiple DNA components at the top level are allowed even without a collection",
						getDNAComponentDescription(dc1));
	// sequence
	DNASequence *ds1 = getDNASequence("http://example.com/ds1");
	CuAssertStrEquals(tc, "tccctatcagtgat", getNucleotides(ds1));
	CuAssertPtrEquals(tc, ds1, getDNAComponentSequence(dc1));
}

void TestLoadedValid10(CuTest *tc) {}
void TestLoadedValid11(CuTest *tc) {}
void TestLoadedValid12(CuTest *tc) {}
void TestLoadedValid13(CuTest *tc) {}

// TODO learn macro to de-duplicate this

// a list of all the TestLoadedValid* functions
// so they can be retrieved by index in a loop
void (*TEST_LOADED_FUNCTIONS[13])() = {
	TestLoadedValid01,
	TestLoadedValid02,
	TestLoadedValid03,
	TestLoadedValid04,
	TestLoadedValid05,
	TestLoadedValid06,
	TestLoadedValid07,
	TestLoadedValid08,
	TestLoadedValid09,
	TestLoadedValid10,
	TestLoadedValid11,
	TestLoadedValid12,
	TestLoadedValid13
};
