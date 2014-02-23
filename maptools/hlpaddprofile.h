#ifndef HLPADDPROFILE_H
#define HLPADDPROFILE_H

#include "qgsvectorlayer.h"

#include "hlpmaptoolcatpure.h"


class HlpAddProfile : public HlpMapToolCapture
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

#endif // HLPADDPROFILE_H
