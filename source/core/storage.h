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

// add to the arrays
void registerComponent(struct _DNAComponent* com);
void registerSequenceAnnotation(struct _SequenceAnnotation* ann);
void registerCollection(struct _Collection* col);

// work with the arrays
GenericArray* startGenericArray();
void resizeArray(GenericArray* arr, int capacity);
int indexByPtr(const GenericArray* arr, const void* obj);
void insertIntoArray(GenericArray* arr, void* obj);
void removeFromArray(GenericArray* arr, int index);
void expandArray(GenericArray* arr);
void shrinkArray(GenericArray* arr);

// check object type
int isComponentPtr(const void* pointer);
int isAnnotationPtr(const void* pointer);
int isCollectionPtr(const void* pointer);
int isComponentID(const char* id);
int isAnnotationID(const char* id);
int isCollectionID(const char* id);

// iterate through arrays
int getNumCollections();
int getNumDNAComponents();
int getNumSequenceAnnotations();
struct _Collection* getNthCollection(int n);
struct _DNAComponent* getNthDNAComponent(int n);
struct _SequenceAnnotation* getNthSequenceAnnotation(int n);

// delete everything
void cleanup();

#endif
