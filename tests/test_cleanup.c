#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "property.h"
#include "document.h"
#include "test_examples.h"

#define NUM_SLOW_TESTS 10
#define INFILE "../examples/valid/ntriples.nt"

void TestMultipleDeleteTextProperty(CuTest* tc) {
	int n;
	char* data;
	TextProperty* pro;
	for (n=0; n<NUM_SLOW_TESTS; n++) {
		data = randomString();
		pro = createTextProperty();
		setTextProperty(pro, data);
		deleteTextProperty(pro);
	}
}

void PrintCleanupTestInfo() {
	printf("testing memory cleanup\n");
}

CuSuite* CleanupGetSuite() {
	CuSuite* cleanupTests = CuSuiteNew();
	SUITE_ADD_TEST(cleanupTests, PrintCleanupTestInfo);
	SUITE_ADD_TEST(cleanupTests, TestMultipleDeleteTextProperty);
	return cleanupTests;
}
