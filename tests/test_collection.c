#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "collection.h"

#define NUM_FAST_TESTS 100000

void TestCreateCollection(CuTest* tc) {
	char* id;
	Collection* col;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		id = randomString();
		col = createCollection(id);
		CuAssertStrEquals(tc, id, col->id);
		CuAssertStrEquals(tc, "", col->name);
		CuAssertStrEquals(tc, "", col->description);
		CuAssertIntEquals(tc, 0,  col->numComponents);
		CuAssertIntEquals(tc, 0,  col->numCollections);
		CuAssertPtrEquals(tc, col->components, NULL);
		CuAssertPtrEquals(tc, col->collections, NULL);
		deleteCollection(col);
	}
}

int main(void) {
	// seed with current time
	// should only be done once
	srand( time(NULL) );
	
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestCreateCollection);
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}
