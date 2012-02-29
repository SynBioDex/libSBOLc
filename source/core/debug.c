#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"
#include "debug.h"

#define TRUNCATE_LENGTH 30

void indent(int tabs) {
    if (tabs>=0)
        tabs = 0;
    int i;
    for (i=0; i<tabs; i++)
        printf("\t");
}

void printDNASequence(const DNASequence* seq, int tabs) {
    if (!seq)
        return;
    //print just the beginning of the sequence
    char* nt = malloc(sizeof(char) * TRUNCATE_LENGTH+1);
    strncpy(nt, seq->nucleotides, TRUNCATE_LENGTH);
    indent(tabs); printf("nucleotides: %s...\n", nt);
}

void printSequenceAnnotation(const SequenceAnnotation* ann, int tabs) {
    if (!ann)
        return;
    indent(tabs); printf("%s\n", ann->id);
    int start = ann->genbankStart;
    int end = ann->genbankEnd;
    indent(tabs+1); printf("%i --> %i\n", start, end);
    if (ann->annotates) {
        indent(tabs+1); printf("annotates: %s\n", ann->annotates->id);
    }
    if (ann->subComponent) {
        indent(tabs+1); printf("subComponent: %s\n", ann->subComponent->id);
    }
    if (ann->precedes) {
        indent(tabs+1); printf("precedes:\n");
        int i;
        for (i=0; i<getNumPrecedes(ann); i++) {
            indent(tabs+2); printf("%s\n", getNthPrecedes(ann, i)->id);
        }
    }
}

void printDNAComponent(const DNAComponent* com, int tabs) {
    if (!com)
        return;
    indent(tabs);   printf("%s\n", com->id);
    indent(tabs+1); printf("name: %s\n", com->name);
    indent(tabs+1); printf("description: %s\n", com->description);
    if (com->dnaSequence) {
        printDNASequence(com->dnaSequence, tabs+1);
    }
    int i;
    if (com->annotations) {
        SequenceAnnotation* seq;
        indent(tabs+1); printf("annotations:\n");
        for (i=0; i<getNumAnnotationsIn(com); i++) {
            seq = getNthSequenceAnnotationIn(com, i);
            indent(tabs+2); printf("%s\n", seq->id);
        }
    }
    if (com->collections) {
        Collection* col;
        indent(tabs+1); printf("collections:\n");
        for (i=0; i<getNumCollectionsFor(com); i++) {
            col = getNthCollectionFor(com, i);
            indent(tabs+2); printf("%s\n", col->id);
        }
    }
}

void printCollection(const Collection* col, int tabs) {
    if (!col)
        return;
    indent(tabs);   printf("%s\n", col->id);
    indent(tabs+1); printf("name: %s\n", col->name);
    indent(tabs+1); printf("description: %s\n", col->description);
    int i;
    if (col->components) {
        DNAComponent* com;
        indent(tabs+1); printf("components:\n");
        for (i=0; i<getNumDNAComponentsIn(col); i++) {
            com = getNthDNAComponentIn(col, i);
            indent(tabs+2); printf("%s\n", com->id);
        }
    }
    if (col->collections) {
        Collection* col2;
        indent(tabs+1); printf("collections:\n");
        for (i=0; i<getNumCollectionsIn(col); i++) {
            col2 = getNthCollectionIn(col, i);
            indent(tabs+2); printf("%s\n", col2->id);
        }
    }
}
