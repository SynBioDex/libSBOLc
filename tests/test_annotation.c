#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "annotation.h"

#define NUM_FAST_TESTS 100000
#define NUM_SLOW_TESTS 	10000

void TestCreateSequenceAnnotation(CuTest* tc) {
	char* id;
	SequenceAnnotation* ann;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		id  = randomString();
		ann = createSequenceAnnotation(id);
		CuAssertStrEquals(tc, id, ann->id);
		CuAssertIntEquals(tc, 0, ann->genbankStart);
		CuAssertIntEquals(tc, 0, ann->genbankEnd);
		CuAssertIntEquals(tc, 0, ann->numPrecedes);
		deleteSequenceAnnotation(ann);
		// TODO test that deletion worked?
	}
}

void TestPrecedes(CuTest* tc) {
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

int main(void)
{
	// seed with current time
	// should only be done once
	srand( time(NULL) );
	
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestCreateSequenceAnnotation);
	SUITE_ADD_TEST(suite, TestPrecedes);
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}
