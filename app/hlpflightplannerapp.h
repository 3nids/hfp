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


class HlpFlightPlannerApp : public QMainWindow //, private Ui::HlpFlightPlannerApp
{
  Q_OBJECT

  public:

    explicit HlpFlightPlannerApp(QWidget *parent = 0);
    ~HlpFlightPlannerApp();

    Ui::HlpFlightPlannerApp *ui;

    int messageTimeout();


  public slots:
    void setLayerSet(bool updateExtent);

    void panMode();
    void addProfile();

    void zoomIn();
    void zoomOut();

  private slots:
    void mapToolChanged( QgsMapTool *newTool , QgsMapTool* oldTool );
    void displayMapToolMessage( QString message, QgsMessageBar::MessageLevel level = QgsMessageBar::INFO );
    void removeMapToolMessage();

  private:
    void initApp();

    QgsMapCanvas* mMapCanvas;
    QgsMessageBar* mInfoBar;

    QgsVectorLayer* mFlightlineLayer;
    QgsVectorLayer* mProfileLayer;
    QgsVectorLayer* mWaypointLayer;

    HlpMapManager* mMapManager;

    QgsMapTool* mPanTool;
    QgsMapTool* mAddProfileTool;

    QgsMessageBarItem* mLastMapToolMessage;

};

#endif // HLPFLIGHTPLANNERAPP_H
