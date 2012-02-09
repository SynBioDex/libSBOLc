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
# endif //SBOLAPIEXPORTS

BEGIN_C_DECLS

//forward declaration
struct _DNAComponent;
struct _SequenceAnnotation;
struct _Collection;

/************************************************
        C Structs for the SBOL classes
*************************************************/

/*! \brief DNASequence class
*/
typedef struct _DNASequence
{
	char* nucleotides;
} DNASequence;

/*! \brief DNAcomponent class
*/
typedef struct _DNAComponent
{
	char* id;
	char* name;
	char* description;
	struct _DNASequence * dnaSequence;  //pointer to a single DNASequence
	struct _SequenceAnnotation ** annotations; //null terminated array
	struct _Collection ** collections; //null terminated array
} DNAComponent;


/*! \brief SequenceAnnotation class
*/
typedef struct _SequenceAnnotation
{
	char* id;
	struct _DNAComponent * annotates;
	struct _DNAComponent * subComponent;
	int genbankStart;
	int end;
	struct _SequenceAnnotation ** precedes; //null terminated array
} SequenceAnnotation;


/*! \brief Collection class
*/
typedef struct _Collection
{
	char* id;
	char* name;
	char* description;
	struct _DNAComponent ** components;  //pointer to a single DNASequence
	struct _Collection ** collections; //null terminated array
} Collection;

/************************************************
       SBOL function declarations
*************************************************/

/*! \brief get number of collections*/
SBOLAPIEXPORTS int getNumCollections();

/*! \brief get nth collection*/
SBOLAPIEXPORTS Collection getNthCollection(int n);

/*! \brief get number of collections*/
SBOLAPIEXPORTS int getNumCollectionsFor(DNAComponent component);

/*! \brief get nth collection*/
SBOLAPIEXPORTS Collection getNthCollectionFor(DNAComponent component, int n);

/*! \brief get number of DNA components*/
SBOLAPIEXPORTS int getNumDNAComponents();

/*! \brief get nth DNA component*/
SBOLAPIEXPORTS DNAComponent getNthDNAComponent(int n);

/*! \brief get number of DNA components*/
SBOLAPIEXPORTS int getNumDNAComponentsIn(Collection collection);

/*! \brief get nth DNA component*/
SBOLAPIEXPORTS DNAComponent getNthDNAComponentIn(Collection collection, int n);

/*! \brief get number of Sequence Annotations*/
SBOLAPIEXPORTS int getNumSequenceAnnotations();

/*! \brief get nth annotation*/
SBOLAPIEXPORTS SequenceAnnotation getNthSequenceAnnotation(int n);

/*! \brief get number of annotations in a component*/
SBOLAPIEXPORTS int getNumSequenceAnnotationsIn(DNAComponent component);

/*! \brief get nth annotation in a component*/
SBOLAPIEXPORTS SequenceAnnotation getNthSequenceAnnotationIn(DNAComponent component, int n);

/*! \brief get number of precedes relationships in an annotation*/
SBOLAPIEXPORTS int getNumPrecedes(SequenceAnnotation annotation);

/*! \brief get nth precedes relationship in an annotation*/
SBOLAPIEXPORTS SequenceAnnotation getNthPrecedes(SequenceAnnotation annotation, int n);

/*! \brief set collection id*/
SBOLAPIEXPORTS void setCollectionID(Collection * collection, const char* id);

/*! \brief set collection name*/
SBOLAPIEXPORTS void setCollectionName(Collection * collection, const char* name);

/*! \brief set collection description*/
SBOLAPIEXPORTS void setCollectionDescription(Collection * collection, const char* descr);

/*! \brief set component id*/
SBOLAPIEXPORTS void setComponentID(DNAComponent * component, const char* id);

/*! \brief set component name*/
SBOLAPIEXPORTS void setComponentName(DNAComponent * component, const char* name);

/*! \brief set component description*/
SBOLAPIEXPORTS void setComponentDescription(DNAComponent * component, const char* descr);

/*! \brief add existing component to existing collection*/
SBOLAPIEXPORTS void addComponentToCollection(DNAComponent * component, Collection * collection);

/*! \brief add existing component to existing collection*/
SBOLAPIEXPORTS void setSequenceAnnotationID(SequenceAnnotation * annotation, const char* id);

/*! \brief set sub-component for a sequence annotation*/
SBOLAPIEXPORTS void setSubComponent(SequenceAnnotation * annotation, DNAComponent * component);

/*! \brief add existing sequence annotation to existing DNA component*/
SBOLAPIEXPORTS void addSequenceAnnotation(DNAComponent * component, SequenceAnnotation * annotation);

/*! \brief add precedence relationship between two existing sequence annotations*/
SBOLAPIEXPORTS void addPrecedesRelationship(SequenceAnnotation * upstream, SequenceAnnotation * downstream);

/*! \brief free memory*/
SBOLAPIEXPORTS void cleanup();

END_C_DECLS
#endif
