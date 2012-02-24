#include "component.h"

/**************************
	create/destroy
***************************/

void createComponent(const char* id)
{
	DNAComponent component = {0,0,0,0,0,0,0,0};
	component.id = new char[ strlen(id) ];
	strcpy(component.id, id);
	allComponents[ string(id) ] = component;
}

/**************************
	getNum... functions
***************************/

int getNumCollectionsFor(DNAComponent component)
{
	return component.numCollections;
}

int getNumSequenceAnnotationsIn(DNAComponent component)
{
	return component.numAnnotations;
}

/**************************
	getNth... functions
***************************/

Collection getNthCollectionFor(DNAComponent component, int n)
{
	Collection p = {0,0,0,0,0,0,0};
	if (component.collections)
		p = *(component.collections[n]);
	return p;
}

SequenceAnnotation getNthSequenceAnnotationIn(DNAComponent component, int n)
{
	printf("getting annotation %d from %s\n", n, component.id);
	SequenceAnnotation p = {0,0,0,0,0,0,0};
	if (component.numAnnotations >= n) //TODO just > ?
		p = *(component.annotations[n]);
	return p;
}

/**************************
	set... functions
***************************/

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

/**************************
	add annotation
***************************/

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
			//int n=0;
			//while (component->annotations[n]) ++n;
			int n = component->numAnnotations;

			SequenceAnnotation ** p = component->annotations;
			component->annotations = new SequenceAnnotation*[n+1];
			for (int i=0; i < n-1; ++i)
				component->annotations[i] = p[i];
			component->annotations[n-1] = annotation;
			component->annotations[n] = 0;
		}
		component->numAnnotations++;
	}
}

void setSubComponent(SequenceAnnotation * annotation, DNAComponent * component)
{
	if (annotation)
		annotation->subComponent = component;
}
