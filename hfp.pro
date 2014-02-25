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
    gui/hlpmapmanager.cpp #\
#    maptools/hlpaddprofile.cpp \
#    maptools/hlpmaptooledit.cpp \
#    maptools/hlpmaptoolcatpure.cpp

HEADERS  += \
    core/hlpproject.h \
    core/hlpmapregistry.h \
    app/hlpflightplannerapp.h \
    gui/hlpprojectprojectproperties.h \
    gui/hlpmapmanager.h# \
#    maptools/hlpaddprofile.h \
#    maptools/hlpmaptooledit.h \
#    maptools/hlpmaptoolcatpure.h

FORMS    += \
    ui/hlpprojectprojectproperties.ui \
    ui/hlpmapmanager.ui \
    ui/hlpflightplannerapp.ui

#win32:CONFIG(release, debug|release): {
#  LIBS += -LC:/OSGeo4W/lib -lQtCore4 -lQtGui4
#  LIBS += -LC:/OSGeo4W/apps/qgis-dev/lib -lqgis_core -lqgis_gui
#  # LIBS += -LC:/OSGeo4W/apps/qgis-dev/plugins -lgdalprovider
#  INCLUDEPATH += C:/OSGeo4W/include
#  DEPENDPATH += C:/OSGeo4W/include
#  INCLUDEPATH += C:/OSGeo4W/apps/qgis-dev/include
#  DEPENDPATH += C:/OSGeo4W/apps/qgis-dev/include
#  # cross compilation include
#  INCLUDEPATH += /usr/local/include/qgis
#  INCLUDEPATH += /usr/include/
#  INCLUDEPATH += /usr/include/x86_64-linux-gnu/ # if stubs-32.h is missing: sudo apt-get install libc6-dev-i386
#}
#else:win32:CONFIG(debug, debug|release)
#{
#  LIBS += -LC:/OSGeo4W/lib -lQtCore4d -lQtGui4d
#  LIBS += -LC:/OSGeo4W/apps/qgis-dev/lib -lqgis_core -lqgis_gui
#  # LIBS += -LC:/OSGeo4W/apps/qgis-dev/plugins -lgdalprovider
#  INCLUDEPATH += C:/OSGeo4W/include
#  DEPENDPATH += C:/OSGeo4W/include
#  INCLUDEPATH += C:/OSGeo4W/apps/qgis-dev/include
#  DEPENDPATH += C:/OSGeo4W/apps/qgis-dev/include
#}

win32 {
  LIBS += -L"C:/OSGeo4W/lib/" -lQtCore4
  LIBS += -L"C:/OSGeo4W/lib/" -lQtGui4
  LIBS += -L"C:/OSGeo4W/lib/" -lQtXml4
  LIBS += -L"C:/OSGeo4W/apps/qgis-dev/lib/" -lqgis_core
  LIBS += -L"C:/OSGeo4W/apps/qgis-dev/lib/" -lqgis_gui
  INCLUDEPATH += C:/OSGeo4W/include
  DEPENDPATH += C:/OSGeo4W/include
  INCLUDEPATH += C:/OSGeo4W/apps/qgis-dev/include
  DEPENDPATH += C:/OSGeo4W/apps/qgis-dev/include
}

unix {
  # sige: local, mac: rien
  LIBS += -L/usr/local/lib/ -lqgis_core -lqgis_gui
  LIBS += -L/usr/local/lib/qgis/plugins/ -lgdalprovider
  INCLUDEPATH += /usr/local/include/qgis
}

DEFINES += GUI_EXPORT= CORE_EXPORT=

RESOURCES += images/images.qrc
