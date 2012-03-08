#include <stdio.h>
#include "core.h"
#include "reader.h"
#include "writer.h"

#define DEFAULT_INFILE  "../examples/valid/ntriples_simple.nt"
#define DEFAULT_OUTFILE "ntriples_simple.xml"

int main(int argc, char* argv[]) {
	char* infile;
	char* outfile;
	if (argc == 1) {
		infile  = DEFAULT_INFILE;
		outfile = DEFAULT_OUTFILE;
	} else if (argc == 3) {
		infile  = argv[1];
		outfile = argv[2];
	} else {
		printf("usage: %s infile outfile.xml\n", argv[0]);
		return 1;
	}
	int error;
	xmlDocPtr doc;
	char* verdict;
	readSBOLCore(infile);
	error = writeSBOLCore(outfile);
	if (error == 0)
		verdict = "yes";
	else
		verdict = "NO";
	printf("Successful round trip of %s? %s\n", outfile, verdict);
	cleanupSBOLCore();
	return error;
}
