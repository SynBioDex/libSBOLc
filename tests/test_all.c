#include <stdio.h>
#include "CuTest.h"
#include "utilities.h"

CuSuite* DNASequenceGetSuite();
CuSuite* SequenceAnnotationGetSuite();
CuSuite* CollectionGetSuite();
CuSuite* DNAComponentGetSuite();
CuSuite* GenericArrayGetSuite();
CuSuite* PropertyGetSuite();
CuSuite* CleanupGetSuite();
CuSuite* RoundTripGetSuite();
CuSuite* ReaderGetSuite();
CuSuite* WriterGetSuite();
CuSuite* SBOLObjectGetSuite();

void RunUnitTests() {
	CuString* output = CuStringNew();
	CuSuite*  suite  = CuSuiteNew();

	//CuSuiteAddSuite(suite, GenericArrayGetSuite());
	CuSuiteAddSuite(suite, SBOLObjectGetSuite());
	CuSuiteAddSuite(suite, DNASequenceGetSuite());
	CuSuiteAddSuite(suite, SequenceAnnotationGetSuite());
	CuSuiteAddSuite(suite, DNAComponentGetSuite());
	CuSuiteAddSuite(suite, CollectionGetSuite());
	CuSuiteAddSuite(suite, PropertyGetSuite());
	CuSuiteAddSuite(suite, CleanupGetSuite());
	
	printf("\nRunning unit tests...\n");
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

void RunExampleTests() {
	CuString* output = CuStringNew();
	CuSuite*  suite  = CuSuiteNew();

	CuSuiteAddSuite(suite, ReaderGetSuite());
	CuSuiteAddSuite(suite, WriterGetSuite());
	CuSuiteAddSuite(suite, RoundTripGetSuite());
	
	printf("\nChecking that examples are handled correctly...\n");
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

void main() {
	// seed with current time
	// should only be done once
	srand( time(NULL) );

	RunUnitTests();
	RunExampleTests();
}

