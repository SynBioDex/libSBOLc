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

CuSuite* CollectionGetSuite() {
	CuSuite* collectionTests = CuSuiteNew();
	SUITE_ADD_TEST(collectionTests, TestCreateEmptyCollection);
	SUITE_ADD_TEST(collectionTests, TestCreateEmptyCollection);
	SUITE_ADD_TEST(collectionTests, TestCreateRandomCollection);
	return collectionTests;
}
