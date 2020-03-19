#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_zoffset.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"
#include "text.h"
#include "mks_cfg.h"
#include "mks_tft_fifo.h"
#include "mks_tft_com.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

GUI_HWIN hZoffsetWnd;
static TEXT_Handle textZoffset,textZoffsetValue;

extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern TFT_FIFO gcodeCmdTxFIFO;		//gcode 指令发送队列
extern TFT_FIFO gcodeCmdRxFIFO;		//gcode	指令接收队列

static BUTTON_STRUCT buttonInc, buttonDec, buttonStep01, buttonStep05, buttonStep1, buttonRet;

static void cbZoffsetWin(WM_MESSAGE * pMsg) {
	char  buf[50] = {0};
	
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetColor(gCfgItems.state_background_color);
			GUI_FillRect(BTN_X_PIXEL+INTERVAL_V*2, 0, BTN_X_PIXEL *3+INTERVAL_V*3-1, BTN_Y_PIXEL-1);

			break;
		case WM_TOUCH:
		 	
			break;
		case WM_TOUCH_CHILD:
			
			break;
		case WM_NOTIFY_PARENT:
			if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
			{
				if(pMsg->hWinSrc == buttonStep01.btnHandle)
				{
					gCfgItems.stepZoffset=0.01;
					disp_step_zoffset();					
				}
				else if(pMsg->hWinSrc == buttonStep05.btnHandle)
				{
					gCfgItems.stepZoffset=0.1;
					disp_step_zoffset();

				}
				else if(pMsg->hWinSrc == buttonStep1.btnHandle)
				{
					gCfgItems.stepZoffset=1;
					disp_step_zoffset();					
				}				
				else if(pMsg->hWinSrc == buttonInc.btnHandle)
				{
					gCfgItems.Zoffset += gCfgItems.stepZoffset;
					if((gCfgItems.Zoffset>(-0.001))&&(gCfgItems.Zoffset<0.001))
						gCfgItems.Zoffset = 0;
					if(gCfgItems.firmware_type == 1)
						sprintf(buf, "M851 Z%.2f\n", gCfgItems.Zoffset);
					else
						sprintf(buf, "M565 Z%.2f\n", gCfgItems.Zoffset);						
					pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);
					memset(buf,0,sizeof(buf));
					sprintf(buf, "M500\n");
					pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);

					disp_zoffset();
				}
				else if(pMsg->hWinSrc == buttonDec.btnHandle)
				{
					gCfgItems.Zoffset -= gCfgItems.stepZoffset;
					if((gCfgItems.Zoffset>(-0.001))&&(gCfgItems.Zoffset<0.001))
						gCfgItems.Zoffset = 0;
					
					if(gCfgItems.firmware_type == 1)
						sprintf(buf, "M851 Z%.2f\n", gCfgItems.Zoffset);
					else
						sprintf(buf, "M565 Z%.2f\n", gCfgItems.Zoffset);						
					pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);
					memset(buf,0,sizeof(buf));
					sprintf(buf, "M500\n");
					pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);	

					disp_zoffset();
				}
				else  if(pMsg->hWinSrc == buttonRet.btnHandle)
				{
					last_disp_state = ZOFFSET_UI;
					Clear_Zoffset();
					draw_return_ui();
					
				}
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
	}


void draw_Zoffset()
{
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != ZOFFSET_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = ZOFFSET_UI;
	}
	disp_state = ZOFFSET_UI;

	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();

	GUI_DispStringAt(creat_title_text(),  TITLE_XPOS, TITLE_YPOS);	
	
	
	hZoffsetWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbZoffsetWin, 0);
	buttonInc.btnHandle = BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL, hZoffsetWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonDec.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hZoffsetWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	
	buttonStep01.btnHandle = BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hZoffsetWnd, BUTTON_CF_SHOW, 0, 303);
	buttonStep05.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hZoffsetWnd, BUTTON_CF_SHOW, 0, 304);
	buttonStep1.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hZoffsetWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hZoffsetWnd, BUTTON_CF_SHOW, 0, 306);

	#if VERSION_WITH_PIC	
	BUTTON_SetBmpFileName(buttonInc.btnHandle, "bmp_Add.bin",1);
	BUTTON_SetBmpFileName(buttonDec.btnHandle, "bmp_Dec.bin",1);
	
	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);

	BUTTON_SetBitmapEx(buttonInc.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonDec.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);

	BUTTON_SetBkColor(buttonInc.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonInc.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color	);
	BUTTON_SetTextColor(buttonInc.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonInc.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	
	BUTTON_SetBkColor(buttonDec.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonDec.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonDec.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonDec.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);

	if(gCfgItems.multiple_language != 0)
	{
		BUTTON_SetText(buttonInc.btnHandle, zoffset_menu.inc);
		BUTTON_SetText(buttonDec.btnHandle, zoffset_menu.dec);
		BUTTON_SetText(buttonRet.btnHandle, common_menu.text_back);
	}

	#endif
	
	textZoffset = TEXT_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,(BTN_Y_PIXEL-60)/2,BTN_X_PIXEL*2+INTERVAL_V,30, hZoffsetWnd, WM_CF_SHOW, TEXT_CF_HCENTER,	GUI_ID_TEXT1, "Extruder1");
	textZoffsetValue = TEXT_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,(BTN_Y_PIXEL-60)/2+30, BTN_X_PIXEL*2+INTERVAL_V,30, hZoffsetWnd, WM_CF_SHOW, TEXT_CF_HCENTER,	GUI_ID_TEXT1, "0/0");

	TEXT_SetBkColor(textZoffset,gCfgItems.state_background_color);
	TEXT_SetBkColor(textZoffsetValue,gCfgItems.state_background_color); 
	TEXT_SetTextColor(textZoffset,gCfgItems.state_text_color);
	TEXT_SetTextColor(textZoffsetValue,gCfgItems.state_text_color);

	disp_step_zoffset();
	disp_zoffset();
	//GUI_Exec();


	
}

