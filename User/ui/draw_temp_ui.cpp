#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_temp_ui.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"
#include "draw_set.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hTempWnd;


extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;

static BUTTON_STRUCT buttonInc, buttonDec, buttonSprayerTemp, buttonHeatbedTemp, buttonFanOpen, buttonRet;

static void cbTempWin(WM_MESSAGE * pMsg) {

	struct PressEvt *press_event;
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			//GUI_SetBkColor(GUI_BLUE);
			//GUI_Clear();
			//GUI_DispString("window");
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
					Clear_TempSpeed();
					draw_return_ui();
				}
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
	}


void draw_temp()
{
		
//	int titleHeight = 30;

//	int imgHeight = LCD_HEIGHT - titleHeight;	
	
	int i;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != TEMP_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = TEMP_UI;
	}
	disp_state = TEMP_UI;
		
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
	GUI_SetFont(&FONT_TITLE);

	GUI_DispStringAt("准备打印:设置:温度", 0, 0);
	
	hTempWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbTempWin, 0);

	
	buttonInc.btnHandle = BUTTON_CreateEx(0, 0, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, hTempWnd, BUTTON_CF_SHOW, 0, 301);
	buttonDec.btnHandle = BUTTON_CreateEx(LCD_WIDTH * 3 / 4,  0, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, hTempWnd, BUTTON_CF_SHOW, 0, 302);
	buttonSprayerTemp.btnHandle = BUTTON_CreateEx(0 , imgHeight / 2, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, hTempWnd, BUTTON_CF_SHOW, 0, 303);
	buttonHeatbedTemp.btnHandle = BUTTON_CreateEx(LCD_WIDTH / 4 , imgHeight / 2, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, hTempWnd, BUTTON_CF_SHOW, 0, 304);
	buttonFanOpen.btnHandle = BUTTON_CreateEx(LCD_WIDTH /2 , imgHeight / 2, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, hTempWnd, BUTTON_CF_SHOW, 0, 305);
	buttonRet.btnHandle = BUTTON_CreateEx(LCD_WIDTH * 3 / 4 , imgHeight / 2, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, hTempWnd, BUTTON_CF_SHOW, 0, 306);
	TEXT_SetDefaultFont((const GUI_FONT GUI_UNI_PTR *)&GUI_FontHZ_fontHz18);
	

	
	//GUI_Exec();


	
}

void Clear_TempSpeed()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hTempWnd))
	{
		WM_DeleteWindow(hTempWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}


