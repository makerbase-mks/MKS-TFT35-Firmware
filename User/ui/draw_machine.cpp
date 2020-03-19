#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_machine.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hMachineWnd;


extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;

static BUTTON_STRUCT buttonNormal, buttonDelta, buttonRet;

static void cbMachineWin(WM_MESSAGE * pMsg) {

	
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
					Clear_Machine();
					draw_return_ui();
				}
				else if(pMsg->hWinSrc == buttonNormal.btnHandle)
				{
					gCfgItems.machineType = 1;
					///////bakup_cfg_inf(BAK_MACH_TYPE_ID,  gCfgItems.machineType);
					disp_mach_type();
				}
				else if(pMsg->hWinSrc == buttonDelta.btnHandle)
				{
					gCfgItems.machineType = 2;
					////////bakup_cfg_inf(BAK_MACH_TYPE_ID,  gCfgItems.machineType);
					disp_mach_type();
				}
			
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
	}


void draw_Machine()
{
		
//	int titleHeight = 30;

//	int imgHeight = LCD_HEIGHT - titleHeight;	
	
	int i;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != MACHINE_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = MACHINE_UI;
	}
	
	disp_state = MACHINE_UI;
		
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
	GUI_SetFont(&FONT_TITLE);

	//GUI_DispStringAt("准备打印->设置->机型", 0, 0);
	GUI_DispStringAt(creat_title_text(), 0, 0);
	
	hMachineWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbMachineWin, 0);

	
	buttonNormal.btnHandle= BUTTON_CreateEx(0, 0, LCD_WIDTH / 4 - 2, imgHeight / 2 - 1, hMachineWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonDelta.btnHandle = BUTTON_CreateEx(LCD_WIDTH  / 4,  0, LCD_WIDTH / 4 - 2, imgHeight / 2 - 1, hMachineWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonRet.btnHandle = BUTTON_CreateEx(LCD_WIDTH * 3 / 4 , imgHeight / 2, LCD_WIDTH / 4 - 2, imgHeight / 2 - 1, hMachineWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	TEXT_SetDefaultFont(&FONT_STATE_INF);	
	
	
	#if VERSION_WITH_PIC	

//	BUTTON_SetBitmapEx(buttonNormal, 0, &bmbmp_norm, BMP_PIC_X, BMP_PIC_Y);
//	BUTTON_SetBitmapEx(buttonDelta, 0, &bmbmp_delta, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);	
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);


	#endif
	
	disp_mach_type();
	
	//GUI_Exec();


	
}

void disp_mach_type()
{
	if(gCfgItems.machineType == 2)
	{
		
		#if VERSION_WITH_PIC	
		BUTTON_SetBmpFileName(buttonDelta.btnHandle, "bmp_delta_sel.bin",1);	
		BUTTON_SetBmpFileName(buttonNormal.btnHandle, "bmp_norm.bin",1);	
		

		#endif
	}
	else
	{
		
		#if VERSION_WITH_PIC	
		BUTTON_SetBmpFileName(buttonNormal.btnHandle, "bmp_norm_sel.bin",1);	
		BUTTON_SetBmpFileName(buttonDelta.btnHandle, "bmp_delta.bin",1);
	
		#endif
	}
}

void Clear_Machine()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hMachineWnd))
	{
		WM_DeleteWindow(hMachineWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}


