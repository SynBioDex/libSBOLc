# set schema file locations
CONFIGURE_FILE(
	${SBOL_SCHEMA_DIR}/rdf.xsd.in
	${SBOL_SCHEMA_DIR}/rdf.xsd
)
CONFIGURE_FILE(
	${SBOL_SCHEMA_DIR}/sbol.xsd.in
	${SBOL_SCHEMA_DIR}/sbol.xsd
)
