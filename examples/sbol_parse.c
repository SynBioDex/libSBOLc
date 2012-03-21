#include <stdio.h>
#include "sbol.h"

#define DEFAULT_FILE "../examples/valid/ntriples.nt"

void parse(char* filename) {
	readSBOLCore(filename);
	printSBOLCore();
	cleanupSBOLCore();
}

int main(int argc, char** argv) {
	if (argc<2)
		parse(DEFAULT_FILE);
	else {
		int i;
		for (i=1; i<argc; i++)
			parse(argv[i]);
	}
	return 0;
}
