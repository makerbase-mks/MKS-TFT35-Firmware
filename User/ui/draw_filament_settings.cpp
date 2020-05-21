#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hFilamentSettingsWnd;
static BUTTON_STRUCT InTemperature_text,InSpeed_text,InLength_text;
static BUTTON_STRUCT OutSpeed_text,OutLength_text;
static BUTTON_STRUCT InTemperature_value,InSpeed_value,InLength_value;
static BUTTON_STRUCT OutSpeed_value,OutLength_value;
static BUTTON_STRUCT InTemperature_default,InSpeed_default,InLength_default;
static BUTTON_STRUCT OutSpeed_default,OutLength_default;
static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void btnHandle_rest()
{
    InTemperature_text.btnHandle = 0;
    InSpeed_text.btnHandle = 0;
    InLength_text.btnHandle = 0;
    OutSpeed_text.btnHandle = 0;
    OutLength_text.btnHandle = 0;
    InTemperature_value.btnHandle = 0;
    InSpeed_value.btnHandle = 0;
    InLength_value.btnHandle = 0;
    OutSpeed_value.btnHandle = 0;
    OutLength_value.btnHandle = 0;
    InTemperature_default.btnHandle = 0;   
    InSpeed_default.btnHandle = 0;
    InLength_default.btnHandle = 0;    
    OutSpeed_default.btnHandle = 0;
    OutLength_default.btnHandle = 0;       
    button_previous.btnHandle = 0;
    button_next.btnHandle = 0;
    button_back.btnHandle = 0;
}

static void cbFilamentSettingsWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(0xff5449);

			GUI_FillRect(10, 90, 470,90);

            if(current_page != 1)
            {           

			GUI_FillRect(10, 140, 470,140);        
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
    				last_disp_state = FILAMENT_SETTINGS_UI;
    				Clear_FilamentSettings();
    				draw_return_ui();
    			}	
                else if(pMsg->hWinSrc == button_next.btnHandle)
                {
                    current_page = 1;
                    last_disp_state = FILAMENT_SETTINGS_UI;
                    Clear_FilamentSettings();
                    draw_FilamentSettings();
                }
                else if(pMsg->hWinSrc == button_previous.btnHandle)
                {
                    current_page = 0;
                    last_disp_state = FILAMENT_SETTINGS_UI;
                    Clear_FilamentSettings();
                    draw_FilamentSettings();
                }                
    			else if(pMsg->hWinSrc == InTemperature_value.btnHandle)
    			{
    				last_disp_state = FILAMENT_SETTINGS_UI;
    				Clear_FilamentSettings();
    				value=Load_Temper_limit;
                    draw_NumberKey();
    			}
    			else if(pMsg->hWinSrc == InSpeed_value.btnHandle)

    			{
    				last_disp_state = FILAMENT_SETTINGS_UI;
    				Clear_FilamentSettings();
    				value=Load_Speed;
                    draw_NumberKey();                    
    				
    			}
    			else if(pMsg->hWinSrc == InLength_value.btnHandle)

    			{
    				last_disp_state = FILAMENT_SETTINGS_UI;
    				Clear_FilamentSettings();
     				value=Load_Length;
                    draw_NumberKey();                   
    		
    			}       
