#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hPausePosWnd;
static BUTTON_STRUCT X_position_text,Y_position_text,Z_position_text;
static BUTTON_STRUCT X_position_value,Y_position_value,Z_position_value;
static BUTTON_STRUCT X_position_default,Y_position_default,Z_position_default;

static  BUTTON_STRUCT button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void cbPausePosWin(WM_MESSAGE * pMsg) {

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
//		            GUI_FillRect(10, 240, 470,240);
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
    				last_disp_state = PAUSE_POSITION_UI;
    				Clear_PausePos();
    				draw_return_ui();
    			}				
    			else if(pMsg->hWinSrc == X_position_value.btnHandle)
    			{
    				last_disp_state = PAUSE_POSITION_UI;
	                    Clear_PausePos();
	                    value=Position_x;
	                    draw_NumberKey();
    			}
    			else if(pMsg->hWinSrc == Y_position_value.btnHandle)
    			{
    				last_disp_state = PAUSE_POSITION_UI;
	                    Clear_PausePos();
	                    value=Position_y;
	                    draw_NumberKey();                    
    			}
    			else if(pMsg->hWinSrc == Z_position_value.btnHandle)
    			{
    				last_disp_state = PAUSE_POSITION_UI;
	                    Clear_PausePos();
	                    value=Position_z;
	                    draw_NumberKey();                    
    			} 
				else if(pMsg->hWinSrc == X_position_default.btnHandle)
    			{
    				gCfgItems.Pause_XPOS = -1;
    				memset(cmd_code,0,sizeof(cmd_code));
					sprintf(cmd_code,"%d",gCfgItems.Pause_XPOS);
					BUTTON_SetText(X_position_value.btnHandle,cmd_code);		
    				HAL::AT24CXX_Write(BAK_PAUSE_XPOS_ADDR,(uint8_t *)&gCfgItems.Pause_XPOS,2);
    			}
    			else if(pMsg->hWinSrc == Y_position_default.btnHandle)
    			{
    				gCfgItems.Pause_YPOS = -1;
    				memset(cmd_code,0,sizeof(cmd_code));
					sprintf(cmd_code,"%d",gCfgItems.Pause_YPOS);
					BUTTON_SetText(Y_position_value.btnHandle,cmd_code);	

					HAL::AT24CXX_Write(BAK_PAUSE_YPOS_ADDR,(uint8_t *)&gCfgItems.Pause_YPOS,2);	                    
    			}
    			else if(pMsg->hWinSrc == Z_position_default.btnHandle)
    			{
    				gCfgItems.Pause_ZADD = 10;
    				memset(cmd_code,0,sizeof(cmd_code));
					sprintf(cmd_code,"%d",gCfgItems.Pause_ZADD);
					BUTTON_SetText(Z_position_value.btnHandle,cmd_code);	
                    HAL::AT24CXX_Write(BAK_PAUSE_ZADD_ADDR,(uint8_t *)&gCfgItems.Pause_ZADD,2);
    			} 
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_PausePos()
{   
    int i;

    X_position_text.btnHandle=0;
    Y_position_text.btnHandle=0;
    Z_position_text.btnHandle=0;


    X_position_value.btnHandle=0;
    Y_position_value.btnHandle=0;
    Z_position_value.btnHandle=0;
	
	X_position_default.btnHandle=0;
    Y_position_default.btnHandle=0;
    Z_position_default.btnHandle=0;

    button_back.btnHandle=0;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != PAUSE_POSITION_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = PAUSE_POSITION_UI;
    }
    disp_state = PAUSE_POSITION_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.PositionPuaseConfTitle, TITLE_XPOS, TITLE_YPOS);

    hPausePosWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbPausePosWin, 0);
		
		X_position_text.btnHandle = BUTTON_CreateEx(10,50,300,40,hPausePosWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		X_position_value.btnHandle = BUTTON_CreateEx(320,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPausePosWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		X_position_default.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPausePosWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
		Y_position_text.btnHandle = BUTTON_CreateEx(10,100,300,40,hPausePosWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		Y_position_value.btnHandle = BUTTON_CreateEx(320,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPausePosWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		Y_position_default.btnHandle = BUTTON_CreateEx(400,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPausePosWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
		Z_position_text.btnHandle = BUTTON_CreateEx(10,150,300,40,hPausePosWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		Z_position_value.btnHandle = BUTTON_CreateEx(320,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPausePosWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		Z_position_default.btnHandle = BUTTON_CreateEx(400,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hPausePosWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
	     
	    BUTTON_SetBmpFileName(X_position_value.btnHandle, "bmp_pic70x28_1.bin",1);        
	    BUTTON_SetBmpFileName(Y_position_value.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(Z_position_value.btnHandle, "bmp_pic70x28_1.bin",1);	


        BUTTON_SetBmpFileName(X_position_default.btnHandle, "bmp_pic70x28_2.bin",1); 	   
        BUTTON_SetBmpFileName(Y_position_default.btnHandle, "bmp_pic70x28_2.bin",1); 	
        BUTTON_SetBmpFileName(Z_position_default.btnHandle, "bmp_pic70x28_2.bin",1); 	
	    
	    BUTTON_SetBmpFileName(X_position_text.btnHandle,NULL,1);        
	    BUTTON_SetBmpFileName(Y_position_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(Z_position_text.btnHandle,NULL,1);
	    
	    BUTTON_SetBitmapEx(X_position_value.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(Y_position_value.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(Z_position_value.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(X_position_default.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(Y_position_default.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(Z_position_default.btnHandle,0,&bmp_struct70X28,0,0);

	        
	    BUTTON_SetTextAlign(X_position_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(Y_position_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(Z_position_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(X_position_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(Y_position_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(Z_position_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(X_position_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(Y_position_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
		BUTTON_SetTextAlign(Z_position_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
						

	    BUTTON_SetBkColor(X_position_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(X_position_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(X_position_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(X_position_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

	    BUTTON_SetBkColor(Y_position_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(Y_position_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(Y_position_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(Y_position_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 
		
	    BUTTON_SetBkColor(Z_position_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(Z_position_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(Z_position_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(Z_position_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(X_position_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(X_position_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(X_position_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(X_position_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

		BUTTON_SetBkColor(Y_position_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(Y_position_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(Y_position_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(Y_position_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);
		
		BUTTON_SetBkColor(Z_position_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(Z_position_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(Z_position_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(Z_position_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);

	    memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.Pause_XPOS);
	    BUTTON_SetText(X_position_value.btnHandle,cmd_code);
		
	    memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.Pause_YPOS);
	    BUTTON_SetText(Y_position_value.btnHandle,cmd_code);
		
	    memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.Pause_ZADD);
	    BUTTON_SetText(Z_position_value.btnHandle,cmd_code);
		
	    if(gCfgItems.multiple_language != 0)
	    {
	        BUTTON_SetText(X_position_text.btnHandle, machine_menu.xPosition);
	        BUTTON_SetText(Y_position_text.btnHandle, machine_menu.yPosition);
	        BUTTON_SetText(Z_position_text.btnHandle, machine_menu.zPosition);   
			BUTTON_SetText(X_position_default.btnHandle, machine_menu.default_value); 
			BUTTON_SetText(Y_position_default.btnHandle, machine_menu.default_value); 
			BUTTON_SetText(Z_position_default.btnHandle, machine_menu.default_value);   			
	   }
   
    button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hPausePosWnd,BUTTON_CF_SHOW,0,alloc_win_id());
    
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
    BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0,0);
    BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 
    
    BUTTON_SetText(button_back.btnHandle,machine_menu.back);

}

void Clear_PausePos()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hPausePosWnd))
	{
		WM_DeleteWindow(hPausePosWnd);
	}
}






