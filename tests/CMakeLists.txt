# gather headers
INCLUDE_DIRECTORIES(
    ${LIBXML2_INCLUDE_DIR}
    ${SBOL_SOURCE_DIR}
)

# gather test source files
FILE( GLOB SBOL_TEST_FILES
    ${SBOL_TEST_DIR}/*.h
    ${SBOL_TEST_DIR}/*.c
)

# gather test targets
FILE( GLOB SBOL_TEST_TARGETS
    ${SBOL_TEST_DIR}/test_all.c
)

# build each test target
FOREACH( TARGET ${SBOL_TEST_TARGETS} )

    GET_FILENAME_COMPONENT( BASENAME
        ${TARGET}
        NAME_WE
    )

    ADD_EXECUTABLE( ${BASENAME}
        ${SBOL_TEST_FILES}
        ${TARGET}
    )

    TARGET_LINK_LIBRARIES( ${BASENAME}
        sbol
    )

ENDFOREACH()
