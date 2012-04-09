#include "sbol.h"

// This only creates a Document in memory;
// you would then want to write it out with writeDocument(doc, filename)
// and free it with deleteDocument(doc).
// You can see the output with sbol_run_tests, which writes
// xml files for all the CreateValid* examples.

Document* CreateValid07() {
	Document* doc = createDocument();
	// components
	DNAComponent *dc1 = createDNAComponent(doc, "http://example.com/dc1");
	DNAComponent *dc2 = createDNAComponent(doc, "http://example.com/dc2");
	// dc1 has a dc:creator node that libSBOLc ignores
	setDNAComponentDisplayID(dc1, "DC1");
	setDNAComponentDisplayID(dc2, "DC2");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	setDNAComponentDescription(dc1, "It is valid to have additional elements in any SBOL element as long as they appear after \n\t\tthe elements defined in SBOL core model. This example adds dc:creator annotations to SBOL elements");
	setDNAComponentDescription(dc2, "Another DNA component");
	// sequence
	DNASequence *ds1 = createDNASequence(doc, "http://example.com/ds1");
	setDNASequenceNucleotides(ds1, "tccctatcagtgat");
	setDNAComponentSequence(dc1, ds1);
	// annotation
	SequenceAnnotation *sa1 = createSequenceAnnotation(doc, "http://example.com/sa1");
	// sa1 has a dc:creator node that libSBOLc ignores
	setSequenceAnnotationSubComponent(sa1, dc2);
	addSequenceAnnotation(dc1, sa1);
	return doc;
}

