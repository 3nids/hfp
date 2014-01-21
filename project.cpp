

// QT
#include <QDebug>
#include <QMessageBox>

// QGIS
#include "qgsmaplayer.h"
#include "qgsvectorlayer.h"
#include "qgsmaplayerregistry.h"


// HFP
#include "project.h"

class QgsMapLayerRegistry;



Project::Project()
{
}

bool Project::createEmptyProject(QString dbPath, int epsg)
{
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
  // flightlines
  sqlCommands.append( "create table flightline pkid integer primary key autoincrement id integer" );
  sqlCommands.append( QString("select AddGeometryColumn(flightline,geometry,%1,Line,2)").arg( epsg ) );
  sqlCommands.append( "select CreateSpatialIndex(flightline,geometry)" );

  // flightline points
  sqlCommands.append( "create table flightline_point pkid integer primary key autoincrement id_fl integer order integer type text value real calculated_height real height_uptodate integer");
  sqlCommands.append( QString("select AddGeometryColumn(flightline_point,geometry,%1,Point,2)").arg( epsg ) );
  sqlCommands.append( "select CreateSpatialIndex(flightline_point,geometry)" );

  // profiles
  sqlCommands.append( "create table profile pkid integer primary key autoincrement id_fl integer order integer type text value real calculated_height real height_uptodate integer");
  sqlCommands.append( QString("select AddGeometryColumn(flightline_point,geometry,%1,Point,2)").arg( epsg ) );
  sqlCommands.append( "select AddGeometryColumn(flightline_point,geometry_height,0,Line,2)" );
  sqlCommands.append( "select CreateSpatialIndex(flightline_point,geometry)" );
  sqlCommands.append( "select CreateSpatialIndex(flightline_point,geometry_height)" );

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

  QList<QgsMapLayer *> myList;

  QStringList layerNames = QStringList() << "flightline" << "flightline_point" << "profile" ;
  foreach( const QString &layerName, layerNames )
  {
    QgsVectorLayer *layer = new QgsVectorLayer( QString( "dbname='%1' table='%2'(geometry) sql=" )
                                                .arg( dbPath.toUtf8().constData() )
                                                .arg( layerName ),
                                                "flightlines", "spatialite" );
    if ( !layer->isValid() )
    {
      QMessageBox::critical( 0, QObject::tr( "Invalid Layer" ), QObject::tr( "%1 is an invalid layer and cannot be loaded." ).arg( layerName ) );
      return false;
    }
    myList << layer;
  }

  // also load profile height
  // TODO


  //addMapLayers returns a list of all successfully added layers
  //so we compare that to our original list.
  if ( myList == QgsMapLayerRegistry::instance()->addMapLayers( myList, false ) )
    return true;
  else
    return false;
}
