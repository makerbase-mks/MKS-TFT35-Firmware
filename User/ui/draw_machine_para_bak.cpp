#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "draw_machine_para.h"
#include "draw_set.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hMachineParaWnd;
static BUTTON_STRUCT MachineSettingArrow,TemperatureSettingArrow,MotorSettingArrow,AdvanceSettingArrow;
static BUTTON_STRUCT buttonMachineSetting,buttonTemperatureSetting,buttonMotorSetting,buttonAdvanceSetting,ButtonCustom,buttonConsole;
static BUTTON_STRUCT button_top1,button_title,button_back;

static void cbMachineParaWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);

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
    				last_disp_state = MACHINE_PARA_UI;
    				Clear_MachinePara();
//    				draw_return_ui();
					draw_Set();
    			}	
    			else if(pMsg->hWinSrc == buttonMachineSetting.btnHandle)
    			{
    				last_disp_state = MACHINE_PARA_UI;
    				Clear_MachinePara();
    				draw_MachineSettings();
    			}
    			else if(pMsg->hWinSrc == buttonTemperatureSetting.btnHandle)
    			{
    				last_disp_state = MACHINE_PARA_UI;
    				Clear_MachinePara();
                   draw_TemperatureSettings();
    				
    			}
    			else if(pMsg->hWinSrc == buttonMotorSetting.btnHandle)
    			{
    				last_disp_state = MACHINE_PARA_UI;
    				Clear_MachinePara();
                    draw_MotorSettings();
    			}       
    			else if(pMsg->hWinSrc == buttonAdvanceSetting.btnHandle)
    			{
    				last_disp_state = MACHINE_PARA_UI;
    				Clear_MachinePara();
                    draw_Advanced();
    			}	
				else if(pMsg->hWinSrc == ButtonCustom.btnHandle)
				{
					last_disp_state = MACHINE_PARA_UI;
					Clear_MachinePara();
					draw_CustomConf();
				}	
				else if(pMsg->hWinSrc == buttonConsole.btnHandle)
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
    int i;

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
	
	hMachineParaWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbMachineParaWin, 0);

	

	buttonMachineSetting.btnHandle = BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonTemperatureSetting.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2, 0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//	buttonMotorSetting.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonAdvanceSetting.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	button_back.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	ButtonCustom.btnHandle = BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id()); 

	if(gCfgItems.firmware_type == 1)//marlin
	{
		buttonMotorSetting.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,	0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		buttonConsole.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id()); 
		BUTTON_SetBmpFileName(buttonMotorSetting.btnHandle,"bmp_MotorSetting.bin",1);
		BUTTON_SetBitmapEx(buttonMotorSetting.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
		if(gCfgItems.multiple_language != 0)
		{
			BUTTON_SetText(buttonMotorSetting.btnHandle, MachinePara_menu.MotorSetting);
		}
	}
	else 
		buttonConsole.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hMachineParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	BUTTON_SetBmpFileName(buttonMachineSetting.btnHandle,"bmp_MachineSetting.bin",1);        
    BUTTON_SetBmpFileName(buttonTemperatureSetting.btnHandle,"bmp_TemperatureSetting.bin",1);
    BUTTON_SetBmpFileName(buttonAdvanceSetting.btnHandle,"bmp_AdvanceSetting.bin",1);
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_return.bin",1);   
    BUTTON_SetBmpFileName(ButtonCustom.btnHandle, "bmp_custom.bin",1);   
    BUTTON_SetBmpFileName(buttonConsole.btnHandle, "bmp_gcode.bin",1);   
	  
	BUTTON_SetBitmapEx(buttonTemperatureSetting.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonAdvanceSetting.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(ButtonCustom.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonConsole.btnHandle, 0, &bmp_struct,BMP_PIC_X, BMP_PIC_Y);


    if(gCfgItems.multiple_language != 0)
    {
        BUTTON_SetText(buttonMachineSetting.btnHandle, MachinePara_menu.MachineSetting);
        BUTTON_SetText(buttonTemperatureSetting.btnHandle, MachinePara_menu.TemperatureSetting);
        BUTTON_SetText(buttonAdvanceSetting.btnHandle, MachinePara_menu.AdvanceSetting); 
        BUTTON_SetText(button_back.btnHandle,common_menu.text_back);
		BUTTON_SetText(ButtonCustom.btnHandle, MachinePara_menu.Custom); 
		BUTTON_SetText(buttonConsole.btnHandle, MachinePara_menu.Console); 
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


