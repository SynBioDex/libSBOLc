#include <stdio.h>
#include "core.h"

void cleanupSBOLCore() {
	cleanupDNASequences();
	cleanupSequenceAnnotations();
	cleanupDNAComponents();
	cleanupCollections();
}

// TODO put this somewhere better
void indent(int tabs) {
    if (tabs<0)
        tabs = 0;
    int i;
    for (i=0; i<tabs; i++)
        printf("\t");
}

void printSBOLCore() {
    printAllDNASequences();
    printAllSequenceAnnotations();
    printAllDNAComponents();
    printAllCollections();
}
