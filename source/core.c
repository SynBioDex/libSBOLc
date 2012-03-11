#include <stdio.h>
#include "core.h"

void cleanupSBOLCore() {
	cleanupDNASequences();
	cleanupSequenceAnnotations();
	cleanupDNAComponents();
	cleanupCollections();
}

void printSBOLCore() {
    printAllDNASequences();
    printAllSequenceAnnotations();
    printAllDNAComponents();
    printAllCollections();
}

int isDuplicateURI(const char* uri) {
    return (int) (isDNASequenceURI(uri)
            || isSequenceAnnotationURI(uri)
            || isDNAComponentURI(uri)
            || isCollectionURI(uri));
}
