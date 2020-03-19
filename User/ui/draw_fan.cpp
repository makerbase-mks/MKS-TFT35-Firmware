#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_fan.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"
#include "text.h"
#include "mks_tft_fifo.h"
#include "mks_tft_com.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

GUI_HWIN hFanWnd;
static TEXT_Handle TextFanSpeed,TextFanValue;

extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern TFT_FIFO gcodeCmdTxFIFO;		//gcode 指令发送队列
extern TFT_FIFO gcodeCmdRxFIFO;		//gcode	指令接收队列
extern int X_ADD,X_INTERVAL;   //**图片间隔

static BUTTON_STRUCT buttonAdd, buttonDec, buttonOpen, buttonHalf, buttonOff,  buttonRet;

static void cbFanWin(WM_MESSAGE * pMsg) {

	uint8_t buf[30] = {0};

	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			//#if defined(TFT70)
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(gCfgItems.state_background_color);
			GUI_FillRect(BTN_X_PIXEL+INTERVAL_V*2, 0, BTN_X_PIXEL *3+INTERVAL_V*3-1, BTN_Y_PIXEL-1);;
			//#elif defined(TFT35)
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_FillRect(BTN_X_PIXEL+INTERVAL_V*2, 0, BTN_X_PIXEL *3+5, BTN_Y_PIXEL);
			//#endif
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
										
					//**last_disp_state = FAN_UI;
					//**Clear_fan();
					//**draw_return_ui();
					#if 0
					if(gCfgItems.print_finish_close_machine_flg == 1)
						{
							
							if(printerStaus != pr_idle)
							{
								disp_state_stack._disp_index -= 1;
								Clear_fan();
								draw_return_ui();
							}
							else
							{
								Clear_fan();
								draw_return_ui();
							}
								
						}
						else
					#endif
						{
							last_disp_state = FAN_UI;
							Clear_fan();
							draw_return_ui();
						}
				}
				else if(pMsg->hWinSrc == buttonOpen.btnHandle)
				{					
					//**push_cb_stack(UI_ACTION_FAN_FULL);
					if(last_disp_state == PRINT_READY_UI)
					{
						gCfgItems.fanOnoff = 1;
						gCfgItems.pre_fanSpeed = 255;
						SET_FAN_SPEED_COMMAND((char *)buf, gCfgItems.pre_fanSpeed);
						pushFIFO(&gcodeCmdTxFIFO, buf);
					}
					else
					{
						gCfgItems.fanOnoff = 1;
						gCfgItems.fanSpeed = 255;
						SET_FAN_SPEED_COMMAND((char *)buf, gCfgItems.fanSpeed);
						pushFIFO(&gcodeCmdTxFIFO, buf);			
					}
					disp_fan_speed();
				}
				else if(pMsg->hWinSrc == buttonOff.btnHandle)
				{					
					//**push_cb_stack(UI_ACTION_FAN_OFF);
					if(last_disp_state == PRINT_READY_UI)
					{
						gCfgItems.fanOnoff = 0;
						gCfgItems.pre_fanSpeed = 0;
						pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)SET_FAN_OFF_COMMAND);
					}
					else
					{
						gCfgItems.fanOnoff = 0;
						gCfgItems.fanSpeed = 0;
						pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)SET_FAN_OFF_COMMAND);
					}					
					disp_fan_speed();
				}
				else if(pMsg->hWinSrc == buttonHalf.btnHandle)
				{
										
					//**push_cb_stack(UI_ACTION_FAN_50);
					//last_disp_state = FAN_UI;
					if(last_disp_state == PRINT_READY_UI)
					{
						gCfgItems.fanOnoff = 1;
						gCfgItems.pre_fanSpeed = 127;
						SET_FAN_SPEED_COMMAND((char *)buf, gCfgItems.pre_fanSpeed);
						pushFIFO(&gcodeCmdTxFIFO, buf);
					}
					else
					{
						gCfgItems.fanOnoff = 1;
						gCfgItems.fanSpeed = 127;
						SET_FAN_SPEED_COMMAND((char *)buf, gCfgItems.fanSpeed);
						pushFIFO(&gcodeCmdTxFIFO, buf);					
					}
					disp_fan_speed();

				}
				else if(pMsg->hWinSrc == buttonAdd.btnHandle)
				{										
					//**push_cb_stack(UI_ACTION_FAN_UP);
					if(last_disp_state ==PRINT_READY_UI)
					{
						if(gCfgItems.pre_fanSpeed < 255)
						{
							gCfgItems.fanOnoff = 1;
							gCfgItems.pre_fanSpeed++;
							SET_FAN_SPEED_COMMAND((char *)buf, gCfgItems.pre_fanSpeed);
							pushFIFO(&gcodeCmdTxFIFO, buf);
						}
					}
					else
					{
						if(gCfgItems.fanSpeed < 255)
						{
							gCfgItems.fanOnoff = 1;
							gCfgItems.fanSpeed++;
							SET_FAN_SPEED_COMMAND((char *)buf, gCfgItems.fanSpeed);
							pushFIFO(&gcodeCmdTxFIFO, buf);		
						}
					}
					disp_fan_speed();
				}
				else if(pMsg->hWinSrc == buttonDec.btnHandle)
				{					
					//**push_cb_stack(UI_ACTION_FAN_DOWN);
					if(last_disp_state ==PRINT_READY_UI)
					{
						if(gCfgItems.pre_fanSpeed > 0)
						{
							gCfgItems.pre_fanSpeed--;
							SET_FAN_SPEED_COMMAND((char *)buf, gCfgItems.pre_fanSpeed);						
							pushFIFO(&gcodeCmdTxFIFO, buf);
						}
					}
					else
					{
						if(gCfgItems.fanSpeed > 0)
						{
							gCfgItems.fanSpeed--;
							SET_FAN_SPEED_COMMAND((char *)buf, gCfgItems.fanSpeed);						
							pushFIFO(&gcodeCmdTxFIFO, buf);
						}				
					}
					disp_fan_speed();
				}
			}
			
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
	}


