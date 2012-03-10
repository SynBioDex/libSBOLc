#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "property.h"

#define NUM_SLOW_TESTS 10
#define INFILE "../examples/valid/ntriples.nt"

void TestCleanupFirst(CuTest* tc) {
	cleanupSBOLCore();
}

void TestMultipleCleanupFirst(CuTest* tc) {
	int i;
	for (i=0; i<NUM_SLOW_TESTS; i++)
		cleanupSBOLCore();
}

// TODO change this to use an rdfxml file
void TestReadThenCleanup(CuTest* tc) {
	int num;
	// check that some of each type is read
	num = 0;
	readSBOLCore(INFILE);
	num += (int) (getNumDNASequences()        > 0);
	num += (int) (getNumSequenceAnnotations() > 0);
	num += (int) (getNumDNAComponents()       > 0);
	num += (int) (getNumCollections()         > 0);
	CuAssertIntEquals(tc, 4, num);
	cleanupSBOLCore();
	// check that none are left after cleanup
	num = 0;
	num += (int) (getNumDNASequences()        == 0);
	num += (int) (getNumSequenceAnnotations() == 0);
	num += (int) (getNumDNAComponents()       == 0);
	num += (int) (getNumCollections()         == 0);
	CuAssertIntEquals(tc, 4, num);
	cleanupSBOLCore();
}

void TestMultipleDeleteProperty(CuTest* tc) {
	int n;
	char* data;
	Property* pro;
	for (n=0; n<NUM_SLOW_TESTS; n++) {
		data = randomString();
		pro = createProperty();
		setProperty(pro, data);
		deleteProperty(pro);
	}
}

void PrintCleanupTestInfo() {
	printf("testing memory cleanup\n");
}

CuSuite* CleanupGetSuite() {
	CuSuite* cleanupTests = CuSuiteNew();
	SUITE_ADD_TEST(cleanupTests, PrintCleanupTestInfo);
	SUITE_ADD_TEST(cleanupTests, TestCleanupFirst);
	SUITE_ADD_TEST(cleanupTests, TestMultipleCleanupFirst);
	//SUITE_ADD_TEST(cleanupTests, TestReadThenCleanup);
	SUITE_ADD_TEST(cleanupTests, TestMultipleDeleteProperty);
	return cleanupTests;
}
