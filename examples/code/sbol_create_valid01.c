#include "sbol.h"

// This only creates a Document in memory;
// you would then want to write it out with writeDocument(doc, filename)
// and free it with deleteDocument(doc).
// You can see the output with sbol_run_tests, which writes
// xml files for all the CreateValid* examples.

Document* CreateValid01() {
	Document* doc = createDocument();
	DNAComponent *com = createDNAComponent(doc, "http://example.com/dc1");
	setDNAComponentDisplayID(com, "DC1");
	return doc;
}

