#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hAdvancedWnd;
static BUTTON_STRUCT PowerOffDet_text,PowerOff_text,HaveUPS_text;//,DoubleZandEndstop_text,MotorEnablePin_text;
static BUTTON_STRUCT PowerOff_Sel,HaveUPS_Sel;//,DoubleZandEndstopArrow,MotorEnablePinArrow,PowerOffDet_DET;
static BUTTON_STRUCT PowerOffDet_PWC,Leve_PB0_text,Leve_PB0_sel,Leve_PB1_text,Leve_PB1_sel,z_error_text,z_error_val,mask_PB0_PB1_text,mask_PB0_PB1_sel,pwroff_save_mode_text,pwroff_save_mode_sel;
static BUTTON_STRUCT Z_error_default;

static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void btnHandle_rest()
{
    PowerOffDet_text.btnHandle = 0;
    PowerOffDet_PWC.btnHandle = 0;
    PowerOff_text.btnHandle = 0;
    PowerOff_Sel.btnHandle = 0;
    HaveUPS_text.btnHandle = 0;
    HaveUPS_Sel.btnHandle = 0;
     
    button_previous.btnHandle = 0;
    button_next.btnHandle = 0;
    button_back.btnHandle = 0;
	//add
	Leve_PB0_text.btnHandle = 0;
	Leve_PB1_text.btnHandle = 0;
	z_error_text.btnHandle = 0;
	mask_PB0_PB1_text.btnHandle = 0;
	pwroff_save_mode_text.btnHandle = 0;
	Leve_PB0_sel.btnHandle = 0;
	Leve_PB1_sel.btnHandle = 0;
	z_error_val.btnHandle = 0;
	mask_PB0_PB1_sel.btnHandle = 0;
	pwroff_save_mode_sel.btnHandle = 0;
	Z_error_default.btnHandle = 0;
	
}

static void cbAdvancedWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(0xff5449);

			GUI_FillRect(10, 90, 470,90);
