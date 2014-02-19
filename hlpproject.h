#ifndef HLPPROJECT_H
#define HLPPROJECT_H

#include <QString>

#include "qgsmaplayerregistry.h"
#include "qgsvectorlayer.h"


class HlpProject
{
  public:
    HlpProject();

    //! access coordinate system info
    int epsg(){ return mEpsg; }
    void setEpsg( int epsg ){ mEpsg = epsg; }

    //! create the layers and add them to the map canvas
    static QMap<QString, QgsMapLayer*> createLayers();
    //! create a URI string for the given geometry type and fields
    static QString createUri(QString geomType, QList<HlpField> fields, int epsg);


private:
    QString mPath;
    int mEpsg;

    bool readProperty(QString property, int &value);


};

#endif // HLPPROJECT_H
