#include "core.h"

void cleanup() {
	cleanupDNASequences();
	cleanupSequenceAnnotations();
	cleanupComponents();
	cleanupCollections();
}
