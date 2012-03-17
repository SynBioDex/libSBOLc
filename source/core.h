#ifndef SBOL_CORE
#define SBOL_CORE
#include "core/debug.h"
#include "core/property.h"
#include "core/dnasequence.h"
#include "core/sequenceannotation.h"
#include "core/dnacomponent.h"
#include "core/collection.h"
#include "api.h"

// TODO readSBOLCore --> loadSBOLCore and writeSBOLCore --> saveSBOLCore
// TODO delete* --> free* ?

/***********************************************
 * The SBOL core is split into files to ease
 * maintenance, but since all the structs are
 * interdependent you should probably stick to
 * #including them as a group from here.
 ***********************************************/

// from debug.h
SBOLAPIEXPORTS void indent(int tabs);

// from property.h
// TODO these shouldn't be exported

// TextProperty
SBOLAPIEXPORTS TextProperty* createText();
SBOLAPIEXPORTS void deleteText(TextProperty* pro);
SBOLAPIEXPORTS void setText(TextProperty* pro, const char* text);
SBOLAPIEXPORTS char* getText(const TextProperty* pro);
SBOLAPIEXPORTS int compareText(const TextProperty* pro1, const TextProperty* pro2);
SBOLAPIEXPORTS void printText(const TextProperty* pro);

// URIProperty
SBOLAPIEXPORTS URIProperty* createURI();
SBOLAPIEXPORTS void deleteURI(URIProperty* pro);
SBOLAPIEXPORTS void setURI(URIProperty* pro, const char* uri);
SBOLAPIEXPORTS char* getURI(const URIProperty* pro);
SBOLAPIEXPORTS int compareURI(const URIProperty* pro1, const URIProperty* pro2);
SBOLAPIEXPORTS void printURI(const URIProperty* pro);

// IntProperty
SBOLAPIEXPORTS IntProperty* createInt();
SBOLAPIEXPORTS void deleteInt(IntProperty* pro);
SBOLAPIEXPORTS void setInt(IntProperty* pro, const int value);
SBOLAPIEXPORTS int getInt(const IntProperty* pro);
SBOLAPIEXPORTS int compareInt(const IntProperty* pro1, const IntProperty* pro2);
SBOLAPIEXPORTS void printInt(const IntProperty* pro);

// PositionProperty
SBOLAPIEXPORTS PositionProperty* createPosition();
SBOLAPIEXPORTS void deletePosition(PositionProperty* pro);
SBOLAPIEXPORTS void setPosition(PositionProperty* pro, const int value);
SBOLAPIEXPORTS int getPosition(const PositionProperty* pro);
SBOLAPIEXPORTS int comparePosition(const PositionProperty* pro1, const PositionProperty* pro2);
SBOLAPIEXPORTS void printPosition(const PositionProperty* pro);

// PolarityProperty
SBOLAPIEXPORTS PolarityProperty* createPolarity();
SBOLAPIEXPORTS void deletePolarity(PolarityProperty* pro);
SBOLAPIEXPORTS void setPolarity(PolarityProperty* pro, const int value);
SBOLAPIEXPORTS int getPolarity(const PolarityProperty* pro);
SBOLAPIEXPORTS int comparePolarity(const PolarityProperty* pro1, const PolarityProperty* pro2);
SBOLAPIEXPORTS void printPolarity(const PolarityProperty* pro);

// from dnasequence.h
// TODO create with URI and not sequence
SBOLAPIEXPORTS DNASequence* createDNASequence(char* uri);
SBOLAPIEXPORTS void setNucleotides(DNASequence* seq, const char* nucleotides);
SBOLAPIEXPORTS void deleteDNASequence(DNASequence* seq);
SBOLAPIEXPORTS void printDNASequence(const DNASequence* seq, int tabs);
SBOLAPIEXPORTS void printAllDNASequences();

// from sequenceannotation.h
SBOLAPIEXPORTS void setBioStart(SequenceAnnotation* ann, int start);
SBOLAPIEXPORTS void setBioEnd(SequenceAnnotation* ann, int end);
SBOLAPIEXPORTS int isAnnotationPtr(const void* pointer);
SBOLAPIEXPORTS int isSequenceAnnotationURI(const char* uri);
SBOLAPIEXPORTS SequenceAnnotation* getSequenceAnnotation(const char* uri);
SBOLAPIEXPORTS int getNumSequenceAnnotations();
SBOLAPIEXPORTS SequenceAnnotation* getNthSequenceAnnotation(int n);
SBOLAPIEXPORTS SequenceAnnotation* createSequenceAnnotation(const char* uri);
SBOLAPIEXPORTS void setSequenceAnnotationURI(SequenceAnnotation* ann, const char* uri);
SBOLAPIEXPORTS void deleteSequenceAnnotation(SequenceAnnotation* ann);
SBOLAPIEXPORTS void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
SBOLAPIEXPORTS int getNumPrecedes(const SequenceAnnotation* ann);
SBOLAPIEXPORTS SequenceAnnotation* getNthPrecedes(const SequenceAnnotation* ann, int n);
SBOLAPIEXPORTS void printSequenceAnnotation(const SequenceAnnotation* ann, int tabs);
SBOLAPIEXPORTS void printAllSequenceAnnotations();
SBOLAPIEXPORTS DNAComponent* getSubComponent(const SequenceAnnotation* ann);
SBOLAPIEXPORTS int precedes(const SequenceAnnotation* seq1, const SequenceAnnotation* seq2);

