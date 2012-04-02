#include "sbol.h"

// To actually run the code you need to #include it
// and call this function. You can also use sbol_run_tests,
// which will write xml files for all the CreateValid* examples.

void CreateValid05() {
	DNAComponent *com = createDNAComponent("http://example.com/dc1");
	// dc1 has an rdf:type node too, which libSBOL ignores
	setDNAComponentDisplayID(com, "DC1");
	setDNAComponentName(com, "DnaComponent1");
	setDNAComponentDescription(com, "A DnaComponent can optionally use multiple types from Sequence Ontology");
	DNASequence *seq = createDNASequence("http://example.com/ds1");
	setNucleotides(seq, "tccctatcagtgat");
	setDNAComponentSequence(com, seq);
}

