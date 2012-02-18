#ifndef SBOL_CORE
#define SBOL_CORE
#include <stdlib.h>
#include <stdio.h>

/************************************************
   all the standard defines needed by C libraries
*************************************************/

#ifndef BEGIN_C_DECLS
#ifdef __cplusplus
#        define BEGIN_C_DECLS extern "C" {
#        define END_C_DECLS }
#   else
#        define BEGIN_C_DECLS
#        define END_C_DECLS
#endif
#endif

# ifndef SBOLAPIEXPORTS
#  if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#    if defined(STATIC_LINKED)
#          define SBOLAPIEXPORTS
#    else
#   if defined(SBOL_EXPORTS)
#              if defined(USE_STDCALL)
#                   define SBOLAPIEXPORTS __stdcall __declspec(dllexport)
#              else
#                   define SBOLAPIEXPORTS __declspec(dllexport)
#              endif
#          else
#              define SBOLAPIEXPORTS
#          endif
#     endif
#  else
#    if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#      define SBOLAPIEXPORTS __attribute__ ((visibility("default")))
#    else
#      define SBOLAPIEXPORTS
#    endif
#  endif
# endif

BEGIN_C_DECLS

//forward declaration
struct _DNAComponent;
struct _DNASequence;
struct _SequenceAnnotation;
struct _Collection;

/************************************************
        C Structs for the SBOL core classes
*************************************************/

typedef struct _DNASequence
{
	char* nucleotides;
} DNASequence;

typedef struct _DNAComponent
{
	char* id;
	char* name;
	char* description;
	struct _DNASequence * dnaSequence;  //pointer to a single DNASequence
	struct _SequenceAnnotation ** annotations; //null terminated array
	struct _Collection ** collections; //null terminated array

    int numAnnotations;
    int numCollections;
} DNAComponent;

typedef struct _SequenceAnnotation
{
	char* id;
	struct _DNAComponent * annotates;
	struct _DNAComponent * subComponent;
	int genbankStart;
	int end;
	struct _SequenceAnnotation ** precedes; //null terminated array

    int numPrecedes;
} SequenceAnnotation;

typedef struct _Collection
{
	char* id;
	char* name;
	char* description;
	struct _DNAComponent ** components;  //pointer to multiple DNAComponents
	struct _Collection ** collections; //null terminated array

    int numComponents;
    int numCollections;
} Collection;

/************************************************
       SBOL core function declarations
*************************************************/

SBOLAPIEXPORTS int getNumCollections();
SBOLAPIEXPORTS int getNumDNAComponents();
SBOLAPIEXPORTS int getNumSequenceAnnotations();

SBOLAPIEXPORTS int getNumCollectionsFor(DNAComponent component);
SBOLAPIEXPORTS int getNumDNAComponentsIn(Collection collection);
SBOLAPIEXPORTS int getNumSequenceAnnotationsIn(DNAComponent component);
SBOLAPIEXPORTS int getNumPrecedes(SequenceAnnotation annotation);

SBOLAPIEXPORTS Collection         getNthCollection(int n);
SBOLAPIEXPORTS DNAComponent       getNthDNAComponent(int n);
SBOLAPIEXPORTS SequenceAnnotation getNthSequenceAnnotation(int n);

SBOLAPIEXPORTS Collection         getNthCollectionFor(DNAComponent component, int n);
SBOLAPIEXPORTS DNAComponent       getNthDNAComponentIn(Collection collection, int n);
SBOLAPIEXPORTS SequenceAnnotation getNthSequenceAnnotationIn(DNAComponent component, int n);
SBOLAPIEXPORTS SequenceAnnotation getNthPrecedes(SequenceAnnotation annotation, int n);

SBOLAPIEXPORTS void setCollectionID(Collection * collection, const char* id);
SBOLAPIEXPORTS void setCollectionName(Collection * collection, const char* name);
SBOLAPIEXPORTS void setCollectionDescription(Collection * collection, const char* descr);

SBOLAPIEXPORTS void setComponentID(DNAComponent * component, const char* id);
SBOLAPIEXPORTS void setComponentName(DNAComponent * component, const char* name);
SBOLAPIEXPORTS void setComponentDescription(DNAComponent * component, const char* descr);

SBOLAPIEXPORTS void setSequenceAnnotationID(SequenceAnnotation * annotation, const char* id);
SBOLAPIEXPORTS void setSubComponent(SequenceAnnotation * annotation, DNAComponent * component);

SBOLAPIEXPORTS void addComponentToCollection(DNAComponent * component, Collection * collection);
SBOLAPIEXPORTS void addSequenceAnnotation(DNAComponent * component, SequenceAnnotation * annotation);
SBOLAPIEXPORTS void addPrecedesRelationship(SequenceAnnotation * upstream, SequenceAnnotation * downstream);

SBOLAPIEXPORTS void cleanup();

/************************************************
       "Private" functions that operate
       on global vectors
*************************************************/

//TODO put these in a separate file?

int isComponent(const char* id);
int isAnnotation(const char* id);
int isCollection(const char* id);

void newComponent(const char* id);
void newSequenceAnnotation(const char* id);
void newCollection(const char* id);

DNAComponent getComponent(const char* id);
SequenceAnnotation getSequenceAnnotation(const char* id);
Collection getCollection(const char* id);

END_C_DECLS
#endif
