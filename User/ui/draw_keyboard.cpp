
#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"
#include "draw_set.h"
#include <ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include "wifi_module.h"
#include "draw_keyboard.h"
#include "draw_Tips.h"
#include "string.h"
#include "stdio.h"
#include "draw_wifi_list.h"
#include "wifi_list.h"
#include "spi_flash.h"
#include "pic_manager.h"
#include "mks_tft_com.h"

static GUI_HWIN hKeyboardWnd;
static TEXT_Handle textKeyboardTitle;
static BUTTON_STRUCT buttonRet,buttonJoint;
static BUTTON_STRUCT buttonWifiKey[26];
static BUTTON_STRUCT buttonSpace,buttondel2,buttonPassword;
static BUTTON_STRUCT buttonLetter,buttonDigital,buttonSymbol,buttonArrow;

extern GUI_BITMAP bmp_struct_32x21;
extern GUI_BITMAP bmp_struct_28x21;

KEYBOARD_STYPE keyboard_stype=UPPER_CASE_LETTER;
KEY_VALUE_CALC key_value_calc;

extern GUI_CONST_STORAGE GUI_FONT GUI_FontHelvetica26;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHelvetica36;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ_fontHz14;

extern char buf_to_wifi[256];
extern uint8_t console_flag;
const char digital_key_value[27]={'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
						   '-', '|', ':', ';', '(', ')', '$', '&', '@', '\"',
						   '.', ' ', ' ', ' ', ' ', ' ',0x00};
const char symbol_key_value[27]={',', '?', '!', '\'', '[', ']', '#', '{', '}', '%',
						   '^', '*', '+', '=', '_', '\\', '/', '~', '<', '>',
						    ' ', ' ', ' ', ' ', ' ', ' ',0x00};
#define VALUE_DISP_HEIGHT 60
#define KEY_WIDTH  (uint8_t)((LCD_WIDTH-6)/7)//67
#define KEY_HEIGHT (uint8_t)((LCD_HEIGHT-VALUE_DISP_HEIGHT-6)/6)//42

#define FIRST_LINE_WIDTH (uint8_t)((LCD_WIDTH-4)/5)//95

keyboard_menu_def keyboard_menu;

GUI_BITMAP bmp_struct_32x21 = {
  32,//80, /* XSize */
  21,//50, /* YSize */
  160, /* BytesPerLine */
  16, /* BitsPerPixel */
  (unsigned char *)bmp_public_buf,  /* Pointer to picture data */
  NULL  /* Pointer to palette */
 ,GUI_DRAW_BMPM565
};

GUI_BITMAP bmp_struct_28x21 = {
  28,//80, /* XSize */
  21,//50, /* YSize */
  160, /* BytesPerLine */
  16, /* BitsPerPixel */
  (unsigned char *)bmp_public_buf,  /* Pointer to picture data */
  NULL  /* Pointer to palette */
 ,GUI_DRAW_BMPM565
};

static void Value_confirm(void );
static void disp_KeyValue(void);



