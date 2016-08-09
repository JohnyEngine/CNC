set HEEKSCADPATH=D:\HeeksCAD
set HEEKSCNCPATH=%HEEKSCADPATH%\HeeksCNC
set HEEKSCADSOURCEPATH=%BASESOURCEPATH%\heekscad
set HEEKSCNCSOURCEPATH=%BASESOURCEPATH%\heekscnc
set VOXELCUTPATH=%BASESOURCEPATH%\voxelcut
set WXBINARIESPATH=%WXWIN%\lib\vc_dll
set OPENCASCADEBINPATH=%CASROOT%\win32\vc12\bin
set TBBBINPATH=%THIRDPATRIESPATH%\tbb44_20160526oss\bin\ia32\vc12
set FREEIMAGEBINPATH=%THIRDPATRIESPATH%\freeimage-3.17.0-vc12-32\bin
set FREETYPEBINPATH=%THIRDPATRIESPATH%\freetype-2.5.5-vc12-32\bin
set GETTEXTPATH=%THIRDPATRIESPATH%\gettext0.19.8.1\bin\

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

