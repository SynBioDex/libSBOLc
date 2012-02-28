#include "core.h"

void cleanup() {
	cleanupSequences();
	cleanupSequenceAnnotations();
	cleanupComponents();
	cleanupCollections();
}
