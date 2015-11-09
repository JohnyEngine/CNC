# SystemLibrary project
# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(e3d)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0")
endif(MSVC)

add_definitions(-DHAVE_STRERROR -DHAVE_FLOAT_H -D_CRT_SECURE_NO_WARNINGS)

file(GLOB HEADER_FILES
	"popt/include/*.h"
	"*.h"
)

file(GLOB SOURCE_FILES
	"popt/src/*.c"
	"*.c"
)

include_directories (
	"popt/include"
)

add_executable(${PROJECT_NAME} WIN32 ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME}  PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")

source_group(Header FILES ${HEADER_FILES})
source_group(Source FILES ${SOURCE_FILES})

