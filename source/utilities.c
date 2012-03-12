#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

#define BUFFER_CHARS 100

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

int sameString(const char* string1, const char* string2) {
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

int sameContent(const char* filename1, const char* filename2) {
	FILE *fpread, *fpread2;	
	char  filebuff[BUFFER_CHARS];
	char filebuff2[BUFFER_CHARS];
	int var = 0;
	int linecount = 0;
	fpread  = fopen(filename1, "r");
	fpread2 = fopen(filename2, "r");
	while ( fgets(filebuff,  BUFFER_CHARS, fpread)  != NULL
		 && fgets(filebuff2, BUFFER_CHARS, fpread2) != NULL ) {
		++linecount;
		var = strcmp(filebuff, filebuff2);           
		if (var != 0){
			printf("mismatch:\n%s\n%s\n", filebuff, filebuff2);
			fclose(fpread);
			fclose(fpread2);
			return 0;
		}
	}
	fclose(fpread);
	fclose(fpread2);
	return 1;
}
