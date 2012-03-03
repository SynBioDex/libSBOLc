#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "genericarray.h"
#include "dnasequence.h"

#define NUCLEOTIDES_PRINTED 30

static GenericArray* allDNASequences;

void registerDNASequence(DNASequence* seq) {
	if (!allDNASequences)
		allDNASequences = createGenericArray();
	insertIntoGenericArray(allDNASequences, seq);
}

// TODO constrain to actg and sometimes n?
DNASequence* createDNASequence(char* nucleotides) {
	DNASequence* seq = (DNASequence*)malloc(sizeof(DNASequence));
	if (nucleotides) {
		// TODO avoid copying large sequences?
		seq->nucleotides = (char*)malloc(sizeof(char) * strlen(nucleotides)+1);
		strcpy(seq->nucleotides, nucleotides);
	} else
	    seq->nucleotides = NULL;
	registerDNASequence(seq);
	return seq;
}

void removeDNASequence(DNASequence* seq) {
	if (seq && allDNASequences) {
		int index = indexByPtr(allDNASequences, seq);
		if (index >= 0)
			removeFromGenericArray(allDNASequences, index);
	}
}

void deleteDNASequence(DNASequence* seq) {
	if (seq) {
		removeDNASequence(seq);
		if (seq->nucleotides) {
			free(seq->nucleotides);
			seq->nucleotides = NULL;
		}
		free(seq);
	}
}

void cleanupDNASequences() {
	if (allDNASequences) {
		int index;
		for (index=allDNASequences->numInUse; index>0; index--)
			deleteDNASequence( allDNASequences->array[index] );
		deleteGenericArray(allDNASequences);
		allDNASequences = NULL;
	}
}

int getNumDNASequences() {
    if (allDNASequences)
        return allDNASequences->numInUse;
    else
        return 0;
}

DNASequence* getNthDNASequence(int n) {
    if (!allDNASequences || allDNASequences->numInUse<=n)
        return NULL;
    else
        return allDNASequences->array[n];
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
