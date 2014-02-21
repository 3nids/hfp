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
    hlpproject.cpp \
    hlpflightplannerapp.cpp \
    hlpprojectprojectproperties.cpp \
    hlpmapmanager.cpp \
    hlpmapregistry.cpp \
    hlpaddprofile.cpp \
    hlpmaptooledit.cpp

HEADERS  += \
    hlpproject.h \
    hlpflightplannerapp.h \
    hlpprojectprojectproperties.h \
    hlpmapmanager.h \
    hlpmapregistry.h \
    hlpaddprofile.h \
    hlpmaptooledit.h

FORMS    += \
    ui/hlpprojectprojectproperties.ui \
    ui/hlpmapmanager.ui \
    ui/hlpflightplannerapp.ui

win32:CONFIG(release, debug|release): {
  LIBS += -LC:\\OSGeo4W\\apps\\qgis-dev\\lib\\ -lqgis_core -lqgis_gui
  LIBS += -LC:\\OSGeo4W\\apps\\qgis-dev\\plugins\\ -lgdalprovider
  INCLUDEPATH += C:\\OSGeo4W\\apps\\qgis-dev\\include
  # cross compilation include
  INCLUDEPATH += /usr/local/include/qgis
  INCLUDEPATH += /usr/include/
  INCLUDEPATH += /usr/include/x86_64-linux-gnu/ # if stubs-32.h is missing: sudo apt-get install libc6-dev-i386
}

unix {
  # sige: local, mac: rien
  LIBS += -L/usr/local/lib/ -lqgis_core -lqgis_gui
  LIBS += -L/usr/local/lib/qgis/plugins/ -lgdalprovider
  INCLUDEPATH += /usr/local/include/qgis
}

DEFINES += GUI_EXPORT= CORE_EXPORT=

RC_FILE = ./images/images.qrc

RESOURCES += \
    images/images.qrc

