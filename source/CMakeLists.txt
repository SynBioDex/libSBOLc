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

# build library
ADD_LIBRARY( sbol
    ${SBOL_LIBRARY_TYPE}
	${SBOL_SOURCE_FILES}
)
TARGET_LINK_LIBRARIES( sbol
	xml2
)
