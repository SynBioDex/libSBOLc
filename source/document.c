#include <stdio.h>
#include <stdlib.h>

#include "document.h"
#include "array.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"

/********************
 * isXURI functions
 ********************/

int isDNASequenceURI(Document* doc, const char* uri) {
	if (!doc || !uri)
		return 0; /// @todo return -1 instead?
	int n;
	char* candidate;
	DNASequence* seq;
	for (n=0; n < getNumDNASequences(doc); n++) {
		seq = getNthDNASequence(doc, n);
		candidate = getDNASequenceURI(seq);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

int isSequenceAnnotationURI(Document* doc, const char* uri) {
	if (!doc || !uri)
		return 0; /// @todo return -1 instead?
	int n;
	char* candidate;
	SequenceAnnotation* ann;
	for (n=0; n < getNumSequenceAnnotations(doc); n++) {
		ann = getNthSequenceAnnotation(doc, n);
		candidate = getSequenceAnnotationURI(ann);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

int isDNAComponentURI(Document* doc, const char* uri) {
	if (!doc || !uri)
		return 0; /// @todo return -1 instead?
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

int isCollectionURI(Document* doc, const char* uri) {
	if (!doc || !uri)
		return 0; /// @todo return -1 instead?
	int n;
	char* candidate;
	Collection* col;
	for (n=0; n < getNumCollections(doc); n++) {
		col = getNthCollection(doc, n);
		candidate = getCollectionURI(col);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

int isSBOLObjectURI(Document* doc, const char* uri) {
	return isDNASequenceURI(doc, uri)
		|| isSequenceAnnotationURI(doc, uri)
		|| isDNAComponentURI(doc, uri)
		|| isCollectionURI(doc, uri);
}

/***********************
 * registerX functions
 ***********************/

void registerDNASequence(DNASequence* seq) {
	if (seq && seq->doc) {
		insertPointerIntoArray(seq->doc->allDNASequences, seq);
	}
}

void registerSequenceAnnotation(SequenceAnnotation* ann) {
	if (ann && ann->doc) {
		insertPointerIntoArray(ann->doc->allSequenceAnnotations, ann);
	}
}

void registerDNAComponent(DNAComponent* com) {
	if (com && com->doc) {
		insertPointerIntoArray(com->doc->allDNAComponents, com);
	}
}

void registerCollection(Collection* col) {
	if (col && col->doc) {
		insertPointerIntoArray(col->doc->allCollections, col);
	}
}

/*********************
 * removeX functions
 *********************/

void removeDNASequence(Document* doc, DNASequence* seq) {
	if (doc && doc->allDNASequences && seq) {
		int index = indexOfPointerInArray(doc->allDNASequences, seq);
		if (index >= 0)
			removePointerFromArray(doc->allDNASequences, index);
	}
}

void removeSequenceAnnotation(Document* doc, SequenceAnnotation* ann) {
	if (doc && doc->allSequenceAnnotations && ann) {
		int index = indexOfPointerInArray(doc->allSequenceAnnotations, ann);
		if (index >= 0)
			removePointerFromArray(doc->allSequenceAnnotations, index);
	}
}

void removeDNAComponent(Document* doc, DNAComponent* com) {
	if (doc && doc->allDNAComponents && com) {
		int index = indexOfPointerInArray(doc->allDNAComponents, com);
		if (index >= 0)
			removePointerFromArray(doc->allDNAComponents, index);
	}
}

void removeCollection(Document* doc, Collection* col) {
	if (doc && doc->allCollections && col) {
		int index = indexOfPointerInArray(doc->allCollections, col);
		if (index >= 0)
			removePointerFromArray(doc->allCollections, index);
	}
}

/*********************
 * getNumX functions
 *********************/

int getNumDNASequences(const Document* doc) {
	if (doc && doc->allDNASequences)
	    return getNumPointersInArray(doc->allDNASequences);
	else
	    return 0;
}

int getNumSequenceAnnotations(Document* doc) {
	if (doc && doc->allSequenceAnnotations)
		return getNumPointersInArray(doc->allSequenceAnnotations);
	else
		return 0;
}

int getNumDNAComponents(const Document* doc) {
	if (doc && doc->allDNAComponents)
		return getNumPointersInArray(doc->allDNAComponents);
	else
		return 0; /// @todo return -1 instead?
}

int getNumCollections(Document* doc) {
	if (doc && doc->allCollections)
		return getNumPointersInArray(doc->allCollections);
	else
		return 0; /// @todo return -1 instead?
}

int getNumSBOLObjects(Document* doc) {
	if (doc)
		return getNumDNASequences(doc)
			+ getNumSequenceAnnotations(doc)
			+ getNumDNAComponents(doc)
			+ getNumCollections(doc);
	else
		return -1;
}

/*****************
 * isX functions
 *****************/

int isDNASequence(const Document* doc, const void* pointer) {
	if (doc) {
		return (int) indexOfPointerInArray(doc->allDNASequences, pointer) >= 0;
	} else
		return 0; /// @todo return -1 instead?
}

int isSequenceAnnotation(const Document* doc, const void* pointer) {
	if (doc) {
		return (int) indexOfPointerInArray(doc->allSequenceAnnotations, pointer) >= 0;
	} else
		return 0; /// @ todo return -1 instead?
}

int isDNAComponent(const Document* doc, const void* ptr) {
	if (doc) {
		return (int) indexOfPointerInArray(doc->allDNAComponents, ptr) >= 0;
	} else
		return 0; /// @todo return -1 instead?
}

int isCollection(Document* doc, const void* pointer) {
	if (doc && doc->allCollections && pointer) {
		return pointerContainedInArray(doc->allCollections, pointer);
	}
}

/******************
 * getX functions
 ******************/

DNASequence* getDNASequence(Document* doc, const char* uri) {
	if (!doc || !uri)
		return NULL;
	int n;
	char* candidate;
	DNASequence* seq;
	for (n=0; n < getNumDNASequences(doc); n++) {
		seq = getNthDNASequence(doc, n);
		candidate = getDNASequenceURI(seq);
		if (candidate && strcmp(candidate, uri) == 0)
			return seq;
	}
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

DNAComponent* getDNAComponent(Document* doc, const char* uri) {
	if (!doc || !uri)
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

Collection* getCollection(Document* doc, const char* uri) {
	if (!doc || !uri)
		return NULL;
	int n;
	char* candidate;
	Collection* col;
	for (n=0; n < getNumCollections(doc); n++) {
		col = getNthCollection(doc, n);
		candidate = getCollectionURI(col);
		if (candidate && strcmp(candidate, uri) == 0)
			return col;
	}
	return NULL;
}

/*********************
 * getNthX functions
 *********************/

DNASequence* getNthDNASequence(Document* doc, int n) {
	if (doc && getNumDNASequences(doc) > n && n >= 0)
		return (DNASequence*) getNthPointerInArray(doc->allDNASequences, n);
	else
		return NULL;
}

SequenceAnnotation* getNthSequenceAnnotation(Document* doc, int n) {
	if (doc && getNumSequenceAnnotations(doc) > n)
		return getNthPointerInArray(doc->allSequenceAnnotations, n);
	else
		return NULL;
}

DNAComponent* getNthDNAComponent(Document* doc, int n) {
	if (doc && getNumDNAComponents(doc) > n && n >= 0)
		return (DNAComponent *)getNthPointerInArray(doc->allDNAComponents, n);
	else
		return NULL;
}

Collection* getNthCollection(Document* doc, int n) {
    if (doc && getNumCollections(doc) > n && n >= 0)
        return (Collection *)getNthPointerInArray(doc->allCollections, n);
    else
        return NULL;
}

/****************************
 * whole-Document functions
 ****************************/

Document* createDocument() {
	Document* doc = malloc(sizeof(Document));
	doc->allDNASequences        = createPointerArray();
	doc->allSequenceAnnotations = createPointerArray();
	doc->allDNAComponents       = createPointerArray();
	doc->allCollections         = createPointerArray();
	return doc;
}

void deleteDocument(Document* doc) {
	if (!doc)
		return;
	int n;

	// sequences
	if (doc->allDNASequences) {
		DNASequence* seq;
		for (n=0; n<getNumDNASequences(doc); n++) {
			seq = getNthDNASequence(doc, n);
			deleteDNASequence(seq);
			seq = NULL;
		}
		deletePointerArray(doc->allDNASequences);
		doc->allDNASequences = NULL;
	}

	// annotations
	if (doc->allSequenceAnnotations) {
		SequenceAnnotation* seq;
		for (n=0; n<getNumSequenceAnnotations(doc); n++) {
			seq = getNthSequenceAnnotation(doc, n);
			deleteSequenceAnnotation(seq);
		}
		deletePointerArray(doc->allSequenceAnnotations);
		doc->allSequenceAnnotations = NULL;
	}

	// components
	if (doc->allDNAComponents) {
		DNAComponent* com;
		for (n=0; n<getNumDNAComponents(doc); n++) {
			com = getNthDNAComponent(doc, n);
			deleteDNAComponent(com);
		}
		deletePointerArray(doc->allDNAComponents);
		doc->allDNAComponents = NULL;
	}

	// collections
	if (doc->allCollections) {
		Collection* col;
		for (n=0; n<getNumCollections(doc); n++) {
       		col = getNthCollection(doc, n);
			removeCollection(doc, col);
			deleteCollection(col);
		}
		deletePointerArray(doc->allCollections);
		doc->allCollections = NULL;
	}

	free(doc);
	doc = NULL;
}

void printDocument(Document* doc) {
	if (!doc)
		return;
	int n;
	int total;

	// sequences
	total = getNumDNASequences(doc);
	if (total > 0) printf("%i sequences:\n", total);
	for (n=0; n<total; n++)
	printDNASequence(getNthDNASequence(doc, n), 1);

	// annotations
    total = getNumSequenceAnnotations(doc);
    if (total > 0) printf("%i annotations:\n", total);
    for (n=0; n<total; n++)
    	printSequenceAnnotation(getNthSequenceAnnotation(doc, n), 1);

	// components
	total = getNumDNAComponents(doc);
	if (total > 0) printf("%i components:\n", total);
	for (n=0; n<total; n++)
		printDNAComponent(getNthDNAComponent(doc, n), 1);

	// collections
    total = getNumCollections(doc);
    if (total > 0) printf("%i collections:\n", total);
    for (n=0; n<total; n++)
        printCollection(getNthCollection(doc, n), 1);
}

