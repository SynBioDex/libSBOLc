///////////////////////////////////////////////////////////
/// @file dnacomponent.h
/// Contains the DNAComponent struct, as well
/// as functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_DNACOMPONENT_HEADER
#define SBOL_DNACOMPONENT_HEADER

#include "constants.h"
#include "prototypes.h"

/// Implements the SBOL Core DNAComponent object.
typedef struct DNAComponent {
	struct SBOLCompoundObject* base;  ///< uri, displayID, name, description
	struct DNASequence* dnaSequence;  ///< sequence
	struct PointerArray* annotations; ///< array of SequenceAnnotations
} DNAComponent;

/// Create an empty DNAComponent.
DNAComponent* createDNAComponent(const char* uri);

/// Delete a DNAComponent.
/// This doesn't delete any of the other structs
/// it references.
void deleteDNAComponent(DNAComponent* com);

/// Find out whether this pointer points to a DNAComponent.
int isDNAComponent(const void* pointer);

/// Find out if there's a DNAComponent with this uri.
int isDNAComponentURI(const char* uri);

/// Get the total number of DNAComponents.
/// Useful as a loop condition.
int getNumDNAComponents();

/// Get the Nth DNAComponent.
/// Useful for iterating over all of them.
DNAComponent* getNthDNAComponent(int n);

/// Get the DNAComponent associated with this uri.
/// Returns NULL on failure.
DNAComponent* getDNAComponent(const char* uri);

/// Get the number of SequenceAnnotations for a DNAComponent.
int getNumSequenceAnnotationsFor(const DNAComponent* com);

/// Get the Nth SequenceAnnotation for a DNAComponent.
struct SequenceAnnotation* getNthSequenceAnnotationFor(const DNAComponent* com, int n);

/// Get the uri of a DNAComponent.
/// Gotcha: this is different from both name and displayID.
char* getDNAComponentURI(const DNAComponent* com);

/// Get the displayID of a DNAComponent.
/// Gotcha: this is different from both uri and name.
char* getDNAComponentDisplayID(const DNAComponent* com);

/// Get the name of a DNAComponent.
/// Gotcha: this is different from both uri and displayID.
char* getDNAComponentName(const DNAComponent* com);

/// Get the description of a DNAComponent.
char* getDNAComponentDescription(const DNAComponent* com);

/// Get the DNASequence of a DNAComponent.
/// Gotcha: DNA, not Dna
struct DNASequence* getDNAComponentSequence(DNAComponent* com);

/// Set the uri of a DNAComponent.
/// Gotcha: this is different from both name and displayID.
void setDNAComponentURI(DNAComponent* com, const char* uri);

/// Set the displayID of a DNAComponent.
/// Gotcha: this is different from both uri and name.
void setDNAComponentDisplayID(DNAComponent* com, const char* id);

/// Set the name of a DNAComponent.
/// Gotcha: this is different from both uri and displayID.
void setDNAComponentName(DNAComponent* com, const char* name);

/// Set the description of a DNAComponent.
void setDNAComponentDescription(DNAComponent* com, const char* desc);

/// Set the DNASequence of a DNAComponent.
/// Gotcha: DNA, not Dna
void setDNAComponentSequence(DNAComponent* com, struct DNASequence* seq);

/// Add a SequenceAnnotation to a DNAComponent.
/// @todo where should this go? here, sequenceannotation.h, sbol.h?
void addSequenceAnnotation(DNAComponent* com, struct SequenceAnnotation* ann);

/// Set a DNAComponent as the subComponent of a SequenceAnnotation.
/// To remove it later, call this with a NULL annotation.
void setSubComponent(struct SequenceAnnotation* ann, DNAComponent* com);

/// Print an outline of a DNAComponent to stdout.
void printDNAComponent(const DNAComponent* com, int tabs);

/// Print an outline of all the DNAComponents to stdout.
void printAllDNAComponents();

/// Delete all DNAComponents.
/// To delete everything instead, use cleanupSBOLCore.
/// @todo remove this? is it ever used?
void cleanupDNAComponents();

#endif
