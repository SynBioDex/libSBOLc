#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "collection.h"

#define NUM_FAST_TESTS 10000

void TestCreateEmptyCollection(CuTest* tc) {
	Collection* col = createCollection("");
	CuAssertStrEquals(tc, col->id, "");
	deleteCollection(col);
}

void TestCreateNullCollection(CuTest* tc) {
	Collection* col = createCollection(NULL);
	CuAssertStrEquals(tc, NULL, col->id);
	deleteCollection(col);
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

void TestEmptyCollectionProperties(CuTest* tc) {
	Collection* col = createCollection("");
	setCollectionName(col, "");
	setCollectionDescription(col, "");
	CuAssertStrEquals(tc, "", getCollectionID(col));
	CuAssertStrEquals(tc, "", getCollectionName(col));
	CuAssertStrEquals(tc, "", getCollectionDescription(col));
	deleteCollection(col);
}

void TestNullCollectionProperties(CuTest* tc) {
	Collection* col = createCollection(NULL);
	setCollectionName(col, NULL);
	setCollectionDescription(col, NULL);
	CuAssertStrEquals(tc, NULL, getCollectionID(col));
	CuAssertStrEquals(tc, NULL, getCollectionName(col));
	CuAssertStrEquals(tc, NULL, getCollectionDescription(col));
	deleteCollection(col);
}

void TestRandomCollectionProperties(CuTest* tc) {
	char* id;
	char* name;
	char* descr;
	Collection* col;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		id    = randomString();
		name  = randomString();
		descr = randomString();
		col = createCollection(id);
		setCollectionName(col, name);
		setCollectionDescription(col, descr);
		CuAssertStrEquals(tc, id,    getCollectionID(col));
		CuAssertStrEquals(tc, name,  getCollectionName(col));
		CuAssertStrEquals(tc, descr, getCollectionDescription(col));
		deleteCollection(col);
	}
}

CuSuite* CollectionGetSuite() {
	CuSuite* collectionTests = CuSuiteNew();
	SUITE_ADD_TEST(collectionTests, TestCreateEmptyCollection);
	SUITE_ADD_TEST(collectionTests, TestCreateEmptyCollection);
	SUITE_ADD_TEST(collectionTests, TestCreateRandomCollection);
	SUITE_ADD_TEST(collectionTests, TestEmptyCollectionProperties);
	SUITE_ADD_TEST(collectionTests, TestNullCollectionProperties);
	SUITE_ADD_TEST(collectionTests, TestRandomCollectionProperties);
	return collectionTests;
}
