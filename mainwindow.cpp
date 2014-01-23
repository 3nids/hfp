


#include <QGridLayout>
#include <QSettings>

#include "qgsmaplayerregistry.h"
#include "qgsproviderregistry.h"
#include "qgsvectorlayer.h"

#include "mainwindow.h"
#include "project.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // create map layer registry if doesn't exist
  QgsMapLayerRegistry::instance();

#if defined(Q_WS_MAC)
  QString myPluginsDir        = "/Users/timsutton/apps/qgis.app/Contents/MacOS/lib/qgis";
#else
  QString myPluginsDir        = "/usr/local/lib/qgis/plugins/";
#endif
  QgsProviderRegistry::instance(myPluginsDir);

  QSettings settings;

  QWidget *centralWidget = this->centralWidget();
  QGridLayout *centralLayout = new QGridLayout( centralWidget );
  centralWidget->setLayout( centralLayout );
  centralLayout->setContentsMargins( 0, 0, 0, 0 );

  // "theMapCanvas" used to find this canonical instance later
  mMapCanvas = new QgsMapCanvas( centralWidget, "theMapCanvas" );
  mMapCanvas->setWhatsThis( tr( "Map canvas. This is where raster and vector "
                                "layers are displayed when added to the map" ) );

  // set canvas color right away
  int myRed = settings.value( "/qgis/default_canvas_color_red", 255 ).toInt();
  int myGreen = settings.value( "/qgis/default_canvas_color_green", 255 ).toInt();
  int myBlue = settings.value( "/qgis/default_canvas_color_blue", 255 ).toInt();
  mMapCanvas->setCanvasColor( QColor( myRed, myGreen, myBlue ) );

  centralLayout->addWidget( mMapCanvas, 0, 0, 2, 1 );

  // a bar to warn the user with non-blocking messages
  mInfoBar = new QgsMessageBar( centralWidget );
  mInfoBar->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Fixed );
  centralLayout->addWidget( mInfoBar, 0, 0, 1, 1 );

  QString filePath = "/home/denis/tmp2/test.sp3";
  if ( Project::createEmptyProject( filePath, 21781 ) )
  {
    Project::openProject( filePath );
  }


}

MainWindow::~MainWindow()
{
  delete ui;
}
