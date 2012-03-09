#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CuTest.h"
#include "utilities.h"
#include "genericarray.h"
#include "dnacomponent.h"
#include "sequenceannotation.h"
#include "collection.h"

#define NUM_FAST_TESTS 10000
#define NUM_SLOW_TESTS  1000

void TestSingleDNAComponent(CuTest* tc) {
	cleanupDNAComponents();
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
	DNAComponent* com = createDNAComponent("one");
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
	CuAssertPtrEquals(tc, com, getNthDNAComponent(0));
	CuAssertIntEquals(tc, 1, isDNAComponentID("one"));
	CuAssertIntEquals(tc, 1, isDNAComponentPtr(com));
	deleteDNAComponent(com);
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
	CuAssertIntEquals(tc, 0, isDNAComponentID("one"));
	CuAssertIntEquals(tc, 0, isDNAComponentPtr(com));
}

void TestNumDNAComponents(CuTest* tc) {
	cleanupDNAComponents();
	char* id;
	DNAComponent* com;
	int num;
	for (num=0; num<NUM_FAST_TESTS; num++) {
		CuAssertIntEquals(tc, num, getNumDNAComponents());
		id = randomString();
		com = createDNAComponent(id);
		CuAssertIntEquals(tc, num+1, getNumDNAComponents());
	}
	for (; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumDNAComponents());
		com = getNthDNAComponent(0);
		deleteDNAComponent(com);
		CuAssertIntEquals(tc, num-1, getNumDNAComponents());
	}
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
}

void TestDNAComponentIndexing(CuTest* tc) {
	cleanupDNAComponents();
	char* id;
	DNAComponent* com;
	int num;
	for (num=0; num<NUM_SLOW_TESTS; num++) {
		id = randomString();
		while (isDNAComponentID(id))
			id = randomString();
		com = createDNAComponent(id);
	}
	int index;
	for (num=NUM_SLOW_TESTS; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumDNAComponents());
		index = randomNumber(num);
		com = getNthDNAComponent(index);
		// copy id (because it will be destroyed)
		id = getDNAComponentID(com);
		CuAssertIntEquals(tc, 1, isDNAComponentPtr(com));
		CuAssertIntEquals(tc, 1, isDNAComponentID(id));
		deleteDNAComponent(com);
		CuAssertIntEquals(tc, num-1, getNumDNAComponents());
		CuAssertIntEquals(tc, 0, isDNAComponentPtr(com));
		CuAssertIntEquals(tc, 0, isDNAComponentID(id));
	}
}

void TestSingleAnnotation(CuTest* tc) {
	cleanupSequenceAnnotations();
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	SequenceAnnotation* ann = createSequenceAnnotation("one");
	CuAssertIntEquals(tc, 1, getNumSequenceAnnotations());
	CuAssertPtrEquals(tc, ann, getNthSequenceAnnotation(0));
	CuAssertIntEquals(tc, 1, isSequenceAnnotationID("one"));
	CuAssertIntEquals(tc, 1, isAnnotationPtr(ann));
	deleteSequenceAnnotation(ann);
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	CuAssertIntEquals(tc, 0, isSequenceAnnotationID("one"));
	CuAssertIntEquals(tc, 0, isAnnotationPtr(ann));
}

void TestNumAnnotations(CuTest* tc) {
	cleanupSequenceAnnotations();
	char* id;
	SequenceAnnotation* ann;
	int num;
	for (num=0; num<NUM_FAST_TESTS; num++) {
		CuAssertIntEquals(tc, num, getNumSequenceAnnotations());
		id = randomString();
		ann = createSequenceAnnotation(id);
		CuAssertIntEquals(tc, num+1, getNumSequenceAnnotations());
	}
	for (; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumSequenceAnnotations());
		ann = getNthSequenceAnnotation(0);
		deleteSequenceAnnotation(ann);
		CuAssertIntEquals(tc, num-1, getNumSequenceAnnotations());
	}
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
}

