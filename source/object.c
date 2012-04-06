#include <stdlib.h>

#include "property.h"
#include "array.h"
#include "object.h"

/***********************************************************
 * SBOLObjects Static Array
 * 
 * This stores pointers to all the SBOLObjects in memory
 * for searching and cleanup.
 ***********************************************************/

static PointerArray* allSBOLObjects;

static void lazyCreateAllSBOLObjects() {
	if (!allSBOLObjects)
		allSBOLObjects = createPointerArray();
}

static void registerSBOLObject(SBOLObject* obj) {
	lazyCreateAllSBOLObjects();
	insertPointerIntoArray(allSBOLObjects, obj);
}

static void removeSBOLObject(SBOLObject* obj) {
	if (obj && allSBOLObjects) {
		int index = indexOfPointerInArray(allSBOLObjects, obj);
		if (index >= 0)
			removePointerFromArray(allSBOLObjects, index);
	}
}

int getNumSBOLObjects() {
	if (allSBOLObjects)
	    return getNumPointersInArray(allSBOLObjects);
	else
	    return 0;
}

/// @todo generalize this so it's not repeated everywhere
int isSBOLObjectURI(const char* uri) {
	lazyCreateAllSBOLObjects();
	if (!uri)
		return 0;
	int n;
	char* candidate;
	SBOLObject* obj;
	for (n=0; n < getNumSBOLObjects(); n++) {
		obj = getNthSBOLObject(n);
		candidate = getSBOLObjectURI(obj);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

SBOLObject* getNthSBOLObject(int n) {
	if (getNumSBOLObjects() > n)
		return (SBOLObject*) getNthPointerInArray(allSBOLObjects, n);
	else
		return NULL;
}

SBOLObject* getSBOLObject(const char* uri) {
	lazyCreateAllSBOLObjects();
	if (!uri)
		return NULL;
	int n;
	char* candidate;
	SBOLObject* obj;
	for (n=0; n < getNumSBOLObjects(); n++) {
		obj = (SBOLObject*) getNthSBOLObject(n);
		candidate = getSBOLObjectURI(obj);
		if (candidate && strcmp(candidate, uri) == 0)
			return obj;
	}
	return NULL;
}

void cleanupSBOLObjects() {
	if (allSBOLObjects) {
		int n;
		SBOLObject* obj;
		for (n=getNumSBOLObjects()-1; n>=0; n--) {
			obj = getNthSBOLObject(n);
			deleteSBOLObject(obj);
		}
		deletePointerArray(allSBOLObjects);
		allSBOLObjects = NULL;
	}
}

/**************
 * SBOLObject
 **************/

SBOLObject* createSBOLObject(const char* uri) {
	if (!uri || isSBOLObjectURI(uri))
		return NULL;
	SBOLObject* obj = malloc(sizeof(SBOLObject));
	obj->uri = createURIProperty();
	setSBOLObjectURI(obj, uri);
	registerSBOLObject(obj);
	return obj;
}

void deleteSBOLObject(SBOLObject* obj) {
	if (obj) {
		if (obj->uri) {
			deleteURIProperty(obj->uri);
			obj->uri = NULL;
		}
		removeSBOLObject(obj);
		//free(obj); /// @todo what's wrong with this?
		obj = NULL;
	}
}

void setSBOLObjectURI(SBOLObject* obj, const char* uri) {
	if (obj && uri)
		setURIProperty(obj->uri, uri);
}

char* getSBOLObjectURI(const SBOLObject* obj) {
	if (obj)
		return getURIProperty(obj->uri);
	else
		return NULL;
}

/***********************************************************
 * SBOLCompoundObjects Static Array
 * 
 * This stores pointers to all the SBOLCompoundObjects
 * in memory for searching and cleanup.
 ***********************************************************/

static PointerArray* allSBOLCompoundObjects;

static void lazyCreateAllSBOLCompoundObjects() {
	if (!allSBOLCompoundObjects)
		allSBOLCompoundObjects = createPointerArray();
}

static void registerSBOLCompoundObject(SBOLCompoundObject* obj) {
	lazyCreateAllSBOLCompoundObjects();
	insertPointerIntoArray(allSBOLCompoundObjects, obj);
}

static void removeSBOLCompoundObject(SBOLCompoundObject* obj) {
	if (obj && allSBOLCompoundObjects) {
		int index = indexOfPointerInArray(allSBOLCompoundObjects, obj);
		if (index >= 0)
			removePointerFromArray(allSBOLCompoundObjects, index);
	}
}

int getNumSBOLCompoundObjects() {
	if (allSBOLCompoundObjects)
	    return getNumPointersInArray(allSBOLCompoundObjects);
	else
	    return 0;
}

int isSBOLCompoundObjectURI(const char* uri) {
	lazyCreateAllSBOLCompoundObjects();
	if (!uri)
		return 0;
	int n;
	char* candidate;
	SBOLCompoundObject* obj;
	for (n=0; n < getNumSBOLCompoundObjects(); n++) {
		obj = getNthSBOLCompoundObject(n);
		candidate = getSBOLCompoundObjectURI(obj);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

SBOLCompoundObject* getNthSBOLCompoundObject(int n) {
	if (getNumSBOLCompoundObjects() > n && n >= 0)
		return (SBOLCompoundObject *)getNthPointerInArray(allSBOLCompoundObjects, n);
	else
		return NULL;
}

SBOLCompoundObject* getSBOLCompoundObject(const char* uri) {
	lazyCreateAllSBOLCompoundObjects();
	if (!uri)
		return NULL;
	int n;
	char* candidate;
	SBOLCompoundObject* obj;
	for (n=0; n < getNumSBOLCompoundObjects(); n++) {
		obj = getNthSBOLCompoundObject(n);
		candidate = getSBOLCompoundObjectURI(obj);
		if (candidate && strcmp(candidate, uri) == 0)
			return obj;
	}
	return NULL;
}

void cleanupSBOLCompoundObjects() {
	if (allSBOLCompoundObjects) {
		int n;
		SBOLCompoundObject* obj;
		for (n=getNumSBOLCompoundObjects()-1; n>=0; n--) {
			obj = getNthSBOLCompoundObject(n);
			deleteSBOLCompoundObject(obj);
		}
		deletePointerArray(allSBOLCompoundObjects);
		allSBOLCompoundObjects = NULL;
	}
}

/**********************
 * SBOLCompoundObject
 **********************/

SBOLCompoundObject* createSBOLCompoundObject(const char* uri) {
	if (!uri || isSBOLCompoundObjectURI(uri) || isSBOLObjectURI(uri))
		return NULL;
	SBOLCompoundObject* obj = malloc(sizeof(SBOLCompoundObject));
	obj->base        = createSBOLObject(uri);
	obj->displayID   = createTextProperty();
	obj->name        = createTextProperty();
	obj->description = createTextProperty();
	registerSBOLCompoundObject(obj);
	return obj;
}

void deleteSBOLCompoundObject(SBOLCompoundObject* obj) {
	if (obj) {
		if (obj->base) {
			deleteSBOLObject(obj->base);
			obj->base = NULL;
		}
		if (obj->displayID) {
			deleteTextProperty(obj->displayID);
			obj->displayID = NULL;
		}
		if (obj->name) {
			deleteTextProperty(obj->name);
			obj->name = NULL;
		}
		if (obj->description) {
			deleteTextProperty(obj->description);
			obj->description = NULL;
		}
		removeSBOLCompoundObject(obj);
		free(obj);
		obj = NULL;
	}
}

void setSBOLCompoundObjectURI(SBOLCompoundObject* obj, const char* uri) {
	if (obj)
		setSBOLObjectURI(obj->base, uri);
}

char* getSBOLCompoundObjectURI(const SBOLCompoundObject* obj) {
	if (obj)
		return getSBOLObjectURI(obj->base);
	else
		return NULL;
}

void setSBOLCompoundObjectDisplayID(SBOLCompoundObject* obj, const char* id) {
	if (obj) {
		setTextProperty(obj->displayID, id);
	}
}

char* getSBOLCompoundObjectDisplayID(const SBOLCompoundObject* obj) {
	if (obj)
		return getTextProperty(obj->displayID);
	else
		return NULL;
}

void setSBOLCompoundObjectName(SBOLCompoundObject* obj, const char* name) {
	if (obj) {
		setTextProperty(obj->name, name);
	}
}

char* getSBOLCompoundObjectName(const SBOLCompoundObject* obj) {
	if (obj)
		return getTextProperty(obj->name);
	else
		return NULL;
}

void setSBOLCompoundObjectDescription(SBOLCompoundObject* obj, const char* descr) {
	if (obj) {
		setTextProperty(obj->description, descr);
	}
}

char* getSBOLCompoundObjectDescription(const SBOLCompoundObject* obj) {
	if (obj)
		return getTextProperty(obj->description);
	else
		return NULL;
}

