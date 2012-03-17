#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "object.h"

#define NUM_FAST_TESTS 1000

void TestCreateBlankSBOLObject(CuTest* tc) {
	cleanupSBOLObjects();
	
	// test null
	SBOLObject* obj = createSBOLObject(NULL);
	CuAssertIntEquals(tc, 0, getNumSBOLObjects());
	CuAssertIntEquals(tc, 0, getNumSBOLCompoundObjects());
	CuAssertPtrEquals(tc, NULL, obj);
	CuAssertPtrEquals(tc, NULL, getSBOLObjectURI(obj));
	deleteSBOLObject(obj);
	
	// test empty string
	obj = createSBOLObject("");
	CuAssertIntEquals(tc, 1, getNumSBOLObjects());
	CuAssertIntEquals(tc, 0, getNumSBOLCompoundObjects());
	CuAssertPtrEquals(tc, obj, getNthSBOLObject(0));
	CuAssertStrEquals(tc, "", getSBOLObjectURI(obj));
	deleteSBOLObject(obj);
	
	cleanupSBOLObjects();
}

void TestCreateDuplicateSBOLObject(CuTest* tc) {
	cleanupSBOLObjects();
	
	// create same uri twice
	char* uri = randomUniqueURI();
	SBOLObject* obj1 = createSBOLObject(uri);
	SBOLObject* obj2 = createSBOLObject(uri);
	
	// 2nd one should be rejected
	CuAssertStrEquals(tc, uri, getSBOLObjectURI(obj1));
	CuAssertPtrEquals(tc, NULL, obj2);
	CuAssertPtrEquals(tc, NULL, getSBOLObjectURI(obj2));
	
	// delete them both
	deleteSBOLObject(obj1);
	deleteSBOLObject(obj2);
	
	cleanupSBOLObjects();
}

void TestCleanupSBOLObjects(CuTest* tc) {

	// test that everything starts empty
	CuAssertIntEquals(tc, 0, getNumSBOLObjects());
	cleanupSBOLObjects();
	
	// create some SBOLObjects
	int n;
	char* uri;
	SBOLObject* obj;
	for (n=0; n<NUM_FAST_TESTS; n++) {
		do { uri = randomString(); } while (isSBOLObjectURI(uri));
		obj = createSBOLObject(uri);
		CuAssertPtrEquals(tc, obj, getNthSBOLObject(n));
		CuAssertStrEquals(tc, uri, getSBOLObjectURI(obj));
	}
	CuAssertIntEquals(tc, NUM_FAST_TESTS, getNumSBOLObjects());
	
	// test that they're deleted
	cleanupSBOLObjects();
	CuAssertIntEquals(tc, 0, getNumSBOLObjects());

}

void TestCreateRandomSBOLObjects(CuTest* tc) {
	cleanupSBOLObjects();
	
	// create some random SBOLObjects
	// and check that they behave right
	int n;
	char* uri;
	SBOLObject* obj;
	int duplicates = 0;
	for (n=0; n<NUM_FAST_TESTS; n++) {
		CuAssertIntEquals(tc, n-duplicates, getNumSBOLObjects());
		uri = randomString();
		if (isSBOLObjectURI(uri))
			duplicates++;
		else {
			obj = createSBOLObject(uri);
			CuAssertStrEquals(tc, uri, getSBOLObjectURI(obj));
		}
		CuAssertIntEquals(tc, (n+1)-duplicates, getNumSBOLObjects());
	}
	
	cleanupSBOLObjects();
}

