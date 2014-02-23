
#include <QFileDialog>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>

#include "qgsrasterlayer.h"

#include "hlpmapmanager.h"
#include "hlpmapregistry.h"
#include "ui_hlpmapmanager.h"


HlpMapManager::HlpMapManager(QWidget *parent) :
  QDockWidget(parent),
  ui(new Ui::HlpMapManager)
{
  ui->setupUi(this);

  ui->mapList->setModel( HlpMapRegistry::instance() );

  connect( ui->addButton, SIGNAL(clicked()), this, SLOT(addMap()) );
}

HlpMapManager::~HlpMapManager()
{
  delete ui;
}

void HlpMapManager::addMap()
{
  QSettings settings;
  QString lastDir = settings.value( "/hlp/last_map_dir", "" ).toString();
  QString myFileName = QFileDialog::getOpenFileName( this, tr( "Add a map" ),
                                                     lastDir);
  if (myFileName.isEmpty())
    return;

  QFileInfo myRasterFileInfo( myFileName );
  settings.setValue("/hlp/last_map_dir", myRasterFileInfo.path() );
  QgsRasterLayer *mypLayer = new QgsRasterLayer( myRasterFileInfo.filePath(),
                                                 myRasterFileInfo.completeBaseName() );

  qDebug() << "Adding map layer " << myRasterFileInfo.filePath();

  if ( !mypLayer->isValid() )
  {
    qDebug( "  invalid map layer" );
    return;
  }

  HlpMapRegistry::instance()->addMapLayer(mypLayer);
}
