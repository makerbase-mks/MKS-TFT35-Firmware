#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_operate.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"
#include "text.h"
#include "draw_printing.h"
#include "draw_pause_ui.h"
#include "draw_pre_heat.h"
#include "draw_fan.h"
#include "draw_change_speed.h"
#include "draw_printing_moremenu.h"
#include "mks_tft_com.h"
#include "mks_cfg.h"
#include "draw_move_motor.h"
#include "draw_extrusion.h"
#include "draw_filamentchange.h"
#include "draw_babyStep.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hOperateWnd, hStopDlgWnd;

extern int8_t curFilePath[30];
extern FILE_PRINT_STATE gCurFileState ;
extern void reset_tx_fifo();

extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern int X_ADD, X_INTERVAL;

static PROGBAR_Handle printingBar;

static TEXT_Handle textPrintTemp1, textPrintTemp2, printStopDlgText,Fill_State_BK;
static BUTTON_STRUCT buttonPause, buttonStop, buttonTemperature, buttonSpeed, buttonMore_printing, buttonRet, buttonOk, buttonCancle,buttonFan;
static BUTTON_STRUCT buttonFilament,buttonAuto_Off,buttonExtrude,buttonMove,buttonBabyStep;

extern PR_STATUS printerStaus;
extern uint8_t flash_preview_begin;
extern uint8_t from_flash_pic;
extern uint8_t default_preview_flg;

uint8_t pause_flag;

uint8_t IsChooseAutoShutdown = 0;

//void Autoshutdown_display();

static void cbOperateWin(WM_MESSAGE * pMsg) {

switch (pMsg->MsgId)
{
	case WM_PAINT:
		//GUI_SetColor(gCfgItems.state_background_color);
		//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
		//GUI_SetColor(gCfgItems.state_background_color);
		//GUI_FillRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
		
		break;
	case WM_TOUCH:
	 	
		break;
	case WM_TOUCH_CHILD:
		
		break;
		
	case WM_NOTIFY_PARENT:
		if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
		{
			#if 0
			if(pMsg->hWinSrc == buttonPause.btnHandle)
			{
				stop_print_time();
				if(printerStaus == pr_working)
				{
					//**I2C_EE_Init(100000);
					MX_I2C1_Init(100000);
					/////print_task_flag = TASK_PAUSE;
					last_disp_state = OPERATE_UI;
					printerStaus = pr_pause;
					Clear_operate();
					draw_pause();
				}
			}
			else if(pMsg->hWinSrc == buttonStop.btnHandle)
			{	
				last_disp_state = OPERATE_UI;
				Clear_operate();
				
				draw_dialog(DIALOG_TYPE_STOP);
				
			}
			else 
				#endif
				if(pMsg->hWinSrc == buttonRet.btnHandle)
			{
				if(from_flash_pic==1)
					flash_preview_begin = 1;
				else
					default_preview_flg = 1;
				
				last_disp_state = OPERATE_UI;
				Clear_operate();
				draw_return_ui();
			}
			else if(pMsg->hWinSrc == buttonTemperature.btnHandle)
			{
				//sean 2019.1.3
				#if 0
				if(gCfgItems.sprayerNum==2)
				{
					gCfgItems.curSprayerChoose_bak= gCfgItems.curSprayerChoose;
				}
				#endif
				last_disp_state = OPERATE_UI;
				Clear_operate();
				draw_preHeat();
			}
			else if(pMsg->hWinSrc == buttonFan.btnHandle)
			{
				last_disp_state = OPERATE_UI;
				Clear_operate();
				draw_fan();
			}
			else if(pMsg->hWinSrc == buttonFilament.btnHandle)
			{
				if(gCfgItems.sprayerNum==2)
				{
					gCfgItems.curSprayerChoose_bak= gCfgItems.curSprayerChoose;
				}
				
				if(printerStaus == pr_working)
				{
					stop_print_time();
					last_disp_state = OPERATE_UI;
					MX_I2C1_Init(100000);
					printerStaus = pr_pause;				
					Clear_operate();
					draw_FilamentChange();
				}
				else
				{
					last_disp_state = OPERATE_UI;
					Clear_operate();
					draw_FilamentChange();					
				}

			}			
			else if (pMsg->hWinSrc == buttonMore_printing.btnHandle)
			{
				last_disp_state = OPERATE_UI;
				Clear_operate();
				draw_printmore();				
			}
			else if(pMsg->hWinSrc == buttonSpeed.btnHandle)
			{
				last_disp_state = OPERATE_UI;
				Clear_operate();
				//sean 2019.1.3
				#if 0
				if(gCfgItems.sprayerNum==2)
				{
					gCfgItems.curSprayerChoose_bak= gCfgItems.curSprayerChoose;
				}	
				#endif
				draw_changeSpeed();
			}
			else if(pMsg->hWinSrc == buttonExtrude.btnHandle)
			{
				last_disp_state = OPERATE_UI;
				Clear_operate();
				if(gCfgItems.sprayerNum==2)
				{
					//sean 2019.1.3
					//gCfgItems.curSprayerChoose_bak= gCfgItems.curSprayerChoose;
				}
				draw_extrusion();
			}	
			else if(pMsg->hWinSrc == buttonMove.btnHandle)
			{
				last_disp_state = OPERATE_UI;
				Clear_operate();
				draw_move_motor();
			}
			#if 1
			else if(pMsg->hWinSrc == buttonAuto_Off.btnHandle)
			{
				if(IsChooseAutoShutdown == 1)
				{
						IsChooseAutoShutdown = 0;		
						Autoshutdown_display();
				}
				else
				{
						IsChooseAutoShutdown = 1;
						Autoshutdown_display();
				}
			}	
			else if(pMsg->hWinSrc == buttonBabyStep.btnHandle)
			{
				pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) GET_BABY_STEP_VALUE_COMMAND);
				pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) GET_BABY_ZOFFSET_COMMAND);
				
				last_disp_state = OPERATE_UI;
				Clear_operate();
				draw_babyStep();
			}
			#endif
		}
		break;
		
	default:
		WM_DefaultProc(pMsg);
	}
}


