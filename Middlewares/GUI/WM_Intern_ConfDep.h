

#ifndef WM_INTERN_CONFDEP_H            /* Make sure we only include it once */
#define WM_INTERN_CONFDEP_H            /* Make sure we only include it once */

#include "WM_Intern.h"

#if GUI_WINSUPPORT


#ifdef WM_C
  #define GUI_EXTERN
#else
  #define GUI_EXTERN extern
#endif

GUI_EXTERN WM_HWIN   WM__ahDesktopWin[GUI_NUM_LAYERS];   /* No longer depends on LCDConf.h ... Can be moved to an other file */
GUI_EXTERN GUI_COLOR WM__aBkColor[GUI_NUM_LAYERS];       /* No longer depends on LCDConf.h ... Can be moved to an other file */

#undef GUI_EXTERN

#endif   /* GUI_WINSUPPORT */

#endif   /* WM_INTERN_H */

/*************************** End of file ****************************/
