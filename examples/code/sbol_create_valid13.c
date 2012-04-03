#include "sbol.h"

// To actually run the code you need to #include it
// and call this function. You can also use sbol_run_tests,
// which will write xml files for all the CreateValid* examples.

void CreateValid13() {
	DNASequence *seq = createDNASequence("http://example.com/ds1");
	setDNASequenceNucleotides(seq, "tccctatcagtgat");
}

