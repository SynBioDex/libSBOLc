#adjust paths
SET( SBOL_RELEASE_DIR       ${SBOL_RELEASE_DIR}/examples )
SET( EXECUTABLE_OUTPUT_PATH ${SBOL_RELEASE_DIR}          )
SET( LIBRARY_OUTPUT_PATH    ${SBOL_RELEASE_DIR}          )

# gather headers
INCLUDE_DIRECTORIES(
    ${LIBXML2_INCLUDE_DIR}
    ${SBOL_SOURCE_DIR}
)

# gather source files
FILE( GLOB SBOL_EXAMPLE_TARGETS
    ${SBOL_EXAMPLE_DIR}/code/sbol_parse.c
    ${SBOL_EXAMPLE_DIR}/code/sbol_validate.c
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

	# link against the release version of the library
    TARGET_LINK_LIBRARIES( ${BASENAME}
        sbol
    )

ENDFOREACH()
