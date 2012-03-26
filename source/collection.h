///////////////////////////////////////////////////////////
/// @file collection.h
/// This file defines the Collection object, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_COLLECTION_HEADER
#define SBOL_COLLECTION_HEADER
#include "api.h"

struct _SBOLCompoundObject;
struct _PointerArray;
struct _DNAComponent;

typedef struct _Collection {
	struct _SBOLCompoundObject* base;
	struct _PointerArray *components;
	struct _PointerArray *collections;
} Collection;

// create/destroy
Collection* createCollection(const char* uri);
void deleteCollection(Collection* col);

// work with global array
int isCollectionPtr(const void* pointer); // TODO rename and export
SBOLAPIEXPORTS int isCollectionURI(const char* uri);
SBOLAPIEXPORTS int getNumCollections();
SBOLAPIEXPORTS Collection* getNthCollection(int n);
SBOLAPIEXPORTS Collection* getNthCollectionInCollection(const Collection* col, int n);

// iterate
SBOLAPIEXPORTS Collection* getCollection(const char* uri);
SBOLAPIEXPORTS int getNumDNAComponentsIn(const Collection* col);
SBOLAPIEXPORTS int getNumCollectionsIn(const Collection* col);
SBOLAPIEXPORTS struct _DNAComponent* getNthDNAComponentIn(const Collection* col, int n);
// TODO more consistent naming
SBOLAPIEXPORTS Collection *getNthCollectionInCollection(const Collection *col, int n);

// get properties
SBOLAPIEXPORTS char* getCollectionURI(const Collection* col);
SBOLAPIEXPORTS char* getCollectionDisplayID(const Collection* col);
SBOLAPIEXPORTS char* getCollectionName(const Collection* col);
SBOLAPIEXPORTS char* getCollectionDescription(const Collection* col);

// set properties
SBOLAPIEXPORTS void setCollectionURI(Collection* col, const char* uri); // TODO remove?
SBOLAPIEXPORTS void setCollectionDisplayID(Collection* col, const char* id);
SBOLAPIEXPORTS void setCollectionName(Collection* col, const char* name);
SBOLAPIEXPORTS void setCollectionDescription(Collection* col, const char* desc);

// add component
SBOLAPIEXPORTS void addDNAComponentToCollection(struct _DNAComponent* com, Collection* col);
// TODO better name
SBOLAPIEXPORTS int  dnaComponentInCollection(const struct _DNAComponent *com, const Collection *col);

void printCollection(const Collection* col, int tabs);
void printAllCollections();

void cleanupCollections();

#endif