static void cbKeyboardWin(WM_MESSAGE * pMsg) {
       char buf[NUMBER_OF_DIGITS+2];
	uint8_t i=0;
	
	char wifi_ret_head = 0xa5;
	char wifi_ret_tail = 0xfc;
	char type = 0x08;
	int data_len = 0;
	int data_offset = 4;
	char *p=0,*q=0;
    
    struct PressEvt *press_event;

    //memset(buf,' ',NUMBER_OF_DIGITS+1);
    ///buf[NUMBER_OF_DIGITS+1]=0;
	
    switch (pMsg->MsgId)
    {
		case WM_PAINT:
			//GUI_SetColor(BUTTON_PRESS_BK_COLOR);
			//GUI_FillRect(0,titleHeight-2,LCD_WIDTH,titleHeight);
            
			GUI_SetColor(0x979797);
			GUI_FillRect(0,VALUE_DISP_HEIGHT,LCD_WIDTH-6,VALUE_DISP_HEIGHT+1);//横线
	            	GUI_FillRect(0,VALUE_DISP_HEIGHT+1+KEY_HEIGHT,LCD_WIDTH-6,VALUE_DISP_HEIGHT+1+KEY_HEIGHT+1);
			GUI_FillRect(0,VALUE_DISP_HEIGHT+1+KEY_HEIGHT*2+1,LCD_WIDTH-6,VALUE_DISP_HEIGHT+1+KEY_HEIGHT*2+1*2);
			GUI_FillRect(0,VALUE_DISP_HEIGHT+1+KEY_HEIGHT*3+1*2,LCD_WIDTH-6,VALUE_DISP_HEIGHT+1+KEY_HEIGHT*3+1*3);
			GUI_FillRect(0,VALUE_DISP_HEIGHT+1+KEY_HEIGHT*4+1*3,LCD_WIDTH-6,VALUE_DISP_HEIGHT+1+KEY_HEIGHT*4+1*4);
			GUI_FillRect(0,VALUE_DISP_HEIGHT+1+KEY_HEIGHT*5+1*4,LCD_WIDTH-6,VALUE_DISP_HEIGHT+1+KEY_HEIGHT*5+1*5);

			GUI_FillRect(FIRST_LINE_WIDTH,VALUE_DISP_HEIGHT,FIRST_LINE_WIDTH+1,VALUE_DISP_HEIGHT+(KEY_HEIGHT+1)*1);//第一行竖线
			GUI_FillRect(FIRST_LINE_WIDTH+1+FIRST_LINE_WIDTH*1,VALUE_DISP_HEIGHT,(FIRST_LINE_WIDTH+1)+FIRST_LINE_WIDTH*1+1,VALUE_DISP_HEIGHT+(KEY_HEIGHT+1)*1);
			GUI_FillRect((FIRST_LINE_WIDTH+1)+FIRST_LINE_WIDTH*2+1,VALUE_DISP_HEIGHT,(FIRST_LINE_WIDTH+1)+FIRST_LINE_WIDTH*2+1+1,VALUE_DISP_HEIGHT+(KEY_HEIGHT+1)*1);
			GUI_FillRect((FIRST_LINE_WIDTH+1)+FIRST_LINE_WIDTH*3+1+1,VALUE_DISP_HEIGHT,(FIRST_LINE_WIDTH+1)+FIRST_LINE_WIDTH*3+1+1+1,VALUE_DISP_HEIGHT+(KEY_HEIGHT+1)*1);

			GUI_FillRect(KEY_WIDTH,VALUE_DISP_HEIGHT+1+KEY_HEIGHT,KEY_WIDTH+1,VALUE_DISP_HEIGHT+KEY_HEIGHT*5+4);//竖线
			GUI_FillRect(KEY_WIDTH*2+1,VALUE_DISP_HEIGHT+1+KEY_HEIGHT,KEY_WIDTH*2+1*2,VALUE_DISP_HEIGHT+KEY_HEIGHT*5+5);
			GUI_FillRect(KEY_WIDTH*3+1*2,VALUE_DISP_HEIGHT+1+KEY_HEIGHT,KEY_WIDTH*3+1*3,VALUE_DISP_HEIGHT+KEY_HEIGHT*5+5);
			GUI_FillRect(KEY_WIDTH*4+1*3,VALUE_DISP_HEIGHT+1+KEY_HEIGHT,KEY_WIDTH*4+1*4,VALUE_DISP_HEIGHT+KEY_HEIGHT*5+5);
			GUI_FillRect(KEY_WIDTH*5+1*4,VALUE_DISP_HEIGHT+1+KEY_HEIGHT,KEY_WIDTH*5+1*5,VALUE_DISP_HEIGHT+KEY_HEIGHT*5+5);
			GUI_FillRect(KEY_WIDTH*6+1*5,VALUE_DISP_HEIGHT+1+KEY_HEIGHT,KEY_WIDTH*6+1*6,VALUE_DISP_HEIGHT+KEY_HEIGHT*5+5);

			GUI_FillRect(123,VALUE_DISP_HEIGHT+KEY_HEIGHT*4+4+1,123+1,LCD_HEIGHT);//最后一行竖线
			GUI_FillRect(358,VALUE_DISP_HEIGHT+KEY_HEIGHT*4+4+1,358+1,LCD_HEIGHT);
	            
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
    			if(pMsg->hWinSrc == buttonRet.btnHandle)
				{
					if(gcodeSet_flag != 0)
						gcodeSet_flag = 0;
					key_value_calc.timer = TIMER_STOP;
                    last_disp_state = KEY_BOARD_UI;
					Clear_Keyboard();
					draw_return_ui();	
				}
				else if(pMsg->hWinSrc == buttonJoint.btnHandle)
				{
					//BUTTON_SetFont(buttonJoint.btnHandle,&GUI_FontHelvetica26);
					if(key_value_calc.cnt > 0)
					{
						key_value_calc.timer = TIMER_STOP;
						//lan
						if(valueType == wifi_setting)
						{
							memset((void *)gCfgItems.wifi_ap, 0, sizeof(gCfgItems.wifi_ap));
							memcpy((void *)gCfgItems.wifi_ap, wifi_list.wifiName[wifi_list.nameIndex], 32);

							memset((void *)gCfgItems.wifi_key, 0, sizeof(gCfgItems.wifi_key));
							memcpy((void *)gCfgItems.wifi_key, key_value_calc.password_value, sizeof(key_value_calc.password_value));

							gCfgItems.wifi_mode_sel = 2;
							
							package_to_wifi(WIFI_PARA_SET, (char *)0, 0);

							//连接目前配置的wifi热点
							buf[0] = 0xA5;
							buf[1] = 0x09;
							buf[2] = 0x01;
							buf[3] = 0x00;
							buf[4] = 0x01;
							buf[5] = 0xFC;
							buf[6] = 0x00;
							raw_send_to_wifi(buf, 6);
							last_disp_state = KEY_BOARD_UI;
							Clear_Keyboard();
							tips_type = TIPS_TYPE_JOINING;
							draw_Tips();
						}
						else 
						{
							Value_confirm();
							last_disp_state = KEY_BOARD_UI;
							Clear_Keyboard();							
							if(gcodeSet_flag == 1)
							{
								console_flag=1;
								clear_cur_ui(); 
							}
							else 
								draw_return_ui();
							}
						}
				}       
				else if(pMsg->hWinSrc == buttondel2.btnHandle)
				{
					BUTTON_SetBmpFileName(buttondel2.btnHandle, "bmp_backspace_white.bin",1);
                           		BUTTON_SetBitmapEx(buttondel2.btnHandle, 0, &bmp_struct_32x21,(FIRST_LINE_WIDTH-32)/2, (KEY_HEIGHT-21)/2);
					if(key_value_calc.cnt > 0)
			              {   
			                   key_value_calc.cnt--;  
			              }
		                	key_value_calc.password_value[key_value_calc.cnt] = 0;
					key_value_calc.password_disp[key_value_calc.cnt] = 0;
					if(key_value_calc.cnt  == 0)
					{
//						strncpy((char *)key_value_calc.password_disp,keyboard_menu.password,sizeof(key_value_calc.password_disp));
						BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_PRESSED, 0x3f3f3f);
    						BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_UNPRESSED,0x3f3f3f);
					}
					BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
				}  
				else if(pMsg->hWinSrc == buttonSpace.btnHandle)
		              {
		              	//BUTTON_SetFont(buttonSpace.btnHandle,&GUI_FontHelvetica20);
		              	if(key_value_calc.cnt == 0)
		              	{
		              		memset(key_value_calc.password_disp,0,sizeof(key_value_calc.password_disp));
		              		BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_PRESSED, 0xffffff);
    						BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_UNPRESSED,0xffffff);
						BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
		              	}
		                     if(key_value_calc.cnt <= NUMBER_OF_PASSWORD)
					{
						key_value_calc.timer = TIMER_STOP;
						key_value_calc.timer_count = 0;
						if(key_value_calc.cnt > 0)
						{
//							key_value_calc.password_disp[key_value_calc.cnt - 1] = (uint8_t)TEXT_PIONT_BOLD;
						}
						key_value_calc.password_value[key_value_calc.cnt] = ' ';
						key_value_calc.password_disp[key_value_calc.cnt] = ' ';
						BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
                    				key_value_calc.cnt++;
						key_value_calc.timer = TIMER_START;
					}
		              }
				else if(pMsg->hWinSrc == buttonLetter.btnHandle)
		              {
		              	//BUTTON_SetFont(buttonLetter.btnHandle,&GUI_FontHelvetica26);
		                     keyboard_stype = UPPER_CASE_LETTER;
					update_keyboard_disp();
		              }
				else if(pMsg->hWinSrc == buttonDigital.btnHandle)
		              {
		              	//BUTTON_SetFont(buttonDigital.btnHandle,&GUI_FontHelvetica26);
		                     keyboard_stype = DIGITLA;
					update_keyboard_disp();
		              }
				else if(pMsg->hWinSrc == buttonSymbol.btnHandle)
		              {
		              	//BUTTON_SetFont(buttonSymbol.btnHandle,&GUI_FontHelvetica26);
		                     keyboard_stype = SYMBOL;
					update_keyboard_disp();
		              }
				else if(pMsg->hWinSrc == buttonArrow.btnHandle)
		              {
		                     if(keyboard_stype == UPPER_CASE_LETTER)
		                     {
		                     	keyboard_stype = LOWER_CASE_LETTER;
						BUTTON_SetBmpFileName(buttonArrow.btnHandle,"bmp_Toggle_Up_Arrow_White.bin",1);
    						BUTTON_SetBitmapEx(buttonArrow.btnHandle, 0, &bmp_struct_28x21,(FIRST_LINE_WIDTH-28)/2, (KEY_HEIGHT-21)/2);
		                     }
					else if(keyboard_stype == LOWER_CASE_LETTER)
					{
						keyboard_stype = UPPER_CASE_LETTER;
						BUTTON_SetBmpFileName(buttonArrow.btnHandle,"bmp_Toggle_Down_Arrow_White.bin",1);
    						BUTTON_SetBitmapEx(buttonArrow.btnHandle, 0, &bmp_struct_28x21,(FIRST_LINE_WIDTH-28)/2, (KEY_HEIGHT-21)/2);
					}
					update_keyboard_disp();
		              }
				else if(pMsg->hWinSrc == buttonPassword.btnHandle)
				{
					if(key_value_calc.cnt == 0)
		              	{
		              		memset(key_value_calc.password_disp,0,sizeof(key_value_calc.password_disp));
		              		BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_PRESSED, 0xffffff);
    						BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_UNPRESSED,0xffffff);
						BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
		              	}
				}
				else
				{
					i=26;
                           		while(i--)
	                           	{
						if(pMsg->hWinSrc == buttonWifiKey[i].btnHandle)
						{
							//BUTTON_SetFont(buttonWifiKey[i].btnHandle,&GUI_FontHelvetica26);
							switch(keyboard_stype)
							{
								case UPPER_CASE_LETTER:
									if(key_value_calc.cnt == 0)
						              	{
						              		memset(key_value_calc.password_disp,0,sizeof(key_value_calc.password_disp));
						              		BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_PRESSED, 0xffffff);
				    						BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_UNPRESSED,0xffffff);
										BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
						              	}
						                     if(key_value_calc.cnt <= NUMBER_OF_PASSWORD)
									{
										key_value_calc.timer = TIMER_STOP;
										key_value_calc.timer_count = 0;
										if(key_value_calc.cnt > 0)
										{
//											key_value_calc.password_disp[key_value_calc.cnt - 1] = (uint8_t)TEXT_PIONT_BOLD;
										}
										key_value_calc.password_value[key_value_calc.cnt] = 'A' + i;
										key_value_calc.password_disp[key_value_calc.cnt] = 'A' + i;
										BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
				                    				key_value_calc.cnt++;
										key_value_calc.timer = TIMER_START;
									}
									break;
								case LOWER_CASE_LETTER:
									if(key_value_calc.cnt == 0)
						              	{
						              		memset(key_value_calc.password_disp,0,sizeof(key_value_calc.password_disp));
						              		BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_PRESSED, 0xffffff);
				    						BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_UNPRESSED,0xffffff);
										BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
						              	}
						                     if(key_value_calc.cnt <= NUMBER_OF_PASSWORD)
									{
										key_value_calc.timer = TIMER_STOP;
										key_value_calc.timer_count = 0;
										if(key_value_calc.cnt > 0)
										{
//											key_value_calc.password_disp[key_value_calc.cnt - 1] = (uint8_t)TEXT_PIONT_BOLD;
										}
										key_value_calc.password_value[key_value_calc.cnt] = 'a' + i;
										key_value_calc.password_disp[key_value_calc.cnt] = 'a' + i;
										BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
				                    				key_value_calc.cnt++;
										key_value_calc.timer = TIMER_START;
									}
									break;
								case DIGITLA:
									if(i >= 21)
									{
										continue;
									}
									if(key_value_calc.cnt == 0)
						              	{
						              		memset(key_value_calc.password_disp,0,sizeof(key_value_calc.password_disp));
						              		BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_PRESSED, 0xffffff);
				    						BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_UNPRESSED,0xffffff);
										BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
						              	}
						                     if(key_value_calc.cnt <= NUMBER_OF_PASSWORD)
									{
										key_value_calc.timer = TIMER_STOP;
										key_value_calc.timer_count = 0;
										if(key_value_calc.cnt > 0)
										{
//											key_value_calc.password_disp[key_value_calc.cnt - 1] = (uint8_t)TEXT_PIONT_BOLD;
										}
										key_value_calc.password_value[key_value_calc.cnt] = (uint8_t)digital_key_value[i];
										key_value_calc.password_disp[key_value_calc.cnt] = (uint8_t)digital_key_value[i];
										BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
				                    				key_value_calc.cnt++;
										key_value_calc.timer = TIMER_START;
									}
									break;
								case SYMBOL:
									if(i >= 20)
									{
										continue;
									}
									if(key_value_calc.cnt == 0)
						              	{
						              		memset(key_value_calc.password_disp,0,sizeof(key_value_calc.password_disp));
						              		BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_PRESSED, 0xffffff);
				    						BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_UNPRESSED,0xffffff);
										BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
						              	}
						                     if(key_value_calc.cnt <= NUMBER_OF_PASSWORD)
									{
										key_value_calc.timer = TIMER_STOP;
										key_value_calc.timer_count = 0;
										if(key_value_calc.cnt > 0)
										{
//											key_value_calc.password_disp[key_value_calc.cnt - 1] = (uint8_t)TEXT_PIONT_BOLD;
										}
										key_value_calc.password_value[key_value_calc.cnt] = (uint8_t)symbol_key_value[i];
										key_value_calc.password_disp[key_value_calc.cnt] = (uint8_t)symbol_key_value[i];
										BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
				                    				key_value_calc.cnt++;
										key_value_calc.timer = TIMER_START;
									}
									break;
								default:
									break;
							}
						}
	                           }
				}   
                            
            }
	     else if(pMsg->Data.v == WM_NOTIFICATION_CLICKED)
	     {
			if(pMsg->hWinSrc == buttonRet.btnHandle)
			{
				//BUTTON_SetFont(buttonRet.btnHandle,&GUI_FontHelvetica26_bold);
			}
			else if(pMsg->hWinSrc == buttonJoint.btnHandle)
			{
				//BUTTON_SetFont(buttonJoint.btnHandle,&GUI_FontHelvetica26_bold);
			}
			  else if(pMsg->hWinSrc == buttondel2.btnHandle)
	                {
	                     BUTTON_SetBmpFileName(buttondel2.btnHandle, "bmp_backspace_black.bin",1);
	    			 BUTTON_SetBitmapEx(buttondel2.btnHandle, 0, &bmp_struct_32x21,18, 11);
	                }
			  else if(pMsg->hWinSrc == buttonSpace.btnHandle)
	                {
	                     //BUTTON_SetFont(buttonSpace.btnHandle,&GUI_FontHelvetica20_bold);
	                }
			  else if(pMsg->hWinSrc == buttonLetter.btnHandle)
	               {
	                     //BUTTON_SetFont(buttonLetter.btnHandle,&GUI_FontHelvetica26_bold);
	               }
			 else if(pMsg->hWinSrc == buttonDigital.btnHandle)
	               {
	                     //BUTTON_SetFont(buttonDigital.btnHandle,&GUI_FontHelvetica26_bold);
	               }
			 else if(pMsg->hWinSrc == buttonSymbol.btnHandle)
	               {
	                     //BUTTON_SetFont(buttonSymbol.btnHandle,&GUI_FontHelvetica26_bold);
	               }
			 else if(pMsg->hWinSrc == buttonArrow.btnHandle)
	               {
	               	if(keyboard_stype == UPPER_CASE_LETTER)
	               	{
	               		//BUTTON_SetBmpFileName(buttonArrow.btnHandle,"bmp_Toggle_Down_Arrow_Black.bin",1);
    					//BUTTON_SetBitmapEx(buttonArrow.btnHandle, 0, &bmp_struct_28x21,(FIRST_LINE_WIDTH-28)/2, (KEY_HEIGHT-21)/2);
	               	}
	                     else if(keyboard_stype == LOWER_CASE_LETTER)
	                     {
	                     	//BUTTON_SetBmpFileName(buttonArrow.btnHandle,"bmp_Toggle_Up_Arrow_Black.bin",1);
    					//BUTTON_SetBitmapEx(buttonArrow.btnHandle, 0, &bmp_struct_28x21,(FIRST_LINE_WIDTH-28)/2, (KEY_HEIGHT-21)/2);
	                     }
	               }
			  else
			  {
			  	i=26;
				while(i--)
				{
					if(pMsg->hWinSrc == buttonWifiKey[i].btnHandle)
					{
						//BUTTON_SetFont(buttonWifiKey[i].btnHandle,&GUI_FontHelvetica26_bold);
					}
				}
				i=0;
			  }
		  
		}	            
            break;
    }
}

