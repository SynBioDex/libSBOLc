#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <hash_map>

extern "C"
{
	#include "raptor.h"
}

using namespace std;

/**************************************
   A set of global vectors are used to store
   all the SBOL objects
****************************************/

hash_map<string, DNAComponent> allComponents;

/************************************************
       just a couple of neccesary functions
*************************************************/

void cleanup()
{
	
}

int string_equal(const char* s1, const char* s2)
{
	return (strcmp(s1,s2) == 0);
}

/************************************************
    This is where the real SBOL stuff happens
*************************************************/

//read RDF file
static void read_triple(void* user_data, raptor_statement* triple) 
{
	char * s;
	char * p;
	char * o;
	if (triple->subject->type == RAPTOR_TERM_TYPE_URI)
		s = ((char*)(raptor_uri_as_string(triple->subject->value.uri)));
	else
	if (triple->subject->type == RAPTOR_TERM_TYPE_LITERAL)
		s = ((char*)(triple->subject->value.literal.string));

	if (triple->predicate->type == RAPTOR_TERM_TYPE_URI)
		p = ((char*)(raptor_uri_as_string(triple->predicate->value.uri)));
	else
	if (triple->predicate->type == RAPTOR_TERM_TYPE_LITERAL)
		p = ((char*)(triple->predicate->value.literal.string));

	if (triple->object->type == RAPTOR_TERM_TYPE_URI)
		o = ((char*)(raptor_uri_as_string(triple->object->value.uri)));
	else
	if (triple->object->type == RAPTOR_TERM_TYPE_LITERAL)
		o = ((char*)(triple->object->value.literal.string));
		
	if (string_equal(s,""))
	{
	}
}

