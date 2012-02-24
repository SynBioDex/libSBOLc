#ifndef SBOL_CORE_COLLECTION
#define SBOL_CORE_COLLECTION
#include "core_common.h"

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

SBOLAPIEXPORTS void createCollection(const char* id);
SBOLAPIEXPORTS void deleteCollection(Collection* col);

SBOLAPIEXPORTS int getNumDNAComponentsIn(Collection col);
SBOLAPIEXPORTS DNAComponent getNthDNAComponentIn(Collection col, int n);

SBOLAPIEXPORTS void setCollectionID(Collection * col, const char* id);
SBOLAPIEXPORTS void setCollectionName(Collection * col, const char* name);
SBOLAPIEXPORTS void setCollectionDescription(Collection * col, const char* desc);

SBOLAPIEXPORTS void addComponentToCollection(_DNAComponent * com, Collection * col);

#endif
