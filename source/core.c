#include <stdio.h>
#include "core.h"

void cleanupSBOLCore() {
	cleanupDNASequences();
	cleanupSequenceAnnotations();
	cleanupDNAComponents();
	cleanupCollections();
	cleanupSBOLCompoundObjects();
	cleanupSBOLObjects();
}

void printSBOLCore() {
    printAllDNASequences();
    printAllSequenceAnnotations();
    printAllDNAComponents();
    printAllCollections();
}
