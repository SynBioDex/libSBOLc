#ifndef SBOL_CORE
#define SBOL_CORE
#include "api.h"
#include "core/dnasequence.h"
#include "core/sequenceannotation.h"
#include "core/dnacomponent.h"
#include "core/collection.h"

/***********************************************
 * The SBOL core is split into files to ease
 * maintenance, but since all the structs are
 * interdependent you should probably stick to
 * #including them as a group from here.
 ***********************************************/

// from dnasequence.h
SBOLAPIEXPORTS DNASequence* createDNASequence(char* nucleotides);
SBOLAPIEXPORTS void deleteDNASequence(DNASequence* seq);

// from sequenceannotation.h
SBOLAPIEXPORTS int isAnnotationPtr(const void* pointer);
SBOLAPIEXPORTS int isSequenceAnnotationID(const char* id);
SBOLAPIEXPORTS SequenceAnnotation* getSequenceAnnotation(const char* id);
SBOLAPIEXPORTS int getNumSequenceAnnotations();
SBOLAPIEXPORTS SequenceAnnotation* getNthSequenceAnnotation(int n);
SBOLAPIEXPORTS SequenceAnnotation* createSequenceAnnotation(const char* id);
SBOLAPIEXPORTS void setSequenceAnnotationID(SequenceAnnotation* ann, const char* id);
SBOLAPIEXPORTS void deleteSequenceAnnotation(SequenceAnnotation* ann);
SBOLAPIEXPORTS void addPrecedesRelationship(SequenceAnnotation* upstream, SequenceAnnotation* downstream);
SBOLAPIEXPORTS int getNumPrecedes(SequenceAnnotation* ann);
SBOLAPIEXPORTS SequenceAnnotation* getNthPrecedes(SequenceAnnotation* ann, int n);

// from dnacomponent.h
SBOLAPIEXPORTS DNAComponent* createDNAComponent(const char* id);
SBOLAPIEXPORTS void deleteDNAComponent(DNAComponent* com);
SBOLAPIEXPORTS int isDNAComponentPtr(const void* pointer);
SBOLAPIEXPORTS int isDNAComponentID(const char* id);
SBOLAPIEXPORTS int getNumDNAComponents();
SBOLAPIEXPORTS DNAComponent* getNthDNAComponent(int n);
SBOLAPIEXPORTS int getNumCollectionsFor(const DNAComponent* com);
SBOLAPIEXPORTS int getNumSequenceAnnotationsIn(const DNAComponent* com);
SBOLAPIEXPORTS Collection* getNthCollectionFor(const DNAComponent* com, int n);
SBOLAPIEXPORTS SequenceAnnotation* getNthSequenceAnnotationIn(const DNAComponent* com, int n);
SBOLAPIEXPORTS DNAComponent* getDNAComponent(const char* id);
SBOLAPIEXPORTS char* getDNAComponentID(const DNAComponent* com);
SBOLAPIEXPORTS char* getDNAComponentName(const DNAComponent* com);
SBOLAPIEXPORTS char* getDNAComponentDescription(const DNAComponent* com);
SBOLAPIEXPORTS void setDNAComponentID(DNAComponent* com, const char* id);
SBOLAPIEXPORTS void setDNAComponentName(DNAComponent* com, const char* name);
SBOLAPIEXPORTS void setDNAComponentDescription(DNAComponent* com, const char* desc);
SBOLAPIEXPORTS void addSequenceAnnotation(DNAComponent* com, SequenceAnnotation* ann);
SBOLAPIEXPORTS void setSubComponent(SequenceAnnotation* ann, DNAComponent* com);

// from collection.h
SBOLAPIEXPORTS Collection* createCollection(const char* id);
SBOLAPIEXPORTS void deleteCollection(Collection* col);
SBOLAPIEXPORTS int isCollectionPtr(const void* pointer);
SBOLAPIEXPORTS int isCollectionID(const char* id);
SBOLAPIEXPORTS int getNumCollections();
SBOLAPIEXPORTS Collection* getCollection(const char* id);
SBOLAPIEXPORTS Collection* getNthCollection(int n);
SBOLAPIEXPORTS int getNumDNAComponentsIn(Collection* col);
SBOLAPIEXPORTS int getNumCollectionsIn(Collection* col);
SBOLAPIEXPORTS DNAComponent* getNthDNAComponentIn(Collection* col, int n);
SBOLAPIEXPORTS char* getCollectionID(Collection* col);
SBOLAPIEXPORTS char* getCollectionName(Collection* col);
SBOLAPIEXPORTS char* getCollectionDescription(Collection* col);
SBOLAPIEXPORTS void setCollectionID(Collection* col, const char* id); // TODO remove?
SBOLAPIEXPORTS void setCollectionName(Collection* col, const char* name);
SBOLAPIEXPORTS void setCollectionDescription(Collection* col, const char* desc);
SBOLAPIEXPORTS void addDNAComponentToCollection(DNAComponent* com, Collection* col);

// from core.c
SBOLAPIEXPORTS void cleanup();

#endif
