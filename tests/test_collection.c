#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "collection.h"

#define NUM_FAST_TESTS 100000

void TestCreateEmptyCollection(CuTest* tc) {
	Collection* col = createCollection("");
	CuAssertStrEquals(tc, col->id, "");
}

void TestCreateNullCollection(CuTest* tc) {
	Collection* col = createCollection(NULL);
	CuAssertStrEquals(tc, NULL, col->id);
}

void TestCreateRandomCollection(CuTest* tc) {
	char* id;
	Collection* col;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		id = randomString();
		col = createCollection(id);
		CuAssertStrEquals(tc, id,   col->id);
		CuAssertStrEquals(tc, NULL, col->name);
		CuAssertStrEquals(tc, NULL, col->description);
		CuAssertIntEquals(tc, 0,    col->numComponents);
		CuAssertIntEquals(tc, 0,    col->numCollections);
		CuAssertPtrEquals(tc, NULL, col->components);
		CuAssertPtrEquals(tc, NULL, col->collections);
		deleteCollection(col);
	}
}

int main(void) {
	// seed with current time
	// should only be done once
	srand( time(NULL) );
	
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestCreateEmptyCollection);
	SUITE_ADD_TEST(suite, TestCreateNullCollection);
	SUITE_ADD_TEST(suite, TestCreateRandomCollection);
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}
