#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "draw_autoLeveling.h"
#include "at24cxx.h"
#include "pic_manager.h"
#include "spi_flash.h"
#include "draw_zoffset.h"
#include "mks_tft_com.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

extern volatile unsigned char *codebufpoint;
extern char cmd_code[201];

static GUI_HWIN hAutoLevelingWnd;

static BUTTON_STRUCT buttonAutoLeveling, buttonZoffset,buttonRet;

static void cbAutoLevelingWin(WM_MESSAGE * pMsg) {

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
				if(pMsg->hWinSrc == buttonRet.btnHandle)
				{
                  			last_disp_state = AUTO_LEVELING_UI;				
					Clear_autoLeveling();
					draw_return_ui();
				}
				else if(pMsg->hWinSrc == buttonAutoLeveling.btnHandle)
				{
					SPI_FLASH_BufferRead((u8*)cmd_code,BUTTON_AUTOLEVELING_ADDR,201);
					codebufpoint = (u8*)cmd_code;
				}
				else if(pMsg->hWinSrc == buttonZoffset.btnHandle)
				{
					last_disp_state = AUTO_LEVELING_UI;
					pushFIFO(&gcodeCmdTxFIFO,(unsigned char *)"M501\n");
					Clear_autoLeveling();
					draw_Zoffset();
				}				
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
	}


void draw_autoLeveling()
{
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != AUTO_LEVELING_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = AUTO_LEVELING_UI;
	}
	disp_state = AUTO_LEVELING_UI;   
		
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
//	GUI_SetFont(&FONT_TITLE);

	//GUI_DispStringAt("准备打印->设置->文件系统", 0, 0);
	GUI_DispStringAt(creat_title_text(),  TITLE_XPOS, TITLE_YPOS);

	hAutoLevelingWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbAutoLevelingWin, 0);
	
	buttonAutoLeveling.btnHandle = BUTTON_CreateEx(INTERVAL_V,0,BTN_X_PIXEL, BTN_Y_PIXEL,hAutoLevelingWnd, BUTTON_CF_SHOW, 0, 22);//alloc_win_id());
	buttonZoffset.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,0,BTN_X_PIXEL, BTN_Y_PIXEL,hAutoLevelingWnd, BUTTON_CF_SHOW, 0, 23);//alloc_win_id());
	buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hAutoLevelingWnd,BUTTON_CF_SHOW, 0, 308);

	BUTTON_SetBmpFileName(buttonAutoLeveling.btnHandle, "bmp_autoleveling.bin",1);	
	BUTTON_SetBmpFileName(buttonZoffset.btnHandle, "bmp_zoffset.bin",1);
	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);

	BUTTON_SetBitmapEx(buttonAutoLeveling.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonZoffset.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);

	BUTTON_SetBkColor(buttonAutoLeveling.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonAutoLeveling.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonAutoLeveling.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonAutoLeveling.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
		
	BUTTON_SetBkColor(buttonZoffset.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonZoffset.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonZoffset.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonZoffset.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);

	if(gCfgItems.multiple_language != 0)
	{
		BUTTON_SetText(buttonAutoLeveling.btnHandle, tool_menu.autoleveling);
		BUTTON_SetText(buttonZoffset.btnHandle,more_menu.zoffset);
		BUTTON_SetText(buttonRet.btnHandle,common_menu.text_back);
	}
}

void Clear_autoLeveling()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hAutoLevelingWnd))
	{
		WM_DeleteWindow(hAutoLevelingWnd); 
	}
}

