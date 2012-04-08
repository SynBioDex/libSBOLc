#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @todo remove?
#include "property.h"
#include "array.h"
#include "object.h"
#include "document.h"
#include "dnacomponent.h"
#include "sequenceannotation.h"

/// @todo group functions by doc-level and object-level

/*******************
 * create/destroy
 *******************/

SequenceAnnotation* createSequenceAnnotation(Document* doc, const char* uri) {
	if (!doc || !uri || isSBOLObjectURI(doc, uri))
	    return NULL;
	SequenceAnnotation* ann = malloc(sizeof(SequenceAnnotation));
	ann->doc          = doc;
	ann->base         = createSBOLObject(doc, uri);
	ann->genbankStart = createPositionProperty();
	ann->genbankEnd   = createPositionProperty();
	//ann->strand       = 1;
	ann->strand       = createPolarityProperty();
	ann->subComponent = NULL;
	ann->precedes = createPointerArray();
	insertPointerIntoArray(doc->allSequenceAnnotations, ann);	
	return ann;
}

void removeSequenceAnnotation(Document* doc, SequenceAnnotation* ann) {
	if (doc && doc->allSequenceAnnotations && ann) {
		int index = indexOfPointerInArray(doc->allSequenceAnnotations, ann);
		if (index >= 0)
			removePointerFromArray(doc->allSequenceAnnotations, index);
	}
}

void deleteSequenceAnnotation(SequenceAnnotation* ann) {
	if (ann) {
		if (ann->base)
			deleteSBOLObject(ann->base);
			ann->base = NULL;
		if (ann->subComponent)
			ann->subComponent = NULL;
		if (ann->precedes) {
			deletePointerArray(ann->precedes);
			ann->precedes = NULL; // TODO needed?
		}
		if (ann->doc) {
			removeSequenceAnnotation(ann->doc, ann);
			ann->doc = NULL;
		}
		free(ann);
		ann = NULL;
	}
}

void setSequenceAnnotationURI(SequenceAnnotation* ann, const char* uri) {
    if (ann)
        setSBOLObjectURI(ann->base, uri);
}

void setSequenceAnnotationStart(SequenceAnnotation* ann, int start) {
	if (ann)
		setPositionProperty(ann->genbankStart, start);
}

void setSequenceAnnotationEnd(SequenceAnnotation* ann, int end) {
	if (ann)
		setPositionProperty(ann->genbankEnd, end);
}

// TODO use PolarityProperty
void setSequenceAnnotationStrand(SequenceAnnotation* ann, int polarity) {
	if (!ann || polarity < -1 || polarity > 1)
		return;
	setPolarityProperty(ann->strand, polarity);
}

/*******************
 * is... functions
 *******************/

int isSequenceAnnotation(const Document* doc, const void* pointer) {
	if (doc) {
		return (int) indexOfPointerInArray(doc->allSequenceAnnotations, pointer) >= 0;
	} else
		return 0; /// @ todo return -1 instead?
}

int isSequenceAnnotationURI(Document* doc, const char* uri) {
	if (!doc || !uri)
		return 0;
	int index;
	char* candidate;
	SequenceAnnotation* ann;
	for (index=0; index < getNumSequenceAnnotations(doc); index++) {
		ann = getNthSequenceAnnotation(doc, index);
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

int getNumSequenceAnnotations(Document* doc) {
	if (doc && doc->allSequenceAnnotations)
		return getNumPointersInArray(doc->allSequenceAnnotations);
	else
		return 0;
}

int getNumPrecedes(const SequenceAnnotation* ann) {
	if (ann && ann->precedes)
		return getNumPointersInArray(ann->precedes);
	else
		return 0;
}

SequenceAnnotation* getNthSequenceAnnotation(Document* doc, int n) {
	if (doc && getNumSequenceAnnotations(doc) > n)
		return getNthPointerInArray(doc->allSequenceAnnotations, n);
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

SequenceAnnotation* getSequenceAnnotation(Document* doc, const char* uri) {
	if (!doc || !uri)
		return NULL;
	int n;
	char* candidate;
	SequenceAnnotation* ann;
	for (n=0; n < getNumSequenceAnnotations(doc); n++) {
		ann = getNthSequenceAnnotation(doc, n);
		candidate = getSequenceAnnotationURI(ann);
		if (candidate && strcmp(candidate, uri) == 0)
			return ann;
	}
	return NULL;
}

int getSequenceAnnotationStart(const SequenceAnnotation* ann) {
	if (!ann)
		return -1;
	else
		return getPositionProperty(ann->genbankStart);
}

int getSequenceAnnotationEnd(const SequenceAnnotation* ann) {
	if (!ann)
		return -1;
	else
		return getPositionProperty(ann->genbankEnd);
}

DNAComponent* getSequenceAnnotationSubComponent(const SequenceAnnotation* ann) {
	if (ann)
		return ann->subComponent;
	else
		return NULL;
}

int getSequenceAnnotationStrand(const SequenceAnnotation* ann) {
	if (ann)
		return getPolarityProperty(ann->strand);
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

void cleanupSequenceAnnotations(Document* doc) {
	if (doc && doc->allSequenceAnnotations) {
		int n;
		SequenceAnnotation* seq;
		for (n=getNumSequenceAnnotations(doc)-1; n>=0; n--) {
			seq = getNthSequenceAnnotation(doc, n);
			deleteSequenceAnnotation(seq);
		}
		deletePointerArray(doc->allSequenceAnnotations);
		doc->allSequenceAnnotations = NULL;
	}
}

void printSequenceAnnotation(const SequenceAnnotation* ann, int tabs) {
    if (!ann)
        return;
    indent(tabs); printf("%s\n", getSequenceAnnotationURI(ann));
    //int start = ann->genbankStart;
	int start = getSequenceAnnotationStart(ann);
    //int end = ann->genbankEnd;
	int end = getSequenceAnnotationEnd(ann);
    if (start != 0 || end != 0) {
    	indent(tabs+1); printf("%i --> %i\n", start, end);
    }
    char strand = polarityToChar( getPolarityProperty(ann->strand) );
    indent(tabs+1); printf("strand: %c\n", strand);
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

void printAllSequenceAnnotations(Document* doc) {
	if (!doc)
		return;
    int n;
    int num = getNumSequenceAnnotations(doc);
    if (num > 0) {
        printf("%i annotations:\n", num);
        for (n=0; n<num; n++)
            printSequenceAnnotation(getNthSequenceAnnotation(doc, n), 1);
    }
}

