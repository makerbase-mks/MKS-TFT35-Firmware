#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"


#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hFirmwareTypeWnd;
static BUTTON_STRUCT Marlin_Sel,Repetier_Sel,Smoothie_Sel;
static BUTTON_STRUCT buttonMarlin,buttonRepetier,buttonSmoothie;
static BUTTON_STRUCT button_back;


static void cbFirmwareTypeWin(WM_MESSAGE * pMsg) {

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
    				last_disp_state = FIRMWARETYPE_UI;
    				Clear_FirmwareType();
    				draw_return_ui();
    			}	
    			else if(pMsg->hWinSrc == Marlin_Sel.btnHandle)
    			{
    				last_disp_state = FIRMWARETYPE_UI;
						gCfgItems.firmware_type=1;        
						HAL::AT24CXX_Write(BAK_FIRMWARETYPE_ADDR,(uint8_t *)&gCfgItems.firmware_type,1);
	                    Firmware_sel();						
    			}
    			else if(pMsg->hWinSrc == Repetier_Sel.btnHandle)
    			{
    			    last_disp_state = FIRMWARETYPE_UI;
	                    gCfgItems.firmware_type=2;
                            HAL::AT24CXX_Write(BAK_FIRMWARETYPE_ADDR,(uint8_t *)&gCfgItems.firmware_type,1);
	                    Firmware_sel();
    			}
    			else if(pMsg->hWinSrc == Smoothie_Sel.btnHandle)
    			{
    				last_disp_state = FIRMWARETYPE_UI;
	                    gCfgItems.firmware_type=3;
                            HAL::AT24CXX_Write(BAK_FIRMWARETYPE_ADDR,(uint8_t *)&gCfgItems.firmware_type,1);
	                    Firmware_sel();
    			}       			
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_FirmwareType()
{   
    int i;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != FIRMWARETYPE_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = FIRMWARETYPE_UI;
    }
    disp_state = FIRMWARETYPE_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.FirmwareTypeConfTitle, TITLE_XPOS, TITLE_YPOS);

    hFirmwareTypeWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbFirmwareTypeWin, 0);

    buttonMarlin.btnHandle = BUTTON_CreateEx(10,50,360,40,hFirmwareTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    Marlin_Sel.btnHandle = BUTTON_CreateEx(370,50,90,40,hFirmwareTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
    buttonRepetier.btnHandle = BUTTON_CreateEx(10,100,360,40,hFirmwareTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    Repetier_Sel.btnHandle = BUTTON_CreateEx(370,100,90,40,hFirmwareTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
    buttonSmoothie.btnHandle = BUTTON_CreateEx(10,150,360,40,hFirmwareTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    Smoothie_Sel.btnHandle = BUTTON_CreateEx(370,150,90,40,hFirmwareTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

     
    //BUTTON_SetBmpFileName(Marlin_Sel.btnHandle, "bmp_circle.bin",1);        
    //BUTTON_SetBmpFileName(Repetier_Sel.btnHandle, "bmp_circle.bin",1);
    //BUTTON_SetBmpFileName(Smoothie_Sel.btnHandle, "bmp_circle.bin",1);

	Firmware_sel();
    
    BUTTON_SetBmpFileName(buttonMarlin.btnHandle,NULL,1);        
    BUTTON_SetBmpFileName(buttonRepetier.btnHandle,NULL,1);
    BUTTON_SetBmpFileName(buttonSmoothie.btnHandle,NULL,1);

    BUTTON_SetBitmapEx(Marlin_Sel.btnHandle,0,&bmp_struct26X26,64,7);//
    BUTTON_SetBitmapEx(Repetier_Sel.btnHandle,0,&bmp_struct26X26,64,7);
    BUTTON_SetBitmapEx(Smoothie_Sel.btnHandle,0,&bmp_struct26X26,64,7);
    
    BUTTON_SetTextAlign(buttonMarlin.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(buttonRepetier.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(buttonSmoothie.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

    button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hFirmwareTypeWnd,BUTTON_CF_SHOW,0,alloc_win_id());
    
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
    BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0, 0);
    BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 

    if(gCfgItems.multiple_language != 0)
    {
        BUTTON_SetText(buttonMarlin.btnHandle, machine_menu.marlin);
        BUTTON_SetText(buttonRepetier.btnHandle, machine_menu.repetier);
        BUTTON_SetText(buttonSmoothie.btnHandle, machine_menu.smoothie);   
        BUTTON_SetText(button_back.btnHandle,machine_menu.back);
    }
}

void Firmware_sel()
{
    switch(gCfgItems.firmware_type)
    {
        case 1:
                 
            BUTTON_SetBmpFileName(Marlin_Sel.btnHandle, "bmp_circle_sel.bin",1);        
            BUTTON_SetBmpFileName(Repetier_Sel.btnHandle, "bmp_circle.bin",1);
            BUTTON_SetBmpFileName(Smoothie_Sel.btnHandle, "bmp_circle.bin",1);
            break;
        case 2:
                 
            BUTTON_SetBmpFileName(Marlin_Sel.btnHandle, "bmp_circle.bin",1);        
            BUTTON_SetBmpFileName(Repetier_Sel.btnHandle, "bmp_circle_sel.bin",1);
            BUTTON_SetBmpFileName(Smoothie_Sel.btnHandle, "bmp_circle.bin",1);
            break;
        case 3:
                 
            BUTTON_SetBmpFileName(Marlin_Sel.btnHandle, "bmp_circle.bin",1);        
            BUTTON_SetBmpFileName(Repetier_Sel.btnHandle, "bmp_circle.bin",1);
            BUTTON_SetBmpFileName(Smoothie_Sel.btnHandle, "bmp_circle_sel.bin",1);
            break;
        default:
            BUTTON_SetBmpFileName(Marlin_Sel.btnHandle, "bmp_circle_sel.bin",1);        
            BUTTON_SetBmpFileName(Repetier_Sel.btnHandle, "bmp_circle.bin",1);
            BUTTON_SetBmpFileName(Smoothie_Sel.btnHandle, "bmp_circle.bin",1);            
            break;
    }
}
void Clear_FirmwareType()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hFirmwareTypeWnd))
	{
		WM_DeleteWindow(hFirmwareTypeWnd);
	}
}




