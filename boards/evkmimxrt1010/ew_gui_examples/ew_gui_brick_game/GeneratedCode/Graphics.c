/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This software is delivered "as is" and shows the usage of other software 
* components. It is provided as an example software which is intended to be 
* modified and extended according to particular requirements.
* 
* TARA Systems hereby disclaims all warranties and conditions with regard to the
* software, including all implied warranties and conditions of merchantability 
* and non-infringement of any third party IPR or other rights which may result 
* from the use or the inability to use the software.
*
* This file was generated automatically by Embedded Wizard Studio.
*
* Please do not make any modifications of this file! The modifications are lost
* when the file is generated again by Embedded Wizard Studio!
*
* Version  : 10.0
* Date     : 17.02.2021  8:00:50
* Profile  : iMX_RT
* Platform : NXP.iMX_RT.RGB565
*
*******************************************************************************/

#include "ewlocale.h"
#include "_GraphicsCanvas.h"
#include "_ResourcesBitmap.h"
#include "_ResourcesFont.h"
#include "Graphics.h"
#include "Views.h"

/* Strings for the language 'Default'. */
static const unsigned short _StringsDefault0[] =
{
  0xFFFF, 0xFFFF, 0xC557, 0x0043, 0x0061, 0x006E, 0x0020, 0x006E, 0x006F, 0x0074,
  0x0020, 0x0072, 0x0065, 0x0073, 0x0069, 0x007A, 0x0065, 0x0020, 0x0065, 0x0078,
  0x0070, 0x006C, 0x0069, 0x0063, 0x0069, 0x0074, 0x006C, 0x0079, 0x0020, 0x0061,
  0x0074, 0x0074, 0x0061, 0x0063, 0x0068, 0x0065, 0x0064, 0x0020, 0x0067, 0x0072,
  0x0061, 0x0070, 0x0068, 0x0069, 0x0063, 0x0073, 0x0020, 0x0065, 0x006E, 0x0067,
  0x0069, 0x006E, 0x0065, 0x0020, 0x0062, 0x0069, 0x0074, 0x006D, 0x0061, 0x0070,
  0x0073, 0x0000, 0xC557, 0x004E, 0x006F, 0x0020, 0x0067, 0x0072, 0x0061, 0x0070,
  0x0068, 0x0069, 0x0063, 0x0073, 0x0020, 0x0065, 0x006E, 0x0067, 0x0069, 0x006E,
  0x0065, 0x0020, 0x0062, 0x0069, 0x0074, 0x006D, 0x0061, 0x0070, 0x0020, 0x0061,
  0x0074, 0x0074, 0x0061, 0x0063, 0x0068, 0x0065, 0x0064, 0x0020, 0x0074, 0x006F,
  0x0020, 0x0074, 0x0068, 0x0069, 0x0073, 0x0020, 0x0063, 0x0061, 0x006E, 0x0076,
  0x0061, 0x0073, 0x0000, 0xC557, 0x0054, 0x0068, 0x0065, 0x0020, 0x0063, 0x0061,
  0x006E, 0x0076, 0x0061, 0x0073, 0x0020, 0x0069, 0x0073, 0x0020, 0x0061, 0x006C,
  0x0072, 0x0065, 0x0061, 0x0064, 0x0079, 0x0020, 0x0069, 0x006E, 0x0069, 0x0074,
  0x0069, 0x0061, 0x006C, 0x0069, 0x007A, 0x0065, 0x0064, 0x0020, 0x0077, 0x0069,
  0x0074, 0x0068, 0x0020, 0x0061, 0x0020, 0x0067, 0x0072, 0x0061, 0x0070, 0x0068,
  0x0069, 0x0063, 0x0073, 0x0020, 0x0065, 0x006E, 0x0067, 0x0069, 0x006E, 0x0065,
  0x0020, 0x0062, 0x0069, 0x0074, 0x006D, 0x0061, 0x0070, 0x0000, 0xC557, 0x0057,
  0x0061, 0x0072, 0x0070, 0x0042, 0x0069, 0x0074, 0x006D, 0x0061, 0x0070, 0x0028,
  0x0029, 0x0020, 0x006F, 0x0070, 0x0065, 0x0072, 0x0061, 0x0074, 0x0069, 0x006F,
  0x006E, 0x0020, 0x0068, 0x0061, 0x0073, 0x0020, 0x0062, 0x0065, 0x0065, 0x006E,
  0x0020, 0x006F, 0x006D, 0x0069, 0x0074, 0x0074, 0x0065, 0x0064, 0x0020, 0x0064,
  0x0075, 0x0065, 0x0020, 0x0074, 0x006F, 0x0020, 0x0074, 0x0068, 0x0065, 0x0020,
  0x0072, 0x0065, 0x0073, 0x0075, 0x006C, 0x0074, 0x0069, 0x006E, 0x0067, 0x0020,
  0x0061, 0x0072, 0x0065, 0x0061, 0x0020, 0x0062, 0x0065, 0x0069, 0x006E, 0x0067,
  0x0020, 0x0077, 0x0069, 0x0064, 0x0065, 0x0072, 0x0020, 0x006F, 0x0072, 0x0020,
  0x0068, 0x0069, 0x0067, 0x0068, 0x0065, 0x0072, 0x0020, 0x0074, 0x0068, 0x0061,
  0x006E, 0x0020, 0x0034, 0x0030, 0x0036, 0x0039, 0x0020, 0x0070, 0x0069, 0x0078,
  0x0065, 0x006C, 0x002E, 0x0000, 0xC557, 0x0053, 0x0063, 0x0061, 0x006C, 0x0065,
  0x0042, 0x0069, 0x0074, 0x006D, 0x0061, 0x0070, 0x0028, 0x0029, 0x0020, 0x006F,
  0x0070, 0x0065, 0x0072, 0x0061, 0x0074, 0x0069, 0x006F, 0x006E, 0x0020, 0x0068,
  0x0061, 0x0073, 0x0020, 0x0062, 0x0065, 0x0065, 0x006E, 0x0020, 0x006F, 0x006D,
  0x0069, 0x0074, 0x0074, 0x0065, 0x0064, 0x0020, 0x0064, 0x0075, 0x0065, 0x0020,
  0x0074, 0x006F, 0x0020, 0x0074, 0x0068, 0x0065, 0x0020, 0x0072, 0x0065, 0x0073,
  0x0075, 0x006C, 0x0074, 0x0069, 0x006E, 0x0067, 0x0020, 0x0061, 0x0072, 0x0065,
  0x0061, 0x0020, 0x0062, 0x0065, 0x0069, 0x006E, 0x0067, 0x0020, 0x0077, 0x0069,
  0x0064, 0x0065, 0x0072, 0x0020, 0x006F, 0x0072, 0x0020, 0x0068, 0x0069, 0x0067,
  0x0068, 0x0065, 0x0072, 0x0020, 0x0074, 0x0068, 0x0061, 0x006E, 0x0020, 0x0034,
  0x0030, 0x0036, 0x0039, 0x0020, 0x0070, 0x0069, 0x0078, 0x0065, 0x006C, 0x002E,
  0x0000
};