void draw_Keyboard()
{
       char buf[40];
	char cutName[33];
	uint8_t i=0;
    
 	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != KEY_BOARD_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = KEY_BOARD_UI;
	}
	disp_state = KEY_BOARD_UI;
	
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();

	
	   //keyboard_menu.pointBold = TEXT_WIFI_POINT_BOLD_EN;

	   //keyboard_menu.joining = TEXT_WIFI_JOINING_EN;
	   //keyboard_menu.failedJoin = TEXT_WIFI_FAILED_JOIN_EN;
	   //keyboard_menu.wifiConected = TEXT_WIFI_WIFI_CONECTED_EN; 
    
    hKeyboardWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbKeyboardWin, 0);
    //textKeyboardTitle = TEXT_CreateEx(0,0,LCD_WIDTH,titleHeight, hKeyboardWnd, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_VCENTER,   GUI_ID_TEXT1, "");
    //TEXT_SetFont(textKeyboardTitle,&GUI_FontHelvetica36);
    //TEXT_SetTextColor(textKeyboardTitle,BUTTON_PRESS_BK_COLOR);
    //memset(buf,0,sizeof(buf));
    //memset(cutName,0,sizeof(cutName));
    //strcat(buf,wifi_menu.title);
    //strcat(buf," ");
   // cutWifiName((char * )wifi_list.wifiName[wifi_list.nameIndex], 12, cutName);
    //strcat(buf,(const char *)cutName);
    //TEXT_SetText(textKeyboardTitle,buf);
    
    
    buttonRet.btnHandle = BUTTON_CreateEx((KEY_WIDTH+1)*6,VALUE_DISP_HEIGHT+1+KEY_HEIGHT*4+1*4,KEY_WIDTH,KEY_HEIGHT, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

    buttonJoint.btnHandle = BUTTON_CreateEx(LCD_WIDTH-80,10,90,40, hKeyboardWnd, BUTTON_CF_SHOW, 0, 310);

    BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.background_color);
    BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.background_color);
    BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_BK_COLOR);
    BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetBmpFileName(buttonRet.btnHandle,"bmp_keyboard_return.bin",1);
    BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct_32x21,(KEY_WIDTH-32)/2, (KEY_HEIGHT-21)/2);
    
    BUTTON_SetBkColor(buttonJoint.btnHandle, BUTTON_CI_PRESSED, gCfgItems.background_color);
    BUTTON_SetBkColor(buttonJoint.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.background_color);
	
							
    //if(enter_state.join_state == JOIN_STATE_OK)
    //{  
      	//BUTTON_SetTextColor(buttonJoint.btnHandle, BUTTON_CI_PRESSED, 0xffffff);
    	//BUTTON_SetTextColor(buttonJoint.btnHandle, BUTTON_CI_UNPRESSED,0xffffff);
    //}
    //else
    //{
    	BUTTON_SetTextColor(buttonJoint.btnHandle, BUTTON_CI_PRESSED, 0x3f3f3f);
    	BUTTON_SetTextColor(buttonJoint.btnHandle, BUTTON_CI_UNPRESSED,0x3f3f3f);
    //}
    BUTTON_SetTextAlign(buttonJoint.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER);

    //BUTTON_SetFont(buttonRet.btnHandle,&GUI_FontHelvetica24);
    //BUTTON_SetText(buttonRet.btnHandle, build_cancel_menu.back);
    
    BUTTON_SetFont(buttonJoint.btnHandle,&GUI_FontHelvetica36);
	if (gcodeSet_flag != 0 )
    	BUTTON_SetText(buttonJoint.btnHandle, keyboard_menu.send);
	else 
		BUTTON_SetText(buttonJoint.btnHandle, keyboard_menu.apply);

    buttonPassword.btnHandle = BUTTON_CreateEx(10,10,LCD_WIDTH-100,40, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    BUTTON_SetBkColor(buttonPassword.btnHandle, BUTTON_CI_PRESSED, gCfgItems.background_color);
    BUTTON_SetBkColor(buttonPassword.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.background_color);
    BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_PRESSED, 0x3f3f3f);
    BUTTON_SetTextColor(buttonPassword.btnHandle, BUTTON_CI_UNPRESSED,0x3f3f3f);
    BUTTON_SetTextAlign(buttonPassword.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER);
    BUTTON_SetFont(buttonPassword.btnHandle,&GUI_FontHelvetica36);
