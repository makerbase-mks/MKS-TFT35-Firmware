#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_ready_print.h"
#include "draw_ui.h"
#include "draw_print_file.h"
#include "fontLib.h"
#include "draw_move_motor.h"
#include "text.h"
//#include "printer.h"
#include "draw_pre_heat.h"
#include "draw_extrusion.h"
#include "draw_zero.h"
#include "draw_set.h"
#include "draw_more.h"
#include "draw_fan.h"
#include "draw_more.h"
#include "draw_log_ui.h"
#include "draw_language.h"
#include "pic_manager.h"
#include "spi_flash.h"
#include "draw_manual_leveling.h"
#include "sd_usr.h"
#include "draw_tool.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static BUTTON_STRUCT  buttonPreHeat, buttonPrint, buttonExtruder, buttonMove, buttonFan, buttonMore, buttonZero, buttonSet,buttonLeveling;
static BUTTON_STRUCT  buttonTool;

static GUI_HWIN hReadyPrintWnd;
static TEXT_Handle textPrintTemp;
static TEXT_Handle textPrintTemp_CHIN;

int X_ADD=5,X_INTERVAL=10;   //**图片间隔
extern char cmd_code[201];
extern char x[1];
extern volatile char *codebufpoint;
extern volatile uint8_t  get_temp_flag;
extern uint8_t  Get_Temperature_Flg;
extern uint8_t leveling_first_time;

extern uint8_t disp_in_file_dir;


extern int8_t curSprayerTemp[10];
extern int8_t curBedTemp[10];
	

extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;

GUI_BITMAP bmp_test_struct = {
  78,//80, /* XSize */
  104,//50, /* YSize */
  160, /* BytesPerLine */
  16, /* BitsPerPixel */
  NULL,  /* Pointer to picture data */
  NULL  /* Pointer to palette */
 ,GUI_DRAW_BMPM565
};



static void cbReadPrintWin(WM_MESSAGE * pMsg) {
	
	switch (pMsg->MsgId) {
		case WM_PAINT:
			#if 0
			GUI_SetColor(GUI_WHITE);
			GUI_DrawRect(LCD_WIDTH/4 + 1, 1, LCD_WIDTH *3 / 4 -3, imgHeight /2 - 3);
			GUI_SetColor(GUI_STATE_COLOR);
			GUI_FillRect(LCD_WIDTH/4 + 2, 2, LCD_WIDTH *3 / 4 -4, imgHeight /2 - 4);
			#endif
			break;
		
		  
		case WM_NOTIFY_PARENT:
			if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
			{
				if(pMsg->hWinSrc == buttonPrint.btnHandle)
				{
					disp_in_file_dir = 1;
					last_disp_state = PRINT_READY_UI;
					Clear_ready_print();
					draw_print_file();      //printing 按键 入口
				}
				else if(pMsg->hWinSrc == buttonMove.btnHandle)
				{
					gCfgItems.getzpos_flg = 1;
					last_disp_state = PRINT_READY_UI;
					Clear_ready_print();
					draw_move_motor();			
				}
				else if(pMsg->hWinSrc == buttonPreHeat.btnHandle)
				{
					get_temp_flag=1;
					Get_Temperature_Flg = 1;
					last_disp_state = PRINT_READY_UI;
					Clear_ready_print();
					draw_preHeat();
				}
				else if(pMsg->hWinSrc == buttonExtruder.btnHandle)
				{
					
					Get_Temperature_Flg = 1;
					get_temp_flag = 1;
					last_disp_state = PRINT_READY_UI;
					Clear_ready_print();
					draw_extrusion();
				}
				else if(pMsg->hWinSrc == buttonZero.btnHandle)
				{
					last_disp_state = PRINT_READY_UI;
					Clear_ready_print();
					draw_Zero();
				}
				else if(pMsg->hWinSrc == buttonSet.btnHandle)
				{
					last_disp_state = PRINT_READY_UI;
					Clear_ready_print();
					draw_Set();
				}
				else if(pMsg->hWinSrc == buttonMore.btnHandle)
				{
					last_disp_state = PRINT_READY_UI;
					Clear_ready_print();
					draw_More();
				}
				else if(pMsg->hWinSrc == buttonTool.btnHandle)
				{
					last_disp_state = PRINT_READY_UI;
					Clear_ready_print();
					draw_tool();
				}
				else if(pMsg->hWinSrc == buttonLeveling.btnHandle)
				{
					
					if(gCfgItems.leveling_mode == 1)
					{
						SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_AUTOLEVELING_ADDR,201);
						codebufpoint = cmd_code;								
					}
					else
					{
						leveling_first_time = 1;
						last_disp_state = PRINT_READY_UI;
						Clear_ready_print();
						draw_leveling();
					}
					
					
				}
			}
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}




