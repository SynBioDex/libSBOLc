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
