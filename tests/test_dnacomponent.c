#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "document.h"
#include "dnacomponent.h"

#define NUM_FAST_TESTS 10000

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
	return dnaComponentTests;
}
