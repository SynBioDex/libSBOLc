#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "property.h"
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
	Collection* col;
	col = (Collection*)malloc(sizeof(Collection));
	col->uri         = createProperty();
	col->displayID   = createProperty();
	col->name        = createProperty();
	col->description = createProperty();
	col->components  = createGenericArray();
	col->collections = createGenericArray();
	setCollectionURI(col, uri);
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
		removeCollection(col);
		if (col->uri) {
			deleteProperty(col->uri);
			col->uri = NULL;
		}
		if (col->displayID) {
			deleteProperty(col->displayID);
			col->displayID = NULL;
		}
		if (col->name) {
			deleteProperty(col->name);
			col->name = NULL;
		}
		if (col->description) {
			deleteProperty(col->description);
			col->description = NULL;
		}
		if (col->collections) {
			deleteGenericArray(col->collections);
			col->collections = NULL;
		}
		if (col->components) {
			deleteGenericArray(col->components);
			col->components = NULL;
		}
		free(col);
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
	Collection* col;
	for (index=0; index<allCollections->numInUse; index++) {
		col = (Collection*) allCollections->array[index];
		if (compareProperty(col->uri, uri) == 0)
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
	Collection* col;
	for (index=0; index<allCollections->numInUse; index++) {
		col = (Collection*) allCollections->array[index];
		if (compareProperty(col->uri, uri) == 0)
			return col;
	}
	return NULL;
}

char* getCollectionURI(const Collection* col) {
	if (col)
	    return getProperty(col->uri);
}

char* getCollectionDisplayID(const Collection* col) {
    if (col)
        return getProperty(col->displayID);
    else
        return NULL;
}

char* getCollectionName(const Collection* col) {
	if (col)
	    return getProperty(col->name);
    else
        return NULL;
}

char* getCollectionDescription(const Collection* col) {
	if (col)
	    return getProperty(col->description);
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
        setProperty(col->uri, uri);
}

void setCollectionDisplayID(Collection* col, const char* id) {
    if (col && id)
        setProperty(col->displayID, id);
}

void setCollectionName(Collection* col, const char* name) {
	if (col)
	    setProperty(col->name, name);
}

void setCollectionDescription(Collection* col, const char* descr) {
	if (col)
	    setProperty(col->description, descr);
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
    indent(tabs);   printProperty(col->uri);
    indent(tabs+1); printf("name: %s\n", getCollectionName(col));
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
