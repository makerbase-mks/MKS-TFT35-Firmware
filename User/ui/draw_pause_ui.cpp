#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_pause_ui.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"
#include "text.h"
#include "draw_printing.h"
#include "draw_extrusion.h"
#include "draw_pause_ui.h"
#include "draw_fan.h"
#include "draw_pre_heat.h"
#include "draw_move_motor.h"
#include "draw_operate.h"
#include "draw_printing_moremenu.h"
#include "mks_tft_com.h"
#include "mks_cfg.h"
#include "ff.h"
#include "sd_usr.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hPauseWnd;

extern int X_ADD,X_INTERVAL;   //**图片间隔

extern uint8_t  Get_Temperature_Flg;
extern volatile uint8_t get_temp_flag;
extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern PR_STATUS printerStaus;

static TEXT_Handle textPrintTemp1, textPrintTemp2,Fill_State_BK;

static PROGBAR_Handle printingBar;

static BUTTON_STRUCT buttonRecover, buttonStop, buttonExtruOut, buttonPreHeat, buttonMov, buttonmore_pause,buttonFan;



static void cbPauseWin(WM_MESSAGE * pMsg) {

	unsigned char buf[30] = {0};
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetColor(gCfgItems.state_background_color);
			GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(gCfgItems.state_background_color);
			GUI_FillRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			
			break;
		case WM_TOUCH:
		 		
			break;
		case WM_TOUCH_CHILD:
			
			break;
			
		case WM_NOTIFY_PARENT:
			if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
			{
				if(pMsg->hWinSrc == buttonStop.btnHandle)
				{
					last_disp_state = PAUSE_UI;
					Clear_pause();
				
					draw_dialog(DIALOG_TYPE_STOP);
					
				}
				else if(pMsg->hWinSrc == buttonRecover.btnHandle)
				{
					
					
					Get_Temperature_Flg = 1;
					get_temp_flag = 1;
					#if 0
					if(gCfgItems.sprayerNum == 2)
					{
						sprintf((char *)buf,"T%d\n",gCfgItems.curSprayerChoose);
						pushFIFO(&gcodeCmdTxFIFO, buf);
						memset(buf,0,sizeof(buf));
						strcpy((char *)buf, "G1 F1200\n");						
						pushFIFO(&gcodeCmdTxFIFO, buf);
					}
					else
					{
						memset(buf,0,sizeof(buf));
						strcpy((char *)buf, "G1 F1200\n");
						pushFIFO(&gcodeCmdTxFIFO, buf);
					}
					HAL_Delay(50);
					#endif
					if(printerStaus == pr_reprint)
					{
						last_disp_state = PAUSE_UI;
						Clear_pause();
						draw_return_ui();
						GUI_Exec();
						#ifdef SAVE_FROM_SD
						if(gCfgItems.pwroff_save_mode != 0)
						#endif
						{
							rePrintProcess();
						}
						#ifdef SAVE_FROM_SD
						else
						{
							if((RE_PRINT_STATUS)gCfgItems.rePrintFlag == printer_pwdwn_reprint)
							{
								rePrintProcess_pwrdwn();
							}
							else
							{
								rePrintProcess();
							}
						}
						#endif
						printerStaus = pr_working;
						start_print_time();
						MX_I2C1_Init(400000);//恢复打印，将速度改成400k
					}
					if(printerStaus == pr_pause)
					{
						MX_I2C1_Init(400000);
						start_print_time();
						////////	print_task_flag = TASK_GOING;
						last_disp_state = PAUSE_UI;
						printerStaus = pr_working;
						Clear_pause();
						//draw_printing();
						draw_return_ui();

					}
					
			
				}
				else if(pMsg->hWinSrc == buttonExtruOut.btnHandle)
				{
					last_disp_state = PAUSE_UI;
					Clear_pause();
					draw_extrusion();
				}
				else if(pMsg->hWinSrc == buttonMov.btnHandle)
				{
					last_disp_state = PAUSE_UI;
					Clear_pause();
					draw_move_motor();
				}
				else if(pMsg->hWinSrc == buttonFan.btnHandle)
				{
					last_disp_state = PAUSE_UI;
					Clear_pause();
					draw_fan();
				}
				else if(pMsg->hWinSrc == buttonmore_pause.btnHandle)
				{
					last_disp_state = PAUSE_UI;
					Clear_pause();
					draw_printmore();
				}	
				else if(pMsg->hWinSrc == buttonPreHeat.btnHandle)
				{
					last_disp_state = PAUSE_UI;
					Clear_pause();
					draw_preHeat();
				}
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
}

extern FILE_PRINT_STATE gCurFileState ;
void draw_pause()
{
		
//	int titleHeight = 30;

//	int imgHeight = LCD_HEIGHT - titleHeight;	
	//int8_t buf[50] = {0};
	int i;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != PAUSE_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = PAUSE_UI;
	}
	disp_state = PAUSE_UI;
//每个移动操作都已经设置了标志，所以不需要再设置了。
	//if(last_disp_state == MOVE_MOTOR_UI)
	//	positionSaveFlag = 1;
		
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
	//GUI_SetFont(&FONT_TITLE);
	/*if(gCfgItems.language == LANG_ENGLISH)
	{
		GUI_SetFont(&FONT_TITLE);
	}
	else
	{
		GUI_SetFont(&GUI_FontHZ16);
	}*/
        if(gCfgItems.language == LANG_COMPLEX_CHINESE)
	{
		GUI_SetFont(&GUI_FontHZ16);
	}
	else if(gCfgItems.language == LANG_SIMPLE_CHINESE)
	{
		GUI_SetFont(&GUI_FontHZ16);
	}
	else
	{
		GUI_SetFont(&GUI_FontHZ_fontHz18);
	}




	//sprintf(buf, "正在打印->操作->暂停:%s", curFileName);
	//GUI_DispStringAt(buf, 0, 0);
	GUI_DispStringAt(creat_title_text(),  X_ADD, X_INTERVAL);
	
	hPauseWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbPauseWin, 0);


	
	buttonRecover.btnHandle = BUTTON_CreateEx(X_ADD, 0,LCD_WIDTH / 4 - X_INTERVAL, imgHeight / 2 - X_INTERVAL, hPauseWnd, BUTTON_CF_SHOW, 0, 301);
	buttonStop.btnHandle = BUTTON_CreateEx(LCD_WIDTH  * 3 / 4+X_ADD,  0,LCD_WIDTH / 4 - X_INTERVAL, imgHeight / 2 - X_INTERVAL, hPauseWnd, BUTTON_CF_SHOW, 0, 302);
	buttonExtruOut.btnHandle = BUTTON_CreateEx(X_ADD,  imgHeight / 2,LCD_WIDTH / 4 - X_INTERVAL, imgHeight / 2 - X_INTERVAL, hPauseWnd, BUTTON_CF_SHOW, 0, 303);
	buttonMov.btnHandle = BUTTON_CreateEx(LCD_WIDTH / 4+X_ADD,  imgHeight / 2,LCD_WIDTH / 4 - X_INTERVAL, imgHeight / 2 - X_INTERVAL, hPauseWnd, BUTTON_CF_SHOW, 0, 304);
