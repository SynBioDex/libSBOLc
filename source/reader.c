#include <string.h>
#include <raptor.h>
#include "core.h"
#include "reader.h"

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
	
	// predicate is rdf:type,
	// so a new structure needs to be created
	if (strcmp(p, "a") == 0) //TODO or p == rdf:type?
	{
		if (strcmp(o, "DNASequence") == 0)
			createDNASequence(s);
		else 
		if (strcmp(o, "DNAComponent") == 0)
			createDNAComponent(s);
		else if (strcmp(o, "SequenceAnnotation") == 0)
			createSequenceAnnotation(s);
		else if (strcmp(o, "Collection") == 0)
			createCollection(s);
	}

	// subject is an existing DNASequence
	else if (isDNASequenceID(s)) {
		DNASequence* seq = getDNASequence(s);
		if (strcmp(p, "nucleotides") == 0)
			setNucleotides(seq, o);
	}

	// subject is an existing DNAComponent
	else if (isDNAComponentID(s))
	{
		DNAComponent* com = getDNAComponent(s);

		if (strcmp(p, "name") == 0)
			setDNAComponentName(com, o);
		else if (strcmp(p, "description") == 0)
			setDNAComponentDescription(com, o);
		else if (strcmp(p, "collection") == 0) {
			if (isDNAComponentID(s) && isCollectionID(o) > 0)
			{
				Collection* col = getCollection(o);
				addDNAComponentToCollection(com, col);
			}
		}
	}

	// subject is an existing Collection
	else if (isCollectionID(s)) {
		Collection* col = getCollection(s);

		if (strcmp(p, "name") == 0)
			setCollectionName(col, o);
		else if (strcmp(p, "description") == 0)
			setCollectionDescription(col, o);
	}

	// subject is an existing SequenceAnnotation
	else if (isSequenceAnnotationID(s)) {
		SequenceAnnotation* ann = getSequenceAnnotation(s);

		if (strcmp(p, "annotates") == 0) {
			if (isDNAComponentID(o)) {
				DNAComponent* com = getDNAComponent(o);
				addSequenceAnnotation(com, ann);
			}
		} else if (strcmp(p, "subComponent") == 0) {
			if (isDNAComponentID(o)) {
				DNAComponent* com = getDNAComponent(o);
				setSubComponent(ann, com);
			}
		} else if (strcmp(p, "precedes") == 0) {
			if (isSequenceAnnotationID(o)) {
				SequenceAnnotation* ann2 = getSequenceAnnotation(o);
				addPrecedesRelationship(ann, ann2);
			}
		}
	}
}

// import from an RDF file using raptor
void readSBOLCore(char* filename)
{
	const char * format = "ntriples"; // TODO other formats?
	raptor_world *world = NULL;
	raptor_parser* rdf_parser = NULL;
	unsigned char *uri_string;
	raptor_uri *uri, *base_uri;
	world = raptor_new_world();
	rdf_parser = raptor_new_parser(world, format);
	
	// pass each triple to read_triple for analysis
	raptor_parser_set_statement_handler(rdf_parser, NULL, &read_triple);
	
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
