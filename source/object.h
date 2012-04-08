///////////////////////////////////////////////////////////
/// @file
/// Defines the SBOLObject struct, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_OBJECT_HEADER
#define SBOL_OBJECT_HEADER

#include "constants.h"
#include "prototypes.h"

/**************
 * SBOLObject
 **************/

/// A simple struct that just holds a uri so far.
/// Used as a makeshift "base class" for DNASequence, 
/// SequenceAnnotation, DNAComponent, and Collection.
/// This is where to put anything that needs to be 
/// accessible from each of the four main structs.
struct _SBOLObject {
	URIProperty* uri; ///< Unique string for identification.
};

/// Create an empty SBOLObject.
/// @return A pointer to the new SBOLObject.
SBOLObject* createSBOLObject(Document* doc, const char* uri);

/// Delete an SBOLObject.
/// This shouldn't be called directly;
/// instead, use deleteDNASequence, deleteCollection, etc.
void deleteSBOLObject(SBOLObject* obj);

/// Get the total number of SBOLObjects in memory.
/// This includes the ones that are contained in other structs.
/// @todo rename to reflect doc
//SBOLAPIEXPORTS int getNumSBOLObjects(Document* doc);

/// Delete all SBOLObjects from memory.
/// @todo remove this? is it ever used?
/// @todo rename to reflect doc
SBOLAPIEXPORTS void cleanupSBOLObjects(Document* doc);

/// Set the URI of an SBOLObject.
/// This shouldn't be called directly.
void setSBOLObjectURI(SBOLObject* obj, const char* uri);

/// Get the URI of an SBOLObject.
/// This shouldn't be called directly.
char* getSBOLObjectURI(const SBOLObject* obj);

/**********************
 * SBOLCompoundObject
 **********************/

/// SBOLObject that also includes a name,
/// displayID, and description.
/// Used a base struct for DNAComponent and Collection.
struct _SBOLCompoundObject {
	SBOLObject*   base;        ///< uri
	TextProperty* displayID;   ///< Like the uri but for display purposes. Not necessarily unique.
	TextProperty* name;        ///< Like the uri but human-readable. Not necessarily unique.
	TextProperty* description; ///< Some text describing the object.
};

/// Create an empty SBOLCompoundObject.
/// @return A pointer to the new SBOLCompoundObject.
/// @todo rename to reflect doc
SBOLCompoundObject* createSBOLCompoundObject(Document* doc, const char* uri);

/// Delete an SBOLObject.
/// This shouldn't be called directly;
/// instead, use deleteDNAComponent, deleteCollection, etc.
void deleteSBOLCompoundObject(SBOLCompoundObject* obj);

/// Set the URI of an SBOLComoundObject.
/// This shouldn't be called directly.
void setSBOLCompoundObjectURI(SBOLCompoundObject* obj, const char* uri);

/// Get the URI of an SBOLCompoundObject.
/// This shouldn't be called directly.
char* getSBOLCompoundObjectURI(const SBOLCompoundObject* obj);

/// Set the displayID of an SBOLCompoundObject.
/// This shouldn't be called directly.
/// Gotcha: uppercase D
void setSBOLCompoundObjectDisplayID(SBOLCompoundObject* obj, const char* id);

/// Get the URI of an SBOLCompoundObject.
/// This shouldn't be called directly.
/// Gotcha: uppercase D
char* getSBOLCompoundObjectDisplayID(const SBOLCompoundObject* obj);

/// Set the name of an SBOLCompoundObject.
/// This shouldn't be called directly.
void setSBOLCompoundObjectName(SBOLCompoundObject* obj, const char* name);

/// Get the name of an SBOLCompoundObject.
/// This shouldn't be called directly.
char* getSBOLCompoundObjectName(const SBOLCompoundObject* obj);

/// Set the description of an SBOLCompoundObject.
/// This shouldn't be called directly.
void setSBOLCompoundObjectDescription(SBOLCompoundObject* obj, const char* descr);

/// Get the description of an SBOLCompoundObject.
/// This shouldn't be called directly.
char* getSBOLCompoundObjectDescription(const SBOLCompoundObject* obj);

#endif
