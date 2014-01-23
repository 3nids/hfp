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
        mainwindow.cpp \
    project.cpp

HEADERS  += mainwindow.h \
    project.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): \
  LIBS += -L/$${QGISDIR}/lib/ -lqgis_core -lqgis_gui -lqgis_app

else:win32:CONFIG(debug, debug|release): \
  LIBS += -L/$${QGISDIR}/lib/ -lqgis_core -lqgis_gui -lqgis_app


unix {
  # sige: local, mac: rien
  LIBS += -L/usr/local/lib/ -lqgis_core -lqgis_gui
  LIBS += -L/usr/local/lib/qgis/plugins/ -lspatialiteprovider
  INCLUDEPATH += /usr/local/include/qgis \
                 /home/denis/opt/qgis/Quantum-GIS/src/providers/spatialite
}

DEFINES += GUI_EXPORT= CORE_EXPORT=


#unix|win32: LIBS += -lqgis_core -lqgis_gui

unix|win32: LIBS += -lsqlite3

unix|win32: LIBS += -lspatialite

