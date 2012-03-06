#include <stdio.h>
#include "core.h"
#include "reader.h"

void parseAndPrint(char* filename) {
	readSBOLCore(filename);
	printSBOLCore();
	cleanupSBOLCore();
}

int main(int argc, char** argv) {
	char* example;
	if( argc < 2 ) {
		// TODO fill in using CMake?
		// TODO read sbol format!
		example = "../examples/valid/ntriples.nt";
	    parseAndPrint(example);
    } else {
        int i;
        for (i=1; i<argc; i++) {
            example = argv[i];
            parseAndPrint(example);
        }
	}
	return 0;
}
