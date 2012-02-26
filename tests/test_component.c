#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "component.h"

#define NUM_FAST_TESTS 10000

void TestCreateEmptyComponent(CuTest* tc) {
	DNAComponent* com = createComponent("");
	CuAssertStrEquals(tc, "", com->id);
	deleteComponent(com);
}

void TestCreateNullComponent(CuTest* tc) {
	DNAComponent* com = createComponent(NULL);
	CuAssertStrEquals(tc, NULL, com->id);
	deleteComponent(com);
}

void TestCreateRandomComponent(CuTest* tc) {
	char* id;
	char* name;
	char* descr;
	DNAComponent* com;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		id    = randomString();
		name  = randomString();
		descr = randomString();
		com = createComponent(id);
		setComponentName(com, name);
		setComponentDescription(com, descr);
		CuAssertStrEquals(tc, id,    getComponentID(com));
		CuAssertStrEquals(tc, name,  getComponentName(com));
		CuAssertStrEquals(tc, descr, getComponentDescription(com));
		deleteComponent(com);
	}
}

void TestEmptyComponentProperties(CuTest* tc) {
	DNAComponent* com = createComponent("");
	setComponentName(com, "");
	setComponentDescription(com, "");
	CuAssertStrEquals(tc, "", getComponentID(com));
	CuAssertStrEquals(tc, "", getComponentName(com));
	CuAssertStrEquals(tc, "", getComponentDescription(com));
	deleteComponent(com);
}

void TestNullComponentProperties(CuTest* tc) {
	DNAComponent* com = createComponent(NULL);
	setComponentName(com, NULL);
	setComponentDescription(com, NULL);
	CuAssertStrEquals(tc, NULL, getComponentID(com));
	CuAssertStrEquals(tc, NULL, getComponentName(com));
	CuAssertStrEquals(tc, NULL, getComponentDescription(com));
	deleteComponent(com);
}

void TestRandomComponentProperties(CuTest* tc) {
	char* id;
	char* name;
	char* descr;
	DNAComponent* com;
	int repeat;
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		id    = randomString();
		name  = randomString();
		descr = randomString();
		com = createComponent(id);
		setComponentName(com, name);
		setComponentDescription(com, descr);
		CuAssertStrEquals(tc, id,    getComponentID(com));
		CuAssertStrEquals(tc, name,  getComponentName(com));
		CuAssertStrEquals(tc, descr, getComponentDescription(com));
		deleteComponent(com);
	}
}

CuSuite* ComponentGetSuite() {
	CuSuite* collectionTests = CuSuiteNew();
	SUITE_ADD_TEST(collectionTests, TestCreateEmptyComponent);
	SUITE_ADD_TEST(collectionTests, TestCreateNullComponent);
	SUITE_ADD_TEST(collectionTests, TestCreateRandomComponent);
	SUITE_ADD_TEST(collectionTests, TestEmptyComponentProperties);
	SUITE_ADD_TEST(collectionTests, TestNullComponentProperties);
	SUITE_ADD_TEST(collectionTests, TestRandomComponentProperties);
	return collectionTests;
}
