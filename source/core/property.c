#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "property.h"

Property* createProperty() {
    Property* pro = malloc(sizeof(Property));
    pro->data = NULL;
    return pro;
}

void deleteProperty(Property* pro) {
    if (pro) {
        if (pro->data)
            free(pro->data);
        free(pro);
    }
}

int compareProperty(const Property* pro, const char* value) {
    if (!pro || !pro->data || !value)
        // TODO is this a good error value for strcmp?
        return -1;
    return strcmp(pro->data, value);
}

char* getProperty(const Property* pro) {
    if (!pro || !pro->data)
        return NULL;
    char* output = malloc(sizeof(char) * strlen(pro->data)+1);
    strcpy(output, pro->data);
    return output;
}

void setProperty(Property* pro, const char* value) {
    if (!pro || !value)
        return;
    pro->data = realloc(pro->data, sizeof(char) * strlen(value)+1);
    strcpy(pro->data, value);
}

void printProperty(const Property* pro) {
    printf("%s", pro->data);
}
