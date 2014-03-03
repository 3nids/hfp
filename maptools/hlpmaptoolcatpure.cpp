#include <QKeyEvent>
#include <QStatusBar>
#include <QCursor>
#include <QPixmap>


#include "qgscursors.h"
#include "qgsmapcanvas.h"
#include "qgsvectorlayer.h"
#include "qgspoint.h"

#include "../app/hlpflightplannerapp.h"

#include "hlpmaptoolcatpure.h"



HlpMapToolCapture::HlpMapToolCapture(QgsMapCanvas* canvas, QgsVectorLayer *layer) :
  HlpMapToolEdit(canvas)
  , mLayer( layer )
  , mRubberBand( 0 )
  , mTempRubberBand( 0 )
  , mValidator( 0 )
{
  mCapturing = false;

  QPixmap mySelectQPixmap = QPixmap(( const char ** ) capture_point_cursor );
  mCursor = QCursor( mySelectQPixmap, 8, 8 );
}


HlpMapToolCapture::~HlpMapToolCapture()
{
  stopCapturing();
}

void HlpMapToolCapture::deactivate()
{
  HlpMapToolEdit::deactivate();
}


void HlpMapToolCapture::canvasMoveEvent( QMouseEvent * e )
{
  if ( mTempRubberBand && mCapturing )
  {
    QgsPoint mapPoint = toMapCoordinates( e->pos() );
    mTempRubberBand->movePoint( mapPoint );
  }
} // mouseMoveEvent


void HlpMapToolCapture::canvasPressEvent( QMouseEvent *e )
{
  Q_UNUSED( e );
  // nothing to be done
}


int HlpMapToolCapture::addVertex( const QPoint &p )
{
  if ( !mRubberBand )
  {
    mRubberBand = createRubberBand( QGis::Line );
  }

  QgsPoint mapPoint = toMapCoordinates( p );
  mRubberBand->addPoint( mapPoint );
  mCaptureList.append( toLayerCoordinates( mLayer, mapPoint ) );

  if ( !mTempRubberBand )
  {
    mTempRubberBand = createRubberBand( QGis::Line , true );
  }
  else
  {
    mTempRubberBand->reset( false );
  }

  mTempRubberBand->addPoint( mapPoint );

  validateGeometry();

  return 0;
}

void HlpMapToolCapture::undo()
{
  if ( mRubberBand )
  {
    int rubberBandSize = mRubberBand->numberOfVertices();
    int tempRubberBandSize = mTempRubberBand->numberOfVertices();
    int captureListSize = mCaptureList.size();

    if ( rubberBandSize < 1 || captureListSize < 1 )
    {
      return;
    }

    mRubberBand->removePoint( -1 );

    if ( rubberBandSize > 1 )
    {
      if ( tempRubberBandSize > 1 )
      {
        const QgsPoint *point = mRubberBand->getPoint( 0, rubberBandSize - 2 );
        mTempRubberBand->movePoint( tempRubberBandSize - 2, *point );
      }
    }
    else
    {
      mTempRubberBand->reset( false );
    }

    mCaptureList.removeLast();

    validateGeometry();
  }
}

void HlpMapToolCapture::keyPressEvent( QKeyEvent* e )
{
  if ( e->key() == Qt::Key_Backspace || e->key() == Qt::Key_Delete )
  {
    undo();

    // Override default shortcut management in MapCanvas
    e->ignore();
  }
}

void HlpMapToolCapture::startCapturing()
{
  mCapturing = true;
}

void HlpMapToolCapture::stopCapturing()
{
  if ( mRubberBand )
  {
    delete mRubberBand;
    mRubberBand = 0;
  }

  if ( mTempRubberBand )
  {
    delete mTempRubberBand;
    mTempRubberBand = 0;
  }

  while ( !mGeomErrorMarkers.isEmpty() )
  {
    delete mGeomErrorMarkers.takeFirst();
  }

  mGeomErrors.clear();

#ifdef Q_OS_WIN
  // hope your wearing your peril sensitive sunglasses.
  // todo
  //HlpFlightPlannerApp::instance()->skipNextContextMenuEvent();
#endif

  mCapturing = false;
  mCaptureList.clear();
  mCanvas->refresh();
}

void HlpMapToolCapture::deleteTempRubberBand()
{
  if ( mTempRubberBand )
  {
    delete mTempRubberBand;
    mTempRubberBand = 0;
  }
}

void HlpMapToolCapture::validateGeometry()
{
  QSettings settings;
  if ( settings.value( "/qgis/digitizing/validate_geometries", 1 ).toInt() == 0 )
    return;

  if ( mValidator )
  {
    mValidator->deleteLater();
    mValidator = 0;
  }

  mTip = "";
  mGeomErrors.clear();
  while ( !mGeomErrorMarkers.isEmpty() )
  {
    delete mGeomErrorMarkers.takeFirst();
  }

  QgsGeometry *g = 0;

  if ( mCaptureList.size() < 2 )
    return;
  g = QgsGeometry::fromPolyline( mCaptureList.toVector() );

  if ( !g )
    return;

  mValidator = new QgsGeometryValidator( g );
  connect( mValidator, SIGNAL( errorFound( QgsGeometry::Error ) ), this, SLOT( addError( QgsGeometry::Error ) ) );
  mValidator->start();
}

void HlpMapToolCapture::addError( QgsGeometry::Error e )
{
  mGeomErrors << e;
  if ( !mLayer )
    return;

  if ( !mTip.isEmpty() )
    mTip += "\n";

  mTip += e.what();

  if ( e.hasWhere() )
  {
    QgsVertexMarker *vm =  new QgsVertexMarker( mCanvas );
    vm->setCenter( mCanvas->mapSettings().layerToMapCoordinates( mLayer, e.where() ) );
    vm->setIconType( QgsVertexMarker::ICON_X );
    vm->setPenWidth( 2 );
    vm->setToolTip( e.what() );
    vm->setColor( Qt::green );
    vm->setZValue( vm->zValue() + 1 );
    mGeomErrorMarkers << vm;
  }

  emit displayMessage( e.what(), QgsMessageBar::WARNING );
}
