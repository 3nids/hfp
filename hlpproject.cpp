

// QT
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QLibrary>

// QGIS
#include "qgsmaplayer.h"
#include "qgsvectorlayer.h"
#include "qgsmaplayerregistry.h"
#include "qgsproviderregistry.h"
#include "qgsspatialiteprovider.h"

// HFP
#include "hlpproject.h"

class QgsMapLayerRegistry;
class QgsVectorLayer;
class QgsProviderRegistry;



HlpProject::HlpProject(QString projectPath)
  : mProjectPath( projectPath )
{
}

bool HlpProject::createEmptyProject(QString dbPath, int epsg)
{
  QFile* file = new QFile(dbPath);
  if ( file->exists() )
      file->remove();

  QString errCause;
  bool res = false;

  QString spatialite_lib = QgsProviderRegistry::instance()->library( "spatialite" );
  QLibrary* myLib = new QLibrary( spatialite_lib );
  bool loaded = myLib->load();
  if ( loaded )
  {
    QgsDebugMsg( "spatialite provider loaded" );

    typedef bool ( *createDbProc )( const QString&, QString& );
    createDbProc createDbPtr = ( createDbProc ) cast_to_fptr( myLib->resolve( "createDb" ) );
    if ( createDbPtr )
      res = createDbPtr( dbPath, errCause );
  }
  delete myLib;

  if ( !res )
  {
    QMessageBox::warning( 0, QObject::tr( "SpatiaLite Database" ), errCause );
    return false;
  }


  spatialite_init( 0 );
  sqlite3 *sqlite_handle;
  qDebug() << QString( "New sqlite connection for " ) << dbPath;
  int rc = sqlite3_open_v2( dbPath.toUtf8().constData(), &sqlite_handle, SQLITE_OPEN_READWRITE, NULL );
  if ( rc != SQLITE_OK )
  {
    // failure
    qDebug() << QString( "Failure while connecting to: %1\n%2" )
                 .arg( dbPath )
                 .arg( QString::fromUtf8( sqlite3_errmsg( sqlite_handle ) ) );
    return false;
  }

  QStringList sqlCommands;
  // info
  sqlCommands.append( "create table 'project' (pkid integer primary key autoincrement, 'property' text, 'textvalue' text, 'intvalue' int)" );
  sqlCommands.append( "insert into project ('property', 'intvalue') VALUES ('srsid',21781) ");

  // rasters
  sqlCommands.append( "create table 'rasters' (pkid integer primary key autoincrement, 'path' text, 'dtm' int)" );

  // flightlines
  sqlCommands.append( "create table 'flightline' (pkid integer primary key autoincrement, 'id' integer)" );
  sqlCommands.append( QString("select AddGeometryColumn('flightline','geometry',%1,'LINESTRING',2)").arg( epsg ) );
  sqlCommands.append( "select CreateSpatialIndex('flightline','geometry')" );
  sqlCommands.append( QString("select AddGeometryColumn('flightline','geometry_cover',%1,'POLYGON',2)").arg( epsg ) );
  sqlCommands.append( "select CreateSpatialIndex('flightline','geometry_cover')" );

  // flightline points
  sqlCommands.append( "create table flightline_point (pkid integer primary key autoincrement, id_fl integer, 'order' integer, 'type' text, 'value' real, calculated_height real, height_uptodate integer)");
  sqlCommands.append( QString("select AddGeometryColumn('flightline_point','geometry',%1,'POINT',2)").arg( epsg ) );
  sqlCommands.append( "select CreateSpatialIndex('flightline_point','geometry')" );

  // profiles
  sqlCommands.append( "create table profile (pkid integer primary key autoincrement, 'values' text)");
  sqlCommands.append( QString("select AddGeometryColumn('profile','geometry',%1,'POINT',2)").arg( epsg ) );
  sqlCommands.append( "select CreateSpatialIndex('profile','geometry')" );

  char * errmsg;
  foreach (const QString &sql, sqlCommands)
  {
    rc = sqlite3_exec( sqlite_handle, sql.toUtf8(), NULL, NULL, &errmsg );
    if ( rc != SQLITE_OK )
    {
      QMessageBox::warning( 0,
                            QObject::tr( "Error Creating HFP project" ),
                            QObject::tr( "Failed to execute command %1. The database returned:\n%2" ).arg( sql ).arg( errmsg ) );
      sqlite3_free( errmsg );
      return false;
    }
  }

  return true;
}

HlpProject* HlpProject::openProject( QString dbPath )
{

  HlpProject* project = new HlpProject(dbPath);


  QList<QgsMapLayer *> layerList;

  QList< HlpLayer > layerNames = QList< HlpLayer >()
                                 << HlpLayer("project","")  // non-geometric layer
                                 << HlpLayer("flightline","geometry")
                                 << HlpLayer("flightline", "geometry_cover")
                                 << HlpLayer("flightline_point", "geometry")
                                 << HlpLayer("profile", "geometry");

  foreach( const HlpLayer &layerName, layerNames )
  {
    QString uri = QString( "dbname='%1' table='%2'(%3) sql=" )
                  .arg( dbPath.toUtf8().constData() )
                  .arg( layerName.first )
                  .arg( layerName.second );

    layerList << new QgsVectorLayer( uri, layerName.first, "spatialite" );
    if ( !layerList.last()->isValid() )
    {
      QMessageBox::critical( 0, QObject::tr( "Invalid Layer" ), QObject::tr( "%1 is an invalid layer and cannot be loaded." ).arg( layerName.first ) );
      return 0;
    }
  }

  //addMapLayers returns a list of all successfully added layers
  //so we compare that to our original list.
  if ( layerList != QgsMapLayerRegistry::instance()->addMapLayers( layerList, false ) )
  {
    delete project;
    return 0;
  }

  foreach (QgsMapLayer* layer, layerList)
  {
    // TODO enregistrer les id des layers

    QgsVectorLayer* vl = dynamic_cast<QgsVectorLayer*>(layer);
    if (!vl)
    {
      delete project;
      return 0;
    }


    qDebug() << vl->id();

  }


  return project;
}
