////////////////////////////////////////////////////////////
/// @file
/// 
/// Defines the Document struct, as well as
/// functions for operating on it.
////////////////////////////////////////////////////////////

#ifndef SBOL_DOCUMENT_HEADER
#define SBOL_DOCUMENT_HEADER

struct _Document{
    PointerArray* allDNASequences;
    PointerArray* allSequenceAnnotations;
    PointerArray* allDNAComponents;
    PointerArray* allCollections;
} Document;

/// Create an empty Document.
SBOLAPIEXPORTS Document* createDocument();

/// Delete a Document. This also deletes all the
/// SBOL objects contained in the Document.
SBOLAPIEXPORTS void deleteDocument(Document* doc);

/// Find out whether there's an SBOL object with this URI in this Document.
/// Useful for avoiding duplicates.
SBOLAPIEXPORTS int isSBOLObjectURI(const Document* doc, const char* uri);

/// Find out the total number of SBOL objects in a Document.
/// @todo should this be exported? is it ever used?
int getNumSBOLObjects(const Document* doc);

/// Print a Document to stdout.
/// Mainly for debugging.
SBOLAPITEXPORTS void printDocument(const Document* doc, int tabs);

#endif