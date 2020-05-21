#include "gui.h"
#include "button.h"
#include "draw_ui.h"
//#include "Marlin.h"
//#include "cardreader.h"
#include "mks_tft_com.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hMaxFeedRateWnd;
static BUTTON_STRUCT XMaxFeedRate_text,YMaxFeedRate_text,ZMaxFeedRate_text,E0MaxFeedRate_text,E1MaxFeedRate_text;
static BUTTON_STRUCT XMaxFeedRate_value,YMaxFeedRate_value,ZMaxFeedRate_value,E0MaxFeedRate_value,E1MaxFeedRate_value;
static BUTTON_STRUCT XMaxFeedRate_default,YMaxFeedRate_default,ZMaxFeedRate_default,E0MaxFeedRate_default,E1MaxFeedRate_default;

static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void btnHandle_rest()
{
    XMaxFeedRate_text.btnHandle = 0;
    XMaxFeedRate_value.btnHandle = 0;
    XMaxFeedRate_default.btnHandle = 0;
    YMaxFeedRate_text.btnHandle = 0;
    YMaxFeedRate_value.btnHandle = 0;
    YMaxFeedRate_default.btnHandle = 0;
    ZMaxFeedRate_text.btnHandle = 0;
    ZMaxFeedRate_value.btnHandle = 0;
    ZMaxFeedRate_default.btnHandle = 0;
    E0MaxFeedRate_text.btnHandle = 0;   
    E0MaxFeedRate_value.btnHandle = 0;
    E0MaxFeedRate_default.btnHandle = 0;
    E1MaxFeedRate_text.btnHandle = 0;   
    E1MaxFeedRate_value.btnHandle = 0;
    E1MaxFeedRate_default.btnHandle = 0;          
    button_previous.btnHandle = 0;
    button_next.btnHandle = 0;
    button_back.btnHandle = 0;
}

static void cbMaxFeedRateWin(WM_MESSAGE * pMsg) {

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
    				last_disp_state = MAXFEEDRATE_UI;
    				Clear_MaxFeedRate();
    				draw_return_ui();
    			}	
                else if(pMsg->hWinSrc == button_next.btnHandle)
                {
                    current_page = 1;
                    last_disp_state = MAXFEEDRATE_UI;
                    Clear_MaxFeedRate();
                    draw_MaxFeedRate();
                }
                else if(pMsg->hWinSrc == button_previous.btnHandle)
                {
                    current_page = 0;
                    last_disp_state = MAXFEEDRATE_UI;
                    Clear_MaxFeedRate();
                    draw_MaxFeedRate();
                }                
    			else if(pMsg->hWinSrc == XMaxFeedRate_value.btnHandle)
    			{
    				last_disp_state = MAXFEEDRATE_UI;
    				Clear_MaxFeedRate();
    				value=XMaxFeedRate;
                    draw_NumberKey();    				
    			}
    			else if(pMsg->hWinSrc == YMaxFeedRate_value.btnHandle)

    			{
    				last_disp_state = MAXFEEDRATE_UI;
    				Clear_MaxFeedRate();
    				value=YMaxFeedRate;
                    draw_NumberKey();    				
    			}
    			else if(pMsg->hWinSrc == ZMaxFeedRate_value.btnHandle)

    			{
    				last_disp_state = MAXFEEDRATE_UI;
    				Clear_MaxFeedRate();
    				value=ZMaxFeedRate;
                    draw_NumberKey();                    
    		
    			}       
    			else if(pMsg->hWinSrc == E0MaxFeedRate_value.btnHandle)

    			{
    				last_disp_state = MAXFEEDRATE_UI;
    				Clear_MaxFeedRate();
    				value=E0MaxFeedRate;
                    draw_NumberKey();


    			}
    			else if(pMsg->hWinSrc == E1MaxFeedRate_value.btnHandle)

    			{
    				last_disp_state = MAXFEEDRATE_UI;
    				Clear_MaxFeedRate();
    				value=E1MaxFeedRate;
                    draw_NumberKey();

    			}
                #if 0
    			else if(pMsg->hWinSrc == XMaxFeedRate_default.btnHandle)

    			{
    				last_disp_state = MAXFEEDRATE_UI;
    				Clear_MaxFeedRate();

    			} 
    			else if(pMsg->hWinSrc == YMaxFeedRate_default.btnHandle)

    			{
    				last_disp_state = MAXFEEDRATE_UI;
    				Clear_MaxFeedRate();

    			}  
    			else if(pMsg->hWinSrc == ZMaxFeedRate_default.btnHandle)

    			{
    				last_disp_state = MAXFEEDRATE_UI;
    				Clear_MaxFeedRate();

    			} 
    			else if(pMsg->hWinSrc == E0MaxFeedRate_default.btnHandle)

    			{
    				last_disp_state = MAXFEEDRATE_UI;
    				Clear_MaxFeedRate();

    			}   
    			else if(pMsg->hWinSrc == E1MaxFeedRate_default.btnHandle)

    			{
    				last_disp_state = MAXFEEDRATE_UI;
    				Clear_MaxFeedRate();

    			}  
                #endif
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_MaxFeedRate()
{   
    int i;


    btnHandle_rest();
    
    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != MAXFEEDRATE_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = MAXFEEDRATE_UI;
    }
    disp_state = MAXFEEDRATE_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.MaxFeedRateConfTitle, TITLE_XPOS, TITLE_YPOS);

    hMaxFeedRateWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbMaxFeedRateWin, 0);

