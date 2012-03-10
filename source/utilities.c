#include <string.h>
#include <stdlib.h>
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

char* intToStr(int input) {
	int i;
	int digits;
	int lastDigit;
	char* output;
	// determine number of digits
	digits = 0;
	i = input;
	while (i>0) {
		i /= 10;
		digits++;
	}
	if (digits==0) {
		// create a single-char string
		output = malloc(sizeof(char)*2);
		output[0] = (char) (((int)'0')+input);
		output[1] = '\0';
	} else {
		// create string to hold that many chars
		output = malloc(sizeof(char) * (digits+1));
		// copy over each digit as a char
		for (i=digits-1; i>=0; i--) {
			lastDigit = input%10;
			output[i] = (char) (((int)'0')+lastDigit);
			input /= 10;
		}
		output[digits] = '\0';
	}
	return output;
}
