#include <stdio.h>
#include "sbol.h"

void parse(char* filename) {
	Document* doc = createDocument();
	printf("parsing %s\n", filename);
	readDocument(doc, filename);
	printDocument(doc);
	deleteDocument(doc);
}

int main(int argc, char** argv) {
	if (argc < 2)
		printf("usage: %s doc1.xml [doc2.xml ...]\n", argv[0]);
	else {
		int i;
		for (i=1; i<argc; i++)
			parse(argv[i]);
	}
	return 0;
}

