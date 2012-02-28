#include <stdlib.h>
#include <string.h>
#include "storage.h"
#include "collection.h"
#include "component.h"

static GenericArray* allCollections;

/**************************
	create/destroy
***************************/

Collection* createCollection(const char* id) {
	Collection* col;
	col = (Collection*)malloc(sizeof(Collection));
	col->id          = NULL;
	col->name        = NULL;
	col->description = NULL;
	col->numComponents  = 0;
	col->numCollections = 0;
	col->components  = NULL;
	col->collections = NULL;
	setCollectionID(col, id);
	return col;
}

void registerCollection(Collection* col) {
	if (!allCollections)
		allCollections = createGenericArray();
	insertIntoArray(allCollections, col);
}

void removeCollection(Collection* col) {
	if (!allCollections)
		allCollections = createGenericArray();
	int index = indexByPtr(allCollections, col);
	if (index >= 0)
		removeFromArray(allCollections, index);
}

void deleteCollection(Collection* col) {
	if (col) {
		if (col->id) {
			free(col->id);
			col->id = NULL;
		}
		if (col->name) {
			free(col->name);
			col->name = NULL;
		}
		if (col->description) {
			free(col->description);
			col->description = NULL;
		}
		if (col->collections) {
			free(col->collections);
			col->collections = NULL;
		}
		if (col->components) {
			free(col->components);
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

int isCollectionID(const char* id) {
	if (!allCollections)
		allCollections = createGenericArray();
	if (!id)
		return 0;
	int index;
	Collection* col;
	for (index=0; index<allCollections->numInUse; index++) {
		col = (Collection*) allCollections->array[index];
		if (strcmp(col->id, id) == 0)
			return 1;
	}
	return 0;
}

/**************************
	get... functions
***************************/

Collection* getCollection(const char* id) {
	if (!allCollections)
		allCollections = createGenericArray();
	if (!id)
		return NULL;
	int index;
	Collection* col;
	for (index=0; index<allCollections->numInUse; index++) {
		col = (Collection*) allCollections->array[index];
		if (col->id == id)
			return col;
	}
	return NULL;
}

char* getCollectionID(Collection* col) {
	if (col && col->id) {
		char* id = (char*)malloc(sizeof(char) * strlen(col->id)+1);
		strcpy(id, col->id);
		return id;
	} else
		return NULL;
}

char* getCollectionName(Collection* col) {
	if (col && col->name) {
		char* name = (char*)malloc(sizeof(char) * strlen(col->name)+1);
		strcpy(name, col->name);
		return name;
	} else
		return NULL;
}

char* getCollectionDescription(Collection* col) {
	if (col && col->description) {
		char* descr = (char*)malloc(sizeof(char) * strlen(col->description)+1);
		strcpy(descr, col->description);
		return descr;
	} else
		return NULL;
}

/**************************
 *	getNum... functions
 **************************/

int getNumCollections() {
	if (!allCollections)
		allCollections = createGenericArray();
	return allCollections->numInUse;
}

int getNumDNAComponentsIn(Collection* col) {
	if (col)
		return col->numComponents;
	else
		return -1;
}

/**************************
 *	getNth... functions
 **************************/

Collection* getNthCollection(int n) {
	if (!allCollections)
		allCollections = createGenericArray();
	if (allCollections->numInUse > n)
		return allCollections->array[n];
	else
		return NULL;
}

DNAComponent* getNthDNAComponentIn(Collection* col, int n) {
	if (col->numComponents >= n)
		return col->components[n];
	else
		return NULL;
}

/**************************
	set... functions
***************************/

void setCollectionID(Collection* col, const char* id) {
	if (col && id) {
		col->id = (char*)malloc(sizeof(char) * strlen(id)+1);
		strcpy(col->id, id);
	}
}

void setCollectionName(Collection* col, const char* name) {
	if (col && name) {
		col->name = (char*)malloc(sizeof(char) * strlen(name)+1);
		strcpy(col->name, name);
	}
}

void setCollectionDescription(Collection* col, const char* descr) {
	if (col && descr) {
		col->description = (char*)malloc(sizeof(char) * strlen(descr)+1);
		strcpy(col->description, descr);
	}
}

/**************************
	add component
***************************/

void addComponentToCollection(DNAComponent * component, Collection * collection)
{
	Collection   ** p1 = 0;
	DNAComponent ** p2 = 0;
	int i = 0;
	int n = 0;
	if (component && collection)
	{
		p1 = component->collections;
		
		// create a slightly longer array and copy things over,
		// then add the new collection
		if (p1)
		{
			//i = 0;
			//while (p1[i])
			//	++i;
			//n = i; // current number of collections
            n = component->numCollections;

			component->collections = (Collection**)malloc((n+1) * sizeof(Collection*));
			for (i=0; i < n-1; ++i) //TODO remove multiple nulls?
				component->collections[i] = p1[i];
			component->collections[n-1] = collection;
			component->collections[n] = 0;
			free(p1);
			p1 = NULL;
		}

		// create an array and add the new collection
		else
		{
			component->collections = (Collection**)malloc(2 * sizeof(Collection*));
			component->collections[0] = collection;
			component->collections[1] = 0;
		}
		component->numCollections++;

		//while (component->collections[i])
		//	i++;

		p2 = collection->components;

		// create a new array and copy things over,
		// then add the new component to it
		if (p2)
		{
			//i = 0;
			//while (p2[i])
			//	++i;
			//n = i; // current number of components
			n = collection->numComponents;

			collection->components = (DNAComponent**)malloc((n+1) * sizeof(DNAComponent*));
			for (i=0; i < n-1; ++i)
				collection->components[i] = p2[i];
			collection->components[n-1] = component;
			collection->components[n] = 0;
			free(p2);
			p2 = NULL;
		}

		// start an array of components and add the new one
		else
		{
			collection->components = (DNAComponent**)malloc(2 * sizeof(DNAComponent*));
			collection->components[0] = component;
			collection->components[1] = 0;
		}
		collection->numComponents++;

		//while (collection->components[i])
		//	i++;
	}
}

void cleanupCollections() {
	if (allCollections) {
		int index;
		for (index=allCollections->numInUse; index>0; index--)
			deleteCollection( allCollections->array[index] );
		deleteGenericArray(allCollections);
		allCollections = NULL;
	}
}