//	pushFIFO(&gcodeCmdTxFIFO,(unsigned char *)"M503\n");

    if(current_page != 1)
    {
        XMaxFeedRate_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        //XMaxFeedRate_value.btnHandle = BUTTON_CreateEx(270,50,90,40,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        XMaxFeedRate_value.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        YMaxFeedRate_text.btnHandle = BUTTON_CreateEx(10,100,240,40,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        //YMaxFeedRate_value.btnHandle = BUTTON_CreateEx(270,100,90,40,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        YMaxFeedRate_value.btnHandle = BUTTON_CreateEx(400,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        ZMaxFeedRate_text.btnHandle = BUTTON_CreateEx(10,150,240,40,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        //ZMaxFeedRate_value.btnHandle = BUTTON_CreateEx(270,150,90,40,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        ZMaxFeedRate_value.btnHandle = BUTTON_CreateEx(400,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        E0MaxFeedRate_text.btnHandle = BUTTON_CreateEx(10,200,240,40,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        //E0MaxFeedRate_value.btnHandle = BUTTON_CreateEx(270,200,90,40,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        E0MaxFeedRate_value.btnHandle = BUTTON_CreateEx(400,200+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        BUTTON_SetBmpFileName(XMaxFeedRate_value.btnHandle, "bmp_pic70x28_1.bin",1);        
        BUTTON_SetBmpFileName(YMaxFeedRate_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(ZMaxFeedRate_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(E0MaxFeedRate_value.btnHandle, "bmp_pic70x28_1.bin",1);
        //BUTTON_SetBmpFileName(XMaxFeedRate_default.btnHandle, "bmp_pic70x28_1.bin",1);
       // BUTTON_SetBmpFileName(YMaxFeedRate_default.btnHandle, "bmp_pic70x28_1.bin",1);     
        //BUTTON_SetBmpFileName(ZMaxFeedRate_default.btnHandle, "bmp_pic70x28_1.bin",1);
        //BUTTON_SetBmpFileName(E0MaxFeedRate_default.btnHandle, "bmp_pic70x28_1.bin",1);  
        
        BUTTON_SetBmpFileName(XMaxFeedRate_text.btnHandle,NULL,1);        
        BUTTON_SetBmpFileName(YMaxFeedRate_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(ZMaxFeedRate_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(E0MaxFeedRate_text.btnHandle,NULL,1);
        
        BUTTON_SetBitmapEx(XMaxFeedRate_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(YMaxFeedRate_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(ZMaxFeedRate_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(E0MaxFeedRate_value.btnHandle,0,&bmp_struct70X28,0,0); 
        //BUTTON_SetBitmapEx(XMaxFeedRate_default.btnHandle,0,&bmp_struct90X30,0,5);
        //BUTTON_SetBitmapEx(YMaxFeedRate_default.btnHandle,0,&bmp_struct90X30,0,5);
        //BUTTON_SetBitmapEx(ZMaxFeedRate_default.btnHandle,0,&bmp_struct90X30,0,5);
        //BUTTON_SetBitmapEx(E0MaxFeedRate_default.btnHandle,0,&bmp_struct90X30,0,5); 

        
        BUTTON_SetTextAlign(XMaxFeedRate_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(YMaxFeedRate_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(ZMaxFeedRate_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E0MaxFeedRate_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   
        BUTTON_SetTextAlign(XMaxFeedRate_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(YMaxFeedRate_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(ZMaxFeedRate_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E0MaxFeedRate_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

        BUTTON_SetBkColor(XMaxFeedRate_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(XMaxFeedRate_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(XMaxFeedRate_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(XMaxFeedRate_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(YMaxFeedRate_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(YMaxFeedRate_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(YMaxFeedRate_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(YMaxFeedRate_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(ZMaxFeedRate_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(ZMaxFeedRate_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(ZMaxFeedRate_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(ZMaxFeedRate_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(E0MaxFeedRate_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(E0MaxFeedRate_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(E0MaxFeedRate_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(E0MaxFeedRate_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hMaxFeedRateWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
    
        BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);
		///get information from machine
/*        
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%.1f",planner.max_feedrate_mm_s[X_AXIS]);
        BUTTON_SetText(XMaxFeedRate_value.btnHandle,cmd_code);        
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%.1f",planner.max_feedrate_mm_s[Y_AXIS]);
        BUTTON_SetText(YMaxFeedRate_value.btnHandle,cmd_code); 
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%.1f",planner.max_feedrate_mm_s[Z_AXIS]);
        BUTTON_SetText(ZMaxFeedRate_value.btnHandle,cmd_code); 
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%.1f",planner.max_feedrate_mm_s[E_AXIS]);
        BUTTON_SetText(E0MaxFeedRate_value.btnHandle,cmd_code); 
*/
    }
    else
    {
        E1MaxFeedRate_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        //E1MaxFeedRate_value.btnHandle = BUTTON_CreateEx(270,50,90,40,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        E1MaxFeedRate_value.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hMaxFeedRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        BUTTON_SetBmpFileName(E1MaxFeedRate_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(E1MaxFeedRate_default.btnHandle, "bmp_pic70x28_1.bin",1);
        
        BUTTON_SetBmpFileName(E1MaxFeedRate_text.btnHandle,NULL,1); 
        
        BUTTON_SetBitmapEx(E1MaxFeedRate_value.btnHandle,0,&bmp_struct70X28,0,0);
        //BUTTON_SetBitmapEx(E1MaxFeedRate_default.btnHandle,0,&bmp_struct90X30,0,5); 

        BUTTON_SetTextAlign(E1MaxFeedRate_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E1MaxFeedRate_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

        BUTTON_SetBkColor(E1MaxFeedRate_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(E1MaxFeedRate_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(E1MaxFeedRate_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(E1MaxFeedRate_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 


        button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hMaxFeedRateWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
        
        BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);
/*
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%.1f",planner.max_feedrate_mm_s[XYZE]);
        BUTTON_SetText(E1MaxFeedRate_value.btnHandle,cmd_code);        
*/  
    }
	disp_maxFeedRate();

     button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hMaxFeedRateWnd,BUTTON_CF_SHOW,0,alloc_win_id());
     
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
            BUTTON_SetText(XMaxFeedRate_text.btnHandle, machine_menu.XMaxFeedRate);
            BUTTON_SetText(YMaxFeedRate_text.btnHandle, machine_menu.YMaxFeedRate);
            BUTTON_SetText(ZMaxFeedRate_text.btnHandle, machine_menu.ZMaxFeedRate);
            BUTTON_SetText(E0MaxFeedRate_text.btnHandle, machine_menu.E0MaxFeedRate);
            BUTTON_SetText(button_next.btnHandle,machine_menu.next);
        }
        else
        {
            BUTTON_SetText(E1MaxFeedRate_text.btnHandle,machine_menu.E1MaxFeedRate);
            BUTTON_SetText(button_previous.btnHandle,machine_menu.previous);   
        }
         
        BUTTON_SetText(button_back.btnHandle,machine_menu.back);
        
              
     }

}


void Clear_MaxFeedRate()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hMaxFeedRateWnd))
	{
		WM_DeleteWindow(hMaxFeedRateWnd);
	}
}



void disp_maxFeedRate()
{
	if(gCfgItems.firmware_type == 1)
	{
		 if(current_page != 1)
	    {
			 memset(cmd_code,0,sizeof(cmd_code));
			 sprintf(cmd_code,"%d",gCfgItems.xMaxFeedRate);
			 BUTTON_SetText(XMaxFeedRate_value.btnHandle,cmd_code); 	   
			 memset(cmd_code,0,sizeof(cmd_code));
			 sprintf(cmd_code,"%d",gCfgItems.yMaxFeedRate);
			 BUTTON_SetText(YMaxFeedRate_value.btnHandle,cmd_code); 
			 memset(cmd_code,0,sizeof(cmd_code));
			 sprintf(cmd_code,"%d",gCfgItems.zMaxFeedRate);
			 BUTTON_SetText(ZMaxFeedRate_value.btnHandle,cmd_code); 
			 memset(cmd_code,0,sizeof(cmd_code));
			 sprintf(cmd_code,"%d",gCfgItems.e0_MaxFeedRate);
			 BUTTON_SetText(E0MaxFeedRate_value.btnHandle,cmd_code); 

	    }
	    else
	    {
	        memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%d",gCfgItems.e1_MaxFeedRate);
	        BUTTON_SetText(E1MaxFeedRate_value.btnHandle,cmd_code);     

	    }
	}

}

