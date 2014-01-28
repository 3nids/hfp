

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
#include "project.h"

class QgsMapLayerRegistry;
class QgsVectorLayer;
class QgsProviderRegistry;



Project::Project()
{
}

bool Project::createEmptyProject(QString dbPath, int epsg)
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

bool Project::openProject( QString dbPath )
{
  QList<QgsMapLayer *> layerList;

  QList<QPair<QString,QString>> layerNames = QList<QPair<QString,QString>>()
                                               << QPair("flightline","geometry")
                                               << QPair("", "")
                                               << QPair("", "")
                                               << QPair("", "")
                                               << QPair("", "")

  QStringList layerNames = QStringList() << "flightline" << "flightline_point" << "profile" ;
  foreach( const QString &layerName, layerNames )
  {
    QString uri = QString( "dbname='%1' table='%2'(geometry) sql=" )
            .arg( dbPath.toUtf8().constData() )
            .arg( layerName );
    layerList << new QgsVectorLayer( uri, layerName, "spatialite" );
    if ( !layerList.last()->isValid() )
    {
      QMessageBox::critical( 0, QObject::tr( "Invalid Layer" ), QObject::tr( "%1 is an invalid layer and cannot be loaded." ).arg( layerName ) );
      return false;
    }
  }

  // also load profile height
  // TODO


  //addMapLayers returns a list of all successfully added layers
  //so we compare that to our original list.
  if ( layerList == QgsMapLayerRegistry::instance()->addMapLayers( layerList, false ) )
    return true;
  else
    return false;
}
