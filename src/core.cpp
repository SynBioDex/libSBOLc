#include <string.h>
#include <string>  //std string
#include <map>  //std map

extern "C"
{
	#include "core.h"
}

using namespace std;

/**************************************
   A set of global vectors are used to store
   all the SBOL objects
****************************************/

static map<string, DNAComponent>	   allComponents;
static map<string, Collection>		 allCollections;
static map<string, SequenceAnnotation> allAnnotations;

/**************************************
   Functions for working with the
   global vectors
****************************************/

void newComponent(const char* id)
{
	DNAComponent component = {0,0,0,0,0,0};
	component.id = new char[ strlen(id) ];
	strcpy(component.id, id);
	allComponents[ string(id) ] = component;
	//printf("created component %s\n", id);
}

void newSequenceAnnotation(const char* id)
{
	SequenceAnnotation annotation = {0,0,0,0,0};
	annotation.id = new char[ strlen(id) ];
	strcpy(annotation.id, id);
	allAnnotations[ string(id) ] = annotation;
	//printf("created annotation %s\n", id);
}

void newCollection(const char* id)
{
	Collection collection = {0,0,0,0,0};
	collection.id = new char[ strlen(id) ];
	strcpy(collection.id, id);
	allCollections[ string(id) ] = collection;
	//printf("created collection %s\n", id);
}

DNAComponent getComponent(const char* id)
{
	DNAComponent com = allComponents[ string(id) ];
	//printf("getting %s\n", com.id);
	return com;
}

SequenceAnnotation getSequenceAnnotation(const char* id)
{
	SequenceAnnotation ann = allAnnotations[ string(id) ];
	//printf("getting %s\n", ann.id);
	return ann;
}

Collection getCollection(const char* id)
{
	Collection col = allCollections[ string(id) ];
	//printf("getting %s\n", col.id);
	return col;
}

/****************************************
	 The "is.." functions are just for ease
	  of reading the code
*****************************************/

int isComponent(const char* id)
{
	return (int) (allComponents.count( string(id) ) > 0);
}

int isAnnotation(const char* id)
{
	return (int) (allAnnotations.count( string(id) ) > 0);
}

int isCollection(const char* id)
{
	return (int) (allCollections.count( string(id) ) > 0);
}

// free memory used by SBOL data structures
void cleanup()
{
	map<string,Collection>::iterator it1 = allCollections.begin();
	for (; it1 != allCollections.end(); ++it1)
	{
		Collection p = (*it1).second;
		if (p.id) delete p.id;
		if (p.name) delete p.name;
		if (p.description) delete p.description;
		if (p.collections) delete p.collections;
		if (p.components) delete p.components;		
	}

	map<string,DNAComponent>::iterator it2 = allComponents.begin();
	for (; it2 != allComponents.end(); ++it2)
	{
		DNAComponent p = (*it2).second;
		if (p.id) delete p.id;
		if (p.name) delete p.name;
		if (p.description) delete p.description;
		if (p.collections) delete p.collections;
		if (p.annotations) delete p.annotations;		
	}

	map<string,SequenceAnnotation>::iterator it3 = allAnnotations.begin();
	for (; it3 != allAnnotations.end(); ++it3)
	{
		SequenceAnnotation p = (*it3).second;
		if (p.id) delete p.id;
		if (p.precedes) delete p.precedes;
	}
}

/***********************************************
	SBOL core get functions
************************************************/

int getNumCollections()
{
	//printf("getting number of collections...\n");
	int num = allCollections.size();
	//printf("number of collections: %d\n", num);
	return num;
}

Collection getNthCollection(int n)
{
	Collection p = {0,0,0,0,0};
	map<string,Collection>::iterator it = allCollections.begin();
	for (int i=0; it != allCollections.end(); ++it, ++i)
		if (i == n)
			p = (*it).second;
	
	return p;
}

