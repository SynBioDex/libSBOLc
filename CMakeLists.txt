#-------------------------------------------------------------------
#  This file tells Cmake how to create the libSBOLc project
#   CMake will then use this information to create 
#   makefiles, MSVC projects, etc. (cross plarform)
#-------------------------------------------------------------------

#project name
PROJECT( SBOL )
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

#include directories
INCLUDE_DIRECTORIES( BEFORE
	${SBOL_SOURCE_DIR}/curl/include
    ${SBOL_SOURCE_DIR}/expat
	${SBOL_SOURCE_DIR}/expat/lib
	${SBOL_SOURCE_DIR}/raptor2/src
)

#build other required libraries
ADD_SUBDIRECTORY( curl )      #needed by raptor
ADD_SUBDIRECTORY( raptor2 )   #RDF parser

#all the source files in the libSBOLc project
FILE( GLOB  SBOL_SRC_FILES   ${SBOL_SOURCE_DIR}/parser.cpp)

#create the SBOL library
ADD_LIBRARY( sbol
  SHARED
  ${SBOL_SRC_FILES}
)

TARGET_LINK_LIBRARIES( sbol
   sbol
   raptor2
)

ADD_EXECUTABLE( sboltest
#  SHARED
  test.c
)

TARGET_LINK_LIBRARIES( sboltest
   sbol
   raptor2
)
#------------------------------------------------------------------
# The rest is for creating the python module using SWIG
#------------------------------------------------------------------
IF ( WIN32 )
	 IF (MINGW)
		ADD_CUSTOM_COMMAND ( 
			TARGET sbol POST_BUILD
			COMMAND move /Y ..\\bin\\python\\libsbol.dll ..\\bin\\python\\_sbol.pyd
		)
	 ELSE (MINGW)
		ADD_CUSTOM_COMMAND (
			TARGET tcpy POST_BUILD
			COMMAND move /Y \"${SBOL_BINARY_DIR}\"\\Release\\sbol.dll \"${SBOL_BINARY_DIR}\"\\Release\\_sbol.pyd
		)
	 ENDIF (MINGW)
ELSE ( WIN32 )
	 IF( APPLE )
		ADD_CUSTOM_COMMAND ( 
			  TARGET tcpy POST_BUILD
			  COMMAND cp ${SBOL_BINARY_DIR}/libsbol.dylib ${SBOL_BINARY_DIR}/_sbol.so
		)
	ELSE( APPLE )
		ADD_CUSTOM_COMMAND ( 
			  TARGET sbol POST_BUILD 
			  COMMAND mv ${SBOL_BINARY_DIR}/libsbol.so ${SBOL_BINARY_DIR}/_sbol.so
		)
	ENDIF( APPLE )
ENDIF( WIN32 )




