ECHO Setting up QGIS DEV ENV

set PYTHONPATH=

set OSGEO4W_ROOT=C:\OSGeo4W
call "%OSGEO4W_ROOT%\bin\o4w_env.bat"

@set QMAKESPEC=win32-msvc2008
@set PATH=%OSGEO4W_ROOT%\bin;%OSGEO4W_ROOT%\apps\qgis-dev\bin;%OSGEO4W_ROOT%\apps\qgis-dev\plugins;%PATH%

@set INCLUDE=%INCLUDE%;%OSGEO4W_ROOT%\include;%OSGEO4W_ROOT%\apps\qgis-dev\include
@set LIB=%LIB%;%OSGEO4W_ROOT%\lib;%OSGEO4W_ROOT%\apps\qgis-dev\lib

path %SYSTEMROOT%\System32;%SYSTEMROOT%;%SYSTEMROOT%\System32\wbem;C:\Progra~1\CMake 2.8\bin;C:\Progra~1\Git\bin;C:\Qt\qtcreator-3.0.1\bin;%PATH%

set VS90COMNTOOLS=C:\Program Files\Microsoft Visual Studio 9.0\Common7\Tools\
call "C:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86

start "Qt Creator" /B C:\Qt\qtcreator-3.0.1\bin\qtcreator.exe %*
