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
* Version  : 9.30
* Date     : 14.02.2020  8:00:50
* Profile  : iMX_RT
* Platform : NXP.iMX_RT.RGB565
*
*******************************************************************************/

#ifndef _CutterBatchDialog_H
#define _CutterBatchDialog_H

#ifdef __cplusplus
  extern "C"
  {
#endif

#include "ewrte.h"
#if EW_RTE_VERSION != 0x0009001E
  #error Wrong version of Embedded Wizard Runtime Environment.
#endif

#include "ewgfx.h"
#if EW_GFX_VERSION != 0x0009001E
  #error Wrong version of Embedded Wizard Graphics Engine.
#endif

#include "_CoreGroup.h"
#include "_CutterBarGraph.h"
#include "_CutterCancelButton.h"
#include "_CutterSpeedButton.h"
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

/* Forward declaration of the class Cutter::BatchDialog */
#ifndef _CutterBatchDialog_
  EW_DECLARE_CLASS( CutterBatchDialog )
#define _CutterBatchDialog_
#endif

/* Forward declaration of the class Graphics::Canvas */
#ifndef _GraphicsCanvas_
  EW_DECLARE_CLASS( GraphicsCanvas )
#define _GraphicsCanvas_
#endif


/* Dialog class to define the number of cutted papers. */
EW_DEFINE_FIELDS( CutterBatchDialog, CoreGroup )
  EW_PROPERTY( OnCancel,        XSlot )
  EW_PROPERTY( PaperBatch,      XRef )
  EW_OBJECT  ( Text,            ViewsText )
  EW_OBJECT  ( TextBatch,       ViewsText )
  EW_OBJECT  ( BarGraph,        CutterBarGraph )
  EW_OBJECT  ( SpeedButtonL,    CutterSpeedButton )
  EW_OBJECT  ( SpeedButtonR,    CutterSpeedButton )
  EW_OBJECT  ( CancelButton,    CutterCancelButton )
  EW_OBJECT  ( Text0,           ViewsText )
  EW_OBJECT  ( Text1,           ViewsText )
  EW_OBJECT  ( Text2,           ViewsText )
  EW_OBJECT  ( Text3,           ViewsText )
  EW_OBJECT  ( Text4,           ViewsText )
  EW_OBJECT  ( Text5,           ViewsText )
  EW_OBJECT  ( Text6,           ViewsText )
  EW_OBJECT  ( Text7,           ViewsText )
  EW_OBJECT  ( Text8,           ViewsText )
  EW_OBJECT  ( Text9,           ViewsText )
EW_END_OF_FIELDS( CutterBatchDialog )

/* Virtual Method Table (VMT) for the class : 'Cutter::BatchDialog' */
EW_DEFINE_METHODS( CutterBatchDialog, CoreGroup )
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
  EW_METHOD( OnSetOpacity,      void )( CoreGroup _this, XInt32 value )
  EW_METHOD( DispatchEvent,     XObject )( CoreGroup _this, CoreEvent aEvent )
  EW_METHOD( BroadcastEvent,    XObject )( CoreGroup _this, CoreEvent aEvent, XSet 
    aFilter )
  EW_METHOD( UpdateLayout,      void )( CoreGroup _this, XPoint aSize )
  EW_METHOD( UpdateViewState,   void )( CoreGroup _this, XSet aState )
  EW_METHOD( InvalidateArea,    void )( CoreGroup _this, XRect aArea )
EW_END_OF_METHODS( CutterBatchDialog )

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void CutterBatchDialog_Init( CutterBatchDialog _this, XHandle aArg );

/* 'C' function for method : 'Cutter::BatchDialog.OnSetPaperBatch()' */
void CutterBatchDialog_OnSetPaperBatch( CutterBatchDialog _this, XRef value );

/* Slot method to update the display value. */
void CutterBatchDialog_onUpdate( CutterBatchDialog _this, XObject sender );

/* Slot metod to change the paper speed, when user press arrow buttons. */
void CutterBatchDialog_onIncrement( CutterBatchDialog _this, XObject sender );

/* Slot metod to change the paper speed, when user press arrow buttons. */
void CutterBatchDialog_onDecrement( CutterBatchDialog _this, XObject sender );

/* Slot method to forward the cancel event. */
void CutterBatchDialog_onCancel( CutterBatchDialog _this, XObject sender );

#ifdef __cplusplus
  }
#endif

#endif /* _CutterBatchDialog_H */

/* Embedded Wizard */
