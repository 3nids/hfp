#ifndef HLPPROJECT_H
#define HLPPROJECT_H

#include <QString>

#include <sqlite3.h>
#include <spatialite.h>

#include "qgsmaplayerregistry.h"


class HlpProject
{
  public:
    typedef QPair<QString, QString> HlpLayer;

    HlpProject(QString projectPath);

    static HlpProject* openProject( QString dbPath );

    static bool createEmptyProject( QString dbPath, int epsg );

    // access coordinate system info
    int srsId(){ return mSrsId; }
    void setSrdId( int srsId ){ mSrsId = srsId; }

private:
    QString mProjectPath;
    int mSrsId;

    bool readProperty(QString property, int &value);
};

#endif // PROJECT_H
