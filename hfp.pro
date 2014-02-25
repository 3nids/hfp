#-------------------------------------------------
#
# Project created by QtCreator 2014-01-17T09:43:33
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hfp

TEMPLATE = app

SOURCES += main.cpp\
    core/hlpproject.cpp \
    core/hlpmapregistry.cpp \
    app/hlpflightplannerapp.cpp \
    gui/hlpprojectprojectproperties.cpp \
    gui/hlpmapmanager.cpp \
    maptools/hlpmaptooledit.cpp \
    maptools/hlpmaptoolcatpure.cpp \
    maptools/hlpaddprofile.cpp \


HEADERS  += \
    core/hlpproject.h \
    core/hlpmapregistry.h \
    app/hlpflightplannerapp.h \
    gui/hlpprojectprojectproperties.h \
    gui/hlpmapmanager.h\
    maptools/hlpmaptooledit.h \
    maptools/hlpmaptoolcatpure.h \
    maptools/hlpaddprofile.h \

FORMS    += \
    ui/hlpprojectprojectproperties.ui \
    ui/hlpmapmanager.ui \
    ui/hlpflightplannerapp.ui

RESOURCES += images/images.qrc


win32:CONFIG(Release, Debug|Release) {
  LIBS += -L"C:/OSGeo4W/lib/" -lQtCore4
  LIBS += -L"C:/OSGeo4W/lib/" -lQtGui4
  LIBS += -L"C:/OSGeo4W/lib/" -lQtXml4
  LIBS += -L"C:/OSGeo4W/apps/qgis-dev/lib/" -lqgis_core
  LIBS += -L"C:/OSGeo4W/apps/qgis-dev/lib/" -lqgis_gui
}
else:win32:CONFIG(Debug, Debug|Release) {
#  PRE_TARGETDEPS += C:/OSGeo4W/lib/QtCore4.lib
#  PRE_TARGETDEPS += C:/OSGeo4W/lib/QtGui4.lib
#  PRE_TARGETDEPS += C:/OSGeo4W/lib/QtXml4.lib
  LIBS += -L"C:/OSGeo4W/lib/" -lQtCore4
  LIBS += -L"C:/OSGeo4W/lib/" -lQtGui4
  LIBS += -L"C:/OSGeo4W/lib/" -lQtXml4
  LIBS += -L"C:/OSGeo4W/apps/qgis-dev/lib/" -lqgis_core
  LIBS += -L"C:/OSGeo4W/apps/qgis-dev/lib/" -lqgis_gui
}
win32:{
  INCLUDEPATH += C:/OSGeo4W/include
  DEPENDPATH += C:/OSGeo4W/include
  INCLUDEPATH += C:/OSGeo4W/apps/qgis-dev/include
  DEPENDPATH += C:/OSGeo4W/apps/qgis-dev/include
  DEFINES += GUI_EXPORT=__declspec(dllimport) CORE_EXPORT=__declspec(dllimport)
}

unix {
  LIBS += -L/usr/local/lib/ -lqgis_core -lqgis_gui
  LIBS += -L/usr/local/lib/qgis/plugins/ -lgdalprovider
  INCLUDEPATH += /usr/local/include/qgis
  DEFINES += GUI_EXPORT= CORE_EXPORT=
}
