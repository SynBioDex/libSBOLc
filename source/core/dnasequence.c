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
DNASequence* createDNASequence(char* uri) {
	if (!uri || isDuplicateURI(uri))
	    return NULL;
	DNASequence* seq = malloc(sizeof(DNASequence));
	seq->uri         = createProperty();
	seq->nucleotides = createProperty();
	setDNASequenceURI(seq, uri);
	registerDNASequence(seq);
	return seq;
}

void setDNASequenceURI(DNASequence* seq, const char* uri) {
	if (seq)
		setProperty(seq->uri, uri);
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
		deleteProperty(seq->uri);
		deleteProperty(seq->nucleotides);
		seq->uri = NULL;
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

DNASequence* getDNASequence(const char* uri) {
	if (!allDNASequences)
		allDNASequences = createGenericArray();
	if (!uri)
		return NULL;
	int index;
	DNASequence* seq;
	for (index=0; index<allDNASequences->numInUse; index++) {
		seq = (DNASequence*) allDNASequences->array[index];
		if (compareProperty(seq->uri, uri) == 0)
			return seq;
	}
	return NULL;
}

char* getDNASequenceURI(const DNASequence* seq) {
	if (seq)
		return getProperty(seq->uri);
	else
		return NULL;
}

int isDNASequenceURI(const char* uri) {
	if (!allDNASequences)
		allDNASequences = createGenericArray();
	if (!uri)
		return 0;
	int index;
	DNASequence* seq;
	for (index=0; index<getNumDNASequences(); index++) {
		seq = getNthDNASequence(index);
		if (seq && compareProperty(seq->uri, uri) == 0)
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
	indent(tabs); printf("%s\n", getDNASequenceURI(seq));
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
