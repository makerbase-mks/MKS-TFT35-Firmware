#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"
#include "draw_bind.h"
#include "wifi_module.h"
#include "draw_keyboard.h"
#include "draw_set.h"
#include "draw_wifi.h"
#include "wifi_list.h"
#include "draw_wifi_list.h"
#include "string.h"
#include "stdio.h"

//#include "draw_wifi_connected.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hWifiWnd;

static TEXT_Handle textWifiTitle,Wifi_Page_text;

extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern int X_ADD,X_INTERVAL;   //**Í¼Æ¬¼ä¸ô

GUI_BITMAP bmp_struct_18x14 = {
  18,//80, /* XSize */
  14,//50, /* YSize */
  160, /* BytesPerLine */
  16, /* BitsPerPixel */
  (unsigned char *)bmp_public_buf,  /* Pointer to picture data */
  NULL  /* Pointer to palette */
 ,GUI_DRAW_BMPM565
};

GUI_BITMAP bmp_struct_0x0 = {
  0,//80, /* XSize */
  0,//50, /* YSize */
  160, /* BytesPerLine */
  16, /* BitsPerPixel */
  (unsigned char *)bmp_public_buf,  /* Pointer to picture data */
  NULL  /* Pointer to palette */
 ,GUI_DRAW_BMPM565
};
	
static BUTTON_STRUCT  buttonWifiPd,buttonRet,buttonN[4];

WIFI_LIST wifi_list;
list_menu_def list_menu;	
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHelvetica26;

#define NAME_BTN_X 330
#define NAME_BTN_Y 48

#define MARK_BTN_X 0
#define MARK_BTN_Y 68

