#include <string.h>
#include <raptor.h>
#include "core.h"
#include "reader.h"

// TODO will this sequential read miss things declared in certain orders?

int sameString(char* string1, char* string2) {
	if (!string1 || !string2)
		return 0;
	else
		return (int) strcmp(string1, string2) == 0;
}

void createNewObject(char* id, char* type) {
	if (!id || !type)
		return;
	else if (sameString(type, "DNASequence"))
		createDNASequence(id);
	else if (sameString(type, "DNAComponent"))
		createDNAComponent(id);
	else if (sameString(type, "SequenceAnnotation"))
		createSequenceAnnotation(id);
	else if (sameString(type, "Collection"))
		createCollection(id);
}

void addToDNASequence(char* id, char* field, char* value) {
	if (!id || !field || !value)
		return;
	DNASequence* seq = getDNASequence(id);
	if (sameString(field, "nucleotides"))
		setNucleotides(seq, value);
}

void addToDNAComponent(char* id, char* field, char* value) {
	if (!id || !field || !value)
		return;
	DNAComponent* com = getDNAComponent(id);
	if (sameString(field, "name"))
		setDNAComponentName(com, value);
	else if (sameString(field, "description"))
		setDNAComponentDescription(com, value);
	else if (sameString(field, "collection")) {
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
	if (sameString(field, "name"))
		setCollectionName(col, value);
	else if (sameString(field, "description"))
		setCollectionDescription(col, value);
}

void addToSequenceAnnotation(char* id, char* field, char* value) {
	if (!id || !field || !value)
		return;
	SequenceAnnotation* ann = getSequenceAnnotation(id);
	DNAComponent* com;
	if (sameString(field, "annotates") || sameString(field, "subComponent")) {
		if (!isDNAComponentID(value))
			com = createDNAComponent(value);
		else
			com = getDNAComponent(value);
	}
	if (sameString(field, "annotates"))
		addSequenceAnnotation(com, ann);
	else if (sameString(field, "subComponent"))
		setSubComponent(ann, com);
	else if (sameString(field, "precedes")) {
		SequenceAnnotation* ann2;
		if (!isSequenceAnnotationID(value))
			ann2 = createSequenceAnnotation(value);
		else
			ann2 = getSequenceAnnotation(value);
		addPrecedesRelationship(ann, ann2);
	}
	else if (sameString(field, "bioStart"))
		setBioStart(ann, atoi(value));
	else if (sameString(field, "bioEnd"))
		setBioEnd(ann, atoi(value));
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
	
	// adjust SBOL core to match
	if (sameString(p, "a")) //TODO or p == rdf:type?
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

char* getExtension(char* filename) {
	if (!filename)
		return NULL;
	int i;
	int len;
	char* ext;
	// determine index of dot
	len = strlen(filename);
	for (i=len-1; i>=0; i--) {
		if (filename[i] == '.') {
			i++; // don't include the dot itself
			break;
		}
	}
	if (i==0)
		return NULL;
	// return chars after dot
	// TODO is returning part of the same string dangerous?
	return &filename[i];
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
	// TODO have raptor guess this
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
