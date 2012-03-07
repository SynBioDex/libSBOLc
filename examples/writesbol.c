#include <stdio.h>
#include "core.h"
#include "reader.h"
#include "writer.h"

#define INFILE  "../examples/valid/ntriples_simple.nt"
#define OUTFILE "ntriples_simple.xml"

int main() {
	readSBOLCore(INFILE);
	writeSBOLCore(OUTFILE);
	cleanupSBOLCore();
    return 0;
}
