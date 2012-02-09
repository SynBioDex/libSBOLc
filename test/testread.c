#include "../src/reader.h"

void parse(char* examplepath)
{
	int i, j, k, n, m;
	DNAComponent comp;

	readSBOL(examplepath);

	n = getNumDNAComponents();
	for (i=0; i < n; ++i)
	{
		comp = getNthDNAComponent(i);
		printf("component id = %s\n", comp.id);
		printf("      num. collections = %i\n", getNumCollectionsFor(comp));
		for (k=0; k < getNumCollectionsFor(comp); ++k)
		{
			printf("         collection = %s\n", getNthCollectionFor(comp,k).id);
		}
		printf("      num. annotations = %i\n", getNumSequenceAnnotationsIn(comp));
		if (getNumSequenceAnnotationsIn(comp) > 0)
		{
			m = getNumSequenceAnnotationsIn(comp);
			for (j=0; j < m; ++j)
			{
				SequenceAnnotation annotation = getNthSequenceAnnotationIn(comp, j);
				printf("         subComponent %s\n", annotation.subComponent->id);
				for (k=0; k < getNumPrecedes(annotation); ++k)
					printf("            precedes %s\n", getNthPrecedes(annotation, k).id);
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
    printf("parsing %s\n\n", example);
    parse(example);
    return 0;
}