static void cbWifiWin(WM_MESSAGE * pMsg) {
	int8_t i;

	struct PressEvt *press_event;
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			/*GUI_SetColor(0x00dfe0);
			GUI_FillRect(0,titleHeight-2,LCD_WIDTH,titleHeight);

			GUI_SetColor(0x4c4c4c);
			GUI_DrawHLine((imgHeight/6)*1+titleHeight,0,LCD_WIDTH);
			GUI_DrawHLine((imgHeight/6)*2+titleHeight,0,LCD_WIDTH);
			GUI_DrawHLine((imgHeight/6)*3+titleHeight,0,LCD_WIDTH);
			GUI_DrawHLine((imgHeight/6)*4+titleHeight,0,LCD_WIDTH);
			GUI_DrawHLine((imgHeight/6)*5+titleHeight,0,LCD_WIDTH);*/
			break;
		case WM_TOUCH:
		 	press_event = (struct PressEvt *)pMsg->Data.p;
			
			break;
		case WM_TOUCH_CHILD:
			press_event = (struct PressEvt *)pMsg->Data.p;

			break;
			
		case WM_NOTIFY_PARENT:
			if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
			{
				
				if(pMsg->hWinSrc == buttonRet.btnHandle)
				{
					//GUI_Exec();
					//GUI_UC_SetEncodeUTF8();
					
					last_disp_state = WIFI_LIST_UI;
					Clear_Wifi_list();
					draw_Set();
				}	
				else if(pMsg->hWinSrc == buttonWifiPd.btnHandle)
				{
					#if 1
					if(wifi_list.getNameNum > 0)
					{
						if((wifi_list.nameIndex + NUMBER_OF_PAGE) >= wifi_list.getNameNum)
						{
							wifi_list.nameIndex = 0;
							wifi_list.currentWifipage = 1;
						}
						else 
						{
							wifi_list.nameIndex += NUMBER_OF_PAGE;
							wifi_list.currentWifipage++;
						}
						disp_wifi_list();
					}
					#else
					Clear_Wifi_list();
					draw_Keyboard();
					#endif
				}
				else
				{
					i = NUMBER_OF_PAGE;
					while(i--)
					{
						if(pMsg->hWinSrc == buttonN[i].btnHandle)
						{
							if(wifi_list.getNameNum !=0)
							{
								//GUI_Exec();
								//GUI_UC_SetEncodeUTF8();
								
								if(wifi_link_state == WIFI_CONNECTED && strcmp((const char *)wifi_list.wifiConnectedName,(const char *)wifi_list.wifiName[wifi_list.nameIndex + i]) == 0)
								{
									//BUTTON_SetBmpFileName(buttonN[i].btnHandle, "bmp_Check_Mark_Yellow.bin",1);
									//BUTTON_SetBitmapEx(buttonN[i].btnHandle, 0, &bmp_struct_18x14,MARK_BTN_X, (NAME_BTN_Y-1-14)/2);

									wifi_list.nameIndex = wifi_list.nameIndex + i;
									last_disp_state = WIFI_LIST_UI;
									Clear_Wifi_list();
									//draw_WifiConnected();
									draw_Wifi();
								}
								else
								{
									wifi_list.nameIndex = wifi_list.nameIndex + i;
									last_disp_state = WIFI_LIST_UI;
									Clear_Wifi_list();
									valueType = wifi_setting;
									draw_Keyboard();
								}
							}
						}
					}
				}
				
			}
			else if(pMsg->Data.v == WM_NOTIFICATION_CLICKED)
			{
				if(pMsg->hWinSrc == buttonWifiPd.btnHandle)
				{
					//BUTTON_SetFont(buttonWifiPd.btnHandle,&GUI_FontHelvetica36_bold);
				}
				else
				{
					i = NUMBER_OF_PAGE;
					while(i--)
					{
						if(pMsg->hWinSrc == buttonN[i].btnHandle)
						{
							if(wifi_link_state == WIFI_CONNECTED && strcmp((const char *)wifi_list.wifiConnectedName,(const char *)wifi_list.wifiName[wifi_list.nameIndex + i]) == 0)
							{
								//BUTTON_SetBmpFileName(buttonN[i].btnHandle, "bmp_Check_Mark_Black.bin",1);
								//BUTTON_SetBitmapEx(buttonN[i].btnHandle, 0, &bmp_struct_18x14,MARK_BTN_X, (NAME_BTN_Y-1-14)/2);
							}
						}
					}
				}
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
	}

void draw_Wifi_list()
{	
	//int row;

	//char buf[60];
	//char page[20];
	
	
	int8_t i;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != WIFI_LIST_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = WIFI_LIST_UI;
	}
	disp_state = WIFI_LIST_UI;
	GUI_Clear();	

	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();

	

	GUI_DispStringAt(creat_title_text(),  TITLE_XPOS, TITLE_YPOS);
	
	hWifiWnd = WM_CreateWindow(0 , titleHeight,LCD_WIDTH,imgHeight, WM_CF_SHOW, cbWifiWin, 0);

	    buttonRet.btnHandle = BUTTON_CreateEx(OTHER_BTN_XPIEL*3+INTERVAL_V*4,OTHER_BTN_YPIEL*2+INTERVAL_H*2,OTHER_BTN_XPIEL,OTHER_BTN_YPIEL, hWifiWnd, BUTTON_CF_SHOW, 0, 308);
	    Wifi_Page_text = TEXT_CreateEx(LCD_WIDTH-90,titleHeight+5,90,30, hWifiWnd, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_VCENTER,	GUI_ID_TEXT1, "");
	    //if(wifi_list.getPage>=2)
	     buttonWifiPd.btnHandle = BUTTON_CreateEx(OTHER_BTN_XPIEL*3+INTERVAL_V*4,OTHER_BTN_YPIEL+INTERVAL_H,OTHER_BTN_XPIEL,OTHER_BTN_YPIEL, hWifiWnd, BUTTON_CF_SHOW, 0, 309);


	BUTTON_SetBmpFileName(buttonWifiPd.btnHandle, "bmp_pageDown.bin",1);

	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_back.bin",1);
	BUTTON_SetBitmapEx(buttonWifiPd.btnHandle, 0, &bmp_struct_92,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct_92,BMP_PIC_X, BMP_PIC_Y);

	/*BUTTON_SetBkColor(buttonWifiPd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonWifiPd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonWifiPd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonWifiPd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);
*/
	//GUI_Exec();

	    //GUI_UC_SetEncodeNone();

	  
	    
	#if 1	
		  TEXT_SetFont(Wifi_Page_text,&GUI_FontHelvetica26);
           TEXT_SetTextColor(Wifi_Page_text,gCfgItems.title_color);
		   TEXT_SetBkColor(Wifi_Page_text,gCfgItems.background_color);

	   for(i = 0; i < NUMBER_OF_PAGE; i++)
	    {
        	buttonN[i].btnHandle = BUTTON_CreateEx(0,NAME_BTN_Y*i+10,NAME_BTN_X,NAME_BTN_Y,hWifiWnd, BUTTON_CF_SHOW, 0, 107 + i);

		BUTTON_SetFont(buttonN[i].btnHandle,&GUI_FontHelvetica26);
		BUTTON_SetTextAlign(buttonN[i].btnHandle,GUI_CUSTOM_POS|GUI_TA_VCENTER);

		
		BUTTON_SetTextColor(buttonN[i].btnHandle, BUTTON_CI_PRESSED,0X000000);
	       BUTTON_SetTextColor(buttonN[i].btnHandle, BUTTON_CI_UNPRESSED,0xffffff);
		BUTTON_SetBkColor(buttonN[i].btnHandle, BUTTON_CI_PRESSED, 0X00DFE0);
	       BUTTON_SetBkColor(buttonN[i].btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.background_color);
	       
        	BUTTON_SetBmpFileName(buttonN[i].btnHandle, NULL,1);
	    }

	       /*wifi_list.getPage = 0;
		wifi_list.currentWifipage = 0;
		wifi_list.getNameNum = 0;
		wifi_list.nameIndex = 0;
		memset(&wifi_list.wifiConnectedName,0,sizeof(wifi_list.wifiConnectedName));
		memset(&wifi_list.wifiName,0,sizeof(wifi_list.wifiName));*/

		/*if(last_disp_state == SET_UI && wifi_link_state != WIFI_CONNECTED)
		{
			wifi_list.getPage = 0;
			wifi_list.currentWifipage = 0;
			wifi_list.getNameNum = 0;
			wifi_list.nameIndex = 0;
			memset(wifi_list.wifiName,0,sizeof(wifi_list.wifiName));
		}
		else*/
		//{
			wifi_list.nameIndex = 0;
			wifi_list.currentWifipage = 1;
		//}

		if(wifi_link_state == WIFI_CONNECTED && wifiPara.mode == 0x02)
		{
			memset(wifi_list.wifiConnectedName, 0, sizeof(&wifi_list.wifiConnectedName));
			memcpy(wifi_list.wifiConnectedName, wifiPara.ap_name, sizeof(wifi_list.wifiConnectedName));
		}
	    
	    disp_wifi_list();
		#endif
}

