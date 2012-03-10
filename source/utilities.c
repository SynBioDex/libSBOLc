#include <string.h>
#include "utilities.h"

char* getExtension(char* filename) {
	if (!filename)
		return NULL;
	int i;
	int len;
	char* ext;
	// determine index of dot
	len = strlen(filename);
	for (i=len-1; i>=0; i--) {
		if (filename[i] == '.') {
			i++; // don't include the dot itself
			break;
		}
	}
	if (i==0)
		return NULL;
	// return chars after dot
	// TODO is returning part of the same string dangerous?
	return &filename[i];
}

int sameString(char* string1, char* string2) {
	if (!string1 || !string2)
		return 0;
	else
		return (int) strcmp(string1, string2) == 0;
}
