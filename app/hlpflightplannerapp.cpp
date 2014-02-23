


#include <QGridLayout>
#include <QSettings>

#include "qgsmaplayerregistry.h"
#include "qgsproviderregistry.h"
#include "qgsvectorlayer.h"
#include "qgscoordinatereferencesystem.h"
#include "qgsmaptoolpan.h"

#include "hlpflightplannerapp.h"
#include "hlpproject.h"
#include "hlpmapmanager.h"
#include "hlpmapregistry.h"
#include "ui_hlpflightplannerapp.h"



HlpFlightPlannerApp::~HlpFlightPlannerApp()
{
  delete ui;
}

HlpFlightPlannerApp::HlpFlightPlannerApp(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::HlpFlightPlannerApp)
{
  ui->setupUi(this);
  initGui();
  initApp();

  // test
//  QgsRasterLayer *mypLayer = new QgsRasterLayer( "/home/denis/Documents/cpp/hfp/hfp/data/cn1244.png", "cn1244");
//  HlpMapRegistry::instance()->addMapLayer(mypLayer);
//  QgsRasterLayer *mypLayer2 = new QgsRasterLayer( "/home/denis/Documents/cpp/hfp/hfp/data/cn1244.png", "cn1264");
//  HlpMapRegistry::instance()->addMapLayer(mypLayer2);
}

void HlpFlightPlannerApp::initGui()
{
#if defined(Q_WS_MAC)
  QString myPluginsDir = "/Users/denis/apps/qgis.app/Contents/MacOS/lib/qgis";
#else
  QString myPluginsDir = "/usr/local/lib/qgis/plugins/";
#endif
  QgsProviderRegistry::instance(myPluginsDir);

  QSettings settings;

  // Central widget
  QWidget *centralWidget = this->centralWidget();
  QGridLayout *centralLayout = new QGridLayout( centralWidget );
  centralWidget->setLayout( centralLayout );
  centralLayout->setContentsMargins( 0, 0, 0, 0 );

  // Map canvas
  mMapCanvas = new QgsMapCanvas( centralWidget, "theMapCanvas" );
  mMapCanvas->setCanvasColor( QColor( 255, 255, 255 ) );
  centralLayout->addWidget( mMapCanvas, 0, 0, 2, 1 );

  // Message bar
  mInfoBar = new QgsMessageBar( centralWidget );
  mInfoBar->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Fixed );
  centralLayout->addWidget( mInfoBar, 0, 0, 1, 1 );

  // Map manager
  mMapManager = new HlpMapManager( this );
  connect( ui->mActionMapManager, SIGNAL(toggled(bool)), mMapManager, SLOT(setVisible(bool)) );
  connect( mMapManager->toggleViewAction(), SIGNAL(toggled(bool)), ui->mActionMapManager, SLOT(setChecked(bool)) );
  addDockWidget( Qt::LeftDockWidgetArea, mMapManager );

  // Map tools
  connect( ui->mActionPan, SIGNAL(triggered()), this, SLOT(panMode()));
  mPanTool = new QgsMapToolPan(mMapCanvas);
  mPanTool->setAction(ui->mActionPan);
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
  mFlightlineLayer = dynamic_cast<QgsVectorLayer*>( layerList.value("flightline") );
  mProfileLayer = dynamic_cast<QgsVectorLayer*>( layerList.value("profile") );
  mWaypointLayer = dynamic_cast<QgsVectorLayer*>( layerList.value("waypoint") );

  // create empty project
  mProject = HlpProject();


  // layers registries
  connect( HlpMapRegistry::instance(), SIGNAL(layersChanged(bool)), this, SLOT(setLayerSet(bool)) );

}

void HlpFlightPlannerApp::setLayerSet( bool updateExtent )
{
  QList<QgsMapCanvasLayer> layers;
  layers.append( HlpMapRegistry::instance()->layers() );
  mMapCanvas->setLayerSet( layers );
  if ( updateExtent )
    mMapCanvas->zoomToFullExtent();
}


void HlpFlightPlannerApp::panMode()
{
  mMapCanvas->setMapTool(mPanTool);
}

