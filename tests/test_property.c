//#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "property.h"

void TestCreateProperty(CuTest* tc) {
	Property* pro = createProperty();
	CuAssertPtrEquals(tc, NULL, getProperty(pro));
}

CuSuite* PropertyGetSuite() {
	CuSuite* properyTests = CuSuiteNew();
	SUITE_ADD_TEST(properyTests, TestCreateProperty);
	return properyTests;
}