void TestCreateBlankSBOLCompoundObject(CuTest* tc) {
	cleanupSBOLObjects();
	cleanupSBOLCompoundObjects();
	
	// test null
	SBOLCompoundObject* obj = createSBOLCompoundObject(NULL);
	CuAssertIntEquals(tc, 0, getNumSBOLObjects());
	CuAssertIntEquals(tc, 0, getNumSBOLCompoundObjects());
	CuAssertPtrEquals(tc, NULL, obj);
	CuAssertPtrEquals(tc, NULL, getSBOLCompoundObjectURI(obj));
	deleteSBOLCompoundObject(obj);
	
	// test empty string
	obj = createSBOLCompoundObject("");
	CuAssertIntEquals(tc, 1, getNumSBOLObjects());
	CuAssertIntEquals(tc, 1, getNumSBOLCompoundObjects());
	CuAssertPtrEquals(tc, obj, getNthSBOLCompoundObject(0));
	CuAssertStrEquals(tc, "", getSBOLCompoundObjectURI(obj));
	deleteSBOLCompoundObject(obj);
	CuAssertIntEquals(tc, 0, getNumSBOLCompoundObjects());
	
	cleanupSBOLObjects();
	cleanupSBOLCompoundObjects();
}

void TestCreateDuplicateSBOLCompoundObject(CuTest* tc) {
	cleanupSBOLObjects();
	cleanupSBOLCompoundObjects();
	
	// create same uri twice
	char* uri;
	do { uri = randomString(); } while (isSBOLObjectURI(uri));
	SBOLCompoundObject* obj1 = createSBOLCompoundObject(uri);
	SBOLCompoundObject* obj2 = createSBOLCompoundObject(uri);
	
	// 2nd one should be rejected
	CuAssertStrEquals(tc, uri, getSBOLCompoundObjectURI(obj1));
	CuAssertPtrEquals(tc, NULL, obj2);
	CuAssertPtrEquals(tc, NULL, getSBOLCompoundObjectURI(obj2));
	
	// delete them both
	deleteSBOLCompoundObject(obj1);
	deleteSBOLCompoundObject(obj2);
	
	cleanupSBOLCompoundObjects();
	cleanupSBOLObjects();
}

void TestCreateRandomSBOLCompoundObjects(CuTest* tc) {
	cleanupSBOLObjects();
	cleanupSBOLCompoundObjects();

	// create some random SBOLCompoundObjects
	// and check that they behave right
	int n;
	char* uri;
	SBOLCompoundObject* obj;
	int duplicates = 0;
	for (n=0; n<NUM_FAST_TESTS; n++) {
		CuAssertIntEquals(tc, n-duplicates, getNumSBOLCompoundObjects());
		uri = randomString();
		if (isSBOLCompoundObjectURI(uri))
			duplicates++;
		else {
			obj = createSBOLCompoundObject(uri);
			CuAssertStrEquals(tc, uri, getSBOLCompoundObjectURI(obj));
		}
		CuAssertIntEquals(tc, (n+1)-duplicates, getNumSBOLCompoundObjects());
	}
	
	cleanupSBOLCompoundObjects();
	cleanupSBOLObjects();
}

void PrintSBOLObjectTestInfo() {
	printf("testing core/object\n");
}

// TODO TestCreateRandomObjects?

CuSuite* SBOLObjectGetSuite() {
	CuSuite* sbolObjectTests = CuSuiteNew();
	SUITE_ADD_TEST(sbolObjectTests, PrintSBOLObjectTestInfo);
	SUITE_ADD_TEST(sbolObjectTests, TestCreateBlankSBOLObject);
	SUITE_ADD_TEST(sbolObjectTests, TestCleanupSBOLObjects);
	SUITE_ADD_TEST(sbolObjectTests, TestCreateDuplicateSBOLObject);
	SUITE_ADD_TEST(sbolObjectTests, TestCreateRandomSBOLObjects);
	SUITE_ADD_TEST(sbolObjectTests, TestCreateBlankSBOLCompoundObject);
	SUITE_ADD_TEST(sbolObjectTests, TestCreateDuplicateSBOLCompoundObject);
	SUITE_ADD_TEST(sbolObjectTests, TestCreateRandomSBOLCompoundObjects);
	return sbolObjectTests;
}
