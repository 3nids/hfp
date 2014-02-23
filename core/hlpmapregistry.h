#ifndef HLPMAPREGISTRY_H
#define HLPMAPREGISTRY_H

#include <QAbstractListModel>

#include "qgsrasterlayer.h"
#include "qgsmapcanvas.h"

class HlpMapRegistry : public QAbstractListModel
{
  Q_OBJECT
  public:
    //! Returns the instance pointer, creating the object on the first call
    static HlpMapRegistry * instance();

    explicit HlpMapRegistry(QObject *parent = 0);

    bool addMapLayer( QgsRasterLayer* layer );

    QList<QgsMapCanvasLayer> layers();

  signals:
    void layersChanged( bool updateExtent );

  public slots:

  private:
    static HlpMapRegistry *mInstance;
    QList<QgsMapCanvasLayer> mMaps;



  // QAbstractItemModel interface
  public:
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const {return 1;}
    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // HLPMAPREGISTRY_H
