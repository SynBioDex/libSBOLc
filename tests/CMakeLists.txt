#adjust paths
SET( SBOL_RELEASE_DIR       ${SBOL_RELEASE_DIR}/tests )
SET( EXECUTABLE_OUTPUT_PATH ${SBOL_RELEASE_DIR}       )
SET( LIBRARY_OUTPUT_PATH    ${SBOL_RELEASE_DIR}       )

# gather headers
INCLUDE_DIRECTORIES(
    ${LIBXML2_INCLUDE_DIR}
    ${SBOL_SOURCE_DIR}
)

# gather source files
FILE( GLOB SBOL_SOURCE_FILES
	${SBOL_SOURCE_DIR}/*.h
	${SBOL_SOURCE_DIR}/*.c
)

# build a static library because it's supposedly easier
# to use with a debugger, and because it lets tests access
# non-SBOLAPIEXPORTS functions
ADD_LIBRARY( sbol_test
	STATIC
	${SBOL_SOURCE_FILES}
)
TARGET_LINK_LIBRARIES( sbol_test
	xml2
)

# gather test source files
FILE( GLOB SBOL_TEST_FILES
	${SBOL_EXAMPLE_DIR}/code/sbol_create_valid*.c
    ${SBOL_TEST_DIR}/*.h
    ${SBOL_TEST_DIR}/*.c
)

# build test executable
ADD_EXECUTABLE( sbol_run_tests
	${SBOL_TEST_FILES}
)
TARGET_LINK_LIBRARIES( sbol_run_tests
	sbol_test
)

