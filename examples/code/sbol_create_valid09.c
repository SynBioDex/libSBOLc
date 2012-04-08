#include "sbol.h"

// To actually run the code you need to #include it
// and call this function. You can also use sbol_run_tests,
// which will write xml files for all the CreateValid* examples.

void CreateValid09() {
	Document* doc = createDocument();
	// components
	DNAComponent *dc1 = createDNAComponent(doc, "http://example.com/dc1");
	DNAComponent *dc2 = createDNAComponent(doc, "http://example.com/dc2");
	setDNAComponentDisplayID(dc1, "DC1");
	setDNAComponentDisplayID(dc2, "DC2");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	setDNAComponentDescription(dc1, "Multiple DNA components at the top level are allowed even without a collection");
	// sequence
	DNASequence *ds1 = createDNASequence(doc, "http://example.com/ds1");
	setDNASequenceNucleotides(ds1, "tccctatcagtgat");
	setDNAComponentSequence(dc1, ds1);
	deleteDocument(doc);
}

