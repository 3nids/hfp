
#include <QMouseEvent>
#include <QMessageBox>

#include "qgsmapcanvas.h"
#include "qgsvectorlayer.h"
#include "qgsvectorlayereditbuffer.h"

#include "hlpaddprofile.h"




HlpAddProfile::HlpAddProfile( QgsMapCanvas* canvas, QgsVectorLayer* profileLayer ) :
  HlpMapToolCapture(canvas, profileLayer)
{
}


HlpAddProfile::~HlpAddProfile()
{
}


void HlpAddProfile::activate()
{
  if ( !mCanvas || mCanvas->isDrawing() )
  {
    return;
  }

  QgsMapTool::activate();
}

void HlpAddProfile::canvasReleaseEvent( QMouseEvent * e )
{
  //add point to list and to rubber band
  if ( e->button() == Qt::LeftButton )
  {
    int error = addVertex( e->pos() );
    if ( error == 1 )
    {
      //current layer is not a vector layer
      return;
    }
    else if ( error == 2 )
    {
      //problem with coordinate transformation
      QMessageBox::information( 0, tr( "Coordinate transform error" ),
                                tr( "Cannot transform the point to the layers coordinate system" ) );
      return;
    }

    startCapturing();
  }
  else if ( e->button() == Qt::RightButton )
  {
    // End of string
    deleteTempRubberBand();

    //lines: bail out if there are not at least two vertices
    if ( size() < 2 )
    {
      stopCapturing();
      return;
    }

    //create QgsFeature with wkb representation
    QgsFeature f = QgsFeature( mLayer->pendingFields(),  0 );

    QgsGeometry *g;
    g = QgsGeometry::fromPolyline( points().toVector() );
    f.setGeometry( g );
    mLayer->beginEditCommand( tr( "Feature added" ) );

    if ( mLayer->editBuffer()->addFeature( f ) )
    {
      mLayer->endEditCommand();
    }
    else
    {
      mLayer->destroyEditCommand();
    }

    stopCapturing();
  }
}
