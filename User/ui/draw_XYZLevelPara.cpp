#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

static GUI_HWIN hXYZLevelParaWnd;
static BUTTON_STRUCT level_point1_text,level_point2_text,level_point3_text,level_point4_text,level_point5_text;
static BUTTON_STRUCT level_point1_x_value,level_point2_x_value,level_point3_x_value,level_point4_x_value,level_point5_x_value;
static BUTTON_STRUCT level_point1_y_value,level_point2_y_value,level_point3_y_value,level_point4_y_value,level_point5_y_value;
static BUTTON_STRUCT points_number_text,points_number_value,points_number_default;

static BUTTON_STRUCT button_next,button_previous,button_back;

static uint8_t current_page;//0:上一页，1:下一页

static void cbXYZLevelParaWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:
			//GUI_SetColor(gCfgItems.state_background_color);
			//GUI_DrawRect(LCD_WIDTH/4+X_ADD, 0, LCD_WIDTH *3 / 4-X_INTERVAL, imgHeight /2 -15);
			GUI_SetColor(0xff5449);
			GUI_FillRect(10, 90, 470,90);
	GUI_FillRect(10, 140, 470,140);
			if(current_page != 1)
			{
		           
		            GUI_FillRect(10, 190, 470,190);
		            GUI_FillRect(10, 240, 470,240);
			}
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
    				last_disp_state = XYZ_LEVELING_PARA_UI;
    				Clear_XYZLevelPara();
    				draw_return_ui();
    			}	
    			else if(pMsg->hWinSrc == points_number_value.btnHandle)
    			{
    				last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    value=Points_count;
	                    draw_NumberKey();
    			}
    			else if(pMsg->hWinSrc == points_number_default.btnHandle)
    			{
    				gCfgItems.leveling_point_number = 5;
					memset(cmd_code,0,sizeof(cmd_code));
					sprintf(cmd_code,"%d",gCfgItems.leveling_point_number);
					BUTTON_SetText(points_number_value.btnHandle,cmd_code);					
					HAL::AT24CXX_Write(BAK_LEVELING_POINT_NUMBER_ADDR,(uint8_t *)&gCfgItems.leveling_point_number,1);                  
    			}				
    			else if(pMsg->hWinSrc == level_point1_x_value.btnHandle)
    			{
    				last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    value=Point1_x;
	                    draw_NumberKey();
    			}
    			else if(pMsg->hWinSrc == level_point2_x_value.btnHandle)
    			{
    				last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    value=Point2_x;
	                    draw_NumberKey();                    
    			}
    			else if(pMsg->hWinSrc == level_point3_x_value.btnHandle)
    			{
    				last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    value=Point3_x;
	                    draw_NumberKey();                    
    			} 
    			else if(pMsg->hWinSrc == level_point4_x_value.btnHandle)
    			{
    				last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    value=Point4_x;
	                    draw_NumberKey();                    
                    
    			} 
			else if(pMsg->hWinSrc == level_point5_x_value.btnHandle)
    			{
    				last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    value=Point5_x;
	                    draw_NumberKey();                    
                    
    			}
			else if(pMsg->hWinSrc == level_point1_y_value.btnHandle)
    			{
    				last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    value=Point1_y;
	                    draw_NumberKey();
    			}
    			else if(pMsg->hWinSrc == level_point2_y_value.btnHandle)
    			{
    				last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    value=Point2_y;
	                    draw_NumberKey();                    
    			}
    			else if(pMsg->hWinSrc == level_point3_y_value.btnHandle)
    			{
    				last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    value=Point3_y;
	                    draw_NumberKey();                    
    			} 
    			else if(pMsg->hWinSrc == level_point4_y_value.btnHandle)
    			{
    				last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    value=Point4_y;
	                    draw_NumberKey();                    
                    
    			} 
			else if(pMsg->hWinSrc == level_point5_y_value.btnHandle)
    			{
    				last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    value=Point5_y;
	                    draw_NumberKey();                    
                    
    			}
			else if(pMsg->hWinSrc == button_next.btnHandle)
	             {
	                    current_page = 1;
	                    last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    draw_XYZLevelPara();
	              }
	              else if(pMsg->hWinSrc == button_previous.btnHandle)
	              {
	                    current_page = 0;
	                    last_disp_state = XYZ_LEVELING_PARA_UI;
	                    Clear_XYZLevelPara();
	                    draw_XYZLevelPara();
	              } 
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}


