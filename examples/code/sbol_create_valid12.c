#include "sbol.h"

// To actually run the code you need to #include it
// and call this function. You can also use sbol_run_tests,
// which will write xml files for all the CreateValid* examples.

void CreateValid12() {
	Document* doc = createDocument();
	// collections
	Collection *c1 = createCollection(doc, "http://example.com/collection1");
	Collection *c2 = createCollection(doc, "http://example.com/collection2");
	setCollectionDisplayID(c1, "Coll1");
	setCollectionDisplayID(c2, "Coll2");
	setCollectionName(c1, "Collection1");
	setCollectionName(c2, "Collection2");
	setCollectionDescription(c1, "This is the first collection in the document");
	setCollectionDescription(c2, "This is the second collection in the document");
	// components
	DNAComponent *dc1 = createDNAComponent(doc, "http://example.com/dc1");
	DNAComponent *dc2 = createDNAComponent(doc, "http://example.com/dc2");
	setDNAComponentDisplayID(dc1, "DC1");
	setDNAComponentDisplayID(dc2, "DC2");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	addDNAComponentToCollection(c1, dc1);
	addDNAComponentToCollection(c2, dc2);
	// sequence
	DNASequence *ds1 = createDNASequence(doc, "http://example.com/ds1");
	setDNASequenceNucleotides(ds1, "tccctatcagtgat");
	setDNAComponentSequence(dc1, ds1);
	deleteDocument(doc);
}

