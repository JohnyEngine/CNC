project(OpenCamLib)

cmake_minimum_required(VERSION 2.4)

#if(MSVC)
  add_definitions( -D__BOOST_PYTHON_NO_LIB__ )
  add_definitions( -DBOOST_PYTHON_STATIC_LIB=1 )
  add_definitions( -DBOOST_LIB_DIAGNOSTIC )
  add_definitions( -DUNICODE -D_UNICODE )
  add_definitions( -D_USRDLL )
  add_definitions( -DOPENCAMLIB_EXPORTS )

#endif(MSVC)

include_directories (
  ${Boost_INCLUDE_DIRS} 
  ${PYTHON_INCLUDE_DIRS}
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

link_directories( ${Boost_LIBRARY_DIRS} )

# find OpenMP
#find_package( OpenMP REQUIRED )

#IF (OPENMP_FOUND)
#    MESSAGE(STATUS "found OpenMP, compiling with flags: " ${OpenMP_CXX_FLAGS} )
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#ENDIF(OPENMP_FOUND)


IF(EXISTS ${OpenCamLib_SOURCE_DIR}/version_string.hpp)
    file(STRINGS "${OpenCamLib_SOURCE_DIR}/version_string.hpp" OpenCamLib_BUILD_SPECIFICATION REGEX "^[ \t]*#define[ \t]+VERSION_STRING[ \t]+.*$")
    if(OpenCamLib_BUILD_SPECIFICATION)
      string(REGEX REPLACE ".*#define[ \t]+VERSION_STRING[ \t]+\"(.*)\".*" "\\1" MY_VERSION ${OpenCamLib_BUILD_SPECIFICATION})
    else()
        message(FATAL_ERROR "Data were not found for the required build specification.")
    endif()
    SET(version_string ${OpenCamLib_SOURCE_DIR}/version_string.hpp)
ENDIF(EXISTS ${OpenCamLib_SOURCE_DIR}/version_string.hpp)

MESSAGE(STATUS "OpenCamLib version: ${MY_VERSION}")

# this defines the source-files
set(OCL_GEO_SRC
    ${OpenCamLib_SOURCE_DIR}/geo/arc.cpp
    ${OpenCamLib_SOURCE_DIR}/geo/bbox.cpp
    ${OpenCamLib_SOURCE_DIR}/geo/ccpoint.cpp
    ${OpenCamLib_SOURCE_DIR}/geo/clpoint.cpp
    ${OpenCamLib_SOURCE_DIR}/geo/line.cpp
    ${OpenCamLib_SOURCE_DIR}/geo/path.cpp
    ${OpenCamLib_SOURCE_DIR}/geo/point.cpp
    ${OpenCamLib_SOURCE_DIR}/geo/stlreader.cpp
    ${OpenCamLib_SOURCE_DIR}/geo/stlsurf.cpp
    ${OpenCamLib_SOURCE_DIR}/geo/triangle.cpp
)

set(OCL_CUTTER_SRC
    ${OpenCamLib_SOURCE_DIR}/cutters/ballcutter.cpp
    ${OpenCamLib_SOURCE_DIR}/cutters/bullcutter.cpp
    ${OpenCamLib_SOURCE_DIR}/cutters/compositecutter.cpp
    ${OpenCamLib_SOURCE_DIR}/cutters/conecutter.cpp
    ${OpenCamLib_SOURCE_DIR}/cutters/millingcutter.cpp
    ${OpenCamLib_SOURCE_DIR}/cutters/cylcutter.cpp
    ${OpenCamLib_SOURCE_DIR}/cutters/ellipse.cpp
    ${OpenCamLib_SOURCE_DIR}/cutters/ellipseposition.cpp
)

set(OCL_DROPCUTTER_SRC
    ${OpenCamLib_SOURCE_DIR}/dropcutter/batchdropcutter.cpp
    ${OpenCamLib_SOURCE_DIR}/dropcutter/pointdropcutter.cpp
    ${OpenCamLib_SOURCE_DIR}/dropcutter/pathdropcutter.cpp
    ${OpenCamLib_SOURCE_DIR}/dropcutter/adaptivepathdropcutter.cpp
)

set(OCL_ALGO_SRC
    ${OpenCamLib_SOURCE_DIR}/algo/batchpushcutter.cpp
    ${OpenCamLib_SOURCE_DIR}/algo/fiberpushcutter.cpp
    ${OpenCamLib_SOURCE_DIR}/algo/interval.cpp
    ${OpenCamLib_SOURCE_DIR}/algo/fiber.cpp
    ${OpenCamLib_SOURCE_DIR}/algo/waterline.cpp
    ${OpenCamLib_SOURCE_DIR}/algo/adaptivewaterline.cpp
    ${OpenCamLib_SOURCE_DIR}/algo/weave.cpp
    ${OpenCamLib_SOURCE_DIR}/algo/simple_weave.cpp
    ${OpenCamLib_SOURCE_DIR}/algo/smart_weave.cpp
)


set(OCL_COMMON_SRC
    ${OpenCamLib_SOURCE_DIR}/common/numeric.cpp
    ${OpenCamLib_SOURCE_DIR}/common/lineclfilter.cpp
)

set( OCL_INCLUDE_FILES  
    ${OpenCamLib_SOURCE_DIR}/geo/arc.hpp
    ${OpenCamLib_SOURCE_DIR}/geo/bbox.hpp
    ${OpenCamLib_SOURCE_DIR}/geo/ccpoint.hpp
    ${OpenCamLib_SOURCE_DIR}/geo/clpoint.hpp
    ${OpenCamLib_SOURCE_DIR}/geo/line.hpp
    ${OpenCamLib_SOURCE_DIR}/geo/path.hpp
    ${OpenCamLib_SOURCE_DIR}/geo/stlreader.hpp
    ${OpenCamLib_SOURCE_DIR}/geo/stlsurf.hpp
    ${OpenCamLib_SOURCE_DIR}/geo/triangle.hpp
    ${OpenCamLib_SOURCE_DIR}/geo/point.hpp
    
    ${OpenCamLib_SOURCE_DIR}/cutters/ballcutter.hpp
    ${OpenCamLib_SOURCE_DIR}/cutters/bullcutter.hpp
    ${OpenCamLib_SOURCE_DIR}/cutters/compositecutter.hpp
    ${OpenCamLib_SOURCE_DIR}/cutters/conecutter.hpp
    ${OpenCamLib_SOURCE_DIR}/cutters/cylcutter.hpp
    ${OpenCamLib_SOURCE_DIR}/cutters/ellipseposition.hpp
    ${OpenCamLib_SOURCE_DIR}/cutters/millingcutter.hpp
    ${OpenCamLib_SOURCE_DIR}/cutters/ellipse.hpp
    
    ${OpenCamLib_SOURCE_DIR}/dropcutter/adaptivepathdropcutter.hpp
    ${OpenCamLib_SOURCE_DIR}/dropcutter/pathdropcutter.hpp
    ${OpenCamLib_SOURCE_DIR}/dropcutter/batchdropcutter.hpp
    ${OpenCamLib_SOURCE_DIR}/dropcutter/pointdropcutter.hpp
    
    ${OpenCamLib_SOURCE_DIR}/common/brent_zero.hpp
    ${OpenCamLib_SOURCE_DIR}/common/kdnode.hpp
    ${OpenCamLib_SOURCE_DIR}/common/kdtree.hpp
    ${OpenCamLib_SOURCE_DIR}/common/numeric.hpp
    ${OpenCamLib_SOURCE_DIR}/common/lineclfilter.hpp
    ${OpenCamLib_SOURCE_DIR}/common/clfilter.hpp
    ${OpenCamLib_SOURCE_DIR}/common/halfedgediagram.hpp

    
    ${OpenCamLib_SOURCE_DIR}/algo/operation.hpp
    ${OpenCamLib_SOURCE_DIR}/algo/batchpushcutter.hpp
    ${OpenCamLib_SOURCE_DIR}/algo/fiberpushcutter.hpp
    ${OpenCamLib_SOURCE_DIR}/algo/fiber.hpp
    ${OpenCamLib_SOURCE_DIR}/algo/interval.hpp
    ${OpenCamLib_SOURCE_DIR}/algo/waterline.hpp
    ${OpenCamLib_SOURCE_DIR}/algo/adaptivewaterline.hpp
    ${OpenCamLib_SOURCE_DIR}/algo/weave.hpp
    ${OpenCamLib_SOURCE_DIR}/algo/simple_weave.hpp
    ${OpenCamLib_SOURCE_DIR}/algo/smart_weave.hpp
    ${OpenCamLib_SOURCE_DIR}/algo/weave_typedef.hpp
    ${OpenCamLib_SOURCE_DIR}/algo/tsp.hpp

	${OpenCamLib_SOURCE_DIR}/../Windows/stdafx.h
	${OpenCamLib_SOURCE_DIR}/../Windows/targetver.h
    
    ${version_string}

)

set(OCL_LIRARY_SRC
    ${OpenCamLib_SOURCE_DIR}/ocl_cutters.cpp
    ${OpenCamLib_SOURCE_DIR}/ocl_geometry.cpp
    ${OpenCamLib_SOURCE_DIR}/ocl_algo.cpp
    ${OpenCamLib_SOURCE_DIR}/ocl_dropcutter.cpp
    ${OpenCamLib_SOURCE_DIR}/ocl.cpp
    ${OpenCamLib_SOURCE_DIR}/../Windows/dllmain.cpp
	${OpenCamLib_SOURCE_DIR}/../Windows/OpenCamLib.cpp
	${OpenCamLib_SOURCE_DIR}/../Windows/stdafx.cpp
	${OpenCamLib_SOURCE_DIR}/../Windows/stdafx.h
)

# include dirs
include_directories( ${OpenCamLib_SOURCE_DIR}/cutters )
include_directories( ${OpenCamLib_SOURCE_DIR}/geo )
include_directories( ${OpenCamLib_SOURCE_DIR}/algo )
include_directories( ${OpenCamLib_SOURCE_DIR}/dropcutter )
include_directories( ${OpenCamLib_SOURCE_DIR}/common )
include_directories( ${OpenCamLib_SOURCE_DIR} )

link_directories( ${Boost_LIBRARY_DIRS} )

add_library(
	ocl
	SHARED
	${OCL_LIRARY_SRC}
	${OCL_GEO_SRC}
	${OCL_CUTTER_SRC}
	${OCL_ALGO_SRC}
	${OCL_DROPCUTTER_SRC}
	${OCL_COMMON_SRC}
)

target_link_libraries( ocl ${PYTHON_LIBRARIES})

set_target_properties(ocl PROPERTIES PREFIX "") 
set_target_properties(ocl PROPERTIES SUFFIX ".pyd")
set_target_properties(ocl PROPERTIES VERSION ${MY_VERSION}) 
set_target_properties(ocl PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")	


