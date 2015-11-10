rem set HEEKSCADSOURCEPATH=D:\GitHub\CNC\heekscad
rem set GETTEXTPATH=D:\insttools\gettext

"%GETTEXTPATH%\xgettext.exe" -C -n -k_ -o "%HEEKSCADSOURCEPATH%\HeeksCAD.po" %HEEKSCADSOURCEPATH%\src\*.cpp %HEEKSCADSOURCEPATH%\src\*.h %HEEKSCADSOURCEPATH%\interface\*.cpp %HEEKSCADSOURCEPATH%\interface\*.h %HEEKSCADSOURCEPATH%\src\*.cpp %HEEKSCADSOURCEPATH%\src\*.h

pause