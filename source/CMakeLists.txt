PROJECT( SBOL )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# shorthand for common folders
SET( PROJECT_ROOT_DIR    ${PROJECT_SOURCE_DIR}/..    )
SET( PROJECT_BUILD_DIR   ${PROJECT_ROOT_DIR}/build   )
SET( PROJECT_RELEASE_DIR ${PROJECT_ROOT_DIR}/release )

# where to send finished files
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_RELEASE_DIR} )
SET( LIBRARY_OUTPUT_PATH    ${PROJECT_RELEASE_DIR} )

# build libxml2
ADD_SUBDIRECTORY( libxml2 )
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/libxml2/include
)

# build raptor dependencies
# (except expat, which comes next)
ADD_SUBDIRECTORY( curl )
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/curl/include
    ${PROJECT_SOURCE_DIR}/expat
    ${PROJECT_SOURCE_DIR}/expat/lib
)

# build raptor
ADD_SUBDIRECTORY( raptor2 ) # includes expat
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/raptor2/src
)

# build libSBOL
ADD_LIBRARY( sbol
    SHARED
    ${PROJECT_SOURCE_DIR}/core.h
    ${PROJECT_SOURCE_DIR}/core.cpp
    ${PROJECT_SOURCE_DIR}/writer.c
    ${PROJECT_SOURCE_DIR}/reader.h
    ${PROJECT_SOURCE_DIR}/reader.c
)
TARGET_LINK_LIBRARIES( sbol
    xml2
    libcurl
    raptor2
)
