#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "property.h"

/****************
 * TextProperty
 ****************/

TextProperty* createText() {
    TextProperty* pro = malloc(sizeof(TextProperty));
    pro->text = NULL;
    return pro;
}

void deleteText(TextProperty* pro) {
    if (pro) {
        free(pro->text);
        pro->text = NULL;
    }
    free(pro);
}

int compareText(const TextProperty* pro1, const TextProperty* pro2) {
    if (!pro1 || !pro2 || !pro1->text || !pro2->text)
        // TODO is this a good error value for strcmp?
        return -1;
    return strcmp(pro1->text, pro2->text);
}

char* getText(const TextProperty* pro) {
    if (!pro || !pro->text)
        return NULL;
    char* output = malloc(sizeof(char) * strlen(pro->text)+1);
    strcpy(output, pro->text);
    return output;
}

void setText(TextProperty* pro, const char* text) {
    if (!pro || !text)
        return;
    pro->text = realloc(pro->text, sizeof(char) * strlen(text)+1);
    strcpy(pro->text, text);
}

void printText(const TextProperty* pro) {
    if (pro)
		printf("%s", pro->text);
}

/***************
 * URIProperty
 ***************/

URIProperty* createURI() {
	return (URIProperty*) createText();
}

void deleteURI(URIProperty* pro) {
	deleteText((TextProperty*) pro);
}

void setURI(URIProperty* pro, const char* uri) {
	if (pro && !isDuplicateURI(uri))
		setText((TextProperty*) pro, uri);
}

char* getURI(const URIProperty* pro) {
	if (pro)
		return getText((TextProperty*) pro);
	else
		return NULL;
}

int compareURI(const URIProperty* pro1, const URIProperty* pro2) {
	return compareText((TextProperty*) pro1, (TextProperty*) pro2);
}

void printURI(const URIProperty* pro) {
	printText((TextProperty*) pro);
}

/***************
 * IntProperty
 ***************/

IntProperty* createInt() {
	IntProperty* pro = malloc(sizeof(IntProperty));
	pro->number = 0;
	return pro;
}

void deleteInt(IntProperty* pro) {
	if (pro)
		free(pro); // does this mean anything?
}

void setInt(IntProperty* pro, int value) {
	if (pro)
		pro->number = value;
}

int getInt(const IntProperty* pro) {
	if (pro)
		return pro->number;
	// TODO "NULL" value?
}

int compareInt(const IntProperty* pro1, const IntProperty* pro2) {
	// TODO what's a good NULL value?
	return pro2->number - pro1->number;
}

void printInt(const IntProperty* pro) {
	if (pro)
		printf("%i", pro->number);
}

/********************
 * PositionProperty
 ********************/

PositionProperty* createPosition() {
	return (PositionProperty*) createInt();
}

void deletePosition(PositionProperty* pro) {
	deleteInt((IntProperty*) pro);
}

void setPosition(PositionProperty* pro, int pos) {
	if (pro && pos >= 0)
		setInt((IntProperty*) pro, pos);
}

int getPosition(const PositionProperty* pro) {
	return getInt((IntProperty*) pro);
}

int comparePosition(const PositionProperty* pro1, const PositionProperty* pro2) {
	return compareInt((IntProperty*) pro1, (IntProperty*) pro2);
}

void printPosition(const PositionProperty* pro) {
	printInt((IntProperty*) pro);
}

/********************
 * PolarityProperty
 ********************/

PolarityProperty* createPolarity() {
	return (PolarityProperty*) createInt();
}

void deletePolarity(PolarityProperty* pro) {
	deleteInt((IntProperty*) pro);
}

void setPolarity(PolarityProperty* pro, int pol) {
	if (pro) {
		if (pol > 0)
			setInt((IntProperty*) pro, 1);
		else
			setInt((IntProperty*) pro, 0);
	}
}

int getPolarity(const PolarityProperty* pro) {
	return getInt((IntProperty*) pro);
}

int comparePolarity(const PolarityProperty* pro1, const PolarityProperty* pro2) {
	return compareInt((IntProperty*) pro1, (IntProperty*) pro2);
}

void printPolarity(const PolarityProperty* pro) {
	if (pro) {
		if (getInt((IntProperty*) pro) == 1)
			printf("+");
		else
			printf("-");
	}
}
