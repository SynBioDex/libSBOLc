#include <stdio.h>
#include "core.h"
#include "reader.h"
#include "writer.h"

int main() {
	char* infile =  "../examples/valid/ntriples.nt";
	char* outfile = "ntriples.xml";
	readSBOLCore(infile);
	writeSBOLCore(outfile);
	cleanupSBOLCore();
    return 0;
}