/* Constant values used in this 'C' module only. */
static const XPoint _Const0000 = { 0, 0 };
static const XStringRes _Const0001 = { _StringsDefault0, 0x0003 };
static const XColor _Const0002 = { 0x00, 0x00, 0x00, 0x00 };
static const XRect _Const0003 = {{ 0, 0 }, { 0, 0 }};
static const XStringRes _Const0004 = { _StringsDefault0, 0x003F };
static const XStringRes _Const0005 = { _StringsDefault0, 0x0072 };
static const XStringRes _Const0006 = { _StringsDefault0, 0x00B3 };
static const XStringRes _Const0007 = { _StringsDefault0, 0x011D };

/* Initializer for the class 'Graphics::Canvas' */
void GraphicsCanvas__Init( GraphicsCanvas _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ResourcesBitmap__Init( &_this->_Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_GCT = EW_CLASS_GCT( GraphicsCanvas );

  /* Setup the VMT pointer */
  _this->_VMT = EW_CLASS( GraphicsCanvas );

  /* Call the user defined constructor */
  GraphicsCanvas_Init( _this, aArg );
}

/* Re-Initializer for the class 'Graphics::Canvas' */
void GraphicsCanvas__ReInit( GraphicsCanvas _this )
{
  /* At first re-initialize the super class ... */
  ResourcesBitmap__ReInit( &_this->_Super );
}

/* Finalizer method for the class 'Graphics::Canvas' */
void GraphicsCanvas__Done( GraphicsCanvas _this )
{
  /* Call the user defined destructor of the class */
  GraphicsCanvas_Done( _this );

  /* Finalize this class */
  _this->_Super._VMT = EW_CLASS( ResourcesBitmap );

  /* Don't forget to deinitialize the super class ... */
  ResourcesBitmap__Done( &_this->_Super );
}

/* 'C' function for method : 'Graphics::Canvas.Done()' */
void GraphicsCanvas_Done( GraphicsCanvas _this )
{
  if ( _this->attached )
    GraphicsCanvas_DetachBitmap( _this );
}

/* 'C' function for method : 'Graphics::Canvas.Init()' */
void GraphicsCanvas_Init( GraphicsCanvas _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  _this->Super1.Mutable = 1;
}

/* 'C' function for method : 'Graphics::Canvas.OnSetFrameSize()' */
void GraphicsCanvas_OnSetFrameSize( GraphicsCanvas _this, XPoint value )
{
  XHandle handle;

  if (( value.X <= 0 ) || ( value.Y <= 0 ))
    value = _Const0000;

  if ( !EwCompPoint( value, _this->Super1.FrameSize ))
    return;

  if ( _this->attached )
  {
    EwThrow( EwLoadString( &_Const0001 ));
    return;
  }

  _this->Super1.FrameSize = value;
  _this->Super1.Animated = (XBool)(((( _this->Super1.FrameSize.X > 0 ) && ( _this->Super1.FrameSize.Y 
  > 0 )) && ( _this->Super1.FrameDelay > 0 )) && ( _this->Super1.NoOfFrames > 1 ));

  if ( _this->Super1.bitmap == 0 )
    return;

  handle = _this->Super1.bitmap;
  EwFreeBitmap((XBitmap*)handle );
  _this->Super1.bitmap = 0;
}

/* 'C' function for method : 'Graphics::Canvas.Update()' */
void GraphicsCanvas_Update( GraphicsCanvas _this )
{
  if ((( _this->Super1.bitmap == 0 ) && ( _this->Super1.FrameSize.X > 0 )) && ( 
      _this->Super1.FrameSize.Y > 0 ))
  {
    XPoint frameSize = _this->Super1.FrameSize;
    XInt32 noOfFrames = _this->Super1.NoOfFrames;
    XInt32 frameDelay = _this->Super1.FrameDelay;
    XHandle handle = 0;
    {
      handle = (XHandle)EwCreateBitmap( EW_PIXEL_FORMAT_NATIVE, frameSize, 
                                        frameDelay, noOfFrames );
    }
    _this->Super1.bitmap = handle;

    if ( _this->Super1.bitmap == 0 )
    {
      _this->Super1.FrameSize = _Const0000;
      _this->Super1.FrameDelay = 0;
      _this->Super1.NoOfFrames = 1;
    }

    _this->InvalidArea = EwNewRect2Point( _Const0000, _this->Super1.FrameSize );

    if ( !!_this->Super1.bitmap )
    {
      XInt32 dstFrameNr = _this->DstFrameNr;

      for ( _this->DstFrameNr = _this->Super1.NoOfFrames - 1; _this->DstFrameNr 
           >= 0; _this->DstFrameNr-- )
        GraphicsCanvas_FillRectangle( _this, _this->InvalidArea, _this->InvalidArea, 
        _Const0002, _Const0002, _Const0002, _Const0002, 0 );

      _this->DstFrameNr = dstFrameNr;
    }
  }

  if ( !EwIsRectEmpty( _this->InvalidArea ))
  {
    if (( _this->Super1.FrameSize.X > 0 ) && ( _this->Super1.FrameSize.Y > 0 ))
      EwSignal( _this->OnDraw, ((XObject)_this ));

    _this->InvalidArea = _Const0003;
  }
}

/* The method DetachBitmap() exists for the integration purpose with the underlying 
   target system. You will never need to invoke this method directly from your GUI 
   application. The method is invoked after the screen update is finished and the 
   canvas object should be detached from the framebuffer. */
GraphicsCanvas GraphicsCanvas_DetachBitmap( GraphicsCanvas _this )
{
  if ( !_this->attached )
  {
    EwThrow( EwLoadString( &_Const0004 ));
    return 0;
  }

  _this->Super1.bitmap = 0;
  _this->attached = 0;
  _this->Super1.FrameSize = _Const0000;
  _this->Super1.FrameDelay = 0;
  _this->Super1.NoOfFrames = 1;
  _this->Super1.Animated = 0;
  return _this;
}

/* Wrapper function for the non virtual method : 'Graphics::Canvas.DetachBitmap()' */
GraphicsCanvas GraphicsCanvas__DetachBitmap( void* _this )
{
  return GraphicsCanvas_DetachBitmap((GraphicsCanvas)_this );
}

/* The method AttachBitmap() exists for the integration purpose with the underlying 
   target system. You will never need to invoke this method directly from your GUI 
   application. The method is invoked at the beginning of the screen update.
   The method connects the canvas object with the framebuffer. */
GraphicsCanvas GraphicsCanvas_AttachBitmap( GraphicsCanvas _this, XHandle aBitmap )
{
  XInt32 noOfFrames;
  XPoint frameSize;
  XInt32 frameDelay;

  if ( _this->Super1.bitmap != 0 )
  {
    EwThrow( EwLoadString( &_Const0005 ));
    return 0;
  }

  if ( aBitmap == 0 )
    return _this;

  _this->Super1.bitmap = aBitmap;
  _this->attached = 1;
  noOfFrames = 1;
  frameSize = _Const0000;
  frameDelay = 0;
  {
    XBitmap* bmp = (XBitmap*)aBitmap;

    noOfFrames = bmp->NoOfVirtFrames;
    frameSize  = bmp->FrameSize;
    frameDelay = bmp->FrameDelay;
  }
  _this->Super1.NoOfFrames = noOfFrames;
  _this->Super1.FrameSize = frameSize;
  _this->Super1.FrameDelay = frameDelay;
  _this->Super1.Animated = (XBool)(( _this->Super1.FrameDelay > 0 ) && ( _this->Super1.NoOfFrames 
  > 1 ));
  return _this;
}

/* Wrapper function for the non virtual method : 'Graphics::Canvas.AttachBitmap()' */
GraphicsCanvas GraphicsCanvas__AttachBitmap( void* _this, XHandle aBitmap )
{
  return GraphicsCanvas_AttachBitmap((GraphicsCanvas)_this, aBitmap );
}

/* The method DrawText() draws the text row passed in the parameter aString into 
   the canvas. The font to draw the text is passed in the parameter aFont. The parameter 
   aOffset determines within aString the sign to start the drawing operation. If 
   aOffset is zero, the operation starts with the first sign. The parameter aCount 
   determines the max. number of following sigs to draw. If aCount is -1, all signs 
   until the end of the string are drawn. 
   The area to draw the text is determined by the parameter aDstRect. The parameter 
   aOrientation controls the rotation of the text. The parameter aSrcPos determines 
   the base line position of the text relative to a corner of aDstRect, which by 
   taking in account the specified text orientation serves as the origin for the 
   draw operation. For example, if the parameter aOrientation is Views::Orientation.Rotated_270, 
   the text is drawn aSrcPos pixel relative to the bottom-right corner of aDstRect. 
   The parameter aMinWidth determines the min. width in pixel of the drawn text 
   row regardless of the specified rotation. If necessary the space signs within 
   the text will be stretched to fill this area. The parameters aColorTL, aColorTR, 
   aColorBL, aColorBR determine the colors at the corresponding corners of the aDstRect 
   area.
   The parameter aClip limits the drawing operation. Pixel lying outside this area 
   remain unchanged. The last aBlend parameter controls the mode how drawn pixel 
   are combined with the pixel already existing in the destination bitmap. If aBlend 
   is 'true', the drawn pixel are alpha-blended with the background, otherwise the 
   drawn pixel will overwrite the old content. */
void GraphicsCanvas_DrawText( GraphicsCanvas _this, XRect aClip, ResourcesFont aFont, 
  XString aString, XInt32 aOffset, XInt32 aCount, XRect aDstRect, XPoint aSrcPos, 
  XInt32 aMinWidth, XEnum aOrientation, XColor aColorTL, XColor aColorTR, XColor 
  aColorBR, XColor aColorBL, XBool aBlend )
{
  XInt32 orient;
  XInt32 dstFrameNo;
  XHandle dstBitmap;
  XHandle srcFont;
  XRect tempRect;

  if ( _this->Super1.bitmap == 0 )
    ResourcesBitmap__Update( _this );

  if ( _this->Super1.bitmap == 0 )
    return;

  if ( aOffset < 0 )
    aOffset = 0;

  if ((( aFont == 0 ) || ( aFont->font == 0 )) || (( aOffset > 0 ) && ( aOffset 
      >= EwGetStringLength( aString ))))
    return;

  orient = 0;

  if ( aOrientation == ViewsOrientationRotated_90 )
    orient = 90;
  else
    if ( aOrientation == ViewsOrientationRotated_180 )
      orient = 180;
    else
      if ( aOrientation == ViewsOrientationRotated_270 )
        orient = 270;

  dstFrameNo = _this->DstFrameNr;
  dstBitmap = _this->Super1.bitmap;
  srcFont = aFont->font;
  tempRect = aClip;
  {
    EwDrawText((XBitmap*)dstBitmap, (XFont*)srcFont, aString + aOffset, aCount,
                dstFrameNo, tempRect, aDstRect, aSrcPos, aMinWidth, orient, aColorTL, aColorTR,
                aColorBR, aColorBL, aBlend );
  }
}

/* The method WarpBitmap() performs the projection of a rectangular source bitmap 
   area onto a four corner polygon within the destination canvas. The bitmap is 
   specified in the parameter aBitmap and the desired area to copy in aSrcRect. 
   In case of a multi-frame bitmap the desired frame can be selected in the parameter 
   aFrameNr.
   The destination polygon is determined by the coordinates aX1,aY1 .. aX4,aY4. 
   The coefficients aW1 .. aW4 are responsible for the perspective distortion. The 
   parameters aColor1, aColor2, aColor3, aColor4 determine the colors or opacities 
   at the corresponding corners of the polygon area. The parameter aClip limits 
   the drawing operation. Pixel lying outside this area remain unchanged. The aBlend 
   parameter controls the mode how drawn pixel are combined with the pixel already 
   existing in the destination bitmap. If aBlend is 'true', the drawn pixel are 
   alpha-blended with the background, otherwise the drawn pixel will overwrite the 
   old content. The last parameter aFilter controls the bi-linear filter. If aFilter 
   is 'true', the source bitmap pixel will be bi-linear filtered in order to get 
   better output. */
void GraphicsCanvas_WarpBitmap( GraphicsCanvas _this, XRect aClip, ResourcesBitmap 
  aBitmap, XInt32 aFrameNr, XFloat aDstX1, XFloat aDstY1, XFloat aDstW1, XFloat 
  aDstX2, XFloat aDstY2, XFloat aDstW2, XFloat aDstX3, XFloat aDstY3, XFloat aDstW3, 
  XFloat aDstX4, XFloat aDstY4, XFloat aDstW4, XRect aSrcRect, XColor aColor1, XColor 
  aColor2, XColor aColor3, XColor aColor4, XBool aBlend, XBool aFilter )
{
  XFloat x1;
  XFloat x2;
  XFloat y1;
  XFloat y2;
  XHandle dstBitmap;
  XHandle srcBitmap;
  XInt32 dstFrameNr;

  if ( _this->Super1.bitmap == 0 )
    ResourcesBitmap__Update( _this );

  if ( _this->Super1.bitmap == 0 )
    return;

  if (((( aBitmap == 0 ) || ( aBitmap->bitmap == 0 )) || ( aFrameNr < 0 )) || ( 
      aFrameNr >= aBitmap->NoOfFrames ))
    return;

  x1 = aDstX1;
  x2 = aDstX2;
  y1 = aDstY1;
  y2 = aDstY2;

  if ( aDstX2 < x1 )
    x1 = aDstX2;

  if ( aDstX3 < x1 )
    x1 = aDstX3;

  if ( aDstX4 < x1 )
    x1 = aDstX4;

  if ( aDstX2 > x2 )
    x2 = aDstX2;

  if ( aDstX3 > x2 )
    x2 = aDstX3;

  if ( aDstX4 > x2 )
    x2 = aDstX4;

  if ( aDstY2 < y1 )
    y1 = aDstY2;

  if ( aDstY3 < y1 )
    y1 = aDstY3;

  if ( aDstY4 < y1 )
    y1 = aDstY4;

  if ( aDstY2 > y2 )
    y2 = aDstY2;

  if ( aDstY3 > y2 )
    y2 = aDstY3;

  if ( aDstY4 > y2 )
    y2 = aDstY4;

  if ((((( x2 - x1 ) > 4096.000000f ) || (( x2 - x1 ) < -4096.000000f )) || (( y2 
      - y1 ) > 4096.000000f )) || (( y2 - y1 ) < -4096.000000f ))
  {
    EwTrace( "%s", EwLoadString( &_Const0006 ));
    return;
  }

  dstBitmap = _this->Super1.bitmap;
  srcBitmap = aBitmap->bitmap;
  dstFrameNr = _this->DstFrameNr;
  {
    EwWarpBitmap((XBitmap*)dstBitmap, (XBitmap*)srcBitmap, dstFrameNr, aFrameNr,
                  aClip, aDstX1, aDstY1, aDstW1, aDstX2, aDstY2, aDstW2, 
                  aDstX3, aDstY3, aDstW3, aDstX4, aDstY4, aDstW4, aSrcRect, aColor1,
                  aColor2, aColor3, aColor4, aBlend, aFilter );
  }
}

/* The method ScaleBitmap() copies and scales an area of a aBitmap into the canvas. 
   The bitmap is specified in the parameter aBitmap and the desired area to copy 
   in aSrcRect. In case of a multi-frame bitmap the desired frame can be selected 
   in the parameter aFrameNr.
   The destination area in canvas is determined by the parameter aDstRect. The parameters 
   aColorTL, aColorTR, aColorBL, aColorBR determine the colors or opacities at the 
   corresponding corners of the aDstRect area.
   The parameter aClip limits the drawing operation. Pixel lying outside this area 
   remain unchanged. The aBlend parameter controls the mode how drawn pixel are 
   combined with the pixel already existing in the destination bitmap. If aBlend 
   is 'true', the drawn pixel are alpha-blended with the background, otherwise the 
   drawn pixel will overwrite the old content. The last parameter aFilter controls 
   the bi-linear filter. If aFilter is 'true', the source bitmap pixel will be bi-linear 
   filtered in order to get better output. */
void GraphicsCanvas_ScaleBitmap( GraphicsCanvas _this, XRect aClip, ResourcesBitmap 
  aBitmap, XInt32 aFrameNr, XRect aDstRect, XRect aSrcRect, XColor aColorTL, XColor 
  aColorTR, XColor aColorBR, XColor aColorBL, XBool aBlend, XBool aFilter )
{
  XFloat top;
  XFloat left;
  XFloat right;
  XFloat bottom;
  XHandle dstBitmap;
  XHandle srcBitmap;
  XInt32 dstFrameNo;

  if ( _this->Super1.bitmap == 0 )
    ResourcesBitmap__Update( _this );

  if ( _this->Super1.bitmap == 0 )
    return;

  if (((( aBitmap == 0 ) || ( aBitmap->bitmap == 0 )) || ( aFrameNr < 0 )) || ( 
      aFrameNr >= aBitmap->NoOfFrames ))
    return;

  top = (XFloat)aDstRect.Point1.Y;
  left = (XFloat)aDstRect.Point1.X;
  right = (XFloat)aDstRect.Point2.X;
  bottom = (XFloat)aDstRect.Point2.Y;

  if ((((( right - left ) > 4096.000000f ) || (( right - left ) < -4096.000000f )) 
      || (( bottom - top ) > 4096.000000f )) || (( bottom - top ) < -4096.000000f ))
  {
    EwTrace( "%s", EwLoadString( &_Const0007 ));
    return;
  }

  dstBitmap = _this->Super1.bitmap;
  srcBitmap = aBitmap->bitmap;
  dstFrameNo = _this->DstFrameNr;
  {
    EwWarpBitmap((XBitmap*)dstBitmap, (XBitmap*)srcBitmap, dstFrameNo, aFrameNr, aClip,
                  left,  top,    1.0f, right, top,    1.0f,
                  right, bottom, 1.0f, left,  bottom, 1.0f,
                  aSrcRect, aColorTL, aColorTR, aColorBR, aColorBL, aBlend, aFilter );
  }
}

/* The method CopyBitmap() copies an area of a aBitmap into the canvas. The bitmap 
   is specified in the parameter aBitmap. In case of a multi-frame bitmap the desired 
   frame can be selected in the parameter aFrameNr.
   The area to copy the bitmap is determined by the parameter aDstRect. The optional 
   aSrcPos parameter determines a displacement of the bitmap within this aDstRect 
   area. The parameters aColorTL, aColorTR, aColorBL, aColorBR determine the colors 
   or opacities at the corresponding corners of the aDstRect area.
   The parameter aClip limits the drawing operation. Pixel lying outside this area 
   remain unchanged. The last aBlend parameter controls the mode how drawn pixel 
   are combined with the pixel already existing in the destination bitmap. If aBlend 
   is 'true', the drawn pixel are alpha-blended with the background, otherwise the 
   drawn pixel will overwrite the old content. */
void GraphicsCanvas_CopyBitmap( GraphicsCanvas _this, XRect aClip, ResourcesBitmap 
  aBitmap, XInt32 aFrameNr, XRect aDstRect, XPoint aSrcPos, XColor aColorTL, XColor 
  aColorTR, XColor aColorBR, XColor aColorBL, XBool aBlend )
{
  XHandle dstBitmap;
  XHandle srcBitmap;
  XInt32 dstFrameNr;

  if ( _this->Super1.bitmap == 0 )
    ResourcesBitmap__Update( _this );

  if ( _this->Super1.bitmap == 0 )
    return;

  if (((( aBitmap == 0 ) || ( aBitmap->bitmap == 0 )) || ( aFrameNr < 0 )) || ( 
      aFrameNr >= aBitmap->NoOfFrames ))
    return;

  dstBitmap = _this->Super1.bitmap;
  srcBitmap = aBitmap->bitmap;
  dstFrameNr = _this->DstFrameNr;
  {
    EwCopyBitmap((XBitmap*)dstBitmap, (XBitmap*)srcBitmap, dstFrameNr, aFrameNr,
                  aClip, aDstRect, aSrcPos, aColorTL, aColorTR, aColorBR, aColorBL,
                  aBlend );
  }
}

/* The method FillRectangle() fills an area of canvas. The area is determined by 
   the parameter aDstRect. The parameters aColorTL, aColorTR, aColorBL, aColorBR 
   determine the colors at the corresponding corners of the aDstRect area.
   The parameter aClip limits the drawing operation. Pixel lying outside this area 
   remain unchanged. The last aBlend parameter controls the mode how drawn pixel 
   are combined with the pixel already existing in the destination bitmap. If aBlend 
   is 'true', the drawn pixel are alpha-blended with the background, otherwise the 
   drawn pixel will overwrite the old content. */
void GraphicsCanvas_FillRectangle( GraphicsCanvas _this, XRect aClip, XRect aDstRect, 
  XColor aColorTL, XColor aColorTR, XColor aColorBR, XColor aColorBL, XBool aBlend )
{
  XHandle dstBitmap;
  XInt32 dstFrameNo;

  if ( _this->Super1.bitmap == 0 )
    ResourcesBitmap__Update( _this );

  if ( _this->Super1.bitmap == 0 )
    return;

  dstBitmap = _this->Super1.bitmap;
  dstFrameNo = _this->DstFrameNr;
  {
    EwFillRectangle((XBitmap*)dstBitmap, dstFrameNo, aClip, aDstRect, aColorTL, aColorTR,
                     aColorBR, aColorBL, aBlend );
  }
}

/* Variants derived from the class : 'Graphics::Canvas' */
EW_DEFINE_CLASS_VARIANTS( GraphicsCanvas )
EW_END_OF_CLASS_VARIANTS( GraphicsCanvas )

/* Virtual Method Table (VMT) for the class : 'Graphics::Canvas' */
EW_DEFINE_CLASS( GraphicsCanvas, ResourcesBitmap, OnDraw, OnDraw, InvalidArea, InvalidArea, 
                 InvalidArea, InvalidArea, "Graphics::Canvas" )
  GraphicsCanvas_OnSetFrameSize,
  GraphicsCanvas_Update,
EW_END_OF_CLASS( GraphicsCanvas )

/* Embedded Wizard */
