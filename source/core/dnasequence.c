#include <stdlib.h>
#include <string.h>
#include "storage.h"
#include "dnasequence.h"

static GenericArray* allDNASequences;

void registerDNASequence(DNASequence* seq) {
	if (!allDNASequences)
		allDNASequences = createGenericArray();
	insertIntoArray(allDNASequences, seq);
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
			removeFromArray(allDNASequences, index);
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
