%module libsbol
%{
    #define SWIG_FILE_WITH_INIT

    #include <libxml/xmlmemory.h>
    #include <libxml/parser.h>
    #include <libxml/xpath.h>
    #include <libxml/xmlwriter.h>

    #include "constants.h"
    #include "prototypes.h"
    #include "array.h"
    #include "utilities.h"
	#include "document.h"
    #include "collection.h"
    #include "dnacomponent.h"
    #include "dnasequence.h"
    #include "object.h"
    #include "property.h"
    #include "reader.h"
    #include "sequenceannotation.h"
    #include "validator.h"
    #include "writer.h"
    #include "sbol.h"
%}

#ifdef SWIGWIN
    %include <windows.i>
#endif

enum StrandPolarity {
	STRAND_FORWARD,
	STRAND_BIDIRECTIONAL,
	STRAND_REVERSE
};

// tell SWIG how to free strings
%typemap(newfree) char* "free($1);";

// tell SWIG to free the strings returned
// from these functions immediately
// (after copying their values into Python)
%newobject getDNASequenceNucleotides;
%newobject getDNASequenceURI;
%newobject getSequenceAnnotationURI;
%newobject getDNAComponentURI;
%newobject getDNAComponentDisplayID;
%newobject getDNAComponentName;
%newobject getDNAComponentDescription;
%newobject getCollectionURI;
%newobject getCollectionDisplayID;
%newobject getCollectionName;
%newobject getCollectionDescription;

// tell SWIG that these functions delete
// their first argument, and it doesnt need
// to be garbage collected
// (SBOL objects are managed manually anyway,
//  so this just makes doubly sure to avoid segfaults
//  from freeing twice)
%delobject deleteDNASequence;
%delobject deleteSequenceAnnotation;
%delobject deleteDNAComponent;
%delobject deleteCollection;

// functions returing pointers to new objects
Document* createDocument();
DNASequence* createDNASequence(Document* doc, const char* uri);
DNAComponent* createDNAComponent(Document* doc, const char* uri);
Collection* createCollection(Document* doc, const char* uri);
SequenceAnnotation* createSequenceAnnotation(Document* doc, const char* uri);
DNAComponent* copyDNAComponent(DNAComponent* com, char* id_modifier);
DNASequence* copyDNASequence(DNASequence* seq, char* id_modifier);
SequenceAnnotation* copySequenceAnnotation(SequenceAnnotation* ann, char* id_modifier);


// functions that delete objects
void deleteDocument(Document* doc);
void deleteDNASequence(DNASequence* seq);
void deleteSequenceAnnotation(SequenceAnnotation* ann);
void deleteDNAComponent(DNAComponent* com);
void deleteCollection(Collection* col);
void removeDNASequence(Document* doc, DNASequence* seq);
void removeSequenceAnnotation(Document* doc, SequenceAnnotation* ann);
void removeDNAComponent(Document* doc, DNAComponent* com);
void removeCollection(Document* doc, Collection* col);

// funtions returning strings to be newfree()d
char* getDNASequenceNucleotides(const DNASequence* seq);
char* getDNASequenceURI(const DNASequence* seq);
char* getSequenceAnnotationURI(const SequenceAnnotation* ann);
char* getDNAComponentURI(const DNAComponent* com);
char* getDNAComponentDisplayID(const DNAComponent* com);
char* getDNAComponentName(const DNAComponent* com);
char* getDNAComponentDescription(const DNAComponent* com);
char* getDNAComponentType(const DNAComponent* com);
char* getCollectionURI(const Collection* col);
char* getCollectionDisplayID(const Collection* col);
char* getCollectionName(const Collection* col);
char* getCollectionDescription(const Collection* col);
char* writeDocumentToString(Document* doc);

