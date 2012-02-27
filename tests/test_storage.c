#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "storage.h"
#include "component.h"
#include "annotation.h"
#include "collection.h"

#define NUM_FAST_TESTS 10000

void TestSingleComponent(CuTest* tc) {
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
	DNAComponent* com = createComponent("one");
	registerComponent(com);
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	CuAssertPtrEquals(tc, com, getNthDNAComponent(0));
	CuAssertIntEquals(tc, 1, isComponentID("one"));
	CuAssertIntEquals(tc, 1, isComponentPtr(com));
	removeComponent(com);
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
	CuAssertIntEquals(tc, 0, isComponentID("one"));
	CuAssertIntEquals(tc, 0, isComponentPtr(com));
}

void TestSingleAnnotation(CuTest* tc) {
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	SequenceAnnotation* ann = createSequenceAnnotation("one");
	registerSequenceAnnotation(ann);
	CuAssertIntEquals(tc, 1, getNumSequenceAnnotations());
	CuAssertPtrEquals(tc, ann, getNthSequenceAnnotation(0));
	CuAssertIntEquals(tc, 1, isSequenceAnnotationID("one"));
	CuAssertIntEquals(tc, 1, isAnnotationPtr(ann));
	removeAnnotation(ann);
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 0, isSequenceAnnotationID("one"));
	CuAssertIntEquals(tc, 0, isAnnotationPtr(ann));
}

void TestSingleCollection(CuTest* tc) {
	CuAssertIntEquals(tc, 0, getNumCollections());
	Collection* col = createCollection("one");
	registerCollection(col);
	CuAssertIntEquals(tc, 1, getNumCollections());
	CuAssertPtrEquals(tc, col, getNthCollection(0));
	CuAssertIntEquals(tc, 1, isCollectionID("one"));
	CuAssertIntEquals(tc, 1, isCollectionPtr(col));
	removeCollection(col);
	CuAssertIntEquals(tc, 0, getNumCollections());
	CuAssertIntEquals(tc, 0, isCollectionID("one"));
	CuAssertIntEquals(tc, 0, isCollectionPtr(col));
}

CuSuite* StorageGetSuite() {
	CuSuite* storageTests = CuSuiteNew();
	SUITE_ADD_TEST(storageTests, TestSingleComponent);
	SUITE_ADD_TEST(storageTests, TestSingleAnnotation);
	SUITE_ADD_TEST(storageTests, TestSingleCollection);
	return storageTests;
}
