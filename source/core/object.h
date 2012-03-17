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

typedef struct _SBOLCompoundObject {
	struct _SBOLObject*   base;
	struct _TextProperty* displayID;
	struct _TextProperty* name;
	struct _TextProperty* description;
} SBOLCompoundObject;

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
