#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "property.h"
#include "object.h"
#include "genericarray.h"
#include "collection.h"
#include "dnacomponent.h"

static GenericArray* allCollections;

/**************************
	create/destroy
***************************/

void registerCollection(Collection* col) {
	if (!allCollections)
		allCollections = createGenericArray();
	insertIntoGenericArray(allCollections, col);
}

Collection* createCollection(const char* uri) {
	if (!uri || isDuplicateURI(uri))
	    return NULL;
	Collection* col = malloc(sizeof(Collection));
	col->base        = createSBOLCompoundObject(uri);
	col->components  = createGenericArray();
	col->collections = createGenericArray();
	col->processed   = 0;
	registerCollection(col);
	return col;
}

void removeCollection(Collection* col) {
	if (!allCollections)
		allCollections = createGenericArray();
	int index = indexByPtr(allCollections, col);
	if (index >= 0)
		removeFromGenericArray(allCollections, index);
}

void deleteCollection(Collection* col) {
	if (col) {
		if (col->base)        deleteSBOLCompoundObject(col->base);
		if (col->collections) deleteGenericArray(col->collections);
		if (col->components)  deleteGenericArray(col->components);
		removeCollection(col);
		free(col);
		col = NULL;
	}
}

/**************************
 *	is... functions
 **************************/

int isCollectionPtr(const void* pointer) {
	if (!allCollections)
		allCollections = createGenericArray();
	return (int) indexByPtr(allCollections, pointer) >= 0;
}

int isCollectionURI(const char* uri) {
	if (!allCollections)
		allCollections = createGenericArray();
	if (!uri)
		return 0;
	int index;
	char* candidate;
	Collection* col;
	for (index=0; index<allCollections->numInUse; index++) {
		col = (Collection*) allCollections->array[index];
		candidate = getSBOLCompoundObjectURI(col->base);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

/**************************
	get... functions
***************************/

Collection* getCollection(const char* uri) {
	if (!allCollections)
		allCollections = createGenericArray();
	if (!uri)
		return NULL;
	int index;
	char* candidate;
	Collection* col;
	for (index=0; index<allCollections->numInUse; index++) {
		col = (Collection*) allCollections->array[index];
		candidate = getSBOLCompoundObjectURI(col->base);
		if (candidate && strcmp(candidate, uri) == 0)
			return col;
	}
	return NULL;
}

char* getCollectionURI(const Collection* col) {
	if (col)
		return getSBOLCompoundObjectURI(col->base);
	else
		return NULL;
}

char* getCollectionDisplayID(const Collection* col) {
    if (col)
    	return getSBOLCompoundObjectDisplayID(col->base);
    else
    	return NULL;
}

char* getCollectionName(const Collection* col) {
	if (col)
		return getSBOLCompoundObjectName(col->base);
	else
		return NULL;
}

char* getCollectionDescription(const Collection* col) {
	if (col)
		return getSBOLCompoundObjectDescription(col->base);
	else
		return NULL;
}

/**************************
 *	getNum... functions
 **************************/

int getNumCollections() {
	if (allCollections)
		return allCollections->numInUse;
	else
		return 0;
}

int getNumDNAComponentsIn(const Collection* col) {
	if (col)
		return col->components->numInUse;
	else
		return -1;
}

int getNumCollectionsIn(const Collection* col) {
	if (col)
		return col->collections->numInUse;
	else
		return -1;
}

/**************************
 *	getNth... functions
 **************************/

Collection* getNthCollection(int n) {
    if (allCollections)
        return (Collection*) getNthArrayElement(allCollections, n);
    else
        return NULL;
}

DNAComponent* getNthDNAComponentIn(const Collection* col, int n) {
    if (col)
        return (DNAComponent*) getNthArrayElement(col->components, n);
    else
        return NULL;
}

Collection* getNthCollectionIn(const Collection* col, int n) {
	if (col)
	    return (Collection*) getNthArrayElement(col->collections, n);
	else
		return NULL;
}

/**************************
	set... functions
***************************/

void setCollectionURI(Collection* col, const char* uri) {
    if (col)
    	setSBOLCompoundObjectURI(col->base, uri);
}

void setCollectionDisplayID(Collection* col, const char* id) {
	if (col)
		setSBOLCompoundObjectDisplayID(col->base, id);
}

void setCollectionName(Collection* col, const char* name) {
	if (col)
		setSBOLCompoundObjectName(col->base, name);
}

void setCollectionDescription(Collection* col, const char* descr) {
	if (col)
		setSBOLCompoundObjectDescription(col->base, descr);
}

/**************************
	add component
***************************/

void addDNAComponentToCollection(DNAComponent* com, Collection* col) {
	if (com && col) {
		insertIntoGenericArray(com->collections, col);
		insertIntoGenericArray(col->components,  com);
	}
}

void cleanupCollections() {
	if (allCollections) {
		int n;
		Collection* col;
		for (n=getNumCollections()-1; n>=0; n--) {
            col = getNthCollection(n);
			deleteCollection(col);
		}
		deleteGenericArray(allCollections);
		allCollections = NULL;
	}
}

void printCollection(const Collection* col, int tabs) {
    if (!col)
        return;
    indent(tabs);   printf("uri:         %s\n", getCollectionURI(col));
    indent(tabs+1); printf("name:        %s\n", getCollectionName(col));
    indent(tabs+1); printf("description: %s\n", getCollectionDescription(col));
    int i;
    int num;
    if (col->components) {
        DNAComponent* com;
        num = getNumDNAComponentsIn(col);
        if (num > 0) {
            indent(tabs+1); printf("%i components:\n", num);
            for (i=0; i<num; i++) {
                com = getNthDNAComponentIn(col, i);
                indent(tabs+2); printf("%s\n", getDNAComponentURI(com));
            }
        }
    }
    if (col->collections) {
        Collection* col2;
        num = getNumCollectionsIn(col);
        if (num > 0) {
            indent(tabs+1); printf("%i collections:\n", num);
            for (i=0; i<num; i++) {
                col2 = getNthCollectionIn(col, i);
                indent(tabs+2); printf("%s\n", getCollectionURI(col2));
            }
        }
    }
}

void printAllCollections() {
    int n;
    int num = getNumCollections();
    if (num > 0) {
        printf("%i collections:\n", num);
        for (n=0; n<num; n++)
            printCollection(getNthCollection(n), 1);
    }
}
