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

#ifndef _ViewsWarpImage_H
#define _ViewsWarpImage_H

#ifdef __cplusplus
  extern "C"
  {
#endif

#include "ewrte.h"
#if EW_RTE_VERSION != 0x000A0000
  #error Wrong version of Embedded Wizard Runtime Environment.
#endif

#include "ewgfx.h"
#if EW_GFX_VERSION != 0x000A0000
  #error Wrong version of Embedded Wizard Graphics Engine.
#endif

#include "_ViewsWarpView.h"

/* Forward declaration of the class Core::Group */
#ifndef _CoreGroup_
  EW_DECLARE_CLASS( CoreGroup )
#define _CoreGroup_
#endif

/* Forward declaration of the class Core::LayoutContext */
#ifndef _CoreLayoutContext_
  EW_DECLARE_CLASS( CoreLayoutContext )
#define _CoreLayoutContext_
#endif

/* Forward declaration of the class Core::Timer */
#ifndef _CoreTimer_
  EW_DECLARE_CLASS( CoreTimer )
#define _CoreTimer_
#endif

/* Forward declaration of the class Core::View */
#ifndef _CoreView_
  EW_DECLARE_CLASS( CoreView )
#define _CoreView_
#endif

/* Forward declaration of the class Graphics::Canvas */
#ifndef _GraphicsCanvas_
  EW_DECLARE_CLASS( GraphicsCanvas )
#define _GraphicsCanvas_
#endif

/* Forward declaration of the class Graphics::WarpMatrix */
#ifndef _GraphicsWarpMatrix_
  EW_DECLARE_CLASS( GraphicsWarpMatrix )
#define _GraphicsWarpMatrix_
#endif

/* Forward declaration of the class Resources::Bitmap */
#ifndef _ResourcesBitmap_
  EW_DECLARE_CLASS( ResourcesBitmap )
#define _ResourcesBitmap_
#endif

/* Forward declaration of the class Views::WarpImage */
#ifndef _ViewsWarpImage_
  EW_DECLARE_CLASS( ViewsWarpImage )
#define _ViewsWarpImage_
#endif


/* The class Views::WarpImage provides a kind of view able to show a bitmap scaled 
   and rotated in the 2D/3D space. The bitmap is determined by the property @Bitmap. 
   In case of a multi-frame bitmap the desired frame can be selected by the property 
   @FrameNumber. The animation of bitmaps containing short video sequences is controlled 
   by the properties @Animated and @Endless. Alternatively, the animation can be 
   controlled by sending signals to the slot methods @StartAnimation and @StopAnimation.
   First of all, Embedded Wizard is not a 3D GUI development tool! Its lightweight 
   3D functionality is limited to the perspectively correct projection of an image 
   onto a quad (four corners polygon). Depending on this polygon's shape, different 
   kinds of transformations are possible, e.g. scaling, rotation or mirroring. The 
   polygon is determined by the four corners @Point1, @Point2, @Point3 and @Point4. 
   Moving these corners is thus sufficient to determine the desired transformation.
   More sophisticated way to control the transformations is provided by the methods 
   @RotateAndScale() and @Warp3D(). These methods derive the polygon coordinates 
   automatically from the given parameters.
   The properties @Color, @Color1, @Color2, @Color3 and @Color4 can be used to tint 
   the bitmap or to modulate its transparency. For each polygon corner different 
   color can be set, so the bitmap can be shown with fancy color or opacity gradients. 
   The particular effect of the colors depends on the type of the bitmap:
   - Alpha8 bitmaps will be tinted with the given colors due to the fact they don't 
   provide their own color information. This allows one and the same Alpha8 bitmap 
   to be drawn with different colors.
   - In case of Native, Index8 or RGB565 bitmaps the opacity of the bitmap is modulated 
   by the color's alpha value. The original RGB information stored in the bitmap 
   are not affected. This allows one and the same bitmap to be drawn with different 
   transparencies.
   The visibility of the view is controlled by the properties @Visible, @AlphaBlended, 
   @Opacity and @Embedded. In particular the property @Embedded can determine whether 
   the corresponding view is limited (== embedded) to the boundary of a sibling 
   Core::Outline view or not. The embedding of views within a Core::Outline allows 
   a kind of sub-groups within the GUI component itself. Very useful for any kind 
   of scrollable lists, menus, etc. */
EW_DEFINE_FIELDS( ViewsWarpImage, ViewsWarpView )
  EW_VARIABLE( timer,           CoreTimer )
  EW_PROPERTY( Bitmap,          ResourcesBitmap )
  EW_PROPERTY( OnFinished,      XSlot )
  EW_VARIABLE( startTime,       XUInt32 )
  EW_VARIABLE( animFrameNumber, XInt32 )
  EW_PROPERTY( Color4,          XColor )
  EW_PROPERTY( Color3,          XColor )
  EW_PROPERTY( Color2,          XColor )
  EW_PROPERTY( Color1,          XColor )
  EW_PROPERTY( Opacity,         XInt32 )
  EW_PROPERTY( FrameNumber,     XInt32 )
  EW_PROPERTY( Animated,        XBool )
  EW_PROPERTY( Endless,         XBool )
EW_END_OF_FIELDS( ViewsWarpImage )

/* Virtual Method Table (VMT) for the class : 'Views::WarpImage' */
EW_DEFINE_METHODS( ViewsWarpImage, ViewsWarpView )
  EW_METHOD( initLayoutContext, void )( CoreQuadView _this, XRect aBounds, CoreOutline 
    aOutline )
  EW_METHOD( GetRoot,           CoreRoot )( CoreView _this )
  EW_METHOD( Draw,              void )( ViewsWarpImage _this, GraphicsCanvas aCanvas, 
    XRect aClip, XPoint aOffset, XInt32 aOpacity, XBool aBlend )
  EW_METHOD( HandleEvent,       XObject )( CoreView _this, CoreEvent aEvent )
  EW_METHOD( CursorHitTest,     CoreCursorHit )( CoreView _this, XRect aArea, XInt32 
    aFinger, XInt32 aStrikeCount, CoreView aDedicatedView, XSet aRetargetReason )
  EW_METHOD( ArrangeView,       XPoint )( CoreQuadView _this, XRect aBounds, XEnum 
    aFormation )
  EW_METHOD( MoveView,          void )( CoreQuadView _this, XPoint aOffset, XBool 
    aFastMove )
  EW_METHOD( GetExtent,         XRect )( CoreQuadView _this )
  EW_METHOD( ChangeViewState,   void )( CoreView _this, XSet aSetState, XSet aClearState )
  EW_METHOD( OnSetPoint4,       void )( ViewsWarpView _this, XPoint value )
  EW_METHOD( OnSetPoint3,       void )( ViewsWarpView _this, XPoint value )
  EW_METHOD( OnSetPoint2,       void )( ViewsWarpView _this, XPoint value )
  EW_METHOD( OnSetPoint1,       void )( ViewsWarpView _this, XPoint value )
  EW_METHOD( update,            void )( ViewsWarpView _this, XObject sender )
  EW_METHOD( RotateAndScale,    void )( ViewsWarpView _this, XPoint aDstPos, XFloat 
    aAngle, XFloat aScaleX, XFloat aScaleY )
EW_END_OF_METHODS( ViewsWarpImage )

/* The method Draw() is invoked automatically if parts of the view should be redrawn 
   on the screen. This can occur when e.g. the view has been moved or the appearance 
   of the view has changed before.
   Draw() is invoked automatically by the framework, you never will need to invoke 
   this method directly. However you can request an invocation of this method by 
   calling the method InvalidateArea() of the views @Owner. Usually this is also 
   unnecessary unless you are developing your own view.
   The passed parameters determine the drawing destination aCanvas and the area 
   to redraw aClip in the coordinate space of the canvas. The parameter aOffset 
   contains the displacement between the origin of the views owner and the origin 
   of the canvas. You will need it to convert views coordinates into these of the 
   canvas.
   The parameter aOpacity contains the opacity descended from this view's @Owner. 
   It lies in range 0 .. 255. If the view implements its own 'Opacity', 'Color', 
   etc. properties, the Draw() method should calculate the resulting real opacity 
   by mixing the values of these properties with the one passed in aOpacity parameter.
   The parameter aBlend contains the blending mode descended from this view's @Owner. 
   It determines, whether the view should be drawn with alpha-blending active or 
   not. If aBlend is false, the outputs of the view should overwrite the corresponding 
   pixel in the drawing destination aCanvas. If aBlend is true, the outputs should 
   be mixed with the pixel already stored in aCanvas. For this purpose all Graphics 
   Engine functions provide a parameter to specify the mode for the respective drawing 
   operation. If the view implements its own 'Blend' property, the Draw() method 
   should calculate the resulting real blend mode by using logical AND operation 
   of the value of the property and the one passed in aBlend parameter. */
void ViewsWarpImage_Draw( ViewsWarpImage _this, GraphicsCanvas aCanvas, XRect aClip, 
  XPoint aOffset, XInt32 aOpacity, XBool aBlend );

/* 'C' function for method : 'Views::WarpImage.observerSlot()' */
void ViewsWarpImage_observerSlot( ViewsWarpImage _this, XObject sender );

/* 'C' function for method : 'Views::WarpImage.timerSlot()' */
void ViewsWarpImage_timerSlot( ViewsWarpImage _this, XObject sender );

/* 'C' function for method : 'Views::WarpImage.OnSetAnimated()' */
void ViewsWarpImage_OnSetAnimated( ViewsWarpImage _this, XBool value );

/* 'C' function for method : 'Views::WarpImage.OnSetColor()' */
void ViewsWarpImage_OnSetColor( ViewsWarpImage _this, XColor value );

/* 'C' function for method : 'Views::WarpImage.OnSetBitmap()' */
void ViewsWarpImage_OnSetBitmap( ViewsWarpImage _this, ResourcesBitmap value );

#ifdef __cplusplus
  }
#endif

#endif /* _ViewsWarpImage_H */

/* Embedded Wizard */
