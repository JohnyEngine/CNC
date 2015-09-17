cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(CAMBOT)

set(BOOST_INCLUDEDIR D:/boost/)
set(BOOST_LIBRARYDIR ${BOOST_INCLUDEDIR}lib32-msvc-12.0/)
set(BOOST_ROOT ${BOOST_INCLUDEDIR}boost/)

MESSAGE(STATUS "Boost root: " ${BOOST_ROOT})
MESSAGE(STATUS "Boost incude: " ${BOOST_INCLUDEDIR})
MESSAGE(STATUS "Boost lib is: " ${BOOST_LIBRARYDIR})

# find BOOST and boost-python
find_package( Boost COMPONENTS python REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
    MESSAGE(STATUS "found Boost: " ${Boost_LIB_VERSION})
    MESSAGE(STATUS "boost-incude dirs are: " ${Boost_INCLUDE_DIRS})
    MESSAGE(STATUS "boost-python lib is: " ${Boost_PYTHON_LIBRARY})
    MESSAGE(STATUS "boost_LIBRARY_DIRS is: " ${Boost_LIBRARY_DIRS})
    MESSAGE(STATUS "Boost_LIBRARIES is: " ${Boost_LIBRARIES})    
endif()

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