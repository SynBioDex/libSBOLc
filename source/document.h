////////////////////////////////////////////////////////////
/// @file
/// 
/// Defines the Document struct, as well as
/// functions for operating on it.
////////////////////////////////////////////////////////////

#ifndef SBOL_DOCUMENT_HEADER
#define SBOL_DOCUMENT_HEADER

#include "constants.h"
#include "prototypes.h"

/// Represents an SBOL document.
/// Holds pointers to all the SBOL objects in the document,
/// and can be read from and written to a file.
/// Deleting this frees them all from memory.
struct _Document{
    PointerArray* sequences;   ///< All the DNASequences in the Document.
    PointerArray* annotations; ///< All the SequenceAnnotations in the Document.
    PointerArray* components;  ///< All the DNAComponents in the Document.
    PointerArray* collections; ///< All the Collections in the Document.
};

/// Create an empty Document.
SBOLAPIEXPORTS Document* createDocument();

/// Delete a Document. This also deletes all the
/// SBOL objects contained in the Document.
SBOLAPIEXPORTS void deleteDocument(Document* doc);

/// Find out whether there's an SBOL object with this URI in this Document.
/// Useful for avoiding duplicates.
SBOLAPIEXPORTS int isSBOLObjectURI(Document* doc, const char* uri);

/// Find out the total number of SBOL objects in a Document.
SBOLAPIEXPORTS int getNumSBOLObjects(Document* doc);

/// Get the total number of DNASequences in emory.
SBOLAPIEXPORTS int getNumDNASequences(const Document* doc);

/// Get the total number of SequenceAnnotations in a Document.
/// Useful as a loop condition.
SBOLAPIEXPORTS int getNumSequenceAnnotations(Document* doc);

/// Get the total number of DNAComponents.
/// Useful as a loop condition.
SBOLAPIEXPORTS int getNumDNAComponents(const Document* doc);

/// Get the total number of Collections.
/// Useful as a loop condition.
SBOLAPIEXPORTS int getNumCollections(Document* doc);

/// Find out whether a pointer points to a DNASequence in this Document.
SBOLAPIEXPORTS int isDNASequence(const Document* doc, const void* pointer);

/// Find out whether a pointer points to a SequenceAnnotation in this Document.
SBOLAPIEXPORTS int isSequenceAnnotation(const Document* doc, const void* pointer);

/// Find out whether this pointer points to a DNAComponent.
SBOLAPIEXPORTS int isDNAComponent(const Document* doc, const void* pointer);

/// Find out whether this pointer points to a Collection.
SBOLAPIEXPORTS int isCollection(Document* doc, const void* pointer);

/// Find out whether there's a DNASequence with this URI.
SBOLAPIEXPORTS int isDNASequenceURI(Document* doc, const char* uri);

/// Find out whether this URI is associated with a SequenceAnnotation in this Document.
SBOLAPIEXPORTS int isSequenceAnnotationURI(Document* doc, const char* uri);

/// Find out if there's a DNAComponent with this uri.
SBOLAPIEXPORTS int isDNAComponentURI(Document* doc, const char* uri);

/// Find out if there's a Collection with this uri.
SBOLAPIEXPORTS int isCollectionURI(Document* doc, const char* uri);

/// Get the DNASequence associated with this URI.
/// Returns NULL on failure.
SBOLAPIEXPORTS DNASequence* getDNASequence(Document* doc, const char* uri);

/// Get the SequenceAnnotation associated with this URI.
/// Returns NULL on failure.
SBOLAPIEXPORTS SequenceAnnotation* getSequenceAnnotation(Document* doc, const char* uri);

/// Get the DNAComponent associated with this uri.
/// Returns NULL on failure.
SBOLAPIEXPORTS DNAComponent* getDNAComponent(Document* doc, const char* uri);

/// Get the Collection associated with this uri.
/// Returns NULL on failure.
SBOLAPIEXPORTS Collection* getCollection(Document* doc, const char* uri);

/// Get the Nth DNASequnce in a Document.
/// Returns NULL on failure.
SBOLAPIEXPORTS DNASequence* getNthDNASequence(Document* doc, int n);

/// Get the Nth SequenceAnnotation in a Document.
/// Useful for iterating through them.
SBOLAPIEXPORTS SequenceAnnotation* getNthSequenceAnnotation(Document* doc, int n);

/// Get the Nth DNAComponent.
/// Useful for iterating over all of them.
SBOLAPIEXPORTS DNAComponent* getNthDNAComponent(Document* doc, int n);

/// Get the Nth Collection.
/// Useful for iterating over all of them.
SBOLAPIEXPORTS Collection* getNthCollection(Document* doc, int n);

/// Print a Document to stdout.
/// Mainly for debugging.
SBOLAPIEXPORTS void printDocument(Document* doc);

#endif
