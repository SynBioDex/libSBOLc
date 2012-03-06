#ifndef SBOL_WRITER
#define SBOL_WRITER
#include "api.h"

void indentMore();
void indentLess();

void createSBOLWriter(const char* filename);
void deleteSBOLWriter();

void startSBOLDocument(const char* filename);
void endSBOLDocument();

void writeDNASequence(const DNASequence* seq);
void writeDNAComponent(const DNAComponent* com, int includeContents);
void writeCollection(const Collection* col);

SBOLAPIEXPORTS void writeSBOLCore(const char* filename);

#endif
