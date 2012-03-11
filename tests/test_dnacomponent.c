#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "dnacomponent.h"

#define NUM_FAST_TESTS 10000

void TestCreateEmptyDNAComponent(CuTest* tc) {
	DNAComponent* com = createDNAComponent("");
	CuAssertStrEquals(tc, "", getDNAComponentURI(com));
	deleteDNAComponent(com);
}

void TestCreateNullDNAComponent(CuTest* tc) {
	DNAComponent* com = createDNAComponent(NULL);
	CuAssertStrEquals(tc, NULL, getDNAComponentURI(com));
	deleteDNAComponent(com);
}

void TestCreateRandomDNAComponent(CuTest* tc) {
	char* uri;
	char* name;
	char* descr;
	DNAComponent* com;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		uri   = randomString();
		name  = randomString();
		descr = randomString();
		com = createDNAComponent(uri);
		setDNAComponentName(com, name);
		setDNAComponentDescription(com, descr);
		CuAssertStrEquals(tc, uri,   getDNAComponentURI(com));
		CuAssertStrEquals(tc, name,  getDNAComponentName(com));
		CuAssertStrEquals(tc, descr, getDNAComponentDescription(com));
		deleteDNAComponent(com);
	}
}

void TestEmptyDNAComponentProperties(CuTest* tc) {
	DNAComponent* com = createDNAComponent("");
	setDNAComponentName(com, "");
	setDNAComponentDescription(com, "");
	CuAssertStrEquals(tc, "", getDNAComponentURI(com));
	CuAssertStrEquals(tc, "", getDNAComponentName(com));
	CuAssertStrEquals(tc, "", getDNAComponentDescription(com));
	deleteDNAComponent(com);
}

void TestNullDNAComponentProperties(CuTest* tc) {
	DNAComponent* com = createDNAComponent(NULL);
	setDNAComponentName(com, NULL);
	setDNAComponentDescription(com, NULL);
	CuAssertStrEquals(tc, NULL, getDNAComponentURI(com));
	CuAssertStrEquals(tc, NULL, getDNAComponentName(com));
	CuAssertStrEquals(tc, NULL, getDNAComponentDescription(com));
	deleteDNAComponent(com);
}

void TestRandomDNAComponentProperties(CuTest* tc) {
	char* uri;
	char* name;
	char* descr;
	DNAComponent* com;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		uri   = randomString();
		name  = randomString();
		descr = randomString();
		com = createDNAComponent(uri);
		setDNAComponentName(com, name);
		setDNAComponentDescription(com, descr);
		CuAssertStrEquals(tc, uri,   getDNAComponentURI(com));
		CuAssertStrEquals(tc, name,  getDNAComponentName(com));
		CuAssertStrEquals(tc, descr, getDNAComponentDescription(com));
		deleteDNAComponent(com);
	}
}

void PrintDNAComponentTestInfo() {
	printf("testing core/dnacomponent\n");
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
