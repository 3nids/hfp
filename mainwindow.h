#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qgsmapcanvas.h"
#include "qgsmessagebar.h"

namespace Ui {
  class MainWindow;
  }

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QgsMapCanvas* mMapCanvas;
  QgsMessageBar* mInfoBar;
};

#endif // MAINWINDOW_H
