#-------------------------------------------------------------------
#  This file tells Cmake how to create the libSBOLc project
#   CMake will then use this information to create 
#   makefiles, MSVC projects, etc. (cross plarform)
#-------------------------------------------------------------------

# set project info
PROJECT( SBOL )
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

# send executables to DIST dir
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../DIST)
SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

# find raptor
ADD_SUBDIRECTORY( curl    ) # needed by raptor
ADD_SUBDIRECTORY( raptor2 ) # RDF parser

# find libxml2
SET( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" )
FIND_PACKAGE( LibXml2 REQUIRED )

# tell CMake where to look for headers
INCLUDE_DIRECTORIES( BEFORE
	${SBOL_SOURCE_DIR}/curl/include
	${SBOL_SOURCE_DIR}/expat
	${SBOL_SOURCE_DIR}/expat/lib
	${SBOL_SOURCE_DIR}/raptor2/src
	${LIBXML2_INCLUDE_DIR}
)

# list source files to put in the library
FILE( GLOB  SBOL_SRC_FILES
	${SBOL_SOURCE_DIR}/core.h
	${SBOL_SOURCE_DIR}/core.cpp
	${SBOL_SOURCE_DIR}/reader.h
	${SBOL_SOURCE_DIR}/reader.c
	${SBOL_SOURCE_DIR}/validator.h
	${SBOL_SOURCE_DIR}/validator.c
)

# set up the library
ADD_LIBRARY( sbol SHARED ${SBOL_SRC_FILES} )
TARGET_LINK_LIBRARIES( sbol sbol raptor2 xml2 )

# set up tests
ADD_EXECUTABLE( testreadntriples ../test/test_read_ntriples.c )
ADD_EXECUTABLE( testvalidate     ../test/test_validate.c      )
TARGET_LINK_LIBRARIES( testreadntriples sbol )
TARGET_LINK_LIBRARIES( testvalidate     sbol )

