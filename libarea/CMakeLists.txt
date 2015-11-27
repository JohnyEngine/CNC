cmake_minimum_required(VERSION 2.8)

set(targetname libarea)

project(${targetname})

SET(CMAKE_CXX_FLAGS_RELEASE "-Od -Ob1 -GF -Gy")
SET(CMAKE_C_FLAGS_RELEASE "-Od -Ob1 -GF -Gy")

add_definitions( -DHAVE_ROUND )
add_definitions( -D__BOOST_PYTHON_NO_LIB__ )
add_definitions( -DBOOST_PYTHON_STATIC_LIB=1 )
add_definitions( -DBOOST_LIB_DIAGNOSTIC )
add_definitions( -DUNICODE -D_UNICODE )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")

include_directories(${Python_Includes})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# this defines the source-files for library
set(AREA_SRC_COMMON
    Arc.cpp
    Area.cpp
    AreaDxf.cpp
    AreaOrderer.cpp
    AreaPocket.cpp
    Circle.cpp
    Curve.cpp
    dxf.cpp

    kurve/Construction.cpp
    kurve/Finite.cpp
    kurve/kurve.cpp
    kurve/Matrix.cpp
    kurve/offset.cpp
)

set(AREA_SRC_KBOOL
    kbool/src/booleng.cpp
    kbool/src/record.cpp
    kbool/src/scanbeam.cpp
    kbool/src/graph.cpp
    kbool/src/graphlst.cpp
    kbool/src/instonly.cpp
    kbool/src/line.cpp
    kbool/src/link.cpp
    kbool/src/lpoint.cpp
    kbool/src/node.cpp
)

set(AREA_SRC_CLIPPER
    AreaClipper.cpp

    clipper.cpp
)

# this defines the additional source-files for python module (wrapper to libarea)
set(PYAREA_SRC
    PythonStuff.cpp
)

# include directories
include_directories( 
    kurve/
    kbool/src/
)

add_library(
  ${targetname}
  STATIC
  ${AREA_SRC_COMMON}
  ${AREA_SRC_KBOOL}
  ${AREA_SRC_CLIPPER}
)

set_target_properties(${targetname} PROPERTIES PREFIX "")
set_target_properties(${targetname} PROPERTIES SOVERSION 0)
set_target_properties(${targetname} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
