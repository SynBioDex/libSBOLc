#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "property.h"

#define NUM_FAST_TESTS 10000

void TestCreateProperty(CuTest* tc) {
	Property* pro = createProperty();
	CuAssertPtrEquals(tc, NULL, getProperty(pro));
	deleteProperty(pro);
}

void TestGetSetCompareProperty(CuTest* tc) {
	Property* pro;
	char* data;
	int repeat;
	// test null
	pro = createProperty();
	setProperty(pro, NULL);
	CuAssertPtrEquals(tc, NULL, getProperty(pro));
	// test empty
	pro = createProperty();
	setProperty(pro, "");
	CuAssertStrEquals(tc, "", getProperty(pro));
	// test lots of random variations
	for (repeat=0; repeat<NUM_FAST_TESTS; repeat++) {
		data = randomString();
		pro = createProperty();
		setProperty(pro, data);
		CuAssertStrEquals(tc, data, getProperty(pro));
		CuAssertIntEquals(tc, 0, compareProperty(pro, data));
		deleteProperty(pro); // TODO why does this segfault?
	}
}

void PrintPropertyTestInfo() {
	printf("testing core/property\n");
}

CuSuite* PropertyGetSuite() {
	CuSuite* properyTests = CuSuiteNew();
	SUITE_ADD_TEST(properyTests, PrintPropertyTestInfo);
	SUITE_ADD_TEST(properyTests, TestCreateProperty);
	SUITE_ADD_TEST(properyTests, TestGetSetCompareProperty);
	return properyTests;
}