/*
	if(gCfgItems.print_finish_close_machine_flg == 1)
	{
		buttonPreHeat = BUTTON_CreateEx(LCD_WIDTH /2 , imgHeight / 2, LCD_WIDTH / 4 - 2, imgHeight / 2 - 1, hPauseWnd, BUTTON_CF_SHOW, 0, 305);
		buttonmore_pause = BUTTON_CreateEx(LCD_WIDTH * 3 / 4 , imgHeight / 2, LCD_WIDTH / 4 - 2, imgHeight / 2 - 1, hPauseWnd, BUTTON_CF_SHOW, 0, 306);
	}
	else
	{
		buttonFan = BUTTON_CreateEx(LCD_WIDTH /2 , imgHeight / 2, LCD_WIDTH / 4 - 2, imgHeight / 2 - 1, hPauseWnd, BUTTON_CF_SHOW, 0, 305);
		buttonPreHeat = BUTTON_CreateEx(LCD_WIDTH * 3 / 4 , imgHeight / 2, LCD_WIDTH / 4 - 2, imgHeight / 2 - 1, hPauseWnd, BUTTON_CF_SHOW, 0, 306);
	}
	*/
	
	buttonPreHeat.btnHandle = BUTTON_CreateEx(LCD_WIDTH / 2+X_ADD,  imgHeight / 2,LCD_WIDTH / 4 - X_INTERVAL, imgHeight / 2 - X_INTERVAL, hPauseWnd, BUTTON_CF_SHOW, 0, 305);
	buttonmore_pause.btnHandle = BUTTON_CreateEx(LCD_WIDTH * 3 / 4+X_ADD , imgHeight / 2, LCD_WIDTH / 4  - X_INTERVAL, imgHeight / 2  - X_INTERVAL, hPauseWnd, BUTTON_CF_SHOW, 0, 306);



	
	//TEXT_SetDefaultFont(&FONT_STATE_INF);

	#if VERSION_WITH_PIC	
	BUTTON_SetBmpFileName(buttonRecover.btnHandle, "bmp_resume.bin",1);
	BUTTON_SetBmpFileName(buttonStop.btnHandle, "bmp_stop.bin",1);
	BUTTON_SetBmpFileName(buttonExtruOut.btnHandle, "bmp_extruct.bin",1);
	BUTTON_SetBmpFileName(buttonMov.btnHandle, "bmp_mov.bin",1);
	
	BUTTON_SetBmpFileName(buttonmore_pause.btnHandle, "bmp_more.bin",1);
	BUTTON_SetBmpFileName(buttonPreHeat.btnHandle, "bmp_temp.bin",1); 

	/*
	if(gCfgItems.print_finish_close_machine_flg == 1)
	{
		BUTTON_SetBmpFileName(buttonmore_pause, "bmp_more.bin",0);
		BUTTON_SetBmpFileName(buttonPreHeat, "bmp_temp.bin",0);	
	}
	else
	{
		BUTTON_SetBmpFileName(buttonFan, "bmp_fan.bin",0);
		BUTTON_SetBmpFileName(buttonPreHeat, "bmp_temp.bin",0);
	}
	*/
	BUTTON_SetBitmapEx(buttonRecover.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonStop.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonExtruOut.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonMov.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	
	BUTTON_SetBitmapEx(buttonmore_pause.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonPreHeat.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);	


	BUTTON_SetBkColor(buttonRecover.btnHandle, BUTTON_CI_PRESSED, Pause_resume_bk_color);
	BUTTON_SetBkColor(buttonRecover.btnHandle, BUTTON_CI_UNPRESSED, Pause_resume_bk_color);
	
	BUTTON_SetBkColor(buttonStop.btnHandle, BUTTON_CI_PRESSED, Pause_stop_bk_color);
	BUTTON_SetBkColor(buttonStop.btnHandle, BUTTON_CI_UNPRESSED, Pause_stop_bk_color);

	BUTTON_SetBkColor(buttonExtruOut.btnHandle, BUTTON_CI_PRESSED, Pause_extrude_bk_color);
	BUTTON_SetBkColor(buttonExtruOut.btnHandle,BUTTON_CI_UNPRESSED, Pause_extrude_bk_color);

	BUTTON_SetBkColor(buttonMov.btnHandle, BUTTON_CI_PRESSED, Pause_move_bk_color);
	BUTTON_SetBkColor(buttonMov.btnHandle, BUTTON_CI_UNPRESSED, Pause_move_bk_color);

	BUTTON_SetBkColor(buttonmore_pause.btnHandle, BUTTON_CI_PRESSED, Pause_more_bk_color);
	BUTTON_SetBkColor(buttonmore_pause.btnHandle, BUTTON_CI_UNPRESSED, Pause_more_bk_color);

	BUTTON_SetBkColor(buttonPreHeat.btnHandle, BUTTON_CI_PRESSED, Pause_temperature_bk_color);
	BUTTON_SetBkColor(buttonPreHeat.btnHandle, BUTTON_CI_UNPRESSED, Pause_temperature_bk_color);
        
        BUTTON_SetDefaultTextAlign(GUI_TA_BOTTOM| GUI_TA_HCENTER);

	if(gCfgItems.language == LANG_ENGLISH){

		BUTTON_SetFont(buttonRecover.btnHandle,&GUI_FontHZ_fontHz18);	
		BUTTON_SetFont(buttonStop.btnHandle,&GUI_FontHZ_fontHz18);
		BUTTON_SetFont(buttonExtruOut.btnHandle,&GUI_FontHZ_fontHz18);	
		BUTTON_SetFont(buttonMov.btnHandle,&GUI_FontHZ_fontHz18);	
		BUTTON_SetFont(buttonmore_pause.btnHandle,&GUI_FontHZ_fontHz18);
		BUTTON_SetFont(buttonPreHeat.btnHandle,&GUI_FontHZ_fontHz18);
            
		BUTTON_SetText(buttonRecover.btnHandle, English_Resume);
		BUTTON_SetText(buttonStop.btnHandle, English_Stop);
		BUTTON_SetText(buttonExtruOut.btnHandle, English_Extrude);
		BUTTON_SetText(buttonMov.btnHandle, English_Move);
		BUTTON_SetText(buttonmore_pause.btnHandle, English_More);
		BUTTON_SetText(buttonPreHeat.btnHandle, English_Temperature);

	}
	else if(gCfgItems.language == LANG_COMPLEX_CHINESE){
          
		BUTTON_SetText(buttonRecover.btnHandle, Complex_Resume);
		BUTTON_SetText(buttonStop.btnHandle, Complex_Stop);
		BUTTON_SetText(buttonExtruOut.btnHandle, Complex_Extrude);
		BUTTON_SetText(buttonMov.btnHandle, Complex_Move);
		BUTTON_SetText(buttonmore_pause.btnHandle, Complex_More);
		BUTTON_SetText(buttonPreHeat.btnHandle, Complex_Temperature);
	
	}
	else if(gCfgItems.language == LANG_SIMPLE_CHINESE){

		BUTTON_SetText(buttonRecover.btnHandle, Simple_Resume);
		BUTTON_SetText(buttonStop.btnHandle, Simple_Stop);
		BUTTON_SetText(buttonExtruOut.btnHandle, Simple_Extrude);
		BUTTON_SetText(buttonMov.btnHandle, Simple_Move);
		BUTTON_SetText(buttonmore_pause.btnHandle, Simple_More);
		BUTTON_SetText(buttonPreHeat.btnHandle, Simple_Temperature);
		
	}
	/*
	if(gCfgItems.print_finish_close_machine_flg == 1)
	{
		BUTTON_SetBitmapEx(buttonmore_pause, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
		BUTTON_SetBitmapEx(buttonPreHeat, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);	
	}
	else
	{
		BUTTON_SetBitmapEx(buttonFan, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
		BUTTON_SetBitmapEx(buttonPreHeat, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	}
	*/
	#endif
	
	//TEXT_SetDefaultFont(&GUI_FontHZ_fontHz14);
	Fill_State_BK = TEXT_CreateEx(LCD_WIDTH  / 4+X_ADD, 0, LCD_WIDTH / 2-X_INTERVAL, imgHeight / 2-X_INTERVAL, hPauseWnd, WM_CF_SHOW, TEXT_CF_LEFT,	GUI_ID_TEXT0, " ");
	TEXT_SetBkColor(Fill_State_BK, gCfgItems.state_background_color);
	
	printingBar = PROGBAR_CreateEx(LCD_WIDTH  / 4 + 5, 40,  LCD_WIDTH / 2 - 10, 45, hPauseWnd, WM_CF_SHOW, 0, 0);

	//textPrintTemp1 = TEXT_CreateEx(LCD_WIDTH  / 4 + 50, 120, LCD_WIDTH / 4 - 60, 80, hPauseWnd, WM_CF_SHOW, TEXT_CF_LEFT,	GUI_ID_TEXT1, " ");

	//textPrintTemp2 = TEXT_CreateEx(LCD_WIDTH  / 2+ 50 , 120, LCD_WIDTH / 4 - 60, 80, hPauseWnd, WM_CF_SHOW, TEXT_CF_LEFT,	GUI_ID_TEXT2, " ");
	#if 1
	textPrintTemp1 = TEXT_CreateEx(LCD_WIDTH  / 4 + 50, 120, LCD_WIDTH / 4 - 30, 80, hPauseWnd, WM_CF_SHOW, TEXT_CF_LEFT,	GUI_ID_TEXT1, " ");

	textPrintTemp2 = TEXT_CreateEx(LCD_WIDTH  / 2+80 , 120, LCD_WIDTH / 4 - 90, 80, hPauseWnd, WM_CF_SHOW, TEXT_CF_LEFT,	GUI_ID_TEXT2, " ");

	TEXT_SetTextAlign(textPrintTemp1,  GUI_TA_VCENTER | GUI_TA_LEFT);
	TEXT_SetTextAlign(textPrintTemp2,  GUI_TA_VCENTER | GUI_TA_LEFT);
	#endif
	PROGBAR_SetBarColor(printingBar, 0, GUI_GREEN);
	
	PROGBAR_SetTextColor(printingBar, 0, GUI_BLACK);
	PROGBAR_SetFont(printingBar, &GUI_FontHZ_fontHz18);
	
	 if(((RE_PRINT_STATUS)gCfgItems.rePrintFlag == printer_pause_reprint) || ((RE_PRINT_STATUS)gCfgItems.rePrintFlag == printer_pwdwn_reprint)){
	 	PROGBAR_SetValue(printingBar,gCurFileState.totalSend);
	 }
	 else{
	 	PROGBAR_SetValue(printingBar, get_printing_rate(srcfp));
	 }
	
	
	
	disp_temp_pause();
	
	//GUI_Exec();


	
}

