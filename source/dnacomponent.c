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
#include "utilities.h"

DNAComponent* createDNAComponent(Document* doc, const char* uri) {
	if (!doc || !uri || isSBOLObjectURI(doc, uri))
	    return NULL;
	DNAComponent* com = malloc(sizeof(DNAComponent));
	com->doc         = doc;
	com->base        = createSBOLCompoundObject(doc, uri);
	com->dnaSequence = NULL;
	com->annotations = createPointerArray();
    com->type        = createTypeProperty(doc);
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
        if (com->type) {
            deleteTypeProperty(com->type);
            com->type = NULL;
        }
		free(com);
		com = NULL;
	}
}

/// Clone a DNAComponent object
/// TODO:  What rule for the URI of the copy?
DNAComponent* copyDNAComponent(const DNAComponent* com, char* id_modifier) {
	int i;
	if (com) {
		//DNAComponent* copy = createDNAComponent(com->doc, uri);
		char* copy_uri = augmentURI(getDNAComponentURI(com), id_modifier);
		DNAComponent* copy = createDNAComponent(com->doc, copy_uri);
		//setSBOLCompoundObjectDisplayID(copy->base, getSBOLCompoundObjectDisplayID(com->base));
		//setSBOLCompoundObjectName(copy->base, getSBOLCompoundObjectName(com->base));
		//setSBOLCompoundObjectDescription(copy->base, getSBOLCompoundObjectDescription(com->base));
		setDNAComponentDisplayID(copy, getDNAComponentDisplayID(com));
		setDNAComponentName(copy, getDNAComponentName(com));
		setDNAComponentDescription(copy, getDNAComponentDescription(com));
		setDNAComponentType(copy, getDNAComponentType(com));
		setDNAComponentSequence(copy, copyDNASequence(com->dnaSequence, id_modifier));
		for (i = 0; i < getNumSequenceAnnotationsFor(com); i++) {	
			addSequenceAnnotation(copy, copySequenceAnnotation(getNthSequenceAnnotationFor(com, i), id_modifier));
		}
		
		return (DNAComponent *)copy;
	} else 
          return NULL; // TODO: is this right?
}

