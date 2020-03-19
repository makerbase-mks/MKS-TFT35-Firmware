#ifndef _STRING_DEAL_H_
#define _STRING_DEAL_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#if _LFN_UNICODE 
void cutFileName(TCHAR *path, int len, int bytePerLine,  TCHAR *outStr);
#else
void cutFileName(char *path, int len, int bytePerLine,  char *outStr);
#endif


#if defined(__cplusplus)
}
#endif

#endif
