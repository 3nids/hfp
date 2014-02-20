#ifndef HLPFLIGHTPLANNERAPP_H
#define HLPFLIGHTPLANNERAPP_H

#include <QMainWindow>

#include "qgsmapcanvas.h"
#include "qgsmessagebar.h"

#include "hlpproject.h"

namespace Ui {
  class MainWindow;
  }

class HlpFlightPlannerApp : public QMainWindow
{
  Q_OBJECT

public:
  explicit HlpFlightPlannerApp(QWidget *parent = 0);
  ~HlpFlightPlannerApp();

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

#endif // HLPFLIGHTPLANNERAPP_H
