#ifndef SBOL_WRITER
#define SBOL_WRITER
#include "api.h"

struct _DNASequence;
struct _DNAComponent;
struct _Collection;

void indentMore();
void indentLess();

void createSBOLWriter(const char* filename);
void deleteSBOLWriter();

void startSBOLDocument(const char* filename);
void endSBOLDocument();

void writeDNASequence(const struct _DNASequence* seq, int includeContents);
void writeDNAComponent(const struct _DNAComponent* com, int includeContents);
void writeCollection(const struct _Collection* col, int includeContents);

SBOLAPIEXPORTS void writeSBOLCore(const char* filename);

#endif
