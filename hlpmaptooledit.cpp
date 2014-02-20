/***************************************************************************
    qgsmaptooledit.cpp  -  base class for editing map tools
    ---------------------
    begin                : Juli 2007
    copyright            : (C) 2007 by Marco Hugentobler
    email                : marco dot hugentobler at karto dot baug dot ethz dot ch
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <QKeyEvent>
#include <QSettings>

#include "qgsmessagebar.h"
#include "qgsrubberband.h"

#include "hlpmaptooledit.h"

HlpMapToolEdit::HlpMapToolEdit( QgsMapCanvas* canvas )
    : QgsMapTool( canvas )
{
}


HlpMapToolEdit::~HlpMapToolEdit()
{
}

QgsRubberBand* HlpMapToolEdit::createRubberBand( QGis::GeometryType geometryType, bool alternativeBand )
{
  QSettings settings;
  QgsRubberBand* rb = new QgsRubberBand( mCanvas, geometryType );
  rb->setWidth( settings.value( "/hlp/digitizing/line_width", 1 ).toInt() );
  QColor color( settings.value( "/hlp/digitizing/line_color_red", 255 ).toInt(),
                settings.value( "/hlp/digitizing/line_color_green", 0 ).toInt(),
                settings.value( "/hlp/digitizing/line_color_blue", 0 ).toInt() );
  double myAlpha = settings.value( "/hlp/digitizing/line_color_alpha", 200 ).toInt() / 255.0 ;
  if ( alternativeBand )
  {
    myAlpha = myAlpha * settings.value( "/hlp/digitizing/line_color_alpha_scale" , 0.75 ).toDouble();
    rb->setLineStyle( Qt::DotLine );
  }
  if ( geometryType == QGis::Polygon )
  {
    color.setAlphaF( myAlpha );
  }
  color.setAlphaF( myAlpha );
  rb->setColor( color );
  rb->show();
  return rb;
}



