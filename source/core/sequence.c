#include <stdlib.h>
#include <string.h>
#include "storage.h"
#include "sequence.h"

static GenericArray* allSequences;

void registerSequence(DNASequence* seq) {
	if (!allSequences)
		allSequences = createGenericArray();
	insertIntoArray(allSequences, seq);
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
	registerSequence(seq);
	return seq;
}

void removeSequence(DNASequence* seq) {
	if (seq && allSequences) {
		int index = indexByPtr(allSequences, seq);
		if (index >= 0)
			removeFromArray(allSequences, index);
	}
}

void deleteDNASequence(DNASequence* seq) {
	if (seq) {
		removeSequence(seq);
		if (seq->nucleotides) {
			free(seq->nucleotides);
			seq->nucleotides = NULL;
		}
		free(seq);
	}
}

void cleanupSequences() {
	if (allSequences) {
		int index;
		for (index=allSequences->numInUse; index>0; index--)
			deleteDNASequence( allSequences->array[index] );
		deleteGenericArray(allSequences);
		allSequences = NULL;
	}
}