void draw_fan()
{
	int i;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != FAN_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = FAN_UI;
	}
	disp_state = FAN_UI;
		
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();

	GUI_DispStringAt(creat_title_text(),  TITLE_XPOS, TITLE_YPOS);
	
	hFanWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbFanWin, 0);

	buttonAdd.btnHandle = BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL, hFanWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonDec.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hFanWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonOpen.btnHandle = BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H, BTN_X_PIXEL,BTN_Y_PIXEL, hFanWnd, BUTTON_CF_SHOW, 0, 303);
	buttonHalf.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hFanWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonOff.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hFanWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hFanWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	TextFanSpeed = TEXT_CreateEx(BTN_X_PIXEL+INTERVAL_V*2, (BTN_Y_PIXEL-60)/2, BTN_X_PIXEL*2+INTERVAL_V,30, hFanWnd, WM_CF_SHOW, TEXT_CF_HCENTER,	GUI_ID_TEXT1, "喷头温度");
	TextFanValue = TEXT_CreateEx(BTN_X_PIXEL+INTERVAL_V*2, (BTN_Y_PIXEL-60)/2+30, BTN_X_PIXEL*2+INTERVAL_V,30, hFanWnd, WM_CF_SHOW, TEXT_CF_HCENTER,	GUI_ID_TEXT1, "喷头温度");
	
	BUTTON_SetBmpFileName(buttonAdd.btnHandle, "bmp_Add.bin",1);	
	BUTTON_SetBmpFileName(buttonDec.btnHandle, "bmp_Dec.bin",1);	
	BUTTON_SetBmpFileName(buttonOpen.btnHandle, "bmp_speed255.bin",1);	
	BUTTON_SetBmpFileName(buttonHalf.btnHandle, "bmp_speed127.bin",1);	
	BUTTON_SetBmpFileName(buttonOff.btnHandle, "bmp_speed0.bin",1);	
	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);	
	
	BUTTON_SetBitmapEx(buttonAdd.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonDec.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonOpen.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonHalf.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonOff.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);

	BUTTON_SetBkColor(buttonAdd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonAdd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonAdd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonAdd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	
	BUTTON_SetBkColor(buttonDec.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonDec.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonDec.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonDec.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	

	BUTTON_SetBkColor(buttonOpen.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(buttonOpen.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetTextColor(buttonOpen.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
	BUTTON_SetTextColor(buttonOpen.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);
	
	BUTTON_SetBkColor(buttonHalf.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(buttonHalf.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetTextColor(buttonHalf.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
	BUTTON_SetTextColor(buttonHalf.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);
	

	BUTTON_SetBkColor(buttonOff.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(buttonOff.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetTextColor(buttonOff.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
	BUTTON_SetTextColor(buttonOff.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);

	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
	BUTTON_SetBkColor(buttonRet.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);
	
  	if(gCfgItems.multiple_language != 0)	
  	{
		BUTTON_SetText(buttonAdd.btnHandle, fan_menu.add);
		BUTTON_SetText(buttonDec.btnHandle, fan_menu.dec);
		BUTTON_SetText(buttonOpen.btnHandle,fan_menu.full);
		BUTTON_SetText(buttonHalf.btnHandle, fan_menu.half);
		BUTTON_SetText(buttonOff.btnHandle, fan_menu.off);
		BUTTON_SetText(buttonRet.btnHandle, common_menu.text_back);
  	}

	disp_fan_speed();
	
	//GUI_Exec();


	
}

void disp_fan_speed()
{
	char buf[20] = {0};
	char buf1[10] = {0};
	TEXT_SetTextColor(TextFanSpeed, gCfgItems.state_text_color);
	TEXT_SetBkColor(TextFanSpeed, gCfgItems.state_background_color);
	TEXT_SetTextColor(TextFanValue, gCfgItems.state_text_color);
	TEXT_SetBkColor(TextFanValue, gCfgItems.state_background_color);

	sprintf(buf, fan_menu.state);
	if(last_disp_state == PRINT_READY_UI)
	{
			if(gCfgItems.fanOnoff)
			{
				sprintf(buf1, "%d", gCfgItems.pre_fanSpeed);
			}
			else
			{
				sprintf(buf1, "0");
			}
		
	}
	else
	{
			if(gCfgItems.fanOnoff)
			{
				sprintf(buf1, "%d", gCfgItems.fanSpeed);
			}
			else
			{
				sprintf(buf1, "0");
			}
	}

	TEXT_SetText(TextFanSpeed, buf);
	TEXT_SetText(TextFanValue, buf1);
}


void Clear_fan()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hFanWnd))
	{
		WM_DeleteWindow(hFanWnd);
		//GUI_Exec();
	}
	//GUI_Clear();
}