// functions returning pointers to existing objects
DNASequence* getDNASequence(Document* doc, const char* uri);
DNASequence* getNthDNASequence(Document* doc, int n);
DNASequence* getDNAComponentSequence(DNAComponent* com);
SequenceAnnotation* getSequenceAnnotation(Document* doc, const char* uri);
SequenceAnnotation* getNthSequenceAnnotation(Document* doc, int n);
SequenceAnnotation* getNthPrecedes(const SequenceAnnotation* ann, int n);
SequenceAnnotation* getNthSequenceAnnotationFor(const DNAComponent* com, int n);
DNAComponent* getNthDNAComponent(Document* doc, int n);
DNAComponent* getDNAComponent(Document* doc, const char* uri);
DNAComponent* getSequenceAnnotationSubComponent(const SequenceAnnotation* ann);
DNAComponent* getNthDNAComponentIn(const Collection* col, int n);
Collection* getCollection(Document* doc, const char* uri);
Collection* getNthCollection(Document* doc, int n);

// functions returning ints
int getNumSBOLObjects(Document* doc);
int isSBOLObjectURI(Document* doc, const char* uri);
int getNumDNASequences(Document* doc);
int isDNASequenceURI(Document* doc, const char* uri);
int isSequenceAnnotation(Document* doc, const void* pointer);
int isSequenceAnnotationURI(Document* doc, const char* uri);
int getNumSequenceAnnotations(Document* doc);
int getSequenceAnnotationStart(const SequenceAnnotation* ann);
int getSequenceAnnotationEnd(const SequenceAnnotation* ann);
int getSequenceAnnotationStrand(const SequenceAnnotation* ann);
int getNumPrecedes(const SequenceAnnotation* ann);
int precedes(const SequenceAnnotation* upstream, const SequenceAnnotation* downstream);
int isDNAComponent(Document* doc, const void* pointer);
int isDNAComponentURI(Document* doc, const char* uri);
int getNumDNAComponents(Document* doc);
int getNumSequenceAnnotationsFor(const DNAComponent* com);
int isCollection(Document* doc, const void* pointer);
int isCollectionURI(Document* doc, const char* uri);
int getNumCollections(Document* doc);
int getNumDNAComponentsIn(const Collection* col);
int dnaComponentInCollection(const DNAComponent* com, const Collection* col);
int writeDocumentToFile(Document* doc, const char* filename);

// functions returning void
void setDNASequenceNucleotides(DNASequence* seq, const char* nucleotides);
void printDNASequence(const DNASequence* seq, int tabs);
void setSequenceAnnotationStart(SequenceAnnotation* ann, int start);
void setSequenceAnnotationEnd(SequenceAnnotation* ann, int end);
void setSequenceAnnotationStrand(SequenceAnnotation* ann, int polarity);
void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
void removePrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
void printSequenceAnnotation(const SequenceAnnotation* seq, int tabs);
void setDNAComponentURI(DNAComponent* com, const char* uri);
void setDNAComponentDisplayID(DNAComponent* com, const char* id);
void setDNAComponentName(DNAComponent* com, const char* name);
void setDNAComponentDescription(DNAComponent* com, const char* desc);
void setDNAComponentSequence(DNAComponent* com, DNASequence* seq);
void setDNAComponentType(DNAComponent* com, const char* uri);
void addSequenceAnnotation(DNAComponent* com, SequenceAnnotation* ann);
void removeSequenceAnnotationFromDNAComponent(DNAComponent* com, SequenceAnnotation* ann);
void setSequenceAnnotationSubComponent(SequenceAnnotation* ann, DNAComponent* com);
void printDNAComponent(const DNAComponent* com, int tabs);
void setCollectionDisplayID(Collection* col, const char* id);
void setCollectionName(Collection* col, const char* name);
void setCollectionDescription(Collection* col, const char* desc);
void addDNAComponentToCollection(Collection* col, DNAComponent* com);
void removeDNAComponentFromCollection(Collection* col, DNAComponent* com);
void printCollection(const Collection* col, int tabs);
void readDocument(Document* doc, char* filename);
void printDocument(Document* doc);
void deleteDocument(Document* doc);

