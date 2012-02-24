#ifndef SBOL_CORE_COLLECTION
#define SBOL_CORE_COLLECTION
#include "common.h"

typedef struct _Collection
{
	char* id;
	char* name;
	char* description;
	struct _DNAComponent ** components; //pointer to multiple DNAComponents
	struct _Collection ** collections; //null terminated array
    int numComponents;
    int numCollections;
} Collection;

// create/destroy
SBOLAPIEXPORTS void createCollection(const char* id);
SBOLAPIEXPORTS void deleteCollection(Collection* col);

// iterate
SBOLAPIEXPORTS int getNumDNAComponentsIn(Collection col);
SBOLAPIEXPORTS DNAComponent getNthDNAComponentIn(Collection col, int n);

// set properties
SBOLAPIEXPORTS void setCollectionID(Collection * col, const char* id);
SBOLAPIEXPORTS void setCollectionName(Collection * col, const char* name);
SBOLAPIEXPORTS void setCollectionDescription(Collection * col, const char* desc);

// TODO where should this go?
// add component
SBOLAPIEXPORTS void addComponentToCollection(_DNAComponent * com, Collection * col);

#endif
