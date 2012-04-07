#include "sbol.h"

// To actually run the code you need to #include it
// and call this function. You can also use sbol_run_tests,
// which will write xml files for all the CreateValid* examples.

void CreateValid11() {
	// collection
	Collection *col = createCollection("http://example.com/collection1");
	setCollectionDisplayID(col, "Coll1");
	setCollectionName(col, "Collection1");
	setCollectionDescription(col, "A collection may contain multiple components");
	// components
	DNAComponent *dc1 = createDNAComponent("http://example.com/dc1");
	DNAComponent *dc2 = createDNAComponent("http://example.com/dc2");
	setDNAComponentDisplayID(dc1, "DC1");
	setDNAComponentDisplayID(dc2, "DC2");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	addDNAComponentToCollection(col, dc1);
	addDNAComponentToCollection(col, dc2);
	// sequence
	DNASequence *ds1 = createDNASequence("http://example.com/ds1");
	setDNASequenceNucleotides(ds1, "tccctatcagtgat");
	setDNAComponentSequence(dc1, ds1);
}

