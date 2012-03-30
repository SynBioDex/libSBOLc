///////////////////////////////////////////////////////////
/// @file dnacomponent.h
/// This file contains the DNAComponent struct, as well
/// as functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_DNACOMPONENT_HEADER
#define SBOL_DNACOMPONENT_HEADER

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
DNAComponent* createDNAComponent(const char* uri);

/// Delete a DNAComponent.
/// This doesn't delete any of the other structs
/// it references.
void deleteDNAComponent(DNAComponent* com);

// work with storage
int isDNAComponentPtr(const void* pointer); // TODO rename and export
int isDNAComponentURI(const char* uri);
int getNumDNAComponents();
DNAComponent* getNthDNAComponent(int n);

// tools for iteration
DNAComponent* getDNAComponent(const char* uri);
int getNumSequenceAnnotationsIn(const DNAComponent* com);
struct _SequenceAnnotation* getNthSequenceAnnotationIn(const DNAComponent* com, int n);

// get properties
char* getDNAComponentURI(const DNAComponent* com);
char* getDNAComponentDisplayID(const DNAComponent* com);
char* getDNAComponentName(const DNAComponent* com);
char* getDNAComponentDescription(const DNAComponent* com);
struct _DNASequence* getDNAComponentSequence(DNAComponent* com);

// set properties
void setDNAComponentURI(DNAComponent* com, const char* uri);
void setDNAComponentDisplayID(DNAComponent* com, const char* id);
void setDNAComponentName(DNAComponent* com, const char* name);
void setDNAComponentDescription(DNAComponent* com, const char* desc);
void setDNAComponentSequence(DNAComponent* com, struct _DNASequence* seq);

// TODO where should this go?
// work with annotations
void addSequenceAnnotation(DNAComponent* com, struct _SequenceAnnotation* ann);
void setSubComponent(struct _SequenceAnnotation* ann, DNAComponent* com);

void printDNAComponent(const DNAComponent* com, int tabs);
void printAllDNAComponents();
void cleanupDNAComponents();

#endif
