#ifndef HLPAMAPTOOLCATPURE_H
#define HLPAMAPTOOLCATPURE_H

#include "qgsvectorlayer.h"

#include "hlpmaptooledit.h"


class HlpMapToolCapture : public HlpMapToolEdit
{
    Q_OBJECT
  public:
    explicit HlpAddProfile(QgsMapCanvas *canvas = 0, QgsVectorLayer* profileLayer);

    //! destructor
    virtual ~HlpAddProfile();

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

  private:
    QgsVectorLayer* mLayer;
    bool mCapturing;

};

#endif // HLPAMAPTOOLCATPURE_H
