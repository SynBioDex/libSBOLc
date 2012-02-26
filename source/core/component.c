#include <stdlib.h>
#include <string.h>
#include "component.h"
#include "sequence.h"
#include "annotation.h"
#include "collection.h"

/**************************
	create/destroy
***************************/

DNAComponent* createComponent(const char* id) {
	DNAComponent* com;
	com = (DNAComponent*)malloc(sizeof(DNAComponent));
	com->id          = NULL;
	com->name        = NULL;
	com->description = NULL;
	com->numAnnotations = 0;
	com->numCollections = 0;
	com->annotations = NULL;
	com->collections = NULL;
	setComponentID(com, id);
	return com;
}

void deleteComponent(DNAComponent* com) {
	if (com) {
		if (com->id)          free(com->id);
		if (com->name)        free(com->name);
		if (com->description) free(com->description);
		if (com->annotations) free(com->annotations);
		if (com->collections) free(com->collections);
		free(com);
	}
}

/**************************
	getNum... functions
***************************/

int getNumCollectionsFor(const DNAComponent* com) {
	return com->numCollections;
}

int getNumSequenceAnnotationsIn(const DNAComponent* com) {
	return com->numAnnotations;
}

/**************************
	getNth... functions
***************************/

struct _Collection* getNthCollectionFor(const DNAComponent* com, int n) {
	if (com->numCollections >= n)
		return com->collections[n];
	else
		return NULL;
}

struct _SequenceAnnotation* getNthSequenceAnnotationIn(const DNAComponent* com, int n) {
	if (com->numAnnotations >= n)
		return com->annotations[n];
	else
		return NULL;
}

/**************************
	set... functions
***************************/

void setComponentID(DNAComponent* com, const char* id) {
	if (com && id) {
		com->id = (char*)malloc(sizeof(char) * strlen(id)+1);
		strcpy(com->id, id);
	}
}

void setComponentName(DNAComponent* com, const char* name) {
	if (com && name) {
		com->name = (char*)malloc(sizeof(char) * strlen(name)+1);
		strcpy(com->name, name);
	}
}

void setComponentDescription(DNAComponent* com, const char* descr) {
	if (com && descr) {
		com->description = (char*)malloc(sizeof(char) * strlen(descr)+1);
		strcpy(com->description, descr);
	}
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
