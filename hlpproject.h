#ifndef HLPPROJECT_H
#define HLPPROJECT_H

#include <QString>

#include <sqlite3.h>
#include <spatialite.h>

#include "qgsmaplayerregistry.h"
#include "qgsvectorlayer.h"


class HlpProject
{
  public:
    HlpProject();

    // access coordinate system info
    int epsg(){ return mEpsg; }
    void setEpsg( int epsg ){ mEpsg = epsg; }

private:
    QString mPath;
    int mEpsg;

    bool readProperty(QString property, int &value);

    QgsVectorLayer* mFightlineLayer;
    QgsVectorLayer* mFlightlinecover;
    QgsVectorLayer* mProfileLayer;
    QList<QgsVectorLayer*> mRasterLayers;
    QList<QgsVectorLayer*> mDtmLayers;
    QgsVectorLayer* mPropertyLayer;


};

#endif // PROJECT_H
