#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hTemperatureSettingsWnd;
static BUTTON_STRUCT NozzleCnt_text,NozzleMaxT_text,HotBedEnable_text,HotBedMaxT_text;
static BUTTON_STRUCT NozzleCnt_value,NozzleMaxT_value,HotBedEnable_sel,HotBedMaxT_value;
static BUTTON_STRUCT NozzleMaxT_default,HotBedMaxT_default,NozzleCnt_default;
static BUTTON_STRUCT button_back;


static void cbTemperatureSettingsWin(WM_MESSAGE * pMsg) {

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
            GUI_FillRect(10, 190, 470,190);
            GUI_FillRect(10, 240, 470,240);
 
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
    				last_disp_state = TEMPERATURE_SETTINGS_UI;
    				Clear_TemperatureSettings();
    				draw_return_ui();
    			}	
				else if(pMsg->hWinSrc == NozzleCnt_value.btnHandle)
                {
                    value=Nozzle_Cnt;
                    last_disp_state = TEMPERATURE_SETTINGS_UI;
                    Clear_TemperatureSettings();                    
                    draw_NumberKey();
                }
    			else if(pMsg->hWinSrc == NozzleMaxT_value.btnHandle)
    			{
                    value=Nozzle_max;
                    last_disp_state = TEMPERATURE_SETTINGS_UI;
                    Clear_TemperatureSettings();                    
                    draw_NumberKey();
    			}
				else if(pMsg->hWinSrc == NozzleMaxT_default.btnHandle)
    			{
                    last_disp_state = TEMPERATURE_SETTINGS_UI;
					gCfgItems.preheat_max_desireSprayerTemp=270;	
					HAL::AT24CXX_Write(BAK_SPRAYER1_MAXTEMP_ADDR,(uint8_t *)&gCfgItems.preheat_max_desireSprayerTemp,2);	
					memset(cmd_code,0,sizeof(cmd_code));
//					if((gCfgItems.language == LANG_SIMPLE_CHINESE)||(gCfgItems.language == LANG_COMPLEX_CHINESE))
						sprintf(cmd_code,"%d",gCfgItems.preheat_max_desireSprayerTemp);
//					else
//						sprintf(cmd_code,TEMP_UNIT_SYBOL,gCfgItems.preheat_max_desireSprayerTemp);
					BUTTON_SetText(NozzleMaxT_value.btnHandle,cmd_code);	
    			}
				else if(pMsg->hWinSrc == NozzleCnt_default.btnHandle)
    			{
                    last_disp_state = TEMPERATURE_SETTINGS_UI;
					gCfgItems.sprayerNum=1;
				  HAL::AT24CXX_Write(BAK_SPRAYER_NUM_ADDR,(uint8_t *)&gCfgItems.sprayerNum,1);
				  memset(cmd_code,0,sizeof(cmd_code));
				  sprintf(cmd_code,"%d",gCfgItems.sprayerNum);
				  BUTTON_SetText(NozzleCnt_value.btnHandle,cmd_code);   
    			}	

				else if(pMsg->hWinSrc == HotBedMaxT_value.btnHandle)
				{
					if(gCfgItems.custom_bed_flag == 1)
					{
						last_disp_state = TEMPERATURE_SETTINGS_UI;
						Clear_TemperatureSettings();
						value=HotBed_max;				 
						draw_NumberKey();
					}
				} 
				else if(pMsg->hWinSrc == HotBedMaxT_default.btnHandle)
    			{
                    last_disp_state = TEMPERATURE_SETTINGS_UI;
					gCfgItems.preheat_max_desireBedTemp=150;	
					HAL::AT24CXX_Write(BAK_BED_MAXTEMP_ADDR,(uint8_t *)&gCfgItems.preheat_max_desireBedTemp,2); 	
					memset(cmd_code,0,sizeof(cmd_code));
//					if((gCfgItems.language == LANG_SIMPLE_CHINESE)||(gCfgItems.language == LANG_COMPLEX_CHINESE))
						sprintf(cmd_code,"%d",gCfgItems.preheat_max_desireBedTemp);
//					else
//						sprintf(cmd_code,TEMP_UNIT_SYBOL,gCfgItems.preheat_max_desireBedTemp);
					BUTTON_SetText(HotBedMaxT_value.btnHandle,cmd_code);	
    			}
				 else if(pMsg->hWinSrc == HotBedEnable_sel.btnHandle)
				{
					if(gCfgItems.custom_bed_flag == 1)
					{
						gCfgItems.custom_bed_flag = 0;
						BUTTON_SetBmpFileName(HotBedEnable_sel.btnHandle, "bmp_disable.bin",1);
						BUTTON_SetBmpFileName(HotBedMaxT_value.btnHandle, "bmp_pic70x28.bin",1);
						if(gCfgItems.multiple_language != 0)
							BUTTON_SetText(HotBedEnable_sel.btnHandle,machine_menu.disable);
		
						BUTTON_SetBkColor(HotBedMaxT_value.btnHandle, BUTTON_CI_PRESSED, 0x8f8f8f);
						BUTTON_SetBkColor(HotBedMaxT_value.btnHandle, BUTTON_CI_UNPRESSED, 0x8f8f8f); 
						BUTTON_SetTextColor(HotBedMaxT_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
						BUTTON_SetTextColor(HotBedMaxT_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);
					}
					else
					{
						gCfgItems.custom_bed_flag	= 1;						
						BUTTON_SetBmpFileName(HotBedEnable_sel.btnHandle, "bmp_enable.bin",1);  
						BUTTON_SetBmpFileName(HotBedMaxT_value.btnHandle, "bmp_pic70x28_1.bin",1);
						if(gCfgItems.multiple_language != 0)
								BUTTON_SetText(HotBedEnable_sel.btnHandle,machine_menu.enable);	
						
						 BUTTON_SetBkColor(HotBedMaxT_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
						 BUTTON_SetBkColor(HotBedMaxT_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
						 BUTTON_SetTextColor(HotBedMaxT_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
						 BUTTON_SetTextColor(HotBedMaxT_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);
					}						
					HAL::AT24CXX_Write(BAK_CUSTOM_BED_FLAG_ADDR,(uint8_t *)&gCfgItems.custom_bed_flag,1);
				}

				
                #if 0
    			else if((pMsg->hWinSrc == buttonpreTemperatureSetting.btnHandle)||
                    (pMsg->hWinSrc == preTemperatureSettingArrow.btnHandle))

    			{
    				last_disp_state = TEMPERATURE_SETTINGS_UI;
    				Clear_TemperatureSettings();
    		
    			}   
                #endif
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_TemperatureSettings()
{   
    int i;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != TEMPERATURE_SETTINGS_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = TEMPERATURE_SETTINGS_UI;
    }
    disp_state = TEMPERATURE_SETTINGS_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.TemperatureConfTitle, TITLE_XPOS, TITLE_YPOS);

    hTemperatureSettingsWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbTemperatureSettingsWin, 0);


	NozzleCnt_text.btnHandle = BUTTON_CreateEx(10,50,300,40,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	NozzleCnt_value.btnHandle = BUTTON_CreateEx(320,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	NozzleCnt_default.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	NozzleMaxT_text.btnHandle = BUTTON_CreateEx(10,100,300,40,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	NozzleMaxT_value.btnHandle = BUTTON_CreateEx(320,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	NozzleMaxT_default.btnHandle = BUTTON_CreateEx(400,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	
	HotBedEnable_text.btnHandle = BUTTON_CreateEx(10,150,300,40,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//	NozzleCnt_value.btnHandle = BUTTON_CreateEx(320,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	HotBedEnable_sel.btnHandle = BUTTON_CreateEx(370,150,90,40,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	HotBedMaxT_text.btnHandle = BUTTON_CreateEx(10,200,300,40,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	HotBedMaxT_value.btnHandle = BUTTON_CreateEx(320,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	HotBedMaxT_default.btnHandle = BUTTON_CreateEx(400,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hTemperatureSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	

	BUTTON_SetBmpFileName(NozzleCnt_value.btnHandle, "bmp_pic70x28_1.bin",1);
	BUTTON_SetBmpFileName(NozzleMaxT_value.btnHandle, "bmp_pic70x28_1.bin",1);

	if (gCfgItems.custom_bed_flag == 1)
	{
		BUTTON_SetBmpFileName(HotBedMaxT_value.btnHandle, "bmp_pic70x28_1.bin",1);
		BUTTON_SetBmpFileName(HotBedEnable_sel.btnHandle, "bmp_enable.bin",1);
	}
	else 
	{
		BUTTON_SetBmpFileName(HotBedMaxT_value.btnHandle, "bmp_pic70x28.bin",1);
		BUTTON_SetBmpFileName(HotBedEnable_sel.btnHandle, "bmp_disable.bin",1);
	}
			
	BUTTON_SetBmpFileName(NozzleCnt_default.btnHandle, "bmp_pic70x28_2.bin",1);
	BUTTON_SetBmpFileName(NozzleMaxT_default.btnHandle, "bmp_pic70x28_2.bin",1);
	BUTTON_SetBmpFileName(HotBedMaxT_default.btnHandle, "bmp_pic70x28_2.bin",1);	
	     
    BUTTON_SetBmpFileName(NozzleCnt_text.btnHandle,NULL,1);
    BUTTON_SetBmpFileName(NozzleMaxT_text.btnHandle,NULL,1);
    BUTTON_SetBmpFileName(HotBedMaxT_text.btnHandle,NULL,1);
    BUTTON_SetBmpFileName(HotBedEnable_text.btnHandle,NULL,1);	
	
	    BUTTON_SetBitmapEx(NozzleCnt_value.btnHandle,0,&bmp_struct70X28,0,0); 
	    BUTTON_SetBitmapEx(NozzleMaxT_value.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(HotBedMaxT_value.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(HotBedEnable_sel.btnHandle,0,&bmp_struct90X30,0,5);
		
	    BUTTON_SetBitmapEx(NozzleCnt_default.btnHandle,0,&bmp_struct70X28,0,0); 
	    BUTTON_SetBitmapEx(NozzleMaxT_default.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(HotBedMaxT_default.btnHandle,0,&bmp_struct70X28,0,0);
	    
	    BUTTON_SetTextAlign(NozzleCnt_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(NozzleMaxT_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(HotBedMaxT_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(HotBedEnable_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER ); 
        
	    BUTTON_SetTextAlign(NozzleCnt_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(NozzleMaxT_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(HotBedMaxT_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(HotBedEnable_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		
	    BUTTON_SetTextAlign(NozzleCnt_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(NozzleMaxT_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(HotBedMaxT_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

        BUTTON_SetBkColor(NozzleCnt_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(NozzleCnt_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(NozzleCnt_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(NozzleCnt_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(NozzleMaxT_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(NozzleMaxT_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(NozzleMaxT_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(NozzleMaxT_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		if( gCfgItems.custom_bed_flag == 1 )
		{
			BUTTON_SetBkColor(HotBedMaxT_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
			BUTTON_SetBkColor(HotBedMaxT_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
			BUTTON_SetTextColor(HotBedMaxT_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
			BUTTON_SetTextColor(HotBedMaxT_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 	
		}
		else 
		{
			BUTTON_SetBkColor(HotBedMaxT_value.btnHandle, BUTTON_CI_PRESSED, 0x8f8f8f);
			BUTTON_SetBkColor(HotBedMaxT_value.btnHandle, BUTTON_CI_UNPRESSED, 0x8f8f8f); 
			BUTTON_SetTextColor(HotBedMaxT_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
			BUTTON_SetTextColor(HotBedMaxT_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);
		}

		
		
		BUTTON_SetBkColor(NozzleCnt_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
        BUTTON_SetBkColor(NozzleCnt_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
        BUTTON_SetTextColor(NozzleCnt_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
        BUTTON_SetTextColor(NozzleCnt_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color); 
		
        BUTTON_SetBkColor(NozzleMaxT_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
        BUTTON_SetBkColor(NozzleMaxT_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
        BUTTON_SetTextColor(NozzleMaxT_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
        BUTTON_SetTextColor(NozzleMaxT_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color); 	

        BUTTON_SetBkColor(HotBedMaxT_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
        BUTTON_SetBkColor(HotBedMaxT_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
        BUTTON_SetTextColor(HotBedMaxT_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
        BUTTON_SetTextColor(HotBedMaxT_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color); 	

	
        memset(cmd_code,0,sizeof(cmd_code));
		sprintf(cmd_code,"%d",gCfgItems.sprayerNum);
		BUTTON_SetText(NozzleCnt_value.btnHandle,cmd_code);	
		
        memset(cmd_code,0,sizeof(cmd_code));
	 	sprintf(cmd_code,"%d",gCfgItems.preheat_max_desireSprayerTemp);

        BUTTON_SetText(NozzleMaxT_value.btnHandle,cmd_code);
	 
	 	sprintf(cmd_code,"%d",gCfgItems.preheat_max_desireBedTemp);

        BUTTON_SetText(HotBedMaxT_value.btnHandle,cmd_code);	 

		button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hTemperatureSettingsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
			 
	 BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);		 
	 BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0, 0);
		
	 BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	 BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
	 BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	 BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 
	 
	 BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	 if(gCfgItems.multiple_language != 0)
	 {
			BUTTON_SetText(button_back.btnHandle,machine_menu.back);
			BUTTON_SetText(NozzleCnt_text.btnHandle,machine_menu.NozzleCnt);	
			BUTTON_SetText(NozzleMaxT_text.btnHandle,machine_menu.NozzleMaxTemperature);	
			BUTTON_SetText(HotBedEnable_text.btnHandle,machine_menu.HotbedEnable);	
			if(gCfgItems.custom_bed_flag == 1)
				BUTTON_SetText(HotBedEnable_sel.btnHandle,machine_menu.enable);	
			else 				
				BUTTON_SetText(HotBedEnable_sel.btnHandle,machine_menu.disable);	//HotbedEnable

			BUTTON_SetText(HotBedMaxT_text.btnHandle,machine_menu.HotbedMaxTemperature);	

			BUTTON_SetText(NozzleCnt_default.btnHandle,machine_menu.default_value);	
			BUTTON_SetText(HotBedMaxT_default.btnHandle,machine_menu.default_value);	
			BUTTON_SetText(NozzleMaxT_default.btnHandle,machine_menu.default_value);
			
	 }

}

void Clear_TemperatureSettings()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hTemperatureSettingsWnd))
	{
		WM_DeleteWindow(hTemperatureSettingsWnd);
	}
}




