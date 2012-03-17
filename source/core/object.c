#include <stdlib.h>
#include "debug.h"
#include "property.h"
#include "genericarray.h"
#include "object.h"

// TODO will "object" conflict with other filenames?

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
		//free(obj); // TODO what's wrong with this?q
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

/****************************
 * SBOLObjects Global Array
 ****************************/

static GenericArray* allSBOLObjects;

void registerSBOLObject(SBOLObject* obj) {
	if (!allSBOLObjects)
		allSBOLObjects = createGenericArray();
	insertIntoGenericArray(allSBOLObjects, obj);
}

void removeSBOLObject(SBOLObject* obj) {
	if (obj && allSBOLObjects) {
		int index = indexByPtr(allSBOLObjects, obj);
		if (index >= 0)
			removeFromGenericArray(allSBOLObjects, index);
	}
}

int getNumSBOLObjects() {
	if (allSBOLObjects)
	    return allSBOLObjects->numInUse;
	else
	    return 0;
}

// TODO generalize this so it's not repeated everywhere
int isSBOLObjectURI(const char* uri) {
	if (!allSBOLObjects)
		allSBOLObjects = createGenericArray();
	if (!uri)
		return 0;
	int index;
	char* candidate;
	SBOLObject* obj;
	for (index=0; index<getNumSBOLObjects(); index++) {
		obj = getNthSBOLObject(index);
		candidate = getSBOLObjectURI(obj);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

SBOLObject* getNthSBOLObject(int n) {
	if (!allSBOLObjects || allSBOLObjects->numInUse<=n)
	    return NULL;
	else
	    return (SBOLObject*) getNthArrayElement(allSBOLObjects, n);
}

SBOLObject* getSBOLObject(const char* uri) {
	if (!allSBOLObjects)
		allSBOLObjects = createGenericArray();
	if (!uri)
		return NULL;
	int index;
	char* candidate;
	SBOLObject* obj;
	for (index=0; index<allSBOLObjects->numInUse; index++) {
		obj = (SBOLObject*) allSBOLObjects->array[index];
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
		deleteGenericArray(allSBOLObjects);
		allSBOLObjects = NULL;
	}
}

/**********************
 * SBOLCompoundObject
 **********************/

SBOLCompoundObject* createSBOLCompoundObject(const char* uri) {
	// TODO isDuplicateURI
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
	if (obj && id) {
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

/************************************
 * SBOLCompoundObjects GLobal Array
 ************************************/

static GenericArray* allSBOLCompoundObjects;

void registerSBOLCompoundObject(SBOLCompoundObject* obj) {
	if (!allSBOLCompoundObjects)
		allSBOLCompoundObjects = createGenericArray();
	insertIntoGenericArray(allSBOLCompoundObjects, obj);
}

void removeSBOLCompoundObject(SBOLCompoundObject* obj) {
	if (obj && allSBOLCompoundObjects) {
		int index = indexByPtr(allSBOLCompoundObjects, obj);
		if (index >= 0)
			removeFromGenericArray(allSBOLCompoundObjects, index);
	}
}

int getNumSBOLCompoundObjects() {
	if (allSBOLCompoundObjects)
	    return allSBOLCompoundObjects->numInUse;
	else
	    return 0;
}

int isSBOLCompoundObjectURI(const char* uri) {
	if (!allSBOLCompoundObjects)
		allSBOLCompoundObjects = createGenericArray();
	if (!uri)
		return 0;
	int index;
	char* candidate;
	SBOLCompoundObject* obj;
	for (index=0; index<getNumSBOLCompoundObjects(); index++) {
		obj = getNthSBOLCompoundObject(index);
		candidate = getSBOLCompoundObjectURI(obj);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

SBOLCompoundObject* getNthSBOLCompoundObject(int n) {
	if (!allSBOLCompoundObjects || allSBOLCompoundObjects->numInUse<=n)
	    return NULL;
	else
	    return (SBOLCompoundObject*) getNthArrayElement(allSBOLCompoundObjects, n);
}

SBOLCompoundObject* getSBOLCompoundObject(const char* uri) {
	if (!allSBOLCompoundObjects)
		allSBOLCompoundObjects = createGenericArray();
	if (!uri)
		return NULL;
	int index;
	char* candidate;
	SBOLCompoundObject* obj;
	for (index=0; index<allSBOLCompoundObjects->numInUse; index++) {
		obj = (SBOLCompoundObject*) allSBOLCompoundObjects->array[index];
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
		deleteGenericArray(allSBOLCompoundObjects);
		allSBOLCompoundObjects = NULL;
	}
}
