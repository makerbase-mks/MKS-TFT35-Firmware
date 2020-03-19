#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_pre_heat.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"
#include "text.h"
#include "mks_cfg.h"
#include "mks_tft_fifo.h"
#include "mks_tft_com.h"
#ifndef GUI_FLASH
#define GUI_FLASH
#endif

GUI_HWIN hPreHeatWnd;
static TEXT_Handle textDesireTemp,textDesireValue;

extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern TFT_FIFO gcodeCmdTxFIFO;		//gcode 指令发送队列
extern TFT_FIFO gcodeCmdRxFIFO;		//gcode	指令接收队列
extern int X_ADD,X_INTERVAL;   //**图片间隔
extern uint8_t  Get_Temperature_Flg;

static BUTTON_STRUCT buttonInc, buttonDec, buttonTempType, buttondegree, buttonOff, buttonRet;

static void cbPreHeatWin(WM_MESSAGE * pMsg) {
	char  buf[50] = {0};
	
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetColor(gCfgItems.state_background_color);
			//#if defined(TFT70)
			GUI_FillRect(BTN_X_PIXEL+INTERVAL_V*2, 0, BTN_X_PIXEL *3+INTERVAL_V*3-1, BTN_Y_PIXEL-1);
			//#elif defined(TFT35)
			//GUI_FillRect(BTN_X_PIXEL+INTERVAL_V*2, 0, BTN_X_PIXEL *3+5, BTN_Y_PIXEL);
			//#endif
			break;
		case WM_TOUCH:
		 	
			break;
		case WM_TOUCH_CHILD:
			
			break;
		case WM_NOTIFY_PARENT:
			if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
			{
				if(pMsg->hWinSrc == buttonTempType.btnHandle)
				{
					if(gCfgItems.curTempType == 0)
					{
						if(gCfgItems.sprayerNum == 2)
						{
							if(gCfgItems.curSprayerChoose == 0)
							{
								gCfgItems.curSprayerChoose = 1;
							}
							else if(gCfgItems.curSprayerChoose == 1)
							{
								if(gCfgItems.custom_bed_flag == 1)
								{
									gCfgItems.curTempType = 1;
								}
								else
								{
									gCfgItems.curTempType = 0;
									gCfgItems.curSprayerChoose = 0;
								}
							}

						}
						else
						{	
							if(gCfgItems.curSprayerChoose == 0)
							{
								if(gCfgItems.custom_bed_flag == 1)
								{
									gCfgItems.curTempType = 1;
								}
								else
								{
									gCfgItems.curTempType = 0;
								}
							}
						}
					
					}
					else if(gCfgItems.curTempType == 1)
					{
						gCfgItems.curSprayerChoose = 0;
						gCfgItems.curTempType = 0;
					}

						
					disp_desire_temp();
					disp_temp_type();
					
				}					
				else if(pMsg->hWinSrc == buttonInc.btnHandle)
				{
					if(last_disp_state == PRINT_READY_UI)
					{
						if(gCfgItems.curTempType == 0)
						{
							gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose] += gCfgItems.stepHeat;
							//if((int)gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose] > MAX_SPRAYER_TEMP)
							if((int)gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose] > gCfgItems.preheat_max_desireSprayerTemp)
							{
								//gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose] = (float)MAX_SPRAYER_TEMP;
								gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose] = (float)gCfgItems.preheat_max_desireSprayerTemp;
							}
		
							if(gCfgItems.sprayerNum == 2)
							{
								sprintf(buf, "M104 T%d S%.1f\n", gCfgItems.curSprayerChoose,gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose]);
								pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);
							}
							else
							{
								SET_EXTRUD_TEM_COMMAND(buf, gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose]);
								pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);							
							}	
							//gCfgItems.desireSprayerTempBak_1[gCfgItems.curSprayerChoose] = gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose];
						}
						else
						{
							
							gCfgItems.preheat_desireBedTemp += gCfgItems.stepHeat;
							//if((int)gCfgItems.preheat_desireBedTemp > MAX_BED_TEMP)
							if((int)gCfgItems.preheat_desireBedTemp > gCfgItems.preheat_max_desireBedTemp)
							{
								//gCfgItems.preheat_desireBedTemp = (float)MAX_BED_TEMP;
								gCfgItems.preheat_desireBedTemp = (float)gCfgItems.preheat_max_desireBedTemp;
							}

							SET_BED_TEM_COMMAND(buf, gCfgItems.preheat_desireBedTemp);
							//////printf(buf);
							pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);//////printf(buf);
						}

					}
					else
					{
							if(gCfgItems.curTempType == 0)
							{
								gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose] += gCfgItems.stepHeat;
								//if((int)gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose] > MAX_SPRAYER_TEMP)
								if((int)gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose] > gCfgItems.preheat_max_desireSprayerTemp)
								{
									//gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose] = (float)MAX_SPRAYER_TEMP;
									gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose] = (float)gCfgItems.preheat_max_desireSprayerTemp;
								}

			
								if(gCfgItems.sprayerNum == 2)
								{
									sprintf(buf, "M104 T%d S%.1f\n", gCfgItems.curSprayerChoose,gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose]);
									pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);
								}
								else
								{
									SET_EXTRUD_TEM_COMMAND(buf, gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose]);
									pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf); 						
								} 
								//gCfgItems.desireSprayerTempBak_1[gCfgItems.curSprayerChoose] = gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose];
							}
							else
							{
								
								gCfgItems.desireBedTemp += gCfgItems.stepHeat;
								//if((int)gCfgItems.desireBedTemp > MAX_BED_TEMP)
								if((int)gCfgItems.desireBedTemp > gCfgItems.preheat_max_desireBedTemp)
								{
									//gCfgItems.desireBedTemp = (float)MAX_BED_TEMP;
									gCfgItems.desireBedTemp = (float)gCfgItems.preheat_max_desireBedTemp;
								}

								SET_BED_TEM_COMMAND(buf, gCfgItems.desireBedTemp);
								//////printf(buf);
								pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);//////printf(buf);
							}
						}

					disp_desire_temp();

				}
				else if(pMsg->hWinSrc == buttonDec.btnHandle)
				{
					/*if(gCfgItems.curTempType == 0)
					{
						push_cb_stack(UI_ACTION_EXTRUDER_TEMP_DOWN);
					}
					
					else
					{
						if(CfgPrinterItems.cfg_have_heated_bed == 1)
						{
							push_cb_stack(UI_ACTION_HEATED_BED_DOWN);
						}
					}*/
					if(last_disp_state == PRINT_READY_UI)
					{
						if(gCfgItems.curTempType == 0)
						{
								if((int)gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose] > gCfgItems.stepHeat + MIN_SPRAYER_TEMP)
								{
									gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose] -= gCfgItems.stepHeat;
									
								}
								else
								{
									gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose] = (float)MIN_SPRAYER_TEMP;
								}

							if(gCfgItems.sprayerNum == 2)
							{
								sprintf(buf, "M104 T%d S%.1f\n", gCfgItems.curSprayerChoose,gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose]);
								pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);
							}
							else
							{
								SET_EXTRUD_TEM_COMMAND(buf, gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose]);
								pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);							
							}
							//gCfgItems.desireSprayerTempBak_1[gCfgItems.curSprayerChoose] = gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose];
						}
						
						else
						{
						
							
							if((int)gCfgItems.preheat_desireBedTemp > gCfgItems.stepHeat + MIN_BED_TEMP)
							{
								gCfgItems.preheat_desireBedTemp -= gCfgItems.stepHeat;							
							}
							else
							{
								gCfgItems.preheat_desireBedTemp = (float)MIN_BED_TEMP;
							}
							
						
							SET_BED_TEM_COMMAND(buf, gCfgItems.preheat_desireBedTemp);
							//////printf(buf);
							pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);//////printf(buf);
						
							
						}
					}
					else
					{
						if(gCfgItems.curTempType == 0)
						{
								if((int)gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose] > gCfgItems.stepHeat + MIN_SPRAYER_TEMP)
								{
									gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose] -= gCfgItems.stepHeat;
									
								}
								else
								{
									gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose] = (float)MIN_SPRAYER_TEMP;
								}

							if(gCfgItems.sprayerNum == 2)
							{
								sprintf(buf, "M104 T%d S%.1f\n", gCfgItems.curSprayerChoose,gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose]);
								pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);
							}
							else
							{
								SET_EXTRUD_TEM_COMMAND(buf, gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose]);
								pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);							
							}
							//gCfgItems.desireSprayerTempBak_1[gCfgItems.curSprayerChoose] = gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose];
						}
						
						else
						{
							if((int)gCfgItems.desireBedTemp > gCfgItems.stepHeat + MIN_BED_TEMP)
							{
								gCfgItems.desireBedTemp -= gCfgItems.stepHeat;							
							}
							else
							{
								gCfgItems.desireBedTemp = (float)MIN_BED_TEMP;
							}
							
							SET_BED_TEM_COMMAND(buf, gCfgItems.desireBedTemp);
							//////printf(buf);
							pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);//////printf(buf);
						}
					}						
					disp_desire_temp();
					
													
				}
				
				else if(pMsg->hWinSrc == buttondegree.btnHandle)
				{
					switch(gCfgItems.stepHeat)
					{
						case 1:
							gCfgItems.stepHeat = 5;
							break;

						case 5:
							gCfgItems.stepHeat = 10;
							break;
							
						case 10:
							gCfgItems.stepHeat = 1;
							break;

						default:
							break;
					}
					disp_step_heat();
				}
				else if(pMsg->hWinSrc == buttonOff.btnHandle)
				{
					/*if(gCfgItems.curTempType == 0)
					{
						gCfgItems.preheat_desireSprayerTemp[Extruder::current->id] = 0;												
						if (CfgPrinterItems.cfg_num_extruder == 2)
						{
							if(Extruder::current->id == 0)
							{
								push_cb_stack(UI_ACTION_EXTRUDER0_OFF);
							}
							else if(Extruder::current->id == 1)
							{
								push_cb_stack(UI_ACTION_EXTRUDER1_OFF);
							}
							gCfgItems.preheat_desireSprayerTemp[Extruder::current->id] = 0;
						}
						else
						{
							push_cb_stack(UI_ACTION_EXTRUDER0_OFF);
							gCfgItems.preheat_desireSprayerTemp[0] = 0;
						}	

					}
					else
					{
						push_cb_stack(UI_ACTION_HEATED_BED_OFF);
						gCfgItems.preheat_desireBedTemp = 0;
	
					}
										
					disp_desire_temp();*/
					if(last_disp_state == PRINT_READY_UI)
					{
						if(gCfgItems.curTempType == 0)
						{

							gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose] = 0;
							if(gCfgItems.sprayerNum == 2)
							{
								sprintf(buf, "M104 T%d S%.1f\n", gCfgItems.curSprayerChoose,gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose]);
								pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);							
							}
							else
							{
								SET_EXTRUD_TEM_COMMAND(buf, gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose]);
								pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);
							}
							//gCfgItems.desireSprayerTempBak_1[gCfgItems.curSprayerChoose] = gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose];
						}
						else
						{
							
							gCfgItems.preheat_desireBedTemp = 0;
							
							SET_BED_TEM_COMMAND(buf, gCfgItems.preheat_desireBedTemp);
							//////printf(buf);
							pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);//////printf(buf);
						}
					}	
					else
					{
						if(gCfgItems.curTempType == 0)
						{

							gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose] = 0;
							if(gCfgItems.sprayerNum == 2)
							{
								sprintf(buf, "M104 T%d S%.1f\n", gCfgItems.curSprayerChoose,gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose]);
								pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);							
							}
							else
							{
								SET_EXTRUD_TEM_COMMAND(buf, gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose]);
								pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);
							}	
							//gCfgItems.desireSprayerTempBak_1[gCfgItems.curSprayerChoose] = gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose];
						}
						else
						{
							
							gCfgItems.desireBedTemp = 0;
							
							SET_BED_TEM_COMMAND(buf, gCfgItems.desireBedTemp);
							//////printf(buf);
							pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);//////printf(buf);
						}
					}
					disp_desire_temp();
				}
				
				else  if(pMsg->hWinSrc == buttonRet.btnHandle)
				{		
					//if((last_disp_state != PAUSE_UI)&&(last_disp_state != OPERATE_UI))
					if((printerStaus!= pr_pause)&&(last_disp_state != OPERATE_UI))
					{
						Get_Temperature_Flg = 0;
					}					
					Clear_preHeat();
					//sean 2019.1.3
					#if 0
					if((gCfgItems.sprayerNum == 2)&&(printerStaus != pr_idle))
					{
						gCfgItems.curSprayerChoose = gCfgItems.curSprayerChoose_bak;
						sprintf(buf,"T%d\n",gCfgItems.curSprayerChoose);
						pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);
					}
					#endif
					draw_return_ui();
					
				}
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
	}


