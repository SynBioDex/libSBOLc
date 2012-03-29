///////////////////////////////////////////////////////////
/// @file validator.h
/// This file defines the isValidSBOL function, which
/// is used to verify SBOL documents before parsing.
/// It only catches errors that are defined in the SBOL
/// schema, and will miss logical inconsistencies like
/// cyclic precedes, bioStart being after bioEnd, etc.
/// Separate functions will probably have to be written
/// for those cases, and this would be a good place to
/// put them.
///////////////////////////////////////////////////////////

#ifndef SBOL_VALIDATOR_HEADER
#define SBOL_VALIDATOR_HEADER
#include <libxml/parser.h>

// TODO fill this in using CMake
#define SBOL_SCHEMA_FILENAME "../schema/sbol.xsd"

int isValidSBOL(const xmlDocPtr doc);

#endif
