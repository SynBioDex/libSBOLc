#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "property.h"
#include "array.h"
#include "object.h"
#include "dnacomponent.h"
#include "sequenceannotation.h"

static PointerArray* allSequenceAnnotations;

void lazyCreateAllSequenceAnnotations() {
	if (!allSequenceAnnotations)
		allSequenceAnnotations = createPointerArray();
}

/*******************
 * create/destroy
 *******************/

void registerSequenceAnnotation(SequenceAnnotation* ann) {
	lazyCreateAllSequenceAnnotations();
	insertPointerIntoArray(allSequenceAnnotations, ann);
}

SequenceAnnotation* createSequenceAnnotation(const char* uri) {
	if (!uri || isSBOLObjectURI(uri))
	    return NULL;
	SequenceAnnotation* ann = malloc(sizeof(SequenceAnnotation));
	ann->base         = createSBOLObject(uri);
	ann->genbankStart = -1;
	ann->genbankEnd   = -1;
	ann->strand       = 1;
	ann->annotates    = NULL;
	ann->subComponent = NULL;
	ann->precedes = createPointerArray();
	ann->processed = 0;
	registerSequenceAnnotation(ann);
	return ann;
}

void removeSequenceAnnotation(SequenceAnnotation* ann) {
	if (ann && allSequenceAnnotations) {
		int index = indexOfPointerInArray(allSequenceAnnotations, ann);
		if (index >= 0)
			removePointerFromArray(allSequenceAnnotations, index);
	}
}

void deleteSequenceAnnotation(SequenceAnnotation* ann) {
	if (ann) {
		if (ann->base)
			deleteSBOLObject(ann->base);
		// TODO will these get deleted correctly?
		if (ann->annotates)
			ann->annotates = NULL;
		if (ann->subComponent)
			ann->subComponent = NULL;
		if (ann->precedes) {
			deletePointerArray(ann->precedes);
			ann->precedes = NULL; // TODO needed?
		}
		removeSequenceAnnotation(ann);
		free(ann);
	}
}

void setSequenceAnnotationURI(SequenceAnnotation* ann, const char* uri) {
    if (ann)
        setSBOLObjectURI(ann->base, uri);
}

void setBioStart(SequenceAnnotation* ann, int start) {
	if (ann)
		ann->genbankStart = start;
}

void setBioEnd(SequenceAnnotation* ann, int end) {
	if (ann)
		ann->genbankEnd = end;
}

// TODO use PolarityProperty
void setStrandPolarity(SequenceAnnotation* ann, int polarity) {
	if (!ann || polarity < -1 || polarity > 1)
		return;
	ann->strand = polarity;
}

/*******************
 * is... functions
 *******************/

int isAnnotationPtr(const void* pointer) {
	lazyCreateAllSequenceAnnotations();
	return (int) indexOfPointerInArray(allSequenceAnnotations, pointer) >= 0;
}

int isSequenceAnnotationURI(const char* uri) {
	lazyCreateAllSequenceAnnotations();
	if (!uri)
		return 0;
	int index;
	char* candidate;
	SequenceAnnotation* ann;
	for (index=0; index < getNumSequenceAnnotations(); index++) {
		ann = getNthSequenceAnnotation(index);
		if (ann) {
			candidate = getSequenceAnnotationURI(ann);
			if (candidate && strcmp(candidate, uri) == 0)
				return 1;
		}
	}
	return 0;
}

/***********************
 * getNum... functions
 ***********************/

int getNumSequenceAnnotations() {
	if (allSequenceAnnotations)
		return getNumPointersInArray(allSequenceAnnotations);
	else
		return 0;
}

int getNumPrecedes(const SequenceAnnotation* ann) {
	if (ann && ann->precedes)
		return getNumPointersInArray(ann->precedes);
	else
		return 0;
}

SequenceAnnotation* getNthSequenceAnnotation(int n) {
	lazyCreateAllSequenceAnnotations();
	if (getNumSequenceAnnotations() > n)
		return getNthPointerInArray(allSequenceAnnotations, n);
	else
		return NULL;
}

/********************
 * get... functions
 ********************/

