#include "sbol.h"

// This only creates a Document in memory;
// you would then want to write it out with writeDocument(doc, filename)
// and free it with deleteDocument(doc).
// You can see the output with sbol_run_tests, which writes
// xml files for all the CreateValid* examples.

Document* CreateValid08() {
	Document* doc = createDocument();
	// components
	DNAComponent *dc1 = createDNAComponent(doc, "http://example.com/dc1");
	DNAComponent *dc2 = createDNAComponent(doc, "http://example.com/dc2");
	DNAComponent *dc3 = createDNAComponent(doc, "http://example.com/dc3");
	DNAComponent *dc4 = createDNAComponent(doc, "http://example.com/dc4");
	setDNAComponentDisplayID(dc1, "DC1");
	setDNAComponentDisplayID(dc2, "DC2");
	setDNAComponentDisplayID(dc3, "DC3");
	setDNAComponentDisplayID(dc4, "DC4");
	setDNAComponentName(dc1, "DnaComponent1");
	setDNAComponentName(dc2, "DnaComponent2");
	setDNAComponentName(dc3, "DnaComponent3");
	setDNAComponentName(dc4, "DnaComponent4");
	setDNAComponentDescription(dc1, "Various sequence annotations");
	setDNAComponentDescription(dc2, "Another DNA component");
	// sequences
	DNASequence *ds1 = createDNASequence(doc, "http://example.com/ds1");
	DNASequence *ds2 = createDNASequence(doc, "http://example.com/ds2");
	setDNASequenceNucleotides(ds1, "tccctatcagtgat");
	setDNASequenceNucleotides(ds2, "tc");
	setDNAComponentSequence(dc1, ds1);
	setDNAComponentSequence(dc2, ds2);
	// annotations
	SequenceAnnotation *sa1 = createSequenceAnnotation(doc, "http://example.com/sa1");
	SequenceAnnotation *sa2 = createSequenceAnnotation(doc, "http://example.com/sa2");
	SequenceAnnotation *sa3 = createSequenceAnnotation(doc, "http://example.com/sa3");
	addSequenceAnnotation(dc1, sa1);
	addSequenceAnnotation(dc1, sa2);
	addSequenceAnnotation(dc1, sa3);
	setSequenceAnnotationStart(sa1, 1); setSequenceAnnotationEnd(sa1, 2);
	setSequenceAnnotationStart(sa2, 3); setSequenceAnnotationEnd(sa2, 5);
	setSequenceAnnotationSubComponent(sa1, dc2);
	setSequenceAnnotationSubComponent(sa2, dc3);
	setSequenceAnnotationSubComponent(sa3, dc4);
	addPrecedesRelationship(sa1, sa2);
	addPrecedesRelationship(sa1, sa3);
	return doc;
}

