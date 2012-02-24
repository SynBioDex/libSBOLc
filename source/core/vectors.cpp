#include <map>

extern "C"
{
	#include "vectors.h"
}

using namespace std;

static map<string, DNAComponent>	   allComponents;
static map<string, Collection>         allCollections;
static map<string, SequenceAnnotation> allAnnotations;

/**************************
	is... functions
***************************/

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

/**************************
	getNum... functions
***************************/

int getNumCollections()
{
	return allCollections.size();
}

int getNumDNAComponents()
{
	return allComponents.size();
}

int getNumSequenceAnnotations()
{
	return allAnnotations.size();
}

/**************************
	getNth... functions
***************************/

Collection getNthCollection(int n)
{
	Collection p = {0,0,0,0,0};
	map<string,Collection>::iterator it = allCollections.begin();
	for (int i=0; it != allCollections.end(); ++it, ++i)
		if (i == n)
			p = (*it).second;
	
	return p;
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

SequenceAnnotation getNthSequenceAnnotation(int n)
{
	SequenceAnnotation p = {0,0,0,0,0,0,0};
	map<string,SequenceAnnotation>::iterator it = allAnnotations.begin();
	for (int i=0; it != allAnnotations.end(); ++it, ++i)
		if (i == n)
			p = (*it).second;
	
	return p;
}

/**************************
	get... functions
***************************/

DNAComponent getComponent(const char* id)
{
	return allComponents[ string(id) ];
}

SequenceAnnotation getSequenceAnnotation(const char* id)
{
	return allAnnotations[ string(id) ];
}

Collection getCollection(const char* id)
{
	return allCollections[ string(id) ];
}

/**************************
	free all memory
***************************/

void cleanup()
{
	map<string, Collection>::iterator it1 = allCollections.begin();
	for (; it1 != allCollections.end(); ++it1)
	{
		Collection p = (*it1).second;
		deleteCollection(&p);
	}

	map<string, DNAComponent>::iterator it2 = allComponents.begin();
	for (; it2 != allComponents.end(); ++it2)
	{
		DNAComponent p = (*it2).second;
		if (p.id) delete p.id;
		if (p.name) delete p.name;
		if (p.description) delete p.description;
		if (p.collections) delete p.collections;
		if (p.annotations) delete p.annotations;		
		if (p.numAnnotations) delete &p.numAnnotations;
		if (p.numCollections) delete &p.numCollections;
	}

	map<string, SequenceAnnotation>::iterator it3 = allAnnotations.begin();
	for (; it3 != allAnnotations.end(); ++it3)
	{
		SequenceAnnotation p = (*it3).second;
		if (p.id) delete p.id;
		if (p.precedes) delete p.precedes;
		if (p.numPrecedes) delete &p.numPrecedes;
	}
}

