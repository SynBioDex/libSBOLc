#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

void TestValidateValidExamples(CuTest *tc) {
	printf("\n");
	xmlDocPtr  doc;
	int n;
	for (n=0; n<NUM_VALID_EXAMPLES; n++) {
		printf("validating %s\n", VALID_EXAMPLE_FILENAMES[n]);
		doc = xmlParseFile(VALID_EXAMPLE_FILENAMES[n]);
		CuAssertIntEquals(tc, 1, isValidSBOL(doc));
		xmlFreeDoc(doc);
		xmlCleanupParser();
	}
}

// TODO keep this from printing errors
void TestRejectInvalidExamples(CuTest *tc) {
	printf("\n");
	xmlDocPtr  doc;
	int n;
	for (n=0; n<NUM_INVALID_EXAMPLES; n++) {
		printf("rejecting %s\n", INVALID_EXAMPLE_FILENAMES[n]);
		doc = xmlParseFile(INVALID_EXAMPLE_FILENAMES[n]);
		CuAssertIntEquals(tc, 0, isValidSBOL(doc));
		xmlFreeDoc(doc);
		xmlCleanupParser();
	}
}

CuSuite* ValidatorGetSuite() {

	// this initializes the library and checks potential ABI mismatches
	// between the version it was compiled for and the actual shared
	// library used.
    LIBXML_TEST_VERSION

	CuSuite* validatorTests = CuSuiteNew();
	SUITE_ADD_TEST(validatorTests, TestValidateValidExamples);
	SUITE_ADD_TEST(validatorTests, TestRejectInvalidExamples);
	return validatorTests;
}
