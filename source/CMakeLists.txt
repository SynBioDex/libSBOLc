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
    ${PROJECT_SOURCE_DIR}/core/*.cpp
    ${PROJECT_SOURCE_DIR}/*.h
    ${PROJECT_SOURCE_DIR}/*.c
)

# gather test files
FILE( GLOB PROJECT_TEST_FILES
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
#ADD_LIBRARY( sbol
#    SHARED
#    ${PROJECT_SOURCE_FILES}
#)
#TARGET_LINK_LIBRARIES( sbol
#    xml2
#    libcurl
#    raptor2
#)
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/core
)

# build examples
#ADD_EXECUTABLE( readntriples
#    ${PROJECT_SOURCE_FILES}
#    ${PROJECT_EXAMPLE_DIR}/read_ntriples.c
#)
#ADD_EXECUTABLE( validate
#    ${PROJECT_SOURCE_FILES}
#    ${PROJECT_EXAMPLE_DIR}/validate.c
#)
#TARGET_LINK_LIBRARIES( readntriples sbol )
#TARGET_LINK_LIBRARIES( validate     sbol )

# build tests
ADD_EXECUTABLE( testsequence
	${PROJECT_SOURCE_DIR}/core/sequence.h
	${PROJECT_SOURCE_DIR}/core/sequence.c
	${PROJECT_TEST_DIR}/CuTest.h
	${PROJECT_TEST_DIR}/CuTest.c
	${PROJECT_TEST_DIR}/utilities.h
	${PROJECT_TEST_DIR}/utilities.c
	${PROJECT_TEST_DIR}/test_sequence.c
)
ADD_EXECUTABLE( testannotation
	${PROJECT_SOURCE_DIR}/core/annotation.h
	${PROJECT_SOURCE_DIR}/core/annotation.c
	${PROJECT_TEST_DIR}/CuTest.h
	${PROJECT_TEST_DIR}/CuTest.c
	${PROJECT_TEST_DIR}/utilities.h
	${PROJECT_TEST_DIR}/utilities.c
	${PROJECT_TEST_DIR}/test_annotation.c
)
ADD_EXECUTABLE( testcollection
	${PROJECT_SOURCE_DIR}/core/collection.h
	${PROJECT_SOURCE_DIR}/core/collection.c
	${PROJECT_TEST_DIR}/CuTest.h
	${PROJECT_TEST_DIR}/CuTest.c
	${PROJECT_TEST_DIR}/utilities.h
	${PROJECT_TEST_DIR}/utilities.c
	${PROJECT_TEST_DIR}/test_collection.c
)
#ADD_EXECUTABLE( testcore
#	${PROJECT_TEST_FILES}
#)
#TARGET_LINK_LIBRARIES( testcore sbol )