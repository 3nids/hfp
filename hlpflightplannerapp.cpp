


#include <QGridLayout>
#include <QSettings>

#include "qgsmaplayerregistry.h"
#include "qgsproviderregistry.h"
#include "qgsvectorlayer.h"
#include "qgscoordinatereferencesystem.h"

#include "hlpflightplannerapp.h"
#include "hlpproject.h"
#include "ui_hlpflightplanner.h"

HlpFlightPlannerApp::HlpFlightPlannerApp(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  initGui();
  initApp();
}

void HlpFlightPlannerApp::initGui()
{
#if defined(Q_WS_MAC)
  QString myPluginsDir = "/Users/denis/apps/qgis.app/Contents/MacOS/lib/qgis";
#else
  QString myPluginsDir = "/usr/local/lib/hlp/plugins/";
#endif
  QgsProviderRegistry::instance(myPluginsDir);

  QSettings settings;

  QWidget *centralWidget = this->centralWidget();
  QGridLayout *centralLayout = new QGridLayout( centralWidget );
  centralWidget->setLayout( centralLayout );
  centralLayout->setContentsMargins( 0, 0, 0, 0 );

  // "theMapCanvas" used to find this canonical instance later
  mMapCanvas = new QgsMapCanvas( centralWidget, "theMapCanvas" );

  // set canvas color right away
  int myRed = settings.value( "/hlp/default_canvas_color_red", 255 ).toInt();
  int myGreen = settings.value( "/hlp/default_canvas_color_green", 255 ).toInt();
  int myBlue = settings.value( "/hlp/default_canvas_color_blue", 255 ).toInt();
  mMapCanvas->setCanvasColor( QColor( myRed, myGreen, myBlue ) );

  // configure canvas

  centralLayout->addWidget( mMapCanvas, 0, 0, 2, 1 );

  // a bar to warn the user with non-blocking messages
  mInfoBar = new QgsMessageBar( centralWidget );
  mInfoBar->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Fixed );
  centralLayout->addWidget( mInfoBar, 0, 0, 1, 1 );
}

void HlpFlightPlannerApp::initApp()
{
  QSettings settings;

  // create map layer registry if doesn't exist
  QgsMapLayerRegistry::instance();

  // CRS
  int epsg = settings.value( "/hlp/default_crs", 21781 ).toInt();
  QgsCoordinateReferenceSystem crs = QgsCoordinateReferenceSystem( epsg, QgsCoordinateReferenceSystem::EpsgCrsId );
  mMapCanvas->mapRenderer()->setDestinationCrs( crs );

  // add the layers
  QMap<QString, QgsMapLayer*> layerList = HlpProject::createLayers();
  if (layerList.isEmpty())
  {
    // TODO: what?
    return;
  }
  mFlightlineLayer = layerList.value("flightline");
  mProfileLayer = layerList.value("profile");
  mWaypointLayer = layerList.value("waypoint");

  // create empty project
  mProject = HlpProject();
}

HlpFlightPlannerApp::~HlpFlightPlannerApp()
{
  delete ui;
}


