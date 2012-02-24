#ifndef SBOL_CORE_COLLECTION
#define SBOL_CORE_COLLECTION
#include "component.h"

// TODO move includes to implementation

struct _DNAComponent;

typedef struct _Collection
{
	char* id;
	char* name;
	char* description;
	struct DNAComponent** components; //pointer to multiple DNAComponents
	struct _Collection** collections; //null terminated array
    int numComponents;
    int numCollections;
} Collection;

// create/destroy
void createCollection(const char* id);
void deleteCollection(Collection* col);

// iterate
int getNumDNAComponentsIn(Collection col);
struct _DNAComponent getNthDNAComponentIn(Collection col, int n);

// set properties
void setCollectionID(Collection * col, const char* id);
void setCollectionName(Collection * col, const char* name);
void setCollectionDescription(Collection * col, const char* desc);

// TODO where should this go?
// add component
void addComponentToCollection(struct _DNAComponent* com, Collection * col);

#endif
