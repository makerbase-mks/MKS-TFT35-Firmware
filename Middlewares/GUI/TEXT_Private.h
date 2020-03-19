/*
----------------------------------------------------------------------
File        : TEXT.h
Purpose     : TEXT include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef TEXT_PRIVATE_H
#define TEXT_PRIVATE_H

#include "TEXT.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

#ifndef TEXT_SUPPORT_TRANSPARENCY
  #define TEXT_SUPPORT_TRANSPARENCY WM_SUPPORT_TRANSPARENCY
#endif

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define TEXT_ID 0x4544   /* Magic numer, should be unique if possible */


#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define TEXT_ASSERT_IS_VALID_PTR(p) DEBUG_ERROROUT_IF(p->DebugId != TEXT_ID, "xxx.c: Wrong handle type or Object not init'ed")
  #define TEXT_INIT_ID(p)   p->DebugId = TEXT_ID
  #define TEXT_DEINIT_ID(p) p->DebugId = TEXT_ID+1
#else
  #define TEXT_ASSERT_IS_VALID_PTR(p)
  #define TEXT_INIT_ID(p)
  #define TEXT_DEINIT_ID(p)
#endif

#endif   /* if GUI_WINSUPPORT */
#endif   /* TEXT_PRIVATE_H */
