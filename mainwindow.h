#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qgsmapcanvas.h"
#include "qgsmessagebar.h"

#include "hlpproject.h"

namespace Ui {
  class MainWindow;
  }

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  typedef QPair<QString, QString> HlpField;

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  static QString createUri(QString geomType, QList<HlpField> fields, int epsg);

private:
  void initGui();
  void initApp();

  Ui::MainWindow *ui;
  QgsMapCanvas* mMapCanvas;
  QgsMessageBar* mInfoBar;

  QgsVectorLayer* mFlightlineLayer;
  QgsVectorLayer* mProfileLayer;
  QgsVectorLayer* mWaypointLayer;

  HlpProject mProject;


};

#endif // MAINWINDOW_H
