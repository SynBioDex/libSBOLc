PROJECT( SBOL )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# shorthand for common folders
SET( PROJECT_ROOT_DIR    ${PROJECT_SOURCE_DIR}/..     )
SET( PROJECT_BUILD_DIR   ${PROJECT_ROOT_DIR}/build    )
SET( PROJECT_RELEASE_DIR ${PROJECT_ROOT_DIR}/release  )
SET( PROJECT_EXAMPLE_DIR ${PROJECT_ROOT_DIR}/examples )
SET( PROJECT_SCHEMA_DIR  ${PROJECT_ROOT_DIR}/schemas  )
SET( PROJECT_TEST_DIR    ${PROJECT_ROOT_DIR}/tests    )

# gather source files
FILE( GLOB PROJECT_SOURCE_FILES
	${PROJECT_SOURCE_DIR}/core/*.h
	${PROJECT_SOURCE_DIR}/core/*.c
	${PROJECT_SOURCE_DIR}/*.h
	${PROJECT_SOURCE_DIR}/*.c
)

# gather test files
FILE( GLOB PROJECT_TEST_FILES
	${PROJECT_SOURCE_DIR}/core/*.h
	${PROJECT_SOURCE_DIR}/core/*.c
	${PROJECT_TEST_DIR}/*.h
	${PROJECT_TEST_DIR}/*.c
)

# where to send finished files
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_RELEASE_DIR} )
SET( LIBRARY_OUTPUT_PATH    ${PROJECT_RELEASE_DIR} )

# find libxml2, or build if needed
IF( WIN32 )
	ADD_SUBDIRECTORY( libxml2 )
ELSE()
	FIND_PACKAGE( LibXml2 )
ENDIF()
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
	${PROJECT_SOURCE_FILES}
)
TARGET_LINK_LIBRARIES( sbol
	xml2
	libcurl
	raptor2
)
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/core
	${PROJECT_TEST_DIR}
)

# build examples
ADD_EXECUTABLE( sbol_parse
	${PROJECT_SOURCE_FILES}
	${PROJECT_EXAMPLE_DIR}/sbol_parse.c
)
ADD_EXECUTABLE( sbol_validate
	${PROJECT_SOURCE_FILES}
	${PROJECT_EXAMPLE_DIR}/sbol_validate.c
)
ADD_EXECUTABLE( sbol_roundtrip
	${PROJECT_SOURCE_FILES}
	${PROJECT_EXAMPLE_DIR}/sbol_roundtrip.c
)
TARGET_LINK_LIBRARIES( sbol_parse     sbol )
TARGET_LINK_LIBRARIES( sbol_validate  sbol )
TARGET_LINK_LIBRARIES( sbol_roundtrip sbol )

# build tests
ADD_EXECUTABLE( sbol_test
	${PROJECT_SOURCE_FILES}
	${PROJECT_TEST_FILES}
)
TARGET_LINK_LIBRARIES( sbol_test sbol )
