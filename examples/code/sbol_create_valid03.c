#include "sbol.h"

// To actually run the code you need to #include it
// and call this function. You can also use sbol_run_tests,
// which will write xml files for all the CreateValid* examples.

void CreateValid03() {
	DNAComponent *com = createDNAComponent("http://example.com/dc1");
	setDNAComponentDisplayID(com, "DC1");
	setDNAComponentName(com, "DnaComponent1");
	setDNAComponentDescription(com, "DnaComponent with sequence information");
	DNASequence *seq = createDNASequence("http://example.com/ds1");
	setDNASequenceNucleotides(seq, "tccctatcagtgat");
	setDNAComponentSequence(com, seq);
}

