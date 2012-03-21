#ifndef SBOL_HEADER
#define SBOL_HEADER
#include "debug.h"
#include "property.h"
#include "api.h"

/***********************************************
 * The SBOL core is split into files to ease
 * maintenance, but since all the structs are
 * interdependent you should probably stick to
 * #including them as a group from here.
 ***********************************************/

// from other files
#include "utilities.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"
#include "types.h"
#include "validator.h"
#include "reader.h"
#include "writer.h"

// from core.c
SBOLAPIEXPORTS void printSBOLCore();
SBOLAPIEXPORTS void cleanupSBOLCore();

#endif
