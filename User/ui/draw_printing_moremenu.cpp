#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "fontLib.h"
//#include "printer.h"
#include "sd_usr.h"
#include "draw_printing_moremenu.h"
#include "draw_filamentchange.h"
#include "draw_fan.h"
#include "pic_manager.h"
#include "SPI_Flash.h"
#include "mks_tft_com.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif
extern char cmd_code[201];
extern volatile unsigned char *codebufpoint;
extern volatile uint8_t  mksPrinterStatusFlag;
extern PR_STATUS printerStaus;

static GUI_HWIN hPrintmoreWnd;

extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern int X_ADD,X_INTERVAL;   //**Í¼Æ¬¼ä¸ô

static BUTTON_STRUCT buttonFilament_P,buttonFan_P,buttonoff_P,morefunc1,morefunc2,morefunc3,morefunc4,morefunc5,morefunc6,morefunc7,buttonRet;



static void cbPrintmoreWin(WM_MESSAGE * pMsg) {

	struct PressEvt *press_event;
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			//GUI_SetBkColor(GUI_BLUE);
			//GUI_Clear();
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
				if(pMsg->hWinSrc == buttonRet.btnHandle)
				{
					clear_cur_ui();
					draw_return_ui();
					
				}
				#if 0
				else if(pMsg->hWinSrc == buttonFan_P.btnHandle)
				{
					last_disp_state = PRINT_MORE_UI;
					Clear_Printmore();
					draw_fan();
				}
				else if(pMsg->hWinSrc == buttonFilament_P.btnHandle)
				{
					last_disp_state = PRINT_MORE_UI;
					Clear_Printmore();
					draw_FilamentChange();
				}	
				
				else if(pMsg->hWinSrc == buttonoff_P.btnHandle)
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
				#endif
				else if(pMsg->hWinSrc == morefunc1.btnHandle)
				{
					SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC1_ADDR,201);
					codebufpoint = (volatile unsigned char *)cmd_code;	
				}
				else if(pMsg->hWinSrc == morefunc2.btnHandle)
				{
					SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC2_ADDR,201);
					codebufpoint = (volatile unsigned char *)cmd_code;	
				}					
				else if(pMsg->hWinSrc == morefunc3.btnHandle)
				{
					SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC3_ADDR,201);
					codebufpoint = (volatile unsigned char *)cmd_code;	
				}				
				else if(pMsg->hWinSrc == morefunc4.btnHandle)
				{
					SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC4_ADDR,201);
					codebufpoint = (volatile unsigned char *)cmd_code;	
				}				
				else if(pMsg->hWinSrc == morefunc5.btnHandle)
				{
					SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC5_ADDR,201);
					codebufpoint = (volatile unsigned char *)cmd_code;	
				}	
				else if(pMsg->hWinSrc == morefunc6.btnHandle)
				{
					SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC6_ADDR,201);
					codebufpoint = (u8 *)cmd_code;	
				}
				else if(pMsg->hWinSrc == morefunc7.btnHandle)
				{
					SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC6_ADDR,201);
					codebufpoint = (u8 *)cmd_code;	
				}				
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
	}

void draw_printmore()
{
	int i;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != PRINT_MORE_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = PRINT_MORE_UI;
	}
	
	disp_state = PRINT_MORE_UI;
	
	GUI_Clear();

	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
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
	GUI_DispStringAt(creat_title_text(), TITLE_XPOS, TITLE_YPOS);
	
	hPrintmoreWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbPrintmoreWin, 0);
	
	if(gCfgItems.morefunc_cnt >7)
	{
		gCfgItems.morefunc_cnt = 7;
	}
	switch(gCfgItems.morefunc_cnt)
	{
		case 7:
		   morefunc7.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hPrintmoreWnd, BUTTON_CF_SHOW, 0, 107);	
		case 6:
		   morefunc6.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hPrintmoreWnd, BUTTON_CF_SHOW, 0, 107);	
		case 5:
		   morefunc5.btnHandle= BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL,hPrintmoreWnd, BUTTON_CF_SHOW, 0, 107);
		case 4:
		   morefunc4.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hPrintmoreWnd, BUTTON_CF_SHOW, 0, 106);
		case 3:
		   morefunc3.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,0,BTN_X_PIXEL, BTN_Y_PIXEL,hPrintmoreWnd, BUTTON_CF_SHOW, 0, 105);
		case 2:
		   morefunc2.btnHandle= BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  0, BTN_X_PIXEL, BTN_Y_PIXEL,hPrintmoreWnd, BUTTON_CF_SHOW, 0, 108);
		case 1:
		   morefunc1.btnHandle= BUTTON_CreateEx(INTERVAL_V,  0,BTN_X_PIXEL, BTN_Y_PIXEL,hPrintmoreWnd, BUTTON_CF_SHOW, 0, 103);
		break;
		default:break;			
	}

	
	buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4 , BTN_Y_PIXEL+INTERVAL_H, BTN_X_PIXEL, BTN_Y_PIXEL, hPrintmoreWnd, BUTTON_CF_SHOW, 0, 308);

	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);

	BUTTON_SetBmpFileName(morefunc1.btnHandle, "bmp_morefunc1.bin",1);
	BUTTON_SetBmpFileName(morefunc2.btnHandle, "bmp_morefunc2.bin",1);
	BUTTON_SetBmpFileName(morefunc3.btnHandle, "bmp_morefunc3.bin",1);
	BUTTON_SetBmpFileName(morefunc4.btnHandle, "bmp_morefunc4.bin",1);
	BUTTON_SetBmpFileName(morefunc5.btnHandle, "bmp_morefunc5.bin",1);
	BUTTON_SetBmpFileName(morefunc6.btnHandle, "bmp_morefunc6.bin",1);
	BUTTON_SetBmpFileName(morefunc7.btnHandle, "bmp_morefunc7.bin",1);	
	
	BUTTON_SetBitmapEx(morefunc1.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(morefunc2.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(morefunc3.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(morefunc4.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(morefunc5.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(morefunc6.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(morefunc7.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);

	BUTTON_SetBkColor(morefunc1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc2.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc2.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc3.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc3.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc4.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc4.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc5.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc5.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc6.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc6.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc7.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(morefunc7.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);

	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);

	if(gCfgItems.multiple_language != 0)
	{
		BUTTON_SetText(buttonRet.btnHandle, common_menu.text_back);
	}	
}

void Clear_Printmore()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hPrintmoreWnd))
	{
		WM_DeleteWindow(hPrintmoreWnd);
		//**GUI_Exec();
	}
	//GUI_Clear();
}


