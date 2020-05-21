#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"
//#include "marlin.h"
//#include "mks_reprint.h"
//#include "cardreader.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hMachineTypeWnd;
static BUTTON_STRUCT Normal_Sel,Delta_Sel,Corexy_Sel;
static BUTTON_STRUCT buttonNormal,buttonDelta,buttonCorexy;
static BUTTON_STRUCT button_back;

//extern CardReader card;

static void cbMachineTypeWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(0xff5449);
			GUI_FillRect(10, 90, 470,90);
            GUI_FillRect(10, 140, 470,140);
//            GUI_FillRect(10, 190, 470,190);
 
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
    				last_disp_state = MACHINETYPE_UI;
    				Clear_MachineType();
    				draw_return_ui();
    			}	
    			else if(pMsg->hWinSrc == Normal_Sel.btnHandle)
    			{
    				last_disp_state = MACHINETYPE_UI;
					gCfgItems.machineType = 1;
					HAL::AT24CXX_Write(BAK_MACHINE_TYPE_ADDR,(uint8_t *)&gCfgItems.machineType	,1);
                    Machine_sel();
//						
//				card.mksLoad();
    			}
    			else if(pMsg->hWinSrc == Delta_Sel.btnHandle)
    			{
    			    last_disp_state = MACHINETYPE_UI;
					gCfgItems.machineType = 2;
					HAL::AT24CXX_Write(BAK_MACHINE_TYPE_ADDR,(uint8_t *)&gCfgItems.machineType	,1);
	                Machine_sel();
    			}
//    			else if(pMsg->hWinSrc == Corexy_Sel.btnHandle)
//    			{
//    				last_disp_state = MACHINETYPE_UI;
//	                    mksCfg.machinetype=2;
////	                    epr_write_data(EPR_MACHINETPYE,(uint8_t *)&mksCfg.machinetype,sizeof(mksCfg.machinetype));
//	                    mksCfg.machinetype = (1<<mksCfg.machinetype);
//	                    Machine_sel();
//						
////				card.mksLoad();
//    			}       			
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_MachineType()
{   
    int i;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != MACHINETYPE_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = MACHINETYPE_UI;
    }
    disp_state = MACHINETYPE_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.MachineTypeConfTitle, TITLE_XPOS, TITLE_YPOS);

    hMachineTypeWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbMachineTypeWin, 0);

    buttonNormal.btnHandle = BUTTON_CreateEx(10,50,360,40,hMachineTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    Normal_Sel.btnHandle = BUTTON_CreateEx(370,50,90,40,hMachineTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
    buttonDelta.btnHandle = BUTTON_CreateEx(10,100,360,40,hMachineTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    Delta_Sel.btnHandle = BUTTON_CreateEx(370,100,90,40,hMachineTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
//    buttonCorexy.btnHandle = BUTTON_CreateEx(10,150,360,40,hMachineTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
//    Corexy_Sel.btnHandle = BUTTON_CreateEx(370,150,90,40,hMachineTypeWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

     
    //BUTTON_SetBmpFileName(Normal_Sel.btnHandle, "bmp_circle.bin",1);        
    //BUTTON_SetBmpFileName(Delta_Sel.btnHandle, "bmp_circle.bin",1);
    //BUTTON_SetBmpFileName(Corexy_Sel.btnHandle, "bmp_circle.bin",1);

	Machine_sel();
    
    BUTTON_SetBmpFileName(buttonNormal.btnHandle,NULL,1);        
    BUTTON_SetBmpFileName(buttonDelta.btnHandle,NULL,1);
//    BUTTON_SetBmpFileName(buttonCorexy.btnHandle,NULL,1);

    BUTTON_SetBitmapEx(Normal_Sel.btnHandle,0,&bmp_struct26X26,64,7);//ͼƬ��СΪ26x26
    BUTTON_SetBitmapEx(Delta_Sel.btnHandle,0,&bmp_struct26X26,64,7);
//    BUTTON_SetBitmapEx(Corexy_Sel.btnHandle,0,&bmp_struct26X26,64,7);
    
    BUTTON_SetTextAlign(buttonNormal.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(buttonDelta.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
//    BUTTON_SetTextAlign(buttonCorexy.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

    button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hMachineTypeWnd,BUTTON_CF_SHOW,0,alloc_win_id());
    
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
    BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0, 0);
    BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 

    if(gCfgItems.multiple_language != 0)
    {
        BUTTON_SetText(buttonNormal.btnHandle, machine_menu.normal);
        BUTTON_SetText(buttonDelta.btnHandle, machine_menu.delta);
//        BUTTON_SetText(buttonCorexy.btnHandle, machine_menu.corexy);   
        BUTTON_SetText(button_back.btnHandle,machine_menu.back);
    }
}

void Machine_sel()
{
	switch (gCfgItems.machineType)
    {
        case 1:
                 
            BUTTON_SetBmpFileName(Normal_Sel.btnHandle, "bmp_circle_sel.bin",1);        
            BUTTON_SetBmpFileName(Delta_Sel.btnHandle, "bmp_circle.bin",1);
//            BUTTON_SetBmpFileName(Corexy_Sel.btnHandle, "bmp_circle.bin",1);
            break;
        case 2:
                 
            BUTTON_SetBmpFileName(Normal_Sel.btnHandle, "bmp_circle.bin",1);        
            BUTTON_SetBmpFileName(Delta_Sel.btnHandle, "bmp_circle_sel.bin",1);
//            BUTTON_SetBmpFileName(Corexy_Sel.btnHandle, "bmp_circle.bin",1);
            break;
//        case 4:
//                 
//            BUTTON_SetBmpFileName(Normal_Sel.btnHandle, "bmp_circle.bin",1);        
//            BUTTON_SetBmpFileName(Delta_Sel.btnHandle, "bmp_circle.bin",1);
//            BUTTON_SetBmpFileName(Corexy_Sel.btnHandle, "bmp_circle_sel.bin",1);
//            break;
        default:
            BUTTON_SetBmpFileName(Normal_Sel.btnHandle, "bmp_circle_sel.bin",1);        
            BUTTON_SetBmpFileName(Delta_Sel.btnHandle, "bmp_circle.bin",1);
//            BUTTON_SetBmpFileName(Corexy_Sel.btnHandle, "bmp_circle.bin",1);            
            break;
    }
}
void Clear_MachineType()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hMachineTypeWnd))
	{
		WM_DeleteWindow(hMachineTypeWnd);
	}
}




