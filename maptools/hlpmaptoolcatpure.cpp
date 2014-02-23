#include "hlpmaptoolcatpure.h"

HlpMapToolCapture::HlpMapToolCapture(QgsMapCanvas* canvas, QgsVectorLayer* profileLayer) :
  HlpMapToolEdit(canvas)
  , mLayer( profileLayer )
{
  mCapturing = false;

  QPixmap mySelectQPixmap = QPixmap(( const char ** ) capture_point_cursor );
    mCursor = QCursor( mySelectQPixmap, 8, 8 );
}


HlpMapToolCapture::~HlpMapToolCapture()
{
  stopCapturing();
}

void HlpAddProfile::deactivate()
{
  HlpMapToolEdit::deactivate();
}


void HlpMapToolCapture::canvasMoveEvent( QMouseEvent * e )
{
} // mouseMoveEvent


void HlpMapToolCapture::canvasPressEvent( QMouseEvent *e )
{
  Q_UNUSED( e );
  // nothing to be done
}

int HlpMapToolCapture::nextPoint( const QPoint &p )
{
  QgsPoint digitisedPoint;
  try
  {
    digitisedPoint = toLayerCoordinates( mLayer, p );
  }
  catch ( QgsCsException &cse )
  {
    Q_UNUSED( cse );
    QgsDebugMsg( "transformation to layer coordinate failed" );
    return 2;
  }

  return 0;
}


int HlpMapToolCapture::addVertex( const QPoint &p )
{
  QgsPoint mapPoint;

  int res = nextPoint( p );
  if ( res != 0 )
  {
    QgsDebugMsg( "nextPoint failed: " + QString::number( res ) );
    return res;
  }

  if ( !mRubberBand )
  {
    mRubberBand = createRubberBand( QGis::Line );
  }
  mRubberBand->addPoint( mapPoint );

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
  QgisApp::instance()->skipNextContextMenuEvent();
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

  switch ( mCaptureMode )
  {
    case CaptureNone:
    case CapturePoint:
      return;
    case CaptureLine:
      if ( mCaptureList.size() < 2 )
        return;
      g = QgsGeometry::fromPolyline( mCaptureList.toVector() );
      break;
    case CapturePolygon:
      if ( mCaptureList.size() < 3 )
        return;
      g = QgsGeometry::fromPolygon( QgsPolygon() << ( QgsPolyline() << mCaptureList.toVector() << mCaptureList[0] ) );
      break;
  }

  if ( !g )
    return;

  mValidator = new QgsGeometryValidator( g );
  connect( mValidator, SIGNAL( errorFound( QgsGeometry::Error ) ), this, SLOT( addError( QgsGeometry::Error ) ) );
  connect( mValidator, SIGNAL( finished() ), this, SLOT( validationFinished() ) );
  mValidator->start();

  QStatusBar *sb = QgisApp::instance()->statusBar();
  sb->showMessage( tr( "Validation started." ) );
}

void HlpMapToolCapture::addError( QgsGeometry::Error e )
{
  mGeomErrors << e;
  QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>( mCanvas->currentLayer() );
  if ( !vlayer )
    return;

  if ( !mTip.isEmpty() )
    mTip += "\n";

  mTip += e.what();

  if ( e.hasWhere() )
  {
    QgsVertexMarker *vm =  new QgsVertexMarker( mCanvas );
    vm->setCenter( mCanvas->mapSettings().layerToMapCoordinates( vlayer, e.where() ) );
    vm->setIconType( QgsVertexMarker::ICON_X );
    vm->setPenWidth( 2 );
    vm->setToolTip( e.what() );
    vm->setColor( Qt::green );
    vm->setZValue( vm->zValue() + 1 );
    mGeomErrorMarkers << vm;
  }

  QStatusBar *sb = QgisApp::instance()->statusBar();
  sb->showMessage( e.what() );
  if ( !mTip.isEmpty() )
    sb->setToolTip( mTip );
}

void HlpMapToolCapture::validationFinished()
{
  QStatusBar *sb = QgisApp::instance()->statusBar();
  sb->showMessage( tr( "Validation finished." ) );
}
