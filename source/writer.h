///////////////////////////////////////////////////////////
/// @file writer.h
/// This file contains functions for writing the SBOL core
/// to an XML file. Only writeSBOLCore is meant to be
/// exported; everything else supports it.
///////////////////////////////////////////////////////////

#ifndef SBOL_WRITER_HEADER
#define SBOL_WRITER_HEADER
#include <libxml/xmlwriter.h>

// forward declarations
struct _DNASequence;
struct _DNAComponent;
struct _Collection;

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

void writeDNASequence(struct _DNASequence* seq);
void writeDNAComponent(struct _DNAComponent* com);
void writeCollection(struct _Collection* col);

/***********************
 * main write function
 ***********************/

int writeSBOLCore(const char* filename);

#endif
