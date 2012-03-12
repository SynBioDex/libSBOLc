#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "property.h"
#include "genericarray.h"
#include "dnacomponent.h"
#include "sequenceannotation.h"

static GenericArray* allSequenceAnnotations;

/*******************
 * create/destroy
 *******************/

void registerSequenceAnnotation(SequenceAnnotation* ann) {
	if (!allSequenceAnnotations)
		allSequenceAnnotations = createGenericArray();
	insertIntoGenericArray(allSequenceAnnotations, ann);
}

SequenceAnnotation* createSequenceAnnotation(const char* uri) {
	if (!uri || isDuplicateURI(uri))
	    return NULL;
	SequenceAnnotation* ann;
	ann = (SequenceAnnotation*)malloc(sizeof(SequenceAnnotation));
	ann->uri          = createURI();
	ann->genbankStart = 0;
	ann->genbankEnd   = 0;
	ann->strand       = 1;
	ann->annotates    = NULL;
	ann->subComponent = NULL;
	ann->precedes = createGenericArray();
	ann->processed = 0;
	setSequenceAnnotationURI(ann, uri);
	registerSequenceAnnotation(ann);
	return ann;
}

void removeSequenceAnnotation(SequenceAnnotation* ann) {
	if (ann && allSequenceAnnotations) {
		int index = indexByPtr(allSequenceAnnotations, ann);
		if (index >= 0)
			removeFromGenericArray(allSequenceAnnotations, index);
	}
}

void deleteSequenceAnnotation(SequenceAnnotation* ann) {
	if (ann) {
		removeSequenceAnnotation(ann);
		if (ann->uri) {
			deleteURI(ann->uri);
			ann->uri = NULL;
		}
		// TODO will these delete parts of other structs?
		if (ann->annotates) {
			ann->annotates = NULL;
		}
		if (ann->subComponent) {
			ann->subComponent = NULL;
		}
		if (ann->precedes) {
			deleteGenericArray(ann->precedes);
			//free(ann->precedes);
			ann->precedes = NULL;
		}
		free(ann);
	}
}

void setSequenceAnnotationURI(SequenceAnnotation* ann, const char* uri) {
    if (ann)
        setURI(ann->uri, uri);
}

void setBioStart(SequenceAnnotation* ann, int start) {
	if (ann)
		ann->genbankStart = start;
}

void setBioEnd(SequenceAnnotation* ann, int end) {
	if (ann)
		ann->genbankEnd = end;
}

void setStrandPolarity(SequenceAnnotation* ann, int polarity) {
	if (!ann || polarity < -1 || polarity > 1)
		return;
	ann->strand = polarity;
}

/*******************
 * is... functions
 *******************/

int isAnnotationPtr(const void* pointer) {
	if (!allSequenceAnnotations)
		allSequenceAnnotations = createGenericArray();
	return (int) indexByPtr(allSequenceAnnotations, pointer) >= 0;
}

int isSequenceAnnotationURI(const char* uri) {
	if (!allSequenceAnnotations)
		allSequenceAnnotations = createGenericArray();
	if (!uri)
		return 0;
	int index;
	char* candidate;
	SequenceAnnotation* ann;
	for (index=0; index<getNumSequenceAnnotations(); index++) {
		ann = getNthSequenceAnnotation(index);
		if (ann) {
			candidate = getURI(ann->uri);
			if (strcmp(candidate, uri) == 0)
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
		return allSequenceAnnotations->numInUse;
	else
		return 0;
}

int getNumPrecedes(const SequenceAnnotation* ann) {
	if (ann && ann->precedes)
		return ann->precedes->numInUse;
	else
		return 0;
}

SequenceAnnotation* getNthSequenceAnnotation(int n) {
	if (!allSequenceAnnotations)
		allSequenceAnnotations = createGenericArray();
	if (allSequenceAnnotations->numInUse > n)
		return allSequenceAnnotations->array[n];
	else
		return NULL;
}

/********************
 * get... functions
 ********************/

char* getSequenceAnnotationURI(const SequenceAnnotation* ann) {
    if (ann)
        return getURI(ann->uri);
}

SequenceAnnotation* getSequenceAnnotation(const char* uri) {
	if (!allSequenceAnnotations)
		allSequenceAnnotations = createGenericArray();
	if (!uri)
		return NULL;
	int index;
	char* candidate;
	SequenceAnnotation* ann;
	for (index=0; index<allSequenceAnnotations->numInUse; index++) {
		ann = (SequenceAnnotation*) allSequenceAnnotations->array[index];
		candidate = getURI(ann->uri);
		if (strcmp(candidate, uri) == 0)
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
		insertIntoGenericArray(upstream->precedes, downstream);
}

SequenceAnnotation* getNthPrecedes(const SequenceAnnotation* ann, int n) {
	if (ann && ann->precedes->numInUse >= n)
		return (SequenceAnnotation*) ann->precedes->array[n];
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
		if (candidate == ann2)
			return 1;
	}
	return 0;
}

void cleanupSequenceAnnotations() {
	if (allSequenceAnnotations) {
		int n;
		SequenceAnnotation* seq;
		for (n=getNumSequenceAnnotations()-1; n>=0; n--) {
			seq = getNthSequenceAnnotation(n);
			deleteSequenceAnnotation(seq);
		}
		deleteGenericArray(allSequenceAnnotations);
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
    if (ann->annotates) {
        indent(tabs+1); printf("annotates: %s\n", getDNAComponentURI(ann->annotates));
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
