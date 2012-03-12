#ifndef SBOL_CORE_PROPERTY
#define SBOL_CORE_PROPERTY

/****************
 * TextProperty
 ****************/

typedef struct _TextProperty {
	char* text;
} TextProperty;

TextProperty* createText();
void deleteText(TextProperty* pro);
void setText(TextProperty* pro, const char* text);
char* getText(const TextProperty* pro);
int compareText(const TextProperty* pro1, const TextProperty* pro2);
void printText(const TextProperty* pro);

/***************
 * URIProperty
 ***************/

typedef struct _URIProperty {
	TextProperty* uri;
} URIProperty;

URIProperty* createURI();
void deleteURI(URIProperty* pro);
void setURI(URIProperty* pro, const char* uri);
char* getURI(const URIProperty* pro);
int compareURI(const URIProperty* pro1, const URIProperty* pro2);
void printURI(const URIProperty* pro);

/***************
 * IntProperty
 ***************/

typedef struct _IntProperty {
	int number;
} IntProperty;

IntProperty* createInt();
void deleteInt(IntProperty* pro);
void setInt(IntProperty* pro, const int value);
int getInt(const IntProperty* pro);
int compareInt(const IntProperty* pro1, const IntProperty* pro2);
void printInt(const IntProperty* pro);

/********************
 * PositionProperty
 ********************/

typedef struct _PositionProperty {
	IntProperty* position;
} PositionProperty;

PositionProperty* createPosition();
void deletePosition(PositionProperty* pro);
void setPosition(PositionProperty* pro, const int value);
int getPosition(const PositionProperty* pro);
int comparePosition(const PositionProperty* pro1, const PositionProperty* pro2);
void printPosition(const PositionProperty* pro);

/********************
 * PolarityProperty
 ********************/

typedef struct _PolarityProperty {
	IntProperty* polarity;
} PolarityProperty;

PolarityProperty* createPolarity();
void deletePolarity(PolarityProperty* pro);
void setPolarity(PolarityProperty* pro, const int value);
int getPolarity(const PolarityProperty* pro);
int comparePolarity(const PolarityProperty* pro1, const PolarityProperty* pro2);
void printPolarity(const PolarityProperty* pro);

#endif
