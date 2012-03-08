#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "property.h"
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
DNASequence* createDNASequence(char* id) {
	DNASequence* seq = malloc(sizeof(DNASequence));
	seq->id          = createProperty();
	seq->nucleotides = createProperty();
	setDNASequenceID(seq, id);
	registerDNASequence(seq);
	return seq;
}

void setDNASequenceID(DNASequence* seq, const char* id) {
	if (seq)
		setProperty(seq->id, id);
}

void setNucleotides(DNASequence* seq, const char* nucleotides) {
	if (seq)
		setProperty(seq->nucleotides, nucleotides);
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
		deleteProperty(seq->id);
		deleteProperty(seq->nucleotides);
		seq->id = NULL;
		seq->nucleotides = NULL;
		free(seq);
	}
}

void cleanupDNASequences() {
	if (allDNASequences) {
		int n;
		DNASequence* seq;
		for (n=getNumDNASequences()-1; n>=0; n--) {
			seq = getNthDNASequence(n);
			deleteDNASequence(seq);
		}
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

DNASequence* getDNASequence(const char* id) {
	if (!allDNASequences)
		allDNASequences = createGenericArray();
	if (!id)
		return NULL;
	int index;
	DNASequence* seq;
	for (index=0; index<allDNASequences->numInUse; index++) {
		seq = (DNASequence*) allDNASequences->array[index];
		if (compareProperty(seq->id, id) == 0)
			return seq;
	}
	return NULL;
}

char* getDNASequenceID(const DNASequence* seq) {
	if (seq)
		return getProperty(seq->id);
	else
		return NULL;
}

int isDNASequenceID(const char* id) {
	if (!allDNASequences)
		allDNASequences = createGenericArray();
	if (!id)
		return 0;
	int index;
	DNASequence* seq;
	for (index=0; index<getNumDNASequences(); index++) {
		seq = getNthDNASequence(index);
		if (seq && compareProperty(seq->id, id) == 0)
			return 1;
	}
	return 0;
}

char* getNucleotides(const DNASequence* seq) {
	if (seq)
	    return getProperty(seq->nucleotides);
}

DNASequence* getNthDNASequence(int n) {
	if (!allDNASequences || allDNASequences->numInUse<=n)
	    return NULL;
	else
	    return (DNASequence*) getNthArrayElement(allDNASequences, n);
}

void printDNASequence(const DNASequence* seq, int tabs) {
	if (!seq)
	    return;
	// TODO print just the beginning of the sequence?
	indent(tabs); printf("%s\n", getDNASequenceID(seq));
	indent(tabs+1); printf("nucleotides: %s\n", getNucleotides(seq));
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
