#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_Sprayer.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hSprayerWnd;


extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern int X_ADD,X_INTERVAL;   //**图片间隔

static BUTTON_STRUCT buttonSingle, buttonDouble, buttonRet;

static void cbSprayerWin(WM_MESSAGE * pMsg) {

	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			//GUI_SetBkColor(GUI_BLUE);
			//GUI_Clear();
			//GUI_DispString("window");
			break;
		case WM_TOUCH:
		 	
			break;
		case WM_TOUCH_CHILD:
			
			break;
			
		case WM_NOTIFY_PARENT:
			if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
			{
				if(pMsg->hWinSrc == buttonRet.btnHandle)
				{
					Clear_Sprayer();
					draw_return_ui();
				}
				else if(pMsg->hWinSrc == buttonSingle.btnHandle)
				{
					gCfgItems.sprayerNum = 1;
					disp_sel_sprayer_num();
				}
				else if(pMsg->hWinSrc == buttonDouble.btnHandle)
				{
					gCfgItems.sprayerNum = 2;
					disp_sel_sprayer_num();
				}
				
			
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
	}


void draw_Sprayer()
{
		
//	int titleHeight = 30;

//	int imgHeight = LCD_HEIGHT - titleHeight;	
	
	int i;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != SPRAYER_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = SPRAYER_UI;
	}
	disp_state = SPRAYER_UI;
		
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
	GUI_SetFont(&FONT_TITLE);

	//GUI_DispStringAt("准备打印->设置->喷头数", 0, 0);
	GUI_DispStringAt(creat_title_text(),  X_ADD, X_INTERVAL);
	
	hSprayerWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbSprayerWin, 0);

	
	buttonSingle.btnHandle = BUTTON_CreateEx(0, 0, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, hSprayerWnd, BUTTON_CF_SHOW, 0, 301);
	buttonDouble.btnHandle = BUTTON_CreateEx(LCD_WIDTH  / 4,  0, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, hSprayerWnd, BUTTON_CF_SHOW, 0, 302);
	buttonRet.btnHandle = BUTTON_CreateEx(LCD_WIDTH * 3 / 4 , imgHeight / 2, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, hSprayerWnd, BUTTON_CF_SHOW, 0, 308);
	TEXT_SetDefaultFont(&FONT_STATE_INF);	

	

	disp_sel_sprayer_num();					
	
	//GUI_Exec();


	
}

void disp_sel_sprayer_num()
{
	if(gCfgItems.sprayerNum == 2)
	{
		BUTTON_SetBkColor(buttonDouble.btnHandle, BUTTON_CI_UNPRESSED, GUI_FOCUS_CLOLOR);
		BUTTON_SetBkColor(buttonSingle.btnHandle, BUTTON_CI_UNPRESSED, GUI_BLUE);
	}
	else
	{
		BUTTON_SetBkColor(buttonSingle.btnHandle, BUTTON_CI_UNPRESSED, GUI_FOCUS_CLOLOR);
		BUTTON_SetBkColor(buttonDouble.btnHandle, BUTTON_CI_UNPRESSED, GUI_BLUE);
	}
}
	

void Clear_Sprayer()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hSprayerWnd))
	{
		WM_DeleteWindow(hSprayerWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}


