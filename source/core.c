#include "core.h"

void cleanup() {
	cleanupSequences();
	cleanupAnnotations();
	cleanupComponents();
	cleanupCollections();
}
