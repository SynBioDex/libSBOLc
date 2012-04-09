FIND_PACKAGE( SWIG )
IF( SWIG_FOUND )

	# adjust paths
	SET( SBOL_RELEASE_DIR       ${SBOL_RELEASE_DIR}/wrapper )
	SET( EXECUTABLE_OUTPUT_PATH ${SBOL_RELEASE_DIR}         )
	SET( LIBRARY_OUTPUT_PATH    ${SBOL_RELEASE_DIR}         )

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
	
	# build a shared library without visibility limitations
	# because the non-SBOLAPIEXPORTS functions could be useful
	# in writing a higher-level wrapper, and because Python
	# will try to import them anyway and fail
	ADD_LIBRARY( sbol_swig
		SHARED
		${SBOL_SOURCE_FILES}
	)
	TARGET_LINK_LIBRARIES( sbol_swig
		xml2
	)
	
	# set up some SWIG stuff
    INCLUDE( ${SWIG_USE_FILE} )
    FIND_PACKAGE( PythonLibs )
    INCLUDE_DIRECTORIES( ${PYTHON_INCLUDE_PATH} )
    SET( CMAKE_SWIG_FLAGS "" )
    SET( CMAKE_SWIG_OUTDIR ${SBOL_RELEASE_DIR} )

	# build the SWIG wrapper
    SWIG_ADD_MODULE( libsbol
        python
        libsbol.i
        ${SBOL_SOURCE_FILES}
    )
    SWIG_LINK_LIBRARIES( libsbol
        ${PYTHON_LIBRARIES}
        xml2
        sbol_swig
    )

ELSE()

    MESSAGE( "SWIG not found; unable to generate Python bindings" )

ENDIF()
