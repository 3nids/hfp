#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

#include <sqlite3.h>
#include <spatialite.h>

#include "qgsmaplayerregistry.h"


class Project
{
public:
    Project();

    static bool openProject( QString dbPath );

    static bool createEmptyProject( QString dbPath, int epsg );
};

#endif // PROJECT_H
