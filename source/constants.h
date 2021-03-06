///////////////////////////////////////////////////////////
/// @file constants.h.in
/// Central location for defining constants related to
/// SBOL. Used by CMake to generate constants.h
/// 
/// @todo bring up "dnaSequence" vs "DnaSequence"
/// @todo and "component" vs "DnaComponent"
///////////////////////////////////////////////////////////

#ifndef SBOL_TYPES_HEADER
#define SBOL_TYPES_HEADER

/* #undef SBOL_DEBUG_STATEMENTS */

// folder structure
// set using CMake
#define SBOL_SOURCE_DIR  "C:/Users/user/Dev/libSBOLc_v1/libSBOLc/source"  ///< Holds source code for libSBOLc.
#define SBOL_ROOT_DIR    "C:/Users/user/Dev/libSBOLc_v1/libSBOLc"    ///< Top-level project folder.
#define SBOL_BUILD_DIR   "C:/Users/user/Dev/libSBOLc_v1/libSBOLc/build"   ///< Folder for temporary build files.
#define SBOL_SCHEMA_DIR  "C:/Users/user/Dev/libSBOLc_v1/libSBOLc/schema"  ///< Holds the SBOL schema files.
#define SBOL_TEST_DIR    "C:/Users/user/Dev/libSBOLc_v1/libSBOLc/tests"    ///< Holds source code for the tests.
#define SBOL_EXAMPLE_DIR "C:/Users/user/Dev/libSBOLc_v1/libSBOLc/examples" ///< Holds example SBOL documents and code.
#define SBOL_RELEASE_DIR "C:/Users/user/Dev/libSBOLc_v1/libSBOLc/release" ///< Folder for generated binaries, docs, etc.
#define SBOL_MANUAL_DIR  "C:/Users/user/Dev/libSBOLc_v1/libSBOLc/manual"  ///< Holds source code for the SBOL manual.

#define SBOL_SCHEMA_FILENAME SBOL_SCHEMA_DIR "/sbol.xsd" ///< Schema to use when validating documents.

/// Macro for exporting functions from the shared library.
/// @todo Move this to another file?
/// @todo Does the STATIC_LINKED part add anything?
#ifndef SBOLAPIEXPORTS
#	if defined(SWIG) || defined(STATIC_LINKED)
#		define SBOLAPIEXPORTS
#	elif defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#       if defined(USE_STDCALL)
#           define SBOLAPIEXPORTS __stdcall __declspec(dllexport)
#       else
#	    	define SBOLAPIEXPORTS __declspec(dllexport)
#       endif
#	elif defined(__GNUC__) && __GNUC__ >= 4
#		define SBOLAPIEXPORTS __attribute__ ((visibility("default")))
#	else
#		define SBOLAPIEXPORTS
#	endif
#endif

/// Lists possible values of a PolarityProperty.
/// @todo rename to StrandOrientation?
/// @todo Is bidirectional in the SBOL spec so far?
/// @todo why is each entry listed twice in Doxygen?
enum StrandPolarity {
	STRAND_FORWARD,
	STRAND_BIDIRECTIONAL,
	STRAND_REVERSE
};

// xml namespace urls
#define NSURL_RDF  "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
#define NSURL_RDFS "http://www.w3.org/2000/01/rdf-schema#"
#define NSURL_SO   "http://purl.obolibrary.org/obo/"
#define NSURL_SBOL "http://sbols.org/v1#"

// xml namespace prefixes
#define NSPREFIX_RDF  "rdf"
#define NSPREFIX_RDFS "rdfs"
#define NSPREFIX_SO   "so"
#define NSPREFIX_SBOL "s"

// nodes defined in SBOL
#define NODENAME_DNASEQUENCE        "DnaSequence" ///< Gotcha: uppercase D
#define NODENAME_DNASEQUENCE_REF    "dnaSequence" ///< Gotcha: lowercase d
#define NODENAME_SEQUENCEANNOTATION "SequenceAnnotation"
#define NODENAME_DNACOMPONENT       "DnaComponent"
#define NODENAME_COMPONENT          "component"
#define NODENAME_COLLECTION         "Collection"
#define NODENAME_DISPLAYID          "displayId" ///< Gotcha: lowercase d
#define NODENAME_NAME               "name"
#define NODENAME_DESCRIPTION        "description"
#define NODENAME_BIOSTART           "bioStart"
#define NODENAME_BIOEND             "bioEnd"
#define NODENAME_NUCLEOTIDES        "nucleotides"
#define NODENAME_STRAND             "strand"
#define NODENAME_TYPE               "type"
#define NODENAME_PRECEDES           "precedes"
#define NODENAME_ANNOTATION         "annotation"
#define NODENAME_SUBCOMPONENT       "subComponent"

// rdf nodes used in SBOL
#define NODENAME_RDF      "RDF"
#define NODENAME_ABOUT    "about"    ///< URI of a node representing an SBOLObject.
#define NODENAME_RESOURCE "resource" ///< URI of a node referencing an SBOLObject somewhere else.

#endif
