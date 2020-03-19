#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_ui.h"
#include "draw_ready_print.h"
//#include "gcode.h"
//#include "printer.h"
#include "draw_machine.h"
#include "draw_log_ui.h"
#include "draw_language.h"
#include "draw_about.h"
#include "draw_wifi.h"
#include "draw_print_file.h"
#include "draw_printing.h"
#include "draw_move_motor.h"
#include "draw_operate.h"
#include "draw_pause_ui.h"
#include "draw_extrusion.h"
#include "draw_pre_heat.h"
#include "draw_change_speed.h"
#include "draw_fan.h"
#include "draw_set.h"
#include "draw_zero.h"
#include "draw_sprayer.h"
#include "draw_machine.h"
#include "draw_language.h"
#include "draw_log_ui.h"
#include "draw_wifi.h"
#include "draw_more.h"
#include "string_deal.h"
#include "ff.h"
#include "pic_manager.h"
#include "ili9320.h"
#include "draw_printing_moremenu.h"
#include "draw_filamentchange.h"
/******add********/
#include "draw_main.h"
#include "tim.h"
#include "mks_tft_com.h"
#include "draw_manual_leveling.h"
#include "mks_tft_reprint.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_flash_ex.h"

#include "at24cxx.h"
#include "draw_bind.h"
#include "draw_disk.h"
#include "draw_zoffset.h"
#include "draw_tool.h"
#include "draw_babyStep.h"

extern volatile int16_t logo_time;
extern PR_STATUS printerStaus;
extern uint8_t temp_update_flag;

extern uint8_t print_start_flg;
extern uint8_t from_flash_pic;
/******end********/
extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz14;

extern GUI_CONST_STORAGE GUI_BITMAP bmpreheat;
extern GUI_CONST_STORAGE GUI_BITMAP bmadd;
extern GUI_CONST_STORAGE GUI_BITMAP bmdec;
extern GUI_CONST_STORAGE GUI_BITMAP bmdir;
extern GUI_CONST_STORAGE GUI_BITMAP bmextru;
extern GUI_CONST_STORAGE GUI_BITMAP bmfile;
extern GUI_CONST_STORAGE GUI_BITMAP bmmov;
extern GUI_CONST_STORAGE GUI_BITMAP bmpageDown;
extern GUI_CONST_STORAGE GUI_BITMAP bmpageUp;
extern GUI_CONST_STORAGE GUI_BITMAP bmprinting;
extern GUI_CONST_STORAGE GUI_BITMAP bmreturn;
extern GUI_CONST_STORAGE GUI_BITMAP bmset;
extern GUI_CONST_STORAGE GUI_BITMAP bmzero;

extern uint8_t gcode_preview_over;

uint8_t temperature_change_frequency = 1;//用于显示温度更新的频率
//unsigned char bmp_public_buf[16*1024] = {0};

extern uint8_t wifi_refresh_flg;
extern void disp_wifi_state();

extern void filament_dialog_handle(void);


DISP_STATE_STACK disp_state_stack;
DISP_STATE disp_state = MAIN_UI;
DISP_STATE last_disp_state;

char BMP_PIC_X = 0 ;
char BMP_PIC_Y = 0;

uint32_t To_pre_view;

static   GUI_HWIN hMainWnd;
static  BUTTON_STRUCT button4;//button1, button2, button3, button4;

extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
#if _LFN_UNICODE
extern TCHAR curFileName[150];
#else
extern char curFileName[150];
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmlogo;
extern GUI_CONST_STORAGE GUI_BITMAP bmpreheat;

extern CFG_ITMES gCfgItems;

extern int X_ADD,X_INTERVAL;   //**图片间隔
extern uint8_t volatile printing_rate_update_flag;
extern volatile uint32_t TimeIncrease;
static volatile uint8_t fan_move_flag;
extern FILE_PRINT_STATE gCurFileState ;
extern uint8_t fan_change_flag;

//PR_STATUS printerStaus = pr_idle;

#define MAX_TITLE_LEN	28

static CB_EVENT_STACK gCbEventStack;
//Tan21060406
#define INC_RD_POINT(b)	((b.r_idx+1 == sizeof(b.event) / sizeof(b.event[0])) ? 0 : b.r_idx+1)
#define INC_WR_POINT(b)	((b.w_idx+1 == sizeof(b.event) / sizeof(b.event[0])) ? 0 : b.w_idx+1)

void init_cb_stack()
{
	memset(&gCbEventStack.event, 0, sizeof(gCbEventStack.event));
	gCbEventStack.r_idx = 0;
	gCbEventStack.w_idx = 0;
}

void push_cb_stack(int16_t event_id)
{

	if(INC_WR_POINT(gCbEventStack) == gCbEventStack.r_idx) //overflow
	{
		return;
	}
	gCbEventStack.event[gCbEventStack.w_idx] = event_id;
	gCbEventStack.w_idx = INC_WR_POINT(gCbEventStack);
	
			
}

int16_t pop_cb_stack()
{
	int16_t ret;
	if(gCbEventStack.r_idx != gCbEventStack.w_idx)
	{
		ret = gCbEventStack.event[gCbEventStack.r_idx];
		gCbEventStack.r_idx = INC_RD_POINT(gCbEventStack);
		return ret;
	
	}
	else
	{
		return -1;
	}
	
	
}

void GUI_callback()
{
	int16_t action_id = pop_cb_stack();
	if(action_id != (int16_t)-1)
	{
		uid.executeAction(action_id);
	}
}


void titleText_cat(char *str, int strSize, char *addPart)
{
	if(str == 0 || addPart == 0)
	{
		return;
	}

	if(strlen(str) + strlen(addPart) >= strSize)
	{
		return;
	}

	strcat(str, addPart);
}

