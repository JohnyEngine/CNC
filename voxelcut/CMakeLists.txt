# Voxel sculpting program project
# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(targetname voxelcut)

project(${targetname} CXX ASM_MASM)

#if(MSVC)
  add_definitions( -DHAVE_ROUND )
  add_definitions( -D__BOOST_PYTHON_NO_LIB__ )
  add_definitions( -DBOOST_PYTHON_STATIC_LIB=1 )
  add_definitions( -DBOOST_LIB_DIAGNOSTIC )
  add_definitions( -DUNICODE -D_UNICODE )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
#endif(MSVC)

file(GLOB HEADER_FILES
  "msvc.h"
  "PythonStuff.h"
  "SolidView.h"
  "sysmain.h"
  "voxlap5.h"
)

file(GLOB SOURCE_FILES
  "kplib.cpp"
  "PythonStuff.cpp"
  "SolidView.cpp"
  "VoxelCut.cpp"
  "voxlap5.cpp"
  "winmain.cpp"
)

file(GLOB ASM_FILES
  "v5.asm"
)

include_directories (
  ${Boost_INCLUDE_DIRS} 
  ${PYTHON_INCLUDE_DIRS}
)

link_directories( ${Boost_LIBRARY_DIRS} )

SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")

add_library(${targetname} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${ASM_FILES} )

target_link_libraries( ${targetname} ${PYTHON_LIBRARIES} ddraw.lib)

#add_custom_command(target your_target_name
#                   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy ${EXAMPLE_BIN_NAME} ${PROJECT_BINARY_DIR}/.
#)

set_target_properties(${targetname} PROPERTIES SUFFIX ".pyd")
set_target_properties(${targetname} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

if ( MSVC )
  SET_SOURCE_FILES_PROPERTIES(${ASM_FILES} PROPERTIES LANGUAGE ASM_MASM)
  SET_SOURCE_FILES_PROPERTIES(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)
endif ( MSVC )

source_group(Header FILES ${HEADER_FILES})
source_group(Source FILES ${SOURCE_FILES} ${ASM_FILES})

