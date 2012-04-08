#include "sbol.h"

// To actually run the code you need to #include it
// and call this function. You can also use sbol_run_tests,
// which will write xml files for all the CreateValid* examples.

void CreateValid10() {
	Document* doc = createDocument();
	Collection *col = createCollection(doc, "http://example.com/collection1");
	setCollectionDisplayID(col, "Coll1");
	setCollectionName(col, "Collection1");
	setCollectionDescription(col, "A collection may be empty");
	deleteDocument(doc);
}

