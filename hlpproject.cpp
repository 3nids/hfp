

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

