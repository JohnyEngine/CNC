rem set HEEKSCADPATH=D:\HeeksCAD
rem set HEEKSCADSOURCEPATH=D:\GitHub\CNC\heekscad
rem set WXBINARIESPATH=D:\wxWidgets\lib\vc_dll
rem set OPENCASCADEBINPATH=D:\OpenCASCADE\opencascade-6.9.1\win32\vc12\bin
rem set TBBBINPATH=D:\OpenCASCADE\tbb44_20150728oss\bin\ia32\vc12
rem set FREEIMAGEBINPATH=D:\OpenCASCADE\freeimage-3.17.0-vc12-32\bin
rem set FREETYPEBINPATH=D:\OpenCASCADE\freetype-2.5.5-vc12-32\bin
rem set HEEKSCADPATH=D:\HeeksCAD
rem set HEEKSCADSOURCEPATH=D:\GitHub\CNC\heekscad
rem set GETTEXTPATH=D:\insttools\gettext

mkdir "%HEEKSCADPATH%"
rem Translation
mkdir "%HEEKSCADPATH%\de"
"%GETTEXTPATH%\msgfmt.exe" -o "%HEEKSCADPATH%\de\HeeksCAD.mo" "%HEEKSCADSOURCEPATH%\translations\de\HeeksCAD.po"
mkdir "%HEEKSCADPATH%\es"
"%GETTEXTPATH%\msgfmt.exe" -o "%HEEKSCADPATH%\es\HeeksCAD.mo" "%HEEKSCADSOURCEPATH%\translations\es\HeeksCAD.po"
mkdir "%HEEKSCADPATH%\fr"
"%GETTEXTPATH%\msgfmt.exe" -o "%HEEKSCADPATH%\fr\HeeksCAD.mo" "%HEEKSCADSOURCEPATH%\translations\fr\HeeksCAD.po"
mkdir "%HEEKSCADPATH%\it"
"%GETTEXTPATH%\msgfmt.exe" -o "%HEEKSCADPATH%\it\HeeksCAD.mo" "%HEEKSCADSOURCEPATH%\translations\it\HeeksCAD.po"
mkdir "%HEEKSCADPATH%\ko"
"%GETTEXTPATH%\msgfmt.exe" -o "%HEEKSCADPATH%\ko\HeeksCAD.mo" "%HEEKSCADSOURCEPATH%\translations\ko\HeeksCAD.po"
mkdir "%HEEKSCADPATH%\ru"
"%GETTEXTPATH%\msgfmt.exe" -o "%HEEKSCADPATH%\ru\HeeksCAD.mo" "%HEEKSCADSOURCEPATH%\translations\ru\HeeksCAD.po"
mkdir "%HEEKSCADPATH%\sk"
"%GETTEXTPATH%\msgfmt.exe" -o "%HEEKSCADPATH%\sk\HeeksCAD.mo" "%HEEKSCADSOURCEPATH%\translations\sk\HeeksCAD.po"
mkdir "%HEEKSCADPATH%\zh"
"%GETTEXTPATH%\msgfmt.exe" -o "%HEEKSCADPATH%\zh\HeeksCAD.mo" "%HEEKSCADSOURCEPATH%\translations\zh\HeeksCAD.po"
rem HeeksCAD
copy /y %HEEKSCADSOURCEPATH%\HeeksCAD.exe %HEEKSCADPATH%\HeeksCAD.exe
mkdir %HEEKSCADPATH%\bitmaps
copy /y %HEEKSCADSOURCEPATH%\bitmaps\*.png %HEEKSCADPATH%\bitmaps
copy /y %HEEKSCADSOURCEPATH%\bitmaps\font.glf %HEEKSCADPATH%\bitmaps\font.glf
mkdir %HEEKSCADPATH%\icons
copy /y %HEEKSCADSOURCEPATH%\icons\*.png %HEEKSCADPATH%\icons
copy /y %WXBINARIESPATH%\wxmsw28u_gl_vc_custom.dll %HEEKSCADPATH%
copy /y %WXBINARIESPATH%\wxmsw28u_core_vc_custom.dll %HEEKSCADPATH%
copy /y %WXBINARIESPATH%\wxmsw28u_aui_vc_custom.dll %HEEKSCADPATH%
copy /y %WXBINARIESPATH%\wxbase28u_vc_custom.dll %HEEKSCADPATH%
rem TBB
copy /y %TBBBINPATH%\tbbmalloc.dll %HEEKSCADPATH%
copy /y %TBBBINPATH%\tbb.dll %HEEKSCADPATH%
rem FreeImage
copy /y %FREEIMAGEBINPATH%\freeimage.dll %HEEKSCADPATH%
rem FreeType
copy /y %FREETYPEBINPATH%\freetype.dll %HEEKSCADPATH%
rem OpenCascade
copy /y %OPENCASCADEBINPATH%\TKBRep.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKernel.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKG2d.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKG3d.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKGeomBase.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKIGES.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKTopAlgo.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKGeomAlgo.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKShHealing.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKPrim.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKBool.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKBO.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKXSBase.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKSTEP.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKSTEPAttr.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKSTEPBase.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKSTEP209.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKFillet.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKOffset.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKV3d.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKService.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKMesh.dll %HEEKSCADPATH%
copy /y %OPENCASCADEBINPATH%\TKHLR.dll %HEEKSCADPATH%