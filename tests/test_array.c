#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CuTest.h"
#include "utilities.h"
#include "document.h"
#include "array.h"
#include "dnacomponent.h"
#include "sequenceannotation.h"
#include "collection.h"

#define NUM_FAST_TESTS 100
#define NUM_SLOW_TESTS  10

void TestSingleDNAComponent(CuTest* tc) {
	Document* doc = createDocument();
	CuAssertIntEquals(tc, 0, getNumDNAComponents(doc));
	DNAComponent* com = createDNAComponent(doc, "one");
	CuAssertIntEquals(tc, 1, getNumDNAComponents(doc));
	CuAssertPtrEquals(tc, com, getNthDNAComponent(doc, 0));
	CuAssertIntEquals(tc, 1, isDNAComponentURI(doc, "one"));
	CuAssertIntEquals(tc, 1, isDNAComponent(doc, com));
	deleteDNAComponent(com);
	CuAssertIntEquals(tc, 0, getNumDNAComponents(doc));
	CuAssertIntEquals(tc, 0, isDNAComponentURI(doc, "one"));
	CuAssertIntEquals(tc, 0, isDNAComponent(doc, com));
	deleteDocument(doc);
}

void TestNumDNAComponents(CuTest* tc) {
	Document* doc = createDocument();
	char* uri;
	DNAComponent* com;
	int num;
	for (num=0; num<NUM_FAST_TESTS; num++) {
		CuAssertIntEquals(tc, num, getNumDNAComponents(doc));
		uri = randomUniqueURI(doc);
		com = createDNAComponent(doc, uri);
		CuAssertIntEquals(tc, num+1, getNumDNAComponents(doc));
	}
	for (; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumDNAComponents(doc));
		com = getNthDNAComponent(doc, 0);
		deleteDNAComponent(com);
		CuAssertIntEquals(tc, num-1, getNumDNAComponents(doc));
	}
	CuAssertIntEquals(tc, 0, getNumDNAComponents(doc));
	deleteDocument(doc);
}

void TestDNAComponentIndexing(CuTest* tc) {
	Document* doc = createDocument();
	char* uri;
	DNAComponent* com;
	int num;
	for (num=0; num<NUM_SLOW_TESTS; num++) {
		uri = randomUniqueURI(doc);
		while (isDNAComponentURI(doc, uri))
			uri = randomUniqueURI(doc);
		com = createDNAComponent(doc, uri);
	}
	int index;
	for (num=NUM_SLOW_TESTS; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumDNAComponents(doc));
		index = randomNumber(num);
		com = getNthDNAComponent(doc, index);
		// copy uri (because it will be destroyed)
		uri = getDNAComponentURI(com);
		CuAssertIntEquals(tc, 1, isDNAComponent(doc, com));
		CuAssertIntEquals(tc, 1, isDNAComponentURI(doc, uri));
		deleteDNAComponent(com);
		CuAssertIntEquals(tc, num-1, getNumDNAComponents(doc));
		CuAssertIntEquals(tc, 0, isDNAComponent(doc, com));
		CuAssertIntEquals(tc, 0, isDNAComponentURI(doc, uri));
	}
	deleteDocument(doc);
}

void TestSingleAnnotation(CuTest* tc) {
	Document* doc = createDocument();
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations(doc));
	SequenceAnnotation* ann = createSequenceAnnotation(doc, "one");
	CuAssertIntEquals(tc, 1, getNumSequenceAnnotations(doc));
	CuAssertPtrEquals(tc, ann, getNthSequenceAnnotation(doc, 0));
	CuAssertIntEquals(tc, 1, isSequenceAnnotationURI(doc, "one"));
	CuAssertIntEquals(tc, 1, isSequenceAnnotation(doc, ann));
	deleteSequenceAnnotation(ann);
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations(doc));
	CuAssertIntEquals(tc, 0, isSequenceAnnotationURI(doc, "one"));
	CuAssertIntEquals(tc, 0, isSequenceAnnotation(doc, ann));
	deleteDocument(doc);
}

void TestNumAnnotations(CuTest* tc) {
	Document* doc = createDocument();
	char* uri;
	SequenceAnnotation* ann;
	int num;
	for (num=0; num<NUM_FAST_TESTS; num++) {
		CuAssertIntEquals(tc, num, getNumSequenceAnnotations(doc));
		uri = randomUniqueURI(doc);
		ann = createSequenceAnnotation(doc, uri);
		CuAssertIntEquals(tc, num+1, getNumSequenceAnnotations(doc));
	}
	for (; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumSequenceAnnotations(doc));
		ann = getNthSequenceAnnotation(doc, 0);
		deleteSequenceAnnotation(ann);
		CuAssertIntEquals(tc, num-1, getNumSequenceAnnotations(doc));
	}
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations(doc));
	deleteDocument(doc);
}

