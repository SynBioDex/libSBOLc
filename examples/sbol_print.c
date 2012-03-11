#include <stdio.h>
#include <raptor.h>
#include <string.h>
#include "../source/utilities.h"

/**************************************************
 * this should work for any non-SBOL RDF file too
 **************************************************/

static void print_triple(void* user_data, raptor_statement* triple) {
  raptor_statement_print_as_ntriples(triple, stdout);
  fputc('\n', stdout);
}

int main (int argc, char *argv[]) {
  raptor_world*  world = raptor_new_world();
  raptor_parser* rdf_parser = raptor_new_parser(world, "guess");

  unsigned char* uri_string = raptor_uri_filename_to_uri_string(argv[1]);
  printf("\nprinting %s\n", uri_string);
  raptor_uri* uri = raptor_new_uri(world, uri_string);	

  raptor_parser_set_statement_handler(rdf_parser, NULL, print_triple);
  raptor_parser_parse_file(rdf_parser, uri, NULL);
  printf("\n");

  raptor_free_parser(rdf_parser);
  raptor_free_uri(uri);
  raptor_free_memory(uri_string);
  raptor_free_world(world);
  return 0;
}
