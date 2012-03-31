///////////////////////////////////////////////////////////
/// @file object.h
/// This file defines the SBOLObject struct, as well as
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
	URIProperty* uri;
};

SBOLObject* createSBOLObject(const char* uri);
void        deleteSBOLObject(SBOLObject* obj);

// TODO remove once it's clear these aren't needed
int getNumSBOLObjects();
int isSBOLObjectURI(const char* uri);
SBOLObject* getNthSBOLObject(int n);
SBOLObject* getSBOLObject(const char* uri);
void registerSBOLObject(SBOLObject* obj);
void removeSBOLObject(SBOLObject* obj);
void cleanupSBOLObjects();

void  setSBOLObjectURI(SBOLObject* obj, const char* uri);
char* getSBOLObjectURI(const SBOLObject* obj);

/**********************
 * SBOLCompoundObject
 **********************/

/// SBOLObject that also includes a name,
/// displayID, and description.
/// Used a basis for DNAComponent and Collection.
struct _SBOLCompoundObject {
	SBOLObject*   base;
	TextProperty* displayID;
	TextProperty* name;
	TextProperty* description;
};

// TODO remove once it's clear these aren't needed
int getNumSBOLCompoundObjects();
int isSBOLCompoundObjectURI(const char* uri);
SBOLCompoundObject* getNthSBOLCompoundObject(int n);
SBOLCompoundObject* getSBOLCompoundObject(const char* uri);
void registerSBOLCompoundObject(SBOLCompoundObject* obj);
void removeSBOLCompoundObject(SBOLCompoundObject* obj);
void cleanupSBOLCompoundObjects();

SBOLCompoundObject* createSBOLCompoundObject(const char* uri);
void                deleteSBOLCompoundObject(SBOLCompoundObject* obj);

void  setSBOLCompoundObjectURI(SBOLCompoundObject* obj, const char* uri);
char* getSBOLCompoundObjectURI(const SBOLCompoundObject* obj);

void  setSBOLCompoundObjectDisplayID(SBOLCompoundObject* obj, const char* id);
char* getSBOLCompoundObjectDisplayID(const SBOLCompoundObject* obj);

void  setSBOLCompoundObjectName(SBOLCompoundObject* obj, const char* name);
char* getSBOLCompoundObjectName(const SBOLCompoundObject* obj);

void  setSBOLCompoundObjectDescription(SBOLCompoundObject* obj, const char* descr);
char* getSBOLCompoundObjectDescription(const SBOLCompoundObject* obj);

#endif
