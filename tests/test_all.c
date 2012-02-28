#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"
//#include "core.h"
#include "sequence.h"
#include "sequenceannotation.h"
#include "collection.h"
#include "storage.h"

CuSuite* SequenceGetSuite();
CuSuite* AnnotationGetSuite();
CuSuite* CollectionGetSuite();
CuSuite* ComponentGetSuite();
CuSuite* StorageGetSuite();

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
	CuSuiteAddSuite(suite, StorageGetSuite());
	
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	
	printf("%s\n", output->buffer);
}

int main(void) {
	RunAllTests();
}
