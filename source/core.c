#include "core.h"
#include "core/sequence.h"
#include "core/annotation.h"
#include "core/collection.h"
#include "core/component.h"

void cleanup() {
	cleanupComponents();
	cleanupAnnotations();
	cleanupCollections();
}

