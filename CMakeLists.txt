cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(CAMBOT)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/Build/)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(CMAKE_BINARY_DIR  ${dir})
set(EXECUTABLE_OUTPUT_PATH ${dir})
set(LIBRARY_OUTPUT_PATH ${dir})
set(CMAKE_CACHEFILE_DIR ${dir})


add_subdirectory(core)
add_subdirectory(controller)
add_subdirectory(client)
add_subdirectory(examples/test1)


if(MSVC)
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET Core PROPERTY FOLDER "System")
	SET_PROPERTY(TARGET Controller PROPERTY FOLDER "CAMBot")
	SET_PROPERTY(TARGET Client PROPERTY FOLDER "CAMBot")
endif(MSVC)