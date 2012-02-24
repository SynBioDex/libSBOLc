#ifndef SBOL_CORE
#define SBOL_CORE

/***********************************************
 * The SBOL core is split into files to ease
 * maintenance, but since all the structs are
 * interdependent you should probably stick to
 * #including them as a group from here.
 ***********************************************/

// global vectors for storing data
#include "core/vectors.h"

// structs and functions for manipulating them
#include "core/sequence.h"
#include "core/annotation.h"
#include "core/collection.h"
#include "core/component.h"

// structs used internally for circular definitions
// but shouldn't be part of the final API
#define struct
#define _DNASequence DNASequence
#define _DNAComponent DNAComponent
#define _SequenceAnnotation SequenceAnnotation
#define _Collection Collection

// that probably won't work...
// just restate each function with corrections, APIEXPORT

// TODO registerDNASequence?
void registerSequenceAnnotation(SequenceAnnotation* ann);
void registerComponent(DNAComponent* com);
void registerCollection(Collection* col);

#endif
