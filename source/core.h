#ifndef SBOL_CORE
#define SBOL_CORE
#include "api.h"

/***********************************************
 * The SBOL core is split into files to ease
 * maintenance, but since all the structs are
 * interdependent you should probably stick to
 * #including them as a group from here.
 ***********************************************/

// forward declarations
struct _SequenceAnnotation;
struct _DNAComponent;
struct _DNASequence;
struct _Collection;

// from sequence.h
SBOLAPIEXPORTS struct _DNASequence* createDNASequence(char* nucleotides);
SBOLAPIEXPORTS void deleteDNASequence(struct _DNASequence* seq);

// from component.h
SBOLAPIEXPORTS struct _DNAComponent* createComponent(const char* id);
SBOLAPIEXPORTS void deleteComponent(struct _DNAComponent* com);
SBOLAPIEXPORTS void registerComponent(struct _DNAComponent* com);
SBOLAPIEXPORTS void removeComponent(struct _DNAComponent* com);
SBOLAPIEXPORTS int isComponentPtr(const void* pointer);
SBOLAPIEXPORTS int isComponentID(const char* id);
SBOLAPIEXPORTS int getNumDNAComponents();
SBOLAPIEXPORTS struct _DNAComponent* getNthDNAComponent(int n);
SBOLAPIEXPORTS int getNumCollectionsFor(const struct _DNAComponent* com);
SBOLAPIEXPORTS int getNumSequenceAnnotationsIn(const struct _DNAComponent* com);
SBOLAPIEXPORTS struct _Collection* getNthCollectionFor(const struct _DNAComponent* com, int n);
SBOLAPIEXPORTS struct _SequenceAnnotation* getNthSequenceAnnotationIn(const struct _DNAComponent* com, int n);
SBOLAPIEXPORTS char* getComponentID(const struct _DNAComponent* com);
SBOLAPIEXPORTS char* getComponentName(const struct _DNAComponent* com);
SBOLAPIEXPORTS char* getComponentDescription(const struct _DNAComponent* com);
SBOLAPIEXPORTS void setComponentID(struct _DNAComponent* com, const char* id);
SBOLAPIEXPORTS void setComponentName(struct _DNAComponent* com, const char* name);
SBOLAPIEXPORTS void setComponentDescription(struct _DNAComponent* com, const char* desc);
SBOLAPIEXPORTS void addSequenceAnnotation(struct _DNAComponent* com, struct _SequenceAnnotation* ann);
SBOLAPIEXPORTS void setSubComponent(struct _SequenceAnnotation* ann, struct _DNAComponent* com);

// from annotation.h
SBOLAPIEXPORTS void registerSequenceAnnotation(struct _SequenceAnnotation* ann);
SBOLAPIEXPORTS void removeAnnotation(struct _SequenceAnnotation* ann);
SBOLAPIEXPORTS int isAnnotationPtr(const void* pointer);
SBOLAPIEXPORTS int isAnnotationID(const char* id);
SBOLAPIEXPORTS int getNumSequenceAnnotations();
SBOLAPIEXPORTS struct _SequenceAnnotation* getNthSequenceAnnotation(int n);
SBOLAPIEXPORTS struct _SequenceAnnotation* createSequenceAnnotation(const char* id);
SBOLAPIEXPORTS void setSequenceAnnotationID(struct _SequenceAnnotation* ann, const char* id);
SBOLAPIEXPORTS void deleteSequenceAnnotation(struct _SequenceAnnotation* ann);
SBOLAPIEXPORTS void addPrecedesRelationship(struct _SequenceAnnotation* upstream, struct _SequenceAnnotation* downstream);
SBOLAPIEXPORTS int getNumPrecedes(struct _SequenceAnnotation* ann);
SBOLAPIEXPORTS struct _SequenceAnnotation* getNthPrecedes(struct _SequenceAnnotation* ann, int n);

// from collection.h
SBOLAPIEXPORTS struct _Collection* createCollection(const char* id);
SBOLAPIEXPORTS void deleteCollection(struct _Collection* col);
SBOLAPIEXPORTS void registerCollection(struct _Collection* col);
SBOLAPIEXPORTS void removeCollection(struct _Collection* col);
SBOLAPIEXPORTS int isCollectionPtr(const void* pointer);
SBOLAPIEXPORTS int isCollectionID(const char* id);
SBOLAPIEXPORTS int getNumCollections();
SBOLAPIEXPORTS struct _Collection* getNthCollection(int n);
SBOLAPIEXPORTS int getNumDNAComponentsIn(struct _Collection* col);
SBOLAPIEXPORTS struct _DNAComponent* getNthDNAComponentIn(struct _Collection* col, int n);
SBOLAPIEXPORTS char* getCollectionID(struct _Collection* col);
SBOLAPIEXPORTS char* getCollectionName(struct _Collection* col);
SBOLAPIEXPORTS char* getCollectionDescription(struct _Collection* col);
SBOLAPIEXPORTS void setCollectionID(struct _Collection* col, const char* id); // TODO remove?
SBOLAPIEXPORTS void setCollectionName(struct _Collection* col, const char* name);
SBOLAPIEXPORTS void setCollectionDescription(struct _Collection* col, const char* desc);
SBOLAPIEXPORTS void addComponentToCollection(struct _DNAComponent* com, struct _Collection* col);

// from core.c
SBOLAPIEXPORTS void cleanup();

#endif
