#ifndef SBOL_WRITER
#define SBOL_WRITER
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

struct _DNASequence;
struct _DNAComponent;
struct _Collection;

void writeDNASequence(struct _DNASequence* seq);
void writeDNAComponent(struct _DNAComponent* com);
void writeCollection(struct _Collection* col);

/***********************
 * main write function
 ***********************/

SBOLAPIEXPORTS int writeSBOLCore(const char* filename);

#endif
