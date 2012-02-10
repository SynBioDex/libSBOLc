#include <string.h>
#include "core.h"
#include "raptor.h" //RDF parser

// analyze a single triple and add to
// SBOL data structures if appropriate
static void read_triple(void* user_data, raptor_statement* triple)
{
	char* s;
	char* p;
	char* o;
	
	// read subject
	if (triple->subject->type == RAPTOR_TERM_TYPE_URI)
		s = (char*)(raptor_uri_as_string(triple->subject->value.uri));
	else if (triple->subject->type == RAPTOR_TERM_TYPE_LITERAL)
		s = (char*)(triple->subject->value.literal.string);
	else
		printf("  subject not URI or literal\n");
	
	// read predicate
	if (triple->predicate->type == RAPTOR_TERM_TYPE_URI)
		p = (char*)(raptor_uri_as_string(triple->predicate->value.uri));
	else if (triple->predicate->type == RAPTOR_TERM_TYPE_LITERAL)
		p = (char*)(triple->predicate->value.literal.string);
	else
		printf("  predicate not URI or literal\n");
		
	// read object
	if (triple->object->type == RAPTOR_TERM_TYPE_URI)
		o = (char*)(raptor_uri_as_string(triple->object->value.uri));
	else if (triple->object->type == RAPTOR_TERM_TYPE_LITERAL)
		o = (char*)(triple->object->value.literal.string);
	else
		printf("  object not URI or literal\n");
	
	//printf("%s %s %s\n", s, p, o);

	// predicate is rdf:type,
	// so a new structure needs to be created
	if (strcmp(p, "a") == 0) //TODO or p == rdf:type?
	{
		if (strcmp(o, "DNAComponent") == 0)
			newComponent(s);
		else if (strcmp(o, "SequenceAnnotation") == 0)
			newSequenceAnnotation(s);
		else if (strcmp(o, "Collection") == 0)
			newCollection(s);
		else
			// not part of SBOL core
			printf("ignoring unknown type %s\n", o);
	}

	// subject is an existing DNAComponent
	else if (isComponent(s))
	{
		//printf("found info: %s %s %s\n", s, p, o);
		DNAComponent com = getComponent(s);

		if (strcmp(p, "name") == 0)
			setComponentName(&com, o);
		else if (strcmp(p, "description") == 0)
			setComponentDescription(&com, o);
		else if (strcmp(p, "collection") == 0)
		{
			if (isComponent(s) && isCollection(o) > 0)
			{
				//printf("adding %s to %s\n", s, o);
				Collection col = getCollection(o);
				//printf("start with %d collections\n", getNumCollectionsFor(com));
				addComponentToCollection(&com, &col);
				//printf("end with %d collections\n", getNumCollectionsFor(com));
			}
		}
		// else not part of SBOL core
	}

	// subject is an existing Collection
	else if (isCollection(s))
	{
		Collection col = getCollection(s);

		if (strcmp(p, "name") == 0)
			setCollectionName(&col, o);
		else if (strcmp(p, "description") == 0)
			setCollectionDescription(&col, o);
		// else not part of SBOL core
	}

	// subject is an existing SequenceAnnotation
	else if (isAnnotation(s))
	{
		SequenceAnnotation ann = getSequenceAnnotation(s);

		if (strcmp(p, "annotates") == 0)
		{
			if (isComponent(o))
			{
				DNAComponent com = getComponent(o);
				addSequenceAnnotation(&com, &ann);
			}
		}
		else if (strcmp(p, "subComponent") == 0)
		{
			if (isComponent(o))
			{
				DNAComponent com = getComponent(o);
				setSubComponent(&ann, &com);
			}
		}
		else if (strcmp(p, "precedes") == 0)
		{
			if (isAnnotation(o))
			{
				SequenceAnnotation ann2 = getSequenceAnnotation(o);
				addPrecedesRelationship(&ann, &ann2);
			}
		}
		// else not part of SBOL core
	}
	
	// else not part of SBOL core
}

// import from an RDF file using raptor
void readSBOL(char* filename)
{
	//printf("starting readSBOL\n");
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
	//printf("done with readSBOL\n");
}
