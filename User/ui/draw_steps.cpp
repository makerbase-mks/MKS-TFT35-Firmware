#include "gui.h"
#include "button.h"
#include "draw_ui.h"
//#include "Marlin.h"
//#include "cardreader.h"
#include "mks_tft_com.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hStepsWnd;
static BUTTON_STRUCT XSteps_text,YSteps_text,ZSteps_text,E0Steps_text,E1Steps_text;
static BUTTON_STRUCT XSteps_value,YSteps_value,ZSteps_value,E0Steps_value,E1Steps_value;
static BUTTON_STRUCT XSteps_default,YSteps_default,ZSteps_default,E0Steps_default,E1Steps_default;

static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void btnHandle_rest()
{
    XSteps_text.btnHandle = 0;
    XSteps_value.btnHandle = 0;
    XSteps_default.btnHandle = 0;
    YSteps_text.btnHandle = 0;
    YSteps_value.btnHandle = 0;
    YSteps_default.btnHandle = 0;
    ZSteps_text.btnHandle = 0;
    ZSteps_value.btnHandle = 0;
    ZSteps_default.btnHandle = 0;
    E0Steps_text.btnHandle = 0;   
    E0Steps_value.btnHandle = 0;
    E0Steps_default.btnHandle = 0;
    E1Steps_text.btnHandle = 0;   
    E1Steps_value.btnHandle = 0;
    E1Steps_default.btnHandle = 0;          
    button_previous.btnHandle = 0;
    button_next.btnHandle = 0;
    button_back.btnHandle = 0;
}

static void cbStepsWin(WM_MESSAGE * pMsg) {

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
    				last_disp_state = STEPS_UI;
    				Clear_Steps();
    				draw_return_ui();
    			}	
                else if(pMsg->hWinSrc == button_next.btnHandle)
                {
                    current_page = 1;
                    last_disp_state = STEPS_UI;
                    Clear_Steps();
                    draw_Steps();
                }
                else if(pMsg->hWinSrc == button_previous.btnHandle)
                {
                    current_page = 0;
                    last_disp_state = STEPS_UI;
                    Clear_Steps();
                    draw_Steps();
                }                
    			else if(pMsg->hWinSrc == XSteps_value.btnHandle)
    			{
    				last_disp_state = STEPS_UI;
    				Clear_Steps();
       				value=Xstep;
                    draw_NumberKey();    				
    			}
    			else if(pMsg->hWinSrc == YSteps_value.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Steps();
       				value=Ystep;
                    draw_NumberKey();    				
    			}
    			else if(pMsg->hWinSrc == ZSteps_value.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Steps();
        			value=Zstep;
                    draw_NumberKey();                   
    		
    			}       
    			else if(pMsg->hWinSrc == E0Steps_value.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Steps();
       				value=E0step;
                    draw_NumberKey();

    			}
    			else if(pMsg->hWinSrc == E1Steps_value.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Steps();
       				value=E1step;
                    draw_NumberKey();

    			}  
                #if 0
    			else if(pMsg->hWinSrc == XSteps_default.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Steps();

    			} 
    			else if(pMsg->hWinSrc == YSteps_default.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Steps();

    			}  
    			else if(pMsg->hWinSrc == ZSteps_default.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Steps();

    			} 
    			else if(pMsg->hWinSrc == E0Steps_default.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Steps();

    			}   
    			else if(pMsg->hWinSrc == E1Steps_default.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Steps();

    			}  
                 #endif
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_Steps()
{   
    int i;


    btnHandle_rest();
    
    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != STEPS_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = STEPS_UI;
    }
    disp_state = STEPS_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.StepsConfTitle, TITLE_XPOS, TITLE_YPOS);

    hStepsWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbStepsWin, 0);

