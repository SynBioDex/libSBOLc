PROJECT( SBOL )
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

#include directories
INCLUDE_DIRECTORIES( BEFORE
	${SBOL_SOURCE_DIR}/curl/include
    ${SBOL_SOURCE_DIR}/expat
	${SBOL_SOURCE_DIR}/expat/lib
	${SBOL_SOURCE_DIR}/raptor2/src
)

ADD_SUBDIRECTORY( curl )      #needed by raptor
ADD_SUBDIRECTORY( raptor2 )   #RDF parser

FILE( GLOB  SBOL_SRC_FILES   ${SBOL_SOURCE_DIR}/parser.cpp)

#create the library
ADD_LIBRARY( SBOL
  SHARED
  ${SBOL_SRC_FILES}
)

TARGET_LINK_LIBRARIES( SBOL
   SBOL
   raptor2
)

ADD_EXECUTABLE( SBOLtest
#  SHARED
  test.c
)

TARGET_LINK_LIBRARIES( SBOLtest
   SBOL
   raptor2
)

