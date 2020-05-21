#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "draw_disk.h"
#include "mks_tft_com.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hMachineSettingsWnd;
static BUTTON_STRUCT MachineArrow,FirmwareArrow,BaudRateArrow,PausePosArrow,FilamentArrow,LevelingArrow;//DeltaLevelParaArrow,WifiConfArrow,FilesysArrow;
static BUTTON_STRUCT buttonMachine,buttonFirmware,buttonBaudRate,buttonPausePos,buttonFilament,buttonLeveling;//DeltaLevelParaText,buttonWifi,buttonFilesys;
static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void cbMachineSettingsWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(0xff5449);

			GUI_FillRect(10, 90, 470,90);
            GUI_FillRect(10, 140, 470,140);
//			GUI_FillRect(10, 190, 470,190);///
            if(current_page != 1)
            {
                //GUI_FillRect(10, 190, 470,190);
                GUI_FillRect(10, 190, 470,190);
                GUI_FillRect(10, 240, 470,240);
            }
            //GUI_FillRect(10, 264, 470,264);
            //GUI_FillRect(10, 310, 470,310);

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
    				last_disp_state = MACHINE_SETTINGS_UI;
    				Clear_MachineSettings();
    				draw_return_ui();
    			}	
                else if(pMsg->hWinSrc == button_next.btnHandle)
                {
                    current_page = 1;
                    last_disp_state = MACHINE_SETTINGS_UI;
                    Clear_MachineSettings();
                    draw_MachineSettings();
                }
                else if(pMsg->hWinSrc == button_previous.btnHandle)
                {
                    current_page = 0;
                    last_disp_state = MACHINE_SETTINGS_UI;
                    Clear_MachineSettings();
                    draw_MachineSettings();
                }                
    			else if((pMsg->hWinSrc == buttonMachine.btnHandle)||
                    (pMsg->hWinSrc == MachineArrow.btnHandle))
    			{
    				last_disp_state = MACHINE_SETTINGS_UI;
    				Clear_MachineSettings();
    				draw_MachineType();
    			}
    			else if((pMsg->hWinSrc == buttonFirmware.btnHandle)||
                    (pMsg->hWinSrc == FirmwareArrow.btnHandle))
    			{
    				last_disp_state = MACHINE_SETTINGS_UI;
    				Clear_MachineSettings();
                     draw_FirmwareType();
    			}
    			else if((pMsg->hWinSrc == buttonBaudRate.btnHandle)||
                    (pMsg->hWinSrc == BaudRateArrow.btnHandle))
    			{
    				last_disp_state = MACHINE_SETTINGS_UI;
    				Clear_MachineSettings();
					 draw_BaudRate();
    			}       
    			else if((pMsg->hWinSrc == buttonPausePos.btnHandle)||
                    (pMsg->hWinSrc == PausePosArrow.btnHandle))
    			{
    				last_disp_state = MACHINE_SETTINGS_UI;
    				Clear_MachineSettings();
						draw_PausePos();
    			}
    			else if((pMsg->hWinSrc == buttonFilament.btnHandle)||
                    (pMsg->hWinSrc == FilamentArrow.btnHandle))

    			{
    				last_disp_state = MACHINE_SETTINGS_UI;
    				Clear_MachineSettings();
                    draw_FilamentSettings();

    			} 
			/*else if((pMsg->hWinSrc == DeltaLevelParaText.btnHandle)||
                    (pMsg->hWinSrc == DeltaLevelParaArrow.btnHandle))
    			{
    				last_disp_state = MACHINE_SETTINGS_UI;
    				Clear_LevelingSettings();
                    draw_DeltaLevelPara();
    				
    			}*/
    			else if((pMsg->hWinSrc == buttonLeveling.btnHandle)||
                    (pMsg->hWinSrc == LevelingArrow.btnHandle))
    			{
    				if(gCfgItems.firmware_type == 1)
    			   	pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) "M503\n");     //get probe offset
    				last_disp_state = MACHINE_SETTINGS_UI;
    				Clear_MachineSettings();
                    draw_LevelingSettings();
    			}      
