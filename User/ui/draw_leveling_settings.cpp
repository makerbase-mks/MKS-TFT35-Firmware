#include "gui.h"
#include "button.h"
#include "draw_ui.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hLevelingSettingsWnd;
static BUTTON_STRUCT LevelParaArrow,XYZLevelParaArrow;
static BUTTON_STRUCT LevelParaText,XYZLevelParaText;
static BUTTON_STRUCT button_back;

static void cbLevelingSettingsWin(WM_MESSAGE * pMsg) {

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
    				last_disp_state = LEVELING_SETTIGNS_UI;
    				Clear_LevelingSettings();
    				draw_return_ui();
    			}	
    			else if((pMsg->hWinSrc == LevelParaText.btnHandle)||
                    (pMsg->hWinSrc == LevelParaArrow.btnHandle))
    			{
    				last_disp_state = LEVELING_SETTIGNS_UI;
    				Clear_LevelingSettings();
    				draw_LevelingPara();
    			}
    			else if((pMsg->hWinSrc == XYZLevelParaText.btnHandle)||
                    (pMsg->hWinSrc == XYZLevelParaArrow.btnHandle))
    			{
    				last_disp_state = LEVELING_SETTIGNS_UI;
    				Clear_LevelingSettings();
                    draw_XYZLevelPara();    		
    			}       			
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_LevelingSettings()
{   
    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != LEVELING_SETTIGNS_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = LEVELING_SETTIGNS_UI;
    }
    disp_state = LEVELING_SETTIGNS_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.LevelingParaConfTitle, TITLE_XPOS, TITLE_YPOS);

    hLevelingSettingsWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbLevelingSettingsWin, 0);

    LevelParaText.btnHandle = BUTTON_CreateEx(10,50,450,40,hLevelingSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    LevelParaArrow.btnHandle = BUTTON_CreateEx(460,50,10,40,hLevelingSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
    //DeltaLevelParaText.btnHandle = BUTTON_CreateEx(10,100,450,40,hLevelingSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    //DeltaLevelParaArrow.btnHandle = BUTTON_CreateEx(460,100,10,40,hLevelingSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
    XYZLevelParaText.btnHandle = BUTTON_CreateEx(10,100,450,40,hLevelingSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    XYZLevelParaArrow.btnHandle = BUTTON_CreateEx(460,100,10,40,hLevelingSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

     
    BUTTON_SetBmpFileName(LevelParaArrow.btnHandle, "bmp_arrow.bin",1);        
    //BUTTON_SetBmpFileName(DeltaLevelParaArrow.btnHandle, "bmp_arrow.bin",1);
    BUTTON_SetBmpFileName(XYZLevelParaArrow.btnHandle, "bmp_arrow.bin",1);
    
    BUTTON_SetBmpFileName(LevelParaText.btnHandle,NULL,1);        
    //BUTTON_SetBmpFileName(DeltaLevelParaText.btnHandle,NULL,1);
    BUTTON_SetBmpFileName(XYZLevelParaText.btnHandle,NULL,1);

    BUTTON_SetBitmapEx(LevelParaArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
    //BUTTON_SetBitmapEx(DeltaLevelParaArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
    BUTTON_SetBitmapEx(XYZLevelParaArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
    
    BUTTON_SetTextAlign(LevelParaText.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
    //BUTTON_SetTextAlign(DeltaLevelParaText.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(XYZLevelParaText.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

    button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hLevelingSettingsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
    
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
    BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0, 0);
    
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 
    
    BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

    if(gCfgItems.multiple_language != 0)
    {
        BUTTON_SetText(LevelParaText.btnHandle, machine_menu.LevelingParaConf);
        //BUTTON_SetText(DeltaLevelParaText.btnHandle, machine_menu.DeltaLevelConf);
        BUTTON_SetText(XYZLevelParaText.btnHandle, machine_menu.XYZLevelconf);   

        BUTTON_SetText(button_back.btnHandle,machine_menu.back);
    }



}


void Clear_LevelingSettings()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hLevelingSettingsWnd))
	{
		WM_DeleteWindow(hLevelingSettingsWnd);
	}
}




