

// QT
#include <QDebug>
#include <QFile>
#include <QSettings>

// QGIS
#include "qgsmaplayer.h"
#include "qgsvectorlayer.h"
#include "qgsmaplayerregistry.h"


// HFP
#include "hlpproject.h"

class QgsMapLayerRegistry;
class QgsVectorLayer;




HlpProject::HlpProject()
{
  QSettings settings;
  mEpsg = settings.value( "/hlp/default_crs", 21781 ).toInt();
  mPath = "";
}

QMap<QString, QgsMapLayer*> HlpProject::createLayers()
{
  QSettings settings;
  mEpsg = settings.value( "/hlp/default_crs", 21781 ).toInt();

  QMap<QString,QgsMapLayer*> layerList;
  QList<HlpField> fields;

  // flightlines
  fields = QList<HlpField>() << HlpField("pkid", "integer")
                             << HlpField("number","integer")
                             << HlpField("comment","text");
  layerList.insert("flightline", new QgsVectorLayer( createUri( "LineString", fields, epsg ), "Flight lines", "memory" ) );

  // profiles
  fields = QList<HlpField>() << HlpField("pkid", "integer")
                             << HlpField("values","text");
  layerList.insert("profile", new QgsVectorLayer( createUri( "LineString", fields, epsg ), "Profiles", "memory" ) );

  // way points
  fields = QList<HlpField>() << HlpField("id_flightline", "integer")
                             << HlpField("type","string")
                             << HlpField("id_profile","integer")
                             << HlpField("dz","double");
  layerList.insert("waypoint",  new QgsVectorLayer( createUri( "Point", fields, epsg ), "Way points", "memory" ) );

  if ( layerList != QgsMapLayerRegistry::instance()->addMapLayers( layerList, true, false ) )
    return QMap<QString,QgsMapLayer*>();

  return layerList;
}


QString HlpProject::createUri( QString geomType, QList<HlpField> fields, int epsg)
{
  QString uri = QString("%1?crs=%2").arg(geomType).arg(epsg);
  foreach( HlpField field, fields)
   uri += QString("&field=%1:%2").arg(field.first).arg(field.second);
  uri += "&index=yes";
  return uri;
}
