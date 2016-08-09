rem 32 bit with Unicode support
rem Boost 1.61
rem Python 2.17
rem OpenCascade 6.9.1
rem WxWidgets 3.0.2
rem
set BASESOURCEPATH=D:\GitHub\CNC
set THIRDPATRIESPATH=%BASESOURCEPATH%\3rdparties
set BOOST_ROOT=%THIRDPATRIESPATH%\boost_1_61_0\
set PYTHONPATH=%THIRDPATRIESPATH%\Python27
set PATH=%PATH%;%BOOST_ROOT%;%PYTHONPATH%
set WXWIN=%THIRDPATRIESPATH%\wxWidgets-3.0.2
set CASROOT=%THIRDPATRIESPATH%\opencascade-6.9.1
rem Build Boost
rem Run MS Visual Studio command prompt
rem "VS2013 x86 Native Tools Command Prompt.lnk"
rem Execute .\bootstrap
rem Execute .\b2 
rem Build Boost Python
rem bjam --with-python python-debugging=off threading=multi variant=release link=shared stage
rem bjam --with-python python-debugging=on threading=multi variant=debug link=shared stage
rem devenv
