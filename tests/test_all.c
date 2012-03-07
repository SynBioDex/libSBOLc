#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"

CuSuite* DNASequenceGetSuite();
CuSuite* SequenceAnnotationGetSuite();
CuSuite* CollectionGetSuite();
CuSuite* DNAComponentGetSuite();
CuSuite* GenericArrayGetSuite();
CuSuite* PropertyGetSuite();
CuSuite* WriteExamplesGetSuite();
CuSuite* CleanupGetSuite();

void RunAllTests(void) {
	// seed with current time
	// should only be done once
	srand( time(NULL) );
	
	CuString* output = CuStringNew();
	CuSuite*  suite  = CuSuiteNew();

	CuSuiteAddSuite(suite, GenericArrayGetSuite());
	CuSuiteAddSuite(suite, DNASequenceGetSuite());
	CuSuiteAddSuite(suite, SequenceAnnotationGetSuite());
	CuSuiteAddSuite(suite, DNAComponentGetSuite());
	CuSuiteAddSuite(suite, CollectionGetSuite());
	CuSuiteAddSuite(suite, PropertyGetSuite());
	CuSuiteAddSuite(suite, CleanupGetSuite());
	CuSuiteAddSuite(suite, WriteExamplesGetSuite());
	
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	
	printf("%s\n", output->buffer);
}

int main(void) {
	RunAllTests();
}
