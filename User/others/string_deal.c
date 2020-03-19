#include "ff.h"
#include "ffconf.h"
#include "string_deal.h"

#if _LFN_UNICODE 
void cutFileName(TCHAR *path, int len, int bytePerLine,  TCHAR *outStr)
#else
void cutFileName(char *path, int len, int bytePerLine,  char *outStr)
#endif
{
	#if _LFN_UNICODE 
	TCHAR *tmpFile;
	TCHAR *strIndex1 = 0, *strIndex2 = 0, *beginIndex;
	TCHAR secSeg[10] = {0};
	TCHAR gFileTail[4] = {'~', '.', 'g', '\0'};
	#else
	char *tmpFile;
	char *strIndex1 = 0, *strIndex2 = 0, *beginIndex;
	char secSeg[10] = {0};
	#endif
	
	if(path == 0 || len <= 3 || outStr == 0)
	{
		return;
	}
	
	tmpFile = path;
	#if _LFN_UNICODE
	strIndex1 = (WCHAR *)wcsstr((const WCHAR *)tmpFile, (const WCHAR *)'/');
	strIndex2 = (WCHAR *)wcsstr((const WCHAR *)tmpFile, (const WCHAR *)'.');
	#else
	strIndex1 = (char *)strrchr(tmpFile, '/');
	strIndex2 = (char *)strrchr(tmpFile, '.');
	#endif

	if(strIndex1 != 0)
	{
		beginIndex = strIndex1 + 1;	
	}
	/*if((strIndex1 != 0) && (strIndex2 != 0) && (strIndex1 < strIndex2))
	{
		beginIndex = strIndex1 + 1;			
	}*/
	else
	{
		beginIndex = tmpFile;
	}

	if(strIndex2 == 0 ||  (strIndex1 > strIndex2))	//not gcode file
	{
		#if _LFN_UNICODE
			if(wcslen(beginIndex) > len)
			{
				wcsncpy(outStr, beginIndex, len);
			
			}
			else
			{
				wcscpy(outStr, beginIndex);
			}
		#else
			if(strlen(beginIndex) > len)
			{
				strncpy(outStr, beginIndex, len);
			
			}
			else
			{
				strcpy(outStr, beginIndex);
			}
		#endif
	}
	else //gcode file
	{
		if(strIndex2 - beginIndex > (len - 2))
		{
			#if _LFN_UNICODE
				wcsncpy(outStr, (const WCHAR *)beginIndex, len - 3);
				wcscat(outStr, (const WCHAR *)gFileTail);
			#else
				//strncpy(outStr, beginIndex, len - 3);
				strncpy(outStr, beginIndex, len - 4);
				strcat(outStr, "~.g");
			#endif
		
		}
		else
		{
			#if _LFN_UNICODE
				wcsncpy(outStr, (const WCHAR *)beginIndex, strIndex2 - beginIndex + 1);
				wcscat(outStr, (const WCHAR *)&gFileTail[3]);
			#else
				strncpy(outStr, beginIndex, strIndex2 - beginIndex + 1);
				strcat(outStr, "g");
			#endif
		}
		
	}
	#if _LFN_UNICODE
	if(wcslen(outStr) > bytePerLine)
	{
		
		wcscpy(secSeg, (const WCHAR *)&outStr[bytePerLine]);
		outStr[bytePerLine] = '\n';
		outStr[bytePerLine + 1] = '\0';
		wcscat(outStr, (const WCHAR *)secSeg);
		
	}
	#else
	if(strlen(outStr) > bytePerLine)
	{
		
		strcpy(secSeg, &outStr[bytePerLine]);
		outStr[bytePerLine] = '\n';
		outStr[bytePerLine + 1] = '\0';
		strcat(outStr, secSeg);
		
	}
	#endif
}
	

