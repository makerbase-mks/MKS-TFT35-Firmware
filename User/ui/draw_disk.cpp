#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_disk.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"


#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hDiskWnd;


extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern int X_ADD,X_INTERVAL;   //**图片间隔
	
static BUTTON_STRUCT buttonMainSd, buttonSd, buttonUdisk, buttonRet;

static void cbDiskWin(WM_MESSAGE * pMsg) {

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
					Clear_Disk();
					draw_return_ui();
					
				}
				else if(pMsg->hWinSrc == buttonSd.btnHandle)
				{
					gCfgItems.fileSysType = 1;		
					bakup_cfg_inf(BAK_FILE_SYS_ID,  gCfgItems.fileSysType);	//**
					disp_disk_choose();
				}
				else if(pMsg->hWinSrc == buttonUdisk.btnHandle)
				{
                    gCfgItems.fileSysType = 0;		
					bakup_cfg_inf(BAK_FILE_SYS_ID,  gCfgItems.fileSysType);	//**	
					disp_disk_choose();
				}
				
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
	}


void draw_Disk()
{
		
//	int titleHeight = 30;

//	int imgHeight = LCD_HEIGHT - titleHeight;	
	
	int i;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != DISK_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = DISK_UI;
	}
	disp_state = DISK_UI;
		
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
	//GUI_SetFont(&FONT_TITLE);

	//GUI_DispStringAt("准备打印->设置->文件系统", 0, 0);
	GUI_DispStringAt(creat_title_text(),  TITLE_XPOS, TITLE_YPOS);
	
	hDiskWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbDiskWin, 0);

	
	buttonSd.btnHandle = BUTTON_CreateEx(INTERVAL_V, 0, BTN_X_PIXEL, BTN_Y_PIXEL, hDiskWnd, BUTTON_CF_SHOW, 0, 301);
	buttonUdisk.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hDiskWnd, BUTTON_CF_SHOW, 0, 302);
	//buttonUdisk = BUTTON_CreateEx(LCD_WIDTH /2 , 0, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, hDiskWnd, BUTTON_CF_SHOW, 0, 303);
	buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,BTN_Y_PIXEL+INTERVAL_H, BTN_X_PIXEL, BTN_Y_PIXEL, hDiskWnd, BUTTON_CF_SHOW, 0, 308);

	#if VERSION_WITH_PIC	  //**
	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);

	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);
	
	if(gCfgItems.multiple_language != 0)
	{
		BUTTON_SetText(buttonSd.btnHandle, filesys_menu.sd_sys);
		BUTTON_SetText(buttonUdisk.btnHandle, filesys_menu.usb_sys);
		BUTTON_SetText(buttonRet.btnHandle, common_menu.text_back);
	}
	
	#endif
	disp_disk_choose();

	
}

void disp_disk_choose()
{
	if(gCfgItems.fileSysType == 0)
	{
		#if VERSION_WITH_PIC	
		BUTTON_SetBmpFileName(buttonUdisk.btnHandle, "bmp_usb_sel.bin",1);
		BUTTON_SetBmpFileName(buttonSd.btnHandle, "bmp_sd.bin",1);
		BUTTON_SetBitmapEx(buttonUdisk.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
		BUTTON_SetBitmapEx(buttonSd.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
		
		BUTTON_SetBkColor(buttonUdisk.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_color);
		BUTTON_SetBkColor(buttonUdisk.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_color);
		BUTTON_SetBkColor(buttonSd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
		BUTTON_SetBkColor(buttonSd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);

		BUTTON_SetTextColor(buttonUdisk.btnHandle,BUTTON_CI_PRESSED,gCfgItems.btn_state_sel_textcolor);
		BUTTON_SetTextColor(buttonUdisk.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.btn_state_sel_textcolor);
		BUTTON_SetTextColor(buttonSd.btnHandle,BUTTON_CI_PRESSED,gCfgItems.btn_state_textcolor);
		BUTTON_SetTextColor(buttonSd.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.btn_state_textcolor);

		#endif
		}	
	else if(gCfgItems.fileSysType == 1)
	{		
		#if VERSION_WITH_PIC	
		BUTTON_SetBmpFileName(buttonUdisk.btnHandle, "bmp_usb.bin",1);
		BUTTON_SetBmpFileName(buttonSd.btnHandle, "bmp_sd_sel.bin",1);
		BUTTON_SetBitmapEx(buttonUdisk.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
		BUTTON_SetBitmapEx(buttonSd.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);

		BUTTON_SetBkColor(buttonUdisk.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
		BUTTON_SetBkColor(buttonUdisk.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
		BUTTON_SetBkColor(buttonSd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_color);
		BUTTON_SetBkColor(buttonSd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_color);
		
		BUTTON_SetTextColor(buttonUdisk.btnHandle,BUTTON_CI_PRESSED,gCfgItems.btn_state_textcolor);
		BUTTON_SetTextColor(buttonUdisk.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.btn_state_textcolor);
		BUTTON_SetTextColor(buttonSd.btnHandle,BUTTON_CI_PRESSED,gCfgItems.btn_state_sel_textcolor);
		BUTTON_SetTextColor(buttonSd.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.btn_state_sel_textcolor);

		#endif
	}	

	if(gCfgItems.multiple_language != 0)
	{
		BUTTON_SetText(buttonUdisk.btnHandle, filesys_menu.usb_sys);
		BUTTON_SetText(buttonSd.btnHandle, filesys_menu.sd_sys);
	}		
		
	
}


void Clear_Disk()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hDiskWnd))
	{
		WM_DeleteWindow(hDiskWnd);
		//GUI_Exec();   
	}
	
	//GUI_Clear();
}