//            if(current_page != 1)
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
    			    current_page = 0;
    				last_disp_state = ADVANCED_UI;
    				Clear_Advanced();
    				draw_return_ui();
    			}	
                else if(pMsg->hWinSrc == button_next.btnHandle)
                {
                    current_page = 1;
                    last_disp_state = ADVANCED_UI;
                    Clear_Advanced();
                    draw_Advanced();
                }
                else if(pMsg->hWinSrc == button_previous.btnHandle)
                {
                    current_page = 0;
                    last_disp_state = ADVANCED_UI;
                    Clear_Advanced();
                    draw_Advanced();
                }                
    			else if(pMsg->hWinSrc == PowerOffDet_PWC.btnHandle)
    			{		
					if(gCfgItems.insert_det_module==0)
					{
						gCfgItems.insert_det_module = 1;	
						BUTTON_SetText(PowerOffDet_PWC.btnHandle, "DET");						
					}
					else 
					{
						gCfgItems.insert_det_module = 0;
						BUTTON_SetText(PowerOffDet_PWC.btnHandle, "PWC");						
					}
					HAL::AT24CXX_Write(BAK_INSERT_MODULE_ADDR,(uint8_t *)&gCfgItems.insert_det_module,1);	
    			}
    			else if(pMsg->hWinSrc == PowerOff_Sel.btnHandle)
    			{
					if(gCfgItems.print_finish_close_machine_flg==1)
					{
						gCfgItems.print_finish_close_machine_flg=0;
						BUTTON_SetBmpFileName(PowerOff_Sel.btnHandle, "bmp_disable.bin",1);
                        if(gCfgItems.multiple_language != 0)
                            BUTTON_SetText(PowerOff_Sel.btnHandle, machine_menu.disable);                            
					}
					else
					{
						gCfgItems.print_finish_close_machine_flg=1;
						BUTTON_SetBmpFileName(PowerOff_Sel.btnHandle, "bmp_enable.bin",1);
                        if(gCfgItems.multiple_language != 0)
                            BUTTON_SetText(PowerOff_Sel.btnHandle, machine_menu.enable);
					}
		    		HAL::AT24CXX_Write(BAK_PRINT_FINISH_CLOASE_MACHINE_ADDR,(uint8_t *)&gCfgItems.print_finish_close_machine_flg,1);
    			}       
    			else if(pMsg->hWinSrc == HaveUPS_Sel.btnHandle)

    			{
					if(gCfgItems.have_ups==1)
					{
						gCfgItems.have_ups=0;
						BUTTON_SetBmpFileName(HaveUPS_Sel.btnHandle, "bmp_disable.bin",1);
                        if(gCfgItems.multiple_language != 0)
                            BUTTON_SetText(HaveUPS_Sel.btnHandle, machine_menu.disable);

                    }
					else
					{
						gCfgItems.have_ups=1;
						BUTTON_SetBmpFileName(HaveUPS_Sel.btnHandle, "bmp_enable.bin",1);
                        if(gCfgItems.multiple_language != 0)
                            BUTTON_SetText(HaveUPS_Sel.btnHandle, machine_menu.enable);                        
					}
					HAL::AT24CXX_Write(BAK_HAVE_UPS_ADDR,(uint8_t *)&gCfgItems.have_ups,1); 
					

    			}

				else if(pMsg->hWinSrc == z_error_val.btnHandle)
				{
    				last_disp_state = ADVANCED_UI;
    				Clear_Advanced();
                    value = Break_Z_error;                
                    draw_NumberKey();
				}
				else if(pMsg->hWinSrc == Leve_PB0_sel.btnHandle)
				{
					if(gCfgItems.filament_det2_level_flg==1)
					{
						gCfgItems.filament_det2_level_flg=0;
						BUTTON_SetBmpFileName(Leve_PB0_sel.btnHandle, "bmp_disable.bin",1);
						if(gCfgItems.multiple_language != 0)
							BUTTON_SetText(Leve_PB0_sel.btnHandle, machine_menu.low_level);
					}
					else
					{
						gCfgItems.filament_det2_level_flg=1;
						BUTTON_SetBmpFileName(Leve_PB0_sel.btnHandle, "bmp_enable.bin",1);
						if(gCfgItems.multiple_language != 0)
							BUTTON_SetText(Leve_PB0_sel.btnHandle, machine_menu.high_level); 					   
					}
					HAL::AT24CXX_Write(BAK_FILAMENT_DET2_FLAG_ADDR,(uint8_t *)&gCfgItems.filament_det2_level_flg,1); 	
				}
				else if(pMsg->hWinSrc == Leve_PB1_sel.btnHandle)
				{
					if(gCfgItems.filament_det1_level_flg==1)
					{
						gCfgItems.filament_det1_level_flg=0;
						BUTTON_SetBmpFileName(Leve_PB1_sel.btnHandle, "bmp_disable.bin",1);
						if(gCfgItems.multiple_language != 0)
							BUTTON_SetText(Leve_PB1_sel.btnHandle, machine_menu.low_level);
					}
					else
					{
						gCfgItems.filament_det1_level_flg=1;
						BUTTON_SetBmpFileName(Leve_PB1_sel.btnHandle, "bmp_enable.bin",1);
						if(gCfgItems.multiple_language != 0)
							BUTTON_SetText(Leve_PB1_sel.btnHandle, machine_menu.high_level); 					   
					}
					HAL::AT24CXX_Write(BAK_FILAMENT_DET1_FLAG_ADDR,(uint8_t *)&gCfgItems.filament_det1_level_flg,1); 	
				}
				else if(pMsg->hWinSrc == mask_PB0_PB1_sel.btnHandle)
				{
					if(gCfgItems.mask_PB0_PB1_Function==1)
					{
						gCfgItems.mask_PB0_PB1_Function=0;
						BUTTON_SetBmpFileName(mask_PB0_PB1_sel.btnHandle, "bmp_disable.bin",1);
						if(gCfgItems.multiple_language != 0)
							BUTTON_SetText(mask_PB0_PB1_sel.btnHandle, machine_menu.disable);
					}
					else
					{
						gCfgItems.mask_PB0_PB1_Function=1;
						BUTTON_SetBmpFileName(mask_PB0_PB1_sel.btnHandle, "bmp_enable.bin",1);
						if(gCfgItems.multiple_language != 0)
							BUTTON_SetText(mask_PB0_PB1_sel.btnHandle, machine_menu.enable); 					   
					}
					HAL::AT24CXX_Write(BAK_MASK_PB0_PB1_FUNCTION_ADDR,(uint8_t *)&gCfgItems.mask_PB0_PB1_Function,1);
				}
				else if(pMsg->hWinSrc == pwroff_save_mode_sel.btnHandle)
				{
					if(gCfgItems.pwroff_save_mode==1)
					{
						gCfgItems.pwroff_save_mode=0;
						BUTTON_SetBmpFileName(pwroff_save_mode_sel.btnHandle, "bmp_disable.bin",1);
						if(gCfgItems.multiple_language != 0)
							BUTTON_SetText(pwroff_save_mode_sel.btnHandle, machine_menu.pwr_saveMode2);
					}
					else
					{
						gCfgItems.pwroff_save_mode=1;
						BUTTON_SetBmpFileName(pwroff_save_mode_sel.btnHandle, "bmp_enable.bin",1);
						if(gCfgItems.multiple_language != 0)
							BUTTON_SetText(pwroff_save_mode_sel.btnHandle, machine_menu.pwr_saveMode1); 					   
					}
					HAL::AT24CXX_Write(BAK_PWROFF_SAVE_MODE_ADDR,(uint8_t *)&gCfgItems.pwroff_save_mode,1); 
				}	
				else if(pMsg->hWinSrc == Z_error_default.btnHandle)
				{
					gCfgItems.breakpoint_z_error = 0.2;
					memset(cmd_code,0,sizeof(cmd_code));
                    sprintf(cmd_code,"%.1f",gCfgItems.breakpoint_z_error);
					BUTTON_SetText(z_error_val.btnHandle, cmd_code); 
					HAL::AT24CXX_Write(BAK_BREAKPOINT_Z_ERROR_ADDR,(uint8_t *)&gCfgItems.breakpoint_z_error,4); 
				}
				
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_Advanced()
{   
    int i;


    btnHandle_rest();
    
    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != ADVANCED_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = ADVANCED_UI;
    }
    disp_state = ADVANCED_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.AdvancedConfTitle, TITLE_XPOS, TITLE_YPOS);

    hAdvancedWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbAdvancedWin, 0);

    if(current_page != 1)
    {
        PowerOffDet_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//        PowerOffDet_DET.btnHandle = BUTTON_CreateEx(270,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        PowerOffDet_PWC.btnHandle = BUTTON_CreateEx(370,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        PowerOff_text.btnHandle = BUTTON_CreateEx(10,100,450,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        PowerOff_Sel.btnHandle = BUTTON_CreateEx(370,100,90,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        HaveUPS_text.btnHandle = BUTTON_CreateEx(10,150,450,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        HaveUPS_Sel.btnHandle = BUTTON_CreateEx(370,150,90,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

		z_error_text.btnHandle = BUTTON_CreateEx(10,200,240,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		z_error_val.btnHandle = BUTTON_CreateEx(270,200+5,VALUE_DEFAULT_X ,VALUE_DEFAULT_Y,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		Z_error_default.btnHandle = BUTTON_CreateEx(370,200+5,VALUE_DEFAULT_X ,VALUE_DEFAULT_Y,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

		BUTTON_SetBmpFileName(PowerOffDet_PWC.btnHandle, "bmp_pic70x28_2.bin",1);


		if(gCfgItems.have_ups==1)
		{
        	BUTTON_SetBmpFileName(HaveUPS_Sel.btnHandle, "bmp_enable.bin",1);
		}
		else
		{
			BUTTON_SetBmpFileName(HaveUPS_Sel.btnHandle, "bmp_disable.bin",1);
		}
		if(gCfgItems.print_finish_close_machine_flg==1)
		{
			BUTTON_SetBmpFileName(PowerOff_Sel.btnHandle, "bmp_enable.bin",1);
		}
		else
		{
			BUTTON_SetBmpFileName(PowerOff_Sel.btnHandle, "bmp_disable.bin",1);
		}
        
        BUTTON_SetBmpFileName(PowerOffDet_text.btnHandle,NULL,1);        
        BUTTON_SetBmpFileName(PowerOff_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(HaveUPS_text.btnHandle,NULL,1);
		BUTTON_SetBmpFileName(z_error_text.btnHandle,NULL,1);
		BUTTON_SetBmpFileName(z_error_val.btnHandle, "bmp_pic70x28_1.bin",1);
		BUTTON_SetBmpFileName(Z_error_default.btnHandle, "bmp_pic70x28_2.bin",1); 
        

        BUTTON_SetBitmapEx(PowerOffDet_PWC.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(PowerOff_Sel.btnHandle,0,&bmp_struct90X30,0,5);
        BUTTON_SetBitmapEx(HaveUPS_Sel.btnHandle,0,&bmp_struct90X30,0,5); 

		BUTTON_SetBitmapEx(z_error_val.btnHandle,0,&bmp_struct70X28,0,0);
		BUTTON_SetBitmapEx(Z_error_default.btnHandle,0,&bmp_struct70X28,0,0);
        
        BUTTON_SetTextAlign(PowerOffDet_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(PowerOff_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(HaveUPS_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

		BUTTON_SetTextAlign(z_error_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );	 

		BUTTON_SetTextAlign(PowerOff_Sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(HaveUPS_Sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(z_error_val.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(Z_error_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		BUTTON_SetTextAlign(PowerOffDet_PWC.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		BUTTON_SetBkColor(z_error_val.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(z_error_val.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(z_error_val.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(z_error_val.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

		BUTTON_SetBkColor(Z_error_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(Z_error_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(Z_error_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(Z_error_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

		BUTTON_SetBkColor(PowerOffDet_PWC.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(PowerOffDet_PWC.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 

        button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hAdvancedWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
    
        BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);
        

    }
    else
    {
        button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hAdvancedWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
        BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);
		
		Leve_PB0_text.btnHandle = BUTTON_CreateEx(10,50,450,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		Leve_PB0_sel.btnHandle = BUTTON_CreateEx(370,50,90,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		Leve_PB1_text.btnHandle = BUTTON_CreateEx(10,100,450,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		Leve_PB1_sel.btnHandle = BUTTON_CreateEx(370,100,90,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		mask_PB0_PB1_text.btnHandle = BUTTON_CreateEx(10,150,450,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		mask_PB0_PB1_sel.btnHandle = BUTTON_CreateEx(370,150,90,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		pwroff_save_mode_text.btnHandle = BUTTON_CreateEx(10,200,450,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		pwroff_save_mode_sel.btnHandle = BUTTON_CreateEx(370,200,90 ,40,hAdvancedWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
		if(gCfgItems.filament_det1_level_flg==1)	//PB1 triger level
        	BUTTON_SetBmpFileName(Leve_PB1_sel.btnHandle, "bmp_enable.bin",1);        
		else
        	BUTTON_SetBmpFileName(Leve_PB1_sel.btnHandle, "bmp_disable.bin",1);  
		
		if(gCfgItems.mask_PB0_PB1_Function==1)	//1:disable mask check filement
        	BUTTON_SetBmpFileName(mask_PB0_PB1_sel.btnHandle, "bmp_enable.bin",1);
		else
			BUTTON_SetBmpFileName(mask_PB0_PB1_sel.btnHandle, "bmp_disable.bin",1);
		
		if(gCfgItems.pwroff_save_mode==1)
			BUTTON_SetBmpFileName(pwroff_save_mode_sel.btnHandle, "bmp_enable.bin",1);
		else//fileSys save 
			BUTTON_SetBmpFileName(pwroff_save_mode_sel.btnHandle, "bmp_disable.bin",1);

		if(gCfgItems.filament_det2_level_flg==1)	//PB0 trigger level
			BUTTON_SetBmpFileName(Leve_PB0_sel.btnHandle, "bmp_enable.bin",1);
		else
			BUTTON_SetBmpFileName(Leve_PB0_sel.btnHandle, "bmp_disable.bin",1);
		
	    BUTTON_SetBmpFileName(Leve_PB0_text.btnHandle,NULL,1);        
        BUTTON_SetBmpFileName(Leve_PB1_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(mask_PB0_PB1_text.btnHandle,NULL,1);
		BUTTON_SetBmpFileName(pwroff_save_mode_text.btnHandle,NULL,1);
			
		BUTTON_SetBitmapEx(Leve_PB0_sel.btnHandle,0,&bmp_struct90X30,0,5);
		BUTTON_SetBitmapEx(Leve_PB1_sel.btnHandle,0,&bmp_struct90X30,0,5); 
		BUTTON_SetBitmapEx(mask_PB0_PB1_sel.btnHandle,0,&bmp_struct90X30,0,5);
		BUTTON_SetBitmapEx(pwroff_save_mode_sel.btnHandle,0,&bmp_struct90X30,0,5); 
		
		BUTTON_SetTextAlign(Leve_PB0_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(Leve_PB1_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(mask_PB0_PB1_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(pwroff_save_mode_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );	 

		BUTTON_SetTextAlign(Leve_PB0_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(Leve_PB1_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(mask_PB0_PB1_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(pwroff_save_mode_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );      
    }

     button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hAdvancedWnd,BUTTON_CF_SHOW,0,alloc_win_id());
     
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
            BUTTON_SetText(PowerOffDet_text.btnHandle, machine_menu.PwrOffDection);
			
			if(gCfgItems.insert_det_module==1)
			 BUTTON_SetText(PowerOffDet_PWC.btnHandle, "DET");
			else 
			  BUTTON_SetText(PowerOffDet_PWC.btnHandle, "PWC");
			
            BUTTON_SetText(PowerOff_text.btnHandle, machine_menu.PwrOffAfterPrint);
            BUTTON_SetText(HaveUPS_text.btnHandle, machine_menu.HaveUps);
            BUTTON_SetText(button_next.btnHandle,machine_menu.next);
            BUTTON_SetText(z_error_text.btnHandle, machine_menu.z_error);
            BUTTON_SetText(Z_error_default.btnHandle, machine_menu.default_value);
			
			if(gCfgItems.have_ups==1)
				BUTTON_SetText(HaveUPS_Sel.btnHandle, machine_menu.enable);
			else
				BUTTON_SetText(HaveUPS_Sel.btnHandle, machine_menu.disable);
			
			if(gCfgItems.print_finish_close_machine_flg==1)
				BUTTON_SetText(PowerOff_Sel.btnHandle, machine_menu.enable);
			else
				BUTTON_SetText(PowerOff_Sel.btnHandle, machine_menu.disable);

			 memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%.1f",gCfgItems.breakpoint_z_error);
			BUTTON_SetText(z_error_val.btnHandle, cmd_code);

		}
        else
        {
			BUTTON_SetText(Leve_PB0_text.btnHandle,machine_menu.level_PB0);
			BUTTON_SetText(Leve_PB1_text.btnHandle,machine_menu.level_PB1);
			BUTTON_SetText(mask_PB0_PB1_text.btnHandle,machine_menu.disable_PB0_PB1);
			BUTTON_SetText(pwroff_save_mode_text.btnHandle,machine_menu.pwr_saveMode);
			
			if(gCfgItems.filament_det1_level_flg==1)	//PB1 triger level
				BUTTON_SetText(Leve_PB1_sel.btnHandle, machine_menu.high_level);
			else
				BUTTON_SetText(Leve_PB1_sel.btnHandle, machine_menu.low_level);	
			
			if(gCfgItems.mask_PB0_PB1_Function==1)	//1:enable mask check filement
				BUTTON_SetText(mask_PB0_PB1_sel.btnHandle, machine_menu.enable);		
			else
				BUTTON_SetText(mask_PB0_PB1_sel.btnHandle, machine_menu.disable);
			
			if(gCfgItems.pwroff_save_mode==1)
				BUTTON_SetText(pwroff_save_mode_sel.btnHandle, machine_menu.pwr_saveMode1);
			else//fileSys save 
				BUTTON_SetText(pwroff_save_mode_sel.btnHandle, machine_menu.pwr_saveMode2);
			
			if(gCfgItems.filament_det2_level_flg==1)	//PB0 trigger level
				BUTTON_SetText(Leve_PB0_sel.btnHandle, machine_menu.high_level);
			else
				BUTTON_SetText(Leve_PB0_sel.btnHandle, machine_menu.low_level);

            BUTTON_SetText(button_previous.btnHandle,machine_menu.previous);   
        }
         
        BUTTON_SetText(button_back.btnHandle,machine_menu.back);
        
              
     }

}


void Clear_Advanced()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hAdvancedWnd))
	{
		WM_DeleteWindow(hAdvancedWnd);
	}
}
