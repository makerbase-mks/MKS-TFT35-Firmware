#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"
#include "spi_flash.h"
#include "pic_manager.h"
#include "mks_tft_com.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hLevelingParaWnd;
static BUTTON_STRUCT ProbeXoffset_text,ProbeYoffset_text,ProbeZoffset_text;
static BUTTON_STRUCT ProbeXYSpeed_text,ProbeZSpeed_text;
static BUTTON_STRUCT ProbeXoffset_value,ProbeYoffset_value,ProbeZoffset_value;
static BUTTON_STRUCT ProbeXYSpeed_value,ProbeZSpeed_value;
static BUTTON_STRUCT AutoLevelEnable_text;
static BUTTON_STRUCT AutoLevelEnable;
static BUTTON_STRUCT z_speed_text,xy_speed_text,z_high_text;
static BUTTON_STRUCT z_speed_value,xy_speed_value,z_high_value;
static BUTTON_STRUCT z_speed_default,xy_speed_default,z_high_default;
static BUTTON_STRUCT auto_LevelCmd_text,auto_Leveling_cmd,auto_LevelCmd_default;



static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void btnHandle_rest()
{
    AutoLevelEnable_text.btnHandle = 0;
    AutoLevelEnable.btnHandle = 0;
    ProbeXoffset_text.btnHandle = 0;
    ProbeYoffset_text.btnHandle = 0;
    ProbeZoffset_text.btnHandle = 0;
    ProbeXYSpeed_text.btnHandle = 0;   
    ProbeZSpeed_text.btnHandle = 0;
    ProbeXoffset_value.btnHandle = 0;
    ProbeYoffset_value.btnHandle = 0;   
    ProbeZoffset_value.btnHandle = 0;
    ProbeXYSpeed_value.btnHandle = 0;    
    ProbeZSpeed_value.btnHandle = 0;   
	  z_speed_text.btnHandle = 0;
	  xy_speed_text.btnHandle = 0;
	  z_high_text.btnHandle = 0;
	  z_speed_value.btnHandle = 0;
	  xy_speed_value.btnHandle = 0;
	  z_high_value.btnHandle = 0;	  
	  z_speed_default.btnHandle = 0;
	  xy_speed_default.btnHandle = 0;
	  z_high_default.btnHandle = 0;


	  auto_LevelCmd_text.btnHandle = 0;
	  auto_Leveling_cmd.btnHandle = 0;
	  auto_LevelCmd_default.btnHandle = 0;

    button_previous.btnHandle = 0;
    button_next.btnHandle = 0;
    button_back.btnHandle = 0;
}

