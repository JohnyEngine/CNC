cmake_minimum_required( VERSION 2.8 )

set( targetname HeeksCAD )

project( ${targetname} )

SET(CMAKE_CXX_FLAGS_RELEASE "-Od -Ob1 -GF -Gy")
SET(CMAKE_C_FLAGS_RELEASE "-Od -Ob1 -GF -Gy")


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

#find OCE or OpenCASCADE
set( CASCADE_LIBS TKBRep TKIGES TKSTEP TKXSBase TKBool TKernel TKFillet TKG2d TKG3d TKGeomAlgo TKGeomBase TKMath TKOffset TKPrim TKTopAlgo TKV3d TKMesh TKBO )
set( CASCADE_NOTUSED_LIBS TKPShape TKShHealing TKLCAF TKFeat TKXCAF TKHLR TKPLCAF TKSTL TKSTEP209 TKAdvTools TKCAF TKV2d TKVRML TKXCAFSchema TKXDESTEP TKSTEPAttr FWOSPlugin TKSTEPBase TKService TKShapeSchema TKCDF )

find_package( OpenGL REQUIRED )
find_package( wxWidgets REQUIRED COMPONENTS base core gl aui )
find_package( PythonLibs REQUIRED )

include(${wxWidgets_USE_FILE})

include_directories ( SYSTEM
    ${OpenCASCADE_INCLUDE_DIR}
    )

include_directories (
    ${PYTHON_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${wxWidgets_INCLUDE_DIRS}
    ${libarea_INCLUDE_DIRS}
    )

set( heekscad_HDRS
    AboutBox.h
    AutoSave.h
    BezierCurve.h
    Cone.h
    ConversionTools.h
    CoordinateSystem.h
    CorrelationTool.h
    Cuboid.h
    Cylinder.h
    DigitizeMode.h
    DigitizedPoint.h
    DimensionDrawing.h
    Drawing.h
    Edge.h
    EndedObject.h
    Face.h
    FaceTools.h
    FastCurves.h
    GLList.h
    GraphicsCanvas.h
    Grid.h
    Gripper.h
    GripperSelTransform.h
    Group.h
    HAngularDimension.h
    HArc.h
    HArea.h
    HCircle.h
    HDimension.h
    HDxf.h
    HEllipse.h
    HGear.h
    HILine.h
    HImage.h
    HLine.h
    HPoint.h
    HSpline.h
    HText.h
    HXml.h
    HeeksCAD.h
    HeeksConfig.h
    HeeksFrame.h
    HeeksPrintout.h
    History.h
    Index.h
    InputModeCanvas.h
    Intersector.h
    LineArcDrawing.h
    Loop.h
    MagDragWindow.h
    MarkedList.h
    ObjPropsCanvas.h
    OptionsCanvas.h
    OrientationModifier.h
    Plugins.h
    PointDrawing.h
    PointOrWindow.h
    PropertiesCanvas.h
    PropertyChange.h
    PropertyTrsf.h
    RegularShapesDrawing.h
    RemoveOrAddTool.h
    RuledSurface.h
    Ruler.h
    Sectioning.h
    SelectMode.h
    Shape.h
    ShapeData.h
    ShapeTools.h
    Sketch.h
    Solid.h
    SolidTools.h
    Sphere.h
    StlSolid.h
    StretchTool.h
    TransformTool.h
    TransformTools.h
    TreeCanvas.h
    Vertex.h
    ViewPanning.h
    ViewPoint.h
    ViewRotating.h
    ViewZooming.h
    Window.h
    Wire.h
    advprops.h
    dxf.h
    glfont2.h
    manager.h
    odcombo.h
    propdev.h
    propgrid.h
    stdafx.h
    svg.h
    wxImageLoader.h
    )

set( heekscad_SRCS
    AboutBox.cpp
    AutoSave.cpp
    BezierCurve.cpp
    Cone.cpp
    ConversionTools.cpp
    CoordinateSystem.cpp
    CorrelationTool.cpp
    Cuboid.cpp
    CxfFont.cpp
    Cylinder.cpp
    DigitizeMode.cpp
    DigitizedPoint.cpp
    DimensionDrawing.cpp
    Drawing.cpp
    Edge.cpp
    EndedObject.cpp
    ExitMainLoop.cpp
    Face.cpp
    FaceTools.cpp
    FastCurves.cpp
    GLList.cpp
    GraphicsCanvas.cpp
    Grid.cpp
    Gripper.cpp
    GripperSelTransform.cpp
    Group.cpp
    HAngularDimension.cpp
    HArc.cpp
    HArea.cpp
    HCircle.cpp
    HDimension.cpp
    HDxf.cpp
    HEllipse.cpp
    HGear.cpp
    HILine.cpp
    HImage.cpp
    HLine.cpp
    HPoint.cpp
    HSpline.cpp
    HText.cpp
    HXml.cpp
    HeeksCAD.cpp
    HeeksFrame.cpp
    HeeksPrintout.cpp
    History.cpp
    Input.cpp
    InputModeCanvas.cpp
    LineArcDrawing.cpp
    Loop.cpp
    MagDragWindow.cpp
    MarkedList.cpp
    ObjPropsCanvas.cpp
    OptionsCanvas.cpp
    OrientationModifier.cpp
    Plugins.cpp
    PointDrawing.cpp
    PointOrWindow.cpp
    PropertiesCanvas.cpp
    PropertyChange.cpp
    PropertyTrsf.cpp
    RS274X.cpp
    RegularShapesDrawing.cpp
    RemoveOrAddTool.cpp
    RuledSurface.cpp
    Ruler.cpp
    Sectioning.cpp
    SelectMode.cpp
    Shape.cpp
    ShapeData.cpp
    ShapeTools.cpp
    Sketch.cpp
    Solid.cpp
    SolidTools.cpp
    Sphere.cpp
    StlSolid.cpp
    StretchTool.cpp
    TransformTool.cpp
    TransformTools.cpp
    TreeCanvas.cpp
    Vertex.cpp
    ViewPanning.cpp
    ViewPoint.cpp
    ViewRotating.cpp
    ViewZooming.cpp
    Window.cpp
    Wire.cpp
    advprops.cpp
    dxf.cpp
    glfont2.cpp
    manager.cpp
    odcombo.cpp
    propgrid.cpp
    props.cpp
    stdafx.cpp
    svg.cpp
    wxImageLoader.cpp
    )

link_directories( ${CMAKE_SOURCE_DIR}/lib ${OpenCASCADE_LIBRARY_DIR} )

add_executable( ${targetname} ${heekscad_SRCS} ${heekscad_HDRS} ${platform_SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/HeeksCAD.rc)

target_link_libraries( ${targetname}
                       ${wxWidgets_LIBRARIES} ${CASCADE_LIBS}
                       ${OPENGL_LIBRARIES} ${PYTHON_LIBRARIES}
                       heekstinyxml libarea heeksintf)

set_target_properties( ${targetname} PROPERTIES VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH} )
set_target_properties( ${targetname} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS" )