// from dnacomponent.h
SBOLAPIEXPORTS DNAComponent* createDNAComponent(const char* uri);
SBOLAPIEXPORTS void deleteDNAComponent(DNAComponent* com);
SBOLAPIEXPORTS int isDNAComponentPtr(const void* pointer);
SBOLAPIEXPORTS int isDNAComponentURI(const char* uri);
SBOLAPIEXPORTS int getNumDNAComponents();
SBOLAPIEXPORTS DNAComponent* getNthDNAComponent(int n);
SBOLAPIEXPORTS int getNumCollectionsFor(const DNAComponent* com);
SBOLAPIEXPORTS int getNumSequenceAnnotationsIn(const DNAComponent* com);
SBOLAPIEXPORTS Collection* getNthCollectionFor(const DNAComponent* com, int n);
SBOLAPIEXPORTS SequenceAnnotation* getNthSequenceAnnotationIn(const DNAComponent* com, int n);
SBOLAPIEXPORTS DNAComponent* getDNAComponent(const char* uri);
SBOLAPIEXPORTS char* getDNAComponentURI(const DNAComponent* com);
SBOLAPIEXPORTS char* getDNAComponentName(const DNAComponent* com);
SBOLAPIEXPORTS char* getDNAComponentDescription(const DNAComponent* com);
SBOLAPIEXPORTS void setDNAComponentURI(DNAComponent* com, const char* uri);
SBOLAPIEXPORTS void setDNAComponentName(DNAComponent* com, const char* name);
SBOLAPIEXPORTS void setDNAComponentDescription(DNAComponent* com, const char* desc);
SBOLAPIEXPORTS void addSequenceAnnotation(DNAComponent* com, SequenceAnnotation* ann);
SBOLAPIEXPORTS void setSubComponent(SequenceAnnotation* ann, DNAComponent* com);
SBOLAPIEXPORTS void printDNAComponent(const DNAComponent* com, int tabs);
SBOLAPIEXPORTS void printAllDNAComponents();

// from collection.h
SBOLAPIEXPORTS Collection* createCollection(const char* uri);
SBOLAPIEXPORTS void deleteCollection(Collection* col);
SBOLAPIEXPORTS int isCollectionPtr(const void* pointer);
SBOLAPIEXPORTS int isCollectionURI(const char* uri);
SBOLAPIEXPORTS int getNumCollections();
SBOLAPIEXPORTS Collection* getCollection(const char* uri);
SBOLAPIEXPORTS Collection* getNthCollection(int n);
SBOLAPIEXPORTS int getNumDNAComponentsIn(const Collection* col);
SBOLAPIEXPORTS int getNumCollectionsIn(const Collection* col);
SBOLAPIEXPORTS DNAComponent* getNthDNAComponentIn(const Collection* col, int n);
SBOLAPIEXPORTS char* getCollectionURI(const Collection* col);
SBOLAPIEXPORTS char* getCollectionName(const Collection* col);
SBOLAPIEXPORTS char* getCollectionDescription(const Collection* col);
SBOLAPIEXPORTS void setCollectionURI(Collection* col, const char* uri); // TODO remove
SBOLAPIEXPORTS void setCollectionName(Collection* col, const char* name);
SBOLAPIEXPORTS void setCollectionDescription(Collection* col, const char* desc);
SBOLAPIEXPORTS void addDNAComponentToCollection(DNAComponent* com, Collection* col);
SBOLAPIEXPORTS void printCollection(const Collection* col, int tabs);
SBOLAPIEXPORTS void printAllCollections();

// from core.c
SBOLAPIEXPORTS void printSBOLCore();
SBOLAPIEXPORTS void cleanupSBOLCore();
int isDuplicateURI(const char* uri);

// from utilities.c
SBOLAPIEXPORTS int sameContent(const char* filename1, const char* filename2);

#endif
