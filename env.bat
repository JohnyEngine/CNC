rem 32 bit with Unicode support
rem Boost 1.61
rem Python 2.17
rem OpenCAscade 6.9.1
rem WxWidgets 3.0.2 
rem
set THIRD_PATRIES_DIR=D:\GitHub\heeks\3rdparties
set BOOST_ROOT=%THIRD_PATRIES_DIR%\boost_1_61_0\
set BOOST_LIBRARYDIR=%BOOST_ROOT%\stage\lib
set PYTHONPATH=%THIRD_PATRIES_DIR%\Python27
set PATH=%PATH%;%BOOST_ROOT%;%PYTHONPATH%
set BOOST43_PYTHON_PATH=%BOOST_ROOT%
set PYTHON26_INCLUDE=%PYTHONPATH%\include
set PYTHON26_LIB=%PYTHONPATH%\libs\python27.lib
set WXWIN=%THIRD_PATRIES_DIR%\wxWidgets-3.0.2
set CASROOT=%THIRD_PATRIES_DIR%\opencascade-6.9.1
set LIBAREA_PATH=D:\GitHub\heeks\libarea
rem Build Boost
rem Run MS Visual Studio command prompt
"VS2013 x86 Native Tools Command Prompt.lnk"
rem Execute .\bootstrap
rem Execute .\b2 
rem Build Boost Python
rem bjam --with-python python-debugging=off threading=multi variant=release link=shared stage
rem bjam --with-python python-debugging=on threading=multi variant=debug link=shared stage
rem devenv
rem cd ..\libarea
rem "c:\Program Files\CMake\bin\cmake-gui.exe"