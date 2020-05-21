#include "gui.h"
#include "button.h"
#include "draw_ui.h"
//#include "Marlin.h"
//#include "cardreader.h"
#include "mks_tft_com.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hAccelerationWnd;
static BUTTON_STRUCT PrintAcceleration_text,RetractAcceleration_text,TravelAcceleration_text,XAcceleration_text,YAcceleration_text,ZAcceleration_text,E0Acceleration_text,E1Acceleration_text;
static BUTTON_STRUCT PrintAcceleration_value,RetractAcceleration_value,TravelAcceleration_value,XAcceleration_value,YAcceleration_value,ZAcceleration_value,E0Acceleration_value,E1Acceleration_value;
static BUTTON_STRUCT PrintAcceleration_default,RetractAcceleration_default,TravelAcceleration_default,XAcceleration_default,YAcceleration_default,ZAcceleration_default,E0Acceleration_default,E1Acceleration_default;

static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void btnHandle_rest()
{
    PrintAcceleration_text.btnHandle = 0;
    PrintAcceleration_value.btnHandle = 0;
    PrintAcceleration_default.btnHandle = 0;
    RetractAcceleration_text.btnHandle = 0;
    RetractAcceleration_value.btnHandle = 0;
    RetractAcceleration_default.btnHandle = 0;
    TravelAcceleration_text.btnHandle = 0;
    TravelAcceleration_value.btnHandle = 0;
    TravelAcceleration_default.btnHandle = 0;

    XAcceleration_text.btnHandle = 0;
    XAcceleration_value.btnHandle = 0;
    XAcceleration_default.btnHandle = 0;
    YAcceleration_text.btnHandle = 0;
    YAcceleration_value.btnHandle = 0;
    YAcceleration_default.btnHandle = 0;
    ZAcceleration_text.btnHandle = 0;
    ZAcceleration_value.btnHandle = 0;
    ZAcceleration_default.btnHandle = 0;
    E0Acceleration_text.btnHandle = 0;   
    E0Acceleration_value.btnHandle = 0;
    E0Acceleration_default.btnHandle = 0;
    E1Acceleration_text.btnHandle = 0;   
    E1Acceleration_value.btnHandle = 0;
    E1Acceleration_default.btnHandle = 0;          
    button_previous.btnHandle = 0;
    button_next.btnHandle = 0;
    button_back.btnHandle = 0;
}

static void cbAccelerationWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			GUI_SetColor(0xff5449);

			GUI_FillRect(10, 90, 470,90);
            GUI_FillRect(10, 140, 470,140);
            GUI_FillRect(10, 190, 470,190);
            GUI_FillRect(10, 240, 470,240);
            
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
    				last_disp_state = ACCELERATION_UI;
    				Clear_Acceleration();
    				draw_return_ui();
    			}	
                else if(pMsg->hWinSrc == button_next.btnHandle)
                {
                    current_page = 1;
                    last_disp_state = ACCELERATION_UI;
                    Clear_Acceleration();
                    draw_Acceleration();
                }
                else if(pMsg->hWinSrc == button_previous.btnHandle)
                {
                    current_page = 0;
                    last_disp_state = ACCELERATION_UI;
                    Clear_Acceleration();
                    draw_Acceleration();
                }   
    			else if(pMsg->hWinSrc == PrintAcceleration_value.btnHandle)
    			{
    				last_disp_state = ACCELERATION_UI;
    				Clear_Acceleration();
    				value=PrintAcceleration;
                    draw_NumberKey();    				
    			}
    			else if(pMsg->hWinSrc == RetractAcceleration_value.btnHandle)
    			{
    				last_disp_state = ACCELERATION_UI;
    				Clear_Acceleration();
    				value=RetractAcceleration;
                    draw_NumberKey();     				
    			}
    			else if(pMsg->hWinSrc == TravelAcceleration_value.btnHandle)
    			{
    				last_disp_state = ACCELERATION_UI;
    				Clear_Acceleration();
    				value=TravelAcceleration;
                    draw_NumberKey();     				
    			}                
    			else if(pMsg->hWinSrc == XAcceleration_value.btnHandle)
    			{
    				last_disp_state = ACCELERATION_UI;
    				Clear_Acceleration();
    				value=XAcceleration;
                    draw_NumberKey();     				
    			}
    			else if(pMsg->hWinSrc == YAcceleration_value.btnHandle)

    			{
    				last_disp_state = ACCELERATION_UI;
    				Clear_Acceleration();
    				value=YAcceleration;
                    draw_NumberKey();    				
    			}
    			else if(pMsg->hWinSrc == ZAcceleration_value.btnHandle)

    			{
    				last_disp_state = ACCELERATION_UI;
    				Clear_Acceleration();
    				value=ZAcceleration;
                    draw_NumberKey();                    
    		
    			}       
    			else if(pMsg->hWinSrc == E0Acceleration_value.btnHandle)

    			{
    				last_disp_state = ACCELERATION_UI;
    				Clear_Acceleration();
    				value=E0Acceleration;
                    draw_NumberKey();

    			}
    			else if(pMsg->hWinSrc == E1Acceleration_value.btnHandle)

    			{
    				last_disp_state = ACCELERATION_UI;
    				Clear_Acceleration();
    				value=E1Acceleration;
                    draw_NumberKey();

    			}  
                #if 0
    			else if(pMsg->hWinSrc == XAcceleration_default.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Acceleration();

    			} 
    			else if(pMsg->hWinSrc == YAcceleration_default.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Acceleration();

    			}  
    			else if(pMsg->hWinSrc == ZAcceleration_default.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Acceleration();

    			} 
    			else if(pMsg->hWinSrc == E0Acceleration_default.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Acceleration();

    			}   
    			else if(pMsg->hWinSrc == E1Acceleration_default.btnHandle)

    			{
    				last_disp_state = STEPS_UI;
    				Clear_Acceleration();

    			} 
    			else if(pMsg->hWinSrc == PrintAcceleration_default.btnHandle)
    			{
    				last_disp_state = STEPS_UI;
    				Clear_Acceleration();
    				
    			}
    			else if(pMsg->hWinSrc == RetractAcceleration_default.btnHandle)
    			{
    				last_disp_state = STEPS_UI;
    				Clear_Acceleration();
    				
    			}
    			else if(pMsg->hWinSrc == TravelAcceleration_default.btnHandle)
    			{
    				last_disp_state = STEPS_UI;
    				Clear_Acceleration();
    				
    			}                
                #endif
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_Acceleration()
{   
    int i;


    btnHandle_rest();
    
    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != ACCELERATION_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = ACCELERATION_UI;
    }
    disp_state = ACCELERATION_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.AccelerationConfTitle, TITLE_XPOS, TITLE_YPOS);

    hAccelerationWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbAccelerationWin, 0);


