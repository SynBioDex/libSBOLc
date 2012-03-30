#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "property.h"
#include "array.h"
#include "dnacomponent.h"
#include "sequenceannotation.h"
#include "object.h"
#include "dnasequence.h"

static PointerArray* allDNAComponents;

void lazyCreateAllDNAComponents() {
	if (!allDNAComponents)
		allDNAComponents = createPointerArray();
}

/**************************
	create/destroy
***************************/

void registerDNAComponent(DNAComponent* com) {
	lazyCreateAllDNAComponents();
	insertPointerIntoArray(allDNAComponents, com);
}

DNAComponent* createDNAComponent(const char* uri) {
	if (!uri || isSBOLObjectURI(uri))
	    return NULL;
	DNAComponent* com = malloc(sizeof(DNAComponent));
	com->base        = createSBOLCompoundObject(uri);
	com->dnaSequence = NULL;
	com->annotations = createPointerArray();
	registerDNAComponent(com);
	return com;
}

void removeDNAComponent(DNAComponent* com) {
	if (com && allDNAComponents) {
		int index = indexOfPointerInArray(allDNAComponents, com);
		if (index >= 0)
			removePointerFromArray(allDNAComponents, index);
	}
}

void deleteDNAComponent(DNAComponent* com) {
	if (com) {
		if (com->base) {
			deleteSBOLCompoundObject(com->base);
			com->base = NULL;
		}
		if (com->annotations) {
			deletePointerArray(com->annotations);
			com->annotations = NULL;
		}
		removeDNAComponent(com);
		free(com);
		com = NULL;
	}
}

/**************************
	is... functions
***************************/

int isDNAComponent(const void* ptr) {
	if (!allDNAComponents)
		allDNAComponents = createPointerArray();
	return (int) indexOfPointerInArray(allDNAComponents, ptr) >= 0;
}

int isDNAComponentURI(const char* uri) {
	if (!allDNAComponents || !uri)
		return 0;
	int n;
	char* candidate;
	DNAComponent* com;
	for (n=0; n < getNumDNAComponents(); n++) {
		com = getNthDNAComponent(n);
		candidate = getDNAComponentURI(com);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

/**************************
	getNum... functions
***************************/

int getNumDNAComponents() {
	if (allDNAComponents)
		return getNumPointersInArray(allDNAComponents);
	else
		return 0;
}

int getNumSequenceAnnotationsFor(const DNAComponent* com) {
	if (com)
		return getNumPointersInArray(com->annotations);
	else
		return -1;
}

/**************************
	getNth... functions
***************************/

DNAComponent* getNthDNAComponent(int n) {
	if (getNumDNAComponents() > n && n >= 0)
		return (DNAComponent *)getNthPointerInArray(allDNAComponents, n);
	else
		return NULL;
}

SequenceAnnotation* getNthSequenceAnnotationFor(const DNAComponent* com, int n) {
	if (com && getNumSequenceAnnotationsFor(com) > n && n >= 0)
		return (SequenceAnnotation *)getNthPointerInArray(com->annotations, n);
	else
		return NULL;
}

/**************************
	get... functions
***************************/

DNAComponent* getDNAComponent(const char* uri) {
	if (!allDNAComponents || !uri)
		return NULL;
	int n;
	char* candidate;
	DNAComponent* com;
	for (n=0; n < getNumDNAComponents(); n++) {
		com = getNthDNAComponent(n);
		candidate = getDNAComponentURI(com);
		if (candidate && strcmp(candidate, uri) == 0)
			return com;
	}
	return NULL;
}

char* getDNAComponentURI(const DNAComponent* com) {
	if (com)
		return getSBOLCompoundObjectURI(com->base);
	else
		return NULL;
}

char* getDNAComponentDisplayID(const DNAComponent* com) {
    if (com)
        return getSBOLCompoundObjectDisplayID(com->base);
    else
        return NULL;
}

char* getDNAComponentName(const DNAComponent* com) {
	if (com)
		return getSBOLCompoundObjectName(com->base);
	else
		return NULL;
}

char* getDNAComponentDescription(const DNAComponent* com) {
	if (com)
		return getSBOLCompoundObjectDescription(com->base);
	else
		return NULL;
}

DNASequence* getDNAComponentSequence(DNAComponent* com) {
	if (com && com->dnaSequence)
		return com->dnaSequence;
	else
		return NULL;
}

/**************************
	set... functions
***************************/

void setDNAComponentURI(DNAComponent* com, const char* uri) {
	if (com)
		setSBOLCompoundObjectURI(com->base, uri);
}

void setDNAComponentDisplayID(DNAComponent* com, const char* id) {
    if (com)
        setSBOLCompoundObjectDisplayID(com->base, id);
}

void setDNAComponentName(DNAComponent* com, const char* name) {
	if (com)
		setSBOLCompoundObjectName(com->base, name);
}

void setDNAComponentDescription(DNAComponent* com, const char* descr) {
	if (com)
		setSBOLCompoundObjectDescription(com->base, descr);
}

void setDNAComponentSequence(DNAComponent* com, struct _DNASequence* seq) {
	if (com && seq)
		com->dnaSequence = seq;
}

/**************************
	add annotation
***************************/

// TODO make it clear this goes with SequenceAnnotation too
void addSequenceAnnotation(DNAComponent* com, SequenceAnnotation* ann) {
	if (com && ann) {
		insertPointerIntoArray(com->annotations, ann);
	}
}

void setSubComponent(SequenceAnnotation* ann, DNAComponent* com) {
	if (ann) {
		ann->subComponent = com;
	}
}

void cleanupDNAComponents() {
	if (allDNAComponents) {
		int n;
		DNAComponent* com;
		for (n=getNumDNAComponents()-1; n>=0; n--) {
			com = getNthDNAComponent(n);
			deleteDNAComponent(com);
		}
		deletePointerArray(allDNAComponents);
		allDNAComponents = NULL;
	}
}

