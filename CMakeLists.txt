cmake_minimum_required(VERSION 2.8)
PROJECT(hfp)
SET(CMAKE_COLOR_MAKEFILE ON)
# set path to additional CMake modules
IF (WIN32)
  SET(CMAKE_MODULE_PATH c:\OSGeo4W\apps\qgis-dev ${CMAKE_MODULE_PATH})
  SET(CMAKE_MODULE_PATH c:\OSGeo4W\apps\qgis ${CMAKE_MODULE_PATH})
ELSE (WIN32)
  SET(CMAKE_MODULE_PATH /usr/local/share/qgis ${CMAKE_MODULE_PATH})
ENDIF(WIN32)

FIND_PACKAGE(QGIS REQUIRED)
IF (NOT QGIS_FOUND)
  MESSAGE (SEND_ERROR "QGIS dependency was not found!")
ENDIF (NOT QGIS_FOUND)
IF (WIN32)
  # expect that classes are being imported by default
  # Note: MSVC doesn't like when the macros are quotes
  # and MSYS doesn't like them unqouted (bacause of braces)
  # import qgis classes
  IF (MSVC)
    ADD_DEFINITIONS("-DGUI_EXPORT=__declspec(dllimport)")
    ADD_DEFINITIONS("-DCORE_EXPORT=__declspec(dllimport)")
  ELSE (MSVC)
    ADD_DEFINITIONS("\"-DGUI_EXPORT=__declspec(dllimport)\"")
    ADD_DEFINITIONS("\"-DCORE_EXPORT=__declspec(dllimport)\"")
  ENDIF (MSVC)
ELSE (WIN32)
  ADD_DEFINITIONS(-DGUI_EXPORT=)
  ADD_DEFINITIONS(-DCORE_EXPORT=)
ENDIF (WIN32)

IF (CMAKE_BUILD_TYPE MATCHES Debug)
  ADD_DEFINITIONS(-DhfpDEBUG=1)
ENDIF (CMAKE_BUILD_TYPE MATCHES Debug)
########################################################
# Files

SET (hfp_SRCS
  main.cpp
  core/hlpproject.cpp
  core/hlpmapregistry.cpp
  app/hlpflightplannerapp.cpp
  gui/hlpprojectprojectproperties.cpp
  gui/hlpmapmanager.cpp
  maptools/hlpmaptooledit.cpp
  maptools/hlpmaptoolcatpure.cpp
  maptools/hlpaddprofile.cpp
)

# This tut uses no UIs
SET (hfp_UIS 
ui/hlpprojectprojectproperties.ui
    ui/hlpmapmanager.ui
    ui/hlpflightplannerapp.ui
)

# This tut needs no MOC
SET (hfp_MOC_HDRS
  core/hlpproject.h 
  core/hlpmapregistry.h 
  app/hlpflightplannerapp.h 
  gui/hlpprojectprojectproperties.h 
  gui/hlpmapmanager.h
  maptools/hlpmaptooledit.h 
  maptools/hlpmaptoolcatpure.h 
  maptools/hlpaddprofile.h
)

SET (hfp_RCCS
 images/images.qrc 
)

SET (QT_USE_QT3SUPPORT FALSE)
SET (QT_USE_QTGUI TRUE)
SET (QT_USE_QTSQL TRUE)
SET (QT_USE_QTSVG TRUE)
SET (QT_USE_QTXML TRUE)
SET (QT_USE_QTNETWORK TRUE)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE( ${QT_USE_FILE} )

########################################################
# Build

QT4_WRAP_UI (hfp_UIS_H  ${hfp_UIS})

QT4_WRAP_CPP (hfp_MOC_SRCS  ${hfp_MOC_HDRS})

QT4_ADD_RESOURCES(hfp_RCC_SRCS ${hfp_RCCS})

ADD_EXECUTABLE (hfp ${hfp_SRCS} ${hfp_MOC_SRCS} ${hfp_RCC_SRCS} ${hfp_UIS_H})

INCLUDE_DIRECTORIES(
     ${GDAL_INCLUDE_DIR}
     ${GEOS_INCLUDE_DIR}
     ${CMAKE_CURRENT_BINARY_DIR}
     ${QT_INCLUDE_DIR}
     ${QGIS_INCLUDE_DIR}
     .
)

#This is probably no longer needed, but I will leave it in for Win machines for the moment
IF(QT_QTSQL_FOUND)
 FIND_LIBRARY(QT_QTSQL_LIBRARY NAMES QtSql QtSql5 PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
 SET(QT_LIBRARIES ${QT_LIBRARIES} ${QT_QTSQL_LIBRARY})
ENDIF(QT_QTSQL_FOUND)

TARGET_LINK_LIBRARIES(hfp
  ${QT_LIBRARIES}
  ${QGIS_CORE_LIBRARY} 
  ${QGIS_GUI_LIBRARY}
  ${GEOS_LIBRARY}
  ${GDAL_LIBRARY}
)

IF (MSVC)
  # Very important or you get all kinds of odd side
  #effects like app crash on start up saying qtgui.dll
  TARGET_LINK_LIBRARIES( hfp
                         qtmain
                       )
ENDIF (MSVC)

########################################################
# Install
