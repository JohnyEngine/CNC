cmake_minimum_required( VERSION 2.8 )

set( targetname HeeksCNC )

project( ${targetname} )

SET(CMAKE_CXX_FLAGS_RELEASE "-Od -Ob1 -GF -Gy")
SET(CMAKE_C_FLAGS_RELEASE "-Od -Ob1 -GF -Gy")

add_definitions( -DUSE_GENERIC_TREECTRL )
add_definitions( -D__WXMSW__ )
add_definitions( -DUNICODE -D_UNICODE )
add_definitions( -DNOPCH )
add_definitions( -DWNT )
add_definitions( -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE )
add_definitions( -D_SECURE_SCL=0 -D_SECURE_ATL=0 )
add_definitions( -D_MATH_DEFINES_DEFINED )
add_definitions( -DTIXML_USE_STL )
add_definitions( -DHEEKSPLUGIN )
add_definitions( -DHEEKSCNC )
add_definitions( -DOPEN_SOURCE_GEOMETRY )
add_definitions( -DWXUSINGDLL )
add_definitions( -DSTABLE_OPS_ONLY )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")

include_directories (
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${OpenCASCADE_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${wxWidgets_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/heekscad
    ${CMAKE_SOURCE_DIR}/heekscad/src
	${CMAKE_SOURCE_DIR}/heekscad/interface
	${CMAKE_SOURCE_DIR}/heekscad/tinyxml
    )

set( platform_SRCS dllmain.cpp stdafx.cpp )

set( HeeksCAD_SRC_DIR ${CMAKE_SOURCE_DIR}/heekscad )

set( heekscad_SRCS
    ${HeeksCAD_SRC_DIR}/interface/Geom.cpp
    ${HeeksCAD_SRC_DIR}/interface/HDialogs.cpp
    ${HeeksCAD_SRC_DIR}/interface/HeeksColor.cpp
    ${HeeksCAD_SRC_DIR}/interface/HeeksObj.cpp
    ${HeeksCAD_SRC_DIR}/interface/HeeksObjDlg.cpp
    ${HeeksCAD_SRC_DIR}/interface/IdNamedObj.cpp
    ${HeeksCAD_SRC_DIR}/interface/IdNamedObjList.cpp
    ${HeeksCAD_SRC_DIR}/interface/LeftAndRight.cpp
    ${HeeksCAD_SRC_DIR}/interface/MarkedObject.cpp
    ${HeeksCAD_SRC_DIR}/interface/NiceTextCtrl.cpp
    ${HeeksCAD_SRC_DIR}/interface/ObjList.cpp
    ${HeeksCAD_SRC_DIR}/interface/PictureFrame.cpp
    ${HeeksCAD_SRC_DIR}/interface/PropertyCheck.cpp
    ${HeeksCAD_SRC_DIR}/interface/PropertyChoice.cpp
    ${HeeksCAD_SRC_DIR}/interface/PropertyColor.cpp
    ${HeeksCAD_SRC_DIR}/interface/PropertyDouble.cpp
    ${HeeksCAD_SRC_DIR}/interface/PropertyFile.cpp
    ${HeeksCAD_SRC_DIR}/interface/PropertyInt.cpp
    ${HeeksCAD_SRC_DIR}/interface/PropertyLength.cpp
    ${HeeksCAD_SRC_DIR}/interface/PropertyList.cpp
    ${HeeksCAD_SRC_DIR}/interface/PropertyString.cpp
    ${HeeksCAD_SRC_DIR}/interface/PropertyVertex.cpp
    ${HeeksCAD_SRC_DIR}/interface/ToolImage.cpp
    ${HeeksCAD_SRC_DIR}/interface/strconv.cpp
    )

set( heekscnc_HDRS
    CNCPoint.h
    CTool.h
    CToolDlg.h
    DepthOp.h
    DepthOpDlg.h
    Drilling.h
    DrillingDlg.h
    Excellon.h
    HeeksCNC.h
    HeeksCNCInterface.h
    HeeksCNCTypes.h
    Interface.h
    NCCode.h
    Op.h
    OpDlg.h
    Operations.h
    OutputCanvas.h
    Pattern.h
    PatternDlg.h
    Patterns.h
    Pocket.h
    PocketDlg.h
    Profile.h
    ProfileDlg.h
    Program.h
    ProgramCanvas.h
    ProgramDlg.h
    PythonString.h
    PythonStuff.h
    Reselect.h
    ScriptOp.h
    ScriptOpDlg.h
    Simulate.h
    SketchOp.h
    SketchOpDlg.h
    SolidsDlg.h
    SpeedOp.h
    SpeedOpDlg.h
    Stock.h
    StockDlg.h
    Stocks.h
    Surface.h
    SurfaceDlg.h
    Surfaces.h
    Tag.h
    Tags.h
    Tools.h
    stdafx.h
   )

set( heekscnc_SRCS
    CNCPoint.cpp
    CTool.cpp
    CToolDlg.cpp
    DepthOp.cpp
    DepthOpDlg.cpp
    Drilling.cpp
    DrillingDlg.cpp
    Excellon.cpp
    HeeksCNC.cpp
    HeeksCNCInterface.cpp
    Interface.cpp
    NCCode.cpp
    Op.cpp
    OpDlg.cpp
    Operations.cpp
    OutputCanvas.cpp
    Pattern.cpp
    PatternDlg.cpp
    Patterns.cpp
    Pocket.cpp
    PocketDlg.cpp
    Profile.cpp
    ProfileDlg.cpp
    Program.cpp
    ProgramCanvas.cpp
    ProgramDlg.cpp
    PythonString.cpp
    PythonStuff.cpp
    Reselect.cpp
    ScriptOp.cpp
    ScriptOpDlg.cpp
    Simulate.cpp
    SketchOp.cpp
    SketchOpDlg.cpp
    SolidsDlg.cpp
    SpeedOp.cpp
    SpeedOpDlg.cpp
    Stock.cpp
    StockDlg.cpp
    Stocks.cpp
    Surface.cpp
    SurfaceDlg.cpp
    Surfaces.cpp
    Tag.cpp
    Tags.cpp
    Tools.cpp
    stdafx.cpp
   )

link_directories( ${CMAKE_SOURCE_DIR}/lib ${OpenCASCADE_LINK_DIRECTORY} ${wxWidgets_LIB_DIR} )
   
add_library( ${targetname} SHARED ${heekscnc_SRCS} ${heekscad_SRCS} ${platform_SRCS} )
target_link_libraries( ${targetname} 
					   ${OpenCASCADE_LIBRARIES}
                       ${OPENGL_LIBRARIES} 
					   wxmsw28u_core
					   wxmsw28u_aui
					   wxmsw28u_gl
					   wxbase28u
					   heekstinyxml )
set_target_properties( ${targetname} PROPERTIES SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH} )
set_target_properties( ${targetname} PROPERTIES LINK_FLAGS -Wl,-Bsymbolic-functions )
set_target_properties( ${targetname} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS" )

