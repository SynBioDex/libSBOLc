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
	
	printf("%s %s %s\n", s, p, o);

	// predicate is rdf:type,
	// so a new structure needs to be created
	if (strcmp(p, "a") == 0) //TODO or p == rdf:type?
	{
	    printf("\tfound new subject\n");
		if (strcmp(o, "DNAComponent") == 0)
		{
			printf("\tcreating new component %s\n", s);
			newComponent(s);
	    }
		else if (strcmp(o, "SequenceAnnotation") == 0)
		{
			printf("\tcreating new annotation %s\n", s);
			newSequenceAnnotation(s);
		}
		else if (strcmp(o, "Collection") == 0)
		{
			printf("\tcreating new collection %s\n", s);
			newCollection(s);
		}
		else
			printf("ignoring unknown object %s\n", o);
	}

	// subject is an existing DNAComponent
	else if (isComponent(s))
	{
	    printf("\tfound new info about component %s\n", s);
		DNAComponent com = getComponent(s);

		if (strcmp(p, "name") == 0)
		{
			printf("\tsetting %s.name to %s\n", com.id, o);
			setComponentName(&com, o);
	    }
		else if (strcmp(p, "description") == 0)
		{
			printf("\tsetting %s.description to %s\n", com.id, o);
			setComponentDescription(&com, o);
		}
		else if (strcmp(p, "collection") == 0)
		{
			if (isComponent(s) && isCollection(o) > 0)
			{
				printf("adding %s to %s\n", s, o);
				Collection col = getCollection(o);
				addComponentToCollection(&com, &col);
			}
		}
		else
			printf("ignoring unknown predicate %s\n", o);
	}

	// subject is an existing Collection
	else if (isCollection(s))
	{
	    printf("\tfound new info about collection %s\n", s);
		Collection col = getCollection(s);

		if (strcmp(p, "name") == 0)
		{
			printf("\tsetting %s.name to %s\n", col.id, o);
			setCollectionName(&col, o);
		}
		else if (strcmp(p, "description") == 0)
		{
			printf("\tsetting %s.description to %s\n", col.id, o);
			setCollectionDescription(&col, o);
		}
		else
			printf("\tignoring unknown predicate %s\n", p);
	}

	// subject is an existing SequenceAnnotation
	else if (isAnnotation(s))
	{
	    printf("\tfound new info about annotation %s\n", s);
		SequenceAnnotation ann = getSequenceAnnotation(s);

		if (strcmp(p, "annotates") == 0)
		{
		    printf("\t%s annotates %s\n", ann.id, o);
			if (isComponent(o))
			{
			    printf("\tsetting %s.annotates %s\n", ann.id, o);
				DNAComponent com = getComponent(o);
				addSequenceAnnotation(&com, &ann);
			}
			else
			    printf("\tignoring annotation of nonexistent object %s\n", o);
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
