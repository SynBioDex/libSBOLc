#include <stdio.h>
#include "sbol.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {

		// print usage
		printf("usage: %s doc1.xml [doc2.xml ...]\n", argv[0]);
		return 1;

	} else {

		// validate each file
		int arg;
		xmlDocPtr doc;
		char* verdict;
		int failures = 0;
		for (arg=1; arg<argc; arg++) {

			// workaround for a problem with libxml2 and MinGW
			safeXmlInitParser();

			// parse
			doc = xmlParseFile( argv[arg] );

			// check against schema
			if (isValidSBOL(doc) > 0)
				verdict = "yes";
			else {
				verdict = "no";
				failures++;
			}
			printf("%s conforms to SBOL schema? %s\n", argv[arg], verdict);

			// cleanup
			xmlFreeDoc(doc);
		}
		xmlCleanupParser();
		return failures;
	}
}
