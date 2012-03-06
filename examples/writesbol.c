#include <stdio.h>
#include "core.h"
#include "reader.h"
#include "writer.h"

int main() {
	char* infile =  "../examples/valid/ntriples_component.nt";
	char* outfile = "ntriples_component.xml";
	readSBOLCore(infile);
	writeSBOLCore(outfile);
	cleanupSBOLCore();
    return 0;
}
