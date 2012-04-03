#include "sbol.h"

// To actually run the code you need to #include it
// and call this function. You can also use sbol_run_tests,
// which will write xml files for all the CreateValid* examples.

void CreateValid06() {
	DNAComponent *com = createDNAComponent("http://example.com/dc1");
	// dc1 has two rdf:type nodes, which libSBOL ignores
	setDNAComponentDisplayID(com, "DC1");
	setDNAComponentName(com, "DnaComponent1");
	setDNAComponentDescription(com, "A DnaComponent can optionally use a type from Sequence Ontology");
	DNASequence *seq = createDNASequence("http://example.com/ds1");
	setDNASequenceNucleotides(seq, "tccctatcagtgat");
	setDNAComponentSequence(com, seq);
}

