#include "core.h"

void cleanup() {
	cleanupDNASequences();
	cleanupSequenceAnnotations();
	cleanupDNAComponents();
	cleanupCollections();
}
