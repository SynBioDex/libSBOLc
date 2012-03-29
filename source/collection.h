///////////////////////////////////////////////////////////
/// @file collection.h
/// This file defines the Collection struct, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_COLLECTION_HEADER
#define SBOL_COLLECTION_HEADER

// forward declarations
struct _SBOLCompoundObject;
struct _PointerArray;
struct _DNAComponent;

/// Implements the SBOL Core Collection object.
typedef struct _Collection {
	struct _SBOLCompoundObject* base;  ///< uri, displayID, name, description
	struct _PointerArray *components;  ///< array of DNAComponents
} Collection;

/// Create an empty Collection.
Collection* createCollection(const char* uri);

/// Delete a Collection.
/// This doesn't delete any of the other structs
/// it references. For that you want cleanupSBOLCore.
void deleteCollection(Collection* col);

// Find out whether *pointer is registered as a Collection.
int isCollectionPtr(const void* pointer); // @todo rename and export?

/// Find out if there's a Collection with this uri.
int isCollectionURI(const char* uri);

/// Get the Collection associated with this uri.
/// Returns NULL on failure.
Collection* getCollection(const char* uri);

/// Get the total number of Collections.
/// Useful as a loop condition.
int getNumCollections();

/// Get the Nth Collection.
/// Useful for iterating over all of them.
Collection* getNthCollection(int n);

/// Get the Nth Collection inside a given Collection.
/// @todo better name
Collection* getNthCollectionInCollection(const Collection* col, int n);

/// Get the number of DNAComponents in a Collection.
int getNumDNAComponentsIn(const Collection* col);

/// Get the Nth DNAComponent inside a Collection.
struct _DNAComponent* getNthDNAComponentIn(const Collection* col, int n);

/// Get the uri of a Collection.
char* getCollectionURI(const Collection* col);

/// Get the displayID of a Collection.
/// Note that this is different from both name and displayID.
char* getCollectionDisplayID(const Collection* col);

/// Get the name of a Collection.
/// Note that this is different from both uri and displayID.
char* getCollectionName(const Collection* col);

/// Get the description of a Collection.
char* getCollectionDescription(const Collection* col);

/// Set the uri of a Collection.
/// @todo remove this? is there any reason to change uris?
void setCollectionURI(Collection* col, const char* uri);

/// Set the displayID of a Collection.
/// Note that this is different from both name and displayID.
void setCollectionDisplayID(Collection* col, const char* id);

/// Set the name of a Collection.
/// Note that this is different from both uri and displayID.
void setCollectionName(Collection* col, const char* name);

/// Set the description of a Collection.
void setCollectionDescription(Collection* col, const char* desc);

/// Add a DNAComponent to a Collection.
void addDNAComponentToCollection(struct _DNAComponent* com, Collection* col);

/// Find out whether a DNAComponent is inside a Collection.
/// @todo better name
int dnaComponentInCollection(const struct _DNAComponent *com, const Collection *col);

/// Print an outline of a Collection to stdout.
/// Mainly for debugging.
void printCollection(const Collection* col, int tabs);

/// Print an outline of all the Collections to stdout.
/// Mainly for debugging.
void printAllCollections();

/// Delete all Collections.
/// To delete everything instead, use cleanupSBOLCore.
/// @todo remove this? is it ever used?
void cleanupCollections();

#endif
