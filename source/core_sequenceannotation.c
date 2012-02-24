#include "core_sequenceannotation.h"

void newSequenceAnnotation(const char* id)
{
	SequenceAnnotation annotation = {0,0,0,0,0,0,0};
	annotation.id = new char[ strlen(id) ];
	strcpy(annotation.id, id);
	allAnnotations[ string(id) ] = annotation;
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
		if (!upstream->precedes)
		{
			upstream->precedes = new SequenceAnnotation*[2];
			upstream->precedes[0] = downstream;
			upstream->precedes[1] = 0;
		}
		else
		{
			//int n=0;
			//while (upstream->precedes[n]) ++n;
			int n = upstream->numPrecedes;

			SequenceAnnotation ** p = upstream->precedes;
			upstream->precedes = new SequenceAnnotation*[n+1];
			for (int i=0; i < n-1; ++i)
				upstream->precedes[i] = p[i];
			upstream->precedes[n-1] = downstream;
			upstream->precedes[n] = 0;
		}
		upstream->numPrecedes++;
	}
}
