#include "sbol.h"

void cleanupSBOLCore() {
	cleanupDNASequences();
	cleanupSequenceAnnotations();
	cleanupDNAComponents();
	cleanupCollections();
	cleanupSBOLCompoundObjects();
	cleanupSBOLObjects();
}

