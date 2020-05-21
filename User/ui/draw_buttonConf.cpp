#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"
#include "spi_flash.h"
#include "pic_manager.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hButtonConfWnd;
static BUTTON_STRUCT Func1Cmd_text,func_btn1_text,quickstop_text,offset_btn_text,printMore_text,More_text,calibrate_btn_display;
static BUTTON_STRUCT Func1Cmd_value,func_btn1_sel,quickstopEnable_sel,offsetBtn_sel,printMoreArrow,MoreArrow,Func1Cmd_default,calibrate_btn_sel;

static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void cbButtonConfWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(0xff5449);
			GUI_FillRect(10, 90, 470,90);
         	 GUI_FillRect(10, 140, 470,140);
	         GUI_FillRect(10, 190, 470,190);
			if(current_page != 1)
			{
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
    			current_page   = 0;
    				last_disp_state = BUTTONCONF_UI;
    				Clear_buttonConf();
    				draw_return_ui();
    			}	
    			else if(pMsg->hWinSrc == quickstopEnable_sel.btnHandle)
    			{
    				last_disp_state = BUTTONCONF_UI;
					if (gCfgItems.quickstop_display_flg == 1)
					{
						gCfgItems.quickstop_display_flg = 0;
						BUTTON_SetBmpFileName(quickstopEnable_sel.btnHandle, "bmp_disable.bin", 1);
						BUTTON_SetText(quickstopEnable_sel.btnHandle, machine_menu.disable);
					}
					else 
					{
						gCfgItems.quickstop_display_flg =1;
						BUTTON_SetBmpFileName(quickstopEnable_sel.btnHandle, "bmp_enable.bin", 1);
						BUTTON_SetText(quickstopEnable_sel.btnHandle, machine_menu.enable);
					}
					HAL::AT24CXX_Write(BAK_QUICKSTOP_DISPLAY_FLG_ADDR,(uint8_t *)&gCfgItems.quickstop_display_flg,1);	
					
    			}
    			else if(pMsg->hWinSrc == Func1Cmd_default.btnHandle)
    			{					
				last_disp_state = BUTTONCONF_UI;
				 memset(cmd_code,0,sizeof(cmd_code));
				strcpy((char*)cmd_code, "M84;");
				BUTTON_SetText(Func1Cmd_value.btnHandle, cmd_code);	
				SPI_FLASH_BufferWrite((u8 *)cmd_code,BUTTON_FUNCTION1_ADDR,(strlen(cmd_code)+1));	

    			}				
    			else if(pMsg->hWinSrc == Func1Cmd_value.btnHandle)
    			{
    				if(gCfgItems.func_btn1_display_flag == 1)
    					{
	    					last_disp_state = BUTTONCONF_UI;
		                    Clear_buttonConf();
		                    valueType=func_btn1Cmd;
		                    draw_Keyboard();
    					}
    			}
    			else if(pMsg->hWinSrc == func_btn1_sel.btnHandle)
    			{
    				last_disp_state = BUTTONCONF_UI; 
					if (gCfgItems.func_btn1_display_flag == 1)
					{
						gCfgItems.func_btn1_display_flag = 0;
						BUTTON_SetBmpFileName(func_btn1_sel.btnHandle, "bmp_disable.bin", 1);
						BUTTON_SetBmpFileName(Func1Cmd_value.btnHandle, "bmp_pic70x28.bin", 1);
						BUTTON_SetText(func_btn1_sel.btnHandle, machine_menu.disable);
					}
					else 
					{
						gCfgItems.func_btn1_display_flag =1;
						BUTTON_SetBmpFileName(func_btn1_sel.btnHandle, "bmp_enable.bin", 1);
						BUTTON_SetBmpFileName(Func1Cmd_value.btnHandle, "bmp_pic70x28_1.bin", 1);
						BUTTON_SetText(func_btn1_sel.btnHandle, machine_menu.enable);
					}
					HAL::AT24CXX_Write(BAK_FUNC1_DISPLAY_ADDR,(uint8_t *)&gCfgItems.func_btn1_display_flag,1);
    			}
				else if(pMsg->hWinSrc == calibrate_btn_sel.btnHandle)
    			{
    				last_disp_state = BUTTONCONF_UI; 
					if (gCfgItems.calibrate_disp_flag == 1)
					{
						gCfgItems.calibrate_disp_flag = 0;
						BUTTON_SetBmpFileName(calibrate_btn_sel.btnHandle, "bmp_disable.bin", 1);
						BUTTON_SetText(calibrate_btn_sel.btnHandle, machine_menu.disable);
					}
					else 
					{
						gCfgItems.calibrate_disp_flag =1;
						BUTTON_SetBmpFileName(calibrate_btn_sel.btnHandle, "bmp_enable.bin", 1);
						BUTTON_SetText(calibrate_btn_sel.btnHandle, machine_menu.enable);
					}
					HAL::AT24CXX_Write(BAK_CALIBRATE_DISP_FLAG_ADDR,(uint8_t *)&gCfgItems.calibrate_disp_flag ,1);
    			}
    			else if(pMsg->hWinSrc == offsetBtn_sel.btnHandle)
    			{
    				last_disp_state = BUTTONCONF_UI; 
					if (gCfgItems.zoffset_display_flg == 1)
					{
						gCfgItems.zoffset_display_flg = 0;
						BUTTON_SetBmpFileName(offsetBtn_sel.btnHandle, "bmp_disable.bin", 1);
						BUTTON_SetText(offsetBtn_sel.btnHandle, machine_menu.disable);
					}
					else 
					{
						gCfgItems.zoffset_display_flg =1;
						BUTTON_SetBmpFileName(offsetBtn_sel.btnHandle, "bmp_enable.bin", 1);
						BUTTON_SetText(offsetBtn_sel.btnHandle, machine_menu.enable);
					}
					HAL::AT24CXX_Write(BAK_ZOFFSET_DISPLAY_FLG_ADDR,(uint8_t *)&gCfgItems.zoffset_display_flg,1);	
                    
    			} 
				else if( (pMsg->hWinSrc == printMoreArrow.btnHandle)||
						 (pMsg->hWinSrc == printMore_text.btnHandle ) )
    			{
    				last_disp_state = BUTTONCONF_UI;
	                    Clear_buttonConf();
	                    draw_printMoreBtn();                    
                    
    			}
				else if( (pMsg->hWinSrc == MoreArrow.btnHandle)||
						 (pMsg->hWinSrc == More_text.btnHandle ) )
    			{
    				last_disp_state = BUTTONCONF_UI;
	                    Clear_buttonConf();
	                    draw_MoreBtns();                    
                    
    			}
    			else if(pMsg->hWinSrc == Func1Cmd_default.btnHandle)
    			{
    				last_disp_state = BUTTONCONF_UI;
//	                    Clear_buttonConf();
//	                    value=Point3_y;
//	                    draw_NumberKey();    
					memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "M84;");
					flash_reWriteInf((u8 *)cmd_code,BUTTON_FUNCTION1_ADDR,(strlen(cmd_code)+1));
					BUTTON_SetText(Func1Cmd_value.btnHandle, cmd_code);  
    			} 
			else if(pMsg->hWinSrc == button_next.btnHandle)
	             {
	                    current_page = 1;
	                    last_disp_state = BUTTONCONF_UI;
	                    Clear_buttonConf();
	                    draw_buttonConf();
	              }
	              else if(pMsg->hWinSrc == button_previous.btnHandle)
	              {
	                    current_page = 0;
	                    last_disp_state = BUTTONCONF_UI;
	                    Clear_buttonConf();
	                    draw_buttonConf();
	              } 
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_buttonConf()
{   
    int i;

    Func1Cmd_text.btnHandle=0;
    func_btn1_text.btnHandle=0;
    quickstop_text.btnHandle=0;
    offset_btn_text.btnHandle=0;
    printMore_text.btnHandle=0;
	More_text.btnHandle =0;
	
    Func1Cmd_value.btnHandle=0;
    func_btn1_sel.btnHandle=0;
    quickstopEnable_sel.btnHandle=0;
    offsetBtn_sel.btnHandle= 0;
    printMoreArrow.btnHandle= 0 ;
	MoreArrow.btnHandle = 0;
    Func1Cmd_default.btnHandle=0;
	calibrate_btn_display.btnHandle = 0;
	calibrate_btn_sel.btnHandle = 0;

    button_back.btnHandle=0;
    button_next.btnHandle=0;
    button_previous.btnHandle=0;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != BUTTONCONF_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = BUTTONCONF_UI;
    }
    disp_state = BUTTONCONF_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.buttonConfTitle, TITLE_XPOS, TITLE_YPOS);

    hButtonConfWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbButtonConfWin, 0);

    if(current_page != 1)
    {
		func_btn1_text.btnHandle = BUTTON_CreateEx(10,50,360,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		func_btn1_sel.btnHandle = BUTTON_CreateEx(370,50,90,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
	    Func1Cmd_text.btnHandle = BUTTON_CreateEx(10,100,300,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    Func1Cmd_value.btnHandle = BUTTON_CreateEx(320,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    Func1Cmd_default.btnHandle = BUTTON_CreateEx(400,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

		quickstop_text.btnHandle = BUTTON_CreateEx(10,150,360,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());//
		quickstopEnable_sel.btnHandle = BUTTON_CreateEx(370,150,90,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
		offset_btn_text.btnHandle = BUTTON_CreateEx(10,200,360,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());//
		offsetBtn_sel.btnHandle = BUTTON_CreateEx(370,200,90,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		if(gCfgItems.func_btn1_display_flag == 1)
			BUTTON_SetBmpFileName(Func1Cmd_value.btnHandle, "bmp_pic70x28_1.bin",1); 
		else 
			BUTTON_SetBmpFileName(Func1Cmd_value.btnHandle, "bmp_pic70x28.bin",1); 		
		
		BUTTON_SetBmpFileName(Func1Cmd_default.btnHandle, "bmp_pic70x28_2.bin",1); 
		
		if (gCfgItems.func_btn1_display_flag  == 1)
		{
			BUTTON_SetBmpFileName(func_btn1_sel.btnHandle, "bmp_enable.bin",1); 
			BUTTON_SetBmpFileName(Func1Cmd_value.btnHandle, "bmp_pic70x28_1.bin",1);
		}
		else 
		{
			BUTTON_SetBmpFileName(func_btn1_sel.btnHandle, "bmp_disable.bin",1); 
			BUTTON_SetBmpFileName(Func1Cmd_value.btnHandle, "bmp_pic70x28.bin",1);			
		}
		if(gCfgItems.quickstop_display_flg == 1)
			   BUTTON_SetBmpFileName(quickstopEnable_sel.btnHandle, "bmp_enable.bin",1); 	
		else
		   BUTTON_SetBmpFileName(quickstopEnable_sel.btnHandle, "bmp_disable.bin",1);
		
		if(gCfgItems.zoffset_display_flg == 1)
		   BUTTON_SetBmpFileName(offsetBtn_sel.btnHandle, "bmp_enable.bin",1);		
		else
		   BUTTON_SetBmpFileName(offsetBtn_sel.btnHandle, "bmp_disable.bin",1);

//		BUTTON_SetBitmapEx(Func1Cmd_value.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);//arrow
		BUTTON_SetBitmapEx(func_btn1_sel.btnHandle,0,&bmp_struct90X30,0,5); //select
		BUTTON_SetBitmapEx(offsetBtn_sel.btnHandle,0,&bmp_struct90X30,0,5); 
		BUTTON_SetBitmapEx(quickstopEnable_sel.btnHandle,0,&bmp_struct90X30,0,5); 
		
		BUTTON_SetBitmapEx(Func1Cmd_value.btnHandle,0,&bmp_struct70X28,0,0);//value
		BUTTON_SetBitmapEx(Func1Cmd_default.btnHandle,0,&bmp_struct70X28,0,0);		
	    
	    BUTTON_SetBmpFileName(Func1Cmd_text.btnHandle,NULL,1);        
	    BUTTON_SetBmpFileName(func_btn1_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(offset_btn_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(quickstop_text.btnHandle,NULL,1);
	    
	    BUTTON_SetTextAlign(Func1Cmd_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(func_btn1_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(offset_btn_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(quickstop_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(func_btn1_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(quickstopEnable_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(offsetBtn_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(offsetBtn_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		BUTTON_SetTextAlign(Func1Cmd_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(Func1Cmd_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		BUTTON_SetBkColor(Func1Cmd_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
		BUTTON_SetBkColor(Func1Cmd_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
		BUTTON_SetTextColor(Func1Cmd_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
		BUTTON_SetTextColor(Func1Cmd_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

		BUTTON_SetBkColor(Func1Cmd_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(Func1Cmd_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(Func1Cmd_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(Func1Cmd_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

	    memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_FUNCTION1_ADDR,201);
	    BUTTON_SetText(Func1Cmd_value.btnHandle,cmd_code);
		
		button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hButtonConfWnd,BUTTON_CF_SHOW,0,alloc_win_id());
		BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
		BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);

		BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
		BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
		BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
		BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
		BUTTON_SetTextAlign(button_next.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );	     
		 
	    if(gCfgItems.multiple_language != 0)
	    {
	        BUTTON_SetText(Func1Cmd_text.btnHandle, machine_menu.function_btn1_cmd);
	        BUTTON_SetText(func_btn1_text.btnHandle, machine_menu.function_btn1_display);
	        BUTTON_SetText(offset_btn_text.btnHandle, machine_menu.zoffset_btn_display);  
			BUTTON_SetText(quickstop_text.btnHandle, machine_menu.quickStop_btn);  
		 	BUTTON_SetText(button_next.btnHandle,machine_menu.next);
			BUTTON_SetText(Func1Cmd_default.btnHandle,machine_menu.default_value);
			if (gCfgItems.func_btn1_display_flag == 1)
		        BUTTON_SetText(func_btn1_sel.btnHandle, machine_menu.enable);
			else 
		        BUTTON_SetText(func_btn1_sel.btnHandle, machine_menu.disable);
			if (gCfgItems.quickstop_display_flg == 1)
		        BUTTON_SetText(quickstopEnable_sel.btnHandle, machine_menu.enable);
			else 
		        BUTTON_SetText(quickstopEnable_sel.btnHandle, machine_menu.disable);	
			if (gCfgItems.zoffset_display_flg == 1)
		        BUTTON_SetText(offsetBtn_sel.btnHandle, machine_menu.enable);
			else 
		        BUTTON_SetText(offsetBtn_sel.btnHandle, machine_menu.disable);	
		}
    }
    else
    {
		More_text.btnHandle = BUTTON_CreateEx(10,50,450,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		MoreArrow.btnHandle = BUTTON_CreateEx(460,50,10,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
		printMore_text.btnHandle = BUTTON_CreateEx(10,100,450,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		printMoreArrow.btnHandle = BUTTON_CreateEx(460,100,10,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

		calibrate_btn_display.btnHandle = BUTTON_CreateEx(10,150,360,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());//
		calibrate_btn_sel.btnHandle = BUTTON_CreateEx(370,150,90,40,hButtonConfWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
		BUTTON_SetBmpFileName(MoreArrow.btnHandle, "bmp_arrow.bin",1); 
		BUTTON_SetBmpFileName(printMoreArrow.btnHandle, "bmp_arrow.bin",1); 
		if(gCfgItems.calibrate_disp_flag == 1)
			BUTTON_SetBmpFileName(calibrate_btn_sel.btnHandle, "bmp_enable.bin",1); 
		else 
			BUTTON_SetBmpFileName(calibrate_btn_sel.btnHandle, "bmp_disable.bin",1); 
			
	    BUTTON_SetBmpFileName(More_text.btnHandle,NULL,1);        
	    BUTTON_SetBmpFileName(printMore_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(calibrate_btn_display.btnHandle,NULL,1);
		
		BUTTON_SetBitmapEx(printMoreArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);//arrow
		BUTTON_SetBitmapEx(MoreArrow.btnHandle,0,&bmp_struct10x17,BMP_PIC_X,12);//arrow
		BUTTON_SetBitmapEx(calibrate_btn_sel.btnHandle,0,&bmp_struct90X30,0,5); 

	    BUTTON_SetTextAlign(printMore_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(More_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(calibrate_btn_display.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(calibrate_btn_sel.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hButtonConfWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
        
        BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);

	     BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	     BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color);    
	     BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
	     
     	     BUTTON_SetTextAlign(button_previous.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    if(gCfgItems.multiple_language != 0)
	    {
	        BUTTON_SetText(printMore_text.btnHandle, machine_menu.print_more_btn);
	        BUTTON_SetText(More_text.btnHandle, machine_menu.more_btn);
	        BUTTON_SetText(calibrate_btn_display.btnHandle, machine_menu.displayCalibrate);
			if(gCfgItems.calibrate_disp_flag == 1)
		        BUTTON_SetText(calibrate_btn_sel.btnHandle, machine_menu.enable);
			else 
		        BUTTON_SetText(calibrate_btn_sel.btnHandle, machine_menu.disable);

	    	 BUTTON_SetText(button_previous.btnHandle,machine_menu.previous); 
	    }
    }

    button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hButtonConfWnd,BUTTON_CF_SHOW,0,alloc_win_id());
    
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
    BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0,0);
    BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 
    
    BUTTON_SetText(button_back.btnHandle,machine_menu.back);

}

void Clear_buttonConf()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hButtonConfWnd))
	{
		WM_DeleteWindow(hButtonConfWnd);
	}
}







