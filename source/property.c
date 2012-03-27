#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "debug.h"
#include "property.h"

/************
 * Property
 ************/

Property *createProperty() {
	Property *pro = malloc(sizeof(Property));
	pro->data = NULL;
	return pro;
}

void deleteProperty(Property *pro) {
	if (pro) {
		if (pro->data) {
			free(pro->data);
			pro->data = NULL;
		}
		free(pro);
	}
}

void setProperty(Property *pro, void *data) {
	if (pro) {
		pro->data = realloc(pro->data, sizeof(data));
		pro->data = data;
	}
}

void *getProperty(const Property *pro) {
	if (!pro)
		return NULL;
	else
		return pro->data;
}

int compareProperty(const Property *pro1, const Property *pro2) {
	if ((!pro1 && !pro2) || (!pro1->data && !pro2->data))
		return 1;
	else if (!pro1 || !pro2 || !pro1->data || !pro2->data)
		return 0;
	else
		return (int) (pro1->data == pro2->data);
}

/****************
 * TextProperty
 ****************/

TextProperty* createTextProperty() {
	TextProperty* pro = malloc(sizeof(TextProperty));
	pro->text = createProperty();
	return pro;
}

void deleteTextProperty(TextProperty* pro) {
	if (pro) {
		if (pro->text) {
			deleteProperty(pro->text);
			pro->text = NULL;
		}
		free(pro);
	}
}

int compareTextProperty(const TextProperty* pro1,
						const TextProperty* pro2) {
	if ((!pro1 && !pro2) || (!pro1->text && !pro2->text))
		return 1;
	else {
		char *text1 = (char *) getProperty(pro1->text);
		char *text2 = (char *) getProperty(pro2->text);
		if (!text1 && !text2)
			return 1;
		else if (!text1 || !text2)
			return 0;
		else {
			int result = strcmp(text1, text2);
			free(text1);
			free(text2);
			return result;
		}
	}
}

char* getTextProperty(const TextProperty* pro) {
	if (!pro || !pro->text)
		return NULL;
	char *data = (char *) getProperty(pro->text);
	if (!data)
		return NULL;
	char *output = malloc(sizeof(char) * strlen(data)+1);
	strcpy(output, data);
	return output;
}

/// @todo remove the pro->text != NULL restriction?
/// @todo warn that you need to free() anything from a Property
void setTextProperty(TextProperty* pro, const char* text) {
	if (!pro)
		return;
	else if (!text) {
		deleteProperty(pro->text);
		pro->text = createProperty();
	} else {
		char *data = (char *) getProperty(pro->text);
		data = realloc(data, sizeof(char) * strlen(text)+1);
		strcpy(data, text);
		setProperty(pro->text, data);
	}
}

void printTextProperty(const TextProperty* pro) {
	if (pro)
		printf("%s", (char *)pro->text);
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
	}
}

void setURIProperty(URIProperty* pro, const char* uri) {
	if (pro && uri && !isSBOLObjectURI(uri))
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
	pro->number = createProperty();
	return pro;
}

void deleteIntProperty(IntProperty* pro) {
	if (pro) {
		if (pro->number)
			deleteProperty(pro->number);
		free(pro);
	}
}

void setIntProperty(IntProperty* pro, int value) {
	if (pro) {
		setProperty(pro->number, (void *) &value);
	}
}

int getIntProperty(const IntProperty* pro) {
	if (pro)
		return *(int *)getProperty(pro->number);
}

int compareIntProperty(const IntProperty* pro1,
					   const IntProperty* pro2) {
	if (!pro1 && !pro2)
		return 1;
	else if (!pro1 || !pro2)
		return 0;
	else {
		int *num1 = (int *) getProperty(pro1->number);
		int *num2 = (int *) getProperty(pro2->number);
		int result = *num1 - *num2;
		free(num1);
		free(num2);
		return result;
	}
}

void printIntProperty(const IntProperty* pro) {
	if (pro)
		printf("%i", *( (int *)getProperty(pro->number) ));
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
