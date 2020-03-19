#include "button.h"
#include "text.h"
#include "draw_ui.h"
#include "draw_main.h"



#ifndef GUI_FLASH
#define GUI_FLASH
#endif


extern DISP_STATE_STACK disp_state_stack;

static GUI_HWIN hMainWnd;


extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern GUI_CONST_STORAGE GUI_BITMAP bmp_logo;

static BUTTON_Handle buttonLangu;

static void cbMainWin(WM_MESSAGE * pMsg) {
	struct PressEvt *press_event;
switch (pMsg->MsgId) {
case WM_PAINT:
//GUI_SetBkColor(GUI_BLACK);
//GUI_Clear();
//GUI_DispString("window");
	break;
case WM_TOUCH:
 	press_event = (struct PressEvt *)pMsg->Data.p;
	
	break;
case WM_TOUCH_CHILD:
 	
	break;



case WM_NOTIFY_PARENT:
	if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
	{
		press_event = (struct PressEvt *)pMsg->Data.p;
	
		if(pMsg->hWinSrc == buttonLangu)
		{
			if(gCfgItems.language == LANG_ENGLISH)
				gCfgItems.language = LANG_SIMPLE_CHINESE;
			else if(gCfgItems.language == LANG_SIMPLE_CHINESE)
				gCfgItems.language = LANG_ENGLISH;
			
		//////	bakup_cfg_inf(BAK_LANG_ID,  gCfgItems.language);	
			disp_sel_lang();
		}
		

	}
	break;

default:
	WM_DefaultProc(pMsg);
}
}


void draw_main_ui()
{
	int index; 
	int x_off = 0, y_off = 0;
	int _x, _y;
	uint16_t *p_index;
	int i;
	
	disp_state_stack._disp_index = 0;
	memset(disp_state_stack._disp_state, 0, sizeof(disp_state_stack._disp_state));
	disp_state_stack._disp_state[disp_state_stack._disp_index] = PRINT_READY_UI;
	
	disp_state = MAIN_UI;
	
	//GUI_SetFont(&FONT_TITLE);
	//GUI_SetBkColor(gCfgItems.background_color);
	//GUI_Clear();

	//GUI_SetColor(gCfgItems.title_color);
	//GUI_FillRect(0, 0, LCD_WIDTH - 1, LCD_HEIGHT/2 - 1);	

	
	//#if VERSION_WITH_PIC	
#if 0
	for(index = 0; index < 10; index ++)
	{
		Pic_Logo_Read("bmp_logo.bin", bmp_public_buf, 15360);

		
		i = 0;
		//GUI_DrawBitmap(&bmp_struct, x_off, y_off);
		
		

		LCD_setWindowArea(0, y_off * 24, 320, 24);
		LCD_SetCursor(0, y_off * 24);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */	
		for(_y = y_off * 24; _y < (y_off + 1) * 24; _y++)
		{
			for (x_off = 0; x_off < 320; x_off++) 
			{
				p_index = (uint16_t *)(&bmp_public_buf[i]);						
				LCD_WriteRAM(*p_index);
				i += 2;
				
			}
			if(i >= 15360)
					break;
		}
		y_off++;		

		
	}
	LCD_setWindowArea(0, 0, 319, 239);
	
	#endif	

}

void clear_main_ui()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hMainWnd))
	{
		WM_DeleteWindow(hMainWnd);
		//GUI_Exec();
	}
	//GUI_Exec();
	
}

