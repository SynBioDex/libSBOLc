#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "collection.h"

#define NUM_FAST_TESTS 10000

void TestCreateEmptyCollection(CuTest* tc) {
	Collection* col = createCollection("");
	CuAssertStrEquals(tc, "", getCollectionURI(col));
	deleteCollection(col);
}

void TestCreateNullCollection(CuTest* tc) {
	Collection* col = createCollection(NULL);
	CuAssertStrEquals(tc, NULL, getCollectionURI(col));
	deleteCollection(col);
}

void TestCreateRandomCollection(CuTest* tc) {
	char* uri;
	Collection* col;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		uri = randomUniqueURI();
		col = createCollection(uri);
		CuAssertStrEquals(tc, uri,   getCollectionURI(col));
		CuAssertStrEquals(tc, NULL, getCollectionName(col));
		CuAssertStrEquals(tc, NULL, getCollectionDescription(col));
		CuAssertIntEquals(tc, 0,    getNumDNAComponentsIn(col));
		CuAssertIntEquals(tc, 0,    getNumCollectionsIn(col));
		deleteCollection(col);
	}
}

void TestEmptyCollectionProperties(CuTest* tc) {
	Collection* col = createCollection("");
	setCollectionName(col, "");
	setCollectionDescription(col, "");
	CuAssertStrEquals(tc, "", getCollectionURI(col));
	CuAssertStrEquals(tc, "", getCollectionName(col));
	CuAssertStrEquals(tc, "", getCollectionDescription(col));
	deleteCollection(col);
}

void TestNullCollectionProperties(CuTest* tc) {
	Collection* col = createCollection(NULL);
	setCollectionName(col, NULL);
	setCollectionDescription(col, NULL);
	CuAssertStrEquals(tc, NULL, getCollectionURI(col));
	CuAssertStrEquals(tc, NULL, getCollectionName(col));
	CuAssertStrEquals(tc, NULL, getCollectionDescription(col));
	deleteCollection(col);
}

void TestRandomCollectionProperties(CuTest* tc) {
	char* uri;
	char* name;
	char* descr;
	Collection* col;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		uri   = randomUniqueURI();
		name  = randomString();
		descr = randomString();
		col = createCollection(uri);
		setCollectionName(col, name);
		setCollectionDescription(col, descr);
		CuAssertStrEquals(tc, uri,   getCollectionURI(col));
		CuAssertStrEquals(tc, name,  getCollectionName(col));
		CuAssertStrEquals(tc, descr, getCollectionDescription(col));
		deleteCollection(col);
	}
}

void PrintCollectionTestInfo() {
	printf("testing core/collection\n");
}

CuSuite* CollectionGetSuite() {
	CuSuite* collectionTests = CuSuiteNew();
	SUITE_ADD_TEST(collectionTests, PrintCollectionTestInfo);
	SUITE_ADD_TEST(collectionTests, TestCreateEmptyCollection);
	SUITE_ADD_TEST(collectionTests, TestCreateEmptyCollection);
	SUITE_ADD_TEST(collectionTests, TestCreateRandomCollection);
	SUITE_ADD_TEST(collectionTests, TestEmptyCollectionProperties);
	SUITE_ADD_TEST(collectionTests, TestNullCollectionProperties);
	SUITE_ADD_TEST(collectionTests, TestRandomCollectionProperties);
	return collectionTests;
}
