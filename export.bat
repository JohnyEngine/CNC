set HEEKSCADPATH=D:\HeeksCAD
set HEEKSCNCPATH=%HEEKSCADPATH%\HeeksCNC
set HEEKSCADSOURCEPATH=D:\GitHub\CNC\heekscad
set HEEKSCNCSOURCEPATH=D:\GitHub\CNC\heekscnc
set WXBINARIESPATH=D:\wxWidgets\lib\vc_dll
set OPENCASCADEBINPATH=D:\OpenCASCADE\opencascade-6.9.1\win32\vc12\bin
set TBBBINPATH=D:\OpenCASCADE\tbb44_20150728oss\bin\ia32\vc12
set FREEIMAGEBINPATH=D:\OpenCASCADE\freeimage-3.17.0-vc12-32\bin
set FREETYPEBINPATH=D:\OpenCASCADE\freetype-2.5.5-vc12-32\bin
set VOXELCUTPATH=D:\GitHub\CNC\voxelcut
set PYTHONPATH=d:\Python27
set GETTEXTPATH=d:\tools\GnuWin32\bin\

mkdir "%HEEKSCADPATH%"

copy /y ".\bin\HeeksCAD.exe" "%HEEKSCADPATH%\HeeksCAD.exe"

cd .\heekscad
call export.bat
cd ..

mkdir "%HEEKSCNCPATH%"

copy /y ".\bin\HeeksCNC.dll" "%HEEKSCNCPATH%\HeeksCNC.dll"

cd .\heekscnc
call export.bat
cd ..

copy /y "%PYTHONPATH%\python.exe" "%HEEKSCNCPATH%\python.exe"
mkdir "%HEEKSCNCPATH%\Boolean"
copy /y ".\bin\area.pyd" "%HEEKSCNCPATH%\Boolean\area.pyd"
copy /y ".\bin\area.pyd" "%HEEKSCNCPATH%\area.pyd"
mkdir "%HEEKSCNCPATH%\Clipper"
copy /y ".\bin\Clipper\area.pyd" "%HEEKSCNCPATH%\Clipper\area.pyd"
copy /y ".\bin\ocl.pyd" "%HEEKSCNCPATH%\ocl.pyd"
copy /y ".\bin\voxelcut.pyd" "%HEEKSCNCPATH%\voxelcut.pyd"

