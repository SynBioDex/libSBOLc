#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "property.h"

#define NUM_FAST_TESTS 10000

void TestCreateTextProperty(CuTest* tc) {
	TextProperty* pro = createText();
	CuAssertPtrEquals(tc, NULL, getText(pro));
	deleteText(pro);
}

void TestGetSetCompareProperty(CuTest* tc) {
	TextProperty* pro;
	char* data;
	int repeat;
	// test null
	pro = createText();
	setText(pro, NULL);
	CuAssertPtrEquals(tc, NULL, getText(pro));
	// test empty
	pro = createText();
	setText(pro, "");
	CuAssertStrEquals(tc, "", getText(pro));
	// test lots of random variations
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		data = randomString();
		pro  = createText();
		setText(pro, data);
		CuAssertStrEquals(tc, data, getText(pro));
		CuAssertIntEquals(tc, 0, strcmp(getText(pro), data));
		deleteText(pro); // TODO why does this segfault?
	}
}

void PrintPropertyTestInfo() {
	printf("testing core/property\n");
}

CuSuite* PropertyGetSuite() {
	CuSuite* properyTests = CuSuiteNew();
	SUITE_ADD_TEST(properyTests, PrintPropertyTestInfo);
	SUITE_ADD_TEST(properyTests, TestCreateTextProperty);
	SUITE_ADD_TEST(properyTests, TestGetSetCompareProperty);
	return properyTests;
}
