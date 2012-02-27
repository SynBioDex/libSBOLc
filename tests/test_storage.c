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

void TestNumComponents(CuTest* tc) {
	char* id;
	DNAComponent* com;
	int num;
	for (num=0; num<NUM_FAST_TESTS; num++) {
		CuAssertIntEquals(tc, num, getNumDNAComponents());
		id = randomString();
		com = createComponent(id);
		registerComponent(com);
		CuAssertIntEquals(tc, num+1, getNumDNAComponents());
	}
	for (; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumDNAComponents());
		com = getNthDNAComponent(0);
		removeComponent(com);
		CuAssertIntEquals(tc, num-1, getNumDNAComponents());
	}
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
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

void TestNumAnnotations(CuTest* tc) {
	char* id;
	SequenceAnnotation* ann;
	int num;
	for (num=0; num<NUM_FAST_TESTS; num++) {
		CuAssertIntEquals(tc, num, getNumSequenceAnnotations());
		id = randomString();
		ann = createSequenceAnnotation(id);
		registerSequenceAnnotation(ann);
		CuAssertIntEquals(tc, num+1, getNumSequenceAnnotations());
	}
	for (; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumSequenceAnnotations());
		ann = getNthSequenceAnnotation(0);
		removeAnnotation(ann);
		CuAssertIntEquals(tc, num-1, getNumSequenceAnnotations());
	}
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
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

void TestNumCollections(CuTest* tc) {
	char* id;
	Collection* col;
	int num;
	for (num=0; num<NUM_FAST_TESTS; num++) {
		CuAssertIntEquals(tc, num, getNumCollections());
		id = randomString();
		col = createCollection(id);
		registerCollection(col);
		CuAssertIntEquals(tc, num+1, getNumCollections());
	}
	for (; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumCollections());
		col = getNthCollection(0);
		removeCollection(col);
		CuAssertIntEquals(tc, num-1, getNumCollections());
	}
	CuAssertIntEquals(tc, 0, getNumCollections());
}

CuSuite* StorageGetSuite() {
	CuSuite* storageTests = CuSuiteNew();
	SUITE_ADD_TEST(storageTests, TestSingleComponent);
	SUITE_ADD_TEST(storageTests, TestNumComponents);
	SUITE_ADD_TEST(storageTests, TestSingleAnnotation);
	SUITE_ADD_TEST(storageTests, TestNumAnnotations);
	SUITE_ADD_TEST(storageTests, TestSingleCollection);
	SUITE_ADD_TEST(storageTests, TestNumCollections);
	return storageTests;
}
