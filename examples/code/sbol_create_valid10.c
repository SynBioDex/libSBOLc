#include "sbol.h"

// This only creates a Document in memory;
// you would then want to write it out with writeDocument(doc, filename)
// and free it with deleteDocument(doc).
// You can see the output with sbol_run_tests, which writes
// xml files for all the CreateValid* examples.

Document* CreateValid10() {
	Document* doc = createDocument();
	Collection *col = createCollection(doc, "http://example.com/collection1");
	setCollectionDisplayID(col, "Coll1");
	setCollectionName(col, "Collection1");
	setCollectionDescription(col, "A collection may be empty");
	return doc;
}