char* getSequenceAnnotationURI(const SequenceAnnotation* ann) {
    if (ann)
        return getSBOLObjectURI(ann->base);
	else
		return NULL;
}

SequenceAnnotation* getSequenceAnnotation(const char* uri) {
	lazyCreateAllSequenceAnnotations();
	if (!uri)
		return NULL;
	int n;
	char* candidate;
	SequenceAnnotation* ann;
	for (n=0; n < getNumSequenceAnnotations(); n++) {
		ann = getNthSequenceAnnotation(n);
		candidate = getSequenceAnnotationURI(ann);
		if (candidate && strcmp(candidate, uri) == 0)
			return ann;
	}
	return NULL;
}

int getBioStart(const SequenceAnnotation* ann) {
	if (!ann)
		return -1;
	else
		return ann->genbankStart;
}

int getBioEnd(const SequenceAnnotation* ann) {
	if (!ann)
		return -1;
	else
		return ann->genbankEnd;
}

DNAComponent* getSubComponent(const SequenceAnnotation* ann) {
	if (ann)
		return ann->subComponent;
	else
		return NULL;
}

// TODO use PolarityProperty
int getStrandPolarity(const SequenceAnnotation* ann) {
	if (ann)
		return ann->strand;
	else
		return -1;
}

/*******************
 * constrain order
 *******************/

void addPrecedesRelationship(SequenceAnnotation * upstream, SequenceAnnotation * downstream) {
	if (upstream && downstream)
		insertPointerIntoArray(upstream->precedes, downstream);
}

SequenceAnnotation* getNthPrecedes(const SequenceAnnotation* ann, int n) {
	if (ann && getNumPrecedes(ann) >= n)
		return (SequenceAnnotation*) getNthPointerInArray(ann->precedes, n);
	else
		return NULL;
}

int precedes(const SequenceAnnotation* ann1, const SequenceAnnotation* ann2) {
	if (!ann1 || !ann2 || getNumPrecedes(ann1) < 1)
		return 0;
	int n;
	SequenceAnnotation* candidate;
	for (n=0; n<getNumPrecedes(ann1); n++) {
		candidate = getNthPrecedes(ann1, n);
		if (candidate && candidate == ann2)
			return 1;
	}
	return 0;
}

int annotates(const SequenceAnnotation *ann, const DNAComponent *com) {
	if (!ann || !com || !ann->annotates)
		return 0;
	return (int) (ann->annotates == com);
}

void cleanupSequenceAnnotations() {
	if (allSequenceAnnotations) {
		int n;
		SequenceAnnotation* seq;
		for (n=getNumSequenceAnnotations()-1; n>=0; n--) {
			seq = getNthSequenceAnnotation(n);
			deleteSequenceAnnotation(seq);
		}
		deletePointerArray(allSequenceAnnotations);
		allSequenceAnnotations = NULL;
	}
}

void printSequenceAnnotation(const SequenceAnnotation* ann, int tabs) {
    if (!ann)
        return;
    indent(tabs); printf("%s\n", getSequenceAnnotationURI(ann));
    int start = ann->genbankStart;
    int end = ann->genbankEnd;
    if (start != 0 || end != 0) {
    	indent(tabs+1); printf("%i --> %i\n", start, end);
    }
    char strand = polarityToChar(ann->strand);
    indent(tabs+1); printf("strand: %c\n", strand);
    if (ann->annotates) {
        indent(tabs+1); printf("annotates:    %s\n", getDNAComponentURI(ann->annotates));
    }
    if (ann->subComponent) {
        indent(tabs+1); printf("subComponent: %s\n", getDNAComponentURI(ann->subComponent));
    }
    int num = getNumPrecedes(ann);
    if (num > 0) {
        indent(tabs+1); printf("%i precedes:\n", num);
        int i;
        for (i=0; i<num; i++) {
            indent(tabs+2); printf("%s\n", getSequenceAnnotationURI(getNthPrecedes(ann, i)));
        }
    }
}

void printAllSequenceAnnotations() {
    int n;
    int num = getNumSequenceAnnotations();
    if (num > 0) {
        printf("%i annotations:\n", num);
        for (n=0; n<num; n++)
            printSequenceAnnotation(getNthSequenceAnnotation(n), 1);
    }
}
