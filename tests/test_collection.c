#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "document.h"
#include "collection.h"

#define NUM_FAST_TESTS 10000

void TestCreateEmptyCollection(CuTest* tc) {
	Document* doc = createDocument();
	
	Collection* col = createCollection(doc, "");
	CuAssertStrEquals(tc, "", getCollectionURI(col));
	deleteCollection(col);

	deleteDocument(doc);
}

void TestCreateNullCollection(CuTest* tc) {
	Document* doc = createDocument();
	
	Collection* col = createCollection(doc, NULL);
	CuAssertStrEquals(tc, NULL, getCollectionURI(col));
	deleteCollection(col);
	
	deleteDocument(doc);
}

void TestCreateRandomCollection(CuTest* tc) {
	Document* doc = createDocument();
	
	char* uri;
	Collection* col;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		uri = randomUniqueURI(doc);
		col = createCollection(doc, uri);
		CuAssertStrEquals(tc, uri,  getCollectionURI(col));
		CuAssertStrEquals(tc, NULL, getCollectionDisplayID(col));
		CuAssertStrEquals(tc, NULL, getCollectionName(col));
		CuAssertStrEquals(tc, NULL, getCollectionDescription(col));
		CuAssertIntEquals(tc, 0,    getNumDNAComponentsIn(col));
		deleteCollection(col);
	}
	
	deleteDocument(doc);
}

void TestEmptyCollectionProperties(CuTest* tc) {
	Document* doc = createDocument();

	Collection* col = createCollection(doc, "");
	setCollectionName(col, "");
	setCollectionDescription(col, "");
	CuAssertStrEquals(tc, "", getCollectionURI(col));
	CuAssertStrEquals(tc, "", getCollectionName(col));
	CuAssertStrEquals(tc, "", getCollectionDescription(col));
	deleteCollection(col);

	deleteDocument(doc);
}

void TestNullCollectionProperties(CuTest* tc) {
	Document* doc = createDocument();
	
	Collection* col = createCollection(doc, NULL);
	setCollectionName(col, NULL);
	setCollectionDescription(col, NULL);
	CuAssertStrEquals(tc, NULL, getCollectionURI(col));
	CuAssertStrEquals(tc, NULL, getCollectionName(col));
	CuAssertStrEquals(tc, NULL, getCollectionDescription(col));
	deleteCollection(col);
	
	deleteDocument(doc);
}

void TestRandomCollectionProperties(CuTest* tc) {
	Document* doc = createDocument();
	
	char* uri;
	char* name;
	char* descr;
	Collection* col;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		uri   = randomUniqueURI(doc);
		name  = randomString();
		descr = randomString();
		col = createCollection(doc, uri);
		setCollectionName(col, name);
		setCollectionDescription(col, descr);
		CuAssertStrEquals(tc, uri,   getCollectionURI(col));
		CuAssertStrEquals(tc, name,  getCollectionName(col));
		CuAssertStrEquals(tc, descr, getCollectionDescription(col));
		deleteCollection(col);
	}
	
	deleteDocument(doc);
}

void PrintCollectionTestInfo() {
	printf("testing collections\n");
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