//    			else if(pMsg->hWinSrc == OutTemperature_value.btnHandle)
//
//    			{
//    				last_disp_state = FILAMENT_SETTINGS_UI;
//    				Clear_FilamentSettings();
//    				value=Unload_Temper_limit;
//                    draw_NumberKey();
//
//
//    			}
    			else if(pMsg->hWinSrc == OutSpeed_value.btnHandle)
    			{
    				last_disp_state = FILAMENT_SETTINGS_UI;
    				Clear_FilamentSettings();
    				value=Unload_Speed;
                    draw_NumberKey();

    			}  
    			else if(pMsg->hWinSrc == OutLength_value.btnHandle)
    			{
    				last_disp_state = FILAMENT_SETTINGS_UI;
    				Clear_FilamentSettings();
    				value=Unload_Length;
                    draw_NumberKey();
    			} 
    			else if(pMsg->hWinSrc == InTemperature_default.btnHandle)
    			{
                    gCfgItems.filament_limit_temper = 200;
                    memset(cmd_code,0,sizeof(cmd_code));
                    sprintf(cmd_code,"%d",gCfgItems.filament_limit_temper);
                    BUTTON_SetText(InTemperature_value.btnHandle,cmd_code);
//                    epr_write_data(EPR_FILAMENT_LOAD_LIMIT_TEMPER, (uint8_t *)&gCfgItems.filament_load_limit_temper,sizeof(uint32_t));
					HAL::AT24CXX_Write(BAK_FILAMENT_LIMIT_TERMPER_ADDR,(uint8_t *)&gCfgItems.filament_limit_temper,2); 
    			}  
    			else if(pMsg->hWinSrc == InSpeed_default.btnHandle)
    			{
                    gCfgItems.filament_load_speed = 1000;
                    memset(cmd_code,0,sizeof(cmd_code));
                    sprintf(cmd_code,"%d",gCfgItems.filament_load_speed);
                    BUTTON_SetText(InSpeed_value.btnHandle,cmd_code);
//                    epr_write_data(EPR_FILAMENT_LOAD_SPEED, (uint8_t *)&gCfgItems.filament_load_speed,sizeof(uint32_t));
                    gCfgItems.filament_loading_time = (uint32_t)((gCfgItems.filament_load_length*60.0/gCfgItems.filament_load_speed)+0.5);
					HAL::AT24CXX_Write(BAK_FILAMENT_LOAD_SPEED_ADDR,(uint8_t *)&gCfgItems.filament_load_speed,2);	
				} 
    			else if(pMsg->hWinSrc == InLength_default.btnHandle)
    			{
                    gCfgItems.filament_load_length = 100;
                    memset(cmd_code,0,sizeof(cmd_code));
                    sprintf(cmd_code,"%d",gCfgItems.filament_load_length);
                    BUTTON_SetText(InLength_value.btnHandle,cmd_code);
//                    epr_write_data(EPR_FILAMENT_LOAD_LENGTH, (uint8_t *)&gCfgItems.filament_load_length,sizeof(uint32_t));
                    gCfgItems.filament_loading_time = (uint32_t)((gCfgItems.filament_load_length*60.0/gCfgItems.filament_load_speed)+0.5);
					HAL::AT24CXX_Write(BAK_FILAMENT_LOAD_LENGTH_ADDR,(uint8_t *)&gCfgItems.filament_load_length,2); 				
				}   
