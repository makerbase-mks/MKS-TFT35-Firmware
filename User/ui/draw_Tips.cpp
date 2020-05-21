#include "draw_Tips.h"
#include "draw_ui.h"
#include "wifi_list.h"
#include "string.h"
#include "stdio.h"
#include "draw_wifi_list.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hTipsWnd;

static TEXT_Handle TEXT_tisps,TEXT_wifi_name;

TIPS_TYPE tips_type;
TIPS_DISP tips_disp;
tips_menu_def tips_menu;

extern GUI_CONST_STORAGE GUI_FONT GUI_FontHelvetica26;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHelvetica36;

static void cbTipsWin(WM_MESSAGE * pMsg) {
    struct PressEvt *press_event;
    switch (pMsg->MsgId) 
    {
		case WM_PAINT:
		
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

            }
            break;
    }
}

void draw_Tips()
{
		

	int i;
	uint8_t buf[30];
	
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != TIPS_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = TIPS_UI;
	}
	disp_state = TIPS_UI;

	GUI_SetBkColor(0x00dfe0);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();

	   
	
	hTipsWnd = WM_CreateWindow(0,0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbTipsWin, 0);

	TEXT_tisps = TEXT_CreateEx(0,100,LCD_WIDTH,100, hTipsWnd, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_BOTTOM,	GUI_ID_TEXT1, "");
	TEXT_SetFont(TEXT_tisps,&GUI_FontHelvetica36);
	TEXT_SetBkColor(TEXT_tisps,0x00dfe0);
	TEXT_SetTextColor(TEXT_tisps,0x000000);
	
	if(tips_type == TIPS_TYPE_JOINING)
	{	
		TEXT_SetText(TEXT_tisps,tips_menu.joining);
	}
	else if(tips_type == TIPS_TYPE_TAILED_JOIN)
	{
		TEXT_SetText(TEXT_tisps,tips_menu.failedJoin);
	}
	else if(tips_type == TIPS_TYPE_WIFI_CONECTED)
	{
		TEXT_SetText(TEXT_tisps,tips_menu.wifiConected);
	}

	TEXT_wifi_name = TEXT_CreateEx(0,200,LCD_WIDTH, 60, hTipsWnd, WM_CF_SHOW,TEXT_CF_HCENTER|TEXT_CF_BOTTOM, GUI_ID_TEXT1, "");
	TEXT_SetFont(TEXT_wifi_name,&GUI_FontHelvetica26);
	TEXT_SetBkColor(TEXT_wifi_name,0x00dfe0);
	TEXT_SetTextColor(TEXT_wifi_name,0x000000);
	TEXT_SetText(TEXT_wifi_name,(const char *)wifi_list.wifiName[wifi_list.nameIndex]);

	tips_disp.timer = TIPS_TIMER_START;
	tips_disp.timer_count = 0;
}

void Clear_Tips()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hTipsWnd))
	{
		WM_DeleteWindow(hTipsWnd);
		//GUI_Exec();
	}
	//GUI_Clear();
}


