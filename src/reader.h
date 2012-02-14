#ifndef SBOL_READER
#define SBOL_READER

#include <string.h>
#include "core.h"
#include "raptor.h" //RDF parser

/*! \brief read n-triples file
 */
SBOLAPIEXPORTS void readSBOL(char* filename);

#endif
