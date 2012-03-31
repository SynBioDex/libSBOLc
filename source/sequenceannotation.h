///////////////////////////////////////////////////////////
/// @file
/// This file contains the SequenceAnnotation struct,
/// as well as functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_SEQUENCEANNOTATION_HEADER
#define SBOL_SEQUENCEANNOTATION_HEADER

#include "constants.h"
#include "prototypes.h"

/// Implements the SBOL Core SequenceAnnotation object.
struct _SequenceAnnotation {
	SBOLObject* base;
	PositionProperty *genbankStart;
	PositionProperty *genbankEnd;
	PolarityProperty *strand;
	DNAComponent* subComponent;
	PointerArray* precedes;
};

// create/destroy
SequenceAnnotation* createSequenceAnnotation(const char* uri);
char* getSequenceAnnotationURI(const SequenceAnnotation* ann);
void setSequenceAnnotationURI(SequenceAnnotation* ann, const char* uri);
void deleteSequenceAnnotation(SequenceAnnotation* ann);

SequenceAnnotation* getSequenceAnnotation(const char* uri);

// work with global arrays
int isSequenceAnnotation(const void* pointer);
int isSequenceAnnotationURI(const char* uri);
int getNumSequenceAnnotations();
SequenceAnnotation* getNthSequenceAnnotation(int n);

int getBioStart(const SequenceAnnotation* ann);
int getBioEnd(const SequenceAnnotation* ann);
int getStrandPolarity(const SequenceAnnotation* ann);
void setBioStart(SequenceAnnotation* ann, int start);
void setBioEnd(SequenceAnnotation* ann, int end);
void setStrandPolarity(SequenceAnnotation* ann, int polarity);

DNAComponent* getSubComponent(const SequenceAnnotation* ann);

// constrain order
void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
int getNumPrecedes(const SequenceAnnotation* ann);
SequenceAnnotation* getNthPrecedes(const SequenceAnnotation* ann, int n);
int precedes(const SequenceAnnotation* seq1, const SequenceAnnotation* seq2);
// TODO removePrecedesRelationship?
void cleanupSequenceAnnotations();

void printSequenceAnnotation(const SequenceAnnotation* seq, int tabs);

void printAllSequenceAnnotations();

#endif
