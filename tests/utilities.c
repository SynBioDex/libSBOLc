#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utilities.h"
#include <dirent.h>

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

int randomNumber(int max) {
    return rand() % max;
}

char** getFilenames(char* dirname) {
	struct dirent* ent;
	DIR* dir;
	int i;
	int numFiles;
	char*  filename;
	char** filenames;
	
	// count files
	// (excluding . and ..)
	numFiles = 0;
	dir = opendir(dirname);
	while (ent = readdir(dir)) {
		if (strcmp(ent->d_name, "." ) != 0
		 && strcmp(ent->d_name, "..") != 0) {
			numFiles++;
		 }
	}
	closedir(dir);
	
	// start an array
	filenames = malloc(sizeof(char*) * (numFiles+1));
	filenames[numFiles] = NULL;
	
	// add filenames to the array
	dir = opendir(dirname);
	for (i=0; i<numFiles;) {
		ent = readdir(dir);
		if (strcmp(ent->d_name, "." ) != 0
		 && strcmp(ent->d_name, "..") != 0) {
			filename = malloc(
					sizeof(char) * 
					(strlen(dirname) + strlen(ent->d_name) + 1)
				);
			strcpy(filename, dirname);
			strcat(filename, ent->d_name);
			filenames[i] = filename;
			i++;
		}
	}
	closedir(dir);
	return filenames;
}

