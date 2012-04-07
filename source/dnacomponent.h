///////////////////////////////////////////////////////////
/// @file
/// Contains the DNAComponent struct, as well
/// as functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_DNACOMPONENT_HEADER
#define SBOL_DNACOMPONENT_HEADER

#include "constants.h"
#include "prototypes.h"

/// Implements the SBOL Core DNAComponent object.
struct _DNAComponent {
	Document* doc;             ///< parent Document
	SBOLCompoundObject* base;  ///< uri, displayID, name, description
	DNASequence* dnaSequence;  ///< sequence
	PointerArray* annotations; ///< array of SequenceAnnotations
};

/// Create an empty DNAComponent.
SBOLAPIEXPORTS DNAComponent* createDNAComponent(Document* doc, const char* uri);

/// Delete a DNAComponent.
/// This doesn't delete any of the other structs
/// it references.
SBOLAPIEXPORTS void deleteDNAComponent(DNAComponent* com);

/// Find out whether this pointer points to a DNAComponent.
SBOLAPIEXPORTS int isDNAComponent(const Document* doc, const void* pointer);

/// Find out if there's a DNAComponent with this uri.
SBOLAPIEXPORTS int isDNAComponentURI(const Document* doc, const char* uri);

/// Get the total number of DNAComponents.
/// Useful as a loop condition.
SBOLAPIEXPORTS int getNumDNAComponents(const Document* doc);

/// Get the Nth DNAComponent.
/// Useful for iterating over all of them.
SBOLAPIEXPORTS DNAComponent* getNthDNAComponent(Document* doc, int n);

/// Get the DNAComponent associated with this uri.
/// Returns NULL on failure.
SBOLAPIEXPORTS DNAComponent* getDNAComponent(Document* doc, const char* uri);

/// Get the number of SequenceAnnotations for a DNAComponent.
SBOLAPIEXPORTS int getNumSequenceAnnotationsFor(const DNAComponent* com);

/// Get the Nth SequenceAnnotation for a DNAComponent.
SBOLAPIEXPORTS SequenceAnnotation* getNthSequenceAnnotationFor(const DNAComponent* com, int n);

/// Get the uri of a DNAComponent.
/// Gotcha: this is different from both name and displayID.
SBOLAPIEXPORTS char* getDNAComponentURI(const DNAComponent* com);

/// Get the displayID of a DNAComponent.
/// Gotcha: this is different from both uri and name.
SBOLAPIEXPORTS char* getDNAComponentDisplayID(const DNAComponent* com);

/// Get the name of a DNAComponent.
/// Gotcha: this is different from both uri and displayID.
SBOLAPIEXPORTS char* getDNAComponentName(const DNAComponent* com);

/// Get the description of a DNAComponent.
SBOLAPIEXPORTS char* getDNAComponentDescription(const DNAComponent* com);

/// Get the DNASequence of a DNAComponent.
/// Gotcha: DNA, not Dna
SBOLAPIEXPORTS DNASequence* getDNAComponentSequence(DNAComponent* com);

/// Set the uri of a DNAComponent.
/// Gotcha: this is different from both name and displayID.
SBOLAPIEXPORTS void setDNAComponentURI(DNAComponent* com, const char* uri);

/// Set the displayID of a DNAComponent.
/// Gotcha: this is different from both uri and name.
SBOLAPIEXPORTS void setDNAComponentDisplayID(DNAComponent* com, const char* id);

/// Set the name of a DNAComponent.
/// Gotcha: this is different from both uri and displayID.
SBOLAPIEXPORTS void setDNAComponentName(DNAComponent* com, const char* name);

/// Set the description of a DNAComponent.
SBOLAPIEXPORTS void setDNAComponentDescription(DNAComponent* com, const char* desc);

/// Set the DNASequence of a DNAComponent.
/// Gotcha: DNA, not Dna
/// @todo how should this handle docs?
SBOLAPIEXPORTS void setDNAComponentSequence(DNAComponent* com, DNASequence* seq);

/// Add a SequenceAnnotation to a DNAComponent.
/// @todo where should this go? here, sequenceannotation.h, sbol.h?
/// @todo how should this handle docs?
SBOLAPIEXPORTS void addSequenceAnnotation(DNAComponent* com, SequenceAnnotation* ann);

/// Set a DNAComponent as the subComponent of a SequenceAnnotation.
/// To remove it later, call this with a NULL annotation.
/// @todo move this to sequenceannotation.h?
/// @todo how should this handle docs?
SBOLAPIEXPORTS void setSequenceAnnotationSubComponent(SequenceAnnotation* ann, DNAComponent* com);

/// @todo removeSequenceAnnotationSubComponent

/// Print an outline of a DNAComponent to stdout.
SBOLAPIEXPORTS void printDNAComponent(const DNAComponent* com, int tabs);

/// Print an outline of all the DNAComponents to stdout.
SBOLAPIEXPORTS void printAllDNAComponents(Document* doc);

/// Delete all DNAComponents.
/// To delete everything instead, use cleanupSBOLCore.
/// @todo remove this? is it ever used?
SBOLAPIEXPORTS void cleanupDNAComponents(Document* doc);

#endif
