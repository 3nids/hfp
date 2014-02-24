#ifndef HLPADDPROFILE_H
#define HLPADDPROFILE_H

#include "qgsvectorlayer.h"

#include "hlpmaptoolcatpure.h"


class HlpAddProfile : public HlpMapToolCapture
{
    Q_OBJECT
  public:
    explicit HlpAddProfile(QgsMapCanvas *canvas, QgsVectorLayer* profileLayer);

    //! destructor
    virtual ~HlpAddProfile();

    //! Overridden mouse release event
    virtual void canvasReleaseEvent( QMouseEvent * e ) = 0;

    void activate();
  signals:

  public slots:

  private:

};

#endif // HLPADDPROFILE_H
