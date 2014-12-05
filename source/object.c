#include <stdlib.h>

#include "property.h"
#include "array.h"
#include "object.h"

/**************
 * SBOLObject
 **************/

SBOLObject* createSBOLObject(Document* doc, const char* uri) {
	if (!doc || !uri || isSBOLObjectURI(doc, uri))
		return NULL;
	SBOLObject* obj = malloc(sizeof(SBOLObject));
	obj->uri = createURIProperty(doc);
	obj->xml_annotations = createPointerArray();
	setSBOLObjectURI(obj, uri);
	return obj;
}

void deleteSBOLObject(SBOLObject* obj) {
	if (obj) {
		if (obj->uri) {
			deleteURIProperty(obj->uri);
			obj->uri = NULL;
		}
		if (obj->xml_annotations) {
			/// @todo free xmlNodes contained in PointerArray
			deletePointerArray(obj->xml_annotations);
		}
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
		return (char *)getURIProperty(obj->uri);
	else
		return NULL;
}

/**********************
 * SBOLCompoundObject
 **********************/

SBOLCompoundObject* createSBOLCompoundObject(Document* doc, const char* uri) {
	if (!doc || !uri || isSBOLObjectURI(doc, uri))
		return NULL;
	SBOLCompoundObject* obj = malloc(sizeof(SBOLCompoundObject));
	obj->base        = createSBOLObject(doc, uri);
	obj->displayID   = createTextProperty();
	obj->name        = createTextProperty();
	obj->description = createTextProperty();
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
		return (char *)getSBOLObjectURI(obj->base);
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

