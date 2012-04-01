# gather headers
INCLUDE_DIRECTORIES(
    ${LIBXML2_INCLUDE_DIR}
    ${SBOL_SOURCE_DIR}
)

FIND_PACKAGE( SWIG )
IF( SWIG_FOUND )

    INCLUDE( ${SWIG_USE_FILE} )
    FIND_PACKAGE( PythonLibs )
    INCLUDE_DIRECTORIES( ${PYTHON_INCLUDE_PATH} )
    SET( CMAKE_SWIG_FLAGS "" )
    SET( CMAKE_SWIG_OUTDIR ${SBOL_RELEASE_DIR} )

    SWIG_ADD_MODULE( sbol
        python
        sbol.i
        ${SBOL_SOURCE_FILES}
    )

    SWIG_LINK_LIBRARIES( sbol
        ${PYTHON_LIBRARIES}
        sbol
    )

ELSE()

    MESSAGE( "SWIG not found; unable to generate Python bindings" )

ENDIF()
