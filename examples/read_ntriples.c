#include <stdio.h>
#include "core.h"
#include "reader.h"

// TODO add the print functions to the core for debugging

void printIndent(int tabs) {
	int i;
	for (i=0; i<tabs; i++)
		printf("\t");
}

void printCollection(Collection* col, int indent) {
	char* id = col->id;
	printIndent(indent); printf("collection = %s\n", id);
}

void printSequenceAnnotation(SequenceAnnotation* ann, int indent) {
	printIndent(indent); printf("annotation = %s\n", ann->id);
	printIndent(indent+1); printf("subComponent = %s\n", ann->subComponent->id);
	int num = getNumPrecedes(ann);
	int i;
	char* id;
	for (i=0; i<num; i++) {
		id = getNthPrecedes(ann, i)->id;
		printIndent(indent+1); printf("precedes %s\n", id);
	}
}

void printDNAComponent(DNAComponent* com, int indent) {
	char* id = com->id;
	int collections = getNumCollectionsFor(com);
	int annotations = getNumSequenceAnnotationsIn(com);
	printIndent(indent); printf("%s\n", id);
	printIndent(indent+1); printf("collections: %i\n", collections);
	printIndent(indent+1); printf("annotations: %i\n", annotations);
	int i;
	for (i=0; i<collections; i++) {
		Collection* col = getNthCollectionFor(com, i);
		printCollection(col, indent+2);
	}
	for (i=0; i<annotations; i++) {
		SequenceAnnotation* ann = getNthSequenceAnnotationIn(com, i);
		printSequenceAnnotation(ann, indent+2);
	}
}

void parseAndPrint(char* filename) {
	readSBOL(filename); // does all the actual parsing
	DNAComponent* com;
	printf("components: %i\n", getNumDNAComponents());
	int i;
	for (i=0; i < getNumDNAComponents(); i++) {
		com = getNthDNAComponent(i);
		printDNAComponent(com, 0);
		printf("\n");
	}
	cleanup();
}

int main(int argc, char** argv) {
	char* example;
	if( argc < 2 )
		// TODO fill in using CMake?
		example = "../examples/valid/ntriples.nt";
	else
		example = argv[1];
	parseAndPrint(example);
	return 0;
}
