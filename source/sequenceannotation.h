///////////////////////////////////////////////////////////
/// @file sequenceannotation.h
/// This file contains the SequenceAnnotation struct,
/// as well as functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_SEQUENCEANNOTATION_HEADER
#define SBOL_SEQUENCEANNOTATION_HEADER
#include "api.h"

struct _DNAComponent;
struct _PointerArray;
struct _URIProperty;

typedef struct _SequenceAnnotation {
	struct _SBOLObject* base;
	int genbankStart;
	int genbankEnd;
	int strand;
   	struct _DNAComponent* annotates;
	struct _DNAComponent* subComponent;
	struct _PointerArray* precedes;
} SequenceAnnotation;

// TODO getAnnotates?

// create/destroy
SBOLAPIEXPORTS SequenceAnnotation* createSequenceAnnotation(const char* uri);
SBOLAPIEXPORTS char* getSequenceAnnotationURI(const SequenceAnnotation* ann);
SBOLAPIEXPORTS void setSequenceAnnotationURI(SequenceAnnotation* ann, const char* uri);
SBOLAPIEXPORTS void deleteSequenceAnnotation(SequenceAnnotation* ann);

SBOLAPIEXPORTS SequenceAnnotation* getSequenceAnnotation(const char* uri);

// work with global arrays
int isSequenceAnnotationPtr(const void* pointer); // TODO rename and export
SBOLAPIEXPORTS int isSequenceAnnotationURI(const char* uri);
SBOLAPIEXPORTS int getNumSequenceAnnotations();
SBOLAPIEXPORTS SequenceAnnotation* getNthSequenceAnnotation(int n);

SBOLAPIEXPORTS int getBioStart(const SequenceAnnotation* ann);
SBOLAPIEXPORTS int getBioEnd(const SequenceAnnotation* ann);
SBOLAPIEXPORTS int getStrandPolarity(const SequenceAnnotation* ann);
SBOLAPIEXPORTS void setBioStart(SequenceAnnotation* ann, int start);
SBOLAPIEXPORTS void setBioEnd(SequenceAnnotation* ann, int end);
SBOLAPIEXPORTS void setStrandPolarity(SequenceAnnotation* ann, int polarity);

SBOLAPIEXPORTS struct _DNAComponent* getSubComponent(const SequenceAnnotation* ann);

SBOLAPIEXPORTS int annotates(const SequenceAnnotation *ann, const struct _DNAComponent *com);

// constrain order
SBOLAPIEXPORTS void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
SBOLAPIEXPORTS int getNumPrecedes(const SequenceAnnotation* ann);
SBOLAPIEXPORTS SequenceAnnotation* getNthPrecedes(const SequenceAnnotation* ann, int n);
SBOLAPIEXPORTS int precedes(const SequenceAnnotation* seq1, const SequenceAnnotation* seq2);
// TODO removePrecedesRelationship?

void printSequenceAnnotation(const SequenceAnnotation* seq, int tabs);
void printAllSequenceAnnotations();
void cleanupSequenceAnnotations();

#endif