//	pushFIFO(&gcodeCmdTxFIFO,(unsigned char *)"M92\n");

    if(current_page != 1)
    {
        XSteps_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        //XSteps_value.btnHandle = BUTTON_CreateEx(270,50,90,40,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        XSteps_value.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        YSteps_text.btnHandle = BUTTON_CreateEx(10,100,240,40,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        //YSteps_value.btnHandle = BUTTON_CreateEx(270,100,90,40,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        YSteps_value.btnHandle = BUTTON_CreateEx(400,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        ZSteps_text.btnHandle = BUTTON_CreateEx(10,150,240,40,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        //ZSteps_value.btnHandle = BUTTON_CreateEx(270,150,90,40,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        ZSteps_value.btnHandle = BUTTON_CreateEx(400,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        E0Steps_text.btnHandle = BUTTON_CreateEx(10,200,240,40,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        //E0Steps_value.btnHandle = BUTTON_CreateEx(270,200,90,40,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        E0Steps_value.btnHandle = BUTTON_CreateEx(400,200+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        BUTTON_SetBmpFileName(XSteps_value.btnHandle, "bmp_pic70x28_1.bin",1);        
        BUTTON_SetBmpFileName(YSteps_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(ZSteps_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(E0Steps_value.btnHandle, "bmp_pic70x28_1.bin",1);
        //BUTTON_SetBmpFileName(XSteps_default.btnHandle, "bmp_default.bin",1);
        //BUTTON_SetBmpFileName(YSteps_default.btnHandle, "bmp_default.bin",1);     
        //BUTTON_SetBmpFileName(ZSteps_default.btnHandle, "bmp_default.bin",1);
        //BUTTON_SetBmpFileName(E0Steps_default.btnHandle, "bmp_default.bin",1);  
        
        BUTTON_SetBmpFileName(XSteps_text.btnHandle,NULL,1);        
        BUTTON_SetBmpFileName(YSteps_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(ZSteps_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(E0Steps_text.btnHandle,NULL,1);
        
        BUTTON_SetBitmapEx(XSteps_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(YSteps_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(ZSteps_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(E0Steps_value.btnHandle,0,&bmp_struct70X28,0,0); 
        //BUTTON_SetBitmapEx(XSteps_default.btnHandle,0,&bmp_struct70X28,0,5);
        //BUTTON_SetBitmapEx(YSteps_default.btnHandle,0,&bmp_struct70X28,0,5);
        //BUTTON_SetBitmapEx(ZSteps_default.btnHandle,0,&bmp_struct70X28,0,5);
        //BUTTON_SetBitmapEx(E0Steps_default.btnHandle,0,&bmp_struct70X28,0,5); 

        
        BUTTON_SetTextAlign(XSteps_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(YSteps_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(ZSteps_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E0Steps_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   
        BUTTON_SetTextAlign(XSteps_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(YSteps_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(ZSteps_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E0Steps_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER ); 

        BUTTON_SetBkColor(XSteps_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(XSteps_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(XSteps_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(XSteps_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(YSteps_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(YSteps_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(YSteps_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(YSteps_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(ZSteps_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(ZSteps_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(ZSteps_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(ZSteps_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(E0Steps_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(E0Steps_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(E0Steps_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(E0Steps_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hStepsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
    
        BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);
		//get setting from machine
		
/*
         memset(cmd_code,0,sizeof(cmd_code));
         sprintf(cmd_code,"%.1f",planner.axis_steps_per_mm[X_AXIS]);
         BUTTON_SetText(XSteps_value.btnHandle,cmd_code);         
         memset(cmd_code,0,sizeof(cmd_code));
         sprintf(cmd_code,"%.1f",planner.axis_steps_per_mm[Y_AXIS]);
         BUTTON_SetText(YSteps_value.btnHandle,cmd_code); 
         memset(cmd_code,0,sizeof(cmd_code));
         sprintf(cmd_code,"%.1f",planner.axis_steps_per_mm[Z_AXIS]);
         BUTTON_SetText(ZSteps_value.btnHandle,cmd_code); 
         memset(cmd_code,0,sizeof(cmd_code));
         sprintf(cmd_code,"%.1f",planner.axis_steps_per_mm[E_AXIS]);
         BUTTON_SetText(E0Steps_value.btnHandle,cmd_code); 
*/
    }
    else
    {
        E1Steps_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        //E1Steps_value.btnHandle = BUTTON_CreateEx(270,50,90,40,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        E1Steps_value.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hStepsWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        BUTTON_SetBmpFileName(E1Steps_value.btnHandle, "bmp_pic70x28_1.bin",1);
        //BUTTON_SetBmpFileName(E1Steps_default.btnHandle, "bmp_default.bin",1);
        
        BUTTON_SetBmpFileName(E1Steps_text.btnHandle,NULL,1); 
        
        BUTTON_SetBitmapEx(E1Steps_value.btnHandle,0,&bmp_struct70X28,0,0);
        //BUTTON_SetBitmapEx(E1Steps_default.btnHandle,0,&bmp_struct90X30,0,5); 

        BUTTON_SetTextAlign(E1Steps_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E1Steps_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetBkColor(E1Steps_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(E1Steps_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(E1Steps_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(E1Steps_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hStepsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
        
        BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);
/*
         memset(cmd_code,0,sizeof(cmd_code));
         sprintf(cmd_code,"%.1f",planner.axis_steps_per_mm[XYZE]);
         BUTTON_SetText(E1Steps_value.btnHandle,cmd_code);        
*/  
    }

     button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hStepsWnd,BUTTON_CF_SHOW,0,alloc_win_id());
     
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
            BUTTON_SetText(XSteps_text.btnHandle, machine_menu.X_Steps);
            BUTTON_SetText(YSteps_text.btnHandle, machine_menu.Y_Steps);
            BUTTON_SetText(ZSteps_text.btnHandle, machine_menu.Z_Steps);
            BUTTON_SetText(E0Steps_text.btnHandle, machine_menu.E0_Steps);
            BUTTON_SetText(button_next.btnHandle,machine_menu.next);
        }
        else
        {
            BUTTON_SetText(E1Steps_text.btnHandle,machine_menu.E1_Steps);
            BUTTON_SetText(button_previous.btnHandle,machine_menu.previous);   
        }
         
        BUTTON_SetText(button_back.btnHandle,machine_menu.back);
        
              
     }
	disp_motor_step();
}


void Clear_Steps()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hStepsWnd))
	{
		WM_DeleteWindow(hStepsWnd);
	}
}

void disp_motor_step()
{
	if(gCfgItems.firmware_type == 1)
	{
		if (current_page != 1 )
		{
			memset(cmd_code,0,sizeof(cmd_code));
	         sprintf(cmd_code,"%.1f",gCfgItems.xStep);
	         BUTTON_SetText(XSteps_value.btnHandle,cmd_code);     

			 memset(cmd_code,0,sizeof(cmd_code));
	         sprintf(cmd_code,"%.1f",gCfgItems.yStep);
	         BUTTON_SetText(YSteps_value.btnHandle,cmd_code);     
			 	     memset(cmd_code,0,sizeof(cmd_code));
	         sprintf(cmd_code,"%.1f",gCfgItems.zStep);
	         BUTTON_SetText(ZSteps_value.btnHandle,cmd_code);     
			 	     memset(cmd_code,0,sizeof(cmd_code));
	         sprintf(cmd_code,"%.1f",gCfgItems.e0Step);
	         BUTTON_SetText(E0Steps_value.btnHandle,cmd_code);     
		}
		else 
		{
			memset(cmd_code,0,sizeof(cmd_code));
	         sprintf(cmd_code,"%.1f",gCfgItems.e1Step);
	         BUTTON_SetText(E1Steps_value.btnHandle,cmd_code); 
		}		
	}
		
				     	 
}





