#ifndef SBOL_VALIDATOR
#define SBOL_VALIDATOR

// TODO fill this in using CMake
#define SBOL_SCHEMA_FILENAME "../schema/sbol.xsd"

SBOLAPIEXPORTS int isValidSBOL(const xmlDocPtr doc);

#endif