void TestAnnotationIndexing(CuTest* tc) {
	cleanupSequenceAnnotations();
	char* id;
	SequenceAnnotation* ann;
	int num;
	for (num=0; num<NUM_SLOW_TESTS; num++) {
		id = randomString();
		// avoid duplicates
		while (isSequenceAnnotationID(id))
			id = randomString();
		ann = createSequenceAnnotation(id);
	}
	int index;
	for (num=NUM_SLOW_TESTS; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumSequenceAnnotations());
		index = randomNumber(num);
		ann = getNthSequenceAnnotation(index);
		// copy id (because it will be destroyed)
		id = getSequenceAnnotationID(ann);
		CuAssertIntEquals(tc, 1, isAnnotationPtr(ann));
		CuAssertIntEquals(tc, 1, isSequenceAnnotationID(id));
		deleteSequenceAnnotation(ann);
		CuAssertIntEquals(tc, num-1, getNumSequenceAnnotations());
		CuAssertIntEquals(tc, 0, isAnnotationPtr(ann));
		CuAssertIntEquals(tc, 0, isSequenceAnnotationID(id));
	}
}

void TestcleanupSequenceAnnotations(CuTest* tc) {
	cleanupSequenceAnnotations();
	int num;
	for (num=0; num<NUM_FAST_TESTS; num++)
		createSequenceAnnotation( randomString() );
	CuAssertIntEquals(tc, NUM_FAST_TESTS, getNumSequenceAnnotations());
	cleanupSequenceAnnotations();
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
}

void TestSingleCollection(CuTest* tc) {
	cleanupCollections();
	CuAssertIntEquals(tc, 0, getNumCollections());
	Collection* col = createCollection("one");
	CuAssertIntEquals(tc, 1, getNumCollections());
	CuAssertPtrEquals(tc, col, getNthCollection(0));
	CuAssertIntEquals(tc, 1, isCollectionID("one"));
	CuAssertIntEquals(tc, 1, isCollectionPtr(col));
	deleteCollection(col);
	CuAssertIntEquals(tc, 0, getNumCollections());
	CuAssertIntEquals(tc, 0, isCollectionID("one"));
	CuAssertIntEquals(tc, 0, isCollectionPtr(col));
}

void TestNumCollections(CuTest* tc) {
	cleanupCollections();
	char* id;
	Collection* col;
	int num;
	for (num=0; num<NUM_FAST_TESTS; num++) {
		CuAssertIntEquals(tc, num, getNumCollections());
		id = randomString();
		col = createCollection(id);
		CuAssertIntEquals(tc, num+1, getNumCollections());
	}
	for (; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumCollections());
		col = getNthCollection(0);
		deleteCollection(col);
		CuAssertIntEquals(tc, num-1, getNumCollections());
	}
	CuAssertIntEquals(tc, 0, getNumCollections());
}

void TestCollectionIndexing(CuTest* tc) {
	cleanupCollections();
	char* id;
	Collection* col;
	int num;
	for (num=0; num<NUM_SLOW_TESTS; num++) {
		id = randomString();
		// avoid duplicates
		while (isCollectionID(id))
			id = randomString();
		col = createCollection(id);
	}
	int index;
	for (num=NUM_SLOW_TESTS; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumCollections());
		index = randomNumber(num);
		col = getNthCollection(index);
		id = getCollectionID(col); // copy id (because it will be destroyed)
		CuAssertIntEquals(tc, 1, isCollectionPtr(col));
		CuAssertIntEquals(tc, 1, isCollectionID(id));
		deleteCollection(col);
		CuAssertIntEquals(tc, num-1, getNumCollections());
		CuAssertIntEquals(tc, 0, isCollectionPtr(col));
		CuAssertIntEquals(tc, 0, isCollectionID(id));
	}	
}

void PrintGenericArrayTestInfo() {
	printf("testing core/genericarray\n");
}

CuSuite* GenericArrayGetSuite() {
	CuSuite* genericArrayTests = CuSuiteNew();
	SUITE_ADD_TEST(genericArrayTests, PrintGenericArrayTestInfo);
	SUITE_ADD_TEST(genericArrayTests, TestSingleDNAComponent);
	SUITE_ADD_TEST(genericArrayTests, TestNumDNAComponents);
	SUITE_ADD_TEST(genericArrayTests, TestDNAComponentIndexing);
	SUITE_ADD_TEST(genericArrayTests, TestSingleAnnotation);
	SUITE_ADD_TEST(genericArrayTests, TestNumAnnotations);
	SUITE_ADD_TEST(genericArrayTests, TestAnnotationIndexing);
	SUITE_ADD_TEST(genericArrayTests, TestcleanupSequenceAnnotations);
	SUITE_ADD_TEST(genericArrayTests, TestSingleCollection);
	SUITE_ADD_TEST(genericArrayTests, TestNumCollections);
	SUITE_ADD_TEST(genericArrayTests, TestCollectionIndexing);
	return genericArrayTests;
}
