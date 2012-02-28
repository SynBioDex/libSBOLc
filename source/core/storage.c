#include <stdlib.h>
#include "storage.h"
// TODO reject (or replace?) duplicate IDs!

#define INITIAL_ARRAY_LENGTH 10
#define ARRAY_SCALING_FACTOR  2

/*****************************
 *	functions for operating
 *  on the global arrays
 *****************************/

GenericArray* createGenericArray() {
	GenericArray* arr = (GenericArray*)malloc(sizeof(GenericArray));
	arr->numInUse = 0;
	arr->numTotal = INITIAL_ARRAY_LENGTH;
	arr->array = (void**)malloc(sizeof(void*) * INITIAL_ARRAY_LENGTH);
	return arr;
}

void deleteGenericArray(GenericArray* arr) {
	if (arr) {
		if (arr->array) {
			free(arr->array);
			arr->array = NULL;
		}
		free(arr);
	}
}

int indexByPtr(const GenericArray* arr, const void* obj) {
	int index = 0;
	while (arr->array[index]) {
		if (arr->array[index] == obj)
			return index;
		else
			index++;
	}
	return -1;
}

void resizeArray(GenericArray* arr, int capacity) {
	if (capacity<INITIAL_ARRAY_LENGTH)
		return;
	arr->array = (void**)realloc(arr->array, capacity * sizeof(void*));
	arr->numTotal = capacity;
}

void expandArray(GenericArray* arr) {
	int capacity;
	if (arr->numTotal == 0) {
		capacity = INITIAL_ARRAY_LENGTH;
	} else
		capacity = arr->numTotal * ARRAY_SCALING_FACTOR;
	resizeArray(arr, capacity);
}

void shrinkArray(GenericArray* arr) {
	if (arr->numTotal>INITIAL_ARRAY_LENGTH*ARRAY_SCALING_FACTOR)
		resizeArray(arr, arr->numTotal / ARRAY_SCALING_FACTOR);
}

void removeFromArray(GenericArray* arr, int index) {
	// shift everything over
	int i;
	for (i=index+1; i<arr->numInUse; i++)
		arr->array[i-1] = arr->array[i];
	arr->array[ --(arr->numInUse) ] = NULL;
	// if array is getting empty, shrink it
	if (arr->numInUse == arr->numTotal/ARRAY_SCALING_FACTOR)
		shrinkArray(arr);
}

void insertIntoArray(GenericArray* arr, void* obj) {
	if (arr && obj) {
		// if array is full, expand it
		if (arr->numInUse == arr->numTotal)
			expandArray(arr);
		// insert obj
		arr->array[ arr->numInUse ] = obj;
		arr->numInUse++;
	}
}