static char TitleText[30];

char *getDispText(int index)
{
	memset(TitleText, 0, sizeof(TitleText));
	
	switch(disp_state_stack._disp_state[index])
	{
		case PRINT_READY_UI:
			strcpy(TitleText, main_menu.title);

			break;

		case PRINT_FILE_UI:
			strcpy(TitleText, file_menu.title);

			break;

		case PRINTING_UI:
			if(disp_state_stack._disp_state[disp_state_stack._disp_index] == PRINTING_UI
			/*
			|| disp_state_stack._disp_state[disp_state_stack._disp_index] == OPERATE_UI
			|| disp_state_stack._disp_state[disp_state_stack._disp_index] == PAUSE_UI
			*/)
			{
				strcpy(TitleText, common_menu.print_special_title);
			}
			else
			{
				strcpy(TitleText, printing_menu.title);
			}

			break;

		case MOVE_MOTOR_UI:
			strcpy(TitleText, move_menu.title);

			break;

		case OPERATE_UI:
			if(disp_state_stack._disp_state[disp_state_stack._disp_index] == PRINTING_UI
			/*
			|| disp_state_stack._disp_state[disp_state_stack._disp_index] == OPERATE_UI
			|| disp_state_stack._disp_state[disp_state_stack._disp_index] == PAUSE_UI
			*/)
			{
				strcpy(TitleText, common_menu.operate_special_title);
			}
			else
			{
				strcpy(TitleText, operation_menu.title);
			}

			break;

		case PAUSE_UI:
			if(disp_state_stack._disp_state[disp_state_stack._disp_index] == PRINTING_UI
			|| disp_state_stack._disp_state[disp_state_stack._disp_index] == OPERATE_UI)
			{
				strcpy(TitleText, common_menu.pause_special_title);
			}
			else
			{
				strcpy(TitleText, pause_menu.title);
			}

			break;

		case EXTRUSION_UI:
			strcpy(TitleText, extrude_menu.title);

			break;

		case CHANGE_SPEED_UI:
			strcpy(TitleText, speed_menu.title);

			break;
			
		case FAN_UI:
			strcpy(TitleText, fan_menu.title);

			break;
			
		case PRE_HEAT_UI:
			if((disp_state_stack._disp_state[disp_state_stack._disp_index - 1] == OPERATE_UI))
			{
				strcpy(TitleText,preheat_menu.adjust_title);

			}
			else
			{
				strcpy(TitleText, preheat_menu.title);

			} 			
			break;

		case SET_UI:
			strcpy(TitleText, set_menu.title);

			break;

		case ZERO_UI:
			strcpy(TitleText, home_menu.title);

			break;

		case SPRAYER_UI:

			break;

		case MACHINE_UI:

			break;

		case LANGUAGE_UI:
			strcpy(TitleText, language_menu.title);

			break;

		case ABOUT_UI:
			strcpy(TitleText, about_menu.title);

			break;

		case LOG_UI:

			break;

		case DISK_UI:
			strcpy(TitleText, filesys_menu.title);
			break;

		case DIALOG_UI:
			strcpy(TitleText, common_menu.dialog_confirm_title);
			break;	

		case WIFI_UI:
			strcpy(TitleText, wifi_menu.title);

			break;	
		case MORE_UI:
		case PRINT_MORE_UI:
			strcpy(TitleText, more_menu.title);

			break;	
		case FILAMENTCHANGE_UI:
			strcpy(TitleText, filament_menu.title); 		
			break;	
		case LEVELING_UI:
			strcpy(TitleText, leveling_menu.title); 					
			break;		
		case BIND_UI:
			strcpy(TitleText, cloud_menu.title);			
			break;
		case ZOFFSET_UI:
			strcpy(TitleText, zoffset_menu.title);			
			break;	
		case TOOL_UI:
			strcpy(TitleText, tool_menu.title);			
			break;	
		case BABY_STEP_UI:
			strcpy(TitleText, operation_menu.babystep);			
			break;
		default:
			break;
	}

	return TitleText;
}

static char titleText[100] = {0};
//uint8_t curFileName[30] = {0};

char *creat_title_text()
{
	int index = 0;
	
	char *tmpText = 0;
	
	TCHAR tmpCurFileStr[20];
	

	memset(tmpCurFileStr, 0, sizeof(tmpCurFileStr));

	#if _LFN_UNICODE
	cutFileName((TCHAR *)curFileName, 16, 16, (TCHAR *)tmpCurFileStr);	
	#else
	cutFileName(curFileName, 16, 16, tmpCurFileStr);
	#endif
	
	memset(titleText, 0, sizeof(titleText));
	
	while(index <= disp_state_stack._disp_index)
	{
		
		tmpText = getDispText(index);
		if((*tmpText == 0) || (tmpText == 0))
		{
			index++;
			continue;
		}
		
		titleText_cat(titleText, sizeof(titleText), tmpText);
		if(index < disp_state_stack._disp_index)
		{
			titleText_cat(titleText, sizeof(titleText), ">");
		}
		
		index++;
	}
	
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] == PRINTING_UI
		/*|| disp_state_stack._disp_state[disp_state_stack._disp_index] == OPERATE_UI
		|| disp_state_stack._disp_state[disp_state_stack._disp_index] == PAUSE_UI*/)
	{
		titleText_cat(titleText, sizeof(titleText), ":");
		titleText_cat(titleText, sizeof(titleText), (char *)tmpCurFileStr);	
	}

	if(strlen(titleText) > MAX_TITLE_LEN)
	{
		memset(titleText, 0, sizeof(titleText));
	
		tmpText = getDispText(0);
		if(*tmpText != 0)
		{
			titleText_cat(titleText, sizeof(titleText), tmpText);
			titleText_cat(titleText, sizeof(titleText), ">...>");
			tmpText = getDispText(disp_state_stack._disp_index);
			if(*tmpText != 0)
			{
				titleText_cat(titleText, sizeof(titleText), tmpText);
			}
		}
		
	}

	return titleText;
}

