#include "gui.h"
#include "button.h"
#include "draw_ui.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hCustomConfWnd;
static BUTTON_STRUCT DisplaySettingArrow,ButtonSettingArrow;
static BUTTON_STRUCT buttonDislaySetting,buttonFunctionSetting;
static BUTTON_STRUCT button_top1,button_title,button_back;

static void cbCustomConfWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(0xff5449);
			GUI_FillRect(10, 90, 470,90);
            GUI_FillRect(10, 140, 470,140);
            //GUI_FillRect(10, 190, 470,190);
 
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
    				last_disp_state = CUSTOM_UI;
    				Clear_CustomConf();
    				draw_return_ui();
    			}	
    			else if((pMsg->hWinSrc == buttonDislaySetting.btnHandle)||
                    (pMsg->hWinSrc == DisplaySettingArrow.btnHandle))
    			{
    				last_disp_state = CUSTOM_UI;
    				Clear_CustomConf();
    				draw_displayConf();
    			}
    			else if((pMsg->hWinSrc == buttonFunctionSetting.btnHandle)||
                    (pMsg->hWinSrc == ButtonSettingArrow.btnHandle))

    			{
    				last_disp_state = CUSTOM_UI;
    				Clear_CustomConf();
                    draw_buttonConf();
    			}
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_CustomConf()
{   
    int i;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != CUSTOM_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = CUSTOM_UI;
    }
    disp_state = CUSTOM_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.CustomConfTitle, TITLE_XPOS, TITLE_YPOS);

    hCustomConfWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbCustomConfWin, 0);

    buttonDislaySetting.btnHandle = BUTTON_CreateEx(10,50,450,40,hCustomConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    DisplaySettingArrow.btnHandle = BUTTON_CreateEx(460,50,10,40,hCustomConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
    buttonFunctionSetting.btnHandle = BUTTON_CreateEx(10,100,450,40,hCustomConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    ButtonSettingArrow.btnHandle = BUTTON_CreateEx(460,100,10,40,hCustomConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
     
    BUTTON_SetBmpFileName(DisplaySettingArrow.btnHandle, "bmp_arrow.bin",1);        
    BUTTON_SetBmpFileName(ButtonSettingArrow.btnHandle, "bmp_arrow.bin",1);
    
    BUTTON_SetBmpFileName(buttonDislaySetting.btnHandle,NULL,1);        
    BUTTON_SetBmpFileName(buttonFunctionSetting.btnHandle,NULL,1);

    BUTTON_SetBitmapEx(DisplaySettingArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
    BUTTON_SetBitmapEx(ButtonSettingArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
    
    BUTTON_SetTextAlign(buttonDislaySetting.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(buttonFunctionSetting.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

    button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hCustomConfWnd,BUTTON_CF_SHOW,0,alloc_win_id());
    
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
    BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0, 0);
    BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_CENTER|GUI_TA_VCENTER );
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 

    if(gCfgItems.multiple_language != 0)
    {
        BUTTON_SetText(buttonDislaySetting.btnHandle, machine_menu.display);
        BUTTON_SetText(buttonFunctionSetting.btnHandle, machine_menu.button); 
        BUTTON_SetText(button_back.btnHandle,machine_menu.back);
    }

}


void Clear_CustomConf()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hCustomConfWnd))
	{
		WM_DeleteWindow(hCustomConfWnd);
	}
}



