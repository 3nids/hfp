#include "hlpaddprofile.h"

HlpAddProfile::HlpAddProfile(QgsMapCanvas* canvas, QgsVectorLayer* profileLayer) :
  HlpMapToolCapture(canvas)
  , mLayer( profileLayer )
{
}


HlpAddProfile::~HlpAddProfile()
{
}


bool HlpAddProfile::addFeature( QgsFeature *f )
{
  QgsFeatureAction action( tr( "add feature" ), *f, mLayer, -1, -1, this );
  return action.addFeature();
}

void QgsMapToolAddFeature::activate()
{
  if ( !mCanvas || mCanvas->isDrawing() )
  {
    return;
  }

  QgsMapTool::activate();
}

void QgsMapToolAddFeature::canvasReleaseEvent( QMouseEvent * e )
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
    QgsFeature* f = new QgsFeature( mLayer->pendingFields(),  0 );

    QgsGeometry *g;
    g = QgsGeometry::fromPolyline( points().toVector() );
    f->setGeometry( g );
    mLayer->beginEditCommand( tr( "Feature added" ) );

    if ( addFeature( vlayer, f ) )
    {
      vlayer->endEditCommand();
    }
    else
    {
      delete f;
      vlayer->destroyEditCommand();
    }

    stopCapturing();
  }
}
