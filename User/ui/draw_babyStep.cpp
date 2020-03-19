#include "draw_babyStep.h"
#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "draw_print_file.h"
#include "fontLib.h"
//#include "printer.h"
//#include "gcode.h"
#include <math.h>
#include <stdint.h>
#include "stdint.h"
#include "mks_tft_fifo.h"
#include "mks_tft_com.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif


static BUTTON_STRUCT buttonXI, buttonXD, buttonYI, buttonYD, buttonZI, buttonZD, buttonV,  buttonRet;
GUI_HWIN hMoveBabyStepWnd;

extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern TFT_FIFO gcodeCmdTxFIFO;		//gcode 指令发送队列
extern TFT_FIFO gcodeCmdRxFIFO;		//gcode	指令接收队列
extern unsigned char positionSaveFlag;
extern int X_ADD,X_INTERVAL;   //**图片间隔
extern PR_STATUS printerStaus;

//int16_t curXSpeed = 3000;
//int16_t curYSpeed = 3000;
//int16_t curZSpeed = 3000;
static float babystep_dist=0.01;
static uint8_t has_adjust_z = 0; 

static void cbBabyStepMotorWin(WM_MESSAGE * pMsg) {
	
	struct PressEvt *press_event;
	char buf[30] = {0};

	switch (pMsg->MsgId) {
	case WM_PAINT:
	//GUI_SetBkColor(GUI_BLACK);
	//	GUI_Clear();
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
		
			press_event = (struct PressEvt *)pMsg->Data.p;

			
			if(pMsg->hWinSrc == buttonXI.btnHandle)
			{
				BABY_STEP_X_COMMAN(buf, babystep_dist);
				pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
			}
			else if(pMsg->hWinSrc == buttonXD.btnHandle)
			{
				BABY_STEP_X_COMMAN(buf, (float)0-babystep_dist);
				pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
			}
			else if(pMsg->hWinSrc == buttonYI.btnHandle)
			{
				BABY_STEP_Y_COMMAN(buf, babystep_dist);
				pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
			}
			else if(pMsg->hWinSrc == buttonYD.btnHandle)
			{
				BABY_STEP_Y_COMMAN(buf, (float)0-babystep_dist);
				pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
			}
			else if(pMsg->hWinSrc == buttonZI.btnHandle)
			{
				has_adjust_z = 1; 
				BABY_STEP_Z_COMMAN(buf, babystep_dist);
				pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
			}
			else if(pMsg->hWinSrc == buttonZD.btnHandle)
			{
				has_adjust_z = 1; 
				BABY_STEP_Z_COMMAN(buf, (float)0-babystep_dist);
				pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
			}
			else if(pMsg->hWinSrc == buttonRet.btnHandle)
			{
				 
				if(has_adjust_z == 1)
					pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) SAVE_EEPROM_COMMAND);
				has_adjust_z = 0;
				
				last_disp_state = BABY_STEP_UI;
				Clear_babyStep();
				draw_return_ui();
								
			}
			else if(pMsg->hWinSrc == buttonV.btnHandle)
			{
				if(abs((int)(100 * babystep_dist)) == 1)
				{
					babystep_dist = 0.05;
				}
				else if(abs((int)(100 * babystep_dist)) == 5)
				{
					babystep_dist = 0.1;
				}
				else 
				{
					babystep_dist = 0.01;
				}
				
				disp_babystep_dist();
				
			}
			
			
		}
		break;
	default:
	WM_DefaultProc(pMsg);
	}
}


