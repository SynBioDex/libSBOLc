#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "debug.h"
#include "property.h"

/************
 * Property
 ************/

union Property *createProperty() {
	union Property *pro = malloc(sizeof(union Property));
	pro->letters = NULL;
	return pro;
}

void deleteProperty(union Property *pro) {
	if (pro) {
		pro->letters = NULL;
		free(pro);
		pro = NULL;
	}
}

void setNumber(union Property *pro, int num) {
	if (pro) {
		pro->number = num;
	}
}

void setLetters(union Property *pro, char *str) {
	if (pro) {
		pro->letters = realloc(pro->letters, sizeof(char) * (strlen(str)+1));
		pro->letters = str;
	}
}

int getNumber(const union Property *pro) {
	if (pro)
		return pro->number;
	else
		return -1; /// @todo decide if -1 is a good default
}

char *getLetters(const union Property *pro) {
	if (!pro)
		return NULL;
	else
		return pro->letters;
}

/*int compareNumbers(const union Property *pro1, const union Property *pro2) {*/
/*	if (!pro1 && !pro2)*/
/*		return 0;*/
/*	else if (!pro1 || !pro2)*/
/*		return -1;*/
/*	else*/
/*		return (pro1->number - pro2->number);*/
/*}*/

/*int compareLetters(const union Property *pro1, const union Property *pro2) {*/
/*	if ((!pro1 && !pro2) || (!pro1->letters && !pro2->letters))*/
/*		return 0;*/
/*	else if (!pro1 || !pro2 || !pro1->letters || !pro2->letters)*/
/*		return -1;*/
/*	else*/
/*		return strcmp(pro1->letters, pro2->letters);*/
/*}*/

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
		char *text1 = (char *) getLetters(pro1->text);
		char *text2 = (char *) getLetters(pro2->text);
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
	char *data = (char *) getLetters(pro->text);
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
		char *data = (char *) getLetters(pro->text);
		data = realloc(data, sizeof(char) * strlen(text)+1);
		strcpy(data, text);
		setLetters(pro->text, data);
	}
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

/// @todo remove IntProperty

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
		setNumber(pro->number, value);
	}
}

int getIntProperty(const IntProperty* pro) {
	if (pro)
		return getNumber(pro->number);
}

int compareIntProperty(const IntProperty* pro1,
					   const IntProperty* pro2) {
	if (!pro1 && !pro2)
		return 1;
	else if (!pro1 || !pro2)
		return 0;
	else {
		int num1 = getNumber(pro1->number);
		int num2 = getNumber(pro2->number);
		return num1 - num2;
	}
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
	setIntProperty(pro->position, -1);
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
	setPolarityProperty(pro, 1);
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
