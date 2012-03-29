///////////////////////////////////////////////////////////
/// @file types.h
/// This file is a central location for defining constants
/// related to SBOL serialization.
///////////////////////////////////////////////////////////

/// @todo remove "collection"
/// @todo remove 
/// @todo bring up "dnaSequence" vs "DnaSequence"
/// @todo and "component" vs "DnaComponent"

#ifndef SBOL_TYPES_HEADER
#define SBOL_TYPES_HEADER

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
#define NODENAME_DNASEQUENCE        "DnaSequence" ///< gotcha: uppercase D
#define NODENAME_DNASEQUENCE_REF    "dnaSequence" ///< gotcha: lowercase d
#define NODENAME_SEQUENCEANNOTATION "SequenceAnnotation"
#define NODENAME_DNACOMPONENT       "DnaComponent"
#define NODENAME_COMPONENT          "component"
#define NODENAME_COLLECTION         "Collection"
#define NODENAME_COLLECTION_REF     "collection" ///< @todo remove
#define NODENAME_DISPLAYID          "displayId" ///< gotcha: lowercase d
#define NODENAME_NAME               "name"
#define NODENAME_DESCRIPTION        "description"
#define NODENAME_BIOSTART           "bioStart"
#define NODENAME_BIOEND             "bioEnd"
#define NODENAME_NUCLEOTIDES        "nucleotides"
#define NODENAME_STRAND             "strand"
#define NODENAME_PRECEDES           "precedes"
#define NODENAME_ANNOTATION         "annotation"
#define NODENAME_SUBCOMPONENT       "subComponent"

// rdf nodes used in SBOL
#define NODENAME_RDF      "RDF"
#define NODENAME_ABOUT    "about"
#define NODENAME_RESOURCE "resource"

#endif
