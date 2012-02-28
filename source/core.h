#ifndef SBOL_CORE
#define SBOL_CORE
#include "api.h"
#include "core/sequence.h"
#include "core/annotation.h"
#include "core/collection.h"
#include "core/component.h"

/***********************************************
 * The SBOL core is split into files to ease
 * maintenance, but since all the structs are
 * interdependent you should probably stick to
 * #including them as a group from here.
 ***********************************************/

// from sequence.h
SBOLAPIEXPORTS DNASequence* createDNASequence(char* nucleotides);
SBOLAPIEXPORTS void deleteDNASequence(DNASequence* seq);

// from component.h
SBOLAPIEXPORTS DNAComponent* createComponent(const char* id);
SBOLAPIEXPORTS void deleteComponent(DNAComponent* com);
SBOLAPIEXPORTS void registerComponent(DNAComponent* com);
SBOLAPIEXPORTS void removeComponent(DNAComponent* com);
SBOLAPIEXPORTS int isComponentPtr(const void* pointer);
SBOLAPIEXPORTS int isComponentID(const char* id);
SBOLAPIEXPORTS int getNumDNAComponents();
SBOLAPIEXPORTS DNAComponent* getNthDNAComponent(int n);
SBOLAPIEXPORTS int getNumCollectionsFor(const DNAComponent* com);
SBOLAPIEXPORTS int getNumSequenceAnnotationsIn(const DNAComponent* com);
SBOLAPIEXPORTS Collection* getNthCollectionFor(const DNAComponent* com, int n);
SBOLAPIEXPORTS SequenceAnnotation* getNthSequenceAnnotationIn(const DNAComponent* com, int n);
SBOLAPIEXPORTS DNAComponent* getComponent(const char* id);
SBOLAPIEXPORTS char* getComponentID(const DNAComponent* com);
SBOLAPIEXPORTS char* getComponentName(const DNAComponent* com);
SBOLAPIEXPORTS char* getComponentDescription(const DNAComponent* com);
SBOLAPIEXPORTS void setComponentID(DNAComponent* com, const char* id);
SBOLAPIEXPORTS void setComponentName(DNAComponent* com, const char* name);
SBOLAPIEXPORTS void setComponentDescription(DNAComponent* com, const char* desc);
SBOLAPIEXPORTS void addSequenceAnnotation(DNAComponent* com, SequenceAnnotation* ann);
SBOLAPIEXPORTS void setSubComponent(SequenceAnnotation* ann, DNAComponent* com);

// from annotation.h
SBOLAPIEXPORTS void registerSequenceAnnotation(SequenceAnnotation* ann);
SBOLAPIEXPORTS void removeAnnotation(SequenceAnnotation* ann);
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

// from collection.h
SBOLAPIEXPORTS Collection* createCollection(const char* id);
SBOLAPIEXPORTS void deleteCollection(Collection* col);
SBOLAPIEXPORTS void registerCollection(Collection* col);
SBOLAPIEXPORTS void removeCollection(Collection* col);
SBOLAPIEXPORTS int isCollectionPtr(const void* pointer);
SBOLAPIEXPORTS int isCollectionID(const char* id);
SBOLAPIEXPORTS int getNumCollections();
SBOLAPIEXPORTS Collection* getCollection(const char* id);
SBOLAPIEXPORTS Collection* getNthCollection(int n);
SBOLAPIEXPORTS int getNumDNAComponentsIn(Collection* col);
SBOLAPIEXPORTS DNAComponent* getNthDNAComponentIn(Collection* col, int n);
SBOLAPIEXPORTS char* getCollectionID(Collection* col);
SBOLAPIEXPORTS char* getCollectionName(Collection* col);
SBOLAPIEXPORTS char* getCollectionDescription(Collection* col);
SBOLAPIEXPORTS void setCollectionID(Collection* col, const char* id); // TODO remove?
SBOLAPIEXPORTS void setCollectionName(Collection* col, const char* name);
SBOLAPIEXPORTS void setCollectionDescription(Collection* col, const char* desc);
SBOLAPIEXPORTS void addComponentToCollection(DNAComponent* com, Collection* col);

// from core.c
SBOLAPIEXPORTS void cleanup();

#endif
