///////////////////////////////////////////////////////////
/// @file
/// Defines the Collection struct, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_COLLECTION_HEADER
#define SBOL_COLLECTION_HEADER

#include "constants.h"
#include "prototypes.h"

/// Implements the SBOL Core Collection object.
struct _Collection {
	SBOLCompoundObject* base;  ///< uri, displayID, name, description
	PointerArray* components;  ///< array of DNAComponents
};

/// Create an empty Collection.
SBOLAPIEXPORTS Collection* createCollection(const char* uri);

/// Delete a Collection.
/// This doesn't delete any of the other structs
/// it references; For that you want cleanupSBOLCore.
SBOLAPIEXPORTS void deleteCollection(Collection* col);

/// Find out whether this pointer points to a Collection.
SBOLAPIEXPORTS int isCollection(const void* pointer);

/// Find out if there's a Collection with this uri.
SBOLAPIEXPORTS int isCollectionURI(const char* uri);

/// Get the Collection associated with this uri.
/// Returns NULL on failure.
SBOLAPIEXPORTS Collection* getCollection(const char* uri);

/// Get the total number of Collections.
/// Useful as a loop condition.
SBOLAPIEXPORTS int getNumCollections();

/// Get the Nth Collection.
/// Useful for iterating over all of them.
SBOLAPIEXPORTS Collection* getNthCollection(int n);

/// Get the number of DNAComponents in a Collection.
SBOLAPIEXPORTS int getNumDNAComponentsIn(const Collection* col);

/// Get the Nth DNAComponent inside a Collection.
SBOLAPIEXPORTS DNAComponent* getNthDNAComponentIn(const Collection* col, int n);

/// Get the uri of a Collection.
/// Gotcha: this is different from both name and displayID.
SBOLAPIEXPORTS char* getCollectionURI(const Collection* col);

/// Get the displayID of a Collection.
/// Gotcha: this is different from both uri and name.
/// Gotcha: uppercase D
SBOLAPIEXPORTS char* getCollectionDisplayID(const Collection* col);

/// Get the name of a Collection.
/// Gotcha: this is different from both uri and displayID.
SBOLAPIEXPORTS char* getCollectionName(const Collection* col);

/// Get the description of a Collection.
SBOLAPIEXPORTS char* getCollectionDescription(const Collection* col);

/// Set the displayID of a Collection.
/// Gotcha: this is different from both name and displayID.
SBOLAPIEXPORTS void setCollectionDisplayID(Collection* col, const char* id);

/// Set the name of a Collection.
/// Gotcha: this is different from both uri and displayID.
SBOLAPIEXPORTS void setCollectionName(Collection* col, const char* name);

/// Set the description of a Collection.
SBOLAPIEXPORTS void setCollectionDescription(Collection* col, const char* desc);

/// Add a DNAComponent to a Collection.
/// @todo move to dnacomponent.h?
SBOLAPIEXPORTS void addDNAComponentToCollection(Collection* col, DNAComponent* com);

/// Find out whether a DNAComponent is inside a Collection.
/// @todo better name
/// Gotcha: lowercase dna
SBOLAPIEXPORTS int dnaComponentInCollection(const DNAComponent* com, const Collection* col);

/// Print an outline of a Collection to stdout.
SBOLAPIEXPORTS void printCollection(const Collection* col, int tabs);

/// Print an outline of all the Collections to stdout.
SBOLAPIEXPORTS void printAllCollections();

/// Delete all Collections.
/// To delete everything instead, use cleanupSBOLCore.
/// @todo remove this? is it ever used?
SBOLAPIEXPORTS void cleanupCollections();

#endif
