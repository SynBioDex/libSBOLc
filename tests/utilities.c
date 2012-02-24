#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utilities.h"

char randomChar()
{
	// TODO allow other characters?
	char* allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int index = rand() % strlen(allowed);
	return allowed[index];
}

char* randomString()
{
	int length = rand() % 100;
	char* string = malloc(sizeof(char*) * length);
	int i;
	for( i=0; i<length-1; i++ )
		string[i] = randomChar();
	string[length] = '\0';
	return string;
}
