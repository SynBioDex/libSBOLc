#include <stdio.h>
#include <string.h>
#include "sbol.h"

// TODO remove this file?

int main(int argc, char** argv) {
	if (argc != 3)
		return -1;
	printf("Are %s and %s the same? ", argv[1], argv[2]);
	int result = sameContent(argv[1], argv[2]);
	if (result == 1)
		printf("yes\n");
	else
		printf("no\n");
	return result;
}