//    			else if(pMsg->hWinSrc == OutTemperature_default.btnHandle)
//    			{
//                    gCfgItems.filament_unload_limit_temper = 200;
//                    memset(cmd_code,0,sizeof(cmd_code));
//                    sprintf(cmd_code,"%d",gCfgItems.filament_unload_limit_temper);
//                    BUTTON_SetText(OutTemperature_value.btnHandle,cmd_code);
////                    epr_write_data(EPR_FILAMENT_UNLOAD_LIMIT_TEMPER, (uint8_t *)&gCfgItems.filament_unload_limit_temper,sizeof(uint32_t));
////					HAL::AT24CXX_Write(BAK_FILAMENT_LIMIT_TERMPER_ADDR,(uint8_t *)&gCfgItems.filament_limit_temper,2); 
//
//    			}  
    			else if(pMsg->hWinSrc == OutSpeed_default.btnHandle)
    			{
                    gCfgItems.filament_unload_speed = 1000;
                    memset(cmd_code,0,sizeof(cmd_code));
                    sprintf(cmd_code,"%d",gCfgItems.filament_unload_speed);
                    BUTTON_SetText(OutSpeed_default.btnHandle,cmd_code);
//                    epr_write_data(EPR_FILAMENT_UNLOAD_SPEED, (uint8_t *)&gCfgItems.filament_unload_speed,sizeof(uint32_t));
                    gCfgItems.filament_unloading_time = (uint32_t)((gCfgItems.filament_unload_length*60.0/gCfgItems.filament_unload_speed)+0.5);
					HAL::AT24CXX_Write(BAK_FILAMENT_UNLOAD_SPEED_ADDR,(uint8_t *)&gCfgItems.filament_unload_speed,2);	

				} 
    			else if(pMsg->hWinSrc == OutLength_default.btnHandle)
    			{
                    gCfgItems.filament_unload_length = 100;
                    memset(cmd_code,0,sizeof(cmd_code));
                    sprintf(cmd_code,"%d",gCfgItems.filament_unload_length);
                    BUTTON_SetText(OutLength_value.btnHandle,cmd_code);
//                    epr_write_data(EPR_FILAMENT_UNLOAD_LENGTH, (uint8_t *)&gCfgItems.filament_unload_length,sizeof(uint32_t));
             		gCfgItems.filament_unloading_time = (uint32_t)((gCfgItems.filament_unload_length*60.0/gCfgItems.filament_unload_speed)+0.5);
					HAL::AT24CXX_Write(BAK_FILAMENT_UNLOAD_LENGTH_ADDR,(uint8_t *)&gCfgItems.filament_unload_length,2); 

				}                   
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_FilamentSettings()
{   
    btnHandle_rest();
    
    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != FILAMENT_SETTINGS_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = FILAMENT_SETTINGS_UI;
    }
    disp_state = FILAMENT_SETTINGS_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.FilamentConfTitle, TITLE_XPOS, TITLE_YPOS);

    hFilamentSettingsWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbFilamentSettingsWin, 0);

    if(current_page != 1)
    {
        InTemperature_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        InTemperature_value.btnHandle = BUTTON_CreateEx(320,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        InTemperature_default.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        InSpeed_text.btnHandle = BUTTON_CreateEx(10,100,240,40,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        InSpeed_value.btnHandle = BUTTON_CreateEx(320,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        InSpeed_default.btnHandle = BUTTON_CreateEx(400,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        InLength_text.btnHandle = BUTTON_CreateEx(10,150,240,40,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        InLength_value.btnHandle = BUTTON_CreateEx(320,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        InLength_default.btnHandle = BUTTON_CreateEx(400,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        OutSpeed_text.btnHandle = BUTTON_CreateEx(10,200,240,40,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        OutSpeed_value.btnHandle = BUTTON_CreateEx(320,200+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        OutSpeed_default.btnHandle = BUTTON_CreateEx(400,200+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        BUTTON_SetBmpFileName(InTemperature_value.btnHandle, "bmp_pic70x28_1.bin",1);        
        BUTTON_SetBmpFileName(InTemperature_default.btnHandle, "bmp_pic70x28_2.bin",1);
        BUTTON_SetBmpFileName(InLength_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(InLength_default.btnHandle, "bmp_pic70x28_2.bin",1);
        BUTTON_SetBmpFileName(InSpeed_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(InSpeed_default.btnHandle, "bmp_pic70x28_2.bin",1);     
        BUTTON_SetBmpFileName(OutSpeed_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(OutSpeed_default.btnHandle, "bmp_pic70x28_2.bin",1);  
        
        BUTTON_SetBmpFileName(InTemperature_text.btnHandle,NULL,1);        
        BUTTON_SetBmpFileName(InLength_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(InSpeed_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(OutSpeed_text.btnHandle,NULL,1);
        
        BUTTON_SetBitmapEx(InTemperature_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(InTemperature_default.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(InLength_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(InLength_default.btnHandle,0,&bmp_struct70X28,0,0); 
        BUTTON_SetBitmapEx(InSpeed_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(InSpeed_default.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(OutSpeed_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(OutSpeed_default.btnHandle,0,&bmp_struct70X28,0,0); 

        
        BUTTON_SetTextAlign(InTemperature_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(InLength_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(InSpeed_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(OutSpeed_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   

        BUTTON_SetTextAlign(InTemperature_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(InLength_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(InSpeed_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(OutSpeed_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

        BUTTON_SetTextAlign(InTemperature_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(InLength_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(InSpeed_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(OutSpeed_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );        

        button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hFilamentSettingsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
    
        BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);

         BUTTON_SetBkColor(InTemperature_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
         BUTTON_SetBkColor(InTemperature_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
         BUTTON_SetTextColor(InTemperature_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
         BUTTON_SetTextColor(InTemperature_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 
        
         BUTTON_SetBkColor(InLength_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
         BUTTON_SetBkColor(InLength_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
         BUTTON_SetTextColor(InLength_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
         BUTTON_SetTextColor(InLength_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);
            
        BUTTON_SetBkColor(InSpeed_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(InSpeed_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(InSpeed_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(InSpeed_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 
        
        BUTTON_SetBkColor(OutSpeed_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(OutSpeed_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(OutSpeed_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(OutSpeed_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);
        


        BUTTON_SetBkColor(InTemperature_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
        BUTTON_SetBkColor(InTemperature_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
        BUTTON_SetTextColor(InTemperature_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
        BUTTON_SetTextColor(InTemperature_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color); 

        BUTTON_SetBkColor(InLength_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
        BUTTON_SetBkColor(InLength_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
        BUTTON_SetTextColor(InLength_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
        BUTTON_SetTextColor(InLength_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);
           
       BUTTON_SetBkColor(InSpeed_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
       BUTTON_SetBkColor(InSpeed_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
       BUTTON_SetTextColor(InSpeed_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
       BUTTON_SetTextColor(InSpeed_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color); 
       
       BUTTON_SetBkColor(OutSpeed_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
       BUTTON_SetBkColor(OutSpeed_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
       BUTTON_SetTextColor(OutSpeed_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
       BUTTON_SetTextColor(OutSpeed_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.filament_limit_temper);
        BUTTON_SetText(InTemperature_value.btnHandle,cmd_code);     
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.filament_load_speed);
        BUTTON_SetText(InSpeed_value.btnHandle,cmd_code); 
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.filament_load_length);
        BUTTON_SetText(InLength_value.btnHandle,cmd_code);        
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.filament_unload_speed);
        BUTTON_SetText(OutSpeed_value.btnHandle,cmd_code);  

    }
    else
    {
        OutLength_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        OutLength_value.btnHandle = BUTTON_CreateEx(320,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        OutLength_default.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

//        OutLength_text.btnHandle = BUTTON_CreateEx(10,100,240,40,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//        OutLength_value.btnHandle = BUTTON_CreateEx(320,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//        OutLength_default.btnHandle = BUTTON_CreateEx(400,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hFilamentSettingsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        BUTTON_SetBmpFileName(OutLength_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(OutLength_default.btnHandle, "bmp_pic70x28_2.bin",1);
//        BUTTON_SetBmpFileName(OutLength_value.btnHandle, "bmp_pic70x28_1.bin",1);
//        BUTTON_SetBmpFileName(OutLength_default.btnHandle, "bmp_pic70x28_1.bin",1);
        
        BUTTON_SetBmpFileName(OutLength_text.btnHandle,NULL,1);
//        BUTTON_SetBmpFileName(OutLength_text.btnHandle,NULL,1);  
        
        BUTTON_SetBitmapEx(OutLength_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(OutLength_default.btnHandle,0,&bmp_struct70X28,0,0); 
//        BUTTON_SetBitmapEx(OutLength_value.btnHandle,0,&bmp_struct70X28,0,0);
//        BUTTON_SetBitmapEx(OutLength_default.btnHandle,0,&bmp_struct70X28,0,0); 
        
        BUTTON_SetTextAlign(OutLength_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
//        BUTTON_SetTextAlign(OutLength_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   

        BUTTON_SetTextAlign(OutLength_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
//        BUTTON_SetTextAlign(OutLength_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
//        BUTTON_SetTextAlign(OutLength_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(OutLength_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
 
       
        button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hFilamentSettingsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
        
        BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);

        BUTTON_SetBkColor(OutLength_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(OutLength_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(OutLength_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(OutLength_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

//        BUTTON_SetBkColor(OutLength_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
//        BUTTON_SetBkColor(OutLength_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
//        BUTTON_SetTextColor(OutLength_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
//        BUTTON_SetTextColor(OutLength_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);
//
//        BUTTON_SetBkColor(OutLength_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
//        BUTTON_SetBkColor(OutLength_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
//        BUTTON_SetTextColor(OutLength_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
//        BUTTON_SetTextColor(OutLength_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color); 

        BUTTON_SetBkColor(OutLength_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
        BUTTON_SetBkColor(OutLength_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
        BUTTON_SetTextColor(OutLength_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
        BUTTON_SetTextColor(OutLength_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);
                
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%d",gCfgItems.filament_unload_speed);
//        BUTTON_SetText(OutLength_value.btnHandle,cmd_code); 
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.filament_unload_length);
        BUTTON_SetText(OutLength_value.btnHandle,cmd_code);              
    }

     button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hFilamentSettingsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
     
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

            BUTTON_SetText(InTemperature_text.btnHandle, machine_menu.InTemperature);
            BUTTON_SetText(InSpeed_text.btnHandle, machine_menu.InSpeed);
            BUTTON_SetText(InLength_text.btnHandle, machine_menu.InLength);
//            BUTTON_SetText(OutTemperature_text.btnHandle, machine_menu.OutTemperature);
            BUTTON_SetText(button_next.btnHandle,machine_menu.next);

            BUTTON_SetText(InTemperature_default.btnHandle, machine_menu.default_value);
            BUTTON_SetText(InSpeed_default.btnHandle, machine_menu.default_value);
            BUTTON_SetText(InLength_default.btnHandle, machine_menu.default_value);
//            BUTTON_SetText(OutTemperature_default.btnHandle, machine_menu.default_value);
            BUTTON_SetText(OutSpeed_text.btnHandle,machine_menu.OutSpeed);
			BUTTON_SetText(OutSpeed_default.btnHandle, machine_menu.default_value);

        }
        else
        {

            BUTTON_SetText(OutLength_text.btnHandle, machine_menu.OutLength); 
            BUTTON_SetText(button_previous.btnHandle,machine_menu.previous);   
            BUTTON_SetText(OutLength_default.btnHandle, machine_menu.default_value);            
        }
         
        BUTTON_SetText(button_back.btnHandle,machine_menu.back);
        
              
     }
}

void Clear_FilamentSettings()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hFilamentSettingsWnd))
	{
		WM_DeleteWindow(hFilamentSettingsWnd);
	}
}




