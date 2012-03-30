///////////////////////////////////////////////////////////
/// @file sequenceannotation.h
/// This file contains the SequenceAnnotation struct,
/// as well as functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_SEQUENCEANNOTATION_HEADER
#define SBOL_SEQUENCEANNOTATION_HEADER

struct _DNAComponent;
struct _PointerArray;
struct _URIProperty;
struct _PositionProperty;
struct _PolarityProperty;

/// Implements the SBOL Core SequenceAnnotation object.
typedef struct _SequenceAnnotation {
	struct _SBOLObject* base;
	struct _PositionProperty *genbankStart;
	struct _PositionProperty *genbankEnd;
	struct _PolarityProperty *strand;
	struct _DNAComponent* subComponent;
	struct _PointerArray* precedes;
} SequenceAnnotation;

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

struct _DNAComponent* getSubComponent(const SequenceAnnotation* ann);

// constrain order
void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
int getNumPrecedes(const SequenceAnnotation* ann);
SequenceAnnotation* getNthPrecedes(const SequenceAnnotation* ann, int n);
int precedes(const SequenceAnnotation* seq1, const SequenceAnnotation* seq2);
// TODO removePrecedesRelationship?
void cleanupSequenceAnnotations();

#endif
