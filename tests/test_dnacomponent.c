#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "dnacomponent.h"

#define NUM_FAST_TESTS 10000

void TestCreateEmptyDNAComponent(CuTest* tc) {
	DNAComponent* com = createDNAComponent("");
	CuAssertStrEquals(tc, "", com->id);
	deleteDNAComponent(com);
}

void TestCreateNullDNAComponent(CuTest* tc) {
	DNAComponent* com = createDNAComponent(NULL);
	CuAssertStrEquals(tc, NULL, com->id);
	deleteDNAComponent(com);
}

void TestCreateRandomDNAComponent(CuTest* tc) {
	char* id;
	char* name;
	char* descr;
	DNAComponent* com;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		id    = randomString();
		name  = randomString();
		descr = randomString();
		com = createDNAComponent(id);
		setDNAComponentName(com, name);
		setDNAComponentDescription(com, descr);
		CuAssertStrEquals(tc, id,    getDNAComponentID(com));
		CuAssertStrEquals(tc, name,  getDNAComponentName(com));
		CuAssertStrEquals(tc, descr, getDNAComponentDescription(com));
		deleteDNAComponent(com);
	}
}

void TestEmptyDNAComponentProperties(CuTest* tc) {
	DNAComponent* com = createDNAComponent("");
	setDNAComponentName(com, "");
	setDNAComponentDescription(com, "");
	CuAssertStrEquals(tc, "", getDNAComponentID(com));
	CuAssertStrEquals(tc, "", getDNAComponentName(com));
	CuAssertStrEquals(tc, "", getDNAComponentDescription(com));
	deleteDNAComponent(com);
}

void TestNullDNAComponentProperties(CuTest* tc) {
	DNAComponent* com = createDNAComponent(NULL);
	setDNAComponentName(com, NULL);
	setDNAComponentDescription(com, NULL);
	CuAssertStrEquals(tc, NULL, getDNAComponentID(com));
	CuAssertStrEquals(tc, NULL, getDNAComponentName(com));
	CuAssertStrEquals(tc, NULL, getDNAComponentDescription(com));
	deleteDNAComponent(com);
}

void TestRandomDNAComponentProperties(CuTest* tc) {
	char* id;
	char* name;
	char* descr;
	DNAComponent* com;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		id    = randomString();
		name  = randomString();
		descr = randomString();
		com = createDNAComponent(id);
		setDNAComponentName(com, name);
		setDNAComponentDescription(com, descr);
		CuAssertStrEquals(tc, id,    getDNAComponentID(com));
		CuAssertStrEquals(tc, name,  getDNAComponentName(com));
		CuAssertStrEquals(tc, descr, getDNAComponentDescription(com));
		deleteDNAComponent(com);
	}
}

CuSuite* DNAComponentGetSuite() {
	CuSuite* dnaComponentTests = CuSuiteNew();
	SUITE_ADD_TEST(dnaComponentTests, TestCreateEmptyDNAComponent);
	SUITE_ADD_TEST(dnaComponentTests, TestCreateNullDNAComponent);
	SUITE_ADD_TEST(dnaComponentTests, TestCreateRandomDNAComponent);
	SUITE_ADD_TEST(dnaComponentTests, TestEmptyDNAComponentProperties);
	SUITE_ADD_TEST(dnaComponentTests, TestNullDNAComponentProperties);
	SUITE_ADD_TEST(dnaComponentTests, TestRandomDNAComponentProperties);
	return dnaComponentTests;
}
