#ifndef HLPFLIGHTPLANNERAPP_H
#define HLPFLIGHTPLANNERAPP_H

#include <QMainWindow>

#include "qgsmapcanvas.h"
#include "qgsmessagebar.h"

#include "hlpproject.h"
#include "hlpmapmanager.h"

namespace Ui {
  class HlpFlightPlannerApp;
  }

class HlpFlightPlannerApp : public QMainWindow
{
  Q_OBJECT

  public:
    explicit HlpFlightPlannerApp(QWidget *parent = 0);
    ~HlpFlightPlannerApp();

  public slots:
    void setLayerSet(bool updateExtent);
    void panMode();

  private:
    void initGui();
    void initApp();

    Ui::HlpFlightPlannerApp *ui;
    QgsMapCanvas* mMapCanvas;
    QgsMessageBar* mInfoBar;

    QgsVectorLayer* mFlightlineLayer;
    QgsVectorLayer* mProfileLayer;
    QgsVectorLayer* mWaypointLayer;

    HlpProject mProject;
    HlpMapManager* mMapManager;

    QgsMapTool* mPanTool;



};

#endif // HLPFLIGHTPLANNERAPP_H