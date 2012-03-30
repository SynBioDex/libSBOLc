#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @todo remove?
#include "property.h"
#include "object.h"
#include "array.h"
#include "collection.h"
#include "dnacomponent.h"

static PointerArray* allCollections;

void lazyCreateAllCollections() {
	if (!allCollections)
		allCollections = createPointerArray();
}

static void registerCollection(Collection* col) {
	lazyCreateAllCollections();
	insertPointerIntoArray(allCollections, col);
}

Collection* createCollection(const char* uri) {
	if (!uri || isSBOLObjectURI(uri))
	    return NULL;
	Collection* col = malloc(sizeof(Collection));
	col->base        = createSBOLCompoundObject(uri);
	col->components  = createPointerArray();
	registerCollection(col);
	return col;
}

static void removeCollection(Collection* col) {
	lazyCreateAllCollections();
	int index = indexOfPointerInArray(allCollections, col);
	if (index >= 0)
		removePointerFromArray(allCollections, index);
}

void deleteCollection(Collection* col) {
	if (col) {
		if (col->base) {
			deleteSBOLCompoundObject(col->base);
			col->base = NULL;
		}
		if (col->components) {
			deletePointerArray(col->components);
			col->components = NULL;
		}
		removeCollection(col);
		free(col);
		col = NULL;
	}
}

int isCollection(const void* pointer) {
	lazyCreateAllCollections();
	return (int) indexOfPointerInArray(allCollections, pointer) >= 0;
}

int isCollectionURI(const char* uri) {
	lazyCreateAllCollections();
	if (!uri)
		return 0;
	int n;
	char* candidate;
	Collection* col;
	for (n=0; n < getNumCollections(); n++) {
		col = getNthCollection(n);
		candidate = getCollectionURI(col);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

Collection* getCollection(const char* uri) {
	lazyCreateAllCollections();
	if (!uri)
		return NULL;
	int n;
	char* candidate;
	Collection* col;
	for (n=0; n < getNumCollections(); n++) {
		col = getNthCollection(n);
		candidate = getCollectionURI(col);
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

int getNumCollections() {
	if (allCollections)
		return getNumPointersInArray(allCollections);
	else
		return 0;
}

int getNumDNAComponentsIn(const Collection* col) {
	if (col)
		return getNumPointersInArray(col->components);
	else
		return -1;
}

Collection* getNthCollection(int n) {
    if (getNumCollections() > n && n >= 0)
        return (Collection *)getNthPointerInArray(allCollections, n);
    else
        return NULL;
}

DNAComponent* getNthDNAComponentIn(const Collection* col, int n) {
    if (col)
        return (DNAComponent *)getNthPointerInArray(col->components, n);
    else
        return NULL;
}

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

void addDNAComponentToCollection(DNAComponent* com, Collection* col) {
	if (com && col) {
		insertPointerIntoArray(col->components,  com);
	}
}

int dnaComponentInCollection(const DNAComponent *com, const Collection *col) {
	if (!com || !col)
		return 0;
	DNAComponent *candidate;
	int n;
	for (n=0; n<getNumDNAComponentsIn(col); n++) {
		candidate = getNthDNAComponentIn(col, n);
		if (candidate == com)
			return 1;
	}
	return 0;
}

void printCollection(const Collection* col, int tabs) {
    if (!col)
        return;
    indent(tabs);   printf("uri: %s\n", getCollectionURI(col));
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

void cleanupCollections() {
	if (allCollections) {
		int n;
		Collection* col;
		for (n=getNumCollections()-1; n>=0; n--) {
            col = getNthCollection(n);
			deleteCollection(col);
			col = NULL;
		}
		deletePointerArray(allCollections);
		allCollections = NULL;
	}
}

