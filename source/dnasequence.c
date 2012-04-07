#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "property.h"
#include "array.h"
#include "object.h"
#include "dnasequence.h"

static void registerDNASequence(Document* doc, DNASequence* seq) {
	if (doc && doc->allDNASequences) {
		insertPointerIntoArray(doc->allDNASequences, seq);
	}
}

// TODO constrain to actg and sometimes n?
DNASequence* createDNASequence(Document* doc, char* uri) {
	if (!doc || !uri || isSBOLObjectURI(doc, uri))
	    return NULL;
	DNASequence* seq = malloc(sizeof(DNASequence));
	seq->base        = createSBOLObject(doc, uri);
	seq->nucleotides = createNucleotidesProperty();
	registerDNASequence(doc, seq);
	return seq;
}

static void setDNASequenceURI(DNASequence* seq, const char* uri) {
	if (seq)
		setSBOLObjectURI(seq->base, uri);
}

void setDNASequenceNucleotides(DNASequence* seq, const char* nucleotides) {
	if (seq)
		setNucleotidesProperty(seq->nucleotides, nucleotides);
}

static void removeDNASequence(Document* doc, DNASequence* seq) {
	if (doc && doc->allDNASequences && seq) {
		int index = indexOfPointerInArray(doc->allDNASequences, seq);
		if (index >= 0)
			removePointerFromArray(doc->allDNASequences, index);
	}
}

void deleteDNASequence(DNASequence* seq) {
	if (seq) {
		if (seq->base) {
			deleteSBOLObject(seq->base);
			seq->base = NULL;
		}
		if (seq->nucleotides) {
			deleteNucleotidesProperty(seq->nucleotides);
			seq->nucleotides = NULL;
		}
		removeDNASequence(seq);
		free(seq);
		seq = NULL;
	}
}

void cleanupDNASequences(Document* doc) {
	if (doc && doc->allDNASequences) {
		int n;
		DNASequence* seq;
		for (n=getNumDNASequences(doc)-1; n>=0; n--) {
			seq = getNthDNASequence(doc, n);
			deleteDNASequence(seq);
			seq = NULL;
		}
		deletePointerArray(doc->allDNASequences);
		doc->allDNASequences = NULL;
	}
}

int getNumDNASequences(Document* doc) {
	if (doc && doc->allDNASequences)
	    return getNumPointersInArray(doc->allDNASequences);
	else
	    return 0;
}

DNASequence* getDNASequence(Document* doc, const char* uri) {
/*	lazyCreateAllDNASequences();*/
	if (!doc || !uri)
		return NULL;
	int n;
	char* candidate;
	DNASequence* seq;
	for (n=0; n < getNumDNASequences(doc); n++) {
		seq = getNthDNASequence(doc, n);
		candidate = getSBOLObjectURI(seq->base);
		if (candidate && strcmp(candidate, uri) == 0)
			return seq;
	}
	return NULL;
}

char* getDNASequenceURI(const DNASequence* seq) {
	if (seq)
		return getSBOLObjectURI(seq->base);
	else
		return NULL;
}

int isDNASequenceURI(Document* doc, const char* uri) {
/*	lazyCreateAllDNASequences();*/
	if (!doc || !uri)
		return 0;
	int n;
	char* candidate;
	DNASequence* seq;
	for (n=0; n < getNumDNASequences(doc); n++) {
		seq = getNthDNASequence(doc, n);
		candidate = getSBOLObjectURI(seq->base);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

char* getDNASequenceNucleotides(const DNASequence* seq) {
	if (seq)
	    return getNucleotidesProperty(seq->nucleotides);
}

DNASequence* getNthDNASequence(Document* doc, int n) {
	if (doc && getNumDNASequences(doc) > n && n >= 0)
		return (DNASequence*) getNthPointerInArray(doc->allDNASequences, n);
	else
		return NULL;
}

void printDNASequence(const DNASequence* seq, int tabs) {
	if (!seq)
	    return;
	indent(tabs); printf("%s\n", getDNASequenceURI(seq));
	
	// print nucleotides, truncating them if there's a lot
	indent(tabs+1);
	printf("nucleotides: ");
    char* nt = getDNASequenceNucleotides(seq);
	if (nt && strlen(nt) > atoi(NUCLEOTIDES_TO_PRINT))
		printf("%." NUCLEOTIDES_TO_PRINT "s", nt);
	else
		printf("%s", nt);
	printf("\n");
}

void printAllDNASequences(Document* doc) {
	if (!doc)
		return;
	int n;
	int num = getNumDNASequences(doc);
	if (num > 0) {
	    printf("%i sequences:\n", num);
	    for (n=0; n<num; n++)
	        printDNASequence(getNthDNASequence(doc, n), 1);
	}
}