int getNumDNAComponents()
{
	//printf("getting number of components...\n");
	int num = allComponents.size();
	//printf("number of components: %d\n", num);
	return num;
}

DNAComponent getNthDNAComponent(int n)
{
	DNAComponent p = {0,0,0,0,0,0};
	map<string,DNAComponent>::iterator it = allComponents.begin();
	for (int i=0; it != allComponents.end(); ++it, ++i)
		if (i == n)
			p = (*it).second;
	
	return p;
}

int getNumDNAComponentsIn(Collection collection)
{
	int n = 0;
	if (collection.components)
		while (collection.components[n]) ++n;
	return n;
	//return collection.numComponents;
}

DNAComponent getNthDNAComponentIn(Collection collection, int n)
{
	DNAComponent p = {0,0,0,0,0,0};
	if (collection.components)
		p = *(collection.components[n]);
	return p;
}

int getNumCollectionsFor(DNAComponent component)
{
	int n = 0;
	if (component.collections)
		while (component.collections[n])
		{
			++n;
			//printf("%s has %d collections\n", component.id, n);
		}
	return n;
	//return component.numCollections;
}

Collection getNthCollectionFor(DNAComponent component, int n)
{
	Collection p = {0,0,0,0,0};
	if (component.collections)
		p = *(component.collections[n]);
	return p;
}

int getNumSequenceAnnotations()
{
	//printf("getting number of annotations...\n");
	int num = allAnnotations.size();
	//printf("number of annotations: %d\n", num);
	return num;
}

SequenceAnnotation getNthSequenceAnnotation(int n)
{
	SequenceAnnotation p = {0,0,0,0,0,0};
	map<string,SequenceAnnotation>::iterator it = allAnnotations.begin();
	for (int i=0; it != allAnnotations.end(); ++it, ++i)
		if (i == n)
			p = (*it).second;
	
	return p;
}

int getNumSequenceAnnotationsIn(DNAComponent component)
{
	int n=0;
	if (component.annotations)
	{
		while (component.annotations[n])
			++n;
	}
	return n;
	//return component.numAnnotations;
}

SequenceAnnotation getNthSequenceAnnotationIn(DNAComponent component, int n)
{
	SequenceAnnotation p = {0,0,0,0,0,0};
	int i=0;
	if (component.annotations)
	{
		while (component.annotations[i] && i < n)
			++i;
		if (i == n)
			p = *(component.annotations[i]);
	}
	return p;
}

int getNumPrecedes(SequenceAnnotation annotation)
{
	int n=0;
	if (annotation.precedes)
	{
		while (annotation.precedes[n])
			++n;
	}
	return n;
	//return annotation.numPrecedes;
}

SequenceAnnotation getNthPrecedes(SequenceAnnotation annotation, int n)
{
	SequenceAnnotation p = {0,0,0,0,0,0};
	int i=0;
	if (annotation.precedes)
	{
		while (annotation.precedes[i] && i < n)
			++i;
		if (i == n)
			p = *(annotation.precedes[i]);
	}
	return p;
}

/************************************************
	SBOL core set functions
*************************************************/
void setCollectionID(Collection * collection, const char* id)
{
	if (collection)
		collection->id = (char*)id;
	else
		printf("tried to set id of NULL collection\n");
}

void setCollectionName(Collection * collection, const char* name)
{
	if (collection)
		collection->name = (char*)name;
	else
		printf("tried to set name of NULL collection\n");
}

void setCollectionDescription(Collection * collection, const char* descr)
{
	if (collection)
		collection->description = (char*)descr;
	else
		printf("tried to set descr of NULL collection\n");
}

void setComponentID(DNAComponent * component, const char* id)
{
	if (component)
	{
		printf("setting component id to %s\n", id);
		component->id = (char*)id;
	}
	else
		printf("tried to set id of NULL component\n");
}

