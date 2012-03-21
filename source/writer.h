#ifndef SBOL_WRITER_HEADER
#define SBOL_WRITER_HEADER
#include <libxml/xmlwriter.h>
#include "sbol.h"

/************************
 * set up SBOL document
 ************************/

void indentMore();
void indentLess();

void createSBOLWriter();
void cleanupSBOLWriter();

void startSBOLDocument();
void endSBOLDocument();

int saveSBOLDocument(const char* filename);

/***********************
 * serialize SBOL core
 ***********************/

void writeDNASequence(DNASequence* seq);
void writeDNAComponent(DNAComponent* com);
void writeCollection(Collection* col);

/***********************
 * main write function
 ***********************/

SBOLAPIEXPORTS int writeSBOLCore(const char* filename);

#endif
