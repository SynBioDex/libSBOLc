#ifndef SBOL_CORE_COLLECTION
#define SBOL_CORE_COLLECTION

struct _Property;
struct _DNAComponent;
struct _GenericArray;

typedef struct _Collection {
	struct _Property* id;
	struct _Property* name;
	struct _Property* description;
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
Collection* getNthCollectionIn(const Collection* col, int n);

// iterate
Collection* getCollection(const char* id);
int getNumDNAComponentsIn(const Collection* col);
int getNumCollectionsIn(const Collection* col);
struct _DNAComponent* getNthDNAComponentIn(const Collection* col, int n);

// get properties
char* getCollectionID(const Collection* col);
char* getCollectionName(const Collection* col);
char* getCollectionDescription(const Collection* col);

// set properties
void setCollectionID(Collection* col, const char* id); // TODO remove?
void setCollectionName(Collection* col, const char* name);
void setCollectionDescription(Collection* col, const char* desc);

// TODO where should this go?
// add component
void addDNAComponentToCollection(struct _DNAComponent* com, Collection* col);

void printCollection(const Collection* col, int tabs);
void printAllCollections();

void cleanupCollections();

#endif
