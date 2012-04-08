#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "property.h"
#include "document.h"
#include "test_examples.h"

#define NUM_SLOW_TESTS 10
#define INFILE "../examples/valid/ntriples.nt"

void TestReadThenCleanup(CuTest* tc) {
	Document* doc = createDocument();
	int num;
	// check that some of each type is read
	num = 0;
	readSBOLCore(doc, VALID_EXAMPLE_FILENAMES[0]);
	num += (int) (getNumDNASequences(doc)        > 0);
	num += (int) (getNumSequenceAnnotations(doc) > 0);
	num += (int) (getNumDNAComponents(doc)       > 0);
	num += (int) (getNumCollections(doc)         > 0);
	CuAssertIntEquals(tc, 4, num);
	cleanupDNASequences(doc);
	cleanupSequenceAnnotations(doc);
	cleanupDNAComponents(doc);
	cleanupCollections(doc);
	// check that none are left after cleanup
	num = 0;
	num += (int) (getNumDNASequences(doc)        == 0);
	num += (int) (getNumSequenceAnnotations(doc) == 0);
	num += (int) (getNumDNAComponents(doc)       == 0);
	num += (int) (getNumCollections(doc)         == 0);
	CuAssertIntEquals(tc, 4, num);
	deleteDocument(doc);
}

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
	SUITE_ADD_TEST(cleanupTests, TestReadThenCleanup);
	SUITE_ADD_TEST(cleanupTests, TestMultipleDeleteTextProperty);
	return cleanupTests;
}
