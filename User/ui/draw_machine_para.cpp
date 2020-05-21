#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "draw_machine_para.h"
#include "draw_set.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hMachineParaWnd;
static BUTTON_STRUCT MachineSettingArrow,TemperatureSettingArrow,MotorSettingArrow,AdvanceSettingArrow,GcodeArrow,CustomArrow;
static BUTTON_STRUCT buttonMachineSetting,buttonTemperatureSetting,buttonMotorSetting,buttonAdvanceSetting,ButtonCustom,buttonGcode;
static BUTTON_STRUCT button_next,button_previous,button_back;
static uint8_t current_page = 0 ;//0:上一页，1:下一页

static void cbMachineParaWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(0xff5449);

			GUI_FillRect(10, 90, 470,90);
			if((gCfgItems.firmware_type ==1) || current_page != 1)
            GUI_FillRect(10, 140, 470,140);
           if(current_page != 1)
            {
                GUI_FillRect(10, 190, 470,190);
                GUI_FillRect(10, 240, 470,240);
            }
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
    				current_page = 0;
    				last_disp_state = MACHINE_PARA_UI;
    				Clear_MachinePara();
//    				draw_return_ui();
					draw_Set();
    			}	
				 else if(pMsg->hWinSrc == button_next.btnHandle)
                {
                    current_page = 1;
                    last_disp_state = MACHINE_PARA_UI;
                    Clear_MachinePara();
                    draw_MachinePara();
                }
                else if(pMsg->hWinSrc == button_previous.btnHandle)
                {
                    current_page = 0;
                    last_disp_state = MACHINE_PARA_UI;
                    Clear_MachinePara();
                    draw_MachinePara();
                }         
    			else if((pMsg->hWinSrc == buttonMachineSetting.btnHandle)
						|| pMsg->hWinSrc == MachineSettingArrow.btnHandle)
    			{
    				last_disp_state = MACHINE_PARA_UI;
    				Clear_MachinePara();
    				draw_MachineSettings();
    			}
    			else if((pMsg->hWinSrc == buttonTemperatureSetting.btnHandle)
						|| pMsg->hWinSrc == TemperatureSettingArrow.btnHandle)
    			{
    				last_disp_state = MACHINE_PARA_UI;
    				Clear_MachinePara();
                   draw_TemperatureSettings();
    				
    			}
    			else if((pMsg->hWinSrc == buttonMotorSetting.btnHandle)
						|| pMsg->hWinSrc == MotorSettingArrow.btnHandle )
    			{
    				last_disp_state = MACHINE_PARA_UI;
    				Clear_MachinePara();
                    draw_MotorSettings();
    			}       
    			else if((pMsg->hWinSrc == buttonAdvanceSetting.btnHandle)
						|| pMsg->hWinSrc == AdvanceSettingArrow.btnHandle )
    			{
    				last_disp_state = MACHINE_PARA_UI;
    				Clear_MachinePara();
                    draw_Advanced();
    			}	
				else if((pMsg->hWinSrc == ButtonCustom.btnHandle)
						|| pMsg->hWinSrc == CustomArrow.btnHandle)
				{
					last_disp_state = MACHINE_PARA_UI;
					Clear_MachinePara();
					draw_CustomConf();
				}	
				else if((pMsg->hWinSrc == buttonGcode.btnHandle)
						|| pMsg->hWinSrc == GcodeArrow.btnHandle)
				{
					last_disp_state = MACHINE_PARA_UI;
					Clear_MachinePara();
					valueType = gcodeCmd;
					gcodeSet_flag = 1;
					draw_Keyboard();
				}
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_MachinePara()
{   

	MachineSettingArrow.btnHandle = 0;
	TemperatureSettingArrow.btnHandle = 0;
	MotorSettingArrow.btnHandle = 0;
	AdvanceSettingArrow.btnHandle = 0;
	GcodeArrow.btnHandle = 0;
	CustomArrow.btnHandle = 0;
	buttonMachineSetting.btnHandle = 0;
	buttonTemperatureSetting.btnHandle = 0;
	buttonMotorSetting.btnHandle = 0;
	buttonAdvanceSetting.btnHandle = 0;
	ButtonCustom.btnHandle = 0;
	buttonGcode.btnHandle = 0;
	button_next.btnHandle = 0;
	button_previous.btnHandle = 0;
	button_back.btnHandle = 0;


    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != MACHINE_PARA_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = MACHINE_PARA_UI;
    }
    disp_state = MACHINE_PARA_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
	GUI_DispStringAt(creat_title_text(), TITLE_XPOS, TITLE_YPOS);
	
