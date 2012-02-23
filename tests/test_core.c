#include "CuTest.h"
#include "utilities.h"
#include "core.h"

void TestInitialNumbers(CuTest* tc)
{
	CuAssertIntEquals(tc, getNumDNAComponents(),		0);
	CuAssertIntEquals(tc, getNumSequenceAnnotations(),	0);
	CuAssertIntEquals(tc, getNumCollections(),			0);
	cleanup();
}

// TODO why does this cause glibc error??
void TestIsComponent(CuTest* tc)
{
	int r;
	char* id;
	for( r=0; r<100; r++ )
	{
		id = randomString();
		CuAssertIntEquals(tc, isComponent(id), 0);
	}
	cleanup();
}

// TODO why does this cause glibc error??
// TODO why is getNumDNAComponents sometimes off by 1??
void TestNewComponent(CuTest* tc)
{
	char* id;
	int sofar = 0;
	int total = 100;
	while( sofar<total )
	{
		// create component
		id = randomString();
		newComponent(id);
		sofar++;
		// check that it's being tracked
		CuAssertIntEquals(tc, isComponent(id), 1);
		CuAssertIntEquals(tc, getNumDNAComponents(), sofar);
	}
	cleanup();
}

int main(void)
{
	// seed with current time
	// should only be done once
	srand( time(NULL) );
	
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestInitialNumbers);
	SUITE_ADD_TEST(suite, TestNewComponent);
	SUITE_ADD_TEST(suite, TestIsComponent);
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}
