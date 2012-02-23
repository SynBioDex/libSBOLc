#include <stdio.h>
#include "CuTest.h"
#include "core.h"

void TestThatPasses(CuTest* tc) { return; }

int main(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestThatPasses);
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}
