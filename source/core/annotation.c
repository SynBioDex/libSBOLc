#include <stdlib.h>
#include <string.h>
#include "annotation.h"

/*******************
 * create/destroy
 *******************/

SequenceAnnotation* createSequenceAnnotation(const char* id) {
	//SequenceAnnotation ann = {
	//	NULL, // id
	//	0, // genbankStart
	//	0, // genbankEnd
	//	0, // numPrecedes
	//	NULL, // annotates
	//	NULL, // subComponent
	//	NULL  // precedes
	//};
	SequenceAnnotation* ann;
	ann = (SequenceAnnotation*)malloc(sizeof(SequenceAnnotation));
	ann->id           = NULL;
	ann->genbankStart = 0;
	ann->genbankEnd   = 0;
	ann->numPrecedes  = 0;
	ann->annotates    = NULL;
	ann->subComponent = NULL;
	ann->precedes     = NULL;
	setSequenceAnnotationID(ann, id);
	// TODO register with allAnnotations
	return ann;
}

void setSequenceAnnotationID(SequenceAnnotation* ann, const char* id) {
	//if (ann) {
		if (!ann->id)
			ann->id = (char*)malloc(sizeof(char) * strlen(id)+1);
		strcpy(ann->id, id);
	//}
	// TODO handle NULL?
}

void deleteSequenceAnnotation(SequenceAnnotation* ann) {
	if (ann) {
		if (ann->id) free(ann->id);
		// TODO will these delete parts of other structs?
		if (ann->annotates)		free(ann->annotates);
		if (ann->subComponent)	free(ann->subComponent);
		if (ann->precedes)		free(ann->precedes);
		free(ann);
	}
}

/*******************
 * constrain order
 *******************/

void addPrecedesRelationship(SequenceAnnotation * upstream,
							SequenceAnnotation * downstream) {
	if (!upstream || !downstream)
		return;
	if (!upstream->precedes) {
		// create array
		size_t size = sizeof(SequenceAnnotation*) * 2;
		upstream->precedes = (SequenceAnnotation**)malloc(size);
		
		// add first value
		upstream->precedes[0] = downstream;
		
		// add null terminator
		upstream->precedes[1] = NULL;
	} else {
		// create longer array
		int n = upstream->numPrecedes;
		SequenceAnnotation** old = upstream->precedes; // TODO memory leak?
		size_t size = sizeof(SequenceAnnotation*) * (n+2);
		upstream->precedes = (SequenceAnnotation**)malloc(size);
		
		// fill it in with values
		int i;
		for (i=0; i<n; ++i)
			upstream->precedes[i] = old[i];
		upstream->precedes[n] = downstream;
		
		// add null terminator
		upstream->precedes[n+1] = NULL;
	}
	upstream->numPrecedes++;
}

int getNumPrecedes(SequenceAnnotation* ann) {
	return ann->numPrecedes;
}

SequenceAnnotation* getNthPrecedes(SequenceAnnotation* ann, int n) {
	if (ann->numPrecedes >= n)
		return ann->precedes[n];
	else
		return NULL;
}
