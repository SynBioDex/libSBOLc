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
        free(pro);
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
	URIProperty* pro = malloc(sizeof(URIProperty));
	pro->uri = createTextProperty();
	return pro;
}

void deleteURIProperty(URIProperty* pro) {
	if (pro) {
		if (pro->uri)
			deleteTextProperty(pro->uri);
		free(pro);
		pro = NULL;
	}
}

void setURIProperty(URIProperty* pro, const char* uri) {
	if (pro && uri && !isDuplicateURI(uri))
		setTextProperty(pro->uri, uri);
}

char* getURIProperty(const URIProperty* pro) {
	if (pro)
		return getTextProperty(pro->uri);
	else
		return NULL;
}

int compareURIProperty(const URIProperty* pro1,
                       const URIProperty* pro2) {
	if (!pro1 || !pro2) // TODO check pro1->text and pro2->text too?
		return -1;
	return compareTextProperty(pro1->uri, pro2->uri);
}

void printURIProperty(const URIProperty* pro) {
	if (pro)
		printTextProperty(pro->uri);
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
	if (pro) {
		if (pro->number)
			free(pro->number);
		free(pro);
		pro = NULL;
	}
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
	if (!pro1 || !pro2) // TODO check numbers too?
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
	PositionProperty* pro = malloc(sizeof(PositionProperty));
	pro->position = createIntProperty();
	return pro;
}

void deletePositionProperty(PositionProperty* pro) {
	if (pro) {
		if (pro->position)
			deleteIntProperty(pro->position);
		free(pro);
		pro = NULL;
	}
}

void setPositionProperty(PositionProperty* pro, int pos) {
	if (pro && pos >= 0)
		setIntProperty(pro->position, pos);
}

int getPositionProperty(const PositionProperty* pro) {
	if (pro)
		return getIntProperty(pro->position);
	else
		return -1; // TODO good error value?
}

int comparePositionProperty(const PositionProperty* pro1,
                            const PositionProperty* pro2) {
	if (!pro1 || !pro2) // TODO check numbers too?
		return compareIntProperty(pro1->position, pro2->position);
	else
		return -1;
}

void printPositionProperty(const PositionProperty* pro) {
	if (pro)
		printIntProperty(pro->position);
}

/********************
 * PolarityProperty
 ********************/

PolarityProperty* createPolarityProperty() {
	PolarityProperty* pro = malloc(sizeof(PolarityProperty));
	pro->polarity = createIntProperty();
	return pro;
}

void deletePolarityProperty(PolarityProperty* pro) {
	if (pro) {
		if (pro->polarity)
			deleteIntProperty(pro->polarity);
		free(pro);
		pro = NULL;
	}
}

void setPolarityProperty(PolarityProperty* pro, int pol) {
	if (pro) {
		if (pol > 0)
			setIntProperty(pro->polarity, 1);
		else
			setIntProperty(pro->polarity, 0);
	}
}

int getPolarityProperty(const PolarityProperty* pro) {
	if (pro)
		return getIntProperty(pro->polarity);
	else
		return -1;
}

int comparePolarityProperty(const PolarityProperty* pro1,
                            const PolarityProperty* pro2) {
	if (pro1 && pro2)
		return compareIntProperty(pro1->polarity, pro2->polarity);
	else
		return -1;
}

void printPolarityProperty(const PolarityProperty* pro) {
	if (pro) {
		if (getIntProperty(pro->polarity) == 1)
			printf("+");
		else
			printf("-");
	}
}