void Clear_Zoffset()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hZoffsetWnd))
	{
		WM_DeleteWindow(hZoffsetWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}


void disp_step_zoffset()
{




	if(gCfgItems.stepZoffset*100 == 1)
	{
		BUTTON_SetBkColor(buttonStep01.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_color);
		BUTTON_SetBkColor(buttonStep01.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_color);
		BUTTON_SetTextColor(buttonStep01.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_textcolor);
		BUTTON_SetTextColor(buttonStep01.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_textcolor);
		BUTTON_SetBkColor(buttonStep05.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
		BUTTON_SetBkColor(buttonStep05.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
		BUTTON_SetTextColor(buttonStep05.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
		BUTTON_SetTextColor(buttonStep05.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);
		BUTTON_SetBkColor(buttonStep1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
		BUTTON_SetBkColor(buttonStep1.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
		BUTTON_SetTextColor(buttonStep1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
		BUTTON_SetTextColor(buttonStep1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);
	
		BUTTON_SetBmpFileName(buttonStep01.btnHandle, "bmp_step001_zoffset_sel.bin",1);
		BUTTON_SetBmpFileName(buttonStep05.btnHandle, "bmp_step01_zoffset.bin",1);
		BUTTON_SetBmpFileName(buttonStep1.btnHandle, "bmp_step1_zoffset.bin",1);
	}
	else if(gCfgItems.stepZoffset*100 == 10)
	{
		BUTTON_SetBkColor(buttonStep01.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
		BUTTON_SetBkColor(buttonStep01.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
		BUTTON_SetTextColor(buttonStep01.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
		BUTTON_SetTextColor(buttonStep01.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);
		BUTTON_SetBkColor(buttonStep05.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_color);
		BUTTON_SetBkColor(buttonStep05.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_color);
		BUTTON_SetTextColor(buttonStep05.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_textcolor);
		BUTTON_SetTextColor(buttonStep05.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_textcolor);
		BUTTON_SetBkColor(buttonStep1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
		BUTTON_SetBkColor(buttonStep1.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
		BUTTON_SetTextColor(buttonStep1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
		BUTTON_SetTextColor(buttonStep1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);
		
		BUTTON_SetBmpFileName(buttonStep01.btnHandle, "bmp_step001_zoffset.bin",1);
		BUTTON_SetBmpFileName(buttonStep05.btnHandle, "bmp_step01_zoffset_sel.bin",1);
		BUTTON_SetBmpFileName(buttonStep1.btnHandle, "bmp_step1_zoffset.bin",1);

	}
	else if(gCfgItems.stepZoffset*100 == 100)
	{
		BUTTON_SetBkColor(buttonStep01.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
		BUTTON_SetBkColor(buttonStep01.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
		BUTTON_SetTextColor(buttonStep01.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
		BUTTON_SetTextColor(buttonStep01.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);
		BUTTON_SetBkColor(buttonStep05.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
		BUTTON_SetBkColor(buttonStep05.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
		BUTTON_SetTextColor(buttonStep05.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
		BUTTON_SetTextColor(buttonStep05.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);		
		BUTTON_SetBkColor(buttonStep1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_color);
		BUTTON_SetBkColor(buttonStep1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_color);
		BUTTON_SetTextColor(buttonStep1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_textcolor);
		BUTTON_SetTextColor(buttonStep1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_textcolor);
		
		BUTTON_SetBmpFileName(buttonStep01.btnHandle, "bmp_step001_zoffset.bin",1);
		BUTTON_SetBmpFileName(buttonStep05.btnHandle, "bmp_step01_zoffset.bin",1);
		BUTTON_SetBmpFileName(buttonStep1.btnHandle, "bmp_step1_zoffset_sel.bin",1);

	}
	BUTTON_SetBitmapEx(buttonStep01.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonStep05.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonStep1.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);

	if(gCfgItems.multiple_language != 0)
	{

		BUTTON_SetText(buttonStep01.btnHandle,zoffset_menu.step001);	
		BUTTON_SetText(buttonStep05.btnHandle,zoffset_menu.step01);
		BUTTON_SetText(buttonStep1.btnHandle,zoffset_menu.step1);	

	}	
}

void disp_zoffset()
{
	char buf[20] = {0};
	char buf1[20] = {0};
	
	TEXT_SetBkColor(textZoffset,gCfgItems.state_background_color);
	TEXT_SetBkColor(textZoffsetValue,gCfgItems.state_background_color); 
	TEXT_SetTextColor(textZoffset,gCfgItems.state_text_color);
	TEXT_SetTextColor(textZoffsetValue,gCfgItems.state_text_color);
	
	sprintf(buf1,"z offset");
	sprintf(buf, "%.2f",gCfgItems.Zoffset);


	TEXT_SetText(textZoffset, buf1);
	TEXT_SetText(textZoffsetValue, buf);
}

