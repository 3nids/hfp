#ifndef HLPFLIGHTPLANNER_H
#define HLPFLIGHTPLANNER_H

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
  typedef QPair<QString, QString> HlpField;

  explicit HlpFlightPlannerApp(QWidget *parent = 0);
  ~HlpFlightPlannerApp();

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

#endif // HLPFLIGHTPLANNER_H
