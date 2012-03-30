#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"

void indent(int tabs) {
    if (tabs<0)
        tabs = 0;
    int i;
    for (i=0; i<tabs; i++)
        printf("\t");
}

void printDNASequence(const DNASequence* seq, int tabs) {
	if (!seq)
	    return;
	// TODO print just the beginning of the sequence?
	char* uri = getDNASequenceURI(seq);
	indent(tabs);
	if (strlen(uri) > 30)
		printf("%.30s\n", uri);
	else
		printf("%s\n", uri);
	indent(tabs+1); printf("nucleotides: %s\n", getNucleotides(seq));
}

void printSequenceAnnotation(const SequenceAnnotation* ann, int tabs) {
    if (!ann)
        return;
    indent(tabs); printf("%s\n", getSequenceAnnotationURI(ann));
    //int start = ann->genbankStart;
	int start = getBioStart(ann);
    //int end = ann->genbankEnd;
	int end = getBioEnd(ann);
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

void printCollection(const Collection* col, int tabs) {
    if (!col)
        return;
    indent(tabs);   printf("uri: %s\n", getCollectionURI(col));
    indent(tabs+1); printf("name:        %s\n", getCollectionName(col));
    indent(tabs+1); printf("description: %s\n", getCollectionDescription(col));
    int i;
    int num;
    if (col->components) {
        DNAComponent* com;
        num = getNumDNAComponentsIn(col);
        if (num > 0) {
            indent(tabs+1); printf("%i components:\n", num);
            for (i=0; i<num; i++) {
                com = getNthDNAComponentIn(col, i);
                indent(tabs+2); printf("%s\n", getDNAComponentURI(com));
            }
        }
    }
}

void printAllDNASequences() {
	int n;
	int num = getNumDNASequences();
	if (num > 0) {
	    printf("%i sequences:\n", num);
	    for (n=0; n<num; n++)
	        printDNASequence(getNthDNASequence(n), 1);
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

void printAllDNAComponents() {
	int n;
	int num = getNumDNAComponents();
	if (num > 0) {
		printf("%i components:\n", num);
		for (n=0; n<num; n++)
			printDNAComponent(getNthDNAComponent(n), 1);
	}
}

void printAllCollections() {
    int n;
    int num = getNumCollections();
    if (num > 0) {
        printf("%i collections:\n", num);
        for (n=0; n<num; n++)
            printCollection(getNthCollection(n), 1);
    }
}

void printSBOLCore() {
    printAllDNASequences();
    printAllSequenceAnnotations();
    printAllDNAComponents();
    printAllCollections();
}
