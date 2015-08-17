# SystemLibrary project
# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(targetname Core)

project(${targetname})

if(MSVC)
  add_definitions( -DNOMINMAX )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
endif(MSVC)

file(GLOB HEADER_FILES
  "include/*.h"
  "include/*.inl"
)

file(GLOB SOURCE_FILES
  "src/*.cpp"
  "src/*.hpp"
  "src/*.c"
  "src/*.inl"
  "src/*.h"
)

include_directories (
  "include"
)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})

add_library(${targetname} STATIC ${HEADER_FILES} ${SOURCE_FILES})

#if ( MSVC )
#  set_target_properties( ${targetname} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
#  set_target_properties( ${targetname} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH} )
#  set_target_properties( ${targetname} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
# etc for the other available configuration types (MinSizeRel, RelWithDebInfo)
#endif ( MSVC )

source_group(Header FILES ${HEADER_FILES})
source_group(Source FILES ${SOURCE_FILES})

