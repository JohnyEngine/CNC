# SystemLibrary project
# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Core)
SET(${PROJECT_NAME} 1.0)

if(MSVC)
	add_definitions( -DNOMINMAX )
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
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

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

source_group(Header FILES ${HEADER_FILES})
source_group(Source FILES ${SOURCE_FILES})

