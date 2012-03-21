#ifndef SBOL_ARRAY_HEADER
#define SBOL_ARRAY_HEADER

#define POINTERARRAY_INITIAL_LENGTH 10
#define POINTERARRAY_SCALING_FACTOR  2

typedef struct _PointerArray {
	int numPointersInUse;
	int numPointersTotal;
	void** pointers;
} PointerArray;

PointerArray *createPointerArray();
void          deletePointerArray(PointerArray *arr);

void insertPointerIntoArray(PointerArray *arr, void *ptr);
void removePointerFromArray(PointerArray *arr, int index);

int    getNumPointersInArray(const PointerArray *arr);
void*   getNthPointerInArray(const PointerArray *arr, int n);
int    indexOfPointerInArray(const PointerArray *arr, const void *ptr);
int  pointerContainedInArray(const PointerArray *arr, const void *ptr);

#endif
