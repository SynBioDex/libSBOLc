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

static map<string, DNAComponent> allComponents;
static map<string, Collection> allCollections;
static map<string, SequenceAnnotation> allAnnotations;

/****************************************
     The "is.." functions are just for ease
	  of reading the code
*****************************************/

bool isComponent(string s)
{
	return (allComponents.count(s) > 0);
}

bool isAnnotation(string s)
{
	return (allAnnotations.count(s) > 0);
}

bool isCollection(string s)
{
	return (allCollections.count(s) > 0);
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
    SBOL get functions
************************************************/

int getNumCollections()
{
	return allCollections.size();
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
	return allComponents.size();
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
		while (component.collections[n]) ++n;
	return n;
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
	return allAnnotations.size();
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
    SBOL set functions
*************************************************/
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

void setComponentID(DNAComponent * component, const char* id)
{
	if (component)
		component->id = (char*)id;
}

void setComponentName(DNAComponent * component, const char* name)
{
	if (component)
		component->name = (char*)name;
}

void setComponentDescription(DNAComponent * component, const char* descr)
{
	if (component)
		component->description = (char*)descr;
}

void addComponentToCollection(DNAComponent * component, Collection * collection)
{
	Collection ** p1 = 0;
	DNAComponent ** p2 = 0;
	int i, n;
	if (component && collection)
	{
		p1 = component->collections;
		if (p1)
		{
			i = 0;
			while (p1[i]) ++i;
			n = i;

			component->collections = (Collection**)malloc((n+2) * sizeof(Collection*));
			for (i=0; i < n; ++i)
				component->collections[i] = p1[i];
			component->collections[n] = collection;
			component->collections[n+1] = 0;
			free(p1);
		}
		else
		{
			component->collections = (Collection**)malloc(2 * sizeof(Collection*));
			component->collections[0] = collection;
			component->collections[1] = 0;
		}

		p2 = collection->components;
		if (p2)
		{
			i = 0;
			while (p2[i]) ++i;
			n = i;

			collection->components = (DNAComponent**)malloc((n+2) * sizeof(DNAComponent*));
			for (i=0; i < n; ++i)
				collection->components[i] = p2[i];
			collection->components[n] = component;
			collection->components[n+1] = 0;
			free(p2);
		}
		else
		{
			collection->components = (DNAComponent**)malloc(2 * sizeof(DNAComponent*));
			collection->components[0] = component;
			collection->components[1] = 0;
		}
	}
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
	}
}

