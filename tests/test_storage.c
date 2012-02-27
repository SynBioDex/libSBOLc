#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "storage.h"

#define NUM_FAST_TESTS 10000

void TestBlank(CuTest* tc) {
	return;
}

CuSuite* StorageGetSuite() {
	CuSuite* storageTests = CuSuiteNew();
	SUITE_ADD_TEST(storageTests, TestBlank);
	return storageTests;
}