void TestAnnotationIndexing(CuTest* tc) {
	Document* doc = createDocument();
	char* uri;
	SequenceAnnotation* ann;
	int num;
	for (num=0; num<NUM_SLOW_TESTS; num++) {
		uri = randomUniqueURI(doc);
		// avoid duplicates
		while (isSequenceAnnotationURI(doc, uri))
			uri = randomUniqueURI(doc);
		ann = createSequenceAnnotation(doc, uri);
	}
	int index;
	for (num=NUM_SLOW_TESTS; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumSequenceAnnotations(doc));
		index = randomNumber(num);
		ann = getNthSequenceAnnotation(doc, index);
		// copy uri (because it will be destroyed)
		uri = getSequenceAnnotationURI(ann);
		CuAssertIntEquals(tc, 1, isSequenceAnnotation(doc, ann));
		CuAssertIntEquals(tc, 1, isSequenceAnnotationURI(doc, uri));
		deleteSequenceAnnotation(ann);
		CuAssertIntEquals(tc, num-1, getNumSequenceAnnotations(doc));
		CuAssertIntEquals(tc, 0, isSequenceAnnotation(doc, ann));
		CuAssertIntEquals(tc, 0, isSequenceAnnotationURI(doc, uri));
	}
	deleteDocument(doc);
}

void TestSingleCollection(CuTest* tc) {
	Document* doc = createDocument();
	CuAssertIntEquals(tc, 0, getNumCollections(doc));
	Collection* col = createCollection(doc, "one");
	CuAssertIntEquals(tc, 1, getNumCollections(doc));
	CuAssertPtrEquals(tc, col, getNthCollection(doc, 0));
	CuAssertIntEquals(tc, 1, isCollectionURI(doc, "one"));
	CuAssertIntEquals(tc, 1, isCollection(doc, col));
	deleteCollection(col);
	CuAssertIntEquals(tc, 0, getNumCollections(doc));
	CuAssertIntEquals(tc, 0, isCollectionURI(doc, "one"));
	CuAssertIntEquals(tc, 0, isCollection(doc, col));
	deleteDocument(doc);
}

void TestNumCollections(CuTest* tc) {
	Document* doc = createDocument();
	char* uri;
	Collection* col;
	int num;
	for (num=0; num<NUM_FAST_TESTS; num++) {
		CuAssertIntEquals(tc, num, getNumCollections(doc));
		uri = randomUniqueURI(doc);
		col = createCollection(doc, uri);
		CuAssertIntEquals(tc, num+1, getNumCollections(doc));
	}
	for (; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumCollections(doc));
		col = getNthCollection(doc, 0);
		deleteCollection(col);
		CuAssertIntEquals(tc, num-1, getNumCollections(doc));
	}
	CuAssertIntEquals(tc, 0, getNumCollections(doc));
	deleteDocument(doc);
}

void TestCollectionIndexing(CuTest* tc) {
	Document* doc = createDocument();
	char* uri;
	Collection* col;
	int num;
	for (num=0; num<NUM_SLOW_TESTS; num++) {
		uri = randomUniqueURI(doc);
		// avoid duplicates
		while (isCollectionURI(doc, uri))
			uri = randomUniqueURI(doc);
		col = createCollection(doc, uri);
	}
	int index;
	for (num=NUM_SLOW_TESTS; num>0; num--) {
		CuAssertIntEquals(tc, num, getNumCollections(doc));
		index = randomNumber(num);
		col = getNthCollection(doc, index);
		uri = getCollectionURI(col); // copy uri (because it will be destroyed)
		CuAssertIntEquals(tc, 1, isCollection(doc, col));
		CuAssertIntEquals(tc, 1, isCollectionURI(doc, uri));
		deleteCollection(col);
		CuAssertIntEquals(tc, num-1, getNumCollections(doc));
		CuAssertIntEquals(tc, 0, isCollection(doc, col));
		CuAssertIntEquals(tc, 0, isCollectionURI(doc, uri));
	}
	deleteDocument(doc);
}

void PrintArrayTestInfo() {
	printf("testing arrays\n");
}

CuSuite* ArrayGetSuite() {
	CuSuite* arrayTests = CuSuiteNew();
	SUITE_ADD_TEST(arrayTests, PrintArrayTestInfo);
	SUITE_ADD_TEST(arrayTests, TestSingleDNAComponent);
	SUITE_ADD_TEST(arrayTests, TestNumDNAComponents);
	SUITE_ADD_TEST(arrayTests, TestDNAComponentIndexing);
	SUITE_ADD_TEST(arrayTests, TestSingleAnnotation);
	SUITE_ADD_TEST(arrayTests, TestNumAnnotations);
	SUITE_ADD_TEST(arrayTests, TestAnnotationIndexing);
	SUITE_ADD_TEST(arrayTests, TestSingleCollection);
	SUITE_ADD_TEST(arrayTests, TestNumCollections);
	SUITE_ADD_TEST(arrayTests, TestCollectionIndexing);
	return arrayTests;
}
