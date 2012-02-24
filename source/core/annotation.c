#include <stdlib.h>
#include <string.h>
#include "annotation.h"
#include "component.h"

void newSequenceAnnotation(const char* id)
{
	SequenceAnnotation annotation = {0,0,0,0,0,0,0};
	annotation.id = (char*)malloc(sizeof(char) * strlen(id)+1);
	strcpy(annotation.id, id);
	//allAnnotations[ string(id) ] = annotation;
}

int getNumPrecedes(SequenceAnnotation annotation)
{
	return annotation.numPrecedes;
}

SequenceAnnotation getNthPrecedes(SequenceAnnotation annotation, int n)
{
	SequenceAnnotation p = {0,0,0,0,0,0,0};
	if (annotation.numPrecedes >= n) //TODO just > ?
		p = *(annotation.precedes[n]);
	return p;
}

void setSequenceAnnotationID(SequenceAnnotation * annotation, const char * id)
{
	if (annotation)
		annotation->id = (char*)id;
}

void addPrecedesRelationship(SequenceAnnotation * upstream, SequenceAnnotation * downstream)
{
	if (upstream && downstream)
	{
	    size_t size;
		if (!upstream->precedes)
		{
			size = sizeof(SequenceAnnotation*) * 2;
			upstream->precedes = (SequenceAnnotation**)malloc(size);
			upstream->precedes[0] = downstream;
			upstream->precedes[1] = 0;
		}
		else
		{
			//int n=0;
			//while (upstream->precedes[n]) ++n;
			int n = upstream->numPrecedes;

			size = sizeof(SequenceAnnotation*) * (n+1);
			SequenceAnnotation ** p = upstream->precedes;
			upstream->precedes = (SequenceAnnotation**)malloc(size);
			int i;
			for( i=0; i<n-1; ++i )
				upstream->precedes[i] = p[i];
			upstream->precedes[n-1] = downstream;
			upstream->precedes[n] = 0;
		}
		upstream->numPrecedes++;
	}
}
