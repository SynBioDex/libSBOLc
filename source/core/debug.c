#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"
#include "debug.h"

// TODO move all this to other core files

#define NUCLEOTIDES_PRINTED 30

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
    //print just the beginning of the sequence
    char* nt = malloc(sizeof(char) * NUCLEOTIDES_PRINTED+1);
    strncpy(nt, seq->nucleotides, NUCLEOTIDES_PRINTED);
    indent(tabs); printf("nucleotides: %s\n", nt);
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
        int num = getNumPrecedes(ann);
        if (num > 0) {
            indent(tabs+1); printf("%i precedes:\n", ann);
            int i;
            for (i=0; i<num; i++) {
                indent(tabs+2); printf("%s\n", getNthPrecedes(ann, i)->id);
            }
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
    int num;
    if (com->annotations) {
        SequenceAnnotation* seq;
        num = getNumSequenceAnnotationsIn(com);
        if (num > 0) {
            indent(tabs+1); printf("%i annotations:\n", num);
            for (i=0; i<num; i++) {
                seq = getNthSequenceAnnotationIn(com, i);
                indent(tabs+2); printf("%s\n", seq->id);
            }
        }
    }
    if (com->collections) {
        Collection* col;
        num = getNumCollectionsFor(com);
        if (num > 0) {
            indent(tabs+1); printf("%i collections:\n", num);
            for (i=0; i<num; i++) {
                col = getNthCollectionFor(com, i);
                indent(tabs+2); printf("%s\n", col->id);
            }
        }
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

void printCollection(const Collection* col, int tabs) {
    if (!col)
        return;
    indent(tabs);   printf("%s\n", col->id);
    indent(tabs+1); printf("name: %s\n", col->name);
    indent(tabs+1); printf("description: %s\n", col->description);
    int i;
    int num;
    if (col->components) {
        DNAComponent* com;
        num = getNumDNAComponentsIn(col);
        if (num > 0) {
            indent(tabs+1); printf("%i components:\n", num);
            for (i=0; i<num; i++) {
                com = getNthDNAComponentIn(col, i);
                indent(tabs+2); printf("%s\n", com->id);
            }
        }
    }
    if (col->collections) {
        Collection* col2;
        num = getNumCollectionsIn(col);
        if (num > 0) {
            indent(tabs+1); printf("%i collections:\n", num);
            for (i=0; i<num; i++) {
                col2 = getNthCollectionIn(col, i);
                indent(tabs+2); printf("%s\n", col2->id);
            }
        }
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
