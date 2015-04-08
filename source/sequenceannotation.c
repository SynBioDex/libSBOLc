#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

/// @todo remove?
<<<<<<< HEAD
#include "sbol.h"
//#include "property.h"
//#include "array.h"
//#include "object.h"
//#include "document.h"
//#include "dnacomponent.h"
//#include "sequenceannotation.h"
=======
#include "property.h"
#include "array.h"
#include "object.h"
#include "document.h"
#include "dnacomponent.h"
#include "sequenceannotation.h"
#include "utilities.h"
>>>>>>> 359edf6a48b340a3707cf503c5a2d495fa27b4d8

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

SequenceAnnotation* copySequenceAnnotation(SequenceAnnotation* ann, char* id_modifier) {
	int i;
	char* copy_uri = augmentURI(getSequenceAnnotationURI(ann), id_modifier);
	SequenceAnnotation* copy = createSequenceAnnotation(ann->doc, copy_uri);
	setSequenceAnnotationStart(copy, getSequenceAnnotationStart(ann));
	setSequenceAnnotationEnd(copy, getSequenceAnnotationEnd(ann));
	setSequenceAnnotationStrand(copy, getSequenceAnnotationStrand(ann));

	// Copy precedes property
	copy->precedes = createPointerArray();
	char *target_uri;
	for (i = 0; i < getNumPointersInArray(ann->precedes); i++) {
		target_uri = (char *)getNthPointerInArray(ann->precedes, i);
		insertPointerIntoArray(copy->precedes, augmentURI(target_uri, id_modifier));
	}

	// Copy SubComponent tree recursively
	if (ann->subComponent) {
		char* sub_com_uri = augmentURI(getDNAComponentURI(ann->subComponent), id_modifier);
		DNAComponent* sub_com_copy = createDNAComponent(ann->doc, sub_com_uri);
		setSequenceAnnotationSubComponent(copy, sub_com_copy);
	}
	return (SequenceAnnotation *)copy;
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
        return (char *)getSBOLObjectURI(ann->base);
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

/// @todo where should this go?
void setSequenceAnnotationSubComponent(SequenceAnnotation* ann, DNAComponent* com) {
	if (ann) {
		ann->subComponent = com;
	}
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
	if (upstream && downstream) {
		char *downstream_uri = getSequenceAnnotationURI(downstream);
		insertPointerIntoArray(upstream->precedes, downstream_uri);
	}
}

void removePrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream) {
	if (upstream && downstream) {
		char *target_uri = getSequenceAnnotationURI(downstream);

		char *query_uri;
		int FOUND = 0; // found URI in list of URIs
		int EOL = 0; // end of list
		int i_uri = 0;  // index of URI in list
		while (!FOUND && !EOL) {
			query_uri = (char *)getNthPointerInArray(upstream->precedes, i_uri);

			if (strcmp(query_uri, target_uri) == 0) {
				FOUND++;
				removePointerFromArray(upstream->precedes, i_uri);
			}
			i_uri++;
			if (i_uri == getNumPointersInArray(upstream->precedes)) {
				EOL++;
			}
		}
	}
	return;
}

SequenceAnnotation* getNthPrecedes(const SequenceAnnotation* ann, int n) {
	if (ann && getNumPrecedes(ann) >= n) {
		char *uri = (char *)getNthPointerInArray(ann->precedes, n);
		return getSequenceAnnotation(ann->doc, uri);
	}
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

void insertAnnotationAfter(SequenceAnnotation* upstream, SequenceAnnotation* new_annotation) {

	//	Update start and end of annotation
	int insert_size = strlen(getDNASequenceNucleotides(getDNAComponentSequence(getSequenceAnnotationSubComponent(new_annotation))));
	int insertion_site = getPositionProperty(upstream->genbankEnd) + 1;
	setSequenceAnnotationStart(new_annotation, insertion_site);
	setSequenceAnnotationEnd(new_annotation, insertion_site + insert_size - 1);


	//  Update precedes relationship of annotations 
	SequenceAnnotation* downstream = NULL;
	if (getNumPointersInArray(upstream->precedes) > 0) {
		downstream = getNthPrecedes(upstream, 0);
		removePrecedesRelationship(upstream, downstream);
		addPrecedesRelationship(upstream, new_annotation);
		addPrecedesRelationship(new_annotation, downstream);
		upstream = new_annotation;

		// Update all start and end indices for annotations downstream from insertion
		int old_start, old_end = 0;
		int new_start = 0;
		int new_end = 0;
		while (getNumPointersInArray(upstream->precedes) > 0) {
			downstream = getNthPrecedes(upstream, 0);
			old_start = getPositionProperty(downstream->genbankStart);
			old_end = getPositionProperty(downstream->genbankEnd);
			new_start = old_start + insert_size;
			new_end = old_end + insert_size;
			setPositionProperty(downstream->genbankStart, new_start);
			setPositionProperty(downstream->genbankEnd, new_end);
			upstream = downstream;
		}
	}
}

void printSequenceAnnotation(const SequenceAnnotation* ann, int tabs) {
    if (!ann)
        return;
    indent(tabs); printf("%s\n", getSequenceAnnotationURI(ann));
	int start = getSequenceAnnotationStart(ann);
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

xmlNode* getNthXMLAnnotationFromSequenceAnnotation(SequenceAnnotation *ann, int index) {
	return getNthStructuredAnnotationAsXML(ann->base, index);
}

void addXMLAnnotationToSequenceAnnotation(SequenceAnnotation *ann, xmlNode *node) {
	addXMLAnnotationToSBOLObject(ann->base, node, ann->doc->xml_doc);
	return;
}

xmlNode* removeXMLAnnotationFromSequenceAnnotation(SequenceAnnotation *ann, int index) {
	xmlNode *node = removeXMLAnnotationFromSBOLObject(ann->base, index, ann->doc->xml_doc);
	return node;
}
