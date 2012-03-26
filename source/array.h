///////////////////////////////////////////////////////////
/// @file array.h
/// This file defines the PointerArray struct, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_ARRAY_HEADER
#define SBOL_ARRAY_HEADER

#define POINTERARRAY_INITIAL_LENGTH 10
#define POINTERARRAY_SCALING_FACTOR  2

/// A dynamic array of void pointers.
/// Used anywhere a variable number of
/// SBOLObjects needs to be stored, for
/// example in DNAComponent->annotations.
/// It could be called "SBOLObjectArray",
/// but you might want to store strings
/// or something instead.
typedef struct _PointerArray {
	int numPointersInUse;
	int numPointersTotal;
	void** pointers;
} PointerArray;

/// Create an empty PointerArray.
PointerArray *createPointerArray();

/// Delete a PointerArray.
/// This frees the array itself, but not the pointers.
void deletePointerArray(PointerArray *arr);

/// Add a new pointer to a PointerArray.
/// Anything works as long as you cast it to (void *)
void insertPointerIntoArray(PointerArray *arr, void *ptr);

/// Get a pointer from a PointerArray.
void removePointerFromArray(PointerArray *arr, int index);

/// Get the number of pointers stored in a PointerArray.
/// Returns -1 on failure.
int getNumPointersInArray(const PointerArray *arr);

/// Get the Nth pointer from a PointerArray.
/// Returns -1 on failure.
void* getNthPointerInArray(const PointerArray *arr, int n);

/// Get the index of a pointer stored in a PointerArray.
/// Returns -1 on failure, or if the pointer isn't found.
int indexOfPointerInArray(const PointerArray *arr, const void *ptr);

/// Find out whether a PointerArray contains a certain pointer.
/// Returns -1 on failure.
int pointerContainedInArray(const PointerArray *arr, const void *ptr);

#endif
