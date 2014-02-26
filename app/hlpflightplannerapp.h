#ifndef HLPFLIGHTPLANNERAPP_H
#define HLPFLIGHTPLANNERAPP_H

#include <QMainWindow>

#include "qgsmapcanvas.h"
#include "qgsmessagebar.h"

#include "../core/hlpproject.h"
#include "../gui/hlpmapmanager.h"

namespace Ui {
  class HlpFlightPlannerApp;
  }

//#include "ui_hlpflightplannerapp.h"

class HlpFlightPlannerApp : public QMainWindow //, private Ui::HlpFlightPlannerApp
{
  Q_OBJECT

  public:
    static HlpFlightPlannerApp *instance() { return mInstance; }

    explicit HlpFlightPlannerApp(QWidget *parent = 0);
    ~HlpFlightPlannerApp();

    Ui::HlpFlightPlannerApp *ui;

  public slots:
    void setLayerSet(bool updateExtent);

    void panMode();
    void addProfile();

  private:
    static HlpFlightPlannerApp* mInstance;

    void initApp();

    QgsMapCanvas* mMapCanvas;
    QgsMessageBar* mInfoBar;

    QgsVectorLayer* mFlightlineLayer;
    QgsVectorLayer* mProfileLayer;
    QgsVectorLayer* mWaypointLayer;

    HlpMapManager* mMapManager;

    QgsMapTool* mPanTool;
    QgsMapTool* mAddProfileTool;

};

#endif // HLPFLIGHTPLANNERAPP_H
