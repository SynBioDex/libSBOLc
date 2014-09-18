# set variables in source code
CONFIGURE_FILE(
	${SBOL_SOURCE_DIR}/constants.h.in
	${SBOL_SOURCE_DIR}/constants.h
)

#adjust paths
SET( SBOL_RELEASE_DIR       ${SBOL_RELEASE_DIR}/library )
SET( LIBRARY_OUTPUT_PATH    ${SBOL_RELEASE_DIR} )

# find/build libxml
IF( WIN32 )
	ADD_SUBDIRECTORY( libxml2 )
	SET( LIBXML2_INCLUDE_DIR ${SBOL_SOURCE_DIR}/libxml2/include )
ELSE()
	FIND_PACKAGE( LibXml2 )
ENDIF()
INCLUDE_DIRECTORIES( ${LIBXML2_INCLUDE_DIR} )

# gather source files
FILE( GLOB SBOL_SOURCE_FILES
	${SBOL_SOURCE_DIR}/*.h
	${SBOL_SOURCE_DIR}/*.c
)

# build static library for release
ADD_LIBRARY( sbol_static
	STATIC 
	${SBOL_SOURCE_FILES}
)

# by default, GCC exports everything;
# this tells it to stick to SBOLAPIEXPORTS functions
IF(CMAKE_COMPILER_IS_GNUCC)
	SET_TARGET_PROPERTIES( sbol_static
		PROPERTIES COMPILE_FLAGS -fvisibility=hidden
	)
ENDIF()

# link against libxml
TARGET_LINK_LIBRARIES( sbol_static
	xml2
)

# build shared library for release
ADD_LIBRARY( sbol_shared
	SHARED
	${SBOL_SOURCE_FILES}
)
set_target_properties(sbol_shared PROPERTIES OUTPUT_NAME sbol)

# by default, GCC exports everything;
# this tells it to stick to SBOLAPIEXPORTS functions
IF(CMAKE_COMPILER_IS_GNUCC)
	SET_TARGET_PROPERTIES( sbol_shared
		PROPERTIES COMPILE_FLAGS -fvisibility=hidden
	)
ENDIF()

# link against libxml
TARGET_LINK_LIBRARIES( sbol_shared
	xml2
)