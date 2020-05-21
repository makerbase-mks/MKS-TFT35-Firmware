#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"
#include "spi_flash.h"
#include "pic_manager.h"



#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hPrintMoreBtnWnd;
static BUTTON_STRUCT morefunc1_text,morefunc2_text,morefunc3_text,morefunc4_text,morefunc5_text,morefunc6_text,morefunc7_text;
static BUTTON_STRUCT morefunc1_cmd,morefunc2_cmd,morefunc3_cmd,morefunc4_cmd,morefunc5_cmd,morefunc6_cmd,morefunc7_cmd;
static BUTTON_STRUCT morefunc1_default,morefunc2_default,morefunc3_default,morefunc4_default,morefunc5_default,morefunc6_default,morefunc7_default;
static BUTTON_STRUCT buttons_count_text,buttons_count_value,buttons_count_default;

static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void cbPrintMoreBtnWnd(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(0xff5449);
			GUI_FillRect(10, 90, 470,90);
//			if(current_page != 1)
//			{
		            GUI_FillRect(10, 140, 470,140);
		            GUI_FillRect(10, 190, 470,190);
		            GUI_FillRect(10, 240, 470,240);
//			}
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
    				last_disp_state = PRINTMOREBTN_UI;
    				Clear_printMoreBtn();
					current_page = 0;
    				draw_return_ui();
    			}	
    			else if(pMsg->hWinSrc == buttons_count_value.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
	                    Clear_printMoreBtn();
	                    value=more_func_cnt;
	                    draw_NumberKey();
    			}
    			else if(pMsg->hWinSrc == buttons_count_default.btnHandle)
    			{
    				gCfgItems.morefunc_cnt = 5;
					memset(cmd_code,0,sizeof(cmd_code));
					sprintf(cmd_code,"%d",gCfgItems.morefunc_cnt);
					BUTTON_SetText(buttons_count_value.btnHandle,cmd_code);					
					HAL::AT24CXX_Write(BAK_PRINTING_MOREFUNC_CNT_ADDR,(uint8_t *)&gCfgItems.morefunc_cnt ,1);                  
    			}				
    			else if(pMsg->hWinSrc == morefunc1_cmd.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
	                    Clear_printMoreBtn();
	                    valueType=func1Cmd;
	                    draw_Keyboard();
    			}
    			else if(pMsg->hWinSrc == morefunc2_cmd.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
	                    Clear_printMoreBtn();
	                    valueType=func2Cmd;
	                    draw_Keyboard();                    
    			}
    			else if(pMsg->hWinSrc == morefunc3_cmd.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
	                    Clear_printMoreBtn();
	                    valueType=func3Cmd;
	                    draw_Keyboard();                    
    			} 
    			else if(pMsg->hWinSrc == morefunc4_cmd.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
	                    Clear_printMoreBtn();
	                    valueType=func4Cmd;
	                    draw_Keyboard();                    
                    
    			} 
			else if(pMsg->hWinSrc == morefunc5_cmd.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
	                    Clear_printMoreBtn();
	                    valueType=func5Cmd;
	                    draw_Keyboard();                    
                    
    			}
			   	else if(pMsg->hWinSrc == morefunc6_cmd.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
	                    Clear_printMoreBtn();
	                    valueType=func6Cmd;
	                    draw_Keyboard();                    
                    
    			} 
			else if(pMsg->hWinSrc == morefunc7_cmd.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
	                    Clear_printMoreBtn();
	                    valueType=func7Cmd;
	                    draw_Keyboard();                    
    			}
			else if(pMsg->hWinSrc == morefunc1_default.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
   					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					BUTTON_SetText(morefunc1_cmd.btnHandle, cmd_code);  
					flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC1_ADDR,(strlen(cmd_code)+1));  
    			}
    			else if(pMsg->hWinSrc == morefunc2_default.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					BUTTON_SetText(morefunc2_cmd.btnHandle, cmd_code);  
					flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC2_ADDR,(strlen(cmd_code)+1));  
    			}
    			else if(pMsg->hWinSrc == morefunc3_default.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					BUTTON_SetText(morefunc3_cmd.btnHandle, cmd_code);  
					flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC3_ADDR,(strlen(cmd_code)+1));  
    			} 
    			else if(pMsg->hWinSrc == morefunc4_default.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					BUTTON_SetText(morefunc4_cmd.btnHandle, cmd_code);  
					flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC4_ADDR,(strlen(cmd_code)+1));  
    			} 
			else if(pMsg->hWinSrc == morefunc5_default.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
   					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					BUTTON_SetText(morefunc5_cmd.btnHandle, cmd_code);  
					flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC5_ADDR,(strlen(cmd_code)+1));                    
    			}
    			else if(pMsg->hWinSrc == morefunc6_default.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
   					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
							BUTTON_SetText(morefunc6_cmd.btnHandle, cmd_code);  
					flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC6_ADDR,(strlen(cmd_code)+1));   
    			} 
				else if(pMsg->hWinSrc == morefunc7_default.btnHandle)
    			{
    				last_disp_state = PRINTMOREBTN_UI;
					memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					BUTTON_SetText(morefunc7_cmd.btnHandle, cmd_code);  
					flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC7_ADDR,(strlen(cmd_code)+1));  
    			}
			else if(pMsg->hWinSrc == button_next.btnHandle)
	             {
	                    current_page = 1;
	                    last_disp_state = PRINTMOREBTN_UI;
	                    Clear_printMoreBtn();
	                    draw_printMoreBtn();
	              }
	              else if(pMsg->hWinSrc == button_previous.btnHandle)
	              {
	                    current_page = 0;
	                    last_disp_state = PRINTMOREBTN_UI;
	                    Clear_printMoreBtn();
	                    draw_printMoreBtn();
	              } 
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_printMoreBtn()
{   
    int i;

    morefunc1_text.btnHandle=0;
    morefunc2_text.btnHandle=0;
    morefunc3_text.btnHandle=0;
    morefunc4_text.btnHandle=0;
    morefunc5_text.btnHandle=0;
    morefunc6_text.btnHandle=0;
    morefunc7_text.btnHandle=0;

    morefunc1_cmd.btnHandle=0;
    morefunc2_cmd.btnHandle=0;
    morefunc3_cmd.btnHandle=0;
    morefunc4_cmd.btnHandle=0;
    morefunc5_cmd.btnHandle=0;
    morefunc6_cmd.btnHandle=0;
    morefunc7_cmd.btnHandle=0;	

    morefunc1_default.btnHandle=0;
    morefunc2_default.btnHandle=0;
    morefunc3_default.btnHandle=0;
    morefunc4_default.btnHandle=0;
    morefunc5_default.btnHandle=0;
    morefunc6_default.btnHandle=0;
    morefunc7_default.btnHandle=0;	
	
	buttons_count_text.btnHandle = 0;
	buttons_count_value.btnHandle = 0;
	buttons_count_default.btnHandle = 0;

    button_back.btnHandle=0;

    button_next.btnHandle=0;
    button_previous.btnHandle=0;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != PRINTMOREBTN_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = PRINTMOREBTN_UI;
    }
    disp_state = PRINTMOREBTN_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.MoreFunctionConfTitle, TITLE_XPOS, TITLE_YPOS);

    hPrintMoreBtnWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbPrintMoreBtnWnd, 0);

    if(current_page != 1)
    {
		buttons_count_text.btnHandle = BUTTON_CreateEx(10,50,300,40,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		buttons_count_value.btnHandle = BUTTON_CreateEx(320,50,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		buttons_count_default.btnHandle = BUTTON_CreateEx(400,50,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
		morefunc1_text.btnHandle = BUTTON_CreateEx(10,100,300,40,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		morefunc1_cmd.btnHandle = BUTTON_CreateEx(320,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		morefunc1_default.btnHandle = BUTTON_CreateEx(400,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    morefunc2_text.btnHandle = BUTTON_CreateEx(10,150,300,40,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc2_cmd.btnHandle = BUTTON_CreateEx(320,150,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc2_default.btnHandle = BUTTON_CreateEx(400,150,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    morefunc3_text.btnHandle = BUTTON_CreateEx(10,200,300,40,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc3_cmd.btnHandle = BUTTON_CreateEx(320,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc3_default.btnHandle = BUTTON_CreateEx(400,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	     
	    BUTTON_SetBmpFileName(morefunc1_cmd.btnHandle, "bmp_pic70x28_1.bin",1);        
	    BUTTON_SetBmpFileName(morefunc2_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(morefunc3_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
		BUTTON_SetBmpFileName(buttons_count_value.btnHandle, "bmp_pic70x28_1.bin",1);			


	    BUTTON_SetBmpFileName(morefunc1_default.btnHandle, "bmp_pic70x28_2.bin",1);        
	    BUTTON_SetBmpFileName(morefunc2_default.btnHandle, "bmp_pic70x28_2.bin",1);
	    BUTTON_SetBmpFileName(morefunc3_default.btnHandle, "bmp_pic70x28_2.bin",1);
        BUTTON_SetBmpFileName(buttons_count_default.btnHandle, "bmp_pic70x28_2.bin",1); 	   
	    
	    BUTTON_SetBmpFileName(morefunc1_text.btnHandle,NULL,1);        
	    BUTTON_SetBmpFileName(morefunc2_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(morefunc3_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(buttons_count_text.btnHandle,NULL,1);
	    
	    BUTTON_SetBitmapEx(morefunc1_cmd.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(morefunc2_cmd.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(morefunc3_cmd.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(buttons_count_value.btnHandle,0,&bmp_struct70X28,0,0);

		BUTTON_SetBitmapEx(morefunc1_default.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(morefunc2_default.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(morefunc3_default.btnHandle,0,&bmp_struct70X28,0,0);
	   	BUTTON_SetBitmapEx(buttons_count_default.btnHandle,0,&bmp_struct70X28,0,0);    
		
	    BUTTON_SetTextAlign(morefunc1_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc2_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc3_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(buttons_count_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(morefunc1_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc2_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc3_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(buttons_count_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		BUTTON_SetTextAlign(morefunc1_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc2_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc3_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(buttons_count_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    BUTTON_SetBkColor(morefunc1_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(morefunc1_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(morefunc1_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(morefunc1_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(morefunc1_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(morefunc1_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(morefunc1_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(morefunc1_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

	    BUTTON_SetBkColor(morefunc2_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(morefunc2_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(morefunc2_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(morefunc2_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(morefunc2_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(morefunc2_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(morefunc2_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(morefunc2_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

	    BUTTON_SetBkColor(morefunc3_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(morefunc3_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(morefunc3_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(morefunc3_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(morefunc3_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(morefunc3_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(morefunc3_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(morefunc3_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

		BUTTON_SetBkColor(buttons_count_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(buttons_count_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(buttons_count_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(buttons_count_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

		BUTTON_SetBkColor(buttons_count_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(buttons_count_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(buttons_count_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(buttons_count_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

	    memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC1_ADDR,201);
	    BUTTON_SetText(morefunc1_cmd.btnHandle,cmd_code);
		
	    memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC2_ADDR,201);
	    BUTTON_SetText(morefunc2_cmd.btnHandle,cmd_code);
		
	    memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC3_ADDR,201);
	    BUTTON_SetText(morefunc3_cmd.btnHandle,cmd_code);

		memset(cmd_code,0,sizeof(cmd_code));
		sprintf(cmd_code,"%d",gCfgItems.morefunc_cnt);
		BUTTON_SetText(buttons_count_value.btnHandle,cmd_code);


		button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hPrintMoreBtnWnd,BUTTON_CF_SHOW,0,alloc_win_id());
           BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
           BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);


	     BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	     BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
	     BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextAlign(button_next.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	     

	    if(gCfgItems.multiple_language != 0)
	    {
	        BUTTON_SetText(morefunc1_text.btnHandle, machine_menu.moreItem_func1);
	        BUTTON_SetText(morefunc2_text.btnHandle, machine_menu.moreItem_func2);
	        BUTTON_SetText(morefunc3_text.btnHandle, machine_menu.moreItem_func3); 
			BUTTON_SetText(buttons_count_text.btnHandle, machine_menu.morefunc_cnt);  
			BUTTON_SetText(morefunc1_default.btnHandle, machine_menu.default_value);  
			BUTTON_SetText(morefunc2_default.btnHandle, machine_menu.default_value);  
			BUTTON_SetText(morefunc3_default.btnHandle, machine_menu.default_value);  
			BUTTON_SetText(buttons_count_default.btnHandle, machine_menu.default_value); 
		 	BUTTON_SetText(button_next.btnHandle,machine_menu.next);
	   }
    }
    else
    {
	    morefunc4_text.btnHandle = BUTTON_CreateEx(10,50,300,40,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc4_cmd.btnHandle = BUTTON_CreateEx(320,50,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc4_default.btnHandle = BUTTON_CreateEx(400,50,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    morefunc5_text.btnHandle = BUTTON_CreateEx(10,100,300,40,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc5_cmd.btnHandle = BUTTON_CreateEx(320,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc5_default.btnHandle = BUTTON_CreateEx(400,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    morefunc6_text.btnHandle = BUTTON_CreateEx(10,150,300,40,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc6_cmd.btnHandle = BUTTON_CreateEx(320,150,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc6_default.btnHandle = BUTTON_CreateEx(400,150,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    morefunc7_text.btnHandle = BUTTON_CreateEx(10,200,300,40,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc7_cmd.btnHandle = BUTTON_CreateEx(320,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    morefunc7_default.btnHandle = BUTTON_CreateEx(400,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPrintMoreBtnWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    BUTTON_SetBmpFileName(morefunc4_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(morefunc4_default.btnHandle, "bmp_pic70x28_2.bin",1); 

	    BUTTON_SetBmpFileName(morefunc5_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(morefunc5_default.btnHandle, "bmp_pic70x28_2.bin",1); 
	    BUTTON_SetBmpFileName(morefunc6_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(morefunc6_default.btnHandle, "bmp_pic70x28_2.bin",1); 
	    BUTTON_SetBmpFileName(morefunc7_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(morefunc7_default.btnHandle, "bmp_pic70x28_2.bin",1); 

	    BUTTON_SetBitmapEx(morefunc4_cmd.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(morefunc4_default.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(morefunc5_cmd.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(morefunc5_default.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(morefunc6_cmd.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(morefunc6_default.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(morefunc7_cmd.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(morefunc7_default.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28


	    BUTTON_SetBkColor(morefunc4_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(morefunc4_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(morefunc4_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(morefunc4_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

	    BUTTON_SetBkColor(morefunc5_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(morefunc5_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(morefunc5_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(morefunc5_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 
		
	    BUTTON_SetBkColor(morefunc6_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(morefunc6_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(morefunc6_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(morefunc6_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

	    BUTTON_SetBkColor(morefunc7_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(morefunc7_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(morefunc7_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(morefunc7_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(morefunc4_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(morefunc4_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(morefunc4_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(morefunc4_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

		BUTTON_SetBkColor(morefunc5_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(morefunc5_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(morefunc5_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(morefunc5_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);
		
		BUTTON_SetBkColor(morefunc6_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(morefunc6_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(morefunc6_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(morefunc6_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);
		
		BUTTON_SetBkColor(morefunc7_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(morefunc7_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(morefunc7_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(morefunc7_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

	    BUTTON_SetTextAlign(morefunc4_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc4_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc4_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(morefunc5_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc5_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc5_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(morefunc6_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc6_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc6_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(morefunc7_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc7_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(morefunc7_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC4_ADDR,201);
	    BUTTON_SetText(morefunc4_cmd.btnHandle,cmd_code);

		memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC5_ADDR,201);
	    BUTTON_SetText(morefunc5_cmd.btnHandle,cmd_code);

		memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC6_ADDR,201);
	    BUTTON_SetText(morefunc6_cmd.btnHandle,cmd_code);

		memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC7_ADDR,201);
	    BUTTON_SetText(morefunc7_cmd.btnHandle,cmd_code);

	    button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hPrintMoreBtnWnd,BUTTON_CF_SHOW,0,alloc_win_id());
           BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
        
           BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);

	     BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	     BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color);    
	     BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
	     
     	     BUTTON_SetTextAlign(button_previous.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    if(gCfgItems.multiple_language != 0)
	    {
	        BUTTON_SetText(morefunc4_text.btnHandle, machine_menu.moreItem_func4);
	        BUTTON_SetText(morefunc5_text.btnHandle, machine_menu.moreItem_func5);
	        BUTTON_SetText(morefunc6_text.btnHandle, machine_menu.moreItem_func6);
	        BUTTON_SetText(morefunc7_text.btnHandle, machine_menu.moreItem_func7);
	        BUTTON_SetText(morefunc4_default.btnHandle, machine_menu.default_value);
	        BUTTON_SetText(morefunc5_default.btnHandle, machine_menu.default_value);
	        BUTTON_SetText(morefunc6_default.btnHandle, machine_menu.default_value);
	        BUTTON_SetText(morefunc7_default.btnHandle, machine_menu.default_value);
			
	    	 BUTTON_SetText(button_previous.btnHandle,machine_menu.previous); 
	    }
    }

    button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hPrintMoreBtnWnd,BUTTON_CF_SHOW,0,alloc_win_id());
    
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
    BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0,0);
    BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 
    
    BUTTON_SetText(button_back.btnHandle,machine_menu.back);

}

void Clear_printMoreBtn()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hPrintMoreBtnWnd))
	{
		WM_DeleteWindow(hPrintMoreBtnWnd);
	}
}






