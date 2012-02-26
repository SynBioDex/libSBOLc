#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utilities.h"

#define MAX_STRING_LENGTH 1000

char randomChar() {
	// TODO allow other characters?
	// TODO #define this?
	char* allowed = " _-abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int index = rand() % strlen(allowed);
	return allowed[index];
}

char* randomString() {
	int length = rand() % MAX_STRING_LENGTH;
	char* string = malloc(sizeof(char*) * length);
	int i;
	for( i=0; i<length-1; i++ )
		string[i] = randomChar();
	string[length] = '\0';
	return string;
}
