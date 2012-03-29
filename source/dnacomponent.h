///////////////////////////////////////////////////////////
/// @file dnacomponent.h
/// This file contains the DNAComponent struct, as well
/// as functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_DNACOMPONENT_HEADER
#define SBOL_DNACOMPONENT_HEADER

#include "api.h"

// forward declarations
struct _PointerArray;
struct _SBOLCompoundObject;
struct _DNASequence;
struct _SequenceAnnotation;

/// Implements the SBOL Core DNAComponent object.
typedef struct _DNAComponent {
	struct _SBOLCompoundObject* base;  ///< uri, displayID, name, description
	struct _DNASequence* dnaSequence;  ///< sequence
	struct _PointerArray* annotations; ///< array of SequenceAnnotations
} DNAComponent;

/// Create an empty DNAComponent.
SBOLAPIEXPORTS DNAComponent* createDNAComponent(const char* uri);

/// Delete a DNAComponent.
/// This doesn't delete any of the other structs
/// it references.
SBOLAPIEXPORTS void deleteDNAComponent(DNAComponent* com);

// work with storage
int isDNAComponentPtr(const void* pointer); // TODO rename and export
SBOLAPIEXPORTS int isDNAComponentID(const char* uri);
SBOLAPIEXPORTS int getNumDNAComponents();
SBOLAPIEXPORTS DNAComponent* getNthDNAComponent(int n);

// tools for iteration
SBOLAPIEXPORTS DNAComponent* getDNAComponent(const char* uri);
SBOLAPIEXPORTS int getNumSequenceAnnotationsIn(const DNAComponent* com);
SBOLAPIEXPORTS struct _SequenceAnnotation* getNthSequenceAnnotationIn(const DNAComponent* com, int n);

// get properties
SBOLAPIEXPORTS char* getDNAComponentURI(const DNAComponent* com);
SBOLAPIEXPORTS char* getDNAComponentDisplayID(const DNAComponent* com);
SBOLAPIEXPORTS char* getDNAComponentName(const DNAComponent* com);
SBOLAPIEXPORTS char* getDNAComponentDescription(const DNAComponent* com);
SBOLAPIEXPORTS struct _DNASequence* getDNAComponentSequence(DNAComponent* com);

// set properties
SBOLAPIEXPORTS void setDNAComponentURI(DNAComponent* com, const char* uri);
SBOLAPIEXPORTS void setDNAComponentDisplayID(DNAComponent* com, const char* id);
SBOLAPIEXPORTS void setDNAComponentName(DNAComponent* com, const char* name);
SBOLAPIEXPORTS void setDNAComponentDescription(DNAComponent* com, const char* desc);
SBOLAPIEXPORTS void setDNAComponentSequence(DNAComponent* com, struct _DNASequence* seq);

// TODO where should this go?
// work with annotations
SBOLAPIEXPORTS void addSequenceAnnotation(DNAComponent* com, struct _SequenceAnnotation* ann);
SBOLAPIEXPORTS void setSubComponent(struct _SequenceAnnotation* ann, DNAComponent* com);

void printDNAComponent(const DNAComponent* com, int tabs);
void printAllDNAComponents();
void cleanupDNAComponents();

#endif
