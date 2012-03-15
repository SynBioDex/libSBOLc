#include "debug.h"
#include "property.h"
#include "genericarray.h"

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
	obj->uri = createURI();
	setURI(obj->uri, uri);
	return obj;
}

void deleteSBOLObject(SBOLObject* obj) {
	if (obj) {
		deleteURI(obj->uri);
		free(obj);
	}
}

void setURI(SBOLObject* obj, const char* uri) {
	if (obj && uri)
		setURI(obj->uri, uri);
}

char* getURI(const SBOLObject* obj) (
	if (obj)
		return getURI(obj->uri);
	else
		return NULL;
)

/**********************
 * SBOLCompoundObject
 **********************/

SBOLCompoundObject* createSBOLCompoundObject(const char* uri) {
	if (!uri)
		return NULL;
	SBOLCompoundObject* obj = malloc(sizeof(SBOLCompoundObject));
	obj->base        = createSBOLObject(uri);
	obj->displayID   = createText();
	obj->name        = createText();
	obj->description = createText();
}

void deleteSBOLCompoundObject(SBOLCompoundObject* obj) {
	if (obj) {
		if (obj->base)
			deleteSBOLObject(base);
			obj->base = NULL;
		if (obj->displayID)
			deleteText(obj->displayID);
			obj->displayID = NULL;
		if (obj->name)
			deleteText(obj->name);
			obj->name = NULL;
		if (obj->description)
			deleteText(obj->description);
			obj->description = NULL;
		free(obj);
	}
}

void setDisplayID(SBOLCompoundObject* obj, const char* id) {
	if (obj && id) {
		setText(obj->id, id);
	}
}

char* getDisplayID(const SBOLCompoundObject* obj) {
	if (obj)
		return getText(obj->displayID);
	else
		return NULL;
}

void setName(SBOLCompoundObject* obj, const char* name) {
	if (obj && name) {
		setText(obj->name, name);
	}
}

char* getName(const SBOLCompoundObject* obj) {
	if (obj)
		return getText(obj->name);
	else
		return NULL;
}

void setDescription(SBOLCompoundObject* obj, const char* descr) {
	if (obj && descr) {
		setText(obj->description, descr);
	}
}

char* getDescription(const SBOLCompoundObject* obj) {
	if (obj)
		return getText(obj->description);
	else
		return NULL;
}