void disp_wifi_list(void)
{
	int8_t tmpStr[WIFI_NAME_BUFFER_SIZE] = {0};
	//int8_t buf[WIFI_NAME_BUFFER_SIZE] = {0};
	uint8_t i,j;
	
	

	if(wifi_list.getPage >= 2)
	{
		//file_menu.page_down = FILE_NEXT_PAGE_EN;
	}
	else
	{
		//file_menu.page_down = 0;
	}
	//BUTTON_SetText(buttonWifiPd.btnHandle, file_menu.page_down);

       sprintf((char *)tmpStr,list_menu.file_pages,wifi_list.currentWifipage,wifi_list.getPage);
       TEXT_SetText(Wifi_Page_text,(const char *)tmpStr);
	
	#if 1
	for(i=0;i<NUMBER_OF_PAGE;i++)
	{

		/*buttonN[i].btnHandle = BUTTON_CreateEx(0,NAME_BTN_Y*i+10,NAME_BTN_X,NAME_BTN_Y,hWifiWnd, BUTTON_CF_SHOW, 0, 107 + i);

		BUTTON_SetFont(buttonN[i].btnHandle,&GUI_FontHZ16);
		BUTTON_SetTextAlign(buttonN[i].btnHandle,GUI_CUSTOM_POS|GUI_TA_VCENTER);

		
		BUTTON_SetTextColor(buttonN[i].btnHandle, BUTTON_CI_PRESSED,0X000000);
	       BUTTON_SetTextColor(buttonN[i].btnHandle, BUTTON_CI_UNPRESSED,0xffffff);
		BUTTON_SetBkColor(buttonN[i].btnHandle, BUTTON_CI_PRESSED, 0X00DFE0);
	       BUTTON_SetBkColor(buttonN[i].btnHandle, BUTTON_CI_UNPRESSED, 0x000000);
	       
        	BUTTON_SetBmpFileName(buttonN[i].btnHandle, NULL,1);*/
			
		memset(tmpStr, 0, sizeof(tmpStr));

		j = wifi_list.nameIndex + i;
		if(j >= wifi_list.getNameNum)
		{
			BUTTON_SetText(buttonN[i].btnHandle, (char const *)(tmpStr));
		}
		else
		{
			//cutWifiName((char *)wifi_list.wifiName[j], 20,  (char *)tmpStr); 
			//BUTTON_SetText(buttonN[i].btnHandle, (char const *)(tmpStr));
			BUTTON_SetText(buttonN[i].btnHandle, (char const *)wifi_list.wifiName[j]);
			
			if(wifi_link_state == WIFI_CONNECTED && strcmp((const char *)wifi_list.wifiConnectedName,(const char *)wifi_list.wifiName[j]) == 0)
			{
				//BUTTON_SetBmpFileName(buttonN[i].btnHandle, "bmp_Check_Mark_Yellow.bin",1);
				//BUTTON_SetBitmapEx(buttonN[i].btnHandle, 0, &bmp_struct_18x14,MARK_BTN_X, (NAME_BTN_Y-1-14)/2);
	       		BUTTON_SetTextColor(buttonN[i].btnHandle, BUTTON_CI_UNPRESSED,0X00DFE0);
			}
			else
			{
				//BUTTON_SetBmpFileName(buttonN[i].btnHandle, "bmp_Check_Mark_None.bin",1);
				//BUTTON_SetBitmapEx(buttonN[i].btnHandle, 0, &bmp_struct_0x0,0,0);
				BUTTON_SetTextColor(buttonN[i].btnHandle, BUTTON_CI_UNPRESSED,0Xffffff);
			}
		}
	}
	//GUI_Exec();
	//GUI_UC_SetEncodeUTF8();
        #endif    
}

void cutWifiName(char *name, int len,char *outStr)
{
	if(name == 0 || len <= 3 || outStr == 0)
	{
		return;
	}
	if(strlen(name) > len)
	{
		strncpy(outStr, name, len);
		strcat(outStr, "~");
	}
	else
	{
		strcpy(outStr, name);
	}
}


void Clear_Wifi_list()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hWifiWnd))
	{
		WM_DeleteWindow(hWifiWnd);
	//	GUI_Exec();
	}
	
	//GUI_Clear();
}


