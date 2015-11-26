project( HeeksCAD )

add_definitions ( -Wall )
FIND_PACKAGE( wxWidgets REQUIRED COMPONENTS base core gl )

#look for OpenCASCADE
if( ${CASROOT} )
  add_definitions ( -DHAVE_CONFIG_H )
  set( OpenCASCADE_LIBRARIES ${CASROOT}/ )
  set( OpenCASCADE_INCLUDE_DIR ${CASROOT} )
endif()

include(${wxWidgets_USE_FILE})

include_directories ( SYSTEM
  ${OpenCASCADE_INCLUDE_DIR}
)

include_directories (
  ${CMAKE_SOURCE_DIR}
  ${wxWidgets_INCLUDE_DIRS}
  ${OSX_INCLUDE_DIRS}
)

# CMake summary
message (STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message (STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

#---------- put subdirs down here so that the package version vars above are visible to them -----------
#add_subdirectory( interface )
#add_subdirectory( tinyxml )
#add_subdirectory( translations )
add_subdirectory( src )  #needs libraries from other subdirs, so it goes last

