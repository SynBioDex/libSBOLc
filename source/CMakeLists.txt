# set variables in source code
CONFIGURE_FILE(
	${SBOL_SOURCE_DIR}/constants.h.in
	${SBOL_SOURCE_DIR}/constants.h
)

# adjust paths
SET( SBOL_RELEASE_DIR       ${SBOL_RELEASE_DIR}/library )
SET( LIBRARY_OUTPUT_PATH    ${SBOL_RELEASE_DIR} )
SET( LIBXML2_STATICLIB_OUTPUT_PATH	${LIBRARY_OUTPUT_PATH} )
# the relative path for headers in the release directory should correspond to the ultimate install paths, depending on platform
IF( WIN32 )
   SET( HEADER_OUTPUT_PATH		${SBOL_RELEASE_DIR}/include/ )
ELSE()
   SET( HEADER_OUTPUT_PATH		${SBOL_RELEASE_DIR}/include/SBOL )
ENDIF()

# find/build libxml
IF( WIN32 )
	ADD_SUBDIRECTORY( libxml2 )
	SET( LIBXML2_INCLUDE_DIR ${SBOL_SOURCE_DIR}/libxml2/include )
ELSE()
	FIND_PACKAGE( LibXml2 )
ENDIF()
INCLUDE_DIRECTORIES( ${LIBXML2_INCLUDE_DIR} )
FILE(GLOB LIBXML2_HEADER_FILES ${LIBXML2_INCLUDE_DIR}/*)

# gather source files
FILE(GLOB SBOL_HEADER_FILES	${SBOL_SOURCE_DIR}/*.h)
FILE(GLOB SBOL_SOURCE_FILES	${SBOL_SOURCE_DIR}/*.c)

# copy header files to release/library/include for out-of-source build
# TODO: remove a couple of Makefiles contaminating the HEADER_OUTPUT_PATH
FILE(COPY ${LIBXML2_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )
FILE(COPY ${SBOL_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )

# build static library for release
IF( SBOL_BUILD_STATIC )
	ADD_LIBRARY( sbol
		STATIC 
		${SBOL_HEADER_FILES}
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
ELSE()  	# build shared library for release
	ADD_LIBRARY( sbol
		SHARED
		${SBOL_HEADER_FILES}
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
		xml2 )
	#target_link_libraries(sbol -Wl,-whole-archive -l${xml2} -l${ws2_32} -Wl,-no-whole-archive  )

ENDIF()
MESSAGE(${HEADER_OUTPUT_PATH})
INSTALL(TARGETS sbol DESTINATION lib)
INSTALL(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
