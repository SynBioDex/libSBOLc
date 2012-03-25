#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "property.h"

#define NUM_FAST_TESTS 10000

void TestCreateTextProperty(CuTest* tc) {
	TextProperty* pro = createTextProperty();
	CuAssertPtrEquals(tc, NULL, getTextProperty(pro));
	deleteTextProperty(pro);
}

void TestGetSetCompareProperty(CuTest* tc) {
	TextProperty* pro;
	char* data;
	int repeat;
	// test null
	pro = createTextProperty();
	setTextProperty(pro, NULL);
	CuAssertPtrEquals(tc, NULL, getTextProperty(pro));
	// test empty
	pro = createTextProperty();
	setTextProperty(pro, "");
	CuAssertStrEquals(tc, "", getTextProperty(pro));
	// test lots of random variations
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		data = randomString();
		pro  = createTextProperty();
		setTextProperty(pro, data);
		CuAssertStrEquals(tc, data, getTextProperty(pro));
		CuAssertIntEquals(tc, 0, strcmp(getTextProperty(pro), data));
		deleteTextProperty(pro);
	}
}

void TestDeleteEmptyProperty(CuTest* tc) {
	deleteTextProperty(NULL);
	TextProperty* pro = createTextProperty();
	deleteTextProperty(pro);
}

void PrintPropertyTestInfo() {
	printf("testing properties\n");
}

CuSuite* PropertyGetSuite() {
	CuSuite* properyTests = CuSuiteNew();
	SUITE_ADD_TEST(properyTests, PrintPropertyTestInfo);
	SUITE_ADD_TEST(properyTests, TestCreateTextProperty);
	SUITE_ADD_TEST(properyTests, TestGetSetCompareProperty);
	SUITE_ADD_TEST(properyTests, TestDeleteEmptyProperty);
	return properyTests;
}
