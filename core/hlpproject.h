#ifndef HLPPROJECT_H
#define HLPPROJECT_H

#include <QString>

#include "qgsmaplayerregistry.h"
#include "qgsvectorlayer.h"
#include "qgscoordinatereferencesystem.h"

class HlpProject
{
  public:
    typedef QPair<QString, QString> HlpField;

    //! Returns the instance pointer, creating the object on the first call
    static HlpProject * instance();

    HlpProject();

    //! access coordinate system info
    QgsCoordinateReferenceSystem crs();
    int epsg(){ return mEpsg; }
    void setEpsg( int epsg );

    //! create the layers and add them to the map canvas
    QMap<QString, QgsMapLayer*> createLayers();
    //! create a URI string for the given geometry type and fields
    QString createUri(QString geomType, QList<HlpField> fields, int epsg);




private:
    QString mPath;
    int mEpsg;
    static HlpProject* mInstance;

    bool readProperty(QString property, int &value);


};

#endif // HLPPROJECT_H