//	pushFIFO(&gcodeCmdTxFIFO,(unsigned char *)"M503\n");		//x/y/z/e
//	pushFIFO(&gcodeCmdTxFIFO,(unsigned char *)"M204\n");		//print/retract/travel

    if(current_page != 1)
    {
        PrintAcceleration_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
       
        PrintAcceleration_value.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        RetractAcceleration_text.btnHandle = BUTTON_CreateEx(10,100,240,40,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
       
        RetractAcceleration_value.btnHandle = BUTTON_CreateEx(400,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        TravelAcceleration_text.btnHandle = BUTTON_CreateEx(10,150,240,40,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        
        TravelAcceleration_value.btnHandle = BUTTON_CreateEx(400,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        XAcceleration_text.btnHandle = BUTTON_CreateEx(10,200,240,40,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        XAcceleration_value.btnHandle = BUTTON_CreateEx(400,200+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        BUTTON_SetBmpFileName(PrintAcceleration_value.btnHandle, "bmp_pic70x28_1.bin",1);        
        BUTTON_SetBmpFileName(RetractAcceleration_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(TravelAcceleration_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(XAcceleration_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(PrintAcceleration_default.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(RetractAcceleration_default.btnHandle, "bmp_pic70x28_1.bin",1);     
        BUTTON_SetBmpFileName(TravelAcceleration_default.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(XAcceleration_default.btnHandle, "bmp_pic70x28_1.bin",1);  
        
        BUTTON_SetBmpFileName(PrintAcceleration_text.btnHandle,NULL,1);        
        BUTTON_SetBmpFileName(RetractAcceleration_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(TravelAcceleration_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(XAcceleration_text.btnHandle,NULL,1);
        
        BUTTON_SetBitmapEx(PrintAcceleration_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(RetractAcceleration_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(TravelAcceleration_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(XAcceleration_value.btnHandle,0,&bmp_struct70X28,0,0); 

        
        BUTTON_SetTextAlign(PrintAcceleration_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(RetractAcceleration_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(TravelAcceleration_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(XAcceleration_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   

        BUTTON_SetTextAlign(PrintAcceleration_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(RetractAcceleration_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(TravelAcceleration_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(XAcceleration_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER ); 

        BUTTON_SetBkColor(PrintAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(PrintAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(PrintAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(PrintAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(RetractAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(RetractAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(RetractAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(RetractAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(TravelAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(TravelAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(TravelAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(TravelAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(XAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(XAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(XAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(XAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hAccelerationWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
    
        BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);
        


    }
    else
    {
        YAcceleration_text.btnHandle = BUTTON_CreateEx(10,50,240,40,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        YAcceleration_value.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        ZAcceleration_text.btnHandle = BUTTON_CreateEx(10,100,240,40,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
        
        ZAcceleration_value.btnHandle = BUTTON_CreateEx(400,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        E0Acceleration_text.btnHandle = BUTTON_CreateEx(10,150,240,40,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
       
        E0Acceleration_value.btnHandle = BUTTON_CreateEx(400,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        E1Acceleration_text.btnHandle = BUTTON_CreateEx(10,200,240,40,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
       
        E1Acceleration_value.btnHandle = BUTTON_CreateEx(400,200+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hAccelerationWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

        BUTTON_SetBmpFileName(YAcceleration_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(ZAcceleration_value.btnHandle, "bmp_pic70x28_1.bin",1);
         BUTTON_SetBmpFileName(E0Acceleration_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(E1Acceleration_value.btnHandle, "bmp_pic70x28_1.bin",1);
 

        
        BUTTON_SetBmpFileName(YAcceleration_text.btnHandle,NULL,1); 
        BUTTON_SetBmpFileName(ZAcceleration_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(E0Acceleration_text.btnHandle,NULL,1);
        BUTTON_SetBmpFileName(E1Acceleration_text.btnHandle,NULL,1);
        
        BUTTON_SetBitmapEx(YAcceleration_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(ZAcceleration_value.btnHandle,0,&bmp_struct70X28,0,0); 
        BUTTON_SetBitmapEx(E0Acceleration_value.btnHandle,0,&bmp_struct70X28,0,0);
        BUTTON_SetBitmapEx(E1Acceleration_value.btnHandle,0,&bmp_struct70X28,0,0); 


        BUTTON_SetTextAlign(YAcceleration_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(ZAcceleration_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E0Acceleration_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E1Acceleration_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(YAcceleration_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(ZAcceleration_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E0Acceleration_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
        BUTTON_SetTextAlign(E1Acceleration_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

        BUTTON_SetBkColor(YAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(YAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(YAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(YAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(ZAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(ZAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(ZAcceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(ZAcceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(E0Acceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(E0Acceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(E0Acceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(E0Acceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        BUTTON_SetBkColor(E1Acceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
        BUTTON_SetBkColor(E1Acceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
        BUTTON_SetTextColor(E1Acceleration_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
        BUTTON_SetTextColor(E1Acceleration_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

        button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hAccelerationWnd,BUTTON_CF_SHOW,0,alloc_win_id());
        BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
        
        BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);

    }
	disp_acceleration();

     button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hAccelerationWnd,BUTTON_CF_SHOW,0,alloc_win_id());
     
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
            BUTTON_SetText(PrintAcceleration_text.btnHandle, machine_menu.PrintAcceleration);
            BUTTON_SetText(RetractAcceleration_text.btnHandle, machine_menu.RetractAcceleration);
            BUTTON_SetText(TravelAcceleration_text.btnHandle, machine_menu.TravelAcceleration);
            BUTTON_SetText(XAcceleration_text.btnHandle, machine_menu.X_Acceleration);
            BUTTON_SetText(button_next.btnHandle,machine_menu.next);
        }
        else
        {
            BUTTON_SetText(YAcceleration_text.btnHandle, machine_menu.Y_Acceleration);
            BUTTON_SetText(ZAcceleration_text.btnHandle, machine_menu.Z_Acceleration);
            BUTTON_SetText(E0Acceleration_text.btnHandle,machine_menu.E0_Acceleration);
            BUTTON_SetText(E1Acceleration_text.btnHandle,machine_menu.E1_Acceleration);

            BUTTON_SetText(button_previous.btnHandle,machine_menu.previous);   
        }
         
        BUTTON_SetText(button_back.btnHandle,machine_menu.back);
        
              
     }

}


void Clear_Acceleration()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hAccelerationWnd))
	{
		WM_DeleteWindow(hAccelerationWnd);
	}
}



void disp_acceleration()
{

	if(gCfgItems.firmware_type == 1)
	{
		if (current_page !=1)
		{
			memset(cmd_code,0,sizeof(cmd_code));
	        sprintf(cmd_code,"%d",gCfgItems.printAccel);
	        BUTTON_SetText(PrintAcceleration_value.btnHandle,cmd_code); 
	        memset(cmd_code,0,sizeof(cmd_code));
	        sprintf(cmd_code,"%d",gCfgItems.retractAccel);
	        BUTTON_SetText(RetractAcceleration_value.btnHandle,cmd_code);        
	        memset(cmd_code,0,sizeof(cmd_code));
	        sprintf(cmd_code,"%d",gCfgItems.travelAccel);
	        BUTTON_SetText(TravelAcceleration_value.btnHandle,cmd_code); 
	        memset(cmd_code,0,sizeof(cmd_code));
	        sprintf(cmd_code,"%d",gCfgItems.xMaxAccel);
	        BUTTON_SetText(XAcceleration_value.btnHandle,cmd_code);
		}
		else 
		{
			memset(cmd_code,0,sizeof(cmd_code));
	        sprintf(cmd_code,"%d",gCfgItems.yMaxAccel);
	        BUTTON_SetText(YAcceleration_value.btnHandle,cmd_code);
	        memset(cmd_code,0,sizeof(cmd_code));
	        sprintf(cmd_code,"%d",gCfgItems.zMaxAccel);
	        BUTTON_SetText(ZAcceleration_value.btnHandle,cmd_code);  
	        memset(cmd_code,0,sizeof(cmd_code));
	        sprintf(cmd_code,"%d",gCfgItems.e0_MaxAccel);
	        BUTTON_SetText(E0Acceleration_value.btnHandle,cmd_code);   
	        memset(cmd_code,0,sizeof(cmd_code));
	        sprintf(cmd_code,"%d",gCfgItems.e1_MaxAccel);
	        BUTTON_SetText(E1Acceleration_value.btnHandle,cmd_code); 		
		}		
	}
	
	    
}



