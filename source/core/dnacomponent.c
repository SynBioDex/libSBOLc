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
	com->annotations = createGenericArray();
	com->collections = createGenericArray();
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
			deleteGenericArray(com->annotations);
			com->annotations = NULL;
		}
		if (com->collections) {
			deleteGenericArray(com->collections);
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
		return com->collections->numInUse;
	else
		return -1;
}

int getNumSequenceAnnotationsIn(const DNAComponent* com) {
	if (com)
		return com->annotations->numInUse;
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
	if (com->collections->numInUse >= n)
		return (Collection*) com->collections->array[n];
	else
		return NULL;
}

SequenceAnnotation* getNthSequenceAnnotationIn(const DNAComponent* com, int n) {
	if (com->annotations->numInUse >= n)
		return (SequenceAnnotation*) com->annotations->array[n];
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
	if (com && ann) {
		insertIntoGenericArray(com->annotations, ann);
	}
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