void disp_sel_lang()
{
	if(gCfgItems.language == LANG_ENGLISH)
	{
		BUTTON_SetBkColor(button4.btnHandle, BUTTON_CI_UNPRESSED, GUI_FOCUS_CLOLOR);	
		//BUTTON_SetBkColor(button1, BUTTON_CI_UNPRESSED, GUI_BLUE);	
		//BUTTON_SetBkColor(button3, BUTTON_CI_UNPRESSED, GUI_BLUE);	
	}
	/*else if(gCfgItems.language == 3)
	{
		BUTTON_SetBkColor(button3, BUTTON_CI_UNPRESSED, GUI_FOCUS_CLOLOR);	
		BUTTON_SetBkColor(button1, BUTTON_CI_UNPRESSED, GUI_BLUE);	
		BUTTON_SetBkColor(button2, BUTTON_CI_UNPRESSED, GUI_BLUE);	
	}*/
	else
	{
		//BUTTON_SetBkColor(button1, BUTTON_CI_UNPRESSED, GUI_FOCUS_CLOLOR);	
		BUTTON_SetBkColor(button4.btnHandle, BUTTON_CI_UNPRESSED, GUI_BUTTON_COLOR);	
		//BUTTON_SetBkColor(button3, BUTTON_CI_UNPRESSED, GUI_BLUE);	
	}
		
}



void clear_cur_ui()
{
	last_disp_state = disp_state_stack._disp_state[disp_state_stack._disp_index];
	
	switch(disp_state_stack._disp_state[disp_state_stack._disp_index])
	{
		case PRINT_READY_UI:	
			Get_Temperature_Flg = 0;
			Clear_ready_print();
			break;

		case PRINT_FILE_UI:
			Clear_print_file();
			break;

		case PRINTING_UI:
			Clear_printing();
			break;

		case MOVE_MOTOR_UI:
			Clear_move_motor();
			break;

		case OPERATE_UI:
			Clear_operate();
			break;

		case PAUSE_UI:
			Clear_pause();
			break;

		case EXTRUSION_UI:
			Clear_extrusion();
			break;

		case PRE_HEAT_UI:
			Clear_preHeat();
			break;

		case CHANGE_SPEED_UI:
			Clear_changeSpeed();
			break;

		case FAN_UI:
			Clear_fan();
			break;

		case SET_UI:
			Clear_Set();
			break;

		case ZERO_UI:
			Clear_Zero();
			break;

		case SPRAYER_UI:
			Clear_Sprayer();
			break;

		case MACHINE_UI:
			Clear_Machine();
			break;

		case LANGUAGE_UI:
			Clear_Language();
			break;

		case ABOUT_UI:
			Clear_About();
			break;

		case LOG_UI:
			Clear_Connect();
			break;
		case DISK_UI:
			Clear_Disk();
			break;
		case WIFI_UI:
			Clear_Wifi();
			break;
			
		case MORE_UI:
			Clear_more();
			break;
			
		case FILETRANSFER_UI:
		///	Clear_fileTransfer();
			break;
		case DIALOG_UI:
			Clear_dialog();
			break;			
		case FILETRANSFERSTATE_UI:
		/////	Clear_WifiFileTransferdialog();
			break;
		case PRINT_MORE_UI:
			Clear_Printmore();
			break;
		case LEVELING_UI:
			Clear_Leveling();//**
			break;
		case BIND_UI:
			Clear_Bind();
			break;
		case ZOFFSET_UI:
			Clear_Zoffset();
			break;
		case TOOL_UI:
			Clear_Tool();
			break;
		//chen 11.7
		case FILAMENTCHANGE_UI:
			Clear_FilamentChange();
			break;
		case BABY_STEP_UI:
			Clear_babyStep();
			break;

		default:
			break;
	}
	GUI_Clear();
}

void draw_return_ui()
{
	if(disp_state_stack._disp_index > 0)
	{
		disp_state_stack._disp_index--;
		
		switch(disp_state_stack._disp_state[disp_state_stack._disp_index])
		{
			case PRINT_READY_UI:
				draw_ready_print();
				break;

			case PRINT_FILE_UI:
				draw_print_file();
				break;

			case PRINTING_UI:
				draw_printing();
				break;

			case MOVE_MOTOR_UI:
				draw_move_motor();
				break;

			case OPERATE_UI:
				draw_operate();
				break;

			case PAUSE_UI:
				draw_pause();
				break;

			case EXTRUSION_UI:
				draw_extrusion();
				break;

			case PRE_HEAT_UI:
				draw_preHeat();
				break;

			case CHANGE_SPEED_UI:
				draw_changeSpeed();
				break;

			case FAN_UI:
				draw_fan();
				break;

			case SET_UI:
				draw_Set();
				break;

			case ZERO_UI:
				draw_Zero();
				break;

			case SPRAYER_UI:
				draw_Sprayer();
				break;

			case MACHINE_UI:
				draw_Machine();
				break;

			case LANGUAGE_UI:
				draw_Language();
				break;

			case ABOUT_UI:
				draw_About();
				break;

			case LOG_UI:
				draw_Connect();
				break;

			case CALIBRATE_UI:
		////		draw_calibrate();
				break;
			case DISK_UI:
				draw_Disk();
				break;
			case WIFI_UI:
				draw_Wifi();
				break;
			case MORE_UI:
				draw_More();
				break;
			case PRINT_MORE_UI:
				draw_printmore();
				break;
			case FILAMENTCHANGE_UI:
				draw_FilamentChange();
				break;
			case LEVELING_UI:
				//draw_leveling();
				break;
			case BIND_UI:
				draw_bind();
				break;
			case ZOFFSET_UI:
				draw_Zoffset();
				break;
			case TOOL_UI:
				draw_tool();
				break;
			case BABY_STEP_UI:
				draw_babyStep();
				break;

			default:
				break;
		}
	}

	
}