void draw_operate()
{
	int i;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != OPERATE_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = OPERATE_UI;
	}
	
	disp_state = OPERATE_UI;
		
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();

	
	//GUI_UC_SetEncodeNone();
	//GUI_SetFont(&GUI_FontHZ16);
	GUI_DispStringAt(creat_title_text(), TITLE_XPOS, TITLE_YPOS);
	//GUI_SetFont(&FONT_TITLE);
	//GUI_UC_SetEncodeUTF8();
	
	hOperateWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbOperateWin, 0);

	buttonTemperature.btnHandle = BUTTON_CreateEx(INTERVAL_V,0,BTN_X_PIXEL, BTN_Y_PIXEL, hOperateWnd, BUTTON_CF_SHOW, 0, 301);
	buttonFan.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,0,BTN_X_PIXEL, BTN_Y_PIXEL, hOperateWnd, BUTTON_CF_SHOW, 0, 302);
	buttonFilament.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,0,BTN_X_PIXEL,BTN_Y_PIXEL, hOperateWnd, BUTTON_CF_SHOW, 0, 303);

	if(printerStaus ==pr_working)
	{
		buttonExtrude.btnHandle = 0;
		buttonMove.btnHandle = 0;
		
		buttonSpeed.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,0,BTN_X_PIXEL, BTN_Y_PIXEL,hOperateWnd, BUTTON_CF_SHOW, 0, 106);
		buttonMore_printing.btnHandle = BUTTON_CreateEx(INTERVAL_V, BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hOperateWnd, BUTTON_CF_SHOW, 0, 302);

		if(gCfgItems.print_finish_close_machine_flg == 1)
		{
			buttonAuto_Off.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hOperateWnd, BUTTON_CF_SHOW, 0, 302);

			if(gCfgItems.baby_step_display_flg == 1)
			{
				buttonBabyStep.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3, BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hOperateWnd, BUTTON_CF_SHOW, 0, 304);
				BUTTON_SetBmpFileName(buttonBabyStep.btnHandle, "bmp_babystep.bin",1);
				BUTTON_SetBitmapEx(buttonBabyStep.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
				BUTTON_SetBkColor(buttonBabyStep.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				BUTTON_SetBkColor(buttonBabyStep.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				BUTTON_SetTextColor(buttonBabyStep.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
				BUTTON_SetTextColor(buttonBabyStep.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);
				BUTTON_SetText(buttonBabyStep.btnHandle, operation_menu.babystep);
			}
		}
		else
		{
			if(gCfgItems.baby_step_display_flg == 1)
			{
				buttonBabyStep.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2, BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hOperateWnd, BUTTON_CF_SHOW, 0, 304);
				BUTTON_SetBmpFileName(buttonBabyStep.btnHandle, "bmp_babystep.bin",1);
				BUTTON_SetBitmapEx(buttonBabyStep.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
				BUTTON_SetBkColor(buttonBabyStep.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				BUTTON_SetBkColor(buttonBabyStep.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				BUTTON_SetTextColor(buttonBabyStep.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
				BUTTON_SetTextColor(buttonBabyStep.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);
				BUTTON_SetText(buttonBabyStep.btnHandle, operation_menu.babystep);	
			}
		}
		

	}
	else
	{
		buttonSpeed.btnHandle = 0;
		buttonAuto_Off.btnHandle = 0;
		
		buttonExtrude.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,0,BTN_X_PIXEL,BTN_Y_PIXEL,hOperateWnd, BUTTON_CF_SHOW, 0, 106);
		buttonMove.btnHandle = BUTTON_CreateEx(INTERVAL_V,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hOperateWnd, BUTTON_CF_SHOW, 0, 106);		
		buttonMore_printing.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2, BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hOperateWnd, BUTTON_CF_SHOW, 0, 302);

		if(gCfgItems.print_finish_close_machine_flg == 1)
		{
			buttonAuto_Off.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL,BTN_Y_PIXEL,hOperateWnd, BUTTON_CF_SHOW, 0, 107);
		}

	}
	buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4, BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hOperateWnd, BUTTON_CF_SHOW, 0, 306);

	#if VERSION_WITH_PIC	

	BUTTON_SetBmpFileName(buttonTemperature.btnHandle, "bmp_opt_temp.bin",1);
	BUTTON_SetBmpFileName(buttonSpeed.btnHandle, "bmp_speed.bin",1);
	BUTTON_SetBmpFileName(buttonFan.btnHandle, "bmp_fan.bin",1);
	BUTTON_SetBmpFileName(buttonFilament.btnHandle, "bmp_filament.bin",1);
	BUTTON_SetBmpFileName(buttonExtrude.btnHandle, "bmp_extrude_opr.bin",1);
	BUTTON_SetBmpFileName(buttonMove.btnHandle, "bmp_move_opr.bin",1);
	BUTTON_SetBmpFileName(buttonMore_printing.btnHandle, "bmp_more_opr.bin",1);
	if(gCfgItems.print_finish_close_machine_flg == 1)
	{
		if(IsChooseAutoShutdown == 1)
		{
			BUTTON_SetBmpFileName(buttonAuto_Off.btnHandle, "bmp_auto_off.bin",1);
			BUTTON_SetBkColor(buttonAuto_Off.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_color);
			BUTTON_SetBkColor(buttonAuto_Off.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_color);	
			BUTTON_SetTextColor(buttonAuto_Off.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_textcolor);
			BUTTON_SetTextColor(buttonAuto_Off.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_textcolor);
			
			if(gCfgItems.multiple_language != 0)
			{	
				BUTTON_SetText(buttonAuto_Off.btnHandle,operation_menu.auto_off);
			}

		}
		else
		{
			BUTTON_SetBmpFileName(buttonAuto_Off.btnHandle, "bmp_manual_off.bin",1);
			BUTTON_SetBkColor(buttonAuto_Off.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
			BUTTON_SetBkColor(buttonAuto_Off.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
			BUTTON_SetTextColor(buttonAuto_Off.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
			BUTTON_SetTextColor(buttonAuto_Off.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);			
			if(gCfgItems.multiple_language != 0)
			{	
				BUTTON_SetText(buttonAuto_Off.btnHandle,operation_menu.manual_off);
			}			
		}
		BUTTON_SetBitmapEx(buttonAuto_Off.btnHandle,0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);

		
	}
	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);
	
	BUTTON_SetBitmapEx(buttonTemperature.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonSpeed.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonFan.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonFilament.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonExtrude.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonMove.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
#if 0
	if(gCfgItems.print_finish_close_machine_flg == 1)
	{
		BUTTON_SetBitmapEx(buttonAuto_Off.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
		BUTTON_SetBitmapEx(buttonMore_printing.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	}
	else
#endif
	{
		BUTTON_SetBitmapEx(buttonMore_printing.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	}
	
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);

	BUTTON_SetBkColor(buttonTemperature.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonTemperature.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonSpeed.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonSpeed.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonFan.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonFan.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonFilament.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonFilament.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonTemperature.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonTemperature.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonSpeed.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonSpeed.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonFan.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonFan.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonFilament.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonFilament.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);


	BUTTON_SetBkColor(buttonMove.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonMove.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonMove.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonMove.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	
	BUTTON_SetBkColor(buttonExtrude.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonExtrude.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonExtrude.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonExtrude.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonMore_printing.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonMore_printing.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonMore_printing.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonMore_printing.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);



	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);

	if(gCfgItems.multiple_language != 0)
	{
		BUTTON_SetText(buttonFan.btnHandle, operation_menu.fan);
		BUTTON_SetText(buttonFilament.btnHandle, operation_menu.filament);
		BUTTON_SetText(buttonTemperature.btnHandle, operation_menu.temp);
		BUTTON_SetText(buttonMore_printing.btnHandle, operation_menu.more);
		BUTTON_SetText(buttonSpeed.btnHandle, operation_menu.speed);
		BUTTON_SetText(buttonExtrude.btnHandle, operation_menu.extr);
		BUTTON_SetText(buttonMove.btnHandle, operation_menu.move);
		BUTTON_SetText(buttonRet.btnHandle, common_menu.text_back);
		
	}

	

	#endif
#if 0
	if(gCfgItems.print_finish_close_machine_flg == 1)
	{
		Autoshutdown_display();
	}
#endif
#if 0
	Fill_State_BK = TEXT_CreateEx(LCD_WIDTH  / 4+X_ADD, 0, LCD_WIDTH / 2-X_INTERVAL, imgHeight / 2-X_INTERVAL, hOperateWnd, WM_CF_SHOW, TEXT_CF_LEFT,	GUI_ID_TEXT0, " ");
	TEXT_SetBkColor(Fill_State_BK, gCfgItems.state_background_color);

	textPrintTemp1 = TEXT_CreateEx(LCD_WIDTH  / 4 + 50, 120, LCD_WIDTH / 4 - 30, 80, hOperateWnd, WM_CF_SHOW, TEXT_CF_LEFT,	GUI_ID_TEXT1, " ");

	textPrintTemp2 = TEXT_CreateEx(LCD_WIDTH  / 2+80 , 120, LCD_WIDTH / 4 - 90, 80, hOperateWnd, WM_CF_SHOW, TEXT_CF_LEFT,	GUI_ID_TEXT2, " ");
	

	TEXT_SetTextAlign(textPrintTemp1,  GUI_TA_VCENTER | GUI_TA_LEFT);
	TEXT_SetTextAlign(textPrintTemp2,  GUI_TA_VCENTER | GUI_TA_LEFT);
	
	printingBar = PROGBAR_CreateEx(LCD_WIDTH  / 4 + 5, 40,  LCD_WIDTH / 2 - 10, 45, hOperateWnd, WM_CF_SHOW, 0, 0);
	
	PROGBAR_SetBarColor(printingBar, 0, GUI_GREEN);
	
	PROGBAR_SetTextColor(printingBar, 0, GUI_BLACK);
	PROGBAR_SetFont(printingBar, &GUI_FontHZ_fontHz18);
	
	
	PROGBAR_SetValue(printingBar, get_printing_rate(srcfp));
      
       
	disp_temp_operate();
#endif	
	//GUI_Exec();
	

	
}


/*void setProBarRateOpera()
{

	int rate;
	volatile long long rate_tmp_op;
	rate_tmp_op = (long long)sd.sdpos * 100;
	rate = rate_tmp_op / sd.filesize;

	if(rate <= 0)
		return;
	
	
	if(disp_state == OPERATE_UI)
	{
		PROGBAR_SetValue(printingBar, rate );
	}
	
}*/

void setProBarRateOpera(int rate)
{
	if(rate <= 0)
		return;
	gCurFileState.totalSend = rate;
	
	if(disp_state == OPERATE_UI)
	{
		PROGBAR_SetValue(printingBar, rate );
	}
	
}

void disp_temp_operate()
{
	char buf[50] = {0};
	
	TEXT_SetTextColor(textPrintTemp1, gCfgItems.state_text_color);
	TEXT_SetTextColor(textPrintTemp2, gCfgItems.state_text_color);
	//GUI_SetFont(&FONT_STATE_INF);

	TEXT_SetBkColor(textPrintTemp1, gCfgItems.state_background_color);
	TEXT_SetBkColor(textPrintTemp2, gCfgItems.state_background_color);
	
/*
	#ifdef SPRAYER_NUM_LIMIT	
	if(gCfgItems.sprayerNum == 2)
	#endif
	{
		sprintf(buf, " E1:%d\n B:%d", (int)gCfgItems.curSprayerTemp[0], (int)gCfgItems.curBedTemp);
	
	}
	#ifdef SPRAYER_NUM_LIMIT	
	else
	{
		sprintf(buf, "%.1f  %.1f  %d", gCfgItems.curSprayerTemp[0], gCfgItems.curBedTemp, gCfgItems.fanSpeed);
	
	}
	#endif
	TEXT_SetText(textPrintTemp1, buf);
	
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "E2:%d\nFAN:%d", (int)gCfgItems.curSprayerTemp[1], gCfgItems.fanSpeed);
	TEXT_SetText(textPrintTemp2, buf);
*/
	if(gCfgItems.sprayerNum == 2)
	{
		TEXT_SetFont(textPrintTemp1,&GUI_FontHZ_fontHz18);
		TEXT_SetFont(textPrintTemp2,&GUI_FontHZ_fontHz18);
		if(gCfgItems.custom_bed_flag == 1)
		{
			
			sprintf(buf, " E1:%d\n B:%d", (int)gCfgItems.curSprayerTemp[0], (int)gCfgItems.curBedTemp);
			TEXT_SetText(textPrintTemp1, buf);
		}
		else
		{
			sprintf(buf, " E 1:%d\n", (int)gCfgItems.curSprayerTemp[0]);
			TEXT_SetText(textPrintTemp1, buf);			
		}
		
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "E 2:%d\nFAN:%d", (int)gCfgItems.curSprayerTemp[1],gCfgItems.fanSpeed);
		TEXT_SetText(textPrintTemp2, buf);
		
	}
	else
	{
		TEXT_SetFont(textPrintTemp1,&GUI_FontHZ_fontHz18);
		TEXT_SetFont(textPrintTemp2,&GUI_FontHZ_fontHz18);
		if(gCfgItems.custom_bed_flag == 1)
		{
			
			sprintf(buf, " E1:%d     B:%d", (int)gCfgItems.curSprayerTemp[0], (int)gCfgItems.curBedTemp);
			TEXT_SetText(textPrintTemp1, buf);
		}
		else
		{
			
			sprintf(buf, " E1:%d\n", (int)gCfgItems.curSprayerTemp[0]);
			TEXT_SetText(textPrintTemp1, buf);			
		}
		
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "FAN:%d", gCfgItems.fanSpeed);
		TEXT_SetText(textPrintTemp2, buf);
	}

}
#if 1
void Autoshutdown_display()
{
	if(IsChooseAutoShutdown == 1)
	{
		BUTTON_SetBmpFileName(buttonAuto_Off.btnHandle, "bmp_auto_off.bin",1);
		
		BUTTON_SetBkColor(buttonAuto_Off.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_color);
		BUTTON_SetBkColor(buttonAuto_Off.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_color);
		
		BUTTON_SetTextColor(buttonAuto_Off.btnHandle,BUTTON_CI_PRESSED,gCfgItems.btn_state_sel_textcolor);
		BUTTON_SetTextColor(buttonAuto_Off.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.btn_state_sel_textcolor);
		
		if(gCfgItems.multiple_language != 0)
		{	
			BUTTON_SetText(buttonAuto_Off.btnHandle,operation_menu.auto_off);
		}
			
	}
	else
	{
		BUTTON_SetBmpFileName(buttonAuto_Off.btnHandle, "bmp_manual_off.bin",1);
		BUTTON_SetBkColor(buttonAuto_Off.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
		BUTTON_SetBkColor(buttonAuto_Off.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);

		BUTTON_SetTextColor(buttonAuto_Off.btnHandle,BUTTON_CI_PRESSED,gCfgItems.btn_state_textcolor);
		BUTTON_SetTextColor(buttonAuto_Off.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.btn_state_textcolor);
		if(gCfgItems.multiple_language != 0)
		{	
			BUTTON_SetText(buttonAuto_Off.btnHandle,operation_menu.manual_off);
		}		
	}

}
#endif
void Clear_operate()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hOperateWnd))
	{
		WM_DeleteWindow(hOperateWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}
