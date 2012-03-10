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

  // choose parse format
  char* ext = getExtension(argv[1]);
  raptor_parser* rdf_parser;
  if (strcmp(ext, "nt") == 0)
    rdf_parser = raptor_new_parser(world, "ntriples");
  else {
    if (strcmp(ext, "xml") != 0)
      printf("WARNING: Unrecognized extension '%s'. Parsing as rdfxml.\n", ext);
    rdf_parser = raptor_new_parser(world, "rdfxml");
  }

  unsigned char* uri_string = raptor_uri_filename_to_uri_string(argv[1]);
  raptor_uri* uri           = raptor_new_uri(world, uri_string);
  raptor_uri* base_uri      = raptor_uri_copy(uri);

  raptor_parser_set_statement_handler(rdf_parser, NULL, print_triple);
  raptor_parser_parse_file(rdf_parser, uri, base_uri);

  raptor_free_parser(rdf_parser);
  raptor_free_uri(base_uri);
  raptor_free_uri(uri);
  raptor_free_memory(uri_string);
  raptor_free_world(world);
  return 0;
}