void gui_view_init()
{
/*
	gCfgItems.custom_pic_flag = 1;
	gCfgItems.language = LANG_SIMPLE_CHINESE;
	gCfgItems.background_color = GUI_BK_CLOLOR;
	gCfgItems.title_color = GUI_TITLE_TEXT_COLOR;
	gCfgItems.state_background_color = GUI_STATE_COLOR;
	gCfgItems.state_text_color = GUI_STATE_TEXT_COLOR;
	gCfgItems.filename_color = GUI_FILE_NAME_TEXT_COLOR;
	gCfgItems.filename_background_color = GUI_FILE_NAME_BK_COLOR;
	gCfgItems.printingstate_word_background_color = GUI_PRINTING_STATE_BK_COLOR;
	gCfgItems.printingstate_word_color = GUI_PRINTING_STATE_TEXT_COLOR;
	//gCfgItems.language = 3;
*/	
#if 0
	if(gCfgItems.language == LANG_COMPLEX_CHINESE)
	{
		GUI_SetFont(&GUI_FontHZ16);
	}
	else
	{
		GUI_SetFont(&FONT_TITLE);
	}

	GUI_SetBkColor(gCfgItems.background_color);
	
	BUTTON_SetDefaultTextAlign(GUI_TA_BOTTOM | GUI_TA_HCENTER);
	if(gCfgItems.language == LANG_COMPLEX_CHINESE)
	{
		BUTTON_SetDefaultFont(&GUI_FontHZ16);
	}
	else
	{
		BUTTON_SetDefaultFont(&FONT_TITLE);
	}

	if(gCfgItems.language == LANG_COMPLEX_CHINESE)
	{
		TEXT_SetDefaultFont(&GUI_FontHZ16);
	}
	else
	{
		TEXT_SetDefaultFont(&FONT_TITLE);
	}
	//BUTTON_SetDefaultFont(&FONT_BUTTON);	
/*	
	BUTTON_SetDefaultBkColor(GUI_BUTTON_COLOR, BUTTON_CI_UNPRESSED);
	BUTTON_SetDefaultBkColor(GUI_BUTTON_COLOR, BUTTON_CI_PRESSED);
	BUTTON_SetDefaultTextColor(GUI_WHITE, BUTTON_CI_UNPRESSED);
	BUTTON_SetDefaultTextColor(GUI_WHITE, BUTTON_CI_PRESSED);
*/
#endif
	GUI_SetFont(&FONT_TITLE);
	BUTTON_SetDefaultFont(&FONT_TITLE);
	TEXT_SetDefaultFont(&FONT_TITLE);
	GUI_SetBkColor(gCfgItems.background_color);
	BUTTON_SetDefaultTextAlign(GUI_TA_BOTTOM | GUI_TA_HCENTER);

	BUTTON_SetDefaultBkColor(gCfgItems.background_color, BUTTON_CI_UNPRESSED);
	BUTTON_SetDefaultBkColor(gCfgItems.background_color, BUTTON_CI_PRESSED);
	BUTTON_SetDefaultTextColor(gCfgItems.title_color, BUTTON_CI_UNPRESSED);
	BUTTON_SetDefaultTextColor(gCfgItems.title_color, BUTTON_CI_PRESSED);
	if(gCfgItems.button_3d_effect_flag != 1)
	{
		WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);
	}

	init_cb_stack();

	//sean 19.3.5
  	#if 1
	//if(gCfgItems.touch_adjust_default == 0)
	//{
		HAL::AT24CXX_Read(BAK_TOUCH_ADJ_FLAG_ADDR,(uint8_t *)&gCfgItems.touch_adj_flag,sizeof(gCfgItems.touch_adj_flag));
		if(gCfgItems.touch_adj_flag == 0xaa)
		{
			HAL::AT24CXX_Read(BAK_TOUCH_ADJ_XMIN_ADDR, (uint8_t *)&gCfgItems.touch_adj_xMin,   4); 
			HAL::AT24CXX_Read(BAK_TOUCH_ADJ_XMAX_ADDR, (uint8_t *)&gCfgItems.touch_adj_xMax,   4); 
			HAL::AT24CXX_Read(BAK_TOUCH_ADJ_YMIN_ADDR, (uint8_t *)&gCfgItems.touch_adj_yMin,   4); 
			HAL::AT24CXX_Read(BAK_TOUCH_ADJ_YMAX_ADDR, (uint8_t *)&gCfgItems.touch_adj_yMax,   4); 
		}
	//}
	#endif
}