void printDNAComponent(const DNAComponent* com, int tabs) {
	if (!com)
		return;
	indent(tabs);   printf("%s\n", getDNAComponentURI(com));
	indent(tabs+1); printf("displayID:   %s\n", getDNAComponentDisplayID(com));
	indent(tabs+1); printf("name:        %s\n", getDNAComponentName(com));
	indent(tabs+1); printf("description: %s\n", getDNAComponentDescription(com));
	indent(tabs+1); printf("sequence:    %s\n", getDNASequenceURI(com->dnaSequence));
    indent(tabs+1); printf("type:        %s\n", getDNAComponentType(com));

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
		return (char *)getSBOLCompoundObjectURI(com->base);
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

char* getDNAComponentType(const DNAComponent* com) {
    if (com && com->type)
    {
        TypeProperty* t  = com->type;
        if (t->uri)
            return getURIProperty(t->uri);
        else
          return NULL;
    }
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

void setDNAComponentType(DNAComponent* com, const char* uri) {
    if (com && uri)
    {
        TypeProperty *t = createTypeProperty(com->doc);
        setTypeProperty(t,uri);
        com->type = t;
    }
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

void removeSequenceAnnotationFromDNAComponent(DNAComponent* com, SequenceAnnotation* ann) {
	if (com && ann) {
		int index = indexOfPointerInArray(com->annotations, ann);
		removePointerFromArray(com->annotations, index);
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

void assemble(DNAComponent* parent) {
	// Validate annotations
	SequenceAnnotation* current_annotation = NULL;
	int current_start, current_end = 0;
	int seq_length, cumulative_seq_length = 0;
	int i, j = 0;
	if (getNumSequenceAnnotationsFor(parent) < 1) {
		fprintf(stdout, "Parent component does not have any annotations to assemble");
		return;
	}
	for (i = 0; i < getNumSequenceAnnotationsFor(parent); i++) {
		current_annotation = getNthSequenceAnnotationFor(parent, i);
		if (!current_annotation->subComponent) {
			fprintf(stdout, "Some annotations are missing subComponents\n");
			return;
		}
		if (!current_annotation->subComponent->dnaSequence) {
			fprintf(stdout, "Some subComponents are missing dnaSequences\n");
			return;
		}
		seq_length = strlen(getDNASequenceNucleotides(getDNAComponentSequence(current_annotation->subComponent)));
		current_start = getPositionProperty(current_annotation->genbankStart);
		current_end = getPositionProperty(current_annotation->genbankEnd);
		if (current_start < 0 || current_end < 0) {
			printf("Sequence annotations are not initialized\n");
			return;
		}
		if ((current_end - current_start) > seq_length) {
			printf("Annotation start and end not consistent with sequence length\n");
			printf("%d\t%d\t%d\t%n", current_start, current_end, seq_length);
			return;
		}
		cumulative_seq_length += seq_length;
		printf("Cumulative seq length: %d\n", cumulative_seq_length);
	}

	// Assemble subComponent sequences and assign new parent sequence
	DNASequence* subComponent_seq;
	char* subComponent_seq_nt;
	char* assembled_seq_nt;
	assembled_seq_nt = malloc(cumulative_seq_length + 1);
	assembled_seq_nt[cumulative_seq_length] = '\0';

	for (i = 0; i < getNumSequenceAnnotationsFor(parent); i++) {
		current_annotation = getNthSequenceAnnotationFor(parent, i);
		current_start = getPositionProperty(current_annotation->genbankStart);
		current_start -= 1;  // adjust because C arrays index from 0, GenBank indexes from 1
		subComponent_seq = current_annotation->subComponent->dnaSequence;
		subComponent_seq_nt = getDNASequenceNucleotides(subComponent_seq);
		seq_length = strlen(subComponent_seq_nt);
		for (j = 0; j < seq_length; j++) {
			assembled_seq_nt[current_start + j] = subComponent_seq_nt[j];
			printf("%d\t%c\n", current_start + j, subComponent_seq_nt[j]);
		}
		// Sequence objects at the lower level of the hierarchy must be deleted,
		// otherwise an XML Schema error occurs
		// deleteDNASequence(subComponent_seq);
		// current_annotation->subComponent->dnaSequence = NULL;
	}
	j = 0;
	for (i = 0; i < cumulative_seq_length; i++) {
		if (assembled_seq_nt[i] == '\0') j++;
	}

	setDNASequenceNucleotides(parent->dnaSequence, assembled_seq_nt);
}


void disassemble(DNAComponent* parent) {
	// Should populate subcomponents even if part of parent sequence is not annotated

	// Validate annotations
	if (getNumSequenceAnnotationsFor(parent) < 1) {
		printf("Parent component does not have any annotations to populate");
		return;
	}
	// Check if parent has valid sequence
	int seq_length = 0;
	char* parent_seq_nt;
	if (!parent->dnaSequence->nucleotides) {
		printf("Parent component does not have a valid sequence");
		return;
	}
	parent_seq_nt = getDNASequenceNucleotides(getDNAComponentSequence(parent));
	seq_length = strlen(parent_seq_nt);


	// Check if annotation starts and ends are initialized (-1 is the default)
	// Check if largest end value is less than length of parent sequence
	SequenceAnnotation* current_annotation = NULL;
	int current_start, current_end = 0;
	int i, j = 0;
	for (i = 0; i < getNumSequenceAnnotationsFor(parent); i++) {
		current_annotation = getNthSequenceAnnotationFor(parent, i);
		current_start = getPositionProperty(current_annotation->genbankStart);
		current_end = getPositionProperty(current_annotation->genbankEnd);
		if (current_start < 0 || current_end < 0) {
			printf("Sequence annotations are not initialized");
			return;
		}
		if (current_start > seq_length || current_end > seq_length) {
			printf("Annotation start or end exceeds parent sequence length");
			return;
		}
	}

	// Check if annotations are already populated with subcomponents and sequences
	for (i = 0; i < getNumSequenceAnnotationsFor(parent); i++) {
		current_annotation = getNthSequenceAnnotationFor(parent, i);
		// instantiate new DNAComponent and attach to current annotation
		if (!current_annotation->subComponent) {
			// @TODO: instantiate new DNAComponent
		}

		// instantatiate new DNASequence and attach to subComponent
		DNASequence* new_seq = NULL;
		char* DEFAULT_SEQ_URI = "http://examples.org//subComponent";
		char* indexed_seq_URI;
		int digits = 1;
		int max = 10;
		if (!current_annotation->subComponent->dnaSequence) {
			// create unique URI for each new dnaSequence object
			// @TODO define a rule for default URIs
			// @TODO define a function that appends indices to URIs that make up an aggregation
			while (i / max) {
				digits++;
				max *= 10;
			}
			indexed_seq_URI = malloc(strlen(DEFAULT_SEQ_URI) + digits + 2);
			sprintf(indexed_seq_URI, "%s_%d\0", DEFAULT_SEQ_URI, i); // append index to default URI
			new_seq = createDNASequence(parent->doc, indexed_seq_URI);
			if (current_annotation->subComponent && new_seq) {
				setDNAComponentSequence(current_annotation->subComponent, new_seq);
			}
		}
		// Extract subsequence from parent and assign to subcomponent
		char* subComponent_seq_nt = NULL;
		current_start = getPositionProperty(current_annotation->genbankStart);
		current_start -= 1;  // adjust because C arrays index from 0, GenBank indexes from 1
		current_end = getPositionProperty(current_annotation->genbankEnd);
		current_end -= 1;  // adjust because C arrays index from 0, GenBank indexes from 1
		seq_length = current_end + 1 - current_start;
		subComponent_seq_nt = malloc(seq_length + 1);
		subComponent_seq_nt[seq_length] = '\0';

		for (j = 0; j < seq_length; j++) {
			subComponent_seq_nt[j] = parent_seq_nt[j + current_start];
		}
		new_seq = getDNAComponentSequence(current_annotation->subComponent);
		setDNASequenceNucleotides(new_seq, subComponent_seq_nt);
		setDNAComponentSequence(current_annotation->subComponent, new_seq);
	}
}


/************************
* arbitrary xml annotation of DNAComponent objects
************************/

xmlNode* getNthXMLAnnotationFromDNAComponent(DNAComponent *com, int index) {
	return getNthStructuredAnnotationAsXML(com->base->base, index);
}

// Annotate a DNAComponent with extra data structured as XML
void addXMLAnnotationToDNAComponent(DNAComponent* com, xmlNode *node) {
	addXMLAnnotationToSBOLObject(com->base->base, node, com->doc->xml_doc);
	return;
}

// Remove XML annotation from DNAComponent
xmlNode* removeXMLAnnotationFromDNAComponent(DNAComponent *com, int index) {
	xmlNode *node = removeXMLAnnotationFromSBOLObject(com->base->base, index, com->doc->xml_doc);
	return node;
}


