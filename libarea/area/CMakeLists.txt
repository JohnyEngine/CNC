set(targetname area)

project(${targetname})

cmake_minimum_required(VERSION 2.4)

#if(MSVC)
  add_definitions( -DHAVE_ROUND )
  add_definitions( -D__BOOST_PYTHON_NO_LIB__ )
  add_definitions( -DBOOST_PYTHON_STATIC_LIB=1 )
  add_definitions( -DBOOST_LIB_DIAGNOSTIC )
  add_definitions( -DUNICODE )
  add_definitions( -D_USRDLL )
  add_definitions( -D_CRT_SECURE_NO_WARNINGS )
  add_definitions( -DAREA_EXPORTS )
#endif(MSVC)

# this defines the source-files for library
set(AREA_SRC_COMMON
  ../Arc.cpp
  ../Area.cpp
  ../AreaDxf.cpp
  ../AreaOrderer.cpp
  ../AreaPocket.cpp
  ../Circle.cpp
  ../Curve.cpp
  ../dxf.cpp

  ../kurve/Construction.cpp
  ../kurve/Finite.cpp
  ../kurve/kurve.cpp
  ../kurve/Matrix.cpp
  ../kurve/offset.cpp
)

set(AREA_SRC_KBOOL
  ../AreaBoolean.cpp

  ../kbool/src/booleng.cpp
  ../kbool/src/record.cpp
  ../kbool/src/scanbeam.cpp
  ../kbool/src/graph.cpp
  ../kbool/src/graphlst.cpp
  ../kbool/src/instonly.cpp
  ../kbool/src/line.cpp
  ../kbool/src/link.cpp
  ../kbool/src/lpoint.cpp
  ../kbool/src/node.cpp
)

# this defines the additional source-files for python module (wrapper to libarea)
set(PYAREA_SRC
  ../PythonStuff.cpp
)

# include directories
include_directories (
  ${Boost_INCLUDE_DIRS}
  ${PYTHON_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/../
  ../kurve/
  ../kbool/src/
)

link_directories( ${Boost_LIBRARY_DIRS} )

add_library(
  ${targetname}
  SHARED
  ${AREA_SRC_COMMON}
  ${AREA_SRC_KBOOL}
  ${PYAREA_SRC}
)


set_target_properties(${targetname} PROPERTIES SUFFIX ".pyd")
set_target_properties(${targetname} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

target_link_libraries(${targetname} ${PYTHON_LIBRARIES})
set_target_properties(${targetname} PROPERTIES PREFIX "") 
