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

void  setURI(SBOLObject* obj, const char* uri);
char* getURI(const SBOLObject* obj);

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

void  setDisplayID(SBOLCompoundObject* obj, const char* id);
char* getDisplayID(const SBOLCompoundObject* obj);

void  setName(SBOLCompoundObject* obj, const char* name);
char* getName(const SBOLCompoundObject* obj);

void  setDescription(SBOLCompoundObject* obj, const char* descr);
char* getDescription(const SBOLCompoundObject* obj);

#endif
