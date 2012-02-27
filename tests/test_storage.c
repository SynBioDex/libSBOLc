#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utilities.h"
#include "storage.h"
#include "component.h"
#include "annotation.h"
#include "collection.h"

#define NUM_FAST_TESTS 10000

void TestAddComponent(CuTest* tc) {
	CuAssertIntEquals(tc, 0, getNumDNAComponents());
	DNAComponent* com = createComponent("one");
	registerComponent(com);
	CuAssertIntEquals(tc, 1, getNumDNAComponents());
}

void TestAddAnnotation(CuTest* tc) {
	CuAssertIntEquals(tc, 0, getNumSequenceAnnotations());
	SequenceAnnotation* ann = createSequenceAnnotation("one");
	registerSequenceAnnotation(ann);
	CuAssertIntEquals(tc, 1, getNumSequenceAnnotations());
}

void TestAddCollection(CuTest* tc) {
	CuAssertIntEquals(tc, 0, getNumCollections());
	Collection* col = createCollection("one");
	registerCollection(col);
	CuAssertIntEquals(tc, 1, getNumCollections());
}

CuSuite* StorageGetSuite() {
	CuSuite* storageTests = CuSuiteNew();
	SUITE_ADD_TEST(storageTests, TestAddComponent);
	SUITE_ADD_TEST(storageTests, TestAddAnnotation);
	SUITE_ADD_TEST(storageTests, TestAddCollection);
	return storageTests;
}
