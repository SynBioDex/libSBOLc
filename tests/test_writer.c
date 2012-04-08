#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

// declare functions from the sbol_create_valid* examples
void CreateValid01(Document* doc);
void CreateValid02(Document* doc);
void CreateValid03(Document* doc);
void CreateValid04(Document* doc);
void CreateValid05(Document* doc);
void CreateValid06(Document* doc);
void CreateValid07(Document* doc);
void CreateValid08(Document* doc);
void CreateValid09(Document* doc);
void CreateValid10(Document* doc);
void CreateValid11(Document* doc);
void CreateValid12(Document* doc);
void CreateValid13(Document* doc);

// put them in an array so they can be called by index
void (*CREATE_FUNCTIONS[NUM_VALID_EXAMPLES])(Document* doc) = {
	CreateValid01,
	CreateValid02,
	CreateValid03,
	CreateValid04,
	CreateValid05,
	CreateValid06,
	CreateValid07,
	CreateValid08,
	CreateValid09,
	CreateValid10,
	CreateValid11,
	CreateValid12,
	CreateValid13
};

// check that the xml they create is actually valid
void CreateValidExamples(CuTest *tc) {
	Document* doc;
	printf("\n");
	int n;
	for (n=0; n<NUM_VALID_EXAMPLES; n++) {
		doc = createDocument();
		TestNothingLoaded(tc, doc);
		printf("creating %s\n", TEST_OUTPUT_FILENAMES[n]);
		CREATE_FUNCTIONS[n](doc);
		TEST_LOADED_FUNCTIONS[n](tc, doc);
		writeSBOLCore(doc, TEST_OUTPUT_FILENAMES[n]);
		deleteDocument(doc);

		doc = createDocument();
		TestNothingLoaded(tc, doc);
		readSBOLCore(doc, TEST_OUTPUT_FILENAMES[n]);
		TEST_LOADED_FUNCTIONS[n](tc, doc);
		deleteDocument(doc);
	}
}

CuSuite* WriterGetSuite() {
	CuSuite* writerTests = CuSuiteNew();
	SUITE_ADD_TEST(writerTests, CreateValidExamples);
	return writerTests;
}
