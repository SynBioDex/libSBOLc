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

CuSuite* ComponentGetSuite() {
	CuSuite* collectionTests = CuSuiteNew();
	SUITE_ADD_TEST(collectionTests, TestCreateEmptyComponent);
	return collectionTests;
}