//**
int8_t get_printing_rate(FIL *fileHandle)
{
	int8_t rate;
	
	if(fileHandle == 0)
		return -1;

	if(fileHandle->fptr == 0)
		return -1;

	if(fileHandle->fsize == 0)
		return -1;

	if(fileHandle->fptr > fileHandle->fsize)
		return -1;
	
	if(from_flash_pic != 1)
	{
		rate = (unsigned char)((float)f_tell(fileHandle)  * 100 / f_size(fileHandle));
	}
	else
	{
		rate = (unsigned char)(((float)f_tell(fileHandle)-(PREVIEW_SIZE+To_pre_view))  * 100 / (f_size(fileHandle)-(PREVIEW_SIZE+To_pre_view)));
	}



	if((rate == 100) && (printerStaus != pr_idle))	
	{
		rate = 99;
	}

	if((rate == 99) && (printerStaus == pr_idle))	
	{
		rate = 100;
	}
	

	gCurFileState.totalSend = rate;

	return  rate;

}

#if 1
extern uint16_t z_high_count;
extern uint8_t move_speed_flg;

void GUI_RefreshPage()
{

  		__IO uint32_t i =0;
		switch(disp_state)
		{
		      case MAIN_UI:                                                    //**
				
				if(logo_time * TICK_CYCLE >= 3000 )
				{
					
					clear_main_ui();
					last_disp_state = MAIN_UI;
					draw_ready_print();
					
				}
				break;

			case EXTRUSION_UI:  
				if(temp_update_flag == 1)
				{
					temp_update_flag = 0;
					disp_sprayer_temp();
				}
				break;

			case PRE_HEAT_UI:
				if(temp_update_flag == 1)
				{
					temp_update_flag = 0;
					disp_desire_temp();
				}
				break;

			case PRINT_READY_UI:
			/*	if(fan_move_flag)
				{
					fan_move_flag = 0;
					disp_fan_move();
				}*/
				break;

			case PRINT_FILE_UI:
				break;

			case PRINTING_UI:
				/*if(temperature_change_frequency == 1)
				{
					temperature_change_frequency = 0;
					disp_sprayer_tem_printing();
					disp_bed_temp_printing();
				}
				setProBarRate();
				#if VERSION_WITH_PIC
				disp_fan_move_printing();
				#endif
				break;*/
				if(temp_update_flag)
					{
						temp_update_flag = 0;
						disp_sprayer_tem_printing();
						disp_bed_temp_printing();
						disp_print_time();
					}
					if(printing_rate_update_flag)
					{
						printing_rate_update_flag = 0;
						if(gcode_preview_over == 0)
						{
							setProBarRate(get_printing_rate(srcfp));
						}
					}
					if(!(TimeIncrease * TICK_CYCLE % 100))	// 0.1s
					{		
						fan_move_flag = 1;
					}
					#if VERSION_WITH_PIC
					if(fan_move_flag)
					{
						fan_move_flag = 0;
						disp_fan_move_printing();
					}
					#endif

					if(move_speed_flg == 1)
					{
						move_speed_flg =0;
						disp_printing_speed();
					}
					break;

			case OPERATE_UI:
				/*if(temperature_change_frequency == 1)
				{
					temperature_change_frequency = 0;
					disp_temp_operate();
				}			
				setProBarRateOpera();
				break;*/
					if(temp_update_flag)
					{
						temp_update_flag = 0;
						disp_temp_operate();
					}
					if(printing_rate_update_flag)
					{
						printing_rate_update_flag = 0;
						setProBarRateOpera(get_printing_rate(srcfp));
					}
					if((printerStaus == pr_idle)&&(gCurFileState.totalSend == 100))
					{
						clear_cur_ui();
						draw_printing();
					}
					break;

			case PAUSE_UI:
				if(printerStaus == pr_idle)
				{
					Clear_pause();
					stop_print_time();
					f_close(srcfp);

					reset_file_info();
					//reset_tx_fifo();
					draw_ready_print();
				}
				if(temp_update_flag)
				{
					temp_update_flag = 0;
					disp_temp_pause();
				}
				
				if(fan_change_flag)
				{
					fan_change_flag = 0;
					disp_temp_pause();
				}
					
				
				break;
				
			case FAN_UI:
				if(fan_change_flag)
				{
					fan_change_flag = 0;
					disp_fan_speed();
				}
				break;
				
			case MOVE_MOTOR_UI:
			//显示Z轴坐标
				if((gCfgItems.getzpos_enable ==0)&&(printerStaus != pr_pause))
				{
					i=0;
					while(RePrintData.mov_z_coordinate[i]!= '\n')
					{
						gCfgItems.move_z_coordinate[i] = RePrintData.mov_z_coordinate[i];
						i++;
						if(i>20)break;
					}
					gCfgItems.move_z_coordinate[i] = 0;
					//GUI_DispStringAtCEOL((const char *)gCfgItems.move_z_coordinate,220, X_INTERVAL);
					if(z_high_count==500) //每隔500us显示一次
					GUI_DispStringAt((const char *)gCfgItems.move_z_coordinate,400, TITLE_YPOS);
				}
				break;

		case WIFI_UI:
			if(wifi_refresh_flg == 1)
			{					
				disp_wifi_state();
				wifi_refresh_flg = 0;
			}
			break;

		case FILAMENTCHANGE_UI:
			if(temp_update_flag)
			{
				temp_update_flag = 0;
				disp_filament_sprayer_temp();
			}
			//FilamentChange_handle();
			break;
		case DIALOG_UI:
			filament_dialog_handle();
			break;	
		case BABY_STEP_UI:
			if(gCfgItems.zoffset_disp_flag == ENABLE)
			{
				gCfgItems.zoffset_disp_flag = DISABLE;
				//获得Zoffset数值
				#if defined(TFT70)
				//GUI_DispStringAt((const char *),480, TITLE_YPOS);
				GUI_SetColor(gCfgItems.background_color);
				GUI_FillRect(480, TITLE_YPOS, LCD_WIDTH, titleHeight);
				GUI_SetColor(gCfgItems.title_color);
				GUI_DispStringAt((const char *)gCfgItems.disp_zoffset_buf,480, TITLE_YPOS);
				#else
				//GUI_DispStringAt((const char *),290, TITLE_YPOS);
				GUI_SetColor(gCfgItems.background_color);
				GUI_FillRect(290, TITLE_YPOS, LCD_WIDTH, titleHeight);
				GUI_SetColor(gCfgItems.title_color);
				GUI_DispStringAt((const char *)gCfgItems.disp_zoffset_buf,290, TITLE_YPOS);
				#endif
				//memset(gCfgItems.disp_zoffset_buf,0,sizeof(gCfgItems.disp_zoffset_buf));
			}
			break;
			default:
				break;
				
	    }
		print_time_run();
	
	
}
	#endif
