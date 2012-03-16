#ifndef SBOL_OBJECT
#define SBOL_OBJECT

struct _TextProperty;
struct _URIProperty;

/**************
 * SBOLObject
 **************/

typedef struct _SBOLObject {
	struct _URIProperty* uri;
} SBOLObject;

SBOLObject* createSBOLObject(const char* uri);
void        deleteSBOLObject(SBOLObject* obj);

void  setSBOLObjectURI(SBOLObject* obj, const char* uri);
char* getSBOLObjectURI(const SBOLObject* obj);

/**********************
 * SBOLCompoundObject
 **********************/

typedef struct _SBOLCompoundObject {
	struct _SBOLObject base;
	struct _TextProperty* displayID;
	struct _TextProperty* name;
	struct _TextProperty* description;
} SBOLCompoundObject;

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
