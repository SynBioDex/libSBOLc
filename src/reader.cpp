#include <string.h>
#include <string>  //std string
#include <map>  //std map

//TODO purge this file of C++ strings, maps and just use C

extern "C"
{
	#include "core.h"
	#include "raptor.h"  //RDF parser
}

using namespace std;

// analyze a single triple and add to
// SBOL data structures if appropriate
static void read_triple(void* user_data, raptor_statement* triple)
{
	string s;
	string p;
	string o;
	
	// read subject
	if (triple->subject->type == RAPTOR_TERM_TYPE_URI)
		s = string((char*)(raptor_uri_as_string(triple->subject->value.uri)));
	else
		if (triple->subject->type == RAPTOR_TERM_TYPE_LITERAL)
			s = string((char*)(triple->subject->value.literal.string));
	
	// read predicate
	if (triple->predicate->type == RAPTOR_TERM_TYPE_URI)
		p = string((char*)(raptor_uri_as_string(triple->predicate->value.uri)));
	else
		if (triple->predicate->type == RAPTOR_TERM_TYPE_LITERAL)
			p = string((char*)(triple->predicate->value.literal.string));
	
	// read object
	if (triple->object->type == RAPTOR_TERM_TYPE_URI)
		o = string((char*)(raptor_uri_as_string(triple->object->value.uri)));
	else
		if (triple->object->type == RAPTOR_TERM_TYPE_LITERAL)
			o = string((char*)(triple->object->value.literal.string));
	
	// predicate is rdf:type,
	// so a new structure needs to be created
	if (p == string("a"))
	{
		if (o.compare("DNAComponent") == 0)
		{
			//DNAComponent component = {0,0,0,0,0,0};
			//component.id = new char[s.length()];
			//strcpy(component.id, s.c_str());
			//getComponent(s.c_str()) = component;
			newComponent(s.c_str());
		}
		else
			if (o.compare("SequenceAnnotation") == 0)
			{
				//SequenceAnnotation annotation = {0,0,0,0,0};
				//annotation.id = new char[s.length()];
				//strcpy(annotation.id, s.c_str());
				//getSequenceAnnotation(s.c_str()) = annotation;
                newSequenceAnnotation(s.c_str());
			}
			else
				if (o.compare("Collection") == 0)
				{
					//Collection collection = {0,0,0,0,0};
					//collection.id = new char[s.length()];
					//strcpy(collection.id, s.c_str());
					//allCollections[s] = collection;
                    newCollection(s.c_str());
				}
		// else not part of SBOL core
	}
	else
		
		// subject is an existing DNAComponent
		if (isComponent(s.c_str()))
		{
			if (p.compare("name") == 0)
			{
				getComponent(s.c_str()).name = new char[o.length()];
				strcpy(getComponent(s.c_str()).name,o.c_str());
			}
			else
				if (p.compare("description") == 0)
				{
					getComponent(s.c_str()).description = new char[o.length()];
					strcpy(getComponent(s.c_str()).description,o.c_str());
				}
				else
					if (p.compare("collection") == 0)
					{
						if (isComponent(s.c_str()) && isCollection(o.c_str()) > 0)
						{
							DNAComponent component = getComponent(s.c_str());
							Collection collection = getCollection(o.c_str());
							addComponentToCollection(&component, &collection);
						}
					}
			// else not part of SBOL core
		}
		else

			// subject is an existing Collection
			if (isCollection(s.c_str()))
			{
				if (p.compare("name") == 0)
				{
					getCollection(s.c_str()).name = new char[o.length()];
					strcpy(getCollection(s.c_str()).name,o.c_str());
				}
				else
					if (p.compare("description") == 0)
					{
						getCollection(s.c_str()).description = new char[o.length()];
						strcpy(getCollection(s.c_str()).description,o.c_str());
					}
				// else not part of SBOL core
			}
			else
				
				// subject is an existing SequenceAnnotation
				if (isAnnotation(s.c_str()))
				{
					if (p.compare("annotates") == 0)
					{
						if (isComponent(o.c_str()))
							addSequenceAnnotation(&getComponent(o.c_str()), &getSequenceAnnotation(s.c_str()));
					}
					else
						if (p.compare("subComponent") == 0)
						{
							if (isComponent(o.c_str()))
								setSubComponent(&getSequenceAnnotation(s.c_str()), &getComponent(o.c_str()));
						}
						else
							if (p.compare("precedes") == 0)
							{
								if (isAnnotation(o.c_str()))
									addPrecedesRelationship(&getSequenceAnnotation(s.c_str()), &getSequenceAnnotation(o.c_str()));
							}
					// else not part of SBOL core
				}
	
	// else not part of SBOL core
}

// import from an RDF file using raptor
void readSBOL(char* filename)
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