void draw_preHeat()
{
	
	int i;
	
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != PRE_HEAT_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = PRE_HEAT_UI;
	}
	disp_state = PRE_HEAT_UI;

	
	
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();

	GUI_DispStringAt(creat_title_text(),  TITLE_XPOS, TITLE_YPOS);	
	
	
	hPreHeatWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbPreHeatWin, 0);
	buttonInc.btnHandle = BUTTON_CreateEx(INTERVAL_V, 0,BTN_X_PIXEL, BTN_Y_PIXEL, hPreHeatWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonDec.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  0,BTN_X_PIXEL, BTN_Y_PIXEL, hPreHeatWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	
	buttonTempType.btnHandle = BUTTON_CreateEx(INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hPreHeatWnd, BUTTON_CF_SHOW, 0, 303);
	buttondegree.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hPreHeatWnd, BUTTON_CF_SHOW, 0, 304);
	buttonOff.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hPreHeatWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	buttonRet.btnHandle = BUTTON_CreateEx(BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H,BTN_X_PIXEL, BTN_Y_PIXEL, hPreHeatWnd, BUTTON_CF_SHOW, 0, 306);

	#if VERSION_WITH_PIC	
	BUTTON_SetBmpFileName(buttonInc.btnHandle, "bmp_Add.bin",1);
	BUTTON_SetBmpFileName(buttonDec.btnHandle, "bmp_Dec.bin",1);
	
	BUTTON_SetBmpFileName(buttonOff.btnHandle, "bmp_speed0.bin",1);
	BUTTON_SetBmpFileName(buttonRet.btnHandle, "bmp_return.bin",1);

	BUTTON_SetBitmapEx(buttonInc.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonDec.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttondegree.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonOff.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);
	BUTTON_SetBitmapEx(buttonRet.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);

	BUTTON_SetBkColor(buttonInc.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonInc.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color	);
	BUTTON_SetTextColor(buttonInc.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonInc.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	
	BUTTON_SetBkColor(buttonDec.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_color);
	BUTTON_SetBkColor(buttonDec.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_color);
	BUTTON_SetTextColor(buttonDec.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_textcolor);
	BUTTON_SetTextColor(buttonDec.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_textcolor);

	BUTTON_SetBkColor(buttonTempType.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(buttonTempType.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetTextColor(buttonTempType.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
	BUTTON_SetTextColor(buttonTempType.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);

	BUTTON_SetBkColor(buttondegree.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(buttondegree.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetTextColor(buttondegree.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
	BUTTON_SetTextColor(buttondegree.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);

	BUTTON_SetBkColor(buttonOff.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(buttonOff.btnHandle,BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetTextColor(buttonOff.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
	BUTTON_SetTextColor(buttonOff.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);

	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
	BUTTON_SetBkColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
	BUTTON_SetTextColor(buttonRet.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor);



	if(gCfgItems.multiple_language != 0)
	{
		BUTTON_SetText(buttonInc.btnHandle, preheat_menu.add);
		BUTTON_SetText(buttonDec.btnHandle, preheat_menu.dec);
		BUTTON_SetText(buttonOff.btnHandle, preheat_menu.off);
		BUTTON_SetText(buttonRet.btnHandle, common_menu.text_back);
	}

	#endif
	
	textDesireTemp = TEXT_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,(BTN_Y_PIXEL-60)/2,BTN_X_PIXEL*2+INTERVAL_V,30, hPreHeatWnd, WM_CF_SHOW, TEXT_CF_HCENTER,	GUI_ID_TEXT1, "Extruder1");
	textDesireValue = TEXT_CreateEx(BTN_X_PIXEL+INTERVAL_V*2,(BTN_Y_PIXEL-60)/2+30, BTN_X_PIXEL*2+INTERVAL_V,30, hPreHeatWnd, WM_CF_SHOW, TEXT_CF_HCENTER,	GUI_ID_TEXT1, "0/0");

	TEXT_SetBkColor(textDesireTemp,gCfgItems.state_background_color);
	TEXT_SetBkColor(textDesireValue,gCfgItems.state_background_color); 
	TEXT_SetTextColor(textDesireTemp,gCfgItems.state_text_color);
	TEXT_SetTextColor(textDesireValue,gCfgItems.state_text_color);

	disp_desire_temp();

	disp_temp_type();

	disp_step_heat();
	
	//GUI_Exec();


	
}

void Clear_preHeat()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hPreHeatWnd))
	{
		WM_DeleteWindow(hPreHeatWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}


void disp_step_heat()
{
	BUTTON_SetBkColor(buttondegree.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(buttondegree.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetTextColor(buttondegree.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
	BUTTON_SetTextColor(buttondegree.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);

	if(gCfgItems.stepHeat == 1)
		BUTTON_SetBmpFileName(buttondegree.btnHandle, "bmp_step1_degree.bin",1);
	else if(gCfgItems.stepHeat == 5)
		BUTTON_SetBmpFileName(buttondegree.btnHandle, "bmp_step5_degree.bin",1);
	else if(gCfgItems.stepHeat == 10)
		BUTTON_SetBmpFileName(buttondegree.btnHandle, "bmp_step10_degree.bin",1);

	if(gCfgItems.multiple_language != 0)
	{
		if(gCfgItems.stepHeat == 1)
			BUTTON_SetText(buttondegree.btnHandle,preheat_menu.step_1c);	
		else if(gCfgItems.stepHeat == 5)
			BUTTON_SetText(buttondegree.btnHandle,preheat_menu.step_5c);
		else if(gCfgItems.stepHeat == 10)
			BUTTON_SetText(buttondegree.btnHandle,preheat_menu.step_10c);	

	}	
}

void disp_desire_temp()
{
	char buf[20] = {0};
	char buf1[20] = {0};
	
	TEXT_SetBkColor(textDesireTemp,gCfgItems.state_background_color);
	TEXT_SetBkColor(textDesireValue,gCfgItems.state_background_color); 
	TEXT_SetTextColor(textDesireTemp,gCfgItems.state_text_color);
	TEXT_SetTextColor(textDesireValue,gCfgItems.state_text_color);
	

	if(gCfgItems.curTempType == 0)
	{
		if(gCfgItems.curSprayerChoose<1)
		{
			sprintf(buf1,preheat_menu.ext1);
		}
		else
		{
			sprintf(buf1,preheat_menu.ext2);
		}
		memset(buf,' ',(sizeof(buf)-1));
		TEXT_SetText(textDesireValue, buf);
		if(last_disp_state == PRINT_READY_UI)//预热界面为默认值
		{
			sprintf(buf, preheat_menu.value_state,(int)gCfgItems.curSprayerTemp[gCfgItems.curSprayerChoose],  (int)gCfgItems.preheat_desireSprayerTemp[gCfgItems.curSprayerChoose]);

		}
		else
		{		
			sprintf(buf, preheat_menu.value_state, (int)gCfgItems.curSprayerTemp[gCfgItems.curSprayerChoose],  (int)gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose]);
		}
	}
	else
	{
		sprintf(buf1,preheat_menu.hotbed);
		memset(buf,' ',sizeof(buf)-1);
		TEXT_SetText(textDesireValue, buf);
		if(last_disp_state == PRINT_READY_UI)
		{			
			sprintf(buf, preheat_menu.value_state, (int)gCfgItems.curBedTemp,  (int)gCfgItems.preheat_desireBedTemp);
		}
		else
		{
			sprintf(buf, preheat_menu.value_state, (int)gCfgItems.curBedTemp,  (int)gCfgItems.desireBedTemp);
		}
	}
	TEXT_SetText(textDesireTemp, buf1);
	TEXT_SetText(textDesireValue, buf);
}

void disp_temp_type()
{
	BUTTON_SetBkColor(buttonTempType.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_color);
	BUTTON_SetBkColor(buttonTempType.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_color);
	BUTTON_SetTextColor(buttonTempType.btnHandle, BUTTON_CI_PRESSED, gCfgItems.btn_state_textcolor);
	BUTTON_SetTextColor(buttonTempType.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.btn_state_textcolor);

	if(gCfgItems.curTempType == 0)
	{		
		if(gCfgItems.curSprayerChoose == 1)
		{			
			BUTTON_SetBmpFileName(buttonTempType.btnHandle, "bmp_extru2.bin",1);
			if(gCfgItems.multiple_language != 0)
				BUTTON_SetText(buttonTempType.btnHandle, preheat_menu.ext2);		
		}
		else
		{
			BUTTON_SetBmpFileName(buttonTempType.btnHandle, "bmp_extru1.bin",1);
			if(gCfgItems.multiple_language != 0)
				BUTTON_SetText(buttonTempType.btnHandle, preheat_menu.ext1);
		}	
	}
	else
	{	
		BUTTON_SetBmpFileName(buttonTempType.btnHandle, "bmp_bed.bin",1);
		if(gCfgItems.multiple_language != 0)
			BUTTON_SetText(buttonTempType.btnHandle, preheat_menu.hotbed);
	}
	BUTTON_SetBitmapEx(buttonTempType.btnHandle, 0, &bmp_struct, BMP_PIC_X, BMP_PIC_Y);

}

