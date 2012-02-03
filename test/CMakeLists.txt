project( validate )
cmake_minimum_required( VERSION 2.6 )

set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules/" ${CMAKE_MODULE_PATH} )
find_package( LibXML++ REQUIRED )
include_directories( ${LibXML++_INCLUDE_DIRS} )
set( LIBS ${LIBS} ${LibXML++_LIBRARIES} )

add_executable( validate validate.cpp )

target_link_libraries( validate ${LIBS} )

