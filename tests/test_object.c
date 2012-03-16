#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
#include "object.h"

void TestCreateBlankSBOLObject(CuTest* tc) {
	// test null
	SBOLObject* obj = createSBOLObject(NULL);
	CuAssertPtrEquals(tc, NULL, obj);
	CuAssertPtrEquals(tc, NULL, getSBOLObjectURI(obj));
	deleteSBOLObject(obj);
	// test empty string
	obj = createSBOLObject("");
	CuAssertStrEquals(tc, "", getSBOLObjectURI(obj));
	deleteSBOLObject(obj);
}

void TestCreateDuplicateSBOLObject(CuTest* tc) {
	// test same uri twice
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
	return;
}

void TestCreateBlankSBOLCompoundObject(CuTest* tc) {
	// test null
	SBOLCompoundObject* obj = createSBOLCompoundObject(NULL);
	CuAssertPtrEquals(tc, NULL, obj);
	CuAssertPtrEquals(tc, NULL, getSBOLCompoundObjectURI(obj));
	deleteSBOLCompoundObject(obj);
	// test empty string
	obj = createSBOLCompoundObject("");
	CuAssertStrEquals(tc, "", getSBOLCompoundObjectURI(obj));
	deleteSBOLCompoundObject(obj);
}

void PrintSBOLObjectTestInfo() {
	printf("testing core/object\n");
}

// TODO TestCreateRandomObjects?

CuSuite* SBOLObjectGetSuite() {
	CuSuite* sbolObjectTests = CuSuiteNew();
	SUITE_ADD_TEST(sbolObjectTests, PrintSBOLObjectTestInfo);
	SUITE_ADD_TEST(sbolObjectTests, TestCreateBlankSBOLObject);
	SUITE_ADD_TEST(sbolObjectTests, TestCreateDuplicateSBOLObject);
	SUITE_ADD_TEST(sbolObjectTests, TestCreateBlankSBOLCompoundObject);
	return sbolObjectTests;
}
