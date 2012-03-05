#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sequenceannotation.h"

#define NUM_FAST_TESTS 10000
#define NUM_SLOW_TESTS  1000

void TestCreateSequenceAnnotation(CuTest* tc) {
	cleanupSequenceAnnotations();
	char* id;
	SequenceAnnotation* ann;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		id  = randomString();
		ann = createSequenceAnnotation(id);
		CuAssertIntEquals(tc, 1, getNumSequenceAnnotations());
		CuAssertStrEquals(tc, id, getSequenceAnnotationID(ann));
		CuAssertIntEquals(tc, 0, ann->genbankStart);
		CuAssertIntEquals(tc, 0, ann->genbankEnd);
		CuAssertIntEquals(tc, 0, getNumPrecedes(ann));
		deleteSequenceAnnotation(ann);
		CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	}
}

// TODO this leaks 1000 annotations for some reason
void TestPrecedes(CuTest* tc) {
	cleanupSequenceAnnotations();
	int index;
	int numDownstream;
	size_t memory;
	SequenceAnnotation* upstream;
	SequenceAnnotation** downstream;
	
	// create the main annotation to test
	upstream = createSequenceAnnotation( randomString() );
	
	// and also some others
	numDownstream = NUM_SLOW_TESTS;
	memory = numDownstream * sizeof(SequenceAnnotation*);
	downstream = (SequenceAnnotation**)malloc(memory);
	for (index=0; index<numDownstream; index++)
		downstream[index] = createSequenceAnnotation( randomString() );
	
	// restrict the main one to coming before each of the others
	for (index=0; index<numDownstream; index++) {
		// check that numPrecedes increments as expected
		CuAssertIntEquals(tc, index, getNumPrecedes(upstream));
		addPrecedesRelationship(upstream, downstream[index]);
		CuAssertIntEquals(tc, index+1, getNumPrecedes(upstream));
		
		// check that precedes array holds the expected values
		SequenceAnnotation* expected = downstream[index];
		SequenceAnnotation* actual = getNthPrecedes(upstream, index);
		CuAssertPtrEquals(tc, expected, actual);
	}
}

CuSuite* SequenceAnnotationGetSuite() {
	CuSuite* sequenceAnnotationTests = CuSuiteNew();
	SUITE_ADD_TEST(sequenceAnnotationTests, TestCreateSequenceAnnotation);
	SUITE_ADD_TEST(sequenceAnnotationTests, TestPrecedes);
	return sequenceAnnotationTests;
}
