#include <stdlib.h>
#include <string.h>
#include "genericarray.h"
#include "dnacomponent.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "collection.h"

static GenericArray* allDNAComponents;

/**************************
	create/destroy
***************************/

void registerDNAComponent(DNAComponent* com) {
	if (!allDNAComponents)
		allDNAComponents = createGenericArray();
	insertIntoGenericArray(allDNAComponents, com);
}

DNAComponent* createDNAComponent(const char* id) {
	DNAComponent* com = (DNAComponent*)malloc(sizeof(DNAComponent));
	com->id          = NULL;
	com->name        = NULL;
	com->description = NULL;
	com->numAnnotations = 0;
	com->numCollections = 0;
	com->annotations = NULL;
	com->collections = NULL;
	setDNAComponentID(com, id);
	registerDNAComponent(com);
	return com;
}

void removeDNAComponent(DNAComponent* com) {
	if (com && allDNAComponents) {
		int index = indexByPtr(allDNAComponents, com);
		if (index >= 0)
			removeFromGenericArray(allDNAComponents, index);
	}
}

void deleteDNAComponent(DNAComponent* com) {
	if (com) {
		removeDNAComponent(com);
		if (com->id) {
			free(com->id);
			com->id = NULL;
		}
		if (com->name) {
			free(com->name);
			com->name = NULL;
		}
		if (com->description) {
			free(com->description);
			com->description = NULL;
		}
		if (com->annotations) {
			free(com->annotations);
			com->annotations = NULL;
		}
		if (com->collections) {
			free(com->collections);
			com->collections = NULL;
		}
		free(com);
	}
}

/**************************
	is... functions
***************************/

int isDNAComponentPtr(const void* pointer) {
	if (!allDNAComponents)
		allDNAComponents = createGenericArray();
	return (int) indexByPtr(allDNAComponents, pointer) >= 0;
}

int isDNAComponentID(const char* id) {
	if (!allDNAComponents)
		allDNAComponents = createGenericArray();
	if (!id)
		return 0;
	int index;
	DNAComponent* com;
	for (index=0; index<allDNAComponents->numInUse; index++) {
		com = (DNAComponent*) allDNAComponents->array[index];
		if (strcmp(com->id, id) == 0)
			return 1;
	}
	return 0;
}

/**************************
	getNum... functions
***************************/

int getNumDNAComponents() {
	if (!allDNAComponents)
		allDNAComponents = createGenericArray();
	return allDNAComponents->numInUse;
}

int getNumCollectionsFor(const DNAComponent* com) {
	if (com)
		return com->numCollections;
	else
		return -1;
}

int getNumSequenceAnnotationsIn(const DNAComponent* com) {
	if (com)
		return com->numAnnotations;
	else
		return -1;
}

/**************************
	getNth... functions
***************************/

DNAComponent* getNthDNAComponent(int n) {
	if (!allDNAComponents)
		allDNAComponents = createGenericArray();
	if (allDNAComponents->numInUse > n)
		return allDNAComponents->array[n];
	else
		return NULL;
}

Collection* getNthCollectionFor(const DNAComponent* com, int n) {
	if (com->numCollections >= n)
		return com->collections[n];
	else
		return NULL;
}

SequenceAnnotation* getNthSequenceAnnotationIn(const DNAComponent* com, int n) {
	if (com->numAnnotations >= n)
		return com->annotations[n];
	else
		return NULL;
}

/**************************
	get... functions
***************************/

DNAComponent* getDNAComponent(const char* id) {
	if (!allDNAComponents)
		allDNAComponents = createGenericArray();
	if (!id)
		return NULL;
	int index;
	DNAComponent* com;
	for (index=0; index<allDNAComponents->numInUse; index++) {
		com = (DNAComponent*) allDNAComponents->array[index];
		if (com->id == id)
			return com;
	}
	return NULL;
}

char* getDNAComponentID(const DNAComponent* com) {
	if (com && com->id) {
		char* id = (char*)malloc(sizeof(char) * strlen(com->id)+1);
		strcpy(id, com->id);
		return id;
	} else
		return NULL;
}

char* getDNAComponentName(const DNAComponent* com) {
	if (com && com->name) {
		char* name = (char*)malloc(sizeof(char) * strlen(com->name)+1);
		strcpy(name, com->name);
		return name;
	} else
		return NULL;
}

char* getDNAComponentDescription(const DNAComponent* com) {
	if (com && com->description) {
		char* descr = (char*)malloc(sizeof(char) * strlen(com->description)+1);
		strcpy(descr, com->description);
		return descr;
	} else
		return NULL;
}

/**************************
	set... functions
***************************/

void setDNAComponentID(DNAComponent* com, const char* id) {
	if (com && id) {
		com->id = (char*)malloc(sizeof(char) * strlen(id)+1);
		strcpy(com->id, id);
	}
}

void setDNAComponentName(DNAComponent* com, const char* name) {
	if (com && name) {
		com->name = (char*)malloc(sizeof(char) * strlen(name)+1);
		strcpy(com->name, name);
	}
}

void setDNAComponentDescription(DNAComponent* com, const char* descr) {
	if (com && descr) {
		com->description = (char*)malloc(sizeof(char) * strlen(descr)+1);
		strcpy(com->description, descr);
	}
}

/**************************
	add annotation
***************************/

void addSequenceAnnotation(DNAComponent* com, SequenceAnnotation* ann) {
	if (!com || !ann)
		return;
	ann->annotates = com;
	if (!com->annotations) {
		// create array
		size_t memory = sizeof(SequenceAnnotation*) * 2;
		com->annotations = (SequenceAnnotation**)malloc(memory);
		// add first value
		com->annotations[0] = ann;
		// finish with null
		com->annotations[1] = NULL;
	} else {
		// create longer array
		int n = com->numAnnotations;
		SequenceAnnotation** old = com->annotations; // TODO memory leak?
		size_t memory = sizeof(SequenceAnnotation*) * (n+2);
		com->annotations = (SequenceAnnotation**)malloc(memory);
		// copy over old values
		int i;
		for (i=0; i<n; ++i)
			com->annotations[i] = old[i];
		// add the new one
		com->annotations[n] = ann;
		// finish with NULL
		com->annotations[n+1] = NULL;
	}
	com->numAnnotations++;
}

void setSubComponent(SequenceAnnotation* ann, DNAComponent* com) {
	if (ann && com)
		ann->subComponent = com;
}

void cleanupDNAComponents() {
	if (allDNAComponents) {
		int index;
		for (index=allDNAComponents->numInUse; index>0; index--)
			deleteDNAComponent( allDNAComponents->array[index] );
		deleteGenericArray(allDNAComponents);
		allDNAComponents = NULL;
	}
}
