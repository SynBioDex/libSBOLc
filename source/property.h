///////////////////////////////////////////////////////////
/// @file property.h
/// This file defines a simple hierarchy of Properties,
/// which hold data for SBOLObjects. Although they don't
/// do much so far, this is where you would add restraints
/// on the getting and setting of specific values. For
/// example, you could add a NucleotidesProperty that
/// only accepts strings of a, c, t, g, and sometimes n.
///////////////////////////////////////////////////////////

#ifndef SBOL_PROPERTY_HEADER
#define SBOL_PROPERTY_HEADER

/// @todo Create Property as a basis for TextProperty and IntProperty

/************
 * Property
 ************/

/// Generic Property that forms the base struct for all the others.
/// Besides making the inheritance diagrams look nice, this provides
/// a hook for doing something whenever a Property is read or written.
typedef struct _Property {
    void *data;
} Property;

Property *createProperty();
void deleteProperty(Property *pro);
void setProperty(Property *pro, void *data);
void *getProperty(const Property *pro);
int compareProperty(const Property *pro1, const Property *pro2);

/****************
 * TextProperty
 ****************/

/// Base struct for all text-containing Properties.
/// @todo Make TextProperty derive from Property
typedef struct _TextProperty {
	struct _Property *text;
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

/// A TextProperty that only allows creation
/// of values that aren't already in use as the
/// uri of an SBOLObject.
typedef struct _URIProperty {
	struct _TextProperty* uri;
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

/// Base struct for all integer-valued Properties.
/// @todo Make IntProperty derive from Property
typedef struct _IntProperty {
    struct _Property *number;
} IntProperty;

IntProperty* createIntProperty();
void deleteIntProperty(IntProperty* pro);
void setIntProperty(IntProperty* pro, int value);
int getIntProperty(const IntProperty* pro);
int compareIntProperty(const IntProperty* pro1, const IntProperty* pro2);
void printIntProperty(const IntProperty* pro);

/********************
 * PositionProperty
 ********************/

/// IntProperty that only allows non-negative values.
/// There should also be other restrictions, but they
/// only make sense for groups, not individual PositionProperties.
/// For example, SequenceAnnotation->bioEnd should be at least
/// as large as SequenceAnnotation->bioStart.
typedef struct _PositionProperty {
	struct _IntProperty* position;
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

/// IntProperty that only allows the values 0 or 1.
/// 1 indicates the positive strand relative to the parent
/// component, and 0 indicates the reverse complement.
/// @todo Separate BooleanProperty?
/// @todo Base this on chars instead of ints? Like '+', '-', '?'
typedef struct _PolarityProperty {
	struct _IntProperty* polarity;
} PolarityProperty;

PolarityProperty* createPolarityProperty();
void deletePolarityProperty(PolarityProperty* pro);
void setPolarityProperty(PolarityProperty* pro, const int value);
int getPolarityProperty(const PolarityProperty* pro);
int comparePolarityProperty(const PolarityProperty* pro1, const PolarityProperty* pro2);
void printPolarityProperty(const PolarityProperty* pro);

#endif
