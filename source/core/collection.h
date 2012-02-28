#ifndef SBOL_CORE_COLLECTION
#define SBOL_CORE_COLLECTION

struct _DNAComponent;

typedef struct _Collection {
	char* id;
	char* name;
	char* description;
    int numComponents;
    int numCollections;
	struct _DNAComponent** components;
	struct _Collection**  collections;
} Collection;

// create/destroy
Collection* createCollection(const char* id);
void deleteCollection(Collection* col);

// work with global array
void registerCollection(struct _Collection* col);
void removeCollection(struct _Collection* col);
int isCollectionPtr(const void* pointer);
int isCollectionID(const char* id);
int getNumCollections();
struct _Collection* getNthCollection(int n);

// iterate
int getNumDNAComponentsIn(Collection* col);
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
void addComponentToCollection(struct _DNAComponent* com, Collection* col);

void cleanupCollections();

#endif
