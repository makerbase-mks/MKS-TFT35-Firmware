#include "draw_more.h"
#include "gui.h"
#include "button.h"
#include "draw_ui.h"
//#include "printer.h"
#include "fontLib.h"
//#include "gcode.h"
#include "stdint.h"
#include "pic_manager.h"
#include "spi_flash.h"
#include "mks_tft_fifo.h"
#include "draw_zoffset.h"
#include "touch_calibrate.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static BUTTON_STRUCT buttonzoffset,buttonCalibrate,buttonCustom1, buttonCustom2, buttonCustom3, buttonCustom4, buttonCustom5, buttonCustom6, buttonCustom7,  buttonRet;
GUI_HWIN hMoreWnd;

extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern TFT_FIFO gcodeCmdTxFIFO;		//gcode 指令发送队列
extern TFT_FIFO gcodeCmdRxFIFO;		//gcode	指令接收队列

/*
extern char cmd1_code[200];
extern char cmd2_code[200];
extern char cmd3_code[200];
extern char cmd4_code[200];
extern char cmd5_code[200];
extern char cmd6_code[200];
extern char cmd7_code[200];
*/
extern char cmd_code[201];

/*
unsigned char codebuff[100];
unsigned char x[1]={0};
volatile unsigned char *codebufpoint = x;
*/
unsigned char codebuff[100];              //**
char x[1]={0};
volatile char *codebufpoint = x;
extern int X_ADD,X_INTERVAL;   //**图片间隔


//void pushButtonCodeToFifo(uint8_t *buttoncode)
void pushButtonCodeToFifo(void)
{
	uint8_t i = 0,j;
#if 1	
	while(*(codebufpoint) != '\0')
	{
		memset(codebuff,0,sizeof(codebuff));
		
		while((*(codebufpoint) != 0x3b)&&(i<96))//命令行以分号为结束符。
		{
			codebuff[i] = *codebufpoint;
			i++;
			codebufpoint++;
		}
		
		codebuff[i] = '\n';
		
		codebufpoint += 1;		
		if(checkFIFO(&gcodeCmdTxFIFO) != fifo_full)
		{
			pushFIFO(&gcodeCmdTxFIFO, codebuff);
		}
		else
		{
			codebufpoint = codebufpoint - i - 1;
			break;
		}
		i = 0;
	}
#endif
	
}
static void cbMoreWin(WM_MESSAGE * pMsg) {

	//unsigned char codebuff[100];
	uint8_t *codebuffpointer;
	unsigned char i = 0,j = 0;
	
	struct PressEvt *press_event;
	//char buf[30] = {0};

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

		
			if(pMsg->hWinSrc == buttonCustom1.btnHandle)
			{
				SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD1_ADDR,201);
				codebufpoint = cmd_code;
			}
			else if(pMsg->hWinSrc == buttonCustom2.btnHandle)
			{
				SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD2_ADDR,201);
				codebufpoint = cmd_code;

			}
			else if(pMsg->hWinSrc == buttonCustom3.btnHandle)
			{
				SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD3_ADDR,201);
				codebufpoint = cmd_code;				
			}
			else if(pMsg->hWinSrc == buttonCustom4.btnHandle)
			{
				SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD4_ADDR,201);
				codebufpoint = cmd_code;

			}
			else if(pMsg->hWinSrc == buttonCustom5.btnHandle)
			{
				SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD5_ADDR,201);
				codebufpoint = cmd_code;

			}
			else if(pMsg->hWinSrc == buttonCustom6.btnHandle)
			{
				SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD6_ADDR,201);
				codebufpoint = cmd_code;

			}
			else if(pMsg->hWinSrc == buttonzoffset.btnHandle)
			{
				last_disp_state = MORE_UI;
				Clear_more();
				draw_Zoffset();

			}			
			else if(pMsg->hWinSrc == buttonRet.btnHandle)
			{
				last_disp_state = MORE_UI;
				Clear_more();
				draw_return_ui();		
			}
			else if(pMsg->hWinSrc == buttonCalibrate.btnHandle)
			{
				last_disp_state = MORE_UI;
				Clear_more();
				draw_calibrate();	
			}

		}
		break;
	default:
	WM_DefaultProc(pMsg);
	}
}


