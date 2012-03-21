#ifndef SBOL_VALIDATOR_HEADER
#define SBOL_VALIDATOR_HEADER
#include <libxml/parser.h>
#include "api.h"

// TODO fill this in using CMake
#define SBOL_SCHEMA_FILENAME "../schema/sbol.xsd"

SBOLAPIEXPORTS int isValidSBOL(const xmlDocPtr doc);

#endif
