%module sbol
%{

#define SWIG_FILE_WITH_INIT

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xmlwriter.h>

#include "array.h"
#include "collection.h"
#include "constants.h"
#include "dnacomponent.h"
#include "dnasequence.h"
#include "object.h"
#include "property.h"
#include "reader.h"
#include "sequenceannotation.h"
#include "utilities.h"
#include "validator.h"
#include "writer.h"
#include "sbol.h"

%}

%include "array.h"
%include "collection.h"
%include "constants.h"
%include "dnacomponent.h"
%include "dnasequence.h"
%include "object.h"
%include "property.h"
%include "reader.h"
%include "sequenceannotation.h"
%include "utilities.h"
%include "validator.h"
%include "writer.h"
%include "sbol.h"
