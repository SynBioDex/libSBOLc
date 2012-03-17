#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "property.h"
#include "genericarray.h"
#include "dnasequence.h"
#include "object.h"

#define NUCLEOTIDES_TO_PRINT 30

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
	DNASequence* seq = (DNASequence*) createSBOLObject(uri);
	seq = realloc(seq, sizeof(DNASequence));
	seq->nucleotides = createTextProperty();
	seq->processed   = 0;
	registerDNASequence(seq);
	return seq;
}

void setDNASequenceURI(DNASequence* seq, const char* uri) {
	setSBOLObjectURI((SBOLObject*) seq, uri);
}

void setNucleotides(DNASequence* seq, const char* nucleotides) {
	if (seq)
		setTextProperty(seq->nucleotides, nucleotides);
}

// TODO generalize this
void removeDNASequence(DNASequence* seq) {
	if (seq && allDNASequences) {
		int index = indexByPtr(allDNASequences, seq);
		if (index >= 0)
			removeFromGenericArray(allDNASequences, index);
	}
}

void deleteDNASequence(DNASequence* seq) {
	if (seq) {
		if (seq->nucleotides) {
			deleteTextProperty(seq->nucleotides);
			seq->nucleotides = NULL;
		}
		removeDNASequence(seq);
		deleteSBOLObject((SBOLObject*) seq);
		//free(seq);
		seq = NULL;
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
	char* candidate;
	DNASequence* seq;
	for (index=0; index<allDNASequences->numInUse; index++) {
		seq = (DNASequence*) allDNASequences->array[index];
		candidate = getSBOLObjectURI((SBOLObject*) seq);
		if (candidate && strcmp(candidate, uri) == 0)
			return seq;
	}
	return NULL;
}

char* getDNASequenceURI(const DNASequence* seq) {
	return getSBOLObjectURI((SBOLObject*) seq);
}

int isDNASequenceURI(const char* uri) {
	if (!allDNASequences)
		allDNASequences = createGenericArray();
	if (!uri)
		return 0;
	int index;
	char* candidate;
	DNASequence* seq;
	for (index=0; index<getNumDNASequences(); index++) {
		seq = getNthDNASequence(index);
		candidate = getSBOLObjectURI((SBOLObject*) seq);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

char* getNucleotides(const DNASequence* seq) {
	if (seq)
	    return getTextProperty(seq->nucleotides);
}

// TODO generalize this further?
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
	char* uri = getDNASequenceURI(seq);
	indent(tabs);
	if (strlen(uri) > NUCLEOTIDES_TO_PRINT)
		printf("%.NUCLEOTIDES_TO_PRINTs\n", uri);
	else
		printf("%s\n", uri);
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
