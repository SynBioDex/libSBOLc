#ifndef SBOL_CORE_COLLECTION
#define SBOL_CORE_COLLECTION

struct _URIProperty;
struct _TextProperty;
struct _DNAComponent;
struct _GenericArray;

typedef struct _Collection {
	struct _URIProperty* uri;
	struct _TextProperty* displayID;
	struct _TextProperty* name;
	struct _TextProperty* description;
	struct _GenericArray* components;
	struct _GenericArray* collections;
	int processed;
} Collection;

// create/destroy
Collection* createCollection(const char* uri);
void deleteCollection(Collection* col);

// work with global array
int isCollectionPtr(const void* pointer);
int isCollectionURI(const char* uri);
int getNumCollections();
Collection* getNthCollection(int n);
Collection* getNthCollectionIn(const Collection* col, int n);

// iterate
Collection* getCollection(const char* uri);
int getNumDNAComponentsIn(const Collection* col);
int getNumCollectionsIn(const Collection* col);
struct _DNAComponent* getNthDNAComponentIn(const Collection* col, int n);

// get properties
char* getCollectionURI(const Collection* col);
char* getCollectionDisplayID(const Collection* col);
char* getCollectionName(const Collection* col);
char* getCollectionDescription(const Collection* col);

// set properties
void setCollectionURI(Collection* col, const char* uri); // TODO remove?
void setCollectionDisplayID(Collection* col, const char* id);
void setCollectionName(Collection* col, const char* name);
void setCollectionDescription(Collection* col, const char* desc);

// TODO where should this go?
// add component
void addDNAComponentToCollection(struct _DNAComponent* com, Collection* col);

void printCollection(const Collection* col, int tabs);
void printAllCollections();

void cleanupCollections();

#endif
