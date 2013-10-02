#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "sbol.h"
#include "test_examples.h"

// declare functions from the sbol_create_valid* examples
Document* CreateValid01();
Document* CreateValid02();
Document* CreateValid03();
Document* CreateValid04();
Document* CreateValid05();
Document* CreateValid06();
Document* CreateValid07();
Document* CreateValid08();
Document* CreateValid09();
Document* CreateValid10();
Document* CreateValid11();
Document* CreateValid12();
Document* CreateValid13();

// put them in an array so they can be called by index
Document* (*CREATE_FUNCTIONS[NUM_VALID_EXAMPLES])() = {
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
		printf("creating %s\n", TEST_OUTPUT_FILENAMES[n]);
		Document* doc = CREATE_FUNCTIONS[n]();
		TEST_LOADED_FUNCTIONS[n](tc, doc);
		writeDocumentToFile(doc, TEST_OUTPUT_FILENAMES[n]);
		deleteDocument(doc);

		doc = createDocument();
		TestNothingLoaded(tc, doc);
		readDocument(doc, TEST_OUTPUT_FILENAMES[n]);
		TEST_LOADED_FUNCTIONS[n](tc, doc);
		deleteDocument(doc);
	}
}

CuSuite* WriterGetSuite() {
	CuSuite* writerTests = CuSuiteNew();
	SUITE_ADD_TEST(writerTests, CreateValidExamples);
	return writerTests;
}
