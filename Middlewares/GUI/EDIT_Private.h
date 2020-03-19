/*
----------------------------------------------------------------------
File        : EDIT_Private.h
Purpose     : Internal header file
---------------------------END-OF-HEADER------------------------------
*/


#if GUI_WINSUPPORT

#include "WIDGET.h"

/*********************************************************************
*
*             Defines
*
**********************************************************************
*/

#define EDIT_REALLOC_SIZE  16

/*********************************************************************
*
*             Types
*
**********************************************************************
*/

typedef struct EDIT_Obj_struct EDIT_Obj;

typedef struct {
  int                          Align;
  int                          Border;
  const GUI_FONT GUI_UNI_PTR * pFont;
  GUI_COLOR                    aTextColor[2];
  GUI_COLOR                    aBkColor[2];
} EDIT_PROPS;

struct EDIT_Obj_struct {
  WIDGET Widget;
  WM_HMEM hpText;
  I16 MaxLen;
  U16 BufferSize;
  I32 Min, Max;            /* Min max values as normalized floats (integers) */
  U8 NumDecs;              /* Number of decimals */
  U32 CurrentValue;        /* Current value */
  int CursorPos;           /* Cursor position. 0 means left most */
  unsigned SelSize;        /* Number of selected characters */
  U8 EditMode;             /* Insert or overwrite mode */
  U8 XSizeCursor;          /* Size of cursor when working in insert mode */
  U8 Flags;
  tEDIT_AddKeyEx     * pfAddKeyEx;     /* Handle key input */
  tEDIT_UpdateBuffer * pfUpdateBuffer;  /* Update textbuffer */
  EDIT_PROPS Props;
  #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
    int DebugId;
  #endif
  int CurrsorShow;	//houhh 20061022... 
};

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  EDIT_Obj* EDIT_h2p(EDIT_Handle h);
  #define EDIT_H2P(h) EDIT_h2p(h)
#else
  #define EDIT_H2P(h) ((EDIT_Obj*)GUI_ALLOC_h2p(h))
#endif

/*********************************************************************
*
*       Public data (internal defaults)
*
**********************************************************************
*/

extern EDIT_PROPS EDIT__DefaultProps;

/*********************************************************************
*
*       Public functions (internal)
*
**********************************************************************
*/

void EDIT__SetCursorPos   (EDIT_Obj* pObj, int CursorPos);
U16  EDIT__GetCurrentChar (EDIT_Obj* pObj);

#endif /* GUI_WINSUPPORT */
