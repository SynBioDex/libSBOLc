#ifndef SBOL_CORE_PROPERTY
#define SBOL_CORE_PROPERTY

/****************
 * TextProperty
 ****************/

typedef struct _TextProperty {
	char* text;
} TextProperty;

TextProperty* createTextProperty();
void deleteTextProperty(TextProperty* pro);
void setTextProperty(TextProperty* pro, const char* text);
char* getTextProperty(const TextProperty* pro);
int compareTextProperty(const TextProperty* pro1, const TextProperty* pro2);
void printTextProperty(const TextProperty* pro);

/***************
 * URIProperty
 ***************/

typedef struct _URIProperty {
	struct _TextProperty uri;
} URIProperty;

URIProperty* createURIProperty();
void deleteURIProperty(URIProperty* pro);
void setURIProperty(URIProperty* pro, const char* uri);
char* getURIProperty(const URIProperty* pro);
int compareURIProperty(const URIProperty* pro1, const URIProperty* pro2);
void printURIProperty(const URIProperty* pro);

/***************
 * IntProperty
 ***************/

typedef struct _IntProperty {
	int number;
} IntProperty;

IntProperty* createIntProperty();
void deleteIntProperty(IntProperty* pro);
void setIntProperty(IntProperty* pro, const int value);
int getIntProperty(const IntProperty* pro);
int compareIntProperty(const IntProperty* pro1, const IntProperty* pro2);
void printIntProperty(const IntProperty* pro);

/********************
 * PositionProperty
 ********************/

typedef struct _PositionProperty {
	struct _IntProperty position;
} PositionProperty;

PositionProperty* createPositionProperty();
void deletePositionProperty(PositionProperty* pro);
void setPositionProperty(PositionProperty* pro, const int value);
int getPositionProperty(const PositionProperty* pro);
int comparePositionProperty(const PositionProperty* pro1, const PositionProperty* pro2);
void printPositionProperty(const PositionProperty* pro);

/********************
 * PolarityProperty
 ********************/

typedef struct _PolarityProperty {
	struct _IntProperty polarity;
} PolarityProperty;

PolarityProperty* createPolarityProperty();
void deletePolarityProperty(PolarityProperty* pro);
void setPolarityProperty(PolarityProperty* pro, const int value);
int getPolarityProperty(const PolarityProperty* pro);
int comparePolarityProperty(const PolarityProperty* pro1, const PolarityProperty* pro2);
void printPolarityProperty(const PolarityProperty* pro);

#endif