static void cbLevelingParaWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			GUI_SetColor(0xff5449);

			GUI_FillRect(10, 90, 470,90);
			if ((current_page != 1 )||(gCfgItems.firmware_type == 1))
			{
			
	            GUI_FillRect(10, 140, 470,140);
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
    				if(gCfgItems.firmware_type == 1)
					pushFIFO(&gcodeCmdTxFIFO,(unsigned char *)"M500\n");     
    			    current_page = 0;
    				last_disp_state = LEVELING_PARA_UI;
    				Clear_LevelingPara();
    				draw_return_ui();
    			}	
                else if(pMsg->hWinSrc == button_next.btnHandle)
                {
                    current_page = 1;
                    last_disp_state = LEVELING_PARA_UI;
                    Clear_LevelingPara();
                    draw_LevelingPara();
                }
                else if(pMsg->hWinSrc == button_previous.btnHandle)
                {
                    current_page = 0;
                    last_disp_state = LEVELING_PARA_UI;
                    Clear_LevelingPara();
                    draw_LevelingPara();
                }                
    			else if(pMsg->hWinSrc == AutoLevelEnable.btnHandle)
    			{

					if(gCfgItems.leveling_mode == 1)
					{
						gCfgItems.leveling_mode = 0;
                        BUTTON_SetBmpFileName(AutoLevelEnable.btnHandle, "bmp_disable.bin",1);
			 			BUTTON_SetBmpFileName(auto_Leveling_cmd.btnHandle, "bmp_pic70x28.bin",1);
                        if(gCfgItems.multiple_language != 0)
                            BUTTON_SetText(AutoLevelEnable.btnHandle,machine_menu.disable);
					}
					else 
					{
						gCfgItems.leveling_mode = 1;
							BUTTON_SetBmpFileName(AutoLevelEnable.btnHandle, "bmp_enable.bin",1);
						BUTTON_SetBmpFileName(auto_Leveling_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
                        if(gCfgItems.multiple_language != 0)
                            BUTTON_SetText(AutoLevelEnable.btnHandle,machine_menu.enable);
							
					}
					HAL::AT24CXX_Write(BAK_LEVELING_MODE_ADDR,(uint8_t *)&gCfgItems.leveling_mode,1);	
    				
    			}      
    			else if(pMsg->hWinSrc == ProbeXoffset_value.btnHandle)
    			{
    				last_disp_state = LEVELING_PARA_UI;
    				Clear_LevelingPara();
                    value=xoffset;
                    draw_NumberKey();                   
    			}
    			else if(pMsg->hWinSrc == ProbeYoffset_value.btnHandle)
    			{
    				last_disp_state = LEVELING_PARA_UI;
    				Clear_LevelingPara();
                    value=yoffset;
                    draw_NumberKey();

    			}  
    			else if(pMsg->hWinSrc == ProbeZoffset_value.btnHandle)
    			{
    				last_disp_state = LEVELING_PARA_UI;
    				Clear_LevelingPara();
                    value=zoffset;
                    draw_NumberKey();
    			} 
				else if(pMsg->hWinSrc == z_speed_value.btnHandle)
				{
					last_disp_state = LEVELING_PARA_UI;
					Clear_LevelingPara();
					  value=z_speed_level;
					  draw_NumberKey();

				} 
				else if(pMsg->hWinSrc == xy_speed_value.btnHandle)
				{
					last_disp_state = LEVELING_PARA_UI;
					Clear_LevelingPara();
					  value=xy_speed_level;
					  draw_NumberKey();

					}  
				else if(pMsg->hWinSrc == z_high_value.btnHandle)
				{
					last_disp_state = LEVELING_PARA_UI;
					Clear_LevelingPara();
					  value=z_high_level;
					  draw_NumberKey();

				} 

				else if(pMsg->hWinSrc == auto_Leveling_cmd.btnHandle)
				{
					if( gCfgItems.leveling_mode == 1 )
					{
						last_disp_state = LEVELING_PARA_UI;
						Clear_LevelingPara();
						  valueType=auto_levelCmd;
						  draw_Keyboard();
					}
				} 
				else if(pMsg->hWinSrc == z_speed_default.btnHandle)
				{
					  gCfgItems.leveling_z_speed = 1500;
					  memset(cmd_code,0,sizeof(cmd_code));
					  sprintf(cmd_code,"%d",gCfgItems.leveling_z_speed);
					  BUTTON_SetText(z_speed_value.btnHandle,cmd_code);
					  HAL::AT24CXX_Write(BAK_LEVELING_Z_SPEED_ADDR,(uint8_t *)&gCfgItems.leveling_z_speed,2);	
				} 
				else if(pMsg->hWinSrc == xy_speed_default.btnHandle)
				{
					 gCfgItems.leveling_xy_speed = 3000;
					  memset(cmd_code,0,sizeof(cmd_code));
					  sprintf(cmd_code,"%d",gCfgItems.leveling_xy_speed);
					  BUTTON_SetText(xy_speed_value.btnHandle,cmd_code);
					 HAL::AT24CXX_Write(BAK_LEVELING_XY_SPEED_ADDR,(uint8_t *)&gCfgItems.leveling_xy_speed,2);	
				} 
				else if(pMsg->hWinSrc == z_high_default.btnHandle)
				{
					 gCfgItems.leveling_z_high= 10;
					  memset(cmd_code,0,sizeof(cmd_code));
					  sprintf(cmd_code,"%d",gCfgItems.leveling_z_high);
					  BUTTON_SetText(z_high_value.btnHandle,cmd_code);
					HAL::AT24CXX_Read(BAK_LEVELING_Z_HIGH_ADDR,(uint8_t *)&gCfgItems.leveling_z_high,2);
				}  
				else if(pMsg->hWinSrc == auto_LevelCmd_default.btnHandle)
				{
					memset(cmd_code,0,sizeof(cmd_code));
				   strcpy((char*)cmd_code, "G28;G29;");
				   flash_reWriteInf((u8 *)cmd_code,BUTTON_AUTOLEVELING_ADDR,(strlen(cmd_code)+1));
				   BUTTON_SetText(auto_Leveling_cmd.btnHandle, cmd_code);  
				} 
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_LevelingPara()
{   
    int i;


    btnHandle_rest();
    
    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != LEVELING_PARA_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = LEVELING_PARA_UI;
    }
	
    disp_state = LEVELING_PARA_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    GUI_DispStringAt(machine_menu.LevelingSubConfTitle, TITLE_XPOS, TITLE_YPOS);

    hLevelingParaWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbLevelingParaWin, 0);

    if(current_page != 1)
    {
        AutoLevelEnable_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        AutoLevelEnable.btnHandle = BUTTON_CreateEx(370,50,90,40,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	   auto_LevelCmd_text.btnHandle = BUTTON_CreateEx(10,100,240,40,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	   auto_Leveling_cmd.btnHandle = BUTTON_CreateEx(270,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	   auto_LevelCmd_default.btnHandle = BUTTON_CreateEx(370,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	   z_speed_text.btnHandle = BUTTON_CreateEx(10,150,240,40,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	   z_speed_value.btnHandle = BUTTON_CreateEx(270,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	   z_speed_default.btnHandle = BUTTON_CreateEx(370,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	   xy_speed_text.btnHandle = BUTTON_CreateEx(10,200,240,40,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	   xy_speed_value.btnHandle = BUTTON_CreateEx(270,200+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	   xy_speed_default.btnHandle = BUTTON_CreateEx(370,200+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	   
		if(gCfgItems.leveling_mode == 1)
		{
			BUTTON_SetBmpFileName(AutoLevelEnable.btnHandle, "bmp_enable.bin",1);  //bmp_pic70x28
			BUTTON_SetBmpFileName(auto_Leveling_cmd.btnHandle, "bmp_pic70x28_1.bin",1);	
		}        
        else
        {
        	BUTTON_SetBmpFileName(AutoLevelEnable.btnHandle, "bmp_disable.bin",1);
			BUTTON_SetBmpFileName(auto_Leveling_cmd.btnHandle, "bmp_pic70x28.bin",1);
        }
           
		 BUTTON_SetBmpFileName(z_speed_value.btnHandle, "bmp_pic70x28_1.bin",1);        	 
		 BUTTON_SetBmpFileName(xy_speed_value.btnHandle, "bmp_pic70x28_1.bin",1);       

		 BUTTON_SetBmpFileName(z_speed_default.btnHandle, "bmp_pic70x28_2.bin",1); 	
		 BUTTON_SetBmpFileName(xy_speed_default.btnHandle, "bmp_pic70x28_2.bin",1); 
		 BUTTON_SetBmpFileName(auto_LevelCmd_default.btnHandle, "bmp_pic70x28_2.bin",1);

		
		 BUTTON_SetBmpFileName(z_speed_text.btnHandle,NULL,1);
		 BUTTON_SetBmpFileName(xy_speed_text.btnHandle,NULL,1);  
		 BUTTON_SetBmpFileName(AutoLevelEnable_text.btnHandle,NULL,1);	
		 BUTTON_SetBmpFileName(auto_LevelCmd_text.btnHandle,NULL,1);	

		 BUTTON_SetBitmapEx(AutoLevelEnable.btnHandle,0,&bmp_struct90X30,0,5); 
     	BUTTON_SetBitmapEx(z_speed_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(xy_speed_value.btnHandle,0,&bmp_struct70X28,0,0); 
        BUTTON_SetBitmapEx(auto_Leveling_cmd.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(auto_LevelCmd_default.btnHandle,0,&bmp_struct70X28,0,0);
     	BUTTON_SetBitmapEx(z_speed_default.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(xy_speed_default.btnHandle,0,&bmp_struct70X28,0,0); 

        BUTTON_SetTextAlign(AutoLevelEnable_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(z_speed_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   
        BUTTON_SetTextAlign(xy_speed_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(auto_LevelCmd_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER ); 

		BUTTON_SetTextAlign(AutoLevelEnable.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(z_speed_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(xy_speed_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );   
		BUTTON_SetTextAlign(auto_Leveling_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		
		BUTTON_SetTextAlign(z_speed_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(xy_speed_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );	
		BUTTON_SetTextAlign(auto_LevelCmd_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		BUTTON_SetBkColor(auto_Leveling_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
		BUTTON_SetBkColor(auto_Leveling_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
		BUTTON_SetTextColor(auto_Leveling_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
		BUTTON_SetTextColor(auto_Leveling_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

        BUTTON_SetBkColor(z_speed_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(z_speed_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(z_speed_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(z_speed_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 
        
        BUTTON_SetBkColor(xy_speed_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(xy_speed_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(xy_speed_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(xy_speed_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);
		
		BUTTON_SetBkColor(z_speed_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(z_speed_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(z_speed_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(z_speed_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);
		
		BUTTON_SetBkColor(xy_speed_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(xy_speed_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(xy_speed_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(xy_speed_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);
		
		BUTTON_SetBkColor(auto_LevelCmd_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(auto_LevelCmd_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(auto_LevelCmd_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(auto_LevelCmd_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);		

		memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_AUTOLEVELING_ADDR,201);
        BUTTON_SetText(auto_Leveling_cmd.btnHandle,cmd_code);  

		memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_z_speed);
        BUTTON_SetText(z_speed_value.btnHandle,cmd_code);  
		
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_xy_speed);
        BUTTON_SetText(xy_speed_value.btnHandle,cmd_code);   

		button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hLevelingParaWnd,BUTTON_CF_SHOW,0,alloc_win_id());
		BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
		BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);

		BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
		BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
		BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
		BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
		BUTTON_SetTextAlign(button_next.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		if(gCfgItems.multiple_language != 0)
		{
			BUTTON_SetText(z_speed_text.btnHandle,machine_menu.leveling_z_speed);
			BUTTON_SetText(xy_speed_text.btnHandle, machine_menu.leveling_xy_speed); 
			BUTTON_SetText(AutoLevelEnable_text.btnHandle, machine_menu.AutoLevelEnable);
			BUTTON_SetText(auto_LevelCmd_text.btnHandle, machine_menu.AutoLevelCmd);
			BUTTON_SetText(auto_LevelCmd_default.btnHandle, machine_menu.default_value);
			BUTTON_SetText(z_speed_default.btnHandle, machine_menu.default_value);
			BUTTON_SetText(xy_speed_default.btnHandle, machine_menu.default_value);
			BUTTON_SetText(button_next.btnHandle,machine_menu.next);
			 if(gCfgItems.leveling_mode == 1)
                BUTTON_SetText(AutoLevelEnable.btnHandle,machine_menu.enable);
            else
                BUTTON_SetText(AutoLevelEnable.btnHandle,machine_menu.disable);
		}

    }
    else
    {
    
        z_high_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        z_high_value.btnHandle = BUTTON_CreateEx(270,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        z_high_default.btnHandle = BUTTON_CreateEx(370,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		if(gCfgItems.firmware_type == 1)
		{
			ProbeXoffset_text.btnHandle = BUTTON_CreateEx(10,100,240,40,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
			ProbeXoffset_value.btnHandle = BUTTON_CreateEx(370,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
			
			ProbeYoffset_text.btnHandle = BUTTON_CreateEx(10,150,240,40,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
			ProbeYoffset_value.btnHandle = BUTTON_CreateEx(370,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	
			ProbeZoffset_text.btnHandle = BUTTON_CreateEx(10,200,240,40,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
			ProbeZoffset_value.btnHandle = BUTTON_CreateEx(370,200+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hLevelingParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	        BUTTON_SetBmpFileName(ProbeXoffset_value.btnHandle, "bmp_pic70x28_1.bin",1);
	        BUTTON_SetBmpFileName(ProbeYoffset_value.btnHandle, "bmp_pic70x28_1.bin",1);
	        BUTTON_SetBmpFileName(ProbeZoffset_value.btnHandle, "bmp_pic70x28_1.bin",1);	
			
	        BUTTON_SetBmpFileName(ProbeYoffset_text.btnHandle,NULL,1);
	        BUTTON_SetBmpFileName(ProbeZoffset_text.btnHandle,NULL,1);  
	        BUTTON_SetBmpFileName(ProbeXoffset_text.btnHandle,NULL,1);		

			BUTTON_SetBitmapEx(ProbeXoffset_value.btnHandle,0,&bmp_struct70X28,0,0);
			BUTTON_SetBitmapEx(ProbeYoffset_value.btnHandle,0,&bmp_struct70X28,0,0); 
			BUTTON_SetBitmapEx(ProbeZoffset_value.btnHandle,0,&bmp_struct70X28,0,0); 	


			BUTTON_SetTextAlign(ProbeXoffset_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
			BUTTON_SetTextAlign(ProbeYoffset_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   
			BUTTON_SetTextAlign(ProbeZoffset_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER ); 
			BUTTON_SetTextAlign(ProbeXoffset_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
			BUTTON_SetTextAlign(ProbeYoffset_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );   
			BUTTON_SetTextAlign(ProbeZoffset_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

			BUTTON_SetBkColor(ProbeXoffset_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
			BUTTON_SetBkColor(ProbeXoffset_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
			BUTTON_SetTextColor(ProbeXoffset_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
			BUTTON_SetTextColor(ProbeXoffset_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

			BUTTON_SetBkColor(ProbeYoffset_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
			BUTTON_SetBkColor(ProbeYoffset_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
			BUTTON_SetTextColor(ProbeYoffset_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
			BUTTON_SetTextColor(ProbeYoffset_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

			BUTTON_SetBkColor(ProbeZoffset_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
			BUTTON_SetBkColor(ProbeZoffset_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
			BUTTON_SetTextColor(ProbeZoffset_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
			BUTTON_SetTextColor(ProbeZoffset_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 
			disp_probeOffset();  
			if(gCfgItems.multiple_language != 0)
			{			
				BUTTON_SetText(ProbeXoffset_text.btnHandle,machine_menu.ProbeXoffset);
				BUTTON_SetText(ProbeYoffset_text.btnHandle, machine_menu.ProbeYoffset); 
				BUTTON_SetText(ProbeZoffset_text.btnHandle, machine_menu.ProbeZoffset); 		   
			}
		}
		
		BUTTON_SetBmpFileName(z_high_value.btnHandle, "bmp_pic70x28_1.bin",1);
		BUTTON_SetBmpFileName(z_high_default.btnHandle, "bmp_pic70x28_2.bin",1); 

		
		BUTTON_SetBmpFileName(z_high_text.btnHandle,NULL,1);

		
        BUTTON_SetBitmapEx(z_high_value.btnHandle,0,&bmp_struct70X28,0,0);	
        BUTTON_SetBitmapEx(z_high_default.btnHandle,0,&bmp_struct70X28,0,0);	
	
		
        BUTTON_SetTextAlign(z_high_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER ); 
		BUTTON_SetTextAlign(z_high_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(z_high_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );


		BUTTON_SetBkColor(z_high_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
		BUTTON_SetBkColor(z_high_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
		BUTTON_SetTextColor(z_high_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
		BUTTON_SetTextColor(z_high_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 


		BUTTON_SetBkColor(z_high_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(z_high_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(z_high_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(z_high_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

		memset(cmd_code,0,sizeof(cmd_code));
		sprintf(cmd_code,"%d",gCfgItems.leveling_z_high);
		BUTTON_SetText(z_high_value.btnHandle,cmd_code);	
		

		button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hLevelingParaWnd,BUTTON_CF_SHOW,0,alloc_win_id());
		BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
		BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);

		BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
		BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
		BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
		BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
		BUTTON_SetTextAlign(button_previous.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		if(gCfgItems.multiple_language != 0)
		{	
			BUTTON_SetText(z_high_text.btnHandle,machine_menu.leveling_z_high);
			BUTTON_SetText(z_high_default.btnHandle,machine_menu.default_value);
			BUTTON_SetText(button_previous.btnHandle,machine_menu.previous);		 		   
		}
    }

     button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hLevelingParaWnd,BUTTON_CF_SHOW,0,alloc_win_id());
     
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
              
     }

}


void Clear_LevelingPara()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hLevelingParaWnd))
	{
		WM_DeleteWindow(hLevelingParaWnd);
	}
}

void disp_probeOffset()
{
	if(gCfgItems.firmware_type == 1)
	{
		if(current_page == 1)
		{
			memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%.1f",gCfgItems.xProbeOffset);
			BUTTON_SetText(ProbeXoffset_value.btnHandle,cmd_code);  
			memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%.1f",gCfgItems.yProbeOffset);
			BUTTON_SetText(ProbeYoffset_value.btnHandle,cmd_code);   
			memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%.1f",gCfgItems.zProbeOffset);
			BUTTON_SetText(ProbeZoffset_value.btnHandle,cmd_code); 
		}
	}
}




