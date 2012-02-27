#include <stdlib.h>
#include "storage.h"
#include "component.h"
#include "annotation.h"
#include "collection.h"
// TODO include sequence?

#define INITIAL_ARRAY_LENGTH 10
#define ARRAY_SCALING_FACTOR  2

/******************
 *	global arrays
 ******************/

static GenericArray* allComponents;
static GenericArray* allAnnotations;
static GenericArray* allCollections;

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

/**************************
 *	register... functions
 **************************/

void registerComponent(struct _DNAComponent* com) {
	if (!allComponents)
		allComponents = createGenericArray();
	insertIntoArray(allComponents, com);
}

void registerSequenceAnnotation(struct _SequenceAnnotation* ann) {
	if (!allAnnotations)
		allAnnotations = createGenericArray();
	insertIntoArray(allAnnotations, ann);
}

void registerCollection(struct _Collection* col) {
	if (!allCollections)
		allCollections = createGenericArray();
	insertIntoArray(allCollections, col);
}

/**************************
 *	remove... functions
 **************************/
 
void removeComponent(struct _DNAComponent* com) {
	if (!allComponents)
		allComponents = createGenericArray();
	int index = indexByPtr(allComponents, com);
	if (index >= 0)
		removeFromArray(allComponents, index);
}

void removeAnnotation(struct _SequenceAnnotation* ann) {
	if (!allAnnotations)
		allAnnotations = createGenericArray();
	int index = indexByPtr(allAnnotations, ann);
	if (index >= 0)
		removeFromArray(allAnnotations, index);
}

void removeCollection(struct _Collection* col) {
	if (!allCollections)
		allCollections = createGenericArray();
	int index = indexByPtr(allCollections, col);
	if (index >= 0)
		removeFromArray(allCollections, index);
}

/**************************
 *	is... functions
 **************************/

int isComponentPtr(const void* pointer) {
	if (!allComponents)
		allComponents = createGenericArray();
	return (int) indexByPtr(allComponents, pointer) >= 0;
}

int isAnnotationPtr(const void* pointer) {
	if (!allAnnotations)
		allAnnotations = createGenericArray();
	return (int) indexByPtr(allAnnotations, pointer) >= 0;
}

int isCollectionPtr(const void* pointer) {
	if (!allCollections)
		allCollections = createGenericArray();
	return (int) indexByPtr(allCollections, pointer) >= 0;
}

int isComponentID(const char* id) {
	if (!allComponents)
		allComponents = createGenericArray();
	if (!id)
		return -1;
	int index;
	struct _DNAComponent* com;
	for (index=0; index<allComponents->numInUse; index++) {
		com = (struct _DNAComponent*) allComponents->array[index];
		if (strcmp(com->id, id) == 0)
			return 1;
	}
	return 0;
}

int isSequenceAnnotationID(const char* id) {
	if (!allAnnotations)
		allAnnotations = createGenericArray();
	if (!id)
		return -1;
	int index;
	SequenceAnnotation* ann;
	for (index=0; index<allAnnotations->numInUse; index++) {
		ann = (SequenceAnnotation*) allAnnotations->array[index];
		if (strcmp(ann->id, id) == 0)
			return 1;
	}
	return 0;
}

int isCollectionID(const char* id) {
	if (!allCollections)
		allCollections = createGenericArray();
	if (!id)
		return -1;
	int index;
	Collection* col;
	for (index=0; index<allCollections->numInUse; index++) {
		col = (Collection*) allCollections->array[index];
		if (strcmp(col->id, id) == 0)
			return 1;
	}
	return 0;
}

/**************************
 *	getNum... functions
 **************************/

int getNumDNAComponents() {
	if (!allComponents)
		allComponents = createGenericArray();
	return allComponents->numInUse;
}

int getNumSequenceAnnotations() {
	if (!allAnnotations)
		allAnnotations = createGenericArray();
	return allAnnotations->numInUse;
}

int getNumCollections() {
	if (!allCollections)
		allCollections = createGenericArray();
	return allCollections->numInUse;
}

/**************************
 *	getNth... functions
 **************************/

DNAComponent* getNthDNAComponent(int n) {
	if (!allComponents)
		allComponents = createGenericArray();
	if (allComponents->numInUse > n)
		return allComponents->array[n];
	else
		return NULL;
}

SequenceAnnotation* getNthSequenceAnnotation(int n) {
	if (!allAnnotations)
		allAnnotations = createGenericArray();
	if (allAnnotations->numInUse > n)
		return allAnnotations->array[n];
	else
		return NULL;
}

Collection* getNthCollection(int n) {
	if (!allCollections)
		allCollections = createGenericArray();
	if (allCollections->numInUse > n)
		return allCollections->array[n];
	else
		return NULL;
}

/**************************
 *	get... functions
 **************************/

DNAComponent* getComponent(const char* id) {
	if (!allComponents)
		allComponents = createGenericArray();
	if (!id)
		return NULL;
	int index;
	struct _DNAComponent* com;
	for (index=0; index<allComponents->numInUse; index++) {
		com = (struct _DNAComponent*) allComponents->array[index];
		if (com->id == id)
			return com;
	}
	return NULL;
}

SequenceAnnotation* getSequenceAnnotation(const char* id) {
	if (!allAnnotations)
		allAnnotations = createGenericArray();
	if (!id)
		return NULL;
	int index;
	struct _SequenceAnnotation* ann;
	for (index=0; index<allAnnotations->numInUse; index++) {
		ann = (struct _SequenceAnnotation*) allAnnotations->array[index];
		if (ann->id == id)
			return ann;
	}
	return NULL;
}

Collection* getCollection(const char* id) {
	if (!allCollections)
		allCollections = createGenericArray();
	if (!id)
		return NULL;
	int index;
	struct _Collection* col;
	for (index=0; index<allCollections->numInUse; index++) {
		col = (struct _Collection*) allCollections->array[index];
		if (col->id == id)
			return col;
	}
	return NULL;
}

/**************************
 *	free memory
 **************************/

void cleanup() {
	int index;
	// delete components
	for (index=0; allComponents->array[index]; index++) {
		deleteComponent(allComponents->array[index]);
	}
	// delete annotations
	for (index=0; allAnnotations->array[index]; index++) {
		if (!allAnnotations)
			allAnnotations = createGenericArray();
		deleteSequenceAnnotation(allAnnotations->array[index]);
	}
	// delete collections
	for (index=0; allCollections->array[index]; index++) {
		deleteCollection(allCollections->array[index]);
	}
	// delete arrays?
}
