#include <stdio.h>
#include <time.h>
#include "CuTest.h"
#include "core.h"

char randomChar()
{
	// TODO allow other characters?
	char* allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int index = rand() % strlen(allowed);
	return allowed[index];
}

char* randomString()
{
	int length = rand() % 100;
	char* string = malloc(sizeof(char*) * length);
	int i;
	for( i=0; i<length-1; i++ )
		string[i] = randomChar();
	string[length] = '\0';
	return string;
}

void TestInitialNumbers(CuTest* tc)
{
	CuAssertIntEquals(tc, getNumDNAComponents(),		0);
	CuAssertIntEquals(tc, getNumSequenceAnnotations(),	0);
	CuAssertIntEquals(tc, getNumCollections(),			0);
}

void TestGetNumTracking(CuTest* tc);

int main(void)
{
	// seed with current time
	// should only be done once
	srand( time(NULL) );
	
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestInitialNumbers);
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}
