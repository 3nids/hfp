#include "hlpmapregistry.h"
#include "qgsmaplayerregistry.h"

// Static calls to enforce singleton behaviour
HlpMapRegistry *HlpMapRegistry::mInstance = 0;
HlpMapRegistry *HlpMapRegistry::instance()
{
  if ( mInstance == 0 )
  {
    mInstance = new HlpMapRegistry();
  }
  return mInstance;
}


HlpMapRegistry::HlpMapRegistry(QObject *parent) :
  QAbstractListModel(parent)
{
}

bool HlpMapRegistry::addMapLayer(QgsRasterLayer *layer)
{
  if ( layer && layer->isValid() )
  {
    QgsMapLayerRegistry::instance()->addMapLayer(layer, false);
    mMaps << layer;
    emit layersChanged();
    return true;
  }
  return false;
}

QList<QgsMapCanvasLayer> HlpMapRegistry::layers()
{
  QList<QgsMapCanvasLayer> layers;

  foreach (QgsRasterLayer* layer, mMaps ) {
    layers << QgsMapCanvasLayer( layer, true );
  }

  return layers;
}

int HlpMapRegistry::rowCount(const QModelIndex& parent) const
{
}

QVariant HlpMapRegistry::data(const QModelIndex& index, int role) const
{
  if ( role == Qt::DisplayRole && index.row() <= mMaps.count() )
  {
     return mMaps.at(index.row())->name();
  }
  return QVariant();
}
