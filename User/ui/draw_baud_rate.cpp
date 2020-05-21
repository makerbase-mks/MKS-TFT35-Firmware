#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"
#include "usart.h"


#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hBaudRateWnd;
static BUTTON_STRUCT Rate9600_sel,Rate57600_sel,Rate115200_sel,Rate250000_sel;
static BUTTON_STRUCT button9600,button57600,button115200,button250000;
static BUTTON_STRUCT button_back;


static void cbBaudRateWin(WM_MESSAGE * pMsg) {

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
            GUI_FillRect(10, 240, 470,240);//draw line
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
    				last_disp_state = BAUDRATE_UI;
    				Clear_BaudRate();
    				draw_return_ui();
    			}	
    			else if(pMsg->hWinSrc == Rate9600_sel.btnHandle)
    			{
    				last_disp_state = BAUDRATE_UI;

						gCfgItems.baud=1;        

						HAL::AT24CXX_Write(BAK_BAUDRATE_ADDR,(uint8_t *)&gCfgItems.baud,1);
	                    BaudRate_sel();						
    			}
    			else if(pMsg->hWinSrc == Rate57600_sel.btnHandle)
    			{
    			    last_disp_state = BAUDRATE_UI;
	                    gCfgItems.baud=2;
                           HAL::AT24CXX_Write(BAK_BAUDRATE_ADDR,(uint8_t *)&gCfgItems.baud,1);
	                    BaudRate_sel();
    			}
    			else if(pMsg->hWinSrc == Rate115200_sel.btnHandle)
    			{
                            last_disp_state = BAUDRATE_UI;
	                    gCfgItems.baud=3;

                            HAL::AT24CXX_Write(BAK_BAUDRATE_ADDR,(uint8_t *)&gCfgItems.baud,1);
	                    BaudRate_sel();
    			} 
				else if(pMsg->hWinSrc == Rate250000_sel.btnHandle)
    			{
    				last_disp_state = BAUDRATE_UI;
	                    gCfgItems.baud=4;

                            HAL::AT24CXX_Write(BAK_BAUDRATE_ADDR,(uint8_t *)&gCfgItems.baud,1);
	                    BaudRate_sel();
						
    			}   
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_BaudRate()
{   
    int i;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != BAUDRATE_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = BAUDRATE_UI;
    }
    disp_state = BAUDRATE_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.BaudRateConfTitle, TITLE_XPOS, TITLE_YPOS);

    hBaudRateWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbBaudRateWin, 0);

    button9600.btnHandle = BUTTON_CreateEx(10,50,360,40,hBaudRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    Rate9600_sel.btnHandle = BUTTON_CreateEx(370,50,90,40,hBaudRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
    button57600.btnHandle = BUTTON_CreateEx(10,100,360,40,hBaudRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    Rate57600_sel.btnHandle = BUTTON_CreateEx(370,100,90,40,hBaudRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
    button115200.btnHandle = BUTTON_CreateEx(10,150,360,40,hBaudRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    Rate115200_sel.btnHandle = BUTTON_CreateEx(370,150,90,40,hBaudRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	button250000.btnHandle = BUTTON_CreateEx(10,200,360,40,hBaudRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    Rate250000_sel.btnHandle = BUTTON_CreateEx(370,200,90,40,hBaudRateWnd, BUTTON_CF_SHOW, 0, alloc_win_id());	

     


	BaudRate_sel();
    
    BUTTON_SetBmpFileName(button9600.btnHandle,NULL,1);        
    BUTTON_SetBmpFileName(button57600.btnHandle,NULL,1);
    BUTTON_SetBmpFileName(button115200.btnHandle,NULL,1);
    BUTTON_SetBmpFileName(button250000.btnHandle,NULL,1);

    BUTTON_SetBitmapEx(Rate9600_sel.btnHandle,0,&bmp_struct26X26,64,7);//
    BUTTON_SetBitmapEx(Rate57600_sel.btnHandle,0,&bmp_struct26X26,64,7);
    BUTTON_SetBitmapEx(Rate115200_sel.btnHandle,0,&bmp_struct26X26,64,7);
    BUTTON_SetBitmapEx(Rate250000_sel.btnHandle,0,&bmp_struct26X26,64,7);

    
    BUTTON_SetTextAlign(button9600.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(button57600.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(button115200.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(button250000.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

    button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hBaudRateWnd,BUTTON_CF_SHOW,0,alloc_win_id());
    
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
    BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0, 0);
    BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 

    if(gCfgItems.multiple_language != 0)
    {
        BUTTON_SetText(button9600.btnHandle, machine_menu.rate1);
        BUTTON_SetText(button57600.btnHandle, machine_menu.rate2);
        BUTTON_SetText(button115200.btnHandle, machine_menu.rate3);   
		BUTTON_SetText(button250000.btnHandle, machine_menu.rate4); 
        BUTTON_SetText(button_back.btnHandle,machine_menu.back);
    }
}

void BaudRate_sel()
{
    switch(gCfgItems.baud)
    {
        case 1:    
            BUTTON_SetBmpFileName(Rate9600_sel.btnHandle, "bmp_circle_sel.bin",1);        
            BUTTON_SetBmpFileName(Rate57600_sel.btnHandle, "bmp_circle.bin",1);
            BUTTON_SetBmpFileName(Rate115200_sel.btnHandle, "bmp_circle.bin",1);
            BUTTON_SetBmpFileName(Rate250000_sel.btnHandle, "bmp_circle.bin",1);
            break;
        case 2:     
            BUTTON_SetBmpFileName(Rate9600_sel.btnHandle, "bmp_circle.bin",1);        
            BUTTON_SetBmpFileName(Rate57600_sel.btnHandle, "bmp_circle_sel.bin",1);
            BUTTON_SetBmpFileName(Rate115200_sel.btnHandle, "bmp_circle.bin",1);
            BUTTON_SetBmpFileName(Rate250000_sel.btnHandle, "bmp_circle.bin",1);
            break;
        case 3:                
            BUTTON_SetBmpFileName(Rate9600_sel.btnHandle, "bmp_circle.bin",1);        
            BUTTON_SetBmpFileName(Rate57600_sel.btnHandle, "bmp_circle.bin",1);
            BUTTON_SetBmpFileName(Rate115200_sel.btnHandle, "bmp_circle_sel.bin",1);
            BUTTON_SetBmpFileName(Rate250000_sel.btnHandle, "bmp_circle.bin",1);
            break;
        case 4: 			
            BUTTON_SetBmpFileName(Rate9600_sel.btnHandle, "bmp_circle.bin",1);        
            BUTTON_SetBmpFileName(Rate57600_sel.btnHandle, "bmp_circle.bin",1);
            BUTTON_SetBmpFileName(Rate115200_sel.btnHandle, "bmp_circle.bin",1);
            BUTTON_SetBmpFileName(Rate250000_sel.btnHandle, "bmp_circle_sel.bin",1);
            break;
        default:
            BUTTON_SetBmpFileName(Rate9600_sel.btnHandle, "bmp_circle_sel.bin",1);        
            BUTTON_SetBmpFileName(Rate57600_sel.btnHandle, "bmp_circle.bin",1);
            BUTTON_SetBmpFileName(Rate115200_sel.btnHandle, "bmp_circle.bin",1);    
	    BUTTON_SetBmpFileName(Rate250000_sel.btnHandle, "bmp_circle.bin",1);    
            break;
    }
	MX_USART3_UART_Init(gCfgItems.baud);
}
void Clear_BaudRate()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hBaudRateWnd))
	{
		WM_DeleteWindow(hBaudRateWnd);
	}
}




