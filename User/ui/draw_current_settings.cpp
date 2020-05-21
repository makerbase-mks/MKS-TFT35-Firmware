#include "gui.h"
#include "button.h"
#include "draw_ui.h"
//#include "mks_tft_com.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hCurrentWnd;
static BUTTON_STRUCT XCurrent_text,YCurrent_text,ZCurrent_text,E0Current_text,E1Current_text;
static BUTTON_STRUCT XCurrent_value,YCurrent_value,ZCurrent_value,E0Current_value,E1Current_value;
static BUTTON_STRUCT XCurrent_default,YCurrent_default,ZCurrent_default,E0Current_default,E1Current_default;

static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void btnHandle_rest()
{
    XCurrent_text.btnHandle = 0;
    XCurrent_value.btnHandle = 0;
    XCurrent_default.btnHandle = 0;
    YCurrent_text.btnHandle = 0;
    YCurrent_value.btnHandle = 0;
    YCurrent_default.btnHandle = 0;
    ZCurrent_text.btnHandle = 0;
    ZCurrent_value.btnHandle = 0;
    ZCurrent_default.btnHandle = 0;
    E0Current_text.btnHandle = 0;   
    E0Current_value.btnHandle = 0;
    E0Current_default.btnHandle = 0;
    E1Current_text.btnHandle = 0;   
    E1Current_value.btnHandle = 0;
    E1Current_default.btnHandle = 0;          
    button_previous.btnHandle = 0;
    button_next.btnHandle = 0;
    button_back.btnHandle = 0;
}

