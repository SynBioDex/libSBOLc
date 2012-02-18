PROJECT( SBOL )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# personal shorthand for common folders
SET( PROJECT_ROOT_DIR    ${PROJECT_SOURCE_DIR}/..    )
SET( PROJECT_BUILD_DIR   ${PROJECT_ROOT_DIR}/build   )
SET( PROJECT_RELEASE_DIR ${PROJECT_ROOT_DIR}/release )

# folders to recurse into
# (each has its own CMakeLists.txt)
ADD_SUBDIRECTORY( libxml2 )

# where to look for headers
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/libxml2/include
)

# how to build the library
ADD_LIBRARY( sbol
    SHARED
    ${PROJECT_SOURCE_DIR}/core.h
    ${PROJECT_SOURCE_DIR}/core.cpp
    ${PROJECT_SOURCE_DIR}/writer.c
)
TARGET_LINK_LIBRARIES( sbol
    xml2
)

# where to send finished files
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_RELEASE_DIR} )
SET( LIBRARY_OUTPUT_PATH    ${PROJECT_RELEASE_DIR} )
