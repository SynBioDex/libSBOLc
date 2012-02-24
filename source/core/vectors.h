#ifndef SBOL_CORE_VECTORS
#define SBOL_CORE_VECTORS

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

// check struct type by ID
int isComponent(const char* id);
int isAnnotation(const char* id);
int isCollection(const char* id);

// get struct by ID
DNAComponent getComponent(const char* id);
Collection getCollection(const char* id);
SequenceAnnotation getSequenceAnnotation(const char* id);

// iterate through structs
int getNumCollections();
int getNumDNAComponents();
int getNumSequenceAnnotations();
Collection getNthCollection(int n);
DNAComponent getNthDNAComponent(int n);
SequenceAnnotation getNthSequenceAnnotation(int n);

// free memory
void cleanup();

END_C_DECLS

#endif