//tan 20160830
/*
void BUTTON_SetBmpFileName(BUTTON_STRUCT *btnStruct, const uint8_t *picName)
{

	btnStruct->btnPic.XSize = 78;
	btnStruct->btnPic.YSize = 104;
	btnStruct->btnPic.BytesPerLine = 160;
	btnStruct->btnPic.BitsPerPixel = 16;
	btnStruct->btnPic.pPal = NULL;
	btnStruct->btnPic.pMethods = GUI_DRAW_BMPM565;
	btnStruct->btnPic.pData = bmp_public_buf;
	bindBmpFileData(&btnStruct->btnPic.pData, (uint8_t *)picName);
	
	BUTTON_SetBitmapEx(btnStruct->btnHandle, 0, &btnStruct->btnPic, BMP_PIC_X, BMP_PIC_Y);

	BUTTON_SetFocussable(btnStruct->btnHandle, 0);
}
*/
//unsigned char bmp_public_buf[1280] = {0};
uint8_t logo_n[13] = "bmp_logo.bin";
uint8_t t[17] = "bmp_pre_heat.bin";
void DRAW_LOGO()
{
	int index; 
	int x_off = 0, y_off = 0;
	int _x, _y;
	uint16_t *p_index;
	int i;
	
	//GUI_SetBkColor(gCfgItems.background_color);
	//GUI_Clear();

	//GUI_SetColor(gCfgItems.title_color);
#if 0	
#if VERSION_WITH_PIC	
	Pic_Read(t,bmp_public_buf);

	for(index = 0; index < 120; index ++)
	{
		Pic_Logo_Read(logo_n, bmp_public_buf, 1280);

		
		i = 0;	

		ili9320_SetWindows(0, y_off * 2, 320, 2);
		ili9320_SetCursor(0, y_off * 2);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */	
		for(_y = y_off * 2; _y < (y_off + 1) * 2; _y++)
		{
			for (x_off = 0; x_off < 320; x_off++) 
			{
				p_index = (uint16_t *)(&bmp_public_buf[i]);						
				LCD_WriteRAM(*p_index);
				i += 2;
				
			}
			if(i >= 1280)
					break;
		}
		y_off++;		

		
	}
	ili9320_SetWindows(0, 0, 319, 239);
	
#endif	
#endif
	#if defined(TFT70)	
	/*for(index = 0; index < 10; index ++)
	{
		Pic_Logo_Read(logo_n, bmp_public_buf, 15360);

		
		i = 0;
		
		
		LCD_setWindowArea(0, y_off * 24, 320, 24);
		//**ili9320_SetCursor(0, y_off * 24);
		LCD_WriteRAM_Prepare(); 
		for(_y = y_off * 24; _y < (y_off + 1) * 24; _y++)
		{
			for (x_off = 0; x_off < 320; x_off++) 
			{
				p_index = (uint16_t *)(&bmp_public_buf[i]); 					
				LCD_WriteRAM(*p_index);
				i += 2;
				
			}
			if(i >= 15360)
					break;
		}
		y_off++;		

		
	}
	LCD_setWindowArea(0, 0, 320, 240);*/

	for(index = 0; index < 30; index ++)//800*480
	//for(index = 0; index < 15; index ++)//800*240
	{
		Pic_Logo_Read(logo_n, bmp_public_buf, 25600);//25k

		
		i = 0;
		
		
		LCD_setWindowArea(0, y_off * 16, 800,48);     //800*480
		//LCD_setWindowArea(0, y_off * 16+120, 800,48);      //800*240  
		//**ili9320_SetCursor(0, y_off * 16);
		LCD_WriteRAM_Prepare(); 
		for(_y = y_off * 16; _y < (y_off + 1) * 16; _y++)
		{
			for (x_off = 0; x_off < 800; x_off++) 
			{
				p_index = (uint16_t *)(&bmp_public_buf[i]); 					
				LCD_WriteRAM(*p_index);
				i += 2;
				
			}
			if(i >= 25600)
					break;
		}
		y_off++;		

		
	}
	LCD_setWindowArea(0, 0, 800, 480);

		/*LCD_setWindowArea(0, 0, 800, 480);
		LCD_setWindowArea(0,  48, 400,48);
		ili9320_SetCursor(0, 0);
		LCD_WriteRAM_Prepare(); 
		for(j=0;j<48;j++)
		{	for(k=0;k<400;k++)
				{
					LCD_WriteRAM(0XFFFFFFFF);	
				}
		}*/
	#elif defined(TFT35)
	for(index = 0; index < 20; index ++)//480*320
	{
		Pic_Logo_Read(logo_n, bmp_public_buf, 15360);//15k
		i = 0;
		LCD_setWindowArea(0, y_off * 16, 480,16);     //480*16
		//LCD_setWindowArea(0, y_off * 16+120, 800,48);      //800*240  
		//**ili9320_SetCursor(0, y_off * 16);
		LCD_WriteRAM_Prepare(); 
		for(_y = y_off * 16; _y < (y_off + 1) * 16; _y++)
		{
			for (x_off = 0; x_off < 480; x_off++) 
			{
				p_index = (uint16_t *)(&bmp_public_buf[i]); 					
				LCD_WriteRAM(*p_index);
				i += 2;
				
			}
			if(i >= 15360)
					break;
		}
		y_off++;		

		
	}
	LCD_setWindowArea(0, 0, 480, 320);	
	#endif	


}
#if 1
void Draw_default_preview(int xpos_pixel,int ypos_pixel,uint8_t sel)
{
	int index; 
	int x_off = 0, y_off = 0;
	int _x, _y;
	uint16_t *p_index;
	int i;
	uint16_t temp_p;
	
	for(index = 0; index < 4; index ++)//200*200
	{
		if(sel == 1)
		{
			flash_view_Read(bmp_public_buf, 20000);//20k
		}
		else
		{
			default_view_Read(bmp_public_buf, 20000);//20k
		}

		i = 0;
		
		LCD_setWindowArea(xpos_pixel, y_off * 50+ypos_pixel, 200,50);     //200*200

		LCD_WriteRAM_Prepare(); 
		for(_y = y_off * 50; _y < (y_off + 1) * 50; _y++)
		{
			for (x_off = 0; x_off < 200; x_off++) 
			{
				if(sel==1)
				{
					temp_p = (uint16_t)(bmp_public_buf[i]|bmp_public_buf[i+1]<<8);
					p_index = &temp_p;
				}
				else
				{
					p_index = (uint16_t *)(&bmp_public_buf[i]); 	
				}
				LCD_WriteRAM(*p_index);
				i += 2;
				
			}
			if(i >= 20000)
				break;
		}
		y_off++;		
	}

}

