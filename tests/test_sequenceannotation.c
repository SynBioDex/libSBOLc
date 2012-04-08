#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "document.h"
#include "sequenceannotation.h"

#define NUM_FAST_TESTS 10000
#define NUM_SLOW_TESTS  1000

void TestCreateSequenceAnnotation(CuTest* tc) {
	Document* doc = createDocument();
	char* uri;
	SequenceAnnotation* ann;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		uri = randomUniqueURI(doc);
		ann = createSequenceAnnotation(doc, uri);
		CuAssertIntEquals(tc, 1, getNumSequenceAnnotations(doc));
		CuAssertStrEquals(tc, uri, getSequenceAnnotationURI(ann));
		CuAssertIntEquals(tc, -1, getSequenceAnnotationStart(ann));
		CuAssertIntEquals(tc, -1, getSequenceAnnotationEnd(ann));
		CuAssertIntEquals(tc, 0, getNumPrecedes(ann));
		deleteSequenceAnnotation(ann);
		CuAssertIntEquals(tc, 0, getNumSequenceAnnotations(doc));
	}
	deleteDocument(doc);
}

// TODO this leaks 1000 annotations for some reason
void TestPrecedes(CuTest* tc) {
	Document* doc = createDocument();
	int index;
	char* uri;
	SequenceAnnotation* upstream;
	SequenceAnnotation** downstream;
	
	// create the main annotation to test
	upstream = createSequenceAnnotation(doc, randomUniqueURI(doc));
	
	// and also some others
	downstream = malloc(NUM_SLOW_TESTS * sizeof(SequenceAnnotation*));
	for (index=0; index<NUM_SLOW_TESTS; index++) {
		uri = randomUniqueURI(doc);
		downstream[index] = createSequenceAnnotation(doc, uri);
	}
	
	// restrict the main one to coming before each of the others
	for (index=0; index<NUM_SLOW_TESTS; index++) {
		// check that numPrecedes increments as expected
		CuAssertIntEquals(tc, index, getNumPrecedes(upstream));
		addPrecedesRelationship(upstream, downstream[index]);
		CuAssertIntEquals(tc, index+1, getNumPrecedes(upstream));
		
		// check that precedes array holds the expected values
		SequenceAnnotation* expected = downstream[index];
		SequenceAnnotation* actual = getNthPrecedes(upstream, index);
		CuAssertPtrEquals(tc, expected, actual);
	}
	deleteDocument(doc);
}

void PrintSequenceAnnotationTestInfo() {
	printf("testing sequenceannotations\n");
}

CuSuite* SequenceAnnotationGetSuite() {
	CuSuite* sequenceAnnotationTests = CuSuiteNew();
	SUITE_ADD_TEST(sequenceAnnotationTests, PrintSequenceAnnotationTestInfo);
	SUITE_ADD_TEST(sequenceAnnotationTests, TestCreateSequenceAnnotation);
	SUITE_ADD_TEST(sequenceAnnotationTests, TestPrecedes);
	return sequenceAnnotationTests;
}