//    			else if((pMsg->hWinSrc == buttonWifi.btnHandle)||
//                    (pMsg->hWinSrc == WifiConfArrow.btnHandle))
//
//    			{
//    				last_disp_state = WIFI_CONF_UI;
//    				Clear_MachineSettings();
//                    draw_WifiConfig();
//
//    			} 	
//    			else if((pMsg->hWinSrc == buttonFilesys.btnHandle)||
//                    (pMsg->hWinSrc == FilesysArrow.btnHandle))
//    			{
//    				last_disp_state = WIFI_CONF_UI;
//    				Clear_MachineSettings();
//                    draw_Disk();
//    			} 
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_MachineSettings()
{   
    buttonMachine.btnHandle = 0;
    MachineArrow.btnHandle = 0;
    buttonFirmware.btnHandle = 0;
    FirmwareArrow.btnHandle = 0;
    buttonBaudRate.btnHandle = 0;
    BaudRateArrow.btnHandle = 0;
    buttonPausePos.btnHandle = 0;
    PausePosArrow.btnHandle = 0;
    buttonFilament.btnHandle = 0;
    FilamentArrow.btnHandle = 0;   
    buttonLeveling.btnHandle = 0;
    LevelingArrow.btnHandle = 0;
//    buttonFilesys.btnHandle = 0;
//    FilesysArrow.btnHandle = 0;
    button_previous.btnHandle = 0;
    button_next.btnHandle = 0;
    button_back.btnHandle = 0;	
//	buttonWifi.btnHandle=0;
//	WifiConfArrow.btnHandle=0;
    
    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != MACHINE_SETTINGS_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = MACHINE_SETTINGS_UI;
    }
    disp_state = MACHINE_SETTINGS_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.MachineConfigTitle, TITLE_XPOS, TITLE_YPOS);

    hMachineSettingsWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbMachineSettingsWin, 0);

    if(current_page != 1)
    {
        buttonMachine.btnHandle = BUTTON_CreateEx(10,50,450,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        MachineArrow.btnHandle = BUTTON_CreateEx(460,50,10,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        buttonFirmware.btnHandle = BUTTON_CreateEx(10,100,450,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        FirmwareArrow.btnHandle = BUTTON_CreateEx(460,100,10,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        buttonBaudRate.btnHandle = BUTTON_CreateEx(10,150,450,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        BaudRateArrow.btnHandle = BUTTON_CreateEx(460,150,10,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        buttonPausePos.btnHandle = BUTTON_CreateEx(10,200,450,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        PausePosArrow.btnHandle = BUTTON_CreateEx(460,200,10,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        BUTTON_SetBmpFileName(MachineArrow.btnHandle, "bmp_arrow.bin",1);        
        BUTTON_SetBmpFileName(FirmwareArrow.btnHandle, "bmp_arrow.bin",1);
        BUTTON_SetBmpFileName(BaudRateArrow.btnHandle, "bmp_arrow.bin",1);
        BUTTON_SetBmpFileName(PausePosArrow.btnHandle, "bmp_arrow.bin",1);
        
        BUTTON_SetBmpFileName(buttonMachine.btnHandle,NULL,1);        
        BUTTON_SetBmpFileName(buttonFirmware.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(buttonBaudRate.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(buttonPausePos.btnHandle,NULL,1);
        
        BUTTON_SetBitmapEx(MachineArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
        BUTTON_SetBitmapEx(FirmwareArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
        BUTTON_SetBitmapEx(BaudRateArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
        BUTTON_SetBitmapEx(PausePosArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12); 
        
        BUTTON_SetTextAlign(buttonMachine.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(buttonFirmware.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(buttonBaudRate.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(buttonPausePos.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   

        button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hMachineSettingsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
    
        BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);
        

    }
    else
    {
        buttonFilament.btnHandle = BUTTON_CreateEx(10,50,450,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        FilamentArrow.btnHandle = BUTTON_CreateEx(460,50,10,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

		 buttonLeveling.btnHandle = BUTTON_CreateEx(10,100,450,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        LevelingArrow.btnHandle = BUTTON_CreateEx(460,100,10,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

//		buttonWifi.btnHandle = BUTTON_CreateEx(10,150,450,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//        WifiConfArrow.btnHandle = BUTTON_CreateEx(460,150,10,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
//		buttonFilesys.btnHandle = BUTTON_CreateEx(10,200,450,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//        FilesysArrow.btnHandle = BUTTON_CreateEx(460,200,10,40,hMachineSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        BUTTON_SetBmpFileName(FilamentArrow.btnHandle, "bmp_arrow.bin",1);
        BUTTON_SetBmpFileName(LevelingArrow.btnHandle, "bmp_arrow.bin",1);
//        BUTTON_SetBmpFileName(WifiConfArrow.btnHandle, "bmp_arrow.bin",1);
//        BUTTON_SetBmpFileName(FilesysArrow.btnHandle, "bmp_arrow.bin",1);

		BUTTON_SetBmpFileName(buttonFilament.btnHandle,NULL,1);
		BUTTON_SetBmpFileName(buttonLeveling.btnHandle,NULL,1);  
//		BUTTON_SetBmpFileName(buttonWifi.btnHandle,NULL,1);  
//		BUTTON_SetBmpFileName(buttonFilesys.btnHandle,NULL,1);
		
        BUTTON_SetBitmapEx(FilamentArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);
        BUTTON_SetBitmapEx(LevelingArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12); 
//		BUTTON_SetBitmapEx(WifiConfArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12); 
//		BUTTON_SetBitmapEx(FilesysArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);  
		
        BUTTON_SetTextAlign(buttonFilament.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(buttonLeveling.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER ); 
//	    BUTTON_SetTextAlign(buttonWifi.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
//	 	BUTTON_SetTextAlign(buttonFilesys.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

        button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hMachineSettingsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
        
        BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);
        
    }

     button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hMachineSettingsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
     
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
            BUTTON_SetText(buttonMachine.btnHandle, machine_menu.MachineType);
            BUTTON_SetText(buttonFirmware.btnHandle, machine_menu.FirmwareType);
            BUTTON_SetText(buttonBaudRate.btnHandle, machine_menu.BaudRateConf);
            BUTTON_SetText(buttonPausePos.btnHandle, machine_menu.PausePosConf);
            BUTTON_SetText(button_next.btnHandle,machine_menu.next);
        }
        else
        {
            BUTTON_SetText(buttonFilament.btnHandle,machine_menu.FilamentConf);
            BUTTON_SetText(buttonLeveling.btnHandle, machine_menu.LevelingConf); 			
            BUTTON_SetText(button_previous.btnHandle,machine_menu.previous);   
//			BUTTON_SetText(buttonWifi.btnHandle, machine_menu.WifiConf); 
//			BUTTON_SetText(buttonFilesys.btnHandle, set_menu.filesys); 
        }
        BUTTON_SetText(button_back.btnHandle,machine_menu.back);    
     }

}


void Clear_MachineSettings()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hMachineSettingsWnd))
	{
		WM_DeleteWindow(hMachineSettingsWnd);
	}
}



