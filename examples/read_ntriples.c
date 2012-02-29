#include <stdio.h>
#include "core.h"
#include "reader.h"

void parse(char* filename) {
    // this does the parsing
	readSBOL(filename);

    // TODO print all structs
    // this prints the resulting DNAComponents
	printf("components:\n");
	int i;
	DNAComponent* com;
	for (i=0; i < getNumDNAComponents(); i++) {
		com = getNthDNAComponent(i);
		printDNAComponent(com, 1);
	}

	// and this deletes them
	cleanup();
}

int main(int argc, char** argv) {
	char* example;
	if( argc < 2 )
		// TODO fill in using CMake?
		example = "../examples/valid/ntriples.nt";
	else {
        int i;
        for (i=1; i<argc; i++) {
            example = argv[i];
            parse(example);
		    printf("\n");
        }

	}
	return 0;
}
