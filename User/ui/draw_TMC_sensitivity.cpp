#include "gui.h"
#include "button.h"
#include "draw_ui.h"
//#include "Marlin.h"
//#include "cardreader.h"
#include "at24cxx.h"


#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hDriverSensityWnd;
static BUTTON_STRUCT Xsensitivity_text;
static BUTTON_STRUCT Xsensitivity_value;
static BUTTON_STRUCT Ysensitivity_text,Zsensitivity_text;
static BUTTON_STRUCT Ysensitivity_value,Zsensitivity_value;



static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页
static void btnHandle_rest()
{
    Xsensitivity_text.btnHandle = 0;
    Xsensitivity_value.btnHandle = 0;
	  Ysensitivity_text.btnHandle = 0;
	  Zsensitivity_text.btnHandle = 0;
	  Ysensitivity_value.btnHandle = 0;
	  Zsensitivity_value.btnHandle = 0;
    button_back.btnHandle = 0;
}

static void cbTMCSensivisityWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			GUI_SetColor(0xff5449);

			GUI_FillRect(10, 90, 470,90);
            GUI_FillRect(10, 140, 470,140);
            GUI_FillRect(10, 190, 470,190);
//            GUI_FillRect(10, 240, 470,240);
            
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
    				last_disp_state = TMCSENSIVISITY_UI;
    				Clear_TMCsensitivity();
    				draw_return_ui();
    			}	              
    			else if(pMsg->hWinSrc == Xsensitivity_value.btnHandle)
    			{
					last_disp_state = TMCSENSIVISITY_UI;
					Clear_TMCsensitivity();
					  value=Sensivisity_X;
					  draw_NumberKey();
    			}
				else if(pMsg->hWinSrc == Ysensitivity_value.btnHandle)
				{
					last_disp_state = TMCSENSIVISITY_UI;
					Clear_TMCsensitivity();
					  value=Sensivisity_Y;
					  draw_NumberKey();
				} 
				else if(pMsg->hWinSrc == Zsensitivity_value.btnHandle)
				{
					last_disp_state = TMCSENSIVISITY_UI;
					Clear_TMCsensitivity();
					  value=Sensivisity_Z;
					  draw_NumberKey();

				}  
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_TMCsensitivity()
{   
    int i;


    btnHandle_rest();
    
    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != TMCSENSIVISITY_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = TMCSENSIVISITY_UI;
    }
    disp_state = TMCSENSIVISITY_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.TMCBumpTitle, TITLE_XPOS, TITLE_YPOS);

    hDriverSensityWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbTMCSensivisityWin, 0);

	Xsensitivity_text.btnHandle = BUTTON_CreateEx(10,50,360,40,hDriverSensityWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	Xsensitivity_value.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hDriverSensityWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	Ysensitivity_text.btnHandle = BUTTON_CreateEx(10,100,360,40,hDriverSensityWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	Ysensitivity_value.btnHandle = BUTTON_CreateEx(400,100+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hDriverSensityWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	Zsensitivity_text.btnHandle = BUTTON_CreateEx(10,150,360,40,hDriverSensityWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	Zsensitivity_value.btnHandle = BUTTON_CreateEx(400,150+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hDriverSensityWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	 
	BUTTON_SetBmpFileName(Xsensitivity_value.btnHandle, "bmp_pic70x28_1.bin",1);
	BUTTON_SetBmpFileName(Ysensitivity_value.btnHandle, "bmp_pic70x28_1.bin",1);        	 
	BUTTON_SetBmpFileName(Zsensitivity_value.btnHandle, "bmp_pic70x28_1.bin",1);      

	BUTTON_SetBmpFileName(Ysensitivity_text.btnHandle,NULL,1);  
	BUTTON_SetBmpFileName(Zsensitivity_text.btnHandle,NULL,1);
	BUTTON_SetBmpFileName(Xsensitivity_text.btnHandle,NULL,1);	

	BUTTON_SetBitmapEx(Xsensitivity_value.btnHandle,0,&bmp_struct70X28,0,0); 
	BUTTON_SetBitmapEx(Ysensitivity_value.btnHandle,0,&bmp_struct70X28,0,0);
	BUTTON_SetBitmapEx(Zsensitivity_value.btnHandle,0,&bmp_struct70X28,0,0); 

	BUTTON_SetTextAlign(Xsensitivity_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	BUTTON_SetTextAlign(Ysensitivity_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );   
	BUTTON_SetTextAlign(Zsensitivity_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER ); 

	BUTTON_SetTextAlign(Xsensitivity_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	BUTTON_SetTextAlign(Ysensitivity_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	BUTTON_SetTextAlign(Zsensitivity_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );   
	
	BUTTON_SetBkColor(Xsensitivity_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	BUTTON_SetBkColor(Xsensitivity_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	BUTTON_SetTextColor(Xsensitivity_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	BUTTON_SetTextColor(Xsensitivity_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 


	BUTTON_SetBkColor(Ysensitivity_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	BUTTON_SetBkColor(Ysensitivity_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	BUTTON_SetTextColor(Ysensitivity_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	BUTTON_SetTextColor(Ysensitivity_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

	BUTTON_SetBkColor(Zsensitivity_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	BUTTON_SetBkColor(Zsensitivity_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	BUTTON_SetTextColor(Zsensitivity_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	BUTTON_SetTextColor(Zsensitivity_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

	disp_TMCsensivisity();

     button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hDriverSensityWnd,BUTTON_CF_SHOW,0,alloc_win_id());
     
     BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
     BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0, 0);
        
     BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
     BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
     BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
     BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 
     BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

     if(gCfgItems.multiple_language != 0)
     {   
            BUTTON_SetText(Xsensitivity_text.btnHandle, machine_menu.X_Sensivisity); 
            BUTTON_SetText(Ysensitivity_text.btnHandle,machine_menu.Y_Sensivisity);
            BUTTON_SetText(Zsensitivity_text.btnHandle, machine_menu.Z_Sensivisity);    
	        BUTTON_SetText(button_back.btnHandle,machine_menu.back);         
     }

}


void Clear_TMCsensitivity()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hDriverSensityWnd))
	{
		WM_DeleteWindow(hDriverSensityWnd);
	}
}

void disp_TMCsensivisity()
{	
	if(gCfgItems.firmware_type == 1)
	{
		memset(cmd_code,0,sizeof(cmd_code));
		sprintf(cmd_code,"%d",gCfgItems.xSensivisity);
		BUTTON_SetText(Xsensitivity_value.btnHandle,cmd_code);  
		memset(cmd_code,0,sizeof(cmd_code));
		sprintf(cmd_code,"%d",gCfgItems.ySensivisity);
		BUTTON_SetText(Ysensitivity_value.btnHandle,cmd_code);   
		memset(cmd_code,0,sizeof(cmd_code));
		sprintf(cmd_code,"%d",gCfgItems.zSensivisity);
		BUTTON_SetText(Zsensitivity_value.btnHandle,cmd_code);  
	}

}