//    BUTTON_SetText(buttonPassword.btnHandle, keyboard_menu.password);
	disp_KeyValue();
    BUTTON_SetBmpFileName(buttonPassword.btnHandle,NULL,1);
    

    buttonLetter.btnHandle = BUTTON_CreateEx(FIRST_LINE_WIDTH+1,VALUE_DISP_HEIGHT+1,FIRST_LINE_WIDTH,KEY_HEIGHT, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    buttonDigital.btnHandle = BUTTON_CreateEx((FIRST_LINE_WIDTH+1)*2,VALUE_DISP_HEIGHT+1,FIRST_LINE_WIDTH,KEY_HEIGHT, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    buttonSymbol.btnHandle = BUTTON_CreateEx((FIRST_LINE_WIDTH+1)*3,VALUE_DISP_HEIGHT+1,FIRST_LINE_WIDTH,KEY_HEIGHT, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    buttonArrow.btnHandle = BUTTON_CreateEx(0,VALUE_DISP_HEIGHT+1,FIRST_LINE_WIDTH,KEY_HEIGHT, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
    BUTTON_SetBkColor(buttonLetter.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_BK_COLOR);
    BUTTON_SetBkColor(buttonLetter.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.background_color);
    BUTTON_SetTextColor(buttonLetter.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_TEXT_COLOR);
    BUTTON_SetTextColor(buttonLetter.btnHandle, BUTTON_CI_UNPRESSED,gCfgItems.btn_textcolor);
    BUTTON_SetTextAlign(buttonLetter.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER);
    BUTTON_SetBmpFileName(buttonLetter.btnHandle,NULL,1);
    
    BUTTON_SetBkColor(buttonDigital.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_BK_COLOR);
    BUTTON_SetBkColor(buttonDigital.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.background_color);
    BUTTON_SetTextColor(buttonDigital.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_TEXT_COLOR);
    BUTTON_SetTextColor(buttonDigital.btnHandle, BUTTON_CI_UNPRESSED,gCfgItems.btn_textcolor);
    BUTTON_SetTextAlign(buttonDigital.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER);
    BUTTON_SetBmpFileName(buttonDigital.btnHandle,NULL,1);
    
    BUTTON_SetBkColor(buttonSymbol.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_BK_COLOR);
    BUTTON_SetBkColor(buttonSymbol.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.background_color);
    BUTTON_SetTextColor(buttonSymbol.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_TEXT_COLOR);
    BUTTON_SetTextColor(buttonSymbol.btnHandle, BUTTON_CI_UNPRESSED,gCfgItems.btn_textcolor);
    BUTTON_SetTextAlign(buttonSymbol.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER);
    BUTTON_SetBmpFileName(buttonSymbol.btnHandle,NULL,1);
    
    BUTTON_SetBkColor(buttonArrow.btnHandle, BUTTON_CI_PRESSED, gCfgItems.background_color);
    BUTTON_SetBkColor(buttonArrow.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.background_color);
    BUTTON_SetTextColor(buttonArrow.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
    BUTTON_SetTextColor(buttonArrow.btnHandle, BUTTON_CI_UNPRESSED,gCfgItems.btn_textcolor);
    BUTTON_SetTextAlign(buttonArrow.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER);
    BUTTON_SetBmpFileName(buttonArrow.btnHandle,"bmp_Toggle_Down_Arrow_White.bin",1);
    BUTTON_SetBitmapEx(buttonArrow.btnHandle, 0, &bmp_struct_28x21,(FIRST_LINE_WIDTH-28)/2, (KEY_HEIGHT-21)/2);

    
    BUTTON_SetFont(buttonLetter.btnHandle,&GUI_FontHelvetica26);
    BUTTON_SetText(buttonLetter.btnHandle, keyboard_menu.letter);
    BUTTON_SetFont(buttonDigital.btnHandle,&GUI_FontHelvetica26);
    BUTTON_SetText(buttonDigital.btnHandle, keyboard_menu.digital);
    BUTTON_SetFont(buttonSymbol.btnHandle,&GUI_FontHelvetica26);
    BUTTON_SetText(buttonSymbol.btnHandle, keyboard_menu.symbol);

    buttonSpace.btnHandle = BUTTON_CreateEx(123+1,VALUE_DISP_HEIGHT+1+KEY_HEIGHT*5+1*5,234,KEY_HEIGHT+2, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	
    BUTTON_SetBkColor(buttonSpace.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_BK_COLOR);
    BUTTON_SetBkColor(buttonSpace.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
    BUTTON_SetTextColor(buttonSpace.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_TEXT_COLOR);
    BUTTON_SetTextColor(buttonSpace.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
    BUTTON_SetTextAlign(buttonSpace.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER);
    BUTTON_SetFont(buttonSpace.btnHandle,&GUI_FontHelvetica26);
    BUTTON_SetBmpFileName(buttonSpace.btnHandle,NULL,1);
    BUTTON_SetText(buttonSpace.btnHandle,keyboard_menu.space);

    buttondel2.btnHandle = BUTTON_CreateEx((FIRST_LINE_WIDTH+1)*4,VALUE_DISP_HEIGHT+1,FIRST_LINE_WIDTH,KEY_HEIGHT, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    BUTTON_SetBmpFileName(buttondel2.btnHandle, "bmp_backspace_white.bin",1);
    BUTTON_SetBitmapEx(buttondel2.btnHandle, 0, &bmp_struct_32x21,(FIRST_LINE_WIDTH-32)/2, (KEY_HEIGHT-21)/2);
    BUTTON_SetBkColor(buttondel2.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_BK_COLOR);
    BUTTON_SetBkColor(buttondel2.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
    BUTTON_SetTextColor(buttondel2.btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_TEXT_COLOR);
    BUTTON_SetTextColor(buttondel2.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	

	i=26;
	while(i--)
	{
		if(i < 7)
		{
			buttonWifiKey[i].btnHandle = BUTTON_CreateEx((KEY_WIDTH+1)*i,VALUE_DISP_HEIGHT+1+KEY_HEIGHT+1,KEY_WIDTH,KEY_HEIGHT, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		}
		else if(i >= 7 && i < 14)
		{
			buttonWifiKey[i].btnHandle = BUTTON_CreateEx((KEY_WIDTH+1)*(i - 7),VALUE_DISP_HEIGHT+1+KEY_HEIGHT*2+1*2,KEY_WIDTH,KEY_HEIGHT, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		}
		else if(i >= 14 && i < 21)
		{
			buttonWifiKey[i].btnHandle = BUTTON_CreateEx((KEY_WIDTH+1)*(i - 14),VALUE_DISP_HEIGHT+1+KEY_HEIGHT*3+1*3,KEY_WIDTH,KEY_HEIGHT, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		}
		else if(i >= 21 && i < 26)
		{
			buttonWifiKey[i].btnHandle = BUTTON_CreateEx((KEY_WIDTH+1)*(i - 20),VALUE_DISP_HEIGHT+1+KEY_HEIGHT*4+1*4,KEY_WIDTH,KEY_HEIGHT, hKeyboardWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
		}

		memset(buf,0,sizeof(buf));
		//sprintf(buf,"%d",0x41 + i);
		buf[0] = 0x41 + i;
		BUTTON_SetText(buttonWifiKey[i].btnHandle, (const char *)buf);

		BUTTON_SetBkColor(buttonWifiKey[i].btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_BK_COLOR);
	    	BUTTON_SetBkColor(buttonWifiKey[i].btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	    	BUTTON_SetTextColor(buttonWifiKey[i].btnHandle, BUTTON_CI_PRESSED, BUTTON_PRESS_TEXT_COLOR);
	    	BUTTON_SetTextColor(buttonWifiKey[i].btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);
	    	BUTTON_SetTextAlign(buttonWifiKey[i].btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER);
	    	BUTTON_SetFont(buttonWifiKey[i].btnHandle,&GUI_FontHelvetica26);
                
              BUTTON_SetBmpFileName(buttonWifiKey[i].btnHandle,NULL,1);
	}
    	/*BUTTON_SetText(buttonkey[0].btnHandle, "0");
		BUTTON_SetText(buttonkey[1].btnHandle, "1");
		BUTTON_SetText(buttonkey[2].btnHandle, "2");
		BUTTON_SetText(buttonkey[3].btnHandle, "3");*/
		
	key_value_calc.cnt = 0;
	memset(key_value_calc.password_value,0,sizeof(key_value_calc.password_value));
	memset(key_value_calc.password_disp,0,sizeof(key_value_calc.password_disp));
	keyboard_stype = UPPER_CASE_LETTER;
    
}



void update_keyboard_disp(void)
{
	int8_t i;
	char buf[2];
	switch(keyboard_stype)
	{
		case UPPER_CASE_LETTER:
			i=26;
			while(i--)
			{
				memset(buf,0,sizeof(buf));
				buf[0] = 0x41 + i;
				BUTTON_SetText(buttonWifiKey[i].btnHandle, (const char *)buf);
			}
			BUTTON_SetBmpFileName(buttonArrow.btnHandle,"bmp_Toggle_Down_Arrow_White.bin",1);
    			BUTTON_SetBitmapEx(buttonArrow.btnHandle, 0, &bmp_struct_28x21,(FIRST_LINE_WIDTH-28)/2, (KEY_HEIGHT-21)/2);
			break;
		case LOWER_CASE_LETTER:
			i=26;
			while(i--)
			{
				memset(buf,0,sizeof(buf));
				buf[0] = 0x61 + i;
				BUTTON_SetText(buttonWifiKey[i].btnHandle, (const char *)buf);
			}
			BUTTON_SetBmpFileName(buttonArrow.btnHandle,"bmp_Toggle_Up_Arrow_White.bin",1);
    			BUTTON_SetBitmapEx(buttonArrow.btnHandle, 0, &bmp_struct_28x21,(FIRST_LINE_WIDTH-28)/2, (KEY_HEIGHT-21)/2);
			break;
		case DIGITLA:
			i=26;
			while(i--)
			{
				memset(buf,0,sizeof(buf));
				buf[0] = digital_key_value[i];
				BUTTON_SetText(buttonWifiKey[i].btnHandle, (const char *)buf);
			}
			BUTTON_SetBmpFileName(buttonArrow.btnHandle,NULL,1);
			break;
		case SYMBOL:
			i=26;
			while(i--)
			{
				memset(buf,0,sizeof(buf));
				buf[0] = symbol_key_value[i];
				BUTTON_SetText(buttonWifiKey[i].btnHandle, (const char *)buf);
			}
			BUTTON_SetBmpFileName(buttonArrow.btnHandle,NULL,1);
			break;
		default:
			break;
	}
}

void update_password_disp(void)
{
	if(key_value_calc.timer_count >= 1000)
	{
		key_value_calc.timer = TIMER_STOP;
		key_value_calc.timer_count = 0;
		
//		key_value_calc.password_disp[key_value_calc.cnt-1] = (uint8_t)TEXT_PIONT_BOLD;
		
		BUTTON_SetText(buttonPassword.btnHandle, (const char *)key_value_calc.password_disp);
	}
}

void update_join_state_disp(void)
{
	if(key_value_calc.cnt == 0)
    	{  
      		BUTTON_SetTextColor(buttonJoint.btnHandle, BUTTON_CI_PRESSED, 0x3f3f3f);
    		BUTTON_SetTextColor(buttonJoint.btnHandle, BUTTON_CI_UNPRESSED,0x3f3f3f);
    	}
    	else
    	{
    		BUTTON_SetTextColor(buttonJoint.btnHandle, BUTTON_CI_PRESSED, 0xffffff);
    		BUTTON_SetTextColor(buttonJoint.btnHandle, BUTTON_CI_UNPRESSED,0xffffff);
    	}
}

void Clear_Keyboard()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hKeyboardWnd))
	{
		WM_DeleteWindow(hKeyboardWnd);
		//GUI_Exec();   
	}
	
	//GUI_Clear();    
}




static void Value_confirm(void )
{
	switch(valueType)
	{
		
	case auto_levelCmd:	
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));		
		flash_reWriteInf((u8 *)cmd_code,BUTTON_AUTOLEVELING_ADDR,(strlen(cmd_code)+1));
		//test
//		memset(cmd_code,0,sizeof(cmd_code));
//		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_AUTOLEVELING_ADDR,201);
//        BUTTON_SetText(auto_Leveling_cmd.btnHandle,cmd_code);  
	break;
	
//	case wifi_name:
//		memset((void *)cmd_code,0,sizeof(cmd_code));		
//		memset((void *)gCfgItems.wifi_ap,0,sizeof(gCfgItems.wifi_ap));		
//		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));	
//		memcpy((void *)gCfgItems.wifi_ap, key_value_calc.password_value, sizeof(key_value_calc.password_value));	
////		strcpy(gCfgItems.wifi_ap,cmd_code);//add
//		flash_reWriteInf((u8 *)cmd_code,WIFI_NAME_ADDR,(strlen(cmd_code)+1));
////			cfg_wifi_flag = 1;
//	break;
//	case wifi_key:
//		memset((void *)cmd_code,0,sizeof(cmd_code));		
//		memset((void *)gCfgItems.wifi_key,0,sizeof(gCfgItems.wifi_key));	
//		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));		
////		strcpy(gCfgItems.wifi_key,()cmd_code);//add
//		memcpy((void *)gCfgItems.wifi_key, key_value_calc.password_value, sizeof(key_value_calc.password_value));		
//		flash_reWriteInf((u8 *)cmd_code,WIFI_KEYCODE_ADDR,(strlen(cmd_code)+1));	
////		cfg_wifi_flag = 1;
//	break;
//	case wifi_host:
//		memset((void *)gCfgItems.cloud_hostUrl,0,sizeof(gCfgItems.cloud_hostUrl));
//		memcpy((void *)gCfgItems.cloud_hostUrl, key_value_calc.password_value, sizeof(key_value_calc.password_value));
////		strncpy(gCfgItems.cloud_hostUrl, cmd_code, 96);
//	cfg_cloud_flag = 1;
//	break;

	
	case func_btn1Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));				
		flash_reWriteInf((u8 *)cmd_code,BUTTON_FUNCTION1_ADDR,(strlen(cmd_code)+1));	

	break;
	case btn1Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));				
		flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD1_ADDR,(strlen(cmd_code)+1));
		
	break;
	case btn2Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));				
		flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD2_ADDR,(strlen(cmd_code)+1));

	break;
	case btn3Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));				
		flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD3_ADDR,(strlen(cmd_code)+1));
	break;
	case btn4Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));				
	flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD4_ADDR,(strlen(cmd_code)+1));

	break;	
	case btn5Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));				
		flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD5_ADDR,(strlen(cmd_code)+1));

	break;
	case btn6Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));				
		flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD6_ADDR,(strlen(cmd_code)+1));
		break;
	case btn7Cmd:	
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));		
		flash_reWriteInf((u8 *)cmd_code,BUTTON_CMD7_ADDR,(strlen(cmd_code)+1));
		break;
	case func1Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));		
		flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC1_ADDR,(strlen(cmd_code)+1));
		break;
	case func2Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));		
		flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC2_ADDR,(strlen(cmd_code)+1));
		
		break;
	case func3Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));		
		flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC3_ADDR,(strlen(cmd_code)+1));
		
		break;
	case func4Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));		
		flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC4_ADDR,(strlen(cmd_code)+1));
		break;
	case func5Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));		
		flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC5_ADDR,(strlen(cmd_code)+1));
		break;

	case func6Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));				
		flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC6_ADDR,(strlen(cmd_code)+1));
		break;
	case func7Cmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));				
		flash_reWriteInf((u8 *)cmd_code,BUTTON_MOREFUNC7_ADDR,(strlen(cmd_code)+1));
		break;
	case gcodeCmd:
		memset((void *)cmd_code,0,sizeof(cmd_code));		
		memcpy((void *)cmd_code, key_value_calc.password_value, sizeof(key_value_calc.password_value));		
		strcat(cmd_code,"\n");
		pushFIFO(&gcodeCmdTxFIFO,(unsigned char *)cmd_code);
	break;	
		default :
			break;
	}
}


