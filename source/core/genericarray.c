#include <stdlib.h>
#include "debug.h"
#include "genericarray.h"
// TODO reject (or replace?) duplicate IDs!

#define GENERICARRAY_INITIAL_LENGTH 10
#define GENERICARRAY_SCALING_FACTOR  2

/*****************************
 *	functions for operating
 *  on the global arrays
 *****************************/

GenericArray* createGenericArray() {
	GenericArray* arr = (GenericArray*)malloc(sizeof(GenericArray));
	arr->numInUse = 0;
	arr->numTotal = GENERICARRAY_INITIAL_LENGTH;
	arr->array = (void**)malloc(sizeof(void*) * GENERICARRAY_INITIAL_LENGTH);
	int num;
	for (num=0; num<arr->numInUse; num++)
		arr->array[num] = NULL;
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
	if (arr && obj) {
		int index;
		for (index=0; index<arr->numInUse; index++)
			if (arr->array[index] == obj)
				return index;
	}
	return -1;
}

int genericArrayContains(const GenericArray* arr, const void* obj) {
    return (int) indexByPtr(arr, obj) >= 0;
}

void resizeGenericArray(GenericArray* arr, int capacity) {
	if (arr) {
		if (capacity<GENERICARRAY_INITIAL_LENGTH)
			return;
		arr->array = (void**)realloc(arr->array, capacity * sizeof(void*));
		arr->numTotal = capacity;
	}
}

void expandGenericArray(GenericArray* arr) {
	if (arr) {
		int capacity;
		if (arr->numTotal == 0)
			capacity = GENERICARRAY_INITIAL_LENGTH;
		else
			capacity = arr->numTotal * GENERICARRAY_SCALING_FACTOR;
		resizeGenericArray(arr, capacity);
	}
}

void shrinkGenericArray(GenericArray* arr) {
	if (arr) {
		int minToShrink = GENERICARRAY_INITIAL_LENGTH*GENERICARRAY_SCALING_FACTOR;
		if (arr->numTotal>minToShrink)
			resizeGenericArray(arr, arr->numTotal / GENERICARRAY_SCALING_FACTOR);
	}
}

void removeFromGenericArray(GenericArray* arr, int index) {
	if (arr && arr->numInUse>index && index >= 0) {
		// shift everything over, deleting array[index]
		int i;
		for (i=index+1; i<arr->numInUse; i++)
			arr->array[i-1] = arr->array[i];
		arr->array[ --(arr->numInUse) ] = NULL;
		// if array is getting small, shrink it
		if (arr->numInUse == arr->numTotal/GENERICARRAY_SCALING_FACTOR)
			shrinkGenericArray(arr);
	}
}

void insertIntoGenericArray(GenericArray* arr, void* obj) {
	if (arr && obj) {
		// if array is full, expand it
		if (arr->numInUse == arr->numTotal)
			expandGenericArray(arr);
		// insert obj
		arr->array[ arr->numInUse ] = obj;
		arr->numInUse++;
	}
}

void* getNthArrayElement(const GenericArray* arr, int n) {
	if (!arr || arr->numInUse<=n)
	    return NULL;
	else
		return arr->array[n];
}
