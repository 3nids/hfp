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

    void canvasReleaseEvent( QMouseEvent * e );

    void activate();
  signals:

  public slots:

  private:

};

#endif // HLPADDPROFILE_H
