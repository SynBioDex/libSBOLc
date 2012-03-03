#ifndef SBOL_CORE_PROPERTY
#define SBOL_CORE_PROPERTY

typedef struct _Property {
    char* data;
} Property;

Property* createProperty();
void deleteProperty(Property* pro);
// TODO compare to other property rather than string?
int compareProperty(const Property* pro, const char* value);
char* getProperty(const Property* pro);
void setProperty(Property* pro, const char* value);
void printProperty(const Property* pro);

#endif
