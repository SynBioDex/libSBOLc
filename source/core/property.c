#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "debug.h"
#include "property.h"

/****************
 * TextProperty
 ****************/

TextProperty* createTextProperty() {
    TextProperty* pro = malloc(sizeof(TextProperty));
    pro->text = NULL;
    return pro;
}

void deleteTextProperty(TextProperty* pro) {
    if (pro) {
    	if (pro->text) {
        	free(pro->text);
        	pro->text = NULL;
        }
        //free(pro); // TODO what's wrong with this?
        pro = NULL;
    }
}

int compareTextProperty(const TextProperty* pro1,
                        const TextProperty* pro2) {
    if (!pro1 || !pro2 || !pro1->text || !pro2->text)
        // TODO is this a good error value for strcmp?
        return -1;
    return strcmp(pro1->text, pro2->text);
}

char* getTextProperty(const TextProperty* pro) {
    if (!pro || !pro->text)
        return NULL;
    char* output = malloc(sizeof(char) * strlen(pro->text)+1);
    strcpy(output, pro->text);
    return output;
}

void setTextProperty(TextProperty* pro, const char* text) {
    if (!pro || !text)
        return;
    pro->text = realloc(pro->text, sizeof(char) * strlen(text)+1);
    strcpy(pro->text, text);
}

void printTextProperty(const TextProperty* pro) {
    if (pro)
		printf("%s", pro->text);
}

/***************
 * URIProperty
 ***************/

URIProperty* createURIProperty() {
	return (URIProperty*) createTextProperty();
}

void deleteURIProperty(URIProperty* pro) {
	deleteTextProperty((TextProperty*) pro);
}

void setURIProperty(URIProperty* pro, const char* uri) {
	if (pro && !isDuplicateURI(uri))
		setTextProperty((TextProperty*) pro, uri);
}

char* getURIProperty(const URIProperty* pro) {
	if (pro)
		return getTextProperty((TextProperty*) pro);
	else
		return NULL;
}

int compareURIProperty(const URIProperty* pro1,
                       const URIProperty* pro2) {
	return compareTextProperty((TextProperty*) pro1, (TextProperty*) pro2);
}

void printURIProperty(const URIProperty* pro) {
	printTextProperty((TextProperty*) pro);
}

/***************
 * IntProperty
 ***************/

IntProperty* createIntProperty() {
	IntProperty* pro = malloc(sizeof(IntProperty));
	pro->number = 0;
	return pro;
}

void deleteIntProperty(IntProperty* pro) {
	if (pro)
		if (pro->number)
			pro->number = 0;
		free(pro);  // does this mean anything?
		pro = NULL;
}

void setIntProperty(IntProperty* pro, int value) {
	if (pro)
		pro->number = value;
}

int getIntProperty(const IntProperty* pro) {
	if (pro)
		return pro->number;
	// TODO "NULL" value?
}

int compareIntProperty(const IntProperty* pro1,
                       const IntProperty* pro2) {
	// TODO what's a good NULL value?
	return pro2->number - pro1->number;
}

void printIntProperty(const IntProperty* pro) {
	if (pro)
		printf("%i", pro->number);
}

/********************
 * PositionProperty
 ********************/

PositionProperty* createPositionProperty() {
	return (PositionProperty*) createIntProperty();
}

void deletePositionProperty(PositionProperty* pro) {
	deleteIntProperty((IntProperty*) pro);
}

void setPositionProperty(PositionProperty* pro, int pos) {
	if (pro && pos >= 0)
		setIntProperty((IntProperty*) pro, pos);
}

int getPositionProperty(const PositionProperty* pro) {
	return getIntProperty((IntProperty*) pro);
}

int comparePositionProperty(const PositionProperty* pro1,
                            const PositionProperty* pro2) {
	return compareIntProperty((IntProperty*) pro1, (IntProperty*) pro2);
}

void printPositionProperty(const PositionProperty* pro) {
	printIntProperty((IntProperty*) pro);
}

/********************
 * PolarityProperty
 ********************/

PolarityProperty* createPolarityProperty() {
	return (PolarityProperty*) createIntProperty();
}

void deletePolarityProperty(PolarityProperty* pro) {
	deleteIntProperty((IntProperty*) pro);
}

void setPolarityProperty(PolarityProperty* pro, int pol) {
	if (pro) {
		if (pol > 0)
			setIntProperty((IntProperty*) pro, 1);
		else
			setIntProperty((IntProperty*) pro, 0);
	}
}

int getPolarityProperty(const PolarityProperty* pro) {
	return getIntProperty((IntProperty*) pro);
}

int comparePolarityProperty(const PolarityProperty* pro1,
                            const PolarityProperty* pro2) {
	return compareIntProperty((IntProperty*) pro1, (IntProperty*) pro2);
}

void printPolarityProperty(const PolarityProperty* pro) {
	if (pro) {
		if (getIntProperty((IntProperty*) pro) == 1)
			printf("+");
		else
			printf("-");
	}
}