//	hMachineParaWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbMachineParaWin, 0);
    hMachineParaWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbMachineParaWin, 0);

//	buttonMachineSetting.btnHandle = BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//	buttonTemperatureSetting.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2, 0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
////	buttonMotorSetting.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//	buttonAdvanceSetting.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//	button_back.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//	ButtonCustom.btnHandle = BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id()); 
//
//	if(gCfgItems.firmware_type == 1)//marlin
//	{
//		buttonMotorSetting.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,	0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//		buttonGcode.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id()); 
//		BUTTON_SetBmpFileName(buttonMotorSetting.btnHandle,"bmp_MotorSetting.bin",1);
//		BUTTON_SetBitmapEx(buttonMotorSetting.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
//		if(gCfgItems.multiple_language != 0)
//		{
//			BUTTON_SetText(buttonMotorSetting.btnHandle, MachinePara_menu.MotorSetting);
//		}
//	}
//	else 
//		buttonGcode.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//
//	BUTTON_SetBmpFileName(buttonMachineSetting.btnHandle,"bmp_MachineSetting.bin",1);        
//    BUTTON_SetBmpFileName(buttonTemperatureSetting.btnHandle,"bmp_TemperatureSetting.bin",1);
//    BUTTON_SetBmpFileName(buttonAdvanceSetting.btnHandle,"bmp_AdvanceSetting.bin",1);
//    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_return.bin",1);   
//    BUTTON_SetBmpFileName(ButtonCustom.btnHandle, "bmp_custom.bin",1);   
//    BUTTON_SetBmpFileName(buttonGcode.btnHandle, "bmp_gcode.bin",1);   
//	  
//	BUTTON_SetBitmapEx(buttonTemperatureSetting.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
//	BUTTON_SetBitmapEx(buttonAdvanceSetting.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
//	BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
//	BUTTON_SetBitmapEx(ButtonCustom.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
//	BUTTON_SetBitmapEx(buttonGcode.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
//
//
//    if(gCfgItems.multiple_language != 0)
//    {
//        BUTTON_SetText(buttonMachineSetting.btnHandle, MachinePara_menu.MachineSetting);
//        BUTTON_SetText(buttonTemperatureSetting.btnHandle, MachinePara_menu.TemperatureSetting);
//        BUTTON_SetText(buttonAdvanceSetting.btnHandle, MachinePara_menu.AdvanceSetting); 
//        BUTTON_SetText(button_back.btnHandle,common_menu.text_back);
//		BUTTON_SetText(ButtonCustom.btnHandle, MachinePara_menu.Custom); 
//		BUTTON_SetText(buttonGcode.btnHandle, MachinePara_menu.Console); 
//    }
	if(current_page != 1)
	  {
		  buttonMachineSetting.btnHandle = BUTTON_CreateEx(10,50,450,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		  MachineSettingArrow.btnHandle = BUTTON_CreateEx(460,50,10,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	
		  buttonTemperatureSetting.btnHandle = BUTTON_CreateEx(10,100,450,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		  TemperatureSettingArrow.btnHandle = BUTTON_CreateEx(460,100,10,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	
		  ButtonCustom.btnHandle = BUTTON_CreateEx(10,150,450,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		  CustomArrow.btnHandle = BUTTON_CreateEx(460,150,10,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	
		  buttonAdvanceSetting.btnHandle = BUTTON_CreateEx(10,200,450,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		  AdvanceSettingArrow.btnHandle = BUTTON_CreateEx(460,200,10,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		  BUTTON_SetBmpFileName(MachineSettingArrow.btnHandle, "bmp_arrow.bin",1); 	   
		  BUTTON_SetBmpFileName(TemperatureSettingArrow.btnHandle, "bmp_arrow.bin",1);
		  BUTTON_SetBmpFileName(CustomArrow.btnHandle, "bmp_arrow.bin",1);
		  BUTTON_SetBmpFileName(AdvanceSettingArrow.btnHandle, "bmp_arrow.bin",1);
		  
		  BUTTON_SetBmpFileName(buttonMachineSetting.btnHandle,NULL,1);		
		  BUTTON_SetBmpFileName(buttonTemperatureSetting.btnHandle,NULL,1);
		  BUTTON_SetBmpFileName(ButtonCustom.btnHandle,NULL,1);
		  BUTTON_SetBmpFileName(buttonAdvanceSetting.btnHandle,NULL,1);
		  
		  BUTTON_SetBitmapEx(MachineSettingArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
		  BUTTON_SetBitmapEx(TemperatureSettingArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
		  BUTTON_SetBitmapEx(CustomArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
		  BUTTON_SetBitmapEx(AdvanceSettingArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12); 
		  
		  BUTTON_SetTextAlign(buttonMachineSetting.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
		  BUTTON_SetTextAlign(buttonTemperatureSetting.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
		  BUTTON_SetTextAlign(ButtonCustom.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
		  BUTTON_SetTextAlign(buttonAdvanceSetting.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   
	
		  button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hMachineParaWnd,BUTTON_CF_SHOW,0,alloc_win_id());
		  BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
	  
		  BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);
		  
	
	  }
	  else
	  {
		  buttonGcode.btnHandle = BUTTON_CreateEx(10,50,450,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		  GcodeArrow.btnHandle = BUTTON_CreateEx(460,50,10,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

		  BUTTON_SetBmpFileName(GcodeArrow.btnHandle, "bmp_arrow.bin",1);
		  BUTTON_SetBmpFileName(buttonGcode.btnHandle,NULL,1);

		  BUTTON_SetBitmapEx(GcodeArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
		  BUTTON_SetTextAlign(buttonGcode.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

		  button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hMachineParaWnd,BUTTON_CF_SHOW,0,alloc_win_id());
		  BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
		  
		  BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);

		if(gCfgItems.firmware_type == 1)//marlin
		{
			buttonMotorSetting.btnHandle = BUTTON_CreateEx(10,100,450,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
			MotorSettingArrow.btnHandle = BUTTON_CreateEx(460,100,10,40,hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
			BUTTON_SetBmpFileName(MotorSettingArrow.btnHandle, "bmp_arrow.bin",1); 
			BUTTON_SetBmpFileName(buttonMotorSetting.btnHandle,NULL,1);  
			BUTTON_SetBitmapEx(MotorSettingArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12); 		
			BUTTON_SetTextAlign(buttonMotorSetting.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER ); 
			BUTTON_SetText(buttonMotorSetting.btnHandle, MachinePara_menu.MotorSetting);		
		}
		  
	  }
	
	   button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hMachineParaWnd,BUTTON_CF_SHOW,0,alloc_win_id());
	   
	   BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1); 	   
	   BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0, 0);
		  
	   BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	   BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
	   BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	   BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
	   BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	   BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color);	
	   BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	   BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);	  
	   BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	   BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
	   BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	   BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 
	   
	   BUTTON_SetTextAlign(button_next.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	   BUTTON_SetTextAlign(button_previous.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	   BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	
	   if(gCfgItems.multiple_language != 0)
	   {
		  if(current_page != 1)
		  {
			  BUTTON_SetText(buttonMachineSetting.btnHandle, MachinePara_menu.MachineSetting);
			  BUTTON_SetText(buttonTemperatureSetting.btnHandle, MachinePara_menu.TemperatureSetting);
			  BUTTON_SetText(ButtonCustom.btnHandle, MachinePara_menu.Custom);
			  BUTTON_SetText(buttonAdvanceSetting.btnHandle, MachinePara_menu.AdvanceSetting);
			  BUTTON_SetText(button_next.btnHandle,machine_menu.next);
		  }
		  else
		  {
			  BUTTON_SetText(buttonGcode.btnHandle,MachinePara_menu.Console);	  
			  BUTTON_SetText(button_previous.btnHandle,machine_menu.previous);	 
		  }
		  BUTTON_SetText(button_back.btnHandle,machine_menu.back);	  
	   }
}


void Clear_MachinePara()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hMachineParaWnd))
	{
		WM_DeleteWindow(hMachineParaWnd);
	}
}


