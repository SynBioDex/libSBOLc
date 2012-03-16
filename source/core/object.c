#include <stdlib.h>
#include "debug.h"
#include "property.h"
#include "genericarray.h"
#include "object.h"

// TODO global arrays for these too?
// (not unless there's some benefit)
// TODO will "object" conflict with other filenames?

/**************
 * SBOLObject
 **************/

SBOLObject* createSBOLObject(const char* uri) {
	if (!uri || isDuplicateURI(uri))
		return NULL;
	SBOLObject* obj = malloc(sizeof(SBOLObject));
	obj->uri = createURIProperty();
	setURIProperty(obj->uri, uri);
	return obj;
}

void deleteSBOLObject(SBOLObject* obj) {
	if (obj) {
		deleteURIProperty(obj->uri);
		free(obj);
	}
}

void setURI(SBOLObject* obj, const char* uri) {
	if (obj && uri)
		setURIProperty(obj->uri, uri);
}

char* getURI(const SBOLObject* obj) {
	if (obj)
		return getURIProperty(obj->uri);
	else
		return NULL;
}

/**********************
 * SBOLCompoundObject
 **********************/

SBOLCompoundObject* createSBOLCompoundObject(const char* uri) {
	if (!uri)
		return NULL;
	SBOLCompoundObject* obj = malloc(sizeof(SBOLCompoundObject));
	SBOLObject* obj2 = (SBOLObject*) &obj;
	obj2 = createSBOLObject(uri);
	obj->displayID   = createTextProperty();
	obj->name        = createTextProperty();
	obj->description = createTextProperty();
	return obj;
}

void deleteSBOLCompoundObject(SBOLCompoundObject* obj) {
	if (obj) {
		if (obj->displayID)
			deleteTextProperty(obj->displayID);
			obj->displayID = NULL;
		if (obj->name)
			deleteTextProperty(obj->name);
			obj->name = NULL;
		if (obj->description)
			deleteTextProperty(obj->description);
			obj->description = NULL;
		deleteSBOLObject((SBOLObject*) obj);
		free(obj);
	}
}

void setDisplayID(SBOLCompoundObject* obj, const char* id) {
	if (obj && id) {
		setTextProperty(obj->displayID, id);
	}
}

char* getDisplayID(const SBOLCompoundObject* obj) {
	if (obj)
		return getTextProperty(obj->displayID);
	else
		return NULL;
}

void setName(SBOLCompoundObject* obj, const char* name) {
	if (obj && name) {
		setTextProperty(obj->name, name);
	}
}

char* getName(const SBOLCompoundObject* obj) {
	if (obj)
		return getTextProperty(obj->name);
	else
		return NULL;
}

void setDescription(SBOLCompoundObject* obj, const char* descr) {
	if (obj && descr) {
		setTextProperty(obj->description, descr);
	}
}

char* getDescription(const SBOLCompoundObject* obj) {
	if (obj)
		return getTextProperty(obj->description);
	else
		return NULL;
}