void draw_XYZLevelPara()
{   
    int i;

    level_point1_text.btnHandle=0;
    level_point2_text.btnHandle=0;
    level_point3_text.btnHandle=0;
    level_point4_text.btnHandle=0;
    level_point5_text.btnHandle=0;

    level_point1_x_value.btnHandle=0;
    level_point2_x_value.btnHandle=0;
    level_point3_x_value.btnHandle=0;
    level_point4_x_value.btnHandle=0;
    level_point5_x_value.btnHandle=0;

    level_point1_y_value.btnHandle=0;
    level_point2_y_value.btnHandle=0;
    level_point3_y_value.btnHandle=0;
    level_point4_y_value.btnHandle=0;
    level_point5_y_value.btnHandle=0;
	
	points_number_text.btnHandle = 0;
	points_number_value.btnHandle = 0;
	points_number_default.btnHandle = 0;

    button_back.btnHandle=0;

    button_next.btnHandle=0;
    button_previous.btnHandle=0;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != XYZ_LEVELING_PARA_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = XYZ_LEVELING_PARA_UI;
    }
    disp_state = XYZ_LEVELING_PARA_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    GUI_DispStringAt(machine_menu.XYZLevelconf, TITLE_XPOS, TITLE_YPOS);

    hXYZLevelParaWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbXYZLevelParaWin, 0);

    if(current_page != 1)
    {
		points_number_text.btnHandle = BUTTON_CreateEx(10,50,300,40,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		points_number_value.btnHandle = BUTTON_CreateEx(320,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		points_number_default.btnHandle = BUTTON_CreateEx(400,50+5,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		
		level_point1_text.btnHandle = BUTTON_CreateEx(10,100,300,40,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		level_point1_x_value.btnHandle = BUTTON_CreateEx(320,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		level_point1_y_value.btnHandle = BUTTON_CreateEx(400,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    level_point2_text.btnHandle = BUTTON_CreateEx(10,150,300,40,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    level_point2_x_value.btnHandle = BUTTON_CreateEx(320,150,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    level_point2_y_value.btnHandle = BUTTON_CreateEx(400,150,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    level_point3_text.btnHandle = BUTTON_CreateEx(10,200,300,40,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    level_point3_x_value.btnHandle = BUTTON_CreateEx(320,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    level_point3_y_value.btnHandle = BUTTON_CreateEx(400,200,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	     
	    BUTTON_SetBmpFileName(level_point1_x_value.btnHandle, "bmp_pic70x28_1.bin",1);        
	    BUTTON_SetBmpFileName(level_point2_x_value.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(level_point3_x_value.btnHandle, "bmp_pic70x28_1.bin",1);
		BUTTON_SetBmpFileName(points_number_value.btnHandle, "bmp_pic70x28_1.bin",1);			


	    BUTTON_SetBmpFileName(level_point1_y_value.btnHandle, "bmp_pic70x28_1.bin",1);        
	    BUTTON_SetBmpFileName(level_point2_y_value.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(level_point3_y_value.btnHandle, "bmp_pic70x28_1.bin",1);
        BUTTON_SetBmpFileName(points_number_default.btnHandle, "bmp_pic70x28_2.bin",1); 	   
	    
	    BUTTON_SetBmpFileName(level_point1_text.btnHandle,NULL,1);        
	    BUTTON_SetBmpFileName(level_point2_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(level_point3_text.btnHandle,NULL,1);
	    BUTTON_SetBmpFileName(points_number_text.btnHandle,NULL,1);
	    
	    BUTTON_SetBitmapEx(level_point1_x_value.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(level_point2_x_value.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(level_point3_x_value.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(points_number_value.btnHandle,0,&bmp_struct70X28,0,0);

		BUTTON_SetBitmapEx(level_point1_y_value.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(level_point2_y_value.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(level_point3_y_value.btnHandle,0,&bmp_struct70X28,0,0);
	    BUTTON_SetBitmapEx(points_number_default.btnHandle,0,&bmp_struct70X28,0,0);  

	    BUTTON_SetTextAlign(level_point1_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(level_point2_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(level_point3_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(points_number_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(level_point1_x_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(level_point2_x_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(level_point3_x_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(points_number_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		BUTTON_SetTextAlign(level_point1_y_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(level_point2_y_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(level_point3_y_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(points_number_default.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    BUTTON_SetBkColor(level_point1_x_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(level_point1_x_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(level_point1_x_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(level_point1_x_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(level_point1_y_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(level_point1_y_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(level_point1_y_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(level_point1_y_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

	    BUTTON_SetBkColor(level_point2_x_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(level_point2_x_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(level_point2_x_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(level_point2_x_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(level_point2_y_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(level_point2_y_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(level_point2_y_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(level_point2_y_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

	    BUTTON_SetBkColor(level_point3_x_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(level_point3_x_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(level_point3_x_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(level_point3_x_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(level_point3_y_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(level_point3_y_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(level_point3_y_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(level_point3_y_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

		BUTTON_SetBkColor(points_number_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(points_number_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(points_number_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(points_number_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

		BUTTON_SetBkColor(points_number_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_bk_color);
		BUTTON_SetBkColor(points_number_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_bk_color); 
		BUTTON_SetTextColor(points_number_default.btnHandle, BUTTON_CI_PRESSED, gCfgItems.default_text_color);
		BUTTON_SetTextColor(points_number_default.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.default_text_color);


	    memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.leveling_point1_x);
	    BUTTON_SetText(level_point1_x_value.btnHandle,cmd_code);
	    memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.leveling_point2_x);
	    BUTTON_SetText(level_point2_x_value.btnHandle,cmd_code);
	    memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.leveling_point3_x);
	    BUTTON_SetText(level_point3_x_value.btnHandle,cmd_code);
		memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.leveling_point1_y);
	    BUTTON_SetText(level_point1_y_value.btnHandle,cmd_code);
	    memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.leveling_point2_y);
	    BUTTON_SetText(level_point2_y_value.btnHandle,cmd_code);
	    memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.leveling_point3_y);
	    BUTTON_SetText(level_point3_y_value.btnHandle,cmd_code);
		memset(cmd_code,0,sizeof(cmd_code));
		sprintf(cmd_code,"%d",gCfgItems.leveling_point_number);
		BUTTON_SetText(points_number_value.btnHandle,cmd_code);


		button_next.btnHandle = BUTTON_CreateEx(320,270,70,40,hXYZLevelParaWnd,BUTTON_CF_SHOW,0,alloc_win_id());
           BUTTON_SetBmpFileName(button_next.btnHandle, "bmp_pic70x40.bin",1); 
           BUTTON_SetBitmapEx(button_next.btnHandle, 0, &bmp_struct70X40,0, 0);


	     BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	     BUTTON_SetBkColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
	     BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextColor(button_next.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextAlign(button_next.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	     

	    if(gCfgItems.multiple_language != 0)
	    {
	        BUTTON_SetText(level_point1_text.btnHandle, leveling_menu.position1);
	        BUTTON_SetText(level_point2_text.btnHandle, leveling_menu.position2);
	        BUTTON_SetText(level_point3_text.btnHandle, leveling_menu.position3); 
			BUTTON_SetText(points_number_text.btnHandle, leveling_menu.count);  
			BUTTON_SetText(points_number_default.btnHandle, machine_menu.default_value);  

		 	BUTTON_SetText(button_next.btnHandle,machine_menu.next);
	   }
    }
    else
    {
    	    level_point4_text.btnHandle = BUTTON_CreateEx(10,50,300,40,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    level_point4_x_value.btnHandle = BUTTON_CreateEx(320,50,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    level_point4_y_value.btnHandle = BUTTON_CreateEx(400,50,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    level_point5_text.btnHandle = BUTTON_CreateEx(10,100,300,40,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    level_point5_x_value.btnHandle = BUTTON_CreateEx(320,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	    level_point5_y_value.btnHandle = BUTTON_CreateEx(400,100,VALUE_DEFAULT_X,VALUE_DEFAULT_Y,hXYZLevelParaWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	    BUTTON_SetBmpFileName(level_point4_x_value.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(level_point4_y_value.btnHandle, "bmp_pic70x28_1.bin",1); 

	    BUTTON_SetBmpFileName(level_point5_x_value.btnHandle, "bmp_pic70x28_1.bin",1);
	    BUTTON_SetBmpFileName(level_point5_y_value.btnHandle, "bmp_pic70x28_1.bin",1); 

		BUTTON_SetBmpFileName(level_point4_text.btnHandle,NULL,1);        
	    BUTTON_SetBmpFileName(level_point5_text.btnHandle,NULL,1);

	    BUTTON_SetBitmapEx(level_point4_x_value.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(level_point4_y_value.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(level_point5_x_value.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28
	    BUTTON_SetBitmapEx(level_point5_y_value.btnHandle,0,&bmp_struct70X28,0,0);//图片大小为70x28

	    BUTTON_SetBkColor(level_point4_x_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(level_point4_x_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(level_point4_x_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(level_point4_x_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

	    BUTTON_SetBkColor(level_point5_x_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(level_point5_x_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(level_point5_x_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(level_point5_x_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color); 

		BUTTON_SetBkColor(level_point4_y_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(level_point4_y_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(level_point4_y_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(level_point4_y_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

		BUTTON_SetBkColor(level_point5_y_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_bk_color);
	    BUTTON_SetBkColor(level_point5_y_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_bk_color); 
	    BUTTON_SetTextColor(level_point5_y_value.btnHandle, BUTTON_CI_PRESSED, gCfgItems.value_text_color);
	    BUTTON_SetTextColor(level_point5_y_value.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.value_text_color);

	    BUTTON_SetTextAlign(level_point4_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(level_point4_x_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(level_point4_y_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    BUTTON_SetTextAlign(level_point5_text.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(level_point5_x_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	    BUTTON_SetTextAlign(level_point5_y_value.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

		memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.leveling_point4_x);
	    BUTTON_SetText(level_point4_x_value.btnHandle,cmd_code);

		memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.leveling_point5_x);
	    BUTTON_SetText(level_point5_x_value.btnHandle,cmd_code);

		memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.leveling_point4_y);
	    BUTTON_SetText(level_point4_y_value.btnHandle,cmd_code);

		memset(cmd_code,0,sizeof(cmd_code));
	    sprintf(cmd_code,"%d",gCfgItems.leveling_point5_y);
	    BUTTON_SetText(level_point5_y_value.btnHandle,cmd_code);

	    button_previous.btnHandle = BUTTON_CreateEx(320,270,70,40,hXYZLevelParaWnd,BUTTON_CF_SHOW,0,alloc_win_id());
           BUTTON_SetBmpFileName(button_previous.btnHandle, "bmp_pic70x40.bin",1); 
           BUTTON_SetBitmapEx(button_previous.btnHandle, 0, &bmp_struct70X40,0, 0);

	     BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
	     BUTTON_SetBkColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color);    
	     BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
	     BUTTON_SetTextColor(button_previous.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor);
	     
     	     BUTTON_SetTextAlign(button_previous.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );

	    if(gCfgItems.multiple_language != 0)
	    {
	        BUTTON_SetText(level_point4_text.btnHandle, leveling_menu.position4);
	        BUTTON_SetText(level_point5_text.btnHandle, leveling_menu.position5);
	    	 BUTTON_SetText(button_previous.btnHandle,machine_menu.previous); 
	    }
    }

    button_back.btnHandle = BUTTON_CreateEx(400,270,70,40,hXYZLevelParaWnd,BUTTON_CF_SHOW,0,alloc_win_id());
    
    BUTTON_SetBmpFileName(button_back.btnHandle, "bmp_pic70x40.bin",1);        
    BUTTON_SetBitmapEx(button_back.btnHandle, 0, &bmp_struct70X40,0,0);
    BUTTON_SetTextAlign(button_back.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_color);
    BUTTON_SetBkColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_color); 
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back1_btn_textcolor);
    BUTTON_SetTextColor(button_back.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back1_btn_textcolor); 
    
    BUTTON_SetText(button_back.btnHandle,machine_menu.back);

}

void Clear_XYZLevelPara()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hXYZLevelParaWnd))
	{
		WM_DeleteWindow(hXYZLevelParaWnd);
	}
}






