#include <stdlib.h>
#include <string.h>
#include "sequence.h"

// TODO constrain to actg and sometimes n?
// TODO copy nucleotides rather than just pointer?
DNASequence* createDNASequence(char* nucleotides) {
	DNASequence* seq;
	seq = (DNASequence*)malloc(sizeof(DNASequence));
	if (nucleotides)
		seq->nucleotides = nucleotides;
	return seq;
}

void deleteDNASequence(DNASequence* seq) {
	if (seq) {
		//if (seq->nucleotides)
		//	free(seq->nucleotides);
		free(seq);
	}
}
