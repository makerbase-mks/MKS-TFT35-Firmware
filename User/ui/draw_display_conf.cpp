#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"
#include "mks_touch_screen.h"
#include "touch_calibrate.h"
#include "ili9320.h"
#include "LCDConf.h" 

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hDisplayConfWnd;
static BUTTON_STRUCT colorConf_text,effect_3d_text,btn_textOffset_text,Screen_rotation_text,display_mode_text,display_error_text,Babastepting_text;
static BUTTON_STRUCT colorConfArrow,effects_3d_sel,btn_textOffset_value,Screen_rotate_sel,display_mode_sel,display_error_sel,btn_textOffset_default,Enable_babastepting;

static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

extern u16 DeviceCode;

static void cbDisplayConfWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(0xff5449);
			GUI_FillRect(10, 90, 470,90);
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
    				last_disp_state = DISPLAY_CONF_UI;
    				Clear_displayConf();
    				draw_return_ui();
    			}	
    			else if(pMsg->hWinSrc == btn_textOffset_value.btnHandle)
    			{
    				last_disp_state = DISPLAY_CONF_UI;
	                    Clear_displayConf();
	                    value=btn_textOffset;
	                    draw_NumberKey();
    			}				
    			else if(pMsg->hWinSrc == effects_3d_sel.btnHandle)
    			{
    				last_disp_state = DISPLAY_CONF_UI;     
					if (gCfgItems.button_3d_effect_flag == 1 )
					{
						gCfgItems.button_3d_effect_flag = 0;
						BUTTON_SetText(effects_3d_sel.btnHandle, machine_menu.disable);
						BUTTON_SetBmpFileName(effects_3d_sel.btnHandle, "bmp_disable.bin",1); 		
						WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);
						
					}
					else 
					{
						BUTTON_SetText(effects_3d_sel.btnHandle, machine_menu.enable);
						gCfgItems.button_3d_effect_flag = 1;
						BUTTON_SetBmpFileName(effects_3d_sel.btnHandle, "bmp_enable.bin",1); 
						WIDGET_SetDefaultEffect(&WIDGET_Effect_3D);		
					}
					HAL::AT24CXX_Write(BAK_BUTTON_3D_EFFECT_FLAG,(uint8_t *)&gCfgItems.button_3d_effect_flag ,1);
    			}
    			else if(pMsg->hWinSrc == Screen_rotate_sel.btnHandle)
    			{
    				last_disp_state = DISPLAY_CONF_UI;
					if(gCfgItems.overturn_180 != 0)
					{
						gCfgItems.overturn_180 = 0;
		  				 //BUTTON_SetBmpFileName(Screen_rotate_sel.btnHandle, "bmp_disable.bin",1);	
						 //BUTTON_SetText(Screen_rotate_sel.btnHandle, machine_menu.disable);
						 HAL::AT24CXX_Write(BAK_SCREEN_OVERTURN_180_ADDR,(uint8_t *)&gCfgItems.overturn_180,1);
						 GUI_Init();
						 GUI_UC_SetEncodeUTF8();
						if(gCfgItems.overturn_180 != 0xEE)
					   {
						gCfgItems.touch_adj_flag = 0;
						gCfgItems.touch_adj_xMin = 95;
						gCfgItems.touch_adj_xMax = 3947;
						gCfgItems.touch_adj_yMin = 3780;
						gCfgItems.touch_adj_yMax = 150; 
					   }
					   else
					   {
						gCfgItems.touch_adj_flag = 0;
						gCfgItems.touch_adj_xMin = 3947;
						gCfgItems.touch_adj_xMax = 95;
						gCfgItems.touch_adj_yMin = 150;
						gCfgItems.touch_adj_yMax = 3780;	
					   }
					   setTouchBound(gCfgItems.touch_adj_xMin, gCfgItems.touch_adj_xMax, gCfgItems.touch_adj_yMax, gCfgItems.touch_adj_yMin);
					   gui_view_init(); 

						Clear_displayConf();
						draw_displayConf();
					}
					else
					{
						gCfgItems.overturn_180 = 0xEE;
						//BUTTON_SetBmpFileName(Screen_rotate_sel.btnHandle, "bmp_enable.bin",1);
						//BUTTON_SetText(Screen_rotate_sel.btnHandle, machine_menu.enable);
						HAL::AT24CXX_Write(BAK_SCREEN_OVERTURN_180_ADDR,(uint8_t *)&gCfgItems.overturn_180,1);
						GUI_Init();
						GUI_UC_SetEncodeUTF8();
						if(gCfgItems.overturn_180 != 0xEE)
					   {
							gCfgItems.touch_adj_flag = 0;
							gCfgItems.touch_adj_xMin = 95;
							gCfgItems.touch_adj_xMax = 3947;
							gCfgItems.touch_adj_yMin = 3780;
							gCfgItems.touch_adj_yMax = 150; 
					   }
					   else
					   {
							gCfgItems.touch_adj_flag = 0;
							gCfgItems.touch_adj_xMin = 3947;
							gCfgItems.touch_adj_xMax = 95;
							gCfgItems.touch_adj_yMin = 150;
							gCfgItems.touch_adj_yMax = 3780;	
					   }
					   setTouchBound(gCfgItems.touch_adj_xMin, gCfgItems.touch_adj_xMax, gCfgItems.touch_adj_yMax, gCfgItems.touch_adj_yMin);
					   gui_view_init(); 

						Clear_displayConf();
						draw_displayConf();
					}		           
    			} 
				else if(pMsg->hWinSrc == display_mode_text.btnHandle)
    			{
    				last_disp_state = DISPLAY_CONF_UI;
					if(gCfgItems.display_style == 1)
					{
						gCfgItems.display_style = 0;
						BUTTON_SetText(display_mode_text.btnHandle, machine_menu.classic_theme); 
					}
					else
					{
						gCfgItems.display_style = 1;
						BUTTON_SetText(display_mode_text.btnHandle, machine_menu.simple_theme);
					}
					HAL::AT24CXX_Write(BAK_SCREEN_DISPLAY_MODE_ADDR,(uint8_t *)&gCfgItems.display_style,1);
    			}
				else if(pMsg->hWinSrc == display_error_sel.btnHandle)
    			{
    				last_disp_state = DISPLAY_CONF_UI;
					if(gCfgItems.display_error == 1)
					{
						gCfgItems.display_error = 0;
		  				 BUTTON_SetBmpFileName(display_error_sel.btnHandle, "bmp_disable.bin",1);	
						 BUTTON_SetText(display_error_sel.btnHandle, machine_menu.disable);
					}
					else
					{
						gCfgItems.display_error = 1;
						BUTTON_SetBmpFileName(display_error_sel.btnHandle, "bmp_enable.bin",1);
						BUTTON_SetText(display_error_sel.btnHandle, machine_menu.enable);
					}
					HAL::AT24CXX_Write(BAK_DISP_EEROR_ADDR,(uint8_t *)&gCfgItems.display_error,1);
    			}
				else if(pMsg->hWinSrc == Enable_babastepting.btnHandle)
    			{
    				last_disp_state = DISPLAY_CONF_UI;
					if(gCfgItems.baby_step_display_flg == 1)
					{
						gCfgItems.baby_step_display_flg = 0;
		  				 BUTTON_SetBmpFileName(Enable_babastepting.btnHandle, "bmp_disable.bin",1);	
						 BUTTON_SetText(Enable_babastepting.btnHandle, machine_menu.disable);
					}
					else
					{
						gCfgItems.baby_step_display_flg = 1;
						BUTTON_SetBmpFileName(Enable_babastepting.btnHandle, "bmp_enable.bin",1);
						BUTTON_SetText(Enable_babastepting.btnHandle, machine_menu.enable);
					}
					HAL::AT24CXX_Write(BAK_BABY_STEP_DISP_ADDR,(uint8_t *)&gCfgItems.baby_step_display_flg,1);
    			}
    			else if(pMsg->hWinSrc == btn_textOffset_default.btnHandle)
    			{
    				last_disp_state = DISPLAY_CONF_UI;
					gCfgItems.btn_text_offset = 23;
					memset(cmd_code,0,sizeof(cmd_code));
					sprintf(cmd_code,"%d",gCfgItems.btn_text_offset);
					BUTTON_SetText(btn_textOffset_value.btnHandle,cmd_code);	
    				HAL::AT24CXX_Write(BAK_BTN_TEXT_OFFSET_ADDR,(uint8_t *)&gCfgItems.btn_text_offset,1);
    			} 
			else if(pMsg->hWinSrc == button_next.btnHandle)
	             {
	                    current_page = 1;
	                    last_disp_state = DISPLAY_CONF_UI;
	                    Clear_displayConf();
	                    draw_displayConf();
	              }
	              else if(pMsg->hWinSrc == button_previous.btnHandle)
	              {
	                    current_page = 0;
	                    last_disp_state = DISPLAY_CONF_UI;
	                    Clear_displayConf();
	                    draw_displayConf();
	              } 
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_displayConf()
{   

    colorConf_text.btnHandle=0;
    effect_3d_text.btnHandle=0;
    btn_textOffset_text.btnHandle=0;
    Screen_rotation_text.btnHandle=0;
    display_mode_text.btnHandle=0;
	display_error_text.btnHandle =0;
	
    colorConfArrow.btnHandle=0;
    effects_3d_sel.btnHandle=0;
    btn_textOffset_value.btnHandle=0;
    Screen_rotate_sel.btnHandle= 0;
    display_mode_sel.btnHandle= 0 ;
	display_error_sel.btnHandle = 0;
    btn_textOffset_default.btnHandle=0;

    button_back.btnHandle=0;
    button_next.btnHandle=0;
    button_previous.btnHandle=0;
	Babastepting_text.btnHandle = 0;
	Enable_babastepting.btnHandle = 0;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != DISPLAY_CONF_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = DISPLAY_CONF_UI;
    }
    disp_state = DISPLAY_CONF_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.DisplayConfTitle, TITLE_XPOS, TITLE_YPOS);//machine_menu.DisplayConfTitle

    hDisplayConfWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbDisplayConfWin, 0);

    if(current_page != 1)
    {		
		effect_3d_text.btnHandle = BUTTON_CreateEx(10,50,360,40,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		effects_3d_sel.btnHandle = BUTTON_CreateEx(370,50,90,40,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    btn_textOffset_text.btnHandle = BUTTON_CreateEx(10,100,300,40,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    btn_textOffset_value.btnHandle = BUTTON_CreateEx(320,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    btn_textOffset_default.btnHandle = BUTTON_CreateEx(400,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());		

		Screen_rotation_text.btnHandle = BUTTON_CreateEx(10,150,360,40,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());//180
		Screen_rotate_sel.btnHandle = BUTTON_CreateEx(370,150,90,40,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
		display_mode_text.btnHandle = BUTTON_CreateEx(10,200,480,40,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());//
//		display_mode_sel.btnHandle = BUTTON_CreateEx(370,200,90,40,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

		if(gCfgItems.button_3d_effect_flag == 1)
			   BUTTON_SetBmpFileName(effects_3d_sel.btnHandle, "bmp_enable.bin",1); 	
		else
		   BUTTON_SetBmpFileName(effects_3d_sel.btnHandle, "bmp_disable.bin",1);

		if(gCfgItems.overturn_180 != 0)
		   BUTTON_SetBmpFileName(Screen_rotate_sel.btnHandle, "bmp_enable.bin",1);		
		else
		   BUTTON_SetBmpFileName(Screen_rotate_sel.btnHandle, "bmp_disable.bin",1);

//		if(gCfgItems.display_style == 1)
//		   BUTTON_SetBmpFileName(display_mode_sel.btnHandle, "bmp_enable.bin",1);		//simple mode
//		else
//		   BUTTON_SetBmpFileName(display_mode_sel.btnHandle, "bmp_disable.bin",1);	

	    BUTTON_SetBmpFileName(btn_textOffset_value.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(btn_textOffset_default.btnHandle, "bmp_pic70x28_2.bin",1);

		
//		BUTTON_SetBitmapEx(colorConfArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);//arrow
		BUTTON_SetBitmapEx(effects_3d_sel.btnHandle,0,&bmp_struct90X30,0,5); //select
		BUTTON_SetBitmapEx(Screen_rotate_sel.btnHandle,0,&bmp_struct90X30,0,5); 
		BUTTON_SetBitmapEx(display_mode_sel.btnHandle,0,&bmp_struct90X30,0,5); 
		
		BUTTON_SetBitmapEx(btn_textOffset_value.btnHandle,0,&bmp_struct70X28,0,0);
		BUTTON_SetBitmapEx(btn_textOffset_default.btnHandle,0,&bmp_struct70X28,0,0);		
	    
//	    BUTTON_SetBmpFileName(colorConf_text.btnHandle,NULL,1);        
	    BUTTON_SetBmpFileName(effect_3d_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(Screen_rotation_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(display_mode_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(btn_textOffset_text.btnHandle,NULL,1);		
	    
//	    BUTTON_SetTextAlign(colorConf_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(effect_3d_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(Screen_rotation_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(display_mode_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(btn_textOffset_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(effects_3d_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
//	    BUTTON_SetTextAlign(display_mode_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(Screen_rotate_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
//	    BUTTON_SetTextAlign(Screen_rotate_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(btn_textOffset_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );	
		BUTTON_SetTextAlign(btn_textOffset_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		BUTTON_SetBkColor(btn_textOffset_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(btn_textOffset_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(btn_textOffset_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(btn_textOffset_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

		BUTTON_SetBkColor(btn_textOffset_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(btn_textOffset_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(btn_textOffset_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(btn_textOffset_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

		BUTTON_SetBkColor(display_mode_text.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_BK_COLOR);
		BUTTON_SetBkColor(display_mode_text.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
		BUTTON_SetTextColor(display_mode_text.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_TEXT_COLOR);
		BUTTON_SetTextColor(display_mode_text.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
		
		memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.btn_text_offset);
	    BUTTON_SetText(btn_textOffset_value.btnHandle,cmd_code);		

		button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hDisplayConfWnd,BUTTON_CF_SHOW,0,alloc_win_id());
           BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
           BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);

	     BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	     BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
	     BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextAlign(button_next.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	     
	    if(gCfgItems.multiple_language != 0)
	    {
	        BUTTON_SetText(effect_3d_text.btnHandle, machine_menu.btn_3D_ecffects);
	        BUTTON_SetText(Screen_rotation_text.btnHandle, machine_menu.screen_overturn); 
			if (gCfgItems.display_style == 1) 						
				BUTTON_SetText(display_mode_text.btnHandle, machine_menu.simple_theme); 
			else 
				BUTTON_SetText(display_mode_text.btnHandle, machine_menu.classic_theme); 
			
	        BUTTON_SetText(btn_textOffset_text.btnHandle, machine_menu.btn_text_offset);
	        BUTTON_SetText(btn_textOffset_default.btnHandle, machine_menu.default_value);	
		 	BUTTON_SetText(button_next.btnHandle,machine_menu.next);

			if(gCfgItems.button_3d_effect_flag == 1)
				 BUTTON_SetText(effects_3d_sel.btnHandle,machine_menu.enable);
			else 
				 BUTTON_SetText(effects_3d_sel.btnHandle,machine_menu.disable);
			if(gCfgItems.overturn_180 == 0)
				 BUTTON_SetText(Screen_rotate_sel.btnHandle,machine_menu.disable);
			else 
				 BUTTON_SetText(Screen_rotate_sel.btnHandle,machine_menu.enable);
//			if(gCfgItems.display_style == 1)
//			   BUTTON_SetText(display_mode_sel.btnHandle,machine_menu.enable);		//simple mode
//			else
//			   BUTTON_SetText(display_mode_sel.btnHandle,machine_menu.disable);	
	   }
    }
    else
    {

		display_error_text.btnHandle = BUTTON_CreateEx(10,50,360,40,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		display_error_sel.btnHandle = BUTTON_CreateEx(370,50,90,40,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		Babastepting_text.btnHandle = BUTTON_CreateEx(10,100,360,40,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		Enable_babastepting.btnHandle = BUTTON_CreateEx(370,100,90,40,hDisplayConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());


		if (gCfgItems.display_error == 1 )
		    BUTTON_SetBmpFileName(display_error_sel.btnHandle, "bmp_enable.bin",1);
		else
		    BUTTON_SetBmpFileName(display_error_sel.btnHandle, "bmp_disable.bin",1);

		if(gCfgItems.baby_step_display_flg ==1 )
			BUTTON_SetBmpFileName(Enable_babastepting.btnHandle, "bmp_enable.bin",1);
		else
			BUTTON_SetBmpFileName(Enable_babastepting.btnHandle, "bmp_disable.bin",1);	
		
	    BUTTON_SetBmpFileName(display_error_text.btnHandle,NULL,1);        
			    BUTTON_SetBmpFileName(Babastepting_text.btnHandle,NULL,1);    
		
		BUTTON_SetBitmapEx(display_error_sel.btnHandle,0,&bmp_struct90X30,0,5); 
		BUTTON_SetBitmapEx(Enable_babastepting.btnHandle,0,&bmp_struct90X30,0,5); 

	    BUTTON_SetTextAlign(display_error_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );		
		BUTTON_SetTextAlign(display_error_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(Babastepting_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );		
		BUTTON_SetTextAlign(Enable_babastepting.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hDisplayConfWnd,BUTTON_CF_SHOW,0,alloc_win_id());
           BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
        
           BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);

	     BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	     BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color);    
	     BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
	     
     	 BUTTON_SetTextAlign(button_previous.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    if(gCfgItems.multiple_language != 0)
	    {
	        BUTTON_SetText(display_error_text.btnHandle,machine_menu.display_error_msg);
	        BUTTON_SetText(Babastepting_text.btnHandle,machine_menu.babastepting);
			
			if(gCfgItems.display_error == 1)
				 BUTTON_SetText(display_error_sel.btnHandle,machine_menu.enable);
			else 
				 BUTTON_SetText(display_error_sel.btnHandle,machine_menu.disable);
			
			if(gCfgItems.baby_step_display_flg == 1)
				 BUTTON_SetText(Enable_babastepting.btnHandle,machine_menu.enable);
			else 
				 BUTTON_SetText(Enable_babastepting.btnHandle,machine_menu.disable);
			
	    	 BUTTON_SetText(button_previous.btnHandle,machine_menu.previous); 
	    }
    }

    button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hDisplayConfWnd,BUTTON_CF_SHOW,0,alloc_win_id());
    
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
    BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0,0);
    BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 
    
    BUTTON_SetText(button_back.btnHandle,machine_menu.back);

}

void Clear_displayConf()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hDisplayConfWnd))
	{
		WM_DeleteWindow(hDisplayConfWnd);
	}
}






