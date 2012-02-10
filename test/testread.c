#include "../src/reader.h"

void parse(char* examplepath)
{
	int i, j, k;
	DNAComponent comp;

	readSBOL(examplepath);

	for (i=0; i < getNumDNAComponents(); ++i)
	{
		comp = getNthDNAComponent(i);
		printf("component id = %s\n", comp.id);
		printf("\tnum. collections = %i\n", getNumCollectionsFor(comp));
		for (k=0; k < getNumCollectionsFor(comp); ++k)
		{
			printf("\tcollection = %s\n", getNthCollectionFor(comp,k).id);
		}
		printf("\tnum. annotations = %i\n", getNumSequenceAnnotationsIn(comp));
		if (getNumSequenceAnnotationsIn(comp) > 0)
		{
			for (j=0; j < getNumSequenceAnnotationsIn(comp); ++j)
			{
				SequenceAnnotation annotation = getNthSequenceAnnotationIn(comp, j);
				printf("\tsubComponent %s\n", annotation.subComponent->id);
				for (k=0; k < getNumPrecedes(annotation); ++k)
					printf("\tprecedes %s\n", getNthPrecedes(annotation, k).id);
			}
		}
		printf("\n");
	}

	cleanup();
}

int main(int argc, char** argv) {
	char* example;
	if( argc < 2 )
		example = "../examples/example.nt";
	else
		example = argv[1];
	printf("parsing %s\n", example);
	parse(example);
	return 0;
}
