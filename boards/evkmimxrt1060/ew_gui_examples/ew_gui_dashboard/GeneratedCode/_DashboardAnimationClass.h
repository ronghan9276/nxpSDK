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

#ifndef _DashboardAnimationClass_H
#define _DashboardAnimationClass_H

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

/* Forward declaration of the class Dashboard::AnimationClass */
#ifndef _DashboardAnimationClass_
  EW_DECLARE_CLASS( DashboardAnimationClass )
#define _DashboardAnimationClass_
#endif


/* Helper class which provides functions to simplifies time independent animations. */
EW_DEFINE_FIELDS( DashboardAnimationClass, XObject )
EW_END_OF_FIELDS( DashboardAnimationClass )

/* Virtual Method Table (VMT) for the class : 'Dashboard::AnimationClass' */
EW_DEFINE_METHODS( DashboardAnimationClass, XObject )
EW_END_OF_METHODS( DashboardAnimationClass )

/* 'C' function for method : 'Dashboard::AnimationClass.linearValueProgress()' */
XInt32 DashboardAnimationClass_linearValueProgress( DashboardAnimationClass _this, 
  XInt32 aValue1, XInt32 aValue2, XFloat aStart, XFloat aEnd, XFloat aProgress );

/* 'C' function for method : 'Dashboard::AnimationClass.linearPointProgess()' */
XPoint DashboardAnimationClass_linearPointProgess( DashboardAnimationClass _this, 
  XPoint aValue1, XPoint aValue2, XFloat aStart, XFloat aEnd, XFloat aProgress );

#ifdef __cplusplus
  }
#endif

#endif /* _DashboardAnimationClass_H */

/* Embedded Wizard */
