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
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


win32:CONFIG(release, debug|release): \
  LIBS += -L/$${QGISDIR}/lib/ -lqgis_core -lqgis_gui -lqgis_app

else:win32:CONFIG(debug, debug|release): \
  LIBS += -L/$${QGISDIR}/lib/ -lqgis_core -lqgis_gui -lqgis_app

else:unix: \
  QGISDIR = /home/denis/opt/qgis/Quantum-GIS \
  LIBS += -L/$${QGISDIR}/build/output/lib/ -lqgis_core -lqgis_gui -lqgis_app

INCLUDEPATH += $${QGISDIR}/src \
            $${QGISDIR}/src/core \
           $${QGISDIR}/src/gui \
          $${QGISDIR}/build/ \

DEPENDPATH += /home/denis/opt/qgis/Quantum-GIS/src

DEFINES += GUI_EXPORT= CORE_EXPORT=
