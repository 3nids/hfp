ECHO Setting up QGIS DEV ENV

@echo off

set PYTHONPATH=

set OSGEO4W_ROOT=C:\OSGeo4W
call "%OSGEO4W_ROOT%\bin\o4w_env.bat"

path %SYSTEMROOT%\System32;%SYSTEMROOT%;%SYSTEMROOT%\System32\wbem;C:\CMake 2.8\bin;C:\GnuWin32\bin;C:\Progra~2\Git\bin;C:\Qt\qtcreator-2.7.1\bin;%PATH%

set VS90COMNTOOLS=C:\Progra~2\Microsoft Visual Studio 9.0\Common7\Tools\
call "C:\Progra~2\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86

@set GRASS_PREFIX=C:/OSGeo4W/apps/grass/grass-6.4.3RC2
@set INCLUDE=%INCLUDE%;%OSGEO4W_ROOT%\include
@set LIB=%LIB%;%OSGEO4W_ROOT%\lib;%OSGEO4W_ROOT%\lib

start "Qt Creator" /B C:\Qt\qtcreator-2.7.1\bin\qtcreator.exe %*