static void disp_KeyValue(void)
{
	switch(valueType)
	{
		
		case auto_levelCmd:
			memset(cmd_code,0,sizeof(cmd_code));			
			SPI_FLASH_BufferRead((u8*)cmd_code,BUTTON_AUTOLEVELING_ADDR,201);
			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);	
		break;
//		case wifi_name:
//			memset(cmd_code,0,sizeof(cmd_code));			
//			SPI_FLASH_BufferRead((u8*)cmd_code,WIFI_NAME_ADDR,200);
//			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);		
//		break;
//		case wifi_key:
//			memset(cmd_code,0,sizeof(cmd_code));
//			SPI_FLASH_BufferRead((u8*)cmd_code,WIFI_KEYCODE_ADDR,200);
//			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);
//		break;
//		case wifi_host:
//			memset(cmd_code,0,sizeof(cmd_code));
//			strncpy(cmd_code, (char *)gCfgItems.cloud_hostUrl, 96);
//			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);			
//		break;
		case func_btn1Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_FUNCTION1_ADDR,201);
		    BUTTON_SetText(buttonPassword.btnHandle,cmd_code);		
		break;
		case btn1Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD1_ADDR,201);
		    BUTTON_SetText(buttonPassword.btnHandle,cmd_code);		
		break;
		case btn2Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD2_ADDR,201);
		    BUTTON_SetText(buttonPassword.btnHandle,cmd_code);

		break;
		case btn3Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD3_ADDR,201);
		    BUTTON_SetText(buttonPassword.btnHandle,cmd_code);

		break;
		case btn4Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD4_ADDR,201);
		    BUTTON_SetText(buttonPassword.btnHandle,cmd_code);		

		break;	
		case btn5Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD5_ADDR,201);
		    BUTTON_SetText(buttonPassword.btnHandle,cmd_code);
		break;
		case btn6Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD6_ADDR,201);
		    BUTTON_SetText(buttonPassword.btnHandle,cmd_code);

		break;
		case btn7Cmd:	
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_CMD7_ADDR,201);
		    BUTTON_SetText(buttonPassword.btnHandle,cmd_code);
		break;

		case func1Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC1_ADDR,201);
			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);
			break;
		case func2Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC2_ADDR,201);
			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);
			break;
		case func3Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC3_ADDR,201);
			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);
			break;
		case func4Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC4_ADDR,201);
			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);			
			break;
		case func5Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC5_ADDR,201);
			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);			
			break;
		case func6Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC6_ADDR,201);
			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);			
			break;
		case func7Cmd:
			memset(cmd_code,0,sizeof(cmd_code));
			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_MOREFUNC7_ADDR,201);
			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);
			break;
		case gcodeCmd:
			memset(cmd_code,0,sizeof(cmd_code));
			BUTTON_SetText(buttonPassword.btnHandle,cmd_code);
			break;
		break;
			default :
				break;
	}
}


