#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "document.h"
#include "dnacomponent.h"
#include "sequenceannotation.h"

#define NUM_FAST_TESTS 10000
#define NUM_SLOW_TESTS   100

void TestCreateEmptyDNAComponent(CuTest* tc) {
	Document* doc = createDocument();
	DNAComponent* com = createDNAComponent(doc, "");
	CuAssertStrEquals(tc, "", getDNAComponentURI(com));
	deleteDNAComponent(com);
	deleteDocument(doc);
}

void TestCreateNullDNAComponent(CuTest* tc) {
	Document* doc = createDocument();
	DNAComponent* com = createDNAComponent(doc, NULL);
	CuAssertStrEquals(tc, NULL, getDNAComponentURI(com));
	deleteDNAComponent(com);
	deleteDocument(doc);
}

void TestCreateRandomDNAComponent(CuTest* tc) {
	Document* doc = createDocument();
	char* uri;
	char* name;
	char* descr;
	DNAComponent* com;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		uri   = randomUniqueURI(doc);
		name  = randomString();
		descr = randomString();
		com = createDNAComponent(doc, uri);
		setDNAComponentName(com, name);
		setDNAComponentDescription(com, descr);
		CuAssertStrEquals(tc, uri,   getDNAComponentURI(com));
		CuAssertStrEquals(tc, name,  getDNAComponentName(com));
		CuAssertStrEquals(tc, descr, getDNAComponentDescription(com));
		deleteDNAComponent(com);
	}
	deleteDocument(doc);
}

void TestEmptyDNAComponentProperties(CuTest* tc) {
	Document* doc = createDocument();
	DNAComponent* com = createDNAComponent(doc, "");
	setDNAComponentName(com, "");
	setDNAComponentDescription(com, "");
	CuAssertStrEquals(tc, "", getDNAComponentURI(com));
	CuAssertStrEquals(tc, "", getDNAComponentName(com));
	CuAssertStrEquals(tc, "", getDNAComponentDescription(com));
	deleteDNAComponent(com);
	deleteDocument(doc);
}

void TestNullDNAComponentProperties(CuTest* tc) {
	Document* doc = createDocument();
	DNAComponent* com = createDNAComponent(doc, NULL);
	setDNAComponentName(com, NULL);
	setDNAComponentDescription(com, NULL);
	CuAssertStrEquals(tc, NULL, getDNAComponentURI(com));
	CuAssertStrEquals(tc, NULL, getDNAComponentName(com));
	CuAssertStrEquals(tc, NULL, getDNAComponentDescription(com));
	deleteDNAComponent(com);
	deleteDocument(doc);
}

void TestRandomDNAComponentProperties(CuTest* tc) {
	Document* doc = createDocument();
	char* uri;
	char* name;
	char* descr;
	DNAComponent* com;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		uri   = randomUniqueURI(doc);
		name  = randomString();
		descr = randomString();
		com = createDNAComponent(doc, uri);
		setDNAComponentName(com, name);
		setDNAComponentDescription(com, descr);
		CuAssertStrEquals(tc, uri,   getDNAComponentURI(com));
		CuAssertStrEquals(tc, name,  getDNAComponentName(com));
		CuAssertStrEquals(tc, descr, getDNAComponentDescription(com));
		deleteDNAComponent(com);
	}
	deleteDocument(doc);
}

void TestAddRemoveAnnotations(CuTest *tc) {
    Document* doc = createDocument();
    int n;
    DNAComponent* com = createDNAComponent(doc, randomUniqueURI(doc));
    char* uri;
    SequenceAnnotation* ann;

    // add annotations
    for (n=0; n<NUM_SLOW_TESTS; n++) {
        uri = randomUniqueURI(doc);
        ann = createSequenceAnnotation(doc, uri);
        CuAssertIntEquals(tc, n, getNumSequenceAnnotationsFor(com));
        printf("numAnnotations: %i\n", n);
        addSequenceAnnotation(com, ann);
        CuAssertIntEquals(tc, n+1, getNumSequenceAnnotationsFor(com));
        CuAssertPtrEquals(tc, ann, getNthSequenceAnnotationFor(com, n));
    }

    // remove annotations
    for (n=0; n<NUM_SLOW_TESTS; n++) {
        CuAssertIntEquals(tc, NUM_SLOW_TESTS-n, getNumSequenceAnnotationsFor(com));
        printf("numAnnotations: %i\n", NUM_SLOW_TESTS-n);
        ann = getNthSequenceAnnotationFor(com, n);
        removeSequenceAnnotation(com, ann);
        CuAssertIntEquals(tc, NUM_SLOW_TESTS-n-1, getNumSequenceAnnotationsFor(com));
        deleteSequenceAnnotation(ann);
    }
    deleteDocument(doc);
}

void PrintDNAComponentTestInfo() {
	printf("testing dnacomponents\n");
}

CuSuite* DNAComponentGetSuite() {
	CuSuite* dnaComponentTests = CuSuiteNew();
	SUITE_ADD_TEST(dnaComponentTests, PrintDNAComponentTestInfo);
	SUITE_ADD_TEST(dnaComponentTests, TestCreateEmptyDNAComponent);
	SUITE_ADD_TEST(dnaComponentTests, TestCreateNullDNAComponent);
	SUITE_ADD_TEST(dnaComponentTests, TestCreateRandomDNAComponent);
	SUITE_ADD_TEST(dnaComponentTests, TestEmptyDNAComponentProperties);
	SUITE_ADD_TEST(dnaComponentTests, TestNullDNAComponentProperties);
	SUITE_ADD_TEST(dnaComponentTests, TestRandomDNAComponentProperties);
	SUITE_ADD_TEST(dnaComponentTests, TestAddRemoveAnnotations);
	return dnaComponentTests;
}
