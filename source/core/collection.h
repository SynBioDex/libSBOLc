#ifndef SBOL_CORE_COLLECTION
#define SBOL_CORE_COLLECTION

struct _DNAComponent;
struct _GenericArray;

typedef struct _Collection {
	char* id;
	char* name;
	char* description;
	struct _GenericArray* components;
	struct _GenericArray* collections;
} Collection;

// create/destroy
Collection* createCollection(const char* id);
void deleteCollection(Collection* col);

// work with global array
int isCollectionPtr(const void* pointer);
int isCollectionID(const char* id);
int getNumCollections();
Collection* getNthCollection(int n);

// iterate
Collection* getCollection(const char* id);
int getNumDNAComponentsIn(Collection* col);
int getNumCollectionsIn(Collection* col);
struct _DNAComponent* getNthDNAComponentIn(Collection* col, int n);

// get properties
char* getCollectionID(Collection* col);
char* getCollectionName(Collection* col);
char* getCollectionDescription(Collection* col);

// set properties
void setCollectionID(Collection* col, const char* id); // TODO remove?
void setCollectionName(Collection* col, const char* name);
void setCollectionDescription(Collection* col, const char* desc);

// TODO where should this go?
// add component
void addDNAComponentToCollection(struct _DNAComponent* com, Collection* col);

void cleanupCollections();

#endif
