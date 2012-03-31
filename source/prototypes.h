#ifndef SBOL_PROTOTYPES_HEADER
#define SBOL_PROTOTYPES_HEADER

typedef enum   _StrandPolarity      StrandPolarity;

typedef union  _Property            Property;
typedef struct _TextProperty        TextProperty;
typedef struct _URIProperty         URIProperty;
typedef struct _NucleotidesProperty NucleotidesProperty;
typedef struct _PositionProperty    PositionProperty;
typedef struct _PolarityProperty    PolarityProperty;

typedef struct _PointerArray PointerArray;

typedef struct _SBOLObject         SBOLObject;
typedef struct _SBOLCompoundObject SBOLCompoundObject;
typedef struct _DNASequence        DNASequence;
typedef struct _SequenceAnnotation SequenceAnnotation;
typedef struct _DNAComponent       DNAComponent;
typedef struct _Collection         Collection;

#endif
