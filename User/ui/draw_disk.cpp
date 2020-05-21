#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "draw_disk.h"
#include "at24cxx.h"
#include "draw_print_file.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hDiskWnd;


//extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
//extern int X_ADD,X_INTERVAL;   //**图片间隔


static BUTTON_STRUCT SD_Sel,USB_Sel;
static BUTTON_STRUCT buttonSd, buttonUdisk,button_back;
//static TEXT_Handle textSelectSys;
extern uint8_t disp_in_file_dir;

static void cbDiskWin(WM_MESSAGE * pMsg) {

	struct PressEvt *press_event;
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			//GUI_SetBkColor(GUI_BLUE);
			//GUI_Clear();
			//GUI_DispString("window");
			GUI_SetColor(0xff5449);
			GUI_FillRect(10, 90, 470,90);
            GUI_FillRect(10, 140, 470,140);			
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
				if(pMsg->hWinSrc == button_back.btnHandle)
				{
                  	last_disp_state = DISK_UI;				
					Clear_Disk();
					draw_return_ui();
				}
				else if((pMsg->hWinSrc == buttonSd.btnHandle)||
						(pMsg->hWinSrc == SD_Sel.btnHandle)	)
				{
					disp_in_file_dir = 1;
                  	last_disp_state = DISK_UI;
					gCfgItems.fileSysType = 1;		
//					bakup_cfg_inf(BAK_FILE_SYS_ID,  gCfgItems.fileSysType);	//**
					HAL::AT24CXX_Write(BAK_FILE_SYS_ADDR,(uint8_t *)&gCfgItems.fileSysType ,  1);
//					disp_disk_choose();
					Clear_Disk();
					draw_print_file();
				}
				else if((pMsg->hWinSrc == buttonUdisk.btnHandle)||
						(pMsg->hWinSrc == USB_Sel.btnHandle)      )
				{
					disp_in_file_dir = 1;
                    last_disp_state = DISK_UI;                                  
	                gCfgItems.fileSysType = 0;		
//					bakup_cfg_inf(BAK_FILE_SYS_ID,  gCfgItems.fileSysType);	//**	
					HAL::AT24CXX_Write(BAK_FILE_SYS_ADDR,(uint8_t *)&gCfgItems.fileSysType ,  1);
//					disp_disk_choose();
					Clear_Disk();

					draw_print_file();
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
	
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != DISK_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = DISK_UI;
	}
	disp_state = DISK_UI;   
		
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
//	GUI_SetFont(&FONT_TITLE);

	//GUI_DispStringAt("准备打印->设置->文件系统", 0, 0);
	GUI_DispStringAt(creat_title_text(),  TITLE_XPOS, TITLE_YPOS);

	hDiskWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbDiskWin, 0);
	
//	textSelectSys = TEXT_CreateEx(0,0, LCD_WIDTH, 90, hDiskWnd, WM_CF_SHOW, TEXT_CF_LEFT, alloc_win_id(), " ");
//	
//	TEXT_SetTextColor(textSelectSys, gCfgItems.title_color);
//	TEXT_SetTextAlign(textSelectSys, GUI_TA_VCENTER | GUI_TA_HCENTER);		
	
//	buttonSd.btnHandle = BUTTON_CreateEx((LCD_WIDTH-140)/2, (imgHeight-40)/2, 140, 50,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//	buttonUdisk.btnHandle = BUTTON_CreateEx((LCD_WIDTH-140)/2, (imgHeight-40)/2, 140, 50,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

