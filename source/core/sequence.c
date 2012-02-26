#include <stdlib.h>
#include <string.h>
#include "sequence.h"

// TODO constrain to actg and sometimes n?
DNASequence* createDNASequence(char* nucleotides) {
	DNASequence* seq = (DNASequence*)malloc(sizeof(DNASequence));
	if (nucleotides) {
		// TODO avoid copying large sequences?
		seq->nucleotides = (char*)malloc(sizeof(char) * strlen(nucleotides)+1);
		strcpy(seq->nucleotides, nucleotides);
	}
	return seq;
}

void deleteDNASequence(DNASequence* seq) {
	if (seq) {
		if (seq->nucleotides)
			free(seq->nucleotides);
		free(seq);
	}
}