static void cbCurrentWin(WM_MESSAGE * pMsg) {

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
    				last_disp_state = CURRENTCONF_UI;
    				Clear_currentSetting();
    				draw_return_ui();
    			}	
                else if(pMsg->hWinSrc == button_next.btnHandle)
                {
                    current_page = 1;
                    last_disp_state = CURRENTCONF_UI;
                    Clear_currentSetting();
                    draw_currentSetting();
                }
                else if(pMsg->hWinSrc == button_previous.btnHandle)
                {
                    current_page = 0;
                    last_disp_state = CURRENTCONF_UI;
                    Clear_currentSetting();
                    draw_currentSetting();
                }                
    			else if(pMsg->hWinSrc == XCurrent_value.btnHandle)
    			{
    				last_disp_state = CURRENTCONF_UI;
    				Clear_currentSetting();
       				value=current_x;
                    draw_NumberKey();    				
    			}
    			else if(pMsg->hWinSrc == YCurrent_value.btnHandle)

    			{
    				last_disp_state = CURRENTCONF_UI;
    				Clear_currentSetting();
       				value=current_y;
                    draw_NumberKey();    				
    			}
    			else if(pMsg->hWinSrc == ZCurrent_value.btnHandle)

    			{
    				last_disp_state = CURRENTCONF_UI;
    				Clear_currentSetting();
        			value=current_z;
                    draw_NumberKey();                   
    		
    			}       
    			else if(pMsg->hWinSrc == E0Current_value.btnHandle)

    			{
    				last_disp_state = CURRENTCONF_UI;
    				Clear_currentSetting();
       				value=current_E0;
                    draw_NumberKey();

    			}
    			else if(pMsg->hWinSrc == E1Current_value.btnHandle)

    			{
    				last_disp_state = CURRENTCONF_UI;
    				Clear_currentSetting();
       				value=current_E1;
                    draw_NumberKey();

    			}  
                #if 0
    			else if(pMsg->hWinSrc == XCurrent_default.btnHandle)

    			{
    				last_disp_state = CURRENTCONF_UI;
    				Clear_currentSetting();

    			} 
    			else if(pMsg->hWinSrc == YCurrent_default.btnHandle)

    			{
    				last_disp_state = CURRENTCONF_UI;
    				Clear_currentSetting();

    			}  
    			else if(pMsg->hWinSrc == ZCurrent_default.btnHandle)

    			{
    				last_disp_state = CURRENTCONF_UI;
    				Clear_currentSetting();

    			} 
    			else if(pMsg->hWinSrc == E0Current_default.btnHandle)

    			{
    				last_disp_state = CURRENTCONF_UI;
    				Clear_currentSetting();

    			}   
    			else if(pMsg->hWinSrc == E1Current_default.btnHandle)

    			{
    				last_disp_state = CURRENTCONF_UI;
    				Clear_currentSetting();

    			}  
                 #endif
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_currentSetting()
{   
    int i;


    btnHandle_rest();
    
    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != CURRENTCONF_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = CURRENTCONF_UI;
    }
    disp_state = CURRENTCONF_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.CurrentConfTitle, TITLE_XPOS, TITLE_YPOS);

    hCurrentWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbCurrentWin, 0);


    if(current_page != 1)
    {
        XCurrent_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hCurrentWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        XCurrent_value.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hCurrentWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        YCurrent_text.btnHandle = BUTTON_CreateEx(10,100,240,40,hCurrentWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        YCurrent_value.btnHandle = BUTTON_CreateEx(400,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hCurrentWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        ZCurrent_text.btnHandle = BUTTON_CreateEx(10,150,240,40,hCurrentWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        ZCurrent_value.btnHandle = BUTTON_CreateEx(400,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hCurrentWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        E0Current_text.btnHandle = BUTTON_CreateEx(10,200,240,40,hCurrentWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
      
        E0Current_value.btnHandle = BUTTON_CreateEx(400,200+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hCurrentWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        BUTTON_SetBmpFileName(XCurrent_value.btnHandle, "bmp_pic70x28_1.bin",1);        
        BUTTON_SetBmpFileName(YCurrent_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(ZCurrent_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(E0Current_value.btnHandle, "bmp_pic70x28_1.bin",1);

        
        BUTTON_SetBmpFileName(XCurrent_text.btnHandle,NULL,1);        
        BUTTON_SetBmpFileName(YCurrent_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(ZCurrent_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(E0Current_text.btnHandle,NULL,1);
        
        BUTTON_SetBitmapEx(XCurrent_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(YCurrent_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(ZCurrent_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(E0Current_value.btnHandle,0,&bmp_struct70X28,0,0); 


        
        BUTTON_SetTextAlign(XCurrent_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(YCurrent_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(ZCurrent_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E0Current_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   
        BUTTON_SetTextAlign(XCurrent_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(YCurrent_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(ZCurrent_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E0Current_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER ); 

        BUTTON_SetBkColor(XCurrent_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(XCurrent_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(XCurrent_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(XCurrent_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(YCurrent_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(YCurrent_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(YCurrent_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(YCurrent_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(ZCurrent_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(ZCurrent_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(ZCurrent_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(ZCurrent_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(E0Current_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(E0Current_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(E0Current_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(E0Current_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hCurrentWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
    
        BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);

    }
    else
    {
        E1Current_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hCurrentWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
      
        E1Current_value.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hCurrentWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        BUTTON_SetBmpFileName(E1Current_value.btnHandle, "bmp_pic70x28_1.bin",1);
       
        
        BUTTON_SetBmpFileName(E1Current_text.btnHandle,NULL,1); 
        
        BUTTON_SetBitmapEx(E1Current_value.btnHandle,0,&bmp_struct70X28,0,0);
       

        BUTTON_SetTextAlign(E1Current_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E1Current_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetBkColor(E1Current_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(E1Current_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(E1Current_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(E1Current_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hCurrentWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
        
        BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);
 
    }

     button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hCurrentWnd,BUTTON_CF_SHOW,0,alloc_win_id());
     
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
            BUTTON_SetText(XCurrent_text.btnHandle, machine_menu.X_Current);
            BUTTON_SetText(YCurrent_text.btnHandle, machine_menu.Y_Current);
            BUTTON_SetText(ZCurrent_text.btnHandle, machine_menu.Z_Current);
            BUTTON_SetText(E0Current_text.btnHandle, machine_menu.E0_Current);
            BUTTON_SetText(button_next.btnHandle,machine_menu.next);
        }
        else
        {
            BUTTON_SetText(E1Current_text.btnHandle,machine_menu.E1_Current);
            BUTTON_SetText(button_previous.btnHandle,machine_menu.previous);   
        }
         
        BUTTON_SetText(button_back.btnHandle,machine_menu.back);
        
              
     }
	disp_motor_current();
}


void Clear_currentSetting()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hCurrentWnd))
	{
		WM_DeleteWindow(hCurrentWnd);
	}
}

void disp_motor_current()
{
	if(gCfgItems.firmware_type == 1)
	{
		if (current_page != 1 )
		{
			memset(cmd_code,0,sizeof(cmd_code));
         sprintf(cmd_code,"%d",gCfgItems.xCurrent);
         BUTTON_SetText(XCurrent_value.btnHandle,cmd_code);     
		 memset(cmd_code,0,sizeof(cmd_code));
         sprintf(cmd_code,"%d",gCfgItems.yCurrent);
         BUTTON_SetText(YCurrent_value.btnHandle,cmd_code);     
		 	     memset(cmd_code,0,sizeof(cmd_code));
         sprintf(cmd_code,"%d",gCfgItems.zCurrent);
         BUTTON_SetText(ZCurrent_value.btnHandle,cmd_code);     
		 	     memset(cmd_code,0,sizeof(cmd_code));
         sprintf(cmd_code,"%d",gCfgItems.e0Current);
         BUTTON_SetText(E0Current_value.btnHandle,cmd_code);     
		}
		else 
		{
		memset(cmd_code,0,sizeof(cmd_code));
         sprintf(cmd_code,"%d",gCfgItems.e1Current);
         BUTTON_SetText(E1Current_value.btnHandle,cmd_code); 
		}
	}

				     	 
}






