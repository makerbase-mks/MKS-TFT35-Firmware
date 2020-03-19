#include "gui.h"
//#include "button.h"
//#include "PROGBAR.h"
#include "draw_tool.h"
#include "draw_ui.h"
#include "draw_print_file.h"
#include "pic.h"
//#include "fontLib.h"
#include "draw_move_motor.h"
//#include "text.h"
//#include "printer.h"
#include "draw_more.h"
#include "draw_manual_leveling.h"
#include "draw_filamentchange.h"
#include "sd_usr.h"
#include "draw_pre_heat.h"
#include "draw_extrusion.h"
#include "draw_zero.h"
#include "pic_manager.h"
#include "spi_flash.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

extern volatile unsigned char *codebufpoint;
extern char cmd_code[201];

extern uint8_t Get_Temperature_Flg;
extern volatile uint8_t get_temp_flag;
extern uint8_t leveling_first_time;

static BUTTON_STRUCT buttonPreHeat, buttonExtruse, buttonMove, buttonZero,buttonLeveling,buttonFilament,buttonMore,buttonRet;
static GUI_HWIN hToolWnd;

//extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
static TEXT_Handle Tool_Title_Text,Tool_state_Text;

static void cbDrawToolWin(WM_MESSAGE * pMsg) {
	
	switch (pMsg->MsgId) {
		case WM_PAINT:

			break;
		
		case WM_NOTIFY_PARENT:
			if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
			{
				if(pMsg->hWinSrc == buttonMove.btnHandle)
				{
					gCfgItems.getzpos_flg = 1;
					last_disp_state = TOOL_UI;
					Clear_Tool();
					draw_move_motor();			
				}
				else if(pMsg->hWinSrc == buttonPreHeat.btnHandle)
				{
					last_disp_state = TOOL_UI;
					Get_Temperature_Flg = 1;
					get_temp_flag = 1;
					Clear_Tool();
					draw_preHeat();
				}
				else if(pMsg->hWinSrc == buttonExtruse.btnHandle)
				{
					last_disp_state = TOOL_UI;
					Get_Temperature_Flg = 1;
					get_temp_flag = 1;
					Clear_Tool();
					draw_extrusion();
				}
				else if(pMsg->hWinSrc == buttonZero.btnHandle)
				{
					last_disp_state = TOOL_UI;
					Clear_Tool();
					draw_Zero();
				}
				else if(pMsg->hWinSrc == buttonLeveling.btnHandle)
				{
					if(gCfgItems.leveling_mode == 1)
					{
						SPI_FLASH_BufferRead((u8*)cmd_code,BUTTON_AUTOLEVELING_ADDR,201);
						codebufpoint = (u8*)cmd_code;								
					}
					else
					{
						last_disp_state = TOOL_UI;
						leveling_first_time = 1;
						Clear_Tool();
						draw_leveling();
					}
				}		
				else if(pMsg->hWinSrc == buttonFilament.btnHandle)
				{
					//gCfgItems.desireSprayerTempBak_1[gCfgItems.curSprayerChoose] = gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose];
					last_disp_state = TOOL_UI;
					Clear_Tool();
					draw_FilamentChange();
				}		
				else if(pMsg->hWinSrc == buttonMore.btnHandle)
				{
					last_disp_state = TOOL_UI;
					Clear_Tool();
					draw_More();
				}				
				else if(pMsg->hWinSrc == buttonRet.btnHandle)
				{
					last_disp_state = TOOL_UI;
					Clear_Tool();
					draw_return_ui();
				}
			}
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}





void draw_tool()
{
	int i;
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != TOOL_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = TOOL_UI;
	}
	disp_state = TOOL_UI;

	
	//GUI_SetFont(&GUI_Font8x18);
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
	//GUI_SetFont(&FONT_TITLE);
	#if 0
	if(gCfgItems.language == LANG_COMPLEX_CHINESE)
	{
		GUI_SetFont(&GUI_FontHZ16);
	}
	else
	{
		GUI_SetFont(&FONT_TITLE);
	}
	#endif
	GUI_DispStringAt(creat_title_text(), 0, 0);
	

	hToolWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbDrawToolWin, 0);
	//Tool_Title_Text = TEXT_CreateEx(0,0, LCD_WIDTH, titleHeight, hToolWnd, WM_CF_SHOW, TEXT_CF_LEFT,	alloc_win_id(), "Tool");
	buttonPreHeat.btnHandle = BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL,hToolWnd, BUTTON_CF_SHOW,0,alloc_win_id());
	buttonExtruse.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2, 0,BTN_X_PIXEL,BTN_Y_PIXEL,hToolWnd,BUTTON_CF_SHOW,0,alloc_win_id());
	buttonMove.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,0,BTN_X_PIXEL,BTN_Y_PIXEL,hToolWnd,BUTTON_CF_SHOW,0,alloc_win_id());
	buttonZero.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,0,BTN_X_PIXEL,BTN_Y_PIXEL,hToolWnd,BUTTON_CF_SHOW,0,alloc_win_id());
	if(gCfgItems.leveling_mode!=2)
	{
		buttonLeveling.btnHandle = BUTTON_CreateEx(INTERVAL_V,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL, hToolWnd,BUTTON_CF_SHOW,0,305);
		buttonFilament.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hToolWnd,BUTTON_CF_SHOW, 0, 306);
		buttonMore.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hToolWnd,BUTTON_CF_SHOW, 0, 307);	
	}
	else
	{
		buttonFilament.btnHandle = BUTTON_CreateEx(INTERVAL_V,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL, hToolWnd,BUTTON_CF_SHOW,0,305);
		buttonMore.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hToolWnd,BUTTON_CF_SHOW, 0, 306);
	}
	buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hToolWnd,BUTTON_CF_SHOW, 0, 308);
	//Tool_state_Text = TEXT_CreateEx(0,LCD_HEIGHT-statHeight, LCD_WIDTH, statHeight, hToolWnd, WM_CF_SHOW, TEXT_CF_LEFT,	alloc_win_id(), " ");

	//TEXT_SetTextColor(Tool_Title_Text, gCfgItems.title_color);
	//TEXT_SetTextAlign(Tool_Title_Text, GUI_TA_VCENTER | GUI_TA_HCENTER);
	//TEXT_SetTextColor(Tool_state_Text, gCfgItems.title_color);
	//TEXT_SetTextAlign(Tool_state_Text, GUI_TA_VCENTER | GUI_TA_LEFT);


	//TEXT_SetText(Tool_Title_Text,tool_menu.title);	
	BUTTON_SetBmpFileName(buttonPreHeat.btnHandle, "bmp_preHeat.bin",1);
	BUTTON_SetBmpFileName(buttonExtruse.btnHandle, "bmp_extruct.bin",1);
	BUTTON_SetBmpFileName(buttonMove.btnHandle, "bmp_mov.bin",1);
	BUTTON_SetBmpFileName(buttonZero.btnHandle, "bmp_zero.bin",1);
	if(gCfgItems.leveling_mode != 2)
	{
		if(gCfgItems.leveling_mode == 1)
		{	
			BUTTON_SetBmpFileName(buttonLeveling.btnHandle, "bmp_autoleveling.bin",1);
		}
		else
		{
			BUTTON_SetBmpFileName(buttonLeveling.btnHandle, "bmp_leveling.bin",1);
		}
	}
	BUTTON_SetBmpFileName(buttonFilament.btnHandle, "bmp_filament.bin",1);	
	BUTTON_SetBmpFileName(buttonMore.btnHandle, "bmp_more.bin",1);	
	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);
	//bmp_struct.XSize = toolbtm_image_X;
	//bmp_struct.YSize = toolbtm_image_Y;
	BUTTON_SetBitmapEx(buttonPreHeat.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonExtruse.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
	BUTTON_SetBitmapEx(buttonMove.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
	BUTTON_SetBitmapEx(buttonZero.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
	if(gCfgItems.leveling_mode != 2)
	{
		BUTTON_SetBitmapEx(buttonLeveling.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
	}
	
	BUTTON_SetBitmapEx(buttonFilament.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
	BUTTON_SetBitmapEx(buttonMore.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);

	BUTTON_SetBkColor(buttonPreHeat.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonPreHeat.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonPreHeat.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonPreHeat.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
		
	BUTTON_SetBkColor(buttonExtruse.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonExtruse.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonExtruse.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonExtruse.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	
	BUTTON_SetBkColor(buttonMove.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonMove.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonMove.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonMove.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	
	BUTTON_SetBkColor(buttonZero.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonZero.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonZero.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonZero.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	
	BUTTON_SetBkColor(buttonLeveling.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonLeveling.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonLeveling.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonLeveling.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	
	BUTTON_SetBkColor(buttonFilament.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonFilament.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonFilament.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonFilament.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	
	BUTTON_SetBkColor(buttonMore.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonMore.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);	
	BUTTON_SetTextColor(buttonMore.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonMore.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);	

	if(gCfgItems.multiple_language != 0)
	{
		BUTTON_SetText(buttonPreHeat.btnHandle,tool_menu.preheat);
		BUTTON_SetText(buttonExtruse.btnHandle,tool_menu.extrude);
		BUTTON_SetText(buttonMove.btnHandle,tool_menu.move);
		BUTTON_SetText(buttonZero.btnHandle,tool_menu.home);
		if(gCfgItems.leveling_mode != 2)
		{
			if(gCfgItems.leveling_mode == 1)
				BUTTON_SetText(buttonLeveling.btnHandle,tool_menu.autoleveling);
			else
				BUTTON_SetText(buttonLeveling.btnHandle,tool_menu.leveling);
		}
		BUTTON_SetText(buttonFilament.btnHandle,tool_menu.filament);
		BUTTON_SetText(buttonMore.btnHandle,tool_menu.more);	
		BUTTON_SetText(buttonRet.btnHandle,common_menu.text_back);
	}

}

void Clear_Tool()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hToolWnd))
	{
		WM_DeleteWindow(hToolWnd);
		GUI_Exec();
	}
	
	//GUI_Clear();
}

