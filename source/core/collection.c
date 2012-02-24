#include "collection.h"
#include "component.h"

/**************************
	create/destroy
***************************/

void createCollection(const char* id)
{
	Collection collection = {0,0,0,0,0,0,0};
	collection.id = new char[ strlen(id) ];
	strcpy(collection.id, id);
	allCollections[ string(id) ] = collection;
}

void deleteCollection(Collection* p)
{
	if (p->id) delete p->id;
	if (p->name) delete p->name;
	if (p->description) delete p->description;
	if (p->collections) delete p->collections;
	if (p->components) delete p->components;		
	if (p->numComponents) delete &p->numComponents;
	if (p->numCollections) delete &p->numCollections;
}

/**************************
	get... functions
***************************/

int getNumDNAComponentsIn(Collection collection)
{
	return collection.numComponents;
}

DNAComponent getNthDNAComponentIn(Collection collection, int n)
{
	DNAComponent p = {0,0,0,0,0,0,0};
	if (collection.components)
		p = *(collection.components[n]);
	return p;
}

/**************************
	set... functions
***************************/

void setCollectionID(Collection * collection, const char* id)
{
	if (collection)
		collection->id = (char*)id;
}

void setCollectionName(Collection * collection, const char* name)
{
	if (collection)
		collection->name = (char*)name;
}

void setCollectionDescription(Collection * collection, const char* descr)
{
	if (collection)
		collection->description = (char*)descr;
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

