#ifndef SBOL_CORE
#define SBOL_CORE
#include "debug.h"
#include "property.h"
#include "api.h"

// TODO rename core --> sbol
// TODO readSBOLCore --> loadSBOLCore and writeSBOLCore --> saveSBOLCore
// TODO deleteX --> freeX ?

/***********************************************
 * The SBOL core is split into files to ease
 * maintenance, but since all the structs are
 * interdependent you should probably stick to
 * #including them as a group from here.
 ***********************************************/

// from other files
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"

// from core.c
SBOLAPIEXPORTS void printSBOLCore();
SBOLAPIEXPORTS void cleanupSBOLCore();

#endif