int ascii2dec_test1(char *ascii)
{
	int result = 0;

	if(ascii == 0)
		return 0;

	if(*(ascii) >= '0' && *(ascii) <= '9')
		result = *(ascii) - '0';
	else if(*(ascii) >= 'a' && *(ascii) <= 'f')
		result = *(ascii) - 'a' + 0x0a;
	else if(*(ascii) >= 'A' && *(ascii) <= 'F')
		result = *(ascii) - 'A' + 0x0a;
	else
		return 0;
		

	return result;
}

uint8_t preview_pic=0;
FIL TEST_FIL1;

FIL curFile_1;

uint8_t buff_pic[512];
uint32_t row;
uint32_t size = 809;
uint8_t gcode_preview_over;
uint8_t flash_preview_begin;
uint8_t default_preview_flg;
uint8_t from_flash_pic;
extern int once_flag;
extern "C" void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
extern "C" void SPI_FLASH_SectorErase(u32 SectorAddr);

void gcode_preview(FIL *file,int xpos_pixel,int ypos_pixel)
{
	uint8_t ress;
	UINT read,write;
	volatile uint32_t i,j;
	volatile uint16_t *p_index;
	int res;
	
	//memset(bmp_public_buf,0,sizeof(bmp_public_buf));
	f_lseek(file, (PREVIEW_LITTLE_PIC_SIZE+To_pre_view)+size*row+8);
	//ress = f_read(file, buff_pic, size, &read);
	//if(ress == FR_OK)
	{
      	LCD_setWindowArea(xpos_pixel, ypos_pixel+row, 200,1);
		LCD_WriteRAM_Prepare(); 
		j=0;
		i=0;
		
		while(1)
		{
			f_read(file, buff_pic, 400, &read);
			for(i=0;i<400;)
			{
				bmp_public_buf[j]= ascii2dec_test1((char*)&buff_pic[i])<<4|ascii2dec_test1((char*)&buff_pic[i+1]);
				//bmp_public_buf[j]= ascii2dec_test1((char*)&buff_pic[8+i])<<4|ascii2dec_test1((char*)&buff_pic[8+i+1]);
				i+=2;
				j++;
			}
			
			//if(i>800)break;
			//#if defined(TFT70)
			//if(j>400)
			//{
			//	f_read(file, buff_pic, 1, &read);
			//	break;
			//}				
			//#elif defined(TFT35)
			if(j>=400)
			{
				//f_read(file, buff_pic, 1, &read);
				break;
			}				
			//#endif

		}
		for(i=0;i<400;)
		{
			p_index = (uint16_t *)(&bmp_public_buf[i]); 					
	    	LCD_WriteRAM(*p_index);
			i=i+2;
		}
		if(row<20)
		{
			SPI_FLASH_SectorErase(BAK_VIEW_ADDR+row*4096);
		}
		SPI_FLASH_BufferWrite(bmp_public_buf, BAK_VIEW_ADDR+row*400, 400);
		row++;
		if(row >= 200)
		{
			size = 809;
			row = 0;
			
			gcode_preview_over = 0;
			//flash_preview_begin = 1;

			f_close(file);

			if(gCurFileState.file_open_flag != 0xaa)
			{
				
			
				reset_file_info();
				res = f_open(file, curFileName, FA_OPEN_EXISTING | FA_READ);
				if(res == FR_OK)
				{
					f_lseek(file,PREVIEW_SIZE+To_pre_view);
					gCurFileState.file_open_flag = 0xaa;

					bakup_file_path((uint8_t *)curFileName, strlen(curFileName));

					srcfp = file;

					printerStaus = pr_working;

					once_flag = 0;
				}
				
			}			
		}
	}
}

