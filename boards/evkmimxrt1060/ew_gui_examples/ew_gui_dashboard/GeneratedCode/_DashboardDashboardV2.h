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

#ifndef _DashboardDashboardV2_H
#define _DashboardDashboardV2_H

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

#include "_CoreGroup.h"
#include "_DashboardLeftBottomBar.h"
#include "_DashboardLeftTopBar.h"
#include "_DashboardRightValueBar.h"
#include "_GraphicsPath.h"
#include "_ViewsImage.h"
#include "_ViewsStrokePath.h"
#include "_ViewsText.h"

/* Forward declaration of the class Core::DialogContext */
#ifndef _CoreDialogContext_
  EW_DECLARE_CLASS( CoreDialogContext )
#define _CoreDialogContext_
#endif

/* Forward declaration of the class Core::KeyPressHandler */
#ifndef _CoreKeyPressHandler_
  EW_DECLARE_CLASS( CoreKeyPressHandler )
#define _CoreKeyPressHandler_
#endif

/* Forward declaration of the class Core::LayoutContext */
#ifndef _CoreLayoutContext_
  EW_DECLARE_CLASS( CoreLayoutContext )
#define _CoreLayoutContext_
#endif

/* Forward declaration of the class Core::TaskQueue */
#ifndef _CoreTaskQueue_
  EW_DECLARE_CLASS( CoreTaskQueue )
#define _CoreTaskQueue_
#endif

/* Forward declaration of the class Core::View */
#ifndef _CoreView_
  EW_DECLARE_CLASS( CoreView )
#define _CoreView_
#endif

/* Forward declaration of the class Dashboard::DashboardV2 */
#ifndef _DashboardDashboardV2_
  EW_DECLARE_CLASS( DashboardDashboardV2 )
#define _DashboardDashboardV2_
#endif

/* Forward declaration of the class Effects::Fader */
#ifndef _EffectsFader_
  EW_DECLARE_CLASS( EffectsFader )
#define _EffectsFader_
#endif

/* Forward declaration of the class Graphics::Canvas */
#ifndef _GraphicsCanvas_
  EW_DECLARE_CLASS( GraphicsCanvas )
#define _GraphicsCanvas_
#endif


/* Deklaration of class : 'Dashboard::DashboardV2' */
EW_DEFINE_FIELDS( DashboardDashboardV2, CoreGroup )
  EW_PROPERTY( Outlet,          XRef )
  EW_OBJECT  ( rightPath,       GraphicsPath )
  EW_OBJECT  ( leftPath,        GraphicsPath )
  EW_OBJECT  ( leftGrowingPath, GraphicsPath )
  EW_OBJECT  ( rightGrowingPath, GraphicsPath )
  EW_OBJECT  ( RightStrokePath, ViewsStrokePath )
  EW_OBJECT  ( LeftStrokePath,  ViewsStrokePath )
  EW_OBJECT  ( RightGlow,       ViewsImage )
  EW_OBJECT  ( CenterGlow,      ViewsImage )
  EW_OBJECT  ( LeftGlow,        ViewsImage )
  EW_OBJECT  ( PWR,             ViewsImage )
  EW_OBJECT  ( KW,              ViewsImage )
  EW_OBJECT  ( RightValueBar,   DashboardRightValueBar )
  EW_OBJECT  ( LeftValueBarTop, DashboardLeftTopBar )
  EW_OBJECT  ( LeftValueBarBottom, DashboardLeftBottomBar )
  EW_OBJECT  ( MAX,             ViewsText )
  EW_OBJECT  ( CHG,             ViewsText )
  EW_PROPERTY( CurrentProgress, XFloat )
  EW_VARIABLE( centerGlowOpacity, XInt32 )
EW_END_OF_FIELDS( DashboardDashboardV2 )

/* Virtual Method Table (VMT) for the class : 'Dashboard::DashboardV2' */
EW_DEFINE_METHODS( DashboardDashboardV2, CoreGroup )
  EW_METHOD( initLayoutContext, void )( CoreRectView _this, XRect aBounds, CoreOutline 
    aOutline )
  EW_METHOD( GetRoot,           CoreRoot )( CoreView _this )
  EW_METHOD( Draw,              void )( CoreGroup _this, GraphicsCanvas aCanvas, 
    XRect aClip, XPoint aOffset, XInt32 aOpacity, XBool aBlend )
  EW_METHOD( HandleEvent,       XObject )( CoreView _this, CoreEvent aEvent )
  EW_METHOD( CursorHitTest,     CoreCursorHit )( CoreGroup _this, XRect aArea, XInt32 
    aFinger, XInt32 aStrikeCount, CoreView aDedicatedView, XSet aRetargetReason )
  EW_METHOD( ArrangeView,       XPoint )( CoreRectView _this, XRect aBounds, XEnum 
    aFormation )
  EW_METHOD( MoveView,          void )( CoreRectView _this, XPoint aOffset, XBool 
    aFastMove )
  EW_METHOD( GetExtent,         XRect )( CoreRectView _this )
  EW_METHOD( ChangeViewState,   void )( CoreGroup _this, XSet aSetState, XSet aClearState )
  EW_METHOD( OnSetBounds,       void )( CoreGroup _this, XRect value )
  EW_METHOD( OnSetFocus,        void )( CoreGroup _this, CoreView value )
  EW_METHOD( OnSetBuffered,     void )( CoreGroup _this, XBool value )
  EW_METHOD( OnSetOpacity,      void )( CoreGroup _this, XInt32 value )
  EW_METHOD( IsDialog,          XBool )( CoreGroup _this, XBool aRecursive )
  EW_METHOD( DispatchEvent,     XObject )( CoreGroup _this, CoreEvent aEvent )
  EW_METHOD( BroadcastEvent,    XObject )( CoreGroup _this, CoreEvent aEvent, XSet 
    aFilter )
  EW_METHOD( UpdateViewState,   void )( DashboardDashboardV2 _this, XSet aState )
  EW_METHOD( InvalidateArea,    void )( CoreGroup _this, XRect aArea )
EW_END_OF_METHODS( DashboardDashboardV2 )

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void DashboardDashboardV2_UpdateViewState( DashboardDashboardV2 _this, XSet aState );

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void DashboardDashboardV2_Init( DashboardDashboardV2 _this, XHandle aArg );

/* 'C' function for method : 'Dashboard::DashboardV2.createPath()' */
void DashboardDashboardV2_createPath( DashboardDashboardV2 _this, XObject sender );

/* 'C' function for method : 'Dashboard::DashboardV2.OnSetOutlet()' */
void DashboardDashboardV2_OnSetOutlet( DashboardDashboardV2 _this, XRef value );

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the widget will update itself. */
void DashboardDashboardV2_onOutlet( DashboardDashboardV2 _this, XObject sender );

/* 'C' function for method : 'Dashboard::DashboardV2.OnSetCurrentProgress()' */
void DashboardDashboardV2_OnSetCurrentProgress( DashboardDashboardV2 _this, XFloat 
  value );

/* 'C' function for method : 'Dashboard::DashboardV2.onSpeedChanged()' */
void DashboardDashboardV2_onSpeedChanged( DashboardDashboardV2 _this, XObject sender );

#ifdef __cplusplus
  }
#endif

#endif /* _DashboardDashboardV2_H */

/* Embedded Wizard */