void draw_babyStep()
{
	
  	char buffer_z[15]={0};
	
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != BABY_STEP_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = BABY_STEP_UI;
	}
	disp_state = BABY_STEP_UI;
	
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();

	GUI_DispStringAt(creat_title_text(),  TITLE_XPOS, TITLE_YPOS);

	hMoveBabyStepWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbBabyStepMotorWin, 0);

	buttonXI.btnHandle = BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoveBabyStepWnd, BUTTON_CF_SHOW, 0, 101);
	buttonYI.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2, 0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoveBabyStepWnd, BUTTON_CF_SHOW, 0, 102);
	buttonZI.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoveBabyStepWnd, BUTTON_CF_SHOW, 0, 103);

	
	buttonXD.btnHandle = BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoveBabyStepWnd, BUTTON_CF_SHOW, 0, 105);
	buttonYD.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoveBabyStepWnd, BUTTON_CF_SHOW, 0, 106);
	buttonZD.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoveBabyStepWnd, BUTTON_CF_SHOW, 0, 107);

	buttonV.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoveBabyStepWnd, BUTTON_CF_SHOW, 0, 108);
	buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoveBabyStepWnd, BUTTON_CF_SHOW, 0, 109);

	#if VERSION_WITH_PIC	

	BUTTON_SetBmpFileName(buttonXI.btnHandle, "bmp_xAdd.bin",1);
	BUTTON_SetBmpFileName(buttonXD.btnHandle, "bmp_xDec.bin",1);
	BUTTON_SetBmpFileName(buttonYI.btnHandle, "bmp_yAdd.bin",1);
	BUTTON_SetBmpFileName(buttonYD.btnHandle, "bmp_yDec.bin",1);
	BUTTON_SetBmpFileName(buttonZI.btnHandle, "bmp_zAdd.bin",1);
	BUTTON_SetBmpFileName(buttonZD.btnHandle, "bmp_zDec.bin",1);
	//
	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);
	
	#endif
	BUTTON_SetBitmapEx(buttonXI.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonXD.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonYI.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonYD.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonZI.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonZD.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonV.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);

	BUTTON_SetBkColor(buttonXI.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonXI.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonXI.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonXI.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonXD.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonXD.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonXD.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonXD.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonYI.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonYI.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonYI.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonYI.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonYD.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonYD.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonYD.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonYD.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonZI.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonZI.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonZI.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonZI.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonZD.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonZD.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonZD.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonZD.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonV.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(buttonV.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetTextColor(buttonV.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
	BUTTON_SetTextColor(buttonV.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);

	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);

	if(gCfgItems.multiple_language != 0)
	{
		BUTTON_SetText(buttonXI.btnHandle, move_menu.x_add);
		BUTTON_SetText(buttonXD.btnHandle,move_menu.x_dec);
		BUTTON_SetText(buttonYI.btnHandle, move_menu.y_add);
		BUTTON_SetText(buttonYD.btnHandle, move_menu.y_dec);
		BUTTON_SetText(buttonZI.btnHandle, move_menu.z_add);
		BUTTON_SetText(buttonZD.btnHandle, move_menu.z_dec);
	    BUTTON_SetText(buttonRet.btnHandle, common_menu.text_back);
	}

	disp_babystep_dist();

	
	
/////	GUI_Exec();

	
}

void disp_babystep_dist()
{
	char buf[30] = {0};
		
	if((int)(100 *babystep_dist) == 1)
	{
		BUTTON_SetBmpFileName(buttonV.btnHandle, "bmp_babystep00_1.bin",1);
	}
	else if((int)(100*babystep_dist) == 5)
	{
		BUTTON_SetBmpFileName(buttonV.btnHandle, "bmp_babystep005.bin",1);
	}
	else if((int)(100*babystep_dist) == 10)
	{
		BUTTON_SetBmpFileName(buttonV.btnHandle, "bmp_babystep0_1.bin",1);
	}
	if(gCfgItems.multiple_language != 0)
	{
		if((int)(100 * babystep_dist) == 1)
			BUTTON_SetText(buttonV.btnHandle,move_menu.step_001mm);
		else if((int)(100 * babystep_dist) == 5)
			BUTTON_SetText(buttonV.btnHandle,move_menu.step_005mm);
		else if((int)(100 * babystep_dist) == 10)
			BUTTON_SetText(buttonV.btnHandle,move_menu.step_01mm);
	}	
}

void Clear_babyStep()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hMoveBabyStepWnd))
	{
		WM_DeleteWindow(hMoveBabyStepWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}

