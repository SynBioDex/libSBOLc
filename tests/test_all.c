#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
//#include "core.h"
#include "sequence.h"
#include "annotation.h"
#include "collection.h"

CuSuite* SequenceGetSuite();
CuSuite* AnnotationGetSuite();
CuSuite* CollectionGetSuite();
CuSuite* ComponentGetSuite();

void RunAllTests(void) {
	// seed with current time
	// should only be done once
	srand( time(NULL) );
	
	CuString* output = CuStringNew();
	CuSuite*  suite  = CuSuiteNew();

	CuSuiteAddSuite(suite, SequenceGetSuite());
	CuSuiteAddSuite(suite, AnnotationGetSuite());
	CuSuiteAddSuite(suite, CollectionGetSuite());
	CuSuiteAddSuite(suite, ComponentGetSuite());
	
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	
	printf("%s\n", output->buffer);
}

int main(void) {
	RunAllTests();
}
