#include "gui.h"
#include "button.h"
#include "text.h"
#include "draw_ui.h"
#include "draw_meshleveling.h"
#include "marlin.h"
static GUI_HWIN hMeshLevelingWnd;
static BUTTON_STRUCT buttonRet,buttonMesh,buttonZadd,buttonZdec,buttonZstep;
static TEXT_Handle LevelingMsg,Zpos,PointNumb;

extern float current_position[XYZE];

static float zstep=0.1;
void disp_Zstep();
void disp_zpos();

static int G29_cnt;

void display_msg(int x)
{
    char bufg[30];
    memset(bufg,' ',30);
    TEXT_SetText(LevelingMsg, bufg);
    sprintf(bufg,"MBL point %d of %d",x,GRID_MAX_POINTS);
    TEXT_SetText(LevelingMsg, bufg);
}
static void cbMeshLevelingWin(WM_MESSAGE * pMsg) {

    char bufz[30];
    
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			break;
		case WM_TOUCH:
		 	
			break;
		case WM_TOUCH_CHILD:
			
			break;
		case WM_NOTIFY_PARENT:

        if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
         {
            if(pMsg->hWinSrc == buttonRet.btnHandle)
            {
                    if(G29_cnt != 0)
                    {
                        G29_cnt=0;
                       //enqueue_and_echo_commands_P(PSTR("G29 S5")); 
                    }
					Clear_MeshLeveling();
					draw_return_ui();                
            }
            else if(pMsg->hWinSrc == buttonMesh.btnHandle)
            {

                //else
                {
                    switch(G29_cnt)
                    {
                    case 0:
                        enqueue_and_echo_commands_P(PSTR("G29 S1"));
                        G29_cnt++;
                        display_msg(G29_cnt);
                        BUTTON_SetText(buttonMesh.btnHandle,"next");
                        break;
                    default:
                        enqueue_and_echo_commands_P(PSTR("G29 S2"));
                        G29_cnt++;
                        
                        if(G29_cnt > GRID_MAX_POINTS)
                        {
                           TEXT_SetText(LevelingMsg, "Mesh probing done."); 
                           G29_cnt=0;
                           //display_msg(G29_cnt);
                           BUTTON_SetText(buttonMesh.btnHandle,"start");
                           break;
                        }
                        display_msg(G29_cnt);
                        break;
                    }
                 }
            }
            else if(pMsg->hWinSrc == buttonZadd.btnHandle)
            {
     			enqueue_and_echo_commands_P(PSTR("G91"));
    			sprintf(bufz, "G1 Z%3.1f F%d\n",zstep, gCfgItems.moveSpeed);
    			enqueue_and_echo_commands_P(PSTR(bufz));
    			enqueue_and_echo_commands_P(PSTR("G90"));           
            }
            else if(pMsg->hWinSrc == buttonZdec.btnHandle)
            {
    			enqueue_and_echo_commands_P(PSTR("G91"));
    			sprintf(bufz, "G1 Z-%3.1f F%d\n",zstep, gCfgItems.moveSpeed);
    			enqueue_and_echo_commands_P(PSTR(bufz));
    			enqueue_and_echo_commands_P(PSTR("G90"));            
            }
            else if(pMsg->hWinSrc == buttonZstep.btnHandle)
            {
				if(abs(10 * (int)zstep) == 10)
				{
					zstep = 0.1;
				}
				else
				{
					zstep *= (float)10;
				}
				
				disp_Zstep();            
            }            

         }
			break;
			
		default:break;

    }
}

void draw_meshleveling()
{
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != MESHLEVELING_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = MESHLEVELING_UI;
	}
	
	disp_state = MESHLEVELING_UI;	

	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();

	GUI_DispStringAt(creat_title_text(),  TITLE_XPOS, TITLE_YPOS); 

    
	hMeshLevelingWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbMeshLevelingWin, 0);

	buttonMesh.btnHandle = BUTTON_CreateEx((LCD_WIDTH/2-100)/2 , imgHeight/2+(imgHeight/2-50)/2, 100, 50, hMeshLevelingWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
	buttonZadd.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3 , 0, BTN_X_PIXEL, BTN_Y_PIXEL, hMeshLevelingWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonZdec.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3 , BTN_Y_PIXEL+INTERVAL_H, BTN_X_PIXEL, BTN_Y_PIXEL, hMeshLevelingWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    buttonZstep.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hMeshLevelingWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

    buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hMeshLevelingWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

    LevelingMsg = TEXT_CreateEx(INTERVAL_V,5,BTN_X_PIXEL*2+INTERVAL_V,60, hMeshLevelingWnd, WM_CF_SHOW, GUI_TA_LEFT,   GUI_ID_TEXT1, "");
    Zpos  = TEXT_CreateEx(INTERVAL_V,65,BTN_X_PIXEL*2+INTERVAL_V,30, hMeshLevelingWnd, WM_CF_SHOW, GUI_TA_LEFT,   GUI_ID_TEXT1, "");

    BUTTON_SetBmpFileName(buttonZadd.btnHandle, "bmp_zAdd.bin",1);
    BUTTON_SetBmpFileName(buttonZdec.btnHandle, "bmp_zDec.bin",1);
    BUTTON_SetBmpFileName(buttonZstep.btnHandle, "bmp_leveling3.bin",1);
    
    BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);
    
    BUTTON_SetBmpFileName(buttonMesh.btnHandle, NULL,1);
    
    BUTTON_SetTextAlign(buttonMesh.btnHandle, GUI_TA_VCENTER | GUI_TA_HCENTER);

    disp_Zstep();
    
	BUTTON_SetBitmapEx(buttonZadd.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonZdec.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonZstep.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);   
	TEXT_SetBkColor(LevelingMsg,gCfgItems.background_color);
	TEXT_SetBkColor(Zpos,gCfgItems.background_color); 
	TEXT_SetTextColor(LevelingMsg,gCfgItems.title_color);
	TEXT_SetTextColor(Zpos,gCfgItems.title_color);

    disp_zpos();

    if(gCfgItems.multiple_language != 0)
    {
        BUTTON_SetText(buttonZadd.btnHandle, move_menu.z_add);
        BUTTON_SetText(buttonZdec.btnHandle,move_menu.z_dec);

        BUTTON_SetText(buttonRet.btnHandle, common_menu.text_back);
        BUTTON_SetText(buttonMesh.btnHandle,"start");

        TEXT_SetText(LevelingMsg, "Click <start> to\nstart leveling.");
    }

}
void disp_zpos()
{
    char zbuf[10]={0};
    sprintf(zbuf,"Z: %.3f",current_position[Z_AXIS]);
    TEXT_SetText(Zpos,zbuf);
}
void disp_Zstep()
{
	char buf[30] = {0};
		
	if((int)(10 * zstep) == 1)
	{
		BUTTON_SetBmpFileName(buttonZstep.btnHandle, "bmp_step_move0_1.bin",1);
	}
	else if((int)(10 * zstep) == 10)
	{
		BUTTON_SetBmpFileName(buttonZstep.btnHandle, "bmp_step_move1.bin",1);
	}

	if(gCfgItems.multiple_language != 0)
	{
		if((int)(10 * zstep) == 1)
			BUTTON_SetText(buttonZstep.btnHandle,move_menu.step_01mm);
		else if((int)(10 * zstep) == 10)
			BUTTON_SetText(buttonZstep.btnHandle,move_menu.step_1mm);

	}	

		
	
}

void Clear_MeshLeveling()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hMeshLevelingWnd))
	{
		WM_DeleteWindow(hMeshLevelingWnd);
		GUI_Exec();
	}

}


