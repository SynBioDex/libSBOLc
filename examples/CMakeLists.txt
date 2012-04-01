# gather headers
INCLUDE_DIRECTORIES(
    ${LIBXML2_INCLUDE_DIR}
    ${SBOL_SOURCE_DIR}
)

# gather source files
FILE( GLOB SBOL_EXAMPLE_TARGETS
    ${SBOL_EXAMPLE_DIR}/*.c
)

# build each source file
FOREACH( TARGET ${SBOL_EXAMPLE_TARGETS} )

    GET_FILENAME_COMPONENT( BASENAME
        ${TARGET}
        NAME_WE
    )

    ADD_EXECUTABLE( ${BASENAME}
        ${TARGET}
    )

    TARGET_LINK_LIBRARIES( ${BASENAME}
        sbol
    )

ENDFOREACH()
