#ifndef SBOL_CORE_GENERICARRAY
#define SBOL_CORE_GENERICARRAY

typedef struct _GenericArray {
	int numInUse;
	int numTotal;
	void** array;
} GenericArray;

// work with the arrays
GenericArray* createGenericArray();
void deleteGenericArray(GenericArray* arr);
void resizeGenericArray(GenericArray* arr, int capacity);
int indexByPtr(const GenericArray* arr, const void* obj);
void insertIntoGenericArray(GenericArray* arr, void* obj);
void removeFromGenericArray(GenericArray* arr, int index);
void expandGenericArray(GenericArray* arr);
void shrinkGenericArray(GenericArray* arr);

#endif
