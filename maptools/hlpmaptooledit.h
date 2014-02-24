#ifndef QGSMAPTOOLEDIT_H
#define QGSMAPTOOLEDIT_H

#include "qgsmaptool.h"
#include "qgsrubberband.h"

class QgsRubberBand;
class QKeyEvent;
class QgsMapCanvas;

/**Base class for map tools that edit vector geometry*/
class HlpMapToolEdit: public QgsMapTool
{
  public:
    HlpMapToolEdit( QgsMapCanvas* canvas );
    virtual ~HlpMapToolEdit();

    virtual bool isEditTool() { return true; }

  protected:
    /**keeps trace of last displayed message*/
    QgsMessageBarItem * mMessageItem;

    /** Creates a rubber band with the color/line width from
    *   the QGIS settings. The caller takes ownership of the
    *   returned object
    *   @param geometryType
    *   @param alternativeBand if true, rubber band will be set with more transparency and a dash pattern. defaut is false.
    */
    QgsRubberBand* createRubberBand( QGis::GeometryType geometryType = QGis::Line , bool alternativeBand = false );
};

#endif
