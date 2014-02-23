#include "hlpmapregistry.h"
#include "qgsmaplayerregistry.h"
#include "qgsmapcanvas.h"

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


HlpMapRegistry::HlpMapRegistry( QObject *parent ) :
  QAbstractListModel(parent)
{
}

bool HlpMapRegistry::addMapLayer( QgsRasterLayer *layer )
{
  if ( layer && layer->isValid() )
  {
    QgsMapLayerRegistry::instance()->addMapLayer( layer, false );
    mMaps.insert( 0, QgsMapCanvasLayer( layer, true ) );
    QModelIndex index = createIndex( 0, 0 );
    emit dataChanged( index, index );
    emit layersChanged( true );
    return true;
  }
  return false;
}

QList<QgsMapCanvasLayer> HlpMapRegistry::layers()
{
  return mMaps;
}

int HlpMapRegistry::rowCount(const QModelIndex& parent) const
{
  return mMaps.count();
}

QVariant HlpMapRegistry::data(const QModelIndex& index, int role) const
{
  if ( mMaps.count()==0 || index.row() > mMaps.count() || index.row() < 0 )
  {
    return QVariant();
  }

  const QgsMapCanvasLayer item = mMaps.at(index.row());

  switch (role)
  {
    case Qt::DisplayRole:
    {
      return item.layer()->name();
    }
    case Qt::CheckStateRole:
    {
      if ( item.isVisible() )
        return Qt::Checked;
      else
        return Qt::Unchecked;
    }
  }
  return QVariant();
}

bool HlpMapRegistry::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if ( role == Qt::CheckStateRole && index.row() >= 0 && index.row() <= mMaps.count() )
  {
    mMaps[index.row()].setVisible( value == Qt::Checked );
    emit layersChanged( false );
  }
  return true;
}

Qt::ItemFlags HlpMapRegistry::flags(const QModelIndex &index) const
{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}
