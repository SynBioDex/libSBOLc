#include "sbol.h"

// This only creates a Document in memory;
// you would then want to write it out with writeDocument(doc, filename)
// and free it with deleteDocument(doc).
// You can see the output with sbol_run_tests, which writes
// xml files for all the CreateValid* examples.

Document* CreateValid05() {
	Document* doc = createDocument();
	DNAComponent *com = createDNAComponent(doc, "http://example.com/dc1");
	// dc1 has an rdf:type node too, which libSBOL ignores
	setDNAComponentDisplayID(com, "DC1");
	setDNAComponentName(com, "DnaComponent1");
	setDNAComponentDescription(com, "A DnaComponent can optionally use multiple types from Sequence Ontology");
	DNASequence *seq = createDNASequence(doc, "http://example.com/ds1");
	setDNASequenceNucleotides(seq, "tccctatcagtgat");
	setDNAComponentSequence(com, seq);
	return doc;
}

