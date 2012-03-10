#include <string.h>
#include <raptor.h>
#include "core.h"
#include "reader.h"
#include "types.h"
#include "utilities.h"

// TODO will this sequential read miss things declared in certain orders?

void createNewObject(char* id, char* type) {
	if (!id || !type)
		return;
	else if (sameString(type, SBOL_DNASEQUENCE))
		createDNASequence(id);
	else if (sameString(type, SBOL_DNACOMPONENT))
		createDNAComponent(id);
	else if (sameString(type, SBOL_SEQUENCEANNOTATION))
		createSequenceAnnotation(id);
	else if (sameString(type, SBOL_COLLECTION))
		createCollection(id);
}

void addToDNASequence(char* id, char* field, char* value) {
	if (!id || !field || !value)
		return;
	DNASequence* seq = getDNASequence(id);
	if (sameString(field, SBOL_NUCLEOTIDES))
		setNucleotides(seq, value);
}

void addToDNAComponent(char* id, char* field, char* value) {
	if (!id || !field || !value)
		return;
	DNAComponent* com = getDNAComponent(id);
	if (sameString(field, SBOL_NAME))
		setDNAComponentName(com, value);
	else if (sameString(field, SBOL_DESCRIPTION))
		setDNAComponentDescription(com, value);
	else if (sameString(field, SBOL_COLLECTION)) {
		Collection* col;
		if (isCollectionID(value)) // something about > 0?
			col = getCollection(value);
		else
			col = createCollection(value);
		addDNAComponentToCollection(com, col);
	}
}

void addToCollection(char* id, char* field, char* value) {
	if (!id || !field || !value)
		return;
	Collection* col = getCollection(id);
	if (sameString(field, SBOL_NAME))
		setCollectionName(col, value);
	else if (sameString(field, SBOL_DESCRIPTION))
		setCollectionDescription(col, value);
}

void addToSequenceAnnotation(char* id, char* field, char* value) {
	if (!id || !field || !value)
		return;
	SequenceAnnotation* ann = getSequenceAnnotation(id);
	DNAComponent* com;
	if (sameString(field, SBOL_ANNOTATES) || sameString(field, SBOL_SUBCOMPONENT)) {
		if (!isDNAComponentID(value))
			com = createDNAComponent(value);
		else
			com = getDNAComponent(value);
	}
	if (sameString(field, SBOL_ANNOTATES))
		addSequenceAnnotation(com, ann);
	else if (sameString(field, SBOL_SUBCOMPONENT))
		setSubComponent(ann, com);
	else if (sameString(field, SBOL_PRECEDES)) {
		SequenceAnnotation* ann2;
		if (!isSequenceAnnotationID(value))
			ann2 = createSequenceAnnotation(value);
		else
			ann2 = getSequenceAnnotation(value);
		addPrecedesRelationship(ann, ann2);
	}
	else if (sameString(field, SBOL_BIOSTART))
		setBioStart(ann, atoi(value));
	else if (sameString(field, SBOL_BIOEND))
		setBioEnd(ann, atoi(value));
}

static void print_triple(raptor_statement* triple) {
  raptor_statement_print_as_ntriples(triple, stdout);
  fputc('\n', stdout);
}

// analyze a single triple and add to
// SBOL data structures if appropriate
void read_triple(void* user_data, raptor_statement* triple) {
	char* s;
	char* p;
	char* o;
	
	// read subject
	if (triple->subject->type == RAPTOR_TERM_TYPE_URI)
		s = (char*)(raptor_uri_as_string(triple->subject->value.uri));
	else if (triple->subject->type == RAPTOR_TERM_TYPE_LITERAL)
		s = (char*)(triple->subject->value.literal.string);
	
	// read predicate
	if (triple->predicate->type == RAPTOR_TERM_TYPE_URI)
		p = (char*)(raptor_uri_as_string(triple->predicate->value.uri));
	else if (triple->predicate->type == RAPTOR_TERM_TYPE_LITERAL)
		p = (char*)(triple->predicate->value.literal.string);
    
	// read object
	if (triple->object->type == RAPTOR_TERM_TYPE_URI)
		o = (char*)(raptor_uri_as_string(triple->object->value.uri));
	else if (triple->object->type == RAPTOR_TERM_TYPE_LITERAL)
		o = (char*)(triple->object->value.literal.string);

	// for debugging
	//print_triple(triple);
	
	// adjust SBOL core to match
	if (sameString(p, RDF_TYPE))
		createNewObject(s, o);
	else if (isDNASequenceID(s))
		addToDNASequence(s, p, o);
	else if (isDNAComponentID(s))
		addToDNAComponent(s, p, o);
	else if (isCollectionID(s))
		addToCollection(s, p, o);
	else if (isSequenceAnnotationID(s))
		addToSequenceAnnotation(s, p, o);
}

void readSBOLCore(char* filename) {
	if (!filename)
		return;

	// raptor stuff
	// (copied from http://librdf.org/raptor/api/tutorial-parser-example.html)
	raptor_world* world = NULL;
	raptor_parser* rdf_parser = NULL;
	unsigned char *uri_string;
	raptor_uri *uri, *base_uri;
	world = raptor_new_world();
	
	// choose parse format
	char* ext = getExtension(filename);
	if (sameString(ext, "nt"))
		rdf_parser = raptor_new_parser(world, "ntriples");
	else {
		if (!sameString(ext, "xml"))
			printf("WARNING: Unrecognized extension '%s'. Parsing as rdfxml.\n", ext);
		rdf_parser = raptor_new_parser(world, "rdfxml");
	}
	
	// pass each triple to read_triple for analysis
	raptor_parser_set_statement_handler(rdf_parser, NULL, &read_triple);
	
	// more raptor stuff
	uri_string = raptor_uri_filename_to_uri_string(filename);
	uri = raptor_new_uri(world, uri_string);
	base_uri = raptor_uri_copy(uri);
	raptor_parser_parse_file(rdf_parser, uri, base_uri);
	raptor_free_parser(rdf_parser);
	raptor_free_uri(base_uri);
	raptor_free_uri(uri);
	raptor_free_memory(uri_string);
	raptor_free_world(world);
}
