#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @todo remove?
#include "property.h"
#include "array.h"
#include "dnacomponent.h"
#include "sequenceannotation.h"
#include "object.h"
#include "dnasequence.h"

/*static PointerArray* allDNAComponents;*/

/*void lazyCreateAllDNAComponents() {*/
/*	if (!allDNAComponents)*/
/*		allDNAComponents = createPointerArray();*/
/*}*/

/**************************
	create/destroy
***************************/

void registerDNAComponent(Document* doc, DNAComponent* com) {
	if (doc && doc->allDNAComponents) {
		insertPointerIntoArray(doc->allDNAComponents, com);
	}
}

DNAComponent* createDNAComponent(Document* doc, const char* uri) {
	if (!doc || !uri || isSBOLObjectURI(doc, uri))
	    return NULL;
	DNAComponent* com = malloc(sizeof(DNAComponent));
	com->base        = createSBOLCompoundObject(doc, uri);
	com->dnaSequence = NULL;
	com->annotations = createPointerArray();
	registerDNAComponent(doc, com);
	return com;
}

void removeDNAComponent(Document* doc, DNAComponent* com) {
	if (doc && doc->allDNAComponents && com) {
		int index = indexOfPointerInArray(doc->allDNAComponents, com);
		if (index >= 0)
			removePointerFromArray(doc->allDNAComponents, index);
	}
}

void deleteDNAComponent(Document* doc, DNAComponent* com) {
	if (doc && com) {
		if (com->base) {
			deleteSBOLCompoundObject(com->base);
			com->base = NULL;
		}
		if (com->annotations) {
			deletePointerArray(com->annotations);
			com->annotations = NULL;
		}
		removeDNAComponent(doc, com);
		free(com);
		com = NULL;
	}
}

/**************************
	is... functions
***************************/

int isDNAComponent(Document* doc, const void* ptr) {
	if (doc) {
		return (int) indexOfPointerInArray(doc->allDNAComponents, ptr) >= 0;
	} else
		return 0; /// @todo return -1 instead?
}

int isDNAComponentURI(Document* doc, const char* uri) {
	if (!doc || !doc->allDNAComponents || !uri)
		return 0;
	int n;
	char* candidate;
	DNAComponent* com;
	for (n=0; n < getNumDNAComponents(doc); n++) {
		com = getNthDNAComponent(doc, n);
		candidate = getDNAComponentURI(com);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

/**************************
	getNum... functions
***************************/

int getNumDNAComponents(Document* doc) {
	if (doc && doc->allDNAComponents)
		return getNumPointersInArray(doc->allDNAComponents);
	else
		return 0; /// @todo return -1 instead?
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

DNAComponent* getNthDNAComponent(Document* doc, int n) {
	if (doc && getNumDNAComponents(doc) > n && n >= 0)
		return (DNAComponent *)getNthPointerInArray(doc->allDNAComponents, n);
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

DNAComponent* getDNAComponent(Document* doc, const char* uri) {
	if (!doc || !doc->allDNAComponents || !uri)
		return NULL;
	int n;
	char* candidate;
	DNAComponent* com;
	for (n=0; n < getNumDNAComponents(doc); n++) {
		com = getNthDNAComponent(doc, n);
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

void setDNAComponentSequence(DNAComponent* com, DNASequence* seq) {
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

void setSequenceAnnotationSubComponent(SequenceAnnotation* ann, DNAComponent* com) {
	if (ann) {
		ann->subComponent = com;
	}
}

void cleanupDNAComponents(Document* doc) {
	if (doc && doc->allDNAComponents) {
		int n;
		DNAComponent* com;
		for (n=getNumDNAComponents(doc)-1; n>=0; n--) {
			com = getNthDNAComponent(doc, n);
			deleteDNAComponent(doc, com);
		}
		deletePointerArray(doc->allDNAComponents);
		doc->allDNAComponents = NULL;
	}
}

void printDNAComponent(const DNAComponent* com, int tabs) {
	if (!com)
		return;
	indent(tabs);   printf("%s\n", getDNAComponentURI(com));
	indent(tabs+1); printf("displayID:   %s\n", getDNAComponentDisplayID(com));
	indent(tabs+1); printf("name:        %s\n", getDNAComponentName(com));
	indent(tabs+1); printf("description: %s\n", getDNAComponentDescription(com));
	indent(tabs+1); printf("sequence:    %s\n", getDNASequenceURI(com->dnaSequence));
	
	SequenceAnnotation* seq;
	int i;
	int num = getNumSequenceAnnotationsFor(com);
	if (num > 0) {
		indent(tabs+1); printf("%i annotations:\n", num);
		for (i=0; i<num; i++) {
			seq = getNthSequenceAnnotationFor(com, i);
			indent(tabs+2); printf("%s\n", getSequenceAnnotationURI(seq));
		}
	}
}

void printAllDNAComponents(Document* doc) {
	int n;
	int num = getNumDNAComponents(doc);
	if (num > 0) {
		printf("%i components:\n", num);
		for (n=0; n<num; n++)
			printDNAComponent(getNthDNAComponent(doc, n), 1);
	}
}

