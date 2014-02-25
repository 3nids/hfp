#ifndef HLPMAPTOOLCATPURE_H
#define HLPMAPTOOLCATPURE_H

#include "qgsgeometryvalidator.h"
#include "qgsvectorlayer.h"
#include "qgsvertexmarker.h"

#include "hlpmaptooledit.h"


class HlpMapToolCapture : public HlpMapToolEdit
{
    Q_OBJECT
  public:
    explicit HlpMapToolCapture(QgsMapCanvas *canvas, QgsVectorLayer* layer );

    //! destructor
    virtual ~HlpMapToolCapture();

    //! Overridden mouse move event
    virtual void canvasMoveEvent( QMouseEvent * e );

    //! Overridden mouse press event
    virtual void canvasPressEvent( QMouseEvent * e );

    //! Overridden mouse release event
    virtual void canvasReleaseEvent( QMouseEvent * e ) = 0;

    virtual void keyPressEvent( QKeyEvent* e );

    //! deactive the tool
    virtual void deactivate();

  signals:

  public slots:
    void addError( QgsGeometry::Error );
    void validationFinished();

  protected:
    int nextPoint( const QPoint &p );

    /**Adds a point to the rubber band (in map coordinates) and to the capture list (in layer coordinates)
     @return 0 in case of success, 1 if current layer is not a vector layer, 2 if coordinate transformation failed*/
    int addVertex( const QPoint& p );

    /**Removes the last vertex from mRubberBand and mCaptureList*/
    void undo();

    void startCapturing();
    void stopCapturing();
    void deleteTempRubberBand();


    int size() { return mCaptureList.size(); }
    QList<QgsPoint>::iterator begin() { return mCaptureList.begin(); }
    QList<QgsPoint>::iterator end() { return mCaptureList.end(); }
    const QList<QgsPoint> &points() { return mCaptureList; }
    void setPoints( const QList<QgsPoint>& pointList ) { mCaptureList = pointList; }

    QgsVectorLayer* mLayer;

  private:
    bool mCapturing;

    /** rubber band for polylines and polygons */
    QgsRubberBand* mRubberBand;

    /** temporary rubber band for polylines and polygons. this connects the last added point to the mouse cursor position */
    QgsRubberBand* mTempRubberBand;

    /** List to store the points of digitised lines and polygons (in layer coordinates)*/
    QList<QgsPoint> mCaptureList;

    void validateGeometry();
    QString mTip;
    QgsGeometryValidator *mValidator;
    QList< QgsGeometry::Error > mGeomErrors;
    QList< QgsVertexMarker * > mGeomErrorMarkers;
};

#endif // HLPMAPTOOLCATPURE_H
