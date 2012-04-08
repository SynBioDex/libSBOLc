#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @todo remove?
#include "property.h"
#include "array.h"
#include "document.h"
#include "dnacomponent.h"
#include "sequenceannotation.h"
#include "object.h"
#include "dnasequence.h"

DNAComponent* createDNAComponent(Document* doc, const char* uri) {
	if (!doc || !uri || isSBOLObjectURI(doc, uri))
	    return NULL;
	DNAComponent* com = malloc(sizeof(DNAComponent));
	com->doc         = doc;
	com->base        = createSBOLCompoundObject(doc, uri);
	com->dnaSequence = NULL;
	com->annotations = createPointerArray();
	registerDNAComponent(com);
	return com;
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
		if (com->doc) {
			removeDNAComponent(com->doc, com);
			com->doc = NULL;
		}
		free(com);
		com = NULL;
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

/********************
 * get... functions
 ********************/

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

/********************
 * set... functions
 ********************/

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

/************************
 * annotation functions
 ************************/

// TODO make it clear this goes with SequenceAnnotation too
void addSequenceAnnotation(DNAComponent* com, SequenceAnnotation* ann) {
	if (com && ann) {
		insertPointerIntoArray(com->annotations, ann);
	}
}

int getNumSequenceAnnotationsFor(const DNAComponent* com) {
	if (com)
		return getNumPointersInArray(com->annotations);
	else
		return -1;
}

SequenceAnnotation* getNthSequenceAnnotationFor(const DNAComponent* com, int n) {
	if (com && getNumSequenceAnnotationsFor(com) > n && n >= 0)
		return (SequenceAnnotation *)getNthPointerInArray(com->annotations, n);
	else
		return NULL;
}

/// @todo where should this go?
void setSequenceAnnotationSubComponent(SequenceAnnotation* ann, DNAComponent* com) {
	if (ann) {
		ann->subComponent = com;
	}
}

