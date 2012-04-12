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
	registerSequenceAnnotation(ann);
	return ann;
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

/***********************
 * getNum... functions
 ***********************/

int getNumPrecedes(const SequenceAnnotation* ann) {
	if (ann && ann->precedes)
		return getNumPointersInArray(ann->precedes);
	else
		return 0;
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

void removePrecedesRelationship(SequenceAnnotation* upstream, const SequenceAnnotation* downstream) {
    if (!upstream || !downstream)
        return;
    else {
        int index = indexOfPointerInArray(upstream->precedes, (void*) downstream);
        if (index >= 0)
            removePointerFromArray(upstream->precedes, index);
    }
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

void printSequenceAnnotation(const SequenceAnnotation* ann, int tabs) {
    if (!ann)
        return;
    indent(tabs); printf("%s\n", getSequenceAnnotationURI(ann));
    //int start = ann->genbankStart;
	int start = getSequenceAnnotationStart(ann);
    //int end = ann->genbankEnd;
	int end = getSequenceAnnotationEnd(ann);
    if (start != -1 || end != -1) { /// @todo is 0 valid?
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

