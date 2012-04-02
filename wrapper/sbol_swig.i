%module sbol_swig
%{
	#define SWIG_FILE_WITH_INIT

	#include <libxml/xmlmemory.h>
	#include <libxml/parser.h>
	#include <libxml/xpath.h>
	#include <libxml/xmlwriter.h>
	
	#include "constants.h"
	#include "prototypes.h"
	#include "array.h"
	#include "utilities.h"
	#include "collection.h"
	#include "dnacomponent.h"
	#include "dnasequence.h"
	#include "object.h"
	#include "property.h"
	#include "reader.h"
	#include "sequenceannotation.h"
	#include "validator.h"
	#include "writer.h"
	#include "sbol.h"
%}

// files in which every function can be included
%include "constants.h"
%include "utilities.h"
%include "object.h"
%include "dnasequence.h"
%include "sequenceannotation.h"
%include "dnacomponent.h"
%include "collection.h"
%include "sbol.h"

// functions from libxml
void xmlFree(xmlChar* str);
void xmlFreeDoc(xmlDoc* doc); /// @todo remove?
void xmlCleanupParser(); /// @todo remove?

// functions from files that can't be completely included
int isValidSBOL(const xmlDocPtr doc);
void readSBOLCore(char* filename);
int writeSBOLCore(const char* filename);
