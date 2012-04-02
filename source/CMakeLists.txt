# find/build libxml
IF( WIN32 )
	ADD_SUBDIRECTORY( libxml2 )
	SET( LIBXML2_INCLUDE_DIR ${SBOL_SOURCE_DIR}/libxml2/include )
ELSE()
	FIND_PACKAGE( LibXml2 )
ENDIF()
INCLUDE_DIRECTORIES( ${LIBXML2_INCLUDE_DIR} )

# set variables
CONFIGURE_FILE(
	${SBOL_SOURCE_DIR}/constants.h.in
	${SBOL_SOURCE_DIR}/constants.h
)

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

TARGET_LINK_LIBRARIES( sbol
	xml2
)

# build another library for internal use
# (lets SWIG and the test suites access non-SBOLAPIEXPORTS functions)
ADD_LIBRARY( sbol_internal
    STATIC
	${SBOL_SOURCE_FILES}
)
TARGET_LINK_LIBRARIES( sbol_internal
	xml2
)
