#ifndef SBOL_CORE_STORAGE
#define SBOL_CORE_STORAGE

struct _DNAComponent;
struct _SequenceAnnotation;
struct _Collection;

typedef struct _GenericArray {
	int numInUse;
	int numTotal;
	void** array;
} GenericArray;

// work with the arrays
GenericArray* createGenericArray();
void deleteGenericArray(GenericArray* arr);
void resizeArray(GenericArray* arr, int capacity);
int indexByPtr(const GenericArray* arr, const void* obj);
void insertIntoArray(GenericArray* arr, void* obj);
void removeFromArray(GenericArray* arr, int index);
void expandArray(GenericArray* arr);
void shrinkArray(GenericArray* arr);

#endif
