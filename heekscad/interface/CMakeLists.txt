cmake_minimum_required( VERSION 2.8 )

set( targetname heeksintf )

project( ${targetname} )

set(CMAKE_CXX_FLAGS_RELEASE "-Od -Ob1 -GF -Gy")
set(CMAKE_C_FLAGS_RELEASE "-Od -Ob1 -GF -Gy")

add_definitions( -DUSE_GENERIC_TREECTRL )
add_definitions( -DHEEKSCAD )
add_definitions( -D__WXMSW__ )
add_definitions( -DUNICODE -D_UNICODE )
add_definitions( -DNOPCH )
add_definitions( -DWNT )
add_definitions( -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE )
add_definitions( -D_SECURE_SCL=0 -D_SECURE_ATL=0 )
add_definitions( -D__WXMSW__ )
add_definitions( -D_MATH_DEFINES_DEFINED )
add_definitions( -DTIXML_USE_STL )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")

# wxWidgets
find_package( wxWidgets REQUIRED COMPONENTS base core gl )

# python libs
find_package( PythonLibs REQUIRED )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR}
                      ${CMAKE_CURRENT_SOURCE_DIR}/../src
                      ${PYTHON_INCLUDE_DIRS}
                      ${OpenCASCADE_INCLUDE_DIR}
                      ${wxWidgets_INCLUDE_DIRS}
                      ${libarea_INCLUDE_DIRS}
                    )

set( heeksintf_SRCS
    DoubleInput.cpp
    Geom.cpp
    HDialogs.cpp
    HeeksCADInterface.cpp
    HeeksColor.cpp
    HeeksObj.cpp
    HeeksObjDlg.cpp
    IdNamedObj.cpp
    IdNamedObjList.cpp
    LeftAndRight.cpp
    MarkedObject.cpp
    NiceTextCtrl.cpp
    ObjList.cpp
    PictureFrame.cpp
    PropertyCheck.cpp
    PropertyChoice.cpp
    PropertyColor.cpp
    PropertyDouble.cpp
    PropertyFile.cpp
    PropertyInt.cpp
    PropertyLength.cpp
    PropertyList.cpp
    PropertyString.cpp
    PropertyVertex.cpp
    ToolImage.cpp
    ToolList.cpp
    strconv.cpp
   )
   
set( heeksintf_HDRS
    Box.h
    DoubleInput.h
    Geom.h
    GripData.h
    GripperTypes.h
    HDialogs.h
    HeeksCADInterface.h
    HeeksColor.h
    HeeksObj.h
    HeeksObjDlg.h
    IdNamedObj.h
    IdNamedObjList.h
    InputMode.h
    LeftAndRight.h
    MarkedObject.h
    Material.h
    NiceTextCtrl.h
    NurbSurfaceParams.h
    ObjList.h
    Observer.h
    PictureFrame.h
    Plugin.h
    Property.h
    PropertyCheck.h
    PropertyChoice.h
    PropertyColor.h
    PropertyDouble.h
    PropertyFile.h
    PropertyInt.h
    PropertyLength.h
    PropertyList.h
    PropertyString.h
    PropertyVertex.h
    SketchOrder.h
    Tool.h
    ToolImage.h
    ToolList.h
    strconv.h
   )

add_library( ${targetname} STATIC ${heeksintf_SRCS} ${heeksintf_HDRS} )

set_target_properties( ${targetname} PROPERTIES SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH} )
set_target_properties( ${targetname} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS" )