void setProBarRatePause()
{
  //int rate = (long long)(sd.sdpos * 100) / sd.filesize;
    int rate;
  	volatile long long rate_tmp_pa;
	rate_tmp_pa = (long long)sd.sdpos * 100;
    rate = rate_tmp_pa / sd.filesize;
	
	if(rate <= 0)
		return;
	
	
	if(disp_state == PAUSE_UI)
	{
		PROGBAR_SetValue(printingBar, rate );
	}
	
}

void disp_temp_pause()
{
	char buf[50] = {0};
	
	TEXT_SetTextColor(textPrintTemp1, gCfgItems.state_text_color);
	TEXT_SetTextColor(textPrintTemp2, gCfgItems.state_text_color);
	//GUI_SetFont(&FONT_STATE_INF);
	TEXT_SetBkColor(textPrintTemp1, gCfgItems.state_background_color);
	TEXT_SetBkColor(textPrintTemp2, gCfgItems.state_background_color);

	TEXT_SetFont(textPrintTemp1,&GUI_FontHZ_fontHz18);
	TEXT_SetFont(textPrintTemp2,&GUI_FontHZ_fontHz18);
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
		if(gCfgItems.custom_bed_flag == 1)
		{
			sprintf(buf, " E1:%d\n B:%d", (int)gCfgItems.curSprayerTemp[0], (int)gCfgItems.curBedTemp);
			TEXT_SetText(textPrintTemp1, buf);
		}
		else
		{
			sprintf(buf, " E1:%d\n", (int)gCfgItems.curSprayerTemp[0]);
			TEXT_SetText(textPrintTemp1, buf);			
		}
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "E2:%d\nFAN:%d", (int)gCfgItems.curSprayerTemp[1],gCfgItems.fanSpeed);
		TEXT_SetText(textPrintTemp2, buf);
		
	}
	else
	{
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

void Clear_pause()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hPauseWnd))
	{
		WM_DeleteWindow(hPauseWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}