void draw_More()
{
if(disp_state_stack._disp_state[disp_state_stack._disp_index] != MORE_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = MORE_UI;
	}
	disp_state = MORE_UI;
	
	//GUI_SetFont(&GUI_Font8x18);
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
	#if 0
	//GUI_SetFont(&FONT_TITLE);
	if(gCfgItems.language == LANG_COMPLEX_CHINESE)
	{
		GUI_SetFont(&GUI_FontHZ16);
	}
	else if(gCfgItems.language == LANG_SIMPLE_CHINESE)
	{
		GUI_SetFont(&FONT_TITLE);
	}
	else
	{
		GUI_SetFont(&GUI_FontHZ_fontHz18);
	}
#endif

	GUI_DispStringAt(creat_title_text(),  TITLE_XPOS, TITLE_YPOS);
	

	hMoreWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbMoreWin, 0);
	if(gCfgItems.zoffset_display_flg == 1)
	{
		buttonzoffset.btnHandle= BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 101);
		BUTTON_SetBmpFileName(buttonzoffset.btnHandle, "bmp_zoffset.bin",1);
		BUTTON_SetBkColor(buttonzoffset.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
		BUTTON_SetBkColor(buttonzoffset.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(buttonzoffset.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
		BUTTON_SetTextColor(buttonzoffset.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);	
		BUTTON_SetBitmapEx(buttonzoffset.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
		if(gCfgItems.calibrate_disp_flag ==1)
		{
			buttonCalibrate.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2, 0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 101);
			BUTTON_SetBmpFileName(buttonCalibrate.btnHandle, "bmp_calibrate.bin",1);
			BUTTON_SetBkColor(buttonCalibrate.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
			BUTTON_SetBkColor(buttonCalibrate.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
			BUTTON_SetTextColor(buttonCalibrate.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
			BUTTON_SetTextColor(buttonCalibrate.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);	
			BUTTON_SetBitmapEx(buttonCalibrate.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
			if(gCfgItems.MoreItem_pic_cnt > 5)
			gCfgItems.MoreItem_pic_cnt = 5;
		
			switch(gCfgItems.MoreItem_pic_cnt)
			{
				case 5:
				   buttonCustom5.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 107);
				   BUTTON_SetBmpFileName(buttonCustom5.btnHandle, "bmp_custom5.bin",1);
				   BUTTON_SetBkColor(buttonCustom5.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom5.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom5.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 4:
				   buttonCustom4.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 106);
				   BUTTON_SetBmpFileName(buttonCustom4.btnHandle, "bmp_custom4.bin",1);
				   BUTTON_SetBkColor(buttonCustom4.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom4.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom4.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 3:
				   buttonCustom3.btnHandle= BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 105);
				   BUTTON_SetBmpFileName(buttonCustom3.btnHandle, "bmp_custom3.bin",1);
				   BUTTON_SetBkColor(buttonCustom3.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom3.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom3.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 2:
				   buttonCustom2.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 108);
				   BUTTON_SetBmpFileName(buttonCustom2.btnHandle, "bmp_custom2.bin",1);
				   BUTTON_SetBkColor(buttonCustom2.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom2.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom2.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 1:
				   buttonCustom1.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 103);
				   BUTTON_SetBmpFileName(buttonCustom1.btnHandle, "bmp_custom1.bin",1);
				   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom1.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				//case 1:
				//   buttonCustom1.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 102); 	   
				//   BUTTON_SetBmpFileName(buttonCustom1.btnHandle, "bmp_custom1.bin",1);
				//   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				//   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				//   BUTTON_SetBitmapEx(buttonCustom1.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				//case 1:
				//   buttonCustom1.btnHandle= BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 101);
				//   BUTTON_SetBmpFileName(buttonCustom1.btnHandle, "bmp_custom1.bin",1);
				//   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				//   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				//   BUTTON_SetBitmapEx(buttonCustom1.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				break;
				default:break;
			}
		}
		else
		{
			if(gCfgItems.MoreItem_pic_cnt > 6)
			gCfgItems.MoreItem_pic_cnt = 6;
		
			switch(gCfgItems.MoreItem_pic_cnt)
			{
				case 6:
				   buttonCustom6.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 107);
				   BUTTON_SetBmpFileName(buttonCustom6.btnHandle, "bmp_custom6.bin",1);
				   BUTTON_SetBkColor(buttonCustom6.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom6.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom6.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 5:
				   buttonCustom5.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 106);
				   BUTTON_SetBmpFileName(buttonCustom5.btnHandle, "bmp_custom5.bin",1);
				   BUTTON_SetBkColor(buttonCustom5.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom5.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom5.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 4:
				   buttonCustom4.btnHandle= BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 105);
				   BUTTON_SetBmpFileName(buttonCustom4.btnHandle, "bmp_custom4.bin",1);
				   BUTTON_SetBkColor(buttonCustom4.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom4.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom4.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 3:
				   buttonCustom3.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 108);
				   BUTTON_SetBmpFileName(buttonCustom3.btnHandle, "bmp_custom3.bin",1);
				   BUTTON_SetBkColor(buttonCustom3.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom3.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom3.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 2:
				   buttonCustom2.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 103);
				   BUTTON_SetBmpFileName(buttonCustom2.btnHandle, "bmp_custom2.bin",1);
				   BUTTON_SetBkColor(buttonCustom2.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom2.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom2.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 1:
				   buttonCustom1.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 102); 	   
				   BUTTON_SetBmpFileName(buttonCustom1.btnHandle, "bmp_custom1.bin",1);
				   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom1.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				//case 1:
				//   buttonCustom1.btnHandle= BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 101);
				//   BUTTON_SetBmpFileName(buttonCustom1.btnHandle, "bmp_custom1.bin",1);
				//   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				//   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				//   BUTTON_SetBitmapEx(buttonCustom1.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				break;
				default:break;
			}
		}
		
	}
	else
	{
		if(gCfgItems.calibrate_disp_flag ==1)
		{
			buttonCalibrate.btnHandle= BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 101);
			BUTTON_SetBmpFileName(buttonCalibrate.btnHandle, "bmp_calibrate.bin",1);
			BUTTON_SetBkColor(buttonCalibrate.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
			BUTTON_SetBkColor(buttonCalibrate.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
			BUTTON_SetTextColor(buttonCalibrate.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
			BUTTON_SetTextColor(buttonCalibrate.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);	
			BUTTON_SetBitmapEx(buttonCalibrate.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
			if(gCfgItems.MoreItem_pic_cnt > 6)
			gCfgItems.MoreItem_pic_cnt = 6;
		
			switch(gCfgItems.MoreItem_pic_cnt)
			{
				case 6:
				   buttonCustom6.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 107);
				   BUTTON_SetBmpFileName(buttonCustom6.btnHandle, "bmp_custom6.bin",1);
				   BUTTON_SetBkColor(buttonCustom6.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom6.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom6.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 5:
				   buttonCustom5.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 106);
				   BUTTON_SetBmpFileName(buttonCustom5.btnHandle, "bmp_custom5.bin",1);
				   BUTTON_SetBkColor(buttonCustom5.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom5.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom5.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 4:
				   buttonCustom4.btnHandle= BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 105);
				   BUTTON_SetBmpFileName(buttonCustom4.btnHandle, "bmp_custom4.bin",1);
				   BUTTON_SetBkColor(buttonCustom4.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom4.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom4.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 3:
				   buttonCustom3.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 108);
				   BUTTON_SetBmpFileName(buttonCustom3.btnHandle, "bmp_custom3.bin",1);
				   BUTTON_SetBkColor(buttonCustom3.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom3.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom3.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 2:
				   buttonCustom2.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 103);
				   BUTTON_SetBmpFileName(buttonCustom2.btnHandle, "bmp_custom2.bin",1);
				   BUTTON_SetBkColor(buttonCustom2.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom2.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom2.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 1:
				   buttonCustom1.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 102); 	   
				   BUTTON_SetBmpFileName(buttonCustom1.btnHandle, "bmp_custom1.bin",1);
				   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom1.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				//case 1:
				//   buttonCustom1.btnHandle= BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 101);
				//   BUTTON_SetBmpFileName(buttonCustom1.btnHandle, "bmp_custom1.bin",1);
				//   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				//   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				//   BUTTON_SetBitmapEx(buttonCustom1.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				break;
				default:break;
			 
			}
		}
		else
		{
			if(gCfgItems.MoreItem_pic_cnt > 7)
			gCfgItems.MoreItem_pic_cnt = 7;
		
			switch(gCfgItems.MoreItem_pic_cnt)
			{
				case 7:
				   buttonCustom7.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 107);
				   BUTTON_SetBmpFileName(buttonCustom7.btnHandle, "bmp_custom7.bin",1);
				   BUTTON_SetBkColor(buttonCustom7.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom7.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom7.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 6:
				   buttonCustom6.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 106);
				   BUTTON_SetBmpFileName(buttonCustom6.btnHandle, "bmp_custom6.bin",1);
				   BUTTON_SetBkColor(buttonCustom6.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom6.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom6.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 5:
				   buttonCustom5.btnHandle= BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 105);
				   BUTTON_SetBmpFileName(buttonCustom5.btnHandle, "bmp_custom5.bin",1);
				   BUTTON_SetBkColor(buttonCustom5.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom5.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom5.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 4:
				   buttonCustom4.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 108);
				   BUTTON_SetBmpFileName(buttonCustom4.btnHandle, "bmp_custom4.bin",1);
				   BUTTON_SetBkColor(buttonCustom4.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom4.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom4.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 3:
				   buttonCustom3.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 103);
				   BUTTON_SetBmpFileName(buttonCustom3.btnHandle, "bmp_custom3.bin",1);
				   BUTTON_SetBkColor(buttonCustom3.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom3.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom3.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 2:
				   buttonCustom2.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 102); 	   
				   BUTTON_SetBmpFileName(buttonCustom2.btnHandle, "bmp_custom2.bin",1);
				   BUTTON_SetBkColor(buttonCustom2.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom2.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom2.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				case 1:
				   buttonCustom1.btnHandle= BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 101);
				   BUTTON_SetBmpFileName(buttonCustom1.btnHandle, "bmp_custom1.bin",1);
				   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBkColor(buttonCustom1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
				   BUTTON_SetBitmapEx(buttonCustom1.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
				break;
				default:break;
			 
			}
		}
				
	}
	buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hMoreWnd, BUTTON_CF_SHOW, 0, 109);
	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
	BUTTON_SetBkColor(buttonRet.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
	BUTTON_SetTextColor(buttonRet.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);

	if(gCfgItems.multiple_language != 0)
	{
		if(gCfgItems.zoffset_display_flg == 1)
		{
			BUTTON_SetText(buttonzoffset.btnHandle, more_menu.zoffset);
		}
		if(gCfgItems.calibrate_disp_flag == 1)
		{
			BUTTON_SetText(buttonCalibrate.btnHandle, more_menu.calibrate);
		}
		BUTTON_SetText(buttonRet.btnHandle, common_menu.text_back);
	}
	

	//GUI_Exec();

	
}

void Clear_more()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hMoreWnd))
	{
		WM_DeleteWindow(hMoreWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}


