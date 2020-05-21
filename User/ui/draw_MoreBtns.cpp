#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"
#include "spi_flash.h"
#include "pic_manager.h"



#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hMoreBtnsWnd;
static BUTTON_STRUCT moreBtn1_text,moreBtn2_text,moreBtn3_text,moreBtn4_text,moreBtn5_text,moreBtn6_text,moreBtn7_text;
static BUTTON_STRUCT moreBtn1_cmd,moreBtn2_cmd,moreBtn3_cmd,moreBtn4_cmd,moreBtn5_cmd,moreBtn6_cmd,moreBtn7_cmd;
static BUTTON_STRUCT moreBtn1_default,moreBtn2_default,moreBtn3_default,moreBtn4_default,moreBtn5_default,moreBtn6_default,moreBtn7_default;
static BUTTON_STRUCT buttons_count_text,buttons_count_value,buttons_count_default;

static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void cbMoreBtnsWnd(WM_MESSAGE * pMsg) {

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
    				last_disp_state = MOREBTN_UI;
    				Clear_MoreBtns();
					current_page = 0;
    				draw_return_ui();
    			}	
    			else if(pMsg->hWinSrc == buttons_count_value.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
	                    Clear_MoreBtns();
	                    value=more_btn_cnt;
	                    draw_NumberKey();
    			}
    			else if(pMsg->hWinSrc == buttons_count_default.btnHandle)
    			{
    				gCfgItems.MoreItem_pic_cnt = 5;
					memset(cmd_code,0,sizeof(cmd_code));
					sprintf(cmd_code,"%d",gCfgItems.MoreItem_pic_cnt);
					BUTTON_SetText(buttons_count_value.btnHandle,cmd_code);					
					HAL::AT24CXX_Write(BAK_MOREITEM_PIC_CNT,(uint8_t *)&gCfgItems.MoreItem_pic_cnt ,1);                
    			}				
    			else if(pMsg->hWinSrc == moreBtn1_cmd.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
	                    Clear_MoreBtns();
	                    valueType=btn1Cmd;
	                    draw_Keyboard();
    			}
    			else if(pMsg->hWinSrc == moreBtn2_cmd.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
	                    Clear_MoreBtns();
	                    valueType=btn2Cmd;
	                    draw_Keyboard();                    
    			}
    			else if(pMsg->hWinSrc == moreBtn3_cmd.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
	                    Clear_MoreBtns();
	                    valueType=btn3Cmd;
	                    draw_Keyboard();                    
    			} 
    			else if(pMsg->hWinSrc == moreBtn4_cmd.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
	                    Clear_MoreBtns();
	                    valueType=btn4Cmd;
	                    draw_Keyboard();                    
    			} 
			else if(pMsg->hWinSrc == moreBtn5_cmd.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
	                    Clear_MoreBtns();
	                    valueType=btn5Cmd;
	                    draw_Keyboard();                    
                    
    			}
			  			else if(pMsg->hWinSrc == moreBtn6_cmd.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
	                    Clear_MoreBtns();
	                    valueType=btn6Cmd;
	                    draw_Keyboard();                    
    			} 
			else if(pMsg->hWinSrc == moreBtn7_cmd.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
	                    Clear_MoreBtns();
	                    valueType=btn7Cmd;
	                    draw_Keyboard();                    
                    
    			}
			else if(pMsg->hWinSrc == moreBtn1_default.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD1_ADDR,(strlen(cmd_code)+1));
					BUTTON_SetText(moreBtn1_cmd.btnHandle, cmd_code);  

    			}
    			else if(pMsg->hWinSrc == moreBtn2_default.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD2_ADDR,(strlen(cmd_code)+1));
					BUTTON_SetText(moreBtn2_cmd.btnHandle, cmd_code);               
    			}
    			else if(pMsg->hWinSrc == moreBtn3_default.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD3_ADDR,(strlen(cmd_code)+1));
					BUTTON_SetText(moreBtn3_cmd.btnHandle, cmd_code);  

                  
    			} 
    			else if(pMsg->hWinSrc == moreBtn4_default.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD4_ADDR,(strlen(cmd_code)+1));
					BUTTON_SetText(moreBtn4_cmd.btnHandle, cmd_code);  

                    
                    
    			} 
			else if(pMsg->hWinSrc == moreBtn5_default.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD5_ADDR,(strlen(cmd_code)+1));
					BUTTON_SetText(moreBtn5_cmd.btnHandle, cmd_code);          
    			}
			    			else if(pMsg->hWinSrc == moreBtn6_default.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
					 memset(cmd_code,0,sizeof(cmd_code));
					strcpy((char*)cmd_code, "G28");
					flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD6_ADDR,(strlen(cmd_code)+1));
					BUTTON_SetText(moreBtn6_cmd.btnHandle, cmd_code);  

                    
                    
    			} 
			else if(pMsg->hWinSrc == moreBtn7_default.btnHandle)
    			{
    				last_disp_state = MOREBTN_UI;
					memset(cmd_code,0,sizeof(cmd_code));
				   strcpy((char*)cmd_code, "G28");
				   flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD7_ADDR,(strlen(cmd_code)+1));
				   BUTTON_SetText(moreBtn7_cmd.btnHandle, cmd_code);        
    			}
			else if(pMsg->hWinSrc == button_next.btnHandle)
	             {
	                    current_page = 1;
	                    last_disp_state = MOREBTN_UI;
	                    Clear_MoreBtns();
	                    draw_MoreBtns();
	              }
	              else if(pMsg->hWinSrc == button_previous.btnHandle)
	              {
	                    current_page = 0;
	                    last_disp_state = MOREBTN_UI;
	                    Clear_MoreBtns();
	                    draw_MoreBtns();
	              } 
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_MoreBtns()
{   
    int i;

    moreBtn1_text.btnHandle=0;
    moreBtn2_text.btnHandle=0;
    moreBtn3_text.btnHandle=0;
    moreBtn4_text.btnHandle=0;
    moreBtn5_text.btnHandle=0;
    moreBtn6_text.btnHandle=0;
    moreBtn7_text.btnHandle=0;

    moreBtn1_cmd.btnHandle=0;
    moreBtn2_cmd.btnHandle=0;
    moreBtn3_cmd.btnHandle=0;
    moreBtn4_cmd.btnHandle=0;
    moreBtn5_cmd.btnHandle=0;
    moreBtn6_cmd.btnHandle=0;
    moreBtn7_cmd.btnHandle=0;

    moreBtn1_default.btnHandle=0;
    moreBtn2_default.btnHandle=0;
    moreBtn3_default.btnHandle=0;
    moreBtn4_default.btnHandle=0;
    moreBtn5_default.btnHandle=0;
    moreBtn6_default.btnHandle=0;
    moreBtn7_default.btnHandle=0;

	
	buttons_count_text.btnHandle = 0;
	buttons_count_value.btnHandle = 0;
	buttons_count_default.btnHandle = 0;

    button_back.btnHandle=0;

    button_next.btnHandle=0;
    button_previous.btnHandle=0;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != MOREBTN_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = MOREBTN_UI;
    }
    disp_state = MOREBTN_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.MoreButtonConfTitle, TITLE_XPOS, TITLE_YPOS);

    hMoreBtnsWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbMoreBtnsWnd, 0);

    if(current_page != 1)
    {
		buttons_count_text.btnHandle = BUTTON_CreateEx(10,50,300,40,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		buttons_count_value.btnHandle = BUTTON_CreateEx(320,50,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		buttons_count_default.btnHandle = BUTTON_CreateEx(400,50,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
		moreBtn1_text.btnHandle = BUTTON_CreateEx(10,100,300,40,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		moreBtn1_cmd.btnHandle = BUTTON_CreateEx(320,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		moreBtn1_default.btnHandle = BUTTON_CreateEx(400,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    moreBtn2_text.btnHandle = BUTTON_CreateEx(10,150,300,40,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn2_cmd.btnHandle = BUTTON_CreateEx(320,150,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn2_default.btnHandle = BUTTON_CreateEx(400,150,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    moreBtn3_text.btnHandle = BUTTON_CreateEx(10,200,300,40,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn3_cmd.btnHandle = BUTTON_CreateEx(320,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn3_default.btnHandle = BUTTON_CreateEx(400,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	     
	    BUTTON_SetBmpFileName(moreBtn1_cmd.btnHandle, "bmp_pic70x28_1.bin",1);        
	    BUTTON_SetBmpFileName(moreBtn2_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(moreBtn3_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
		BUTTON_SetBmpFileName(buttons_count_value.btnHandle, "bmp_pic70x28_1.bin",1);			

	    BUTTON_SetBmpFileName(moreBtn1_default.btnHandle, "bmp_pic70x28_2.bin",1);        
	    BUTTON_SetBmpFileName(moreBtn2_default.btnHandle, "bmp_pic70x28_2.bin",1);
	    BUTTON_SetBmpFileName(moreBtn3_default.btnHandle, "bmp_pic70x28_2.bin",1);
        BUTTON_SetBmpFileName(buttons_count_default.btnHandle, "bmp_pic70x28_2.bin",1); 	   
	    
	    BUTTON_SetBmpFileName(moreBtn1_text.btnHandle,NULL,1);        
	    BUTTON_SetBmpFileName(moreBtn2_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(moreBtn3_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(buttons_count_text.btnHandle,NULL,1);
	    
	    BUTTON_SetBitmapEx(moreBtn1_cmd.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(moreBtn2_cmd.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(moreBtn3_cmd.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(buttons_count_value.btnHandle,0,&bmp_struct70X28,0,0);

		BUTTON_SetBitmapEx(moreBtn1_default.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(moreBtn2_default.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(moreBtn3_default.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(buttons_count_default.btnHandle,0,&bmp_struct70X28,0,0);
	        
	    BUTTON_SetTextAlign(moreBtn1_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn2_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn3_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(buttons_count_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(moreBtn1_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn2_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn3_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(buttons_count_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		BUTTON_SetTextAlign(moreBtn1_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn2_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn3_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(buttons_count_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    BUTTON_SetBkColor(moreBtn1_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(moreBtn1_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(moreBtn1_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(moreBtn1_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(moreBtn1_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(moreBtn1_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(moreBtn1_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(moreBtn1_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

	    BUTTON_SetBkColor(moreBtn2_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(moreBtn2_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(moreBtn2_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(moreBtn2_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(moreBtn2_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(moreBtn2_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(moreBtn2_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(moreBtn2_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

	    BUTTON_SetBkColor(moreBtn3_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(moreBtn3_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(moreBtn3_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(moreBtn3_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(moreBtn3_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(moreBtn3_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(moreBtn3_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(moreBtn3_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

		BUTTON_SetBkColor(buttons_count_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(buttons_count_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(buttons_count_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(buttons_count_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

		BUTTON_SetBkColor(buttons_count_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(buttons_count_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(buttons_count_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(buttons_count_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

	    memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD1_ADDR,201);
	    BUTTON_SetText(moreBtn1_cmd.btnHandle,cmd_code);
	    memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD2_ADDR,201);
	    BUTTON_SetText(moreBtn2_cmd.btnHandle,cmd_code);
	    memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD3_ADDR,201);
	    BUTTON_SetText(moreBtn3_cmd.btnHandle,cmd_code);

		memset(cmd_code,0,sizeof(cmd_code));
		sprintf(cmd_code,"%d",gCfgItems.MoreItem_pic_cnt);
		BUTTON_SetText(buttons_count_value.btnHandle,cmd_code);


		button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hMoreBtnsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
           BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
           BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);


	     BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	     BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
	     BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextAlign(button_next.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	     

	    if(gCfgItems.multiple_language != 0)
	    {
	        BUTTON_SetText(moreBtn1_text.btnHandle, machine_menu.moreItem_btn1);
	        BUTTON_SetText(moreBtn2_text.btnHandle, machine_menu.moreItem_btn2);
	        BUTTON_SetText(moreBtn3_text.btnHandle, machine_menu.moreItem_btn3); 
			BUTTON_SetText(buttons_count_text.btnHandle, machine_menu.moreItem_cnt);  
			BUTTON_SetText(moreBtn1_default.btnHandle, machine_menu.default_value);  
			BUTTON_SetText(moreBtn2_default.btnHandle, machine_menu.default_value);  
			BUTTON_SetText(moreBtn3_default.btnHandle, machine_menu.default_value);  
			BUTTON_SetText(buttons_count_default.btnHandle, machine_menu.default_value);  
		 	BUTTON_SetText(button_next.btnHandle,machine_menu.next);
	   }
    }
    else
    {
	    moreBtn4_text.btnHandle = BUTTON_CreateEx(10,50,300,40,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn4_cmd.btnHandle = BUTTON_CreateEx(320,50,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn4_default.btnHandle = BUTTON_CreateEx(400,50,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    moreBtn5_text.btnHandle = BUTTON_CreateEx(10,100,300,40,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn5_cmd.btnHandle = BUTTON_CreateEx(320,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn5_default.btnHandle = BUTTON_CreateEx(400,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    moreBtn6_text.btnHandle = BUTTON_CreateEx(10,150,300,40,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn6_cmd.btnHandle = BUTTON_CreateEx(320,150,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn6_default.btnHandle = BUTTON_CreateEx(400,150,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    moreBtn7_text.btnHandle = BUTTON_CreateEx(10,200,300,40,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn7_cmd.btnHandle = BUTTON_CreateEx(320,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    moreBtn7_default.btnHandle = BUTTON_CreateEx(400,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMoreBtnsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    BUTTON_SetBmpFileName(moreBtn4_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(moreBtn4_default.btnHandle, "bmp_pic70x28_2.bin",1); 

	    BUTTON_SetBmpFileName(moreBtn5_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(moreBtn5_default.btnHandle, "bmp_pic70x28_2.bin",1); 
	    BUTTON_SetBmpFileName(moreBtn6_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(moreBtn6_default.btnHandle, "bmp_pic70x28_2.bin",1); 
	    BUTTON_SetBmpFileName(moreBtn7_cmd.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(moreBtn7_default.btnHandle, "bmp_pic70x28_2.bin",1); 

	    BUTTON_SetBitmapEx(moreBtn4_cmd.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(moreBtn4_default.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(moreBtn5_cmd.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(moreBtn5_default.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(moreBtn6_cmd.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(moreBtn6_default.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(moreBtn7_cmd.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(moreBtn7_default.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28


	    BUTTON_SetBkColor(moreBtn4_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(moreBtn4_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(moreBtn4_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(moreBtn4_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

	    BUTTON_SetBkColor(moreBtn5_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(moreBtn5_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(moreBtn5_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(moreBtn5_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 
		
	    BUTTON_SetBkColor(moreBtn6_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(moreBtn6_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(moreBtn6_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(moreBtn6_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

	    BUTTON_SetBkColor(moreBtn7_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(moreBtn7_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(moreBtn7_cmd.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(moreBtn7_cmd.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(moreBtn4_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(moreBtn4_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(moreBtn4_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(moreBtn4_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

		BUTTON_SetBkColor(moreBtn5_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(moreBtn5_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(moreBtn5_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(moreBtn5_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);
		
		BUTTON_SetBkColor(moreBtn6_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(moreBtn6_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(moreBtn6_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(moreBtn6_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);
		
		BUTTON_SetBkColor(moreBtn7_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
	    BUTTON_SetBkColor(moreBtn7_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
	    BUTTON_SetTextColor(moreBtn7_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
	    BUTTON_SetTextColor(moreBtn7_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

	    BUTTON_SetTextAlign(moreBtn4_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn4_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn4_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(moreBtn5_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn5_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn5_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(moreBtn6_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn6_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn6_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(moreBtn7_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn7_cmd.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(moreBtn7_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD4_ADDR,201);
	    BUTTON_SetText(moreBtn4_cmd.btnHandle,cmd_code);

		memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD5_ADDR,201);
	    BUTTON_SetText(moreBtn5_cmd.btnHandle,cmd_code);

		memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD6_ADDR,201);
	    BUTTON_SetText(moreBtn6_cmd.btnHandle,cmd_code);

		memset(cmd_code,0,sizeof(cmd_code));
		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD7_ADDR,201);
	    BUTTON_SetText(moreBtn7_cmd.btnHandle,cmd_code);

	    button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hMoreBtnsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
           BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
        
           BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);

	     BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	     BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color);    
	     BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
	     
     	     BUTTON_SetTextAlign(button_previous.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    if(gCfgItems.multiple_language != 0)
	    {
	        BUTTON_SetText(moreBtn4_text.btnHandle, machine_menu.moreItem_btn4);
	        BUTTON_SetText(moreBtn5_text.btnHandle, machine_menu.moreItem_btn5);
	        BUTTON_SetText(moreBtn6_text.btnHandle, machine_menu.moreItem_btn6);
	        BUTTON_SetText(moreBtn7_text.btnHandle, machine_menu.moreItem_btn7);
	        BUTTON_SetText(moreBtn4_default.btnHandle, machine_menu.default_value);
	        BUTTON_SetText(moreBtn5_default.btnHandle, machine_menu.default_value);
	        BUTTON_SetText(moreBtn6_default.btnHandle, machine_menu.default_value);
	        BUTTON_SetText(moreBtn7_default.btnHandle, machine_menu.default_value);			
	    	BUTTON_SetText(button_previous.btnHandle,machine_menu.previous); 
	    }
    }

    button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hMoreBtnsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
    
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
    BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0,0);
    BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 
    
    BUTTON_SetText(button_back.btnHandle,machine_menu.back);

}

void Clear_MoreBtns()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hMoreBtnsWnd))
	{
		WM_DeleteWindow(hMoreBtnsWnd);
	}
}






