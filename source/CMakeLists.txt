# set variables in source code
CONFIGURE_FILE(
	${SBOL_SOURCE_DIR}/constants.h.in
	${SBOL_SOURCE_DIR}/constants.h
)

#adjust paths
SET( SBOL_RELEASE_DIR       ${SBOL_RELEASE_DIR}/library )
SET( EXECUTABLE_OUTPUT_PATH ${SBOL_RELEASE_DIR}         )
SET( LIBRARY_OUTPUT_PATH    ${SBOL_RELEASE_DIR}         )

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

# build shared library for release
ADD_LIBRARY( sbol
	SHARED
	${SBOL_SOURCE_FILES}
)

# by default, GCC exports everything;
# this tells it to stick to SBOLAPIEXPORTS functions
IF(CMAKE_COMPILER_IS_GNUCC)
	SET_TARGET_PROPERTIES( sbol
		PROPERTIES COMPILE_FLAGS -fvisibility=hidden
	)
ENDIF()

# link against libxml
TARGET_LINK_LIBRARIES( sbol
	xml2
)