//	buttonSd.btnHandle= BUTTON_CreateEx(15,(imgHeight-40)/2,140,50,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//	buttonUdisk.btnHandle= BUTTON_CreateEx(170,(imgHeight-40)/2,140,50,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//	button_back.btnHandle = BUTTON_CreateEx(325, (imgHeight-40)/2, 140, 50,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	buttonSd.btnHandle = BUTTON_CreateEx(10,50,450,40,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	SD_Sel.btnHandle = BUTTON_CreateEx(460,50,10,40,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	
	buttonUdisk.btnHandle = BUTTON_CreateEx(10,100,450,40,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	USB_Sel.btnHandle = BUTTON_CreateEx(460,100,10,40,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	BUTTON_SetBmpFileName(SD_Sel.btnHandle, "bmp_arrow.bin",1); 	   
	BUTTON_SetBmpFileName(USB_Sel.btnHandle, "bmp_arrow.bin",1);

	BUTTON_SetBmpFileName(buttonSd.btnHandle,NULL,1);
	BUTTON_SetBmpFileName(buttonUdisk.btnHandle,NULL,1);

	BUTTON_SetBitmapEx(SD_Sel.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
	BUTTON_SetBitmapEx(USB_Sel.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
	
	BUTTON_SetTextAlign(buttonSd.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	BUTTON_SetTextAlign(buttonUdisk.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	BUTTON_SetTextAlign(SD_Sel.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	BUTTON_SetTextAlign(USB_Sel.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   

//	BUTTON_SetBkColor(buttonSd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.dialog_btn_color);
//	BUTTON_SetBkColor(buttonSd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.dialog_btn_color);
//	BUTTON_SetTextColor(buttonSd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.dialog_btn_textcolor);
//	BUTTON_SetTextColor(buttonSd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.dialog_btn_textcolor);
//	BUTTON_SetTextAlign(buttonSd.btnHandle, GUI_TA_VCENTER | GUI_TA_HCENTER);
//
//	BUTTON_SetBkColor(buttonUdisk.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.dialog_btn_color);
//	BUTTON_SetBkColor(buttonUdisk.btnHandle, BUTTON_CI_PRESSED, gCfgItems.dialog_btn_color);
//	BUTTON_SetTextColor(buttonUdisk.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.dialog_btn_textcolor);
//	BUTTON_SetTextColor(buttonUdisk.btnHandle, BUTTON_CI_PRESSED, gCfgItems.dialog_btn_textcolor);
//	BUTTON_SetTextAlign(buttonUdisk.btnHandle, GUI_TA_VCENTER | GUI_TA_HCENTER);
//
//	BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.dialog_btn_color);
//	BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.dialog_btn_color);
//	BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.dialog_btn_textcolor);
//	BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.dialog_btn_textcolor);
//	BUTTON_SetTextAlign(button_back.btnHandle, GUI_TA_VCENTER | GUI_TA_HCENTER);
//
//	BUTTON_SetText(buttonSd.btnHandle, filesys_menu.sd_sys);
//	BUTTON_SetText(buttonUdisk.btnHandle, filesys_menu.usb_sys);
//	BUTTON_SetText(button_back.btnHandle, print_file_dialog_menu.cancle);
//	TEXT_SetText(textSelectSys, print_file_dialog_menu.print_file);



	
////	hDiskWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbDiskWin, 0);
//	hDiskWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbDiskWin, 0);
//
//	
////	buttonSd.btnHandle = BUTTON_CreateEx(INTERVAL_V, 0, BTN_X_PIXEL, BTN_Y_PIXEL, hDiskWnd, BUTTON_CF_SHOW, 0, 301);
////	buttonUdisk.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hDiskWnd, BUTTON_CF_SHOW, 0, 302);
////	//buttonUdisk = BUTTON_CreateEx(LCD_WIDTH /2 , 0, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, hDiskWnd, BUTTON_CF_SHOW, 0, 303);
////	buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,BTN_Y_PIXEL+INTERVAL_H, BTN_X_PIXEL, BTN_Y_PIXEL, hDiskWnd, BUTTON_CF_SHOW, 0, 308);
//    buttonSd.btnHandle = BUTTON_CreateEx(10,50,360,40,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//    SD_Sel.btnHandle = BUTTON_CreateEx(370,50,90,40,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//    
//    buttonUdisk.btnHandle = BUTTON_CreateEx(10,100,360,40,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//    USB_Sel.btnHandle = BUTTON_CreateEx(370,100,90,40,hDiskWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
////	#if VERSION_WITH_PIC	  //**
////	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);
////	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
////
////	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
////	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
////	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
////	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);
////	
////	if(gCfgItems.multiple_language != 0)
////	{
////		BUTTON_SetText(buttonSd.btnHandle, filesys_menu.sd_sys);
////		BUTTON_SetText(buttonUdisk.btnHandle, filesys_menu.usb_sys);
////		BUTTON_SetText(buttonRet.btnHandle, common_menu.text_back);
////	}
////	
////	#endif
//
//	disp_disk_choose();
//
//	BUTTON_SetBmpFileName(buttonSd.btnHandle,NULL,1);		 
//	BUTTON_SetBmpFileName(buttonUdisk.btnHandle,NULL,1);
//
//	BUTTON_SetBitmapEx(SD_Sel.btnHandle,0,&bmp_struct26X26,64,7);
//	BUTTON_SetBitmapEx(USB_Sel.btnHandle,0,&bmp_struct26X26,64,7);
//
//	BUTTON_SetTextAlign(buttonSd.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
//	BUTTON_SetTextAlign(buttonUdisk.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
//
	button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hDiskWnd,BUTTON_CF_SHOW,0,alloc_win_id());

	BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);		
	BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0, 0);
	BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
	BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 

	if(gCfgItems.multiple_language != 0)
	{
		BUTTON_SetText(buttonSd.btnHandle, filesys_menu.sd_sys);
		BUTTON_SetText(buttonUdisk.btnHandle,filesys_menu.usb_sys);
		BUTTON_SetText(button_back.btnHandle,common_menu.text_back);
	}
}

void disp_disk_choose()
{
//	if(gCfgItems.fileSysType == 0)
//	{
//		#if VERSION_WITH_PIC	
//		BUTTON_SetBmpFileName(buttonUdisk.btnHandle, "bmp_usb_sel.bin",1);
//		BUTTON_SetBmpFileName(buttonSd.btnHandle, "bmp_sd.bin",1);
//		BUTTON_SetBitmapEx(buttonUdisk.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
//		BUTTON_SetBitmapEx(buttonSd.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
//		
//		BUTTON_SetBkColor(buttonUdisk.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_color);
//		BUTTON_SetBkColor(buttonUdisk.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_color);
//		BUTTON_SetBkColor(buttonSd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
//		BUTTON_SetBkColor(buttonSd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
//
//		BUTTON_SetTextColor(buttonUdisk.btnHandle,BUTTON_CI_PRESSED,gCfgItems.btn_state_sel_textcolor);
//		BUTTON_SetTextColor(buttonUdisk.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.btn_state_sel_textcolor);
//		BUTTON_SetTextColor(buttonSd.btnHandle,BUTTON_CI_PRESSED,gCfgItems.btn_state_textcolor);
//		BUTTON_SetTextColor(buttonSd.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.btn_state_textcolor);
//
//		#endif
//		}	
//	else if(gCfgItems.fileSysType == 1)
//	{		
//		#if VERSION_WITH_PIC	
//		BUTTON_SetBmpFileName(buttonUdisk.btnHandle, "bmp_usb.bin",1);
//		BUTTON_SetBmpFileName(buttonSd.btnHandle, "bmp_sd_sel.bin",1);
//		BUTTON_SetBitmapEx(buttonUdisk.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
//		BUTTON_SetBitmapEx(buttonSd.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
//
//		BUTTON_SetBkColor(buttonUdisk.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
//		BUTTON_SetBkColor(buttonUdisk.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
//		BUTTON_SetBkColor(buttonSd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_sel_color);
//		BUTTON_SetBkColor(buttonSd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_sel_color);
//		
//		BUTTON_SetTextColor(buttonUdisk.btnHandle,BUTTON_CI_PRESSED,gCfgItems.btn_state_textcolor);
//		BUTTON_SetTextColor(buttonUdisk.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.btn_state_textcolor);
//		BUTTON_SetTextColor(buttonSd.btnHandle,BUTTON_CI_PRESSED,gCfgItems.btn_state_sel_textcolor);
//		BUTTON_SetTextColor(buttonSd.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.btn_state_sel_textcolor);
//
//		#endif
//	}	

//	if(gCfgItems.multiple_language != 0)
//	{
//		BUTTON_SetText(buttonUdisk.btnHandle, filesys_menu.usb_sys);
//		BUTTON_SetText(buttonSd.btnHandle, filesys_menu.sd_sys);
//	}		
//		
//	 switch(gCfgItems.fileSysType)
//    {
//        case 0:
//            BUTTON_SetBmpFileName(USB_Sel.btnHandle, "bmp_circle_sel.bin",1);        
//            BUTTON_SetBmpFileName(SD_Sel.btnHandle, "bmp_circle.bin",1);
//            break;
//        case 1:
//            BUTTON_SetBmpFileName(USB_Sel.btnHandle, "bmp_circle.bin",1);        
//            BUTTON_SetBmpFileName(SD_Sel.btnHandle, "bmp_circle_sel.bin",1);
//            break;
//        default:         
//            break;
//    }
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

