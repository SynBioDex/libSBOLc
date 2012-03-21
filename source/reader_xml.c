#include "sbol.h"

void readDNASequence();
void readSequenceAnnotation();
void readDNAComponent();
void readCollection();

// make a first pass through
// to create the SBOL objects
void readSBOLObjects();

// go back and link up the objects 
// according to rdf:resource nodes
void readSBOLPointers();

void readSBOLCore(char* filename);
