cmake_minimum_required( VERSION 2.8 )

project( heekstinyxml )

SET(CMAKE_CXX_FLAGS_RELEASE "-Od -Ob1 -GF -Gy")
SET(CMAKE_C_FLAGS_RELEASE "-Od -Ob1 -GF -Gy")

add_definitions( -DHEEKSCAD )
add_definitions( -DTIXML_USE_STL )
add_definitions( -DUNICODE -D_UNICODE )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")

include_directories (
    ${CMAKE_SOURCE_DIR}
    ${PYTHON_INCLUDE_DIRS}
)

set( heekstinyxml_SRCS
  tinystr.cpp
  tinyxml.cpp
  tinyxmlerror.cpp
  tinyxmlparser.cpp
)

set( heekstinyxml_HDRS
  tinystr.h
  tinyxml.h
)

add_library( heekstinyxml STATIC ${heekstinyxml_SRCS} ${heekstinyxml_HDRS} )

target_link_libraries( heekstinyxml ${PYTHON_LIBRARIES} )

set_target_properties( heekstinyxml PROPERTIES SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH} )
set_target_properties(${targetname} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")