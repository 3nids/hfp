


#include <QGridLayout>
#include <QSettings>

#include "qgsapplication.h"
#include "qgsmaplayerregistry.h"
#include "qgsproviderregistry.h"
#include "qgsvectorlayer.h"
#include "qgscoordinatereferencesystem.h"
#include "qgsmaptoolpan.h"

#include "../core/hlpproject.h"
#include "../core/hlpmapregistry.h"
#include "../gui/hlpmapmanager.h"
#include "../maptools/hlpaddprofile.h"

#include "hlpflightplannerapp.h"


#include "ui_hlpflightplannerapp.h"


HlpFlightPlannerApp *HlpFlightPlannerApp::mInstance = 0;

HlpFlightPlannerApp::~HlpFlightPlannerApp()
{
  QgsApplication::exitQgis();

  delete HlpProject::instance();
  delete HlpMapRegistry::instance();

  delete mPanTool;
  delete mAddProfileTool;

  delete mMapManager;
  delete mMapCanvas;

  delete ui;
}

HlpFlightPlannerApp::HlpFlightPlannerApp(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::HlpFlightPlannerApp)
{
  ui->setupUi(this);

  initApp();
  mInstance = this;

  // test
//  QgsRasterLayer *mypLayer = new QgsRasterLayer( "/home/denis/Documents/cpp/hfp/hfp/data/cn1244.png", "cn1244");
//  HlpMapRegistry::instance()->addMapLayer(mypLayer);
//  QgsRasterLayer *mypLayer2 = new QgsRasterLayer( "/home/denis/Documents/cpp/hfp/hfp/data/cn1244.png", "cn1264");
//  HlpMapRegistry::instance()->addMapLayer(mypLayer2);
}

void HlpFlightPlannerApp::initApp()
{
#if defined(Q_WS_MAC)
  QString pluginPath = "/Users/denis/apps/qgis.app/Contents/MacOS/lib/qgis";
#elif defined(Q_WS_WIN)
  QString pluginPath = "c:\\OSGeo4W\\apps\\qgis-dev\\plugins";
  QString prefixPath = "c:\\OSGeo4W\\apps\\qgis-dev";
#else
  QString pluginPath = "/usr/local/lib/qgis/plugins/";
  QString prefixPath = "/usr/local";
#endif

  QgsApplication::setPluginPath( pluginPath );
  QgsApplication::setPrefixPath( prefixPath, true);
  QgsApplication::initQgis();

  QSettings settings;

  // Central widget
  QWidget *centralWidget = this->centralWidget();
  QGridLayout *centralLayout = new QGridLayout( centralWidget );
  centralWidget->setLayout( centralLayout );
  centralLayout->setContentsMargins( 0, 0, 0, 0 );

  // Map canvas
  mMapCanvas = new QgsMapCanvas( centralWidget, "theMapCanvas" );
  mMapCanvas->setCanvasColor( QColor( 255, 255, 255 ) );
  mMapCanvas->setWheelAction( QgsMapCanvas::WheelZoomAndRecenter, 2 );
  centralLayout->addWidget( mMapCanvas, 0, 0, 2, 1 );

  // Message bar
  mInfoBar = new QgsMessageBar( centralWidget );
  mInfoBar->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Fixed );
  centralLayout->addWidget( mInfoBar, 0, 0, 1, 1 );

  // Map manager
  mMapManager = new HlpMapManager( this );
  connect( ui->mActionMapManager, SIGNAL(toggled(bool)), mMapManager, SLOT( setVisible( bool )) );
  connect( mMapManager->toggleViewAction(), SIGNAL(toggled(bool)), ui->mActionMapManager, SLOT( setChecked( bool ) ) );
  addDockWidget( Qt::LeftDockWidgetArea, mMapManager );

  // create map layer registry if doesn't exist
  QgsMapLayerRegistry::instance();

  // CRS
  mMapCanvas->setCrsTransformEnabled( true );
  mMapCanvas->setDestinationCrs( HlpProject::instance()->epsg() );
  mMapCanvas->refresh();

  QgsMapToPixel test = mMapCanvas->mapSettings().mapToPixel();

  // add the layers
  QMap<QString, QgsMapLayer*> layerList = HlpProject::instance()->createLayers();
  if ( layerList.isEmpty() )
  {
    // TODO: what?
    return;
  }
  mFlightlineLayer = dynamic_cast<QgsVectorLayer*>( layerList.value("flightline") );
  mProfileLayer = dynamic_cast<QgsVectorLayer*>( layerList.value("profile") );
  mWaypointLayer = dynamic_cast<QgsVectorLayer*>( layerList.value("waypoint") );

  // layers registries
  connect( HlpMapRegistry::instance(), SIGNAL(layersChanged(bool)), this, SLOT(setLayerSet(bool)) );

  // Map tools
  mPanTool = new QgsMapToolPan( mMapCanvas );
  connect( ui->mActionPan, SIGNAL(triggered()), this, SLOT(panMode()));
  mPanTool->setAction(ui->mActionPan);
  mAddProfileTool = new HlpAddProfile( mMapCanvas, mProfileLayer );
  connect( ui->mActionAddProfile, SIGNAL( triggered() ), this, SLOT( addProfile() ) );
  mAddProfileTool->setAction(ui->mActionAddProfile);

  // Other actions
  connect( ui->mActionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()) );
  connect( ui->mActionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()) );

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

void HlpFlightPlannerApp::addProfile()
{
  mMapCanvas->setMapTool( mAddProfileTool );
}

void HlpFlightPlannerApp::zoomIn()
{
  double scale = QSettings().value( "/hlp/scale_factor", 2.0 ).toDouble();
  mMapCanvas->zoomByFactor( 1 / scale );
}

void HlpFlightPlannerApp::zoomOut()
{
  double scale = QSettings().value( "/hlp/scale_factor", 2.0 ).toDouble();
  mMapCanvas->zoomByFactor( scale );
}