void disp_pre_gcode(int xpos_pixel,int ypos_pixel)
{
	if(gcode_preview_over==1)
	{
		gcode_preview(&TEST_FIL1,xpos_pixel,ypos_pixel);
	}
	if(flash_preview_begin == 1)
	{
		flash_preview_begin = 0;
		Draw_default_preview(xpos_pixel,ypos_pixel,1);	
	}
	if(default_preview_flg == 1)
	{
		Draw_default_preview(xpos_pixel,ypos_pixel,0);
		default_preview_flg = 0;
	}

}
void preview_gcode_prehandle(char *path)
{
	uint8_t re;
	UINT read;
	uint32_t pre_read_cnt = 0;
	uint32_t *p1,*p2;
	
	re = f_open(&TEST_FIL1, path, FA_OPEN_EXISTING | FA_READ);//	
	#if 0
	if(re == FR_OK)
	{
		f_lseek(&TEST_FIL1,PREVIEW_LITTLE_PIC_SIZE);//
		f_read(&TEST_FIL1,&bmp_public_buf,8,&read);
		if((bmp_public_buf[0] ==';')&&(bmp_public_buf[1] =='g')
			&&(bmp_public_buf[2] =='i')&&(bmp_public_buf[3] =='m')
			&&(bmp_public_buf[4] =='a')&&(bmp_public_buf[5] =='g')
			&&(bmp_public_buf[6] =='e')&&(bmp_public_buf[7] ==':'))	
		{
			gcode_preview_over = 1;
			from_flash_pic = 1;
			HAL::AT24CXX_Write(BAK_PREVIEW_FROM_FLASH_ADDR, &from_flash_pic,1);
		}
		else
		{
			gcode_preview_over = 0;
			default_preview_flg = 1;
			from_flash_pic = 0; 
			HAL::AT24CXX_Write(BAK_PREVIEW_FROM_FLASH_ADDR, &from_flash_pic,1);
		}
	}
	#else
	if(re==FR_OK)
	{
		//p1 = (int32_t *)&bmp_public_buf[0];
		
		f_read(&TEST_FIL1,&bmp_public_buf[0],1024,&read);
		
		p2 = (uint32_t *)strstr((const char *)&bmp_public_buf[0],(const char *)";simage:");
		if(p2)
		{
			pre_read_cnt = (uint32_t)p2-(uint32_t)((uint32_t *)(&bmp_public_buf[0]));
			//pre_sread_cnt = (uint32_t)ps4-(uint32_t)((uint32_t *)(&bmp_public_buf[0]));

			To_pre_view = pre_read_cnt;
			//f_lseek(&TEST_FIL1,PREVIEW_LITTLE_PIC_SIZE+pre_read_cnt);
			gcode_preview_over = 1;
			from_flash_pic = 1;
			HAL::AT24CXX_Write(BAK_PREVIEW_FROM_FLASH_ADDR, &from_flash_pic,1);			
		}
		else
		{
			gcode_preview_over = 0;
			default_preview_flg = 1;
			from_flash_pic = 0; 
			HAL::AT24CXX_Write(BAK_PREVIEW_FROM_FLASH_ADDR, &from_flash_pic,1);		
		}
	}
	#endif
}

#endif
#if 0

/*****************************************************/
//path:文件路径
//xsize,ysize:显示预览图片大小;
//sel:
//		0:文件目录预览；
//		1:打印文件预览
//
uint8_t drawicon_preview(char *path,int xsize_small,int ysize_small,int xsize_big,int ysize_big,char sel)
{

	uint16_t *p_index;
	int i=0;
	char re;
	UINT read;
	char temp_test[8];
	int row_1=0;
    
	re = f_open(&TEST_FIL,path, FA_OPEN_EXISTING | FA_READ);//huaping.gcode
	if(re == FR_OK)
	{
        memset(bmp_public_buf,0,sizeof(bmp_public_buf));
		if(sel == 1)//big pic
		{
			f_lseek(&TEST_FIL,xsize_small*ysize_small+8*(ysize_small+1));
		}
		f_read(&TEST_FIL,&bmp_public_buf,8,&read);
		if((bmp_public_buf[0] ==';')&&(bmp_public_buf[1] =='s')
			&&(bmp_public_buf[2] =='i')&&(bmp_public_buf[3] =='m')
			&&(bmp_public_buf[4] =='a')&&(bmp_public_buf[5] =='g')
			&&(bmp_public_buf[6] =='e')&&(bmp_public_buf[7] ==':'))
		{
			while(1)
			{
				f_read(&TEST_FIL,&temp_test,2,&read);
				if(sel == 1)//big pic
				{
						bmp_public_buf[row_1*(xsize_big*4)+i/2] = (char)(ascii2dec_test(&temp_test[0])<<4|ascii2dec_test(&temp_test[1]));				
				}
				else
	            {
	              		bmp_public_buf[row_1*(xsize_small*2)+i/2] = (char)(ascii2dec_test(&temp_test[0])<<4|ascii2dec_test(&temp_test[1]));
	            }
				i=i+2;
				if(sel == 1)//big pic
				{
					if(i>=(xsize_big*4))
					{
		                i=0;
		                row_1++;
		                f_read(&TEST_FIL,&temp_test,9,&read);					
					}
					if(row_1>ysize_big)
						break;					
				}
				else
				{
					if(i>=(xsize_small*4))
					{
		                i=0;
		                row_1++;
		                f_read(&TEST_FIL,&temp_test,9,&read);					
					}
					if(row_1>ysize_small)
						break;
				}

			}
			f_close(&TEST_FIL);
			return 1;
		}
	}
	f_close(&TEST_FIL);
	return 0;

}
#endif

