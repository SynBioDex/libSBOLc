#-------------------------------------------------------------------
#  This file tells Cmake how to create the libSBOLc project
#   CMake will then use this information to create 
#   makefiles, MSVC projects, etc. (cross plarform)
#-------------------------------------------------------------------

# project name
PROJECT( SBOL )
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

# find libxml++
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules/" )
find_package( LibXML++ REQUIRED )

# include directories
INCLUDE_DIRECTORIES( BEFORE
    ${SBOL_SOURCE_DIR}/curl/include
    ${SBOL_SOURCE_DIR}/expat
    ${SBOL_SOURCE_DIR}/expat/lib
    ${SBOL_SOURCE_DIR}/raptor2/src
    ${LibXML++_INCLUDE_DIRS}
)

# build other required libraries
ADD_SUBDIRECTORY( curl )      #needed by raptor
ADD_SUBDIRECTORY( raptor2 )   #RDF parser

# all the source files in the libSBOLc project
FILE( GLOB  SBOL_SRC_FILES
    ${SBOL_SOURCE_DIR}/reader.cpp
    ${SBOL_SOURCE_DIR}/writer.cpp
    #${SBOL_SOURCE_DIR}/checker.cpp
)

### add executables ###

ADD_LIBRARY( sbol
    SHARED
    ${SBOL_SRC_FILES}
)

ADD_EXECUTABLE( check
    checker.cpp
)

ADD_EXECUTABLE( testread
    #SHARED
    testread.c
)

ADD_EXECUTABLE( testreadwrite
    writer.cpp
)

### link to libraries ###

TARGET_LINK_LIBRARIES( sbol
    sbol
    raptor2
)

TARGET_LINK_LIBRARIES( check
    ${LibXML++_LIBRARIES}
)

TARGET_LINK_LIBRARIES( testread
   sbol
   raptor2
)

TARGET_LINK_LIBRARIES( testreadwrite
    ${LibXML++_LIBRARIES}
)

#------------------------------------------------------------------
# The rest is for creating the python module using SWIG
#------------------------------------------------------------------
# get Python libs
ADD_DEFINITIONS(-DTC_EXPORTS)

IF( WIN32 AND MINGW)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib -msvcrt90")
ENDIF( WIN32 AND MINGW)
    
IF (NOT DEFINED PYTHON_INCLUDE_PATH OR NOT DEFINED PYTHON_LIBRARY)
    FIND_PACKAGE( PythonLibs )
ENDIF (NOT DEFINED PYTHON_INCLUDE_PATH OR NOT DEFINED PYTHON_LIBRARY)

IF (DEFINED PYTHON_LIB)
    SET(PYTHON_LIBRARY ${PYTHON_LIB})
ENDIF (DEFINED PYTHON_LIB)

IF ((DEFINED PYTHON_INCLUDE_PATH) AND (NOT DEFINED PYTHON_INCLUDE_DIR))
    SET(PYTHON_INCLUDE_DIR ${PYTHON_INCLUDE_PATH})
ENDIF ((DEFINED PYTHON_INCLUDE_PATH) AND (NOT DEFINED PYTHON_INCLUDE_DIR))

IF (DEFINED PYTHON_INCLUDE_DIRS)
   SET(PYTHON_INCLUDE_DIR ${PYTHON_INCLUDE_DIRS})
ENDIF (DEFINED PYTHON_INCLUDE_DIRS)

# DBL_ definitions are missing in new MinGW -- why did they do that?
IF (WIN32 AND MINGW)
    ADD_DEFINITIONS(-DDBL_EPSILON=2.22045e-16)
    ADD_DEFINITIONS(-DDBL_MIN=1e-999)
    ADD_DEFINITIONS(-DDBL_MIN_EXP=-999)
    ADD_DEFINITIONS(-DDBL_MIN_10_EXP=-307)
    ADD_DEFINITIONS(-DDBL_MAX_10_EXP=+307)
    ADD_DEFINITIONS(-DDBL_MAX=1.79769e+308)
ENDIF (WIN32 AND MINGW)

IF (NOT IS_DIRECTORY ${PYTHON_INCLUDE_DIR} OR NOT DEFINED PYTHON_LIBRARY)
    IF (NOT IS_DIRECTORY ${PYTHON_INCLUDE_DIR})
         MESSAGE(WARNING "Directory PYTHON_INCLUDE_PATH not found. Use Add Entry to add it")
    ENDIF (NOT IS_DIRECTORY ${PYTHON_INCLUDE_DIR})
    IF (NOT DEFINED PYTHON_LIBRARY)
         MESSAGE(WARNING "File PYTHON_LIB not found. Use Add Entry to add it")
    ENDIF (NOT DEFINED PYTHON_LIBRARY)
ELSE (NOT IS_DIRECTORY ${PYTHON_INCLUDE_DIR} OR NOT DEFINED PYTHON_LIBRARY)

MESSAGE(STATUS "Using Python library: ${PYTHON_LIBRARY}")

IF ( WIN32 )
  ADD_DEFINITIONS(-D_WIN32)
  ADD_DEFINITIONS(-DNODLOPEN)
  IF (MINGW)
     ADD_DEFINITIONS(-D__MINGW32__)
  ENDIF(MINGW)
ENDIF( WIN32 )

IF ( APPLE )
  SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -framework Python")
  ADD_DEFINITIONS(-DNODLOPEN)
ENDIF ( APPLE )

INCLUDE_DIRECTORIES( BEFORE ${PYTHON_INCLUDE_DIR} )

ADD_LIBRARY( _sbol
  SHARED
  sbol_wrap.c
)

TARGET_LINK_LIBRARIES( _sbol
  _sbol
  sbol
  raptor2
  ${PYTHON_LIBRARY}
)

IF ( WIN32 )
   SET_TARGET_PROPERTIES( _sbol PROPERTIES SUFFIX ".pyd" PREFIX "")
ELSE ( WIN32 )
    SET_TARGET_PROPERTIES( _sbol PROPERTIES SUFFIX ".so" PREFIX "")
ENDIF( WIN32 )

ENDIF (NOT IS_DIRECTORY ${PYTHON_INCLUDE_DIR} OR NOT DEFINED PYTHON_LIBRARY)

