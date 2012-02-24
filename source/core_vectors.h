#ifndef SBOL_CORE_VECTORS
#define SBOL_CORE_VECTORS
#include <stdlib.h> // TODO needed?
#include <stdio.h> // TODO needed?
#include <string.h>
#include <string>
#include "core_common.h"

#ifndef BEGIN_C_DECLS
#	ifdef __cplusplus
#		define BEGIN_C_DECLS extern "C" {
#		define END_C_DECLS }
#   else
#		define BEGIN_C_DECLS
#		define END_C_DECLS
#	endif
#endif

BEGIN_C_DECLS

SBOLAPIEXPORTS int isComponent(const char* id);
SBOLAPIEXPORTS int isAnnotation(const char* id);
SBOLAPIEXPORTS int isCollection(const char* id);

SBOLAPIEXPORTS int getNumCollections();
SBOLAPIEXPORTS int getNumDNAComponents();
SBOLAPIEXPORTS int getNumSequenceAnnotations();

SBOLAPIEXPORTS Collection getNthCollection(int n);
SBOLAPIEXPORTS DNAComponent getNthDNAComponent(int n);
SBOLAPIEXPORTS SequenceAnnotation getNthSequenceAnnotation(int n);

SBOLAPIEXPORTS DNAComponent getComponent(const char* id);
SBOLAPIEXPORTS Collection getCollection(const char* id);
SBOLAPIEXPORTS SequenceAnnotation getSequenceAnnotation(const char* id);

SBOLAPIEXPORTS void cleanup();

END_C_DECLS

#endif
