#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

void TestValidateValidExamples(CuTest *tc) {
	printf("\n");
	xmlDocPtr doc;
	int n;
	for (n=0; n<NUM_VALID_EXAMPLES; n++) {
		printf("validating %s\n", VALID_EXAMPLE_FILENAMES[n]);
		doc = xmlParseFile(VALID_EXAMPLE_FILENAMES[n]);
		CuAssertIntEquals(tc, 1, isValidSBOL(doc));
		xmlFreeDoc(doc);
		xmlCleanupParser();
	}
}

// dummy function that prevents libxml2
// from printing an error for every invalid example
void ignore(void *context, const char *message, ...) {}

void TestRejectInvalidExamples(CuTest *tc) {

	// mask errors with dummy function
	xmlGenericErrorFunc handler = (xmlGenericErrorFunc) ignore;
	initGenericErrorDefaultFunc(&handler);

	printf("\n");
	xmlDocPtr doc;
	int n;
	for (n=0; n<NUM_INVALID_EXAMPLES; n++) {
		printf("rejecting %s\n", INVALID_EXAMPLE_FILENAMES[n]);
		doc = xmlParseFile(INVALID_EXAMPLE_FILENAMES[n]);
		CuAssertIntEquals(tc, 0, isValidSBOL(doc));
		xmlFreeDoc(doc);
		xmlCleanupParser();
	}

	// restore normal error handling
	initGenericErrorDefaultFunc(NULL);
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