void setComponentName(DNAComponent * component, const char* name)
{
	if (component)
	{
		printf("setting component name to %s\n", name);
		component->name = (char*)name;
	}
	else
		printf("tried to set name of NULL component\n");
}

void setComponentDescription(DNAComponent * component, const char* descr)
{
	if (component)
	{
		printf("setting component descr to %s\n", descr);
		component->description = (char*)descr;
	}
	else
		printf("tried to set descr of NULL component\n");
}

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
			i = 0;
			while (p1[i])
				++i;
			n = i; // current number of collections

			component->collections = (Collection**)malloc((n+2) * sizeof(Collection*));
			for (i=0; i < n; ++i)
				component->collections[i] = p1[i];
			component->collections[n] = collection;
			component->collections[n+1] = 0;
			free(p1);
		}

		// create an array and add the new collection
		else
		{
			component->collections = (Collection**)malloc(2 * sizeof(Collection*));
			component->collections[0] = collection;
			component->collections[1] = 0;
		}
		//component->numCollections++;

		//printf("%s has the following %d collections:", component->id, n);
		//while (component->collections[i])
		//{
		//	printf(" %s", component->collections[i]->id);
		//	i++;
		//}
		//printf("\n");

		p2 = collection->components;

		// create a new array and copy things over,
		// then add the new component to it
		if (p2)
		{
			i = 0;
			while (p2[i])
				++i;
			n = i; // current number of components

			collection->components = (DNAComponent**)malloc((n+2) * sizeof(DNAComponent*));
			for (i=0; i < n; ++i)
				collection->components[i] = p2[i];
			collection->components[n] = component;
			collection->components[n+1] = 0;
			free(p2);
		}

		// start an array of components and add the new one
		else
		{
			collection->components = (DNAComponent**)malloc(2 * sizeof(DNAComponent*));
			collection->components[0] = component;
			collection->components[1] = 0;
		}
		//collection->numComponents++;

		//printf("%s has the following %d components:", collection->id, n);
		//while (collection->components[i])
		//{
		//	printf(" %s", collection->components[i]->id);
		//	i++;
		//}
		//printf("\n");

	}
	else
		printf("component or collection was null\n");
}

void setSequenceAnnotationID(SequenceAnnotation * annotation, const char * id)
{
	if (annotation)
		annotation->id = (char*)id;
}

void setSubComponent(SequenceAnnotation * annotation, DNAComponent * component)
{
	if (annotation)
		annotation->subComponent = component;
}

void addSequenceAnnotation(DNAComponent * component, SequenceAnnotation * annotation)
{
	if (component && annotation)
	{
		annotation->annotates = component;
		if (!component->annotations)
		{
			component->annotations = new SequenceAnnotation*[2];
			component->annotations[0] = annotation;
			component->annotations[1] = 0;
		}
		else
		{
			int n=0;
			while (component->annotations[n]) ++n;

			SequenceAnnotation ** p = component->annotations;
			component->annotations = new SequenceAnnotation*[n+2];
			for (int i=0; i < n; ++i)
				component->annotations[i] = p[i];
			component->annotations[n] = annotation;
			component->annotations[n+1] = 0;
		}
		//component->numAnnotations++;
	}
}

void addPrecedesRelationship(SequenceAnnotation * upstream, SequenceAnnotation * downstream)
{
	if (upstream && downstream)
	{
		if (!upstream->precedes)
		{
			upstream->precedes = new SequenceAnnotation*[2];
			upstream->precedes[0] = downstream;
			upstream->precedes[1] = 0;
		}
		else
		{
			int n=0;
			while (upstream->precedes[n]) ++n;

			SequenceAnnotation ** p = upstream->precedes;
			upstream->precedes = new SequenceAnnotation*[n+2];
			for (int i=0; i < n; ++i)
				upstream->precedes[i] = p[i];
			upstream->precedes[n] = downstream;
			upstream->precedes[n+1] = 0;
		}
		//upstream->numPrecedes++;
	}
}