#if defined(TFT70)
void draw_ready_print()
{
	int i;

	disp_state_stack._disp_index = 0;
	memset(disp_state_stack._disp_state, 0, sizeof(disp_state_stack._disp_state));
	disp_state_stack._disp_state[disp_state_stack._disp_index] = PRINT_READY_UI;
	
	disp_state = PRINT_READY_UI;
	
	//GUI_SetFont(&GUI_Font8x18);
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();

	GUI_DispStringAt(creat_title_text(), TITLE_XPOS, TITLE_YPOS);


	hReadyPrintWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbReadPrintWin, 0);
	buttonPreHeat.btnHandle = BUTTON_CreateEx(INTERVAL_V,0,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 22);//alloc_win_id());
	buttonMove.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,0,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 23);//alloc_win_id());
	buttonZero.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,0,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 24);//alloc_win_id());
	buttonPrint.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 25);//alloc_win_id());
	buttonExtruder.btnHandle = BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 26);//alloc_win_id());
	if(gCfgItems.leveling_mode != 2)
	{
		buttonLeveling.btnHandle  = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hReadyPrintWnd, BUTTON_CF_SHOW, 0, 27);
		buttonSet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 29);//alloc_win_id());
		buttonMore.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 28);//alloc_win_id());
	}
	else
	{
		buttonSet.btnHandle  = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hReadyPrintWnd, BUTTON_CF_SHOW, 0, 27);
		buttonMore.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 29);//alloc_win_id());
	}
	BUTTON_SetBmpFileName(buttonPreHeat.btnHandle, "bmp_preHeat.bin",1);	
	BUTTON_SetBmpFileName(buttonPrint.btnHandle, "bmp_printing.bin",1);
	BUTTON_SetBmpFileName(buttonMove.btnHandle, "bmp_mov.bin",1);
	BUTTON_SetBmpFileName(buttonMore.btnHandle, "bmp_more.bin",1);
	BUTTON_SetBmpFileName(buttonZero.btnHandle, "bmp_zero.bin",1);
	//BUTTON_SetBmpFileName(buttonFan.btnHandle, "bmp_fan.bin",1);
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
	else
	{
		//BUTTON_SetBmpFileName(buttonLeveling.btnHandle, "bmp_fan.bin",1);
	}
	
	BUTTON_SetBmpFileName(buttonExtruder.btnHandle, "bmp_extruct.bin",1);
	BUTTON_SetBmpFileName(buttonSet.btnHandle, "bmp_set.bin",1);
	
	BUTTON_SetBitmapEx(buttonPreHeat.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonMove.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
	BUTTON_SetBitmapEx(buttonZero.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonPrint.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
	BUTTON_SetBitmapEx(buttonLeveling.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonExtruder.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
	BUTTON_SetBitmapEx(buttonSet.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
	BUTTON_SetBitmapEx(buttonMore.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
	
	BUTTON_SetBkColor(buttonPreHeat.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonPreHeat.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonPreHeat.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonPreHeat.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	
	BUTTON_SetBkColor(buttonPrint.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonPrint.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonPrint.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonPrint.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonMove.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonMove.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonMove.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonMove.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonMore.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonMore.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonMore.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonMore.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonZero.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonZero.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonZero.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonZero.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonLeveling.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonLeveling.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonLeveling.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonLeveling.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonExtruder.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonExtruder.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonExtruder.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonExtruder.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonSet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonSet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonSet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonSet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	if(gCfgItems.multiple_language !=0)
	{   
		BUTTON_SetText(buttonPreHeat.btnHandle, main_menu.preheat);
		BUTTON_SetText(buttonMove.btnHandle, main_menu.move);
		BUTTON_SetText(buttonZero.btnHandle, main_menu.home);
		BUTTON_SetText(buttonPrint.btnHandle, main_menu.print);
		BUTTON_SetText(buttonExtruder.btnHandle, main_menu.extrude);
		if(gCfgItems.leveling_mode !=2)
		{
			if(gCfgItems.leveling_mode == 1)
			{	
				BUTTON_SetText(buttonLeveling.btnHandle, main_menu.autoleveling);
			}
			else
			{
				BUTTON_SetText(buttonLeveling.btnHandle, main_menu.leveling);
			}
		}
		else
		{
			//BUTTON_SetText(buttonLeveling.btnHandle, main_menu.fan);
		}
		BUTTON_SetText(buttonSet.btnHandle, main_menu.set);
		BUTTON_SetText(buttonMore.btnHandle, main_menu.more);
	}
}
#elif defined(TFT35)
void draw_ready_print()
{
	int i;

	disp_state_stack._disp_index = 0;
	memset(disp_state_stack._disp_state, 0, sizeof(disp_state_stack._disp_state));
	disp_state_stack._disp_state[disp_state_stack._disp_index] = PRINT_READY_UI;
	
	disp_state = PRINT_READY_UI;
	
	//GUI_SetFont(&GUI_Font8x18);
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();

	if(gCfgItems.display_style == 0)
	{
		GUI_DispStringAt(creat_title_text(), TITLE_XPOS, TITLE_YPOS);


		hReadyPrintWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbReadPrintWin, 0);
		buttonPreHeat.btnHandle = BUTTON_CreateEx(INTERVAL_V,0,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 22);//alloc_win_id());
		buttonMove.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,0,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 23);//alloc_win_id());
		buttonZero.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,0,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 24);//alloc_win_id());
		buttonPrint.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 25);//alloc_win_id());
		buttonExtruder.btnHandle = BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 26);//alloc_win_id());
		if(gCfgItems.leveling_mode != 2)
		{
			buttonLeveling.btnHandle  = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hReadyPrintWnd, BUTTON_CF_SHOW, 0, 27);
			buttonSet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 29);//alloc_win_id());
			buttonMore.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 28);//alloc_win_id());
		}
		else
		{
			buttonSet.btnHandle  = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hReadyPrintWnd, BUTTON_CF_SHOW, 0, 27);
			buttonMore.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 29);//alloc_win_id());
		}
		BUTTON_SetBmpFileName(buttonPreHeat.btnHandle, "bmp_preHeat.bin",1);	
		BUTTON_SetBmpFileName(buttonPrint.btnHandle, "bmp_printing.bin",1);
		BUTTON_SetBmpFileName(buttonMove.btnHandle, "bmp_mov.bin",1);
		BUTTON_SetBmpFileName(buttonMore.btnHandle, "bmp_more.bin",1);
		BUTTON_SetBmpFileName(buttonZero.btnHandle, "bmp_zero.bin",1);
		//BUTTON_SetBmpFileName(buttonFan.btnHandle, "bmp_fan.bin",1);
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
		else
		{
			//BUTTON_SetBmpFileName(buttonLeveling.btnHandle, "bmp_fan.bin",1);
		}
		
		BUTTON_SetBmpFileName(buttonExtruder.btnHandle, "bmp_extruct.bin",1);
		BUTTON_SetBmpFileName(buttonSet.btnHandle, "bmp_set.bin",1);
		
		BUTTON_SetBitmapEx(buttonPreHeat.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
		BUTTON_SetBitmapEx(buttonMove.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
		BUTTON_SetBitmapEx(buttonZero.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
		BUTTON_SetBitmapEx(buttonPrint.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
		BUTTON_SetBitmapEx(buttonLeveling.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
		BUTTON_SetBitmapEx(buttonExtruder.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
		BUTTON_SetBitmapEx(buttonSet.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
		BUTTON_SetBitmapEx(buttonMore.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
		
		BUTTON_SetBkColor(buttonPreHeat.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonPreHeat.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonPreHeat.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonPreHeat.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
		
		BUTTON_SetBkColor(buttonPrint.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonPrint.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonPrint.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonPrint.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

		BUTTON_SetBkColor(buttonMove.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonMove.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonMove.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonMove.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

		BUTTON_SetBkColor(buttonMore.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonMore.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonMore.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonMore.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

		BUTTON_SetBkColor(buttonZero.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonZero.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonZero.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonZero.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

		BUTTON_SetBkColor(buttonLeveling.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonLeveling.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonLeveling.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonLeveling.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

		BUTTON_SetBkColor(buttonExtruder.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonExtruder.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonExtruder.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonExtruder.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

		BUTTON_SetBkColor(buttonSet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonSet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonSet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonSet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

		if(gCfgItems.multiple_language !=0)
		{   
			BUTTON_SetText(buttonPreHeat.btnHandle, main_menu.preheat);
			BUTTON_SetText(buttonMove.btnHandle, main_menu.move);
			BUTTON_SetText(buttonZero.btnHandle, main_menu.home);
			BUTTON_SetText(buttonPrint.btnHandle, main_menu.print);
			BUTTON_SetText(buttonExtruder.btnHandle, main_menu.extrude);
			if(gCfgItems.leveling_mode !=2)
			{
				if(gCfgItems.leveling_mode == 1)
				{	
					BUTTON_SetText(buttonLeveling.btnHandle, main_menu.autoleveling);
				}
				else
				{
					BUTTON_SetText(buttonLeveling.btnHandle, main_menu.leveling);
				}
			}
			else
			{
				//BUTTON_SetText(buttonLeveling.btnHandle, main_menu.fan);
			}
			BUTTON_SetText(buttonSet.btnHandle, main_menu.set);
			BUTTON_SetText(buttonMore.btnHandle, main_menu.more);
		}
	}
	else
	{
		hReadyPrintWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbReadPrintWin, 0);
		buttonTool.btnHandle = BUTTON_CreateEx(MAINPAGE_GRAP,(LCD_HEIGHT-BTN_Y_PIXEL)/2,BTN_X_PIXEL,BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 22);//alloc_win_id());
		buttonSet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+MAINPAGE_GRAP*2,(LCD_HEIGHT-BTN_Y_PIXEL)/2,BTN_X_PIXEL,BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 23);//alloc_win_id());
		buttonPrint.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+MAINPAGE_GRAP*3,(LCD_HEIGHT-BTN_Y_PIXEL)/2,BTN_X_PIXEL,BTN_Y_PIXEL,hReadyPrintWnd, BUTTON_CF_SHOW, 0, 24);//alloc_win_id());		

		BUTTON_SetBmpFileName(buttonTool.btnHandle,"bmp_tool.bin",1);
		BUTTON_SetBmpFileName(buttonSet.btnHandle,"bmp_set.bin",1);
		BUTTON_SetBmpFileName(buttonPrint.btnHandle,"bmp_printing.bin",1);

		BUTTON_SetBitmapEx(buttonTool.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
		BUTTON_SetBitmapEx(buttonSet.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	
		BUTTON_SetBitmapEx(buttonPrint.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);	

		BUTTON_SetBkColor(buttonTool.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonTool.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonTool.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonTool.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

		BUTTON_SetBkColor(buttonSet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonSet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonSet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonSet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

		BUTTON_SetBkColor(buttonPrint.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonPrint.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonPrint.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonPrint.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

		if(gCfgItems.multiple_language !=0)
		{
			BUTTON_SetText(buttonTool.btnHandle, main_menu.tool);
			BUTTON_SetText(buttonSet.btnHandle, main_menu.set);
			BUTTON_SetText(buttonPrint.btnHandle, main_menu.print);
		}
		
	}
}
#endif
void Clear_ready_print()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hReadyPrintWnd))
	{
		WM_DeleteWindow(hReadyPrintWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}

