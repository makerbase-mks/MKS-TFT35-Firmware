#include "stdint.h"
#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_dialog.h"
#include "draw_ui.h"
#include "draw_printing.h"
#include "draw_ready_print.h"
#include "draw_pause_ui.h"
//#include "sdio_sdcard.h"
#include "sdio.h"       //skyblue 2016-12-13
#include "mks_tft_com.h"
#include "Ff.h"
#include "mks_cfg.h"
#include "usb_host.h"
#include "at24cxx.h"
#include "sd_usr.h"

#include "draw_bind.h"
#include "mks_cfg.h"
#include "ff_gen_drv.h"
#include "fatfs.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif
//extern GUI_CONST_STORAGE GUI_FONT GUI_FontFont24_MS;
extern void mks_clearFile();

extern uint8_t preview_no_display;

extern unsigned char codebuff[100];
extern char cmd_code[201];

extern FIL fp_reprint_rw;

extern unsigned char path_bak[15];
extern unsigned char *path_reprint;





extern uint8_t  mksPrinterStatusFlag;

static GUI_HWIN hStopDlgWnd;

extern int8_t curFilePath[30];

uint32_t rePrintOffset;

extern volatile int16_t logo_time;

extern GUI_FLASH const GUI_FONT GUI_FontHZ_fontHz18;
extern int X_ADD,X_INTERVAL;   //**Õº∆¨º‰∏Ù

extern uint8_t  Get_Temperature_Flg;
extern PR_STATUS printerStaus;
extern volatile unsigned char BeeperCnt;
extern volatile unsigned long BeeperFreq;
extern volatile uint8_t get_temp_flag;
extern unsigned char SendOneTime;
int8_t  gCurDir[100];
extern FILE_PRINT_STATE gCurFileState ;
extern uint8_t Chk_close_machine_flg;
extern unsigned char breakpoint_homeFlag;

static TEXT_Handle printStopDlgText,filament_temper,printfilename;

static BUTTON_STRUCT buttonOk, buttonCancle;

static PROGBAR_Handle FilamentBar;
uint32_t filament_rate;

static uint8_t DialogType;
extern uint8_t print_start_flg;
extern uint8_t flash_preview_begin;
extern uint8_t from_flash_pic;
extern uint8_t default_preview_flg;

extern uint8_t pause_flag;

extern uint8_t filament_loading_time_flg;
extern uint32_t filament_loading_time_cnt;
extern uint8_t filament_loading_completed;
extern uint8_t filament_load_heat_flg;
extern uint8_t filament_unload_heat_flg;
extern uint8_t filament_unloading_time_flg;
extern uint32_t filament_unloading_time_cnt;
extern uint8_t filament_unloading_completed;

extern uint8_t temp_update_flag;

extern uint8_t disp_in_file_dir;

extern int upload_result ;

extern uint32_t upload_time ;
extern uint32_t upload_size;

extern FATFS fs;

static void cbDlgWin(WM_MESSAGE * pMsg)
{
	int8_t sel_item;
	uint32_t i;
	//int8_t sel_file[30];
	uint8_t i2c_cnt =  0;
	volatile uint8_t tmp = 0xff;
	char buf[30] = {0};
	uint8_t BakfilePathLen;
	char BakFileName[100] = {0};

	//struct PressEvt *press_event;
	switch (pMsg->MsgId) {
	case WM_PAINT:
		//GUI_SetBkColor(GUI_DARKBLUE);
		//GUI_Clear();
		break;

	case WM_TOUCH:		
		break;
		
	case WM_TOUCH_CHILD:
	 	break;

	case WM_NOTIFY_PARENT:
		if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
		{
			if(pMsg->hWinSrc == buttonOk.btnHandle)
			{			
				Clear_dialog();
				//hAlertWin = GUI_CreateDialogBox(aDialogAlert, GUI_COUNTOF(aDialogAlert), _cbAlert, 0, 0, 0);
				if(DialogType == DIALOG_TYPE_STOP)				
				{

					Get_Temperature_Flg = 0;
					memset((char *)gCfgItems.z_display_pos,0,sizeof(gCfgItems.z_display_pos));	
					breakpoint_homeFlag=0;
					gCfgItems.pwd_reprint_flg = 0;
					
					if(printerStaus == pr_reprint)
					{
						//rePrintProcess();
						//«Â≥˛E2PROM ˝æ›
						for(i2c_cnt=0;i2c_cnt<(256-BAK_REPRINT_S);i2c_cnt++)
						{
							HAL::AT24CXX_Write(BAK_REPRINT_S+i2c_cnt,(uint8_t *)&tmp,1);
						}
					}
					
					printerStaus = pr_stop;
					stop_print_time();
					f_close(srcfp);

					#ifdef SAVE_FROM_SD					
					//…æ≥˝–¯¥Ú ˝æ›Œƒº˛°£
					if(gCfgItems.pwroff_save_mode == 0)
						mks_clearFile();
					/*
					if(gCfgItems.pwroff_save_mode == 0)
					{
						if(gCfgItems.fileSysType == FILE_SYS_SD)
						{
							strcpy((char *)path_bak, "1:");
							strcat((char *)path_bak,(const char *)path_reprint);						
							f_unlink((const char *)path_bak);
						}
						else
						{
							strcpy((char *)path_bak, "0:");
							strcat((char *)path_bak,(const char *)path_reprint);						
							f_unlink((const char *)path_bak);
						}

					}*/
					#endif
					
					SPEAKER = 0;
					mksBpAlrmEn=0;
					BeeperCnt=0;
					BeeperFreq = 0;

					reset_file_info();
					//**reset_tx_fifo();
					draw_ready_print();
				}
				else if(DialogType == DIALOG_TYPE_PRINT_FILE)
				{
					//20150917
					//**I2C_EE_Init(400000);
					MX_I2C1_Init(400000);
					//µ⁄∂˛¥Œ≥ı ºªØ£¨±£÷§I2Cƒ‹Ã·ÀŸ°£
					//**I2C_EE_Init(400000);
					MX_I2C1_Init(400000);
					
					gCfgItems.desireSprayerTemp[0] = 0;
					gCfgItems.desireSprayerTemp[1] = 0;
					gCfgItems.desireBedTemp = 0;	
					if(strlen(curFileName)>150)
					{
						draw_dialog(DIALOG_TYPE_MESSEGE_ERR1);
					}
					else
					{
						#if 0 //sean 12.17
						gCfgItems.printSpeed=100;
						gCfgItems.printExtSpeed0=100;
						memset(usart2Data.usart2Txbuf,0,sizeof(usart2Data.usart2Txbuf));	
						strcpy((char *)usart2Data.usart2Txbuf,"M220 S100\n");
						usart2TxStart();
						HAL_Delay(5);
						memset(usart2Data.usart2Txbuf,0,sizeof(usart2Data.usart2Txbuf));
						strcpy((char *)usart2Data.usart2Txbuf,"M221 S100\n");
						usart2TxStart();
						#endif
						
						Get_Temperature_Flg = 1;
						get_temp_flag = 1;
						SendOneTime = 1;
						reset_print_time();
						start_print_time();
						
						//draw_dialog(DIALOG_TYPE_FILE_LOADING);
						//save_preview_to_flash(curFileName,3,40);
						//print_start_flg = 0;
						preview_no_display = 0;
						if(gCfgItems.pwd_reprint_flg == 1)
						{
							HAL::AT24CXX_Read(BAK_PREVIEW_FROM_FLASH_ADDR, &from_flash_pic,1);

							if(from_flash_pic != 0)
							{
								flash_preview_begin = 1;
							}
							else
							{
								default_preview_flg = 1;
							}							
						}
						else
						{
							preview_gcode_prehandle(curFileName);
						}
						draw_printing();
					}
					if(gCfgItems.pwd_reprint_flg == 1)
					{
						usart2Data.printer = printer_waiting;
						usart2Data.prWaitStatus == pr_wait_idle;
						printerStaus = breakpoint_reprint;
					}

				}
				else if(DialogType == DIALOG_TYPE_REPRINT_NO_FILE)
				{
					int8_t res;
					static FIL curFile;

					memset(gCurDir, 0, sizeof(gCurDir));

					if(gCfgItems.fileSysType == FILE_SYS_SD)
					//if (SD_DET_IP == SDCARDDETECTINVERTED)
					{
						strcpy((char  *)gCurDir, "1:");
						//curFileName[0]=(char )'1';
						//**SD_Initialize();
						//**ShowSDFiles();
						MX_SDIO_SD_Init();
						if (SD_DET_IP == SDCARDDETECTINVERTED)
						{
	            			FATFS_LinkDriver_sd(&SD_Driver, SD_Path);
							f_mount(&fs, (TCHAR const*)SD_Path, 0);	
						}
						sd.ShowSDFiles();
					}
					else
					{
						FATFS_LinkDriver_usb(&USBH_Driver, USBH_Path);
		       			f_mount(&fs, (TCHAR const*)USBH_Path, 0);	
						strcpy((char *)gCurDir, "0:");
						//curFileName[0]=(char )'0';
						i=150000;
						while(i--)
						{
							MX_USB_HOST_Process();
						}
					}
					
					logo_time = 3000 / TICK_CYCLE;;

					res = f_open(&curFile, curFileName, FA_OPEN_EXISTING | FA_READ);
					if(res == FR_OK)
					{
						HAL::AT24CXX_Read(BAK_PREVIEW_FROM_FLASH_ADDR, &from_flash_pic,1);
						preview_no_display = 0;

						if(from_flash_pic != 0)
						{
							flash_preview_begin = 1;
						}
						else
						{
							default_preview_flg = 1;
						}
						srcfp = &curFile;
						gCurFileState.file_open_flag = 0xaa;
						if(from_flash_pic != 1)
							gCurFileState.totalSend = (unsigned char)((float)rePrintOffset  * 100 / f_size(&curFile));
						else
							gCurFileState.totalSend = (unsigned char)(((float)rePrintOffset -(PREVIEW_SIZE+To_pre_view)) * 100 / (f_size(&curFile)-(PREVIEW_SIZE+To_pre_view)));

						//if((RE_PRINT_STATUS)gCfgItems.rePrintFlag == printer_pause_reprint)
						{
							//20150710
							//printerStaus = pr_pause;
							printerStaus = pr_reprint;
							disp_state_stack._disp_index = 0;
							memset(disp_state_stack._disp_state, 0, sizeof(disp_state_stack._disp_state));
							disp_state_stack._disp_state[disp_state_stack._disp_index] = PRINTING_UI;
							draw_printing();
							
						}
					/*	else if((RE_PRINT_STATUS)gCfgItems.rePrintFlag == printer_pwdwn_reprint)
						{
							printerStaus = pr_working;
							start_print_time();
							draw_printing();
						}*/
						
						logo_time = 3000 / TICK_CYCLE;
					}
					else
					{
						disp_state_stack._disp_index = 0;
						memset(disp_state_stack._disp_state, 0, sizeof(disp_state_stack._disp_state));
						disp_state_stack._disp_state[disp_state_stack._disp_index] = PRINT_READY_UI;
						draw_dialog(DIALOG_TYPE_REPRINT_NO_FILE);
						
					}
					
				}
				else if(DialogType == DIALOG_TYPE_UNBIND)
				{
					cloud_unbind();
					draw_return_ui();
				}
				else if(DialogType == DIALOG_TYPE_M80_FAIL)
				{
					Clear_dialog();
					draw_ready_print();
				}
				else if(DialogType == DIALOG_TYPE_MESSEGE_ERR1)
				{
					Clear_dialog();
					draw_ready_print();
				}
				else if(DialogType == DIALOG_TYPE_FILAMENT_HEAT_LOAD_COMPLETED)
				{
					Clear_dialog();
					draw_dialog(DIALOG_TYPE_FILAMENT_LOADING);
					
					filament_loading_time_flg = 1;
					filament_loading_time_cnt = 0;

					pushFIFO(&gcodeCmdTxFIFO, (uint8_t *)RELATIVE_COORD_COMMAN);
					if(gCfgItems.sprayerNum == 2)
					{
						memset(buf,0,sizeof(buf));
						sprintf(buf,"T%d\n",gCfgItems.curSprayerChoose);
						pushFIFO(&gcodeCmdTxFIFO, (uint8_t *)buf);				
					}					
					memset(buf,0,sizeof(buf));
					sprintf(buf,"G1 E%d F%d\n",gCfgItems.filament_load_length,gCfgItems.filament_load_speed);
					pushFIFO(&gcodeCmdTxFIFO,(uint8_t *)buf);
					pushFIFO(&gcodeCmdTxFIFO, (uint8_t *)ABSOLUTE_COORD_COMMAN);					

				}
				else if(DialogType == DIALOG_TYPE_FILAMENT_HEAT_UNLOAD_COMPLETED)
				{
					//filament_heat_completed_unload = 1;
					Clear_dialog();
					draw_dialog(DIALOG_TYPE_FILAMENT_UNLOADING);
					filament_unloading_time_flg = 1;
					filament_unloading_time_cnt = 0;	

					//initFIFO(&gcodeCmdTxFIFO);
					pushFIFO(&gcodeCmdTxFIFO, (uint8_t *)RELATIVE_COORD_COMMAN);
					if(gCfgItems.sprayerNum == 2)
					{
							memset(buf,0,sizeof(buf));
							sprintf(buf,"T%d\n",gCfgItems.curSprayerChoose);
							pushFIFO(&gcodeCmdTxFIFO, (uint8_t *)buf);				
					}
					memset(buf,0,sizeof(buf));
					sprintf(buf,"G1 E-%d F%d\n",gCfgItems.filament_unload_length,gCfgItems.filament_unload_speed);
					pushFIFO(&gcodeCmdTxFIFO,(uint8_t *)buf);
					pushFIFO(&gcodeCmdTxFIFO, (uint8_t *)ABSOLUTE_COORD_COMMAN);						
				}								
				else
				{
					if(DialogType == DIALOG_TYPE_MAINBOAR_ERROR)
					{
						if(from_flash_pic==1)
						flash_preview_begin = 1;
						else
						default_preview_flg = 1;
					}
					draw_return_ui();
				}
			}
			else if(pMsg->hWinSrc == buttonCancle.btnHandle)
			{			
				unsigned int tmpFlag;
				
				Chk_close_machine_flg = 0;//»°œ˚÷Æ∫Û‘Ú∂‘¥ÚÕÍπÿª˙±Í÷æ«Â¡„£¨∑¿÷π≥ˆ¥Ì°£
				if((DialogType == DIALOG_TYPE_STOP))
				{
					if(from_flash_pic == 1)
						flash_preview_begin = 1;
					else
						default_preview_flg = 1;
				}
				
				if(DialogType == DIALOG_TYPE_PRINT_FILE)
				{
					disp_in_file_dir = 1;
				}

				Clear_dialog();
				draw_return_ui();

				if(DialogType == DIALOG_TYPE_REPRINT_NO_FILE)
				{	
					//draw_main_ui();	
					//logo_time = 0;
					HAL::AT24CXX_Read(BAK_REPRINT_INFO, (uint8_t *)&tmpFlag,  4);
					tmpFlag &= ~(0xff << 24);
					tmpFlag |= printer_normal << 24;
					HAL::AT24CXX_Write(BAK_REPRINT_INFO, (uint8_t *)&tmpFlag,  4); 		// –¯¥Ú±Í÷æ(uint8_t) | checkXor(uint8_t) | checkSum(uint16_t)
						
				}
			}
		}
	}
}

void draw_dialog(uint8_t type)
{
		
	int8_t buf[100] = {0};
	
	int i;
	
#if 1
	if((DialogType == DIALOG_TYPE_MAINBOAR_ERROR)
		&& (type == DIALOG_TYPE_MAINBOAR_ERROR)
		&&(disp_state == DIALOG_UI) )
		{
			return;
		}
#endif

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != DIALOG_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = DIALOG_UI;
	}
	
	disp_state = DIALOG_UI;
	buttonOk.btnHandle = 0;
	buttonCancle.btnHandle = 0;

	DialogType = type;
		
	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
	#if 0
	//GUI_SetFont(&FONT_TITLE);
	if(gCfgItems.language == LANG_COMPLEX_CHINESE)
	{
		GUI_SetFont(&GUI_FontHZ16);
	}
	else if(gCfgItems.language == LANG_SIMPLE_CHINESE)
	{
		GUI_SetFont(&FONT_TITLE);
	}
	else
	{
		GUI_SetFont(&GUI_FontHZ_fontHz18);
	}

	#endif
	//sprintf(buf, "’˝‘⁄¥Ú”°->≤Ÿ◊˜:%s", curFilePath);
	//GUI_DispStringAt(buf, 0, 0);

	//GUI_DispStringAt(creat_title_text(),  TITLE_XPOS, TITLE_YPOS);

		if(disp_state_stack._disp_index > 1)
			GUI_DispStringAt(creat_title_text(), TITLE_XPOS, TITLE_YPOS);
		
		if(DialogType == DIALOG_TYPE_UPDATE_ESP_FIRMARE) //Êõ¥Êñ∞espÂõ∫‰ª∂
		{
			GUI_DispStringAt(DIALOG_UPDATE_WIFI_FIRMWARE_EN, 40, 120);
		}
		else if(DialogType == DIALOG_TYPE_UPDATE_ESP_DATA) //Êõ¥Êñ∞espÊï∞ÊçÆ
		{
			GUI_DispStringAt(DIALOG_UPDATE_WIFI_WEB_EN, 40, 100);
		}
		else if(DialogType == DIALOG_TYPE_UPLOAD_FILE)// esp ‰∏ä‰º†Êñá‰ª∂
		{
			hStopDlgWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbDlgWin, 0);
			printStopDlgText = TEXT_CreateEx(0,(imgHeight-40)/2-140, LCD_WIDTH, 120, hStopDlgWnd, WM_CF_SHOW, TEXT_CF_LEFT,  alloc_win_id(), "Uploading......");
			TEXT_SetBkColor(printStopDlgText, gCfgItems.background_color);
			TEXT_SetTextColor(printStopDlgText, gCfgItems.title_color);
			TEXT_SetTextAlign(printStopDlgText, GUI_TA_VCENTER | GUI_TA_HCENTER);				
			if(upload_result == 1)
			{
				TEXT_SetText(printStopDlgText, DIALOG_UPLOAD_ING_EN);
			}
			else if(upload_result == 2)
			{
				buttonOk.btnHandle = BUTTON_CreateEx((LCD_WIDTH-140)/2,(imgHeight-40)/2, 140, 50,hStopDlgWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
				TEXT_SetText(printStopDlgText, DIALOG_UPLOAD_ERROR_EN);
				BUTTON_SetText(buttonOk.btnHandle, DIALOG_CONFIRM_EN);
			}
			else if(upload_result == 3)
			{
				char buf[200];
				int _index = 0;
				
				memset(buf,0,sizeof(200));
				
				buttonOk.btnHandle= BUTTON_CreateEx((LCD_WIDTH-140)/2,(imgHeight-40)/2, 140, 50,hStopDlgWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
				
				strcpy(buf, DIALOG_UPLOAD_FINISH_EN);
				_index = strlen(buf);
				buf[_index] = '\n';
				_index++;
				strcat(buf, DIALOG_UPLOAD_SIZE_EN);
				
				_index = strlen(buf);
				buf[_index] = ':';
				_index++;
				sprintf(&buf[_index], " %.1d KBytes\n", upload_size / 1024);

				strcat(buf, DIALOG_UPLOAD_TIME_EN);
				_index = strlen(buf);
				buf[_index] = ':';
				_index++;
				sprintf(&buf[_index], " %d s\n", upload_time);
				
				strcat(buf, DIALOG_UPLOAD_SPEED_EN);
				_index = strlen(buf);
				buf[_index] = ':';
				_index++;
				sprintf(&buf[_index], " %d KBytes/s\n", upload_size / upload_time / 1024);				
				
				TEXT_SetText(printStopDlgText, buf);
				BUTTON_SetText(buttonOk.btnHandle, "OK");
			
			}

			
		}
#if 1
		else if(DialogType == DIALOG_TYPE_MAINBOAR_ERROR)
		{
			hStopDlgWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbDlgWin, 0);
			printStopDlgText = TEXT_CreateEx(0,0, LCD_WIDTH, 90, hStopDlgWnd, WM_CF_SHOW, TEXT_CF_LEFT, alloc_win_id(), " ");
			TEXT_SetTextColor(printStopDlgText, gCfgItems.title_color);
			TEXT_SetTextAlign(printStopDlgText, GUI_TA_VCENTER | GUI_TA_HCENTER);		
			
			buttonOk.btnHandle = BUTTON_CreateEx((LCD_WIDTH-140)/2, (imgHeight-40)/2, 140, 50,hStopDlgWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
			if(strlen(cmd_code)>40)
			{
				memset((char*)codebuff,'\0',sizeof(codebuff));
				strncpy((char*)codebuff,cmd_code,40);
				codebuff[40]='\n';
				strcat((char*)codebuff,&cmd_code[40]);
				TEXT_SetText(printStopDlgText, (char*)codebuff);	
			}
			else
			{
				//chen 11.7
				memset((char*)codebuff,'\0',sizeof(codebuff));
				strncpy((char*)codebuff,cmd_code,40);
				
				TEXT_SetText(printStopDlgText, (char*)codebuff);
			}		
			//TEXT_SetText(printStopDlgText, cmd_code);
			BUTTON_SetText(buttonOk.btnHandle, print_file_dialog_menu.confirm);
		}
#endif
		else		
		{
			hStopDlgWnd = WM_CreateWindow(0, titleHeight, LCD_WIDTH, imgHeight, WM_CF_SHOW, cbDlgWin, 0);
			printStopDlgText = TEXT_CreateEx(0,(imgHeight-40)/2-90, LCD_WIDTH, 70, hStopDlgWnd, WM_CF_SHOW, GUI_TA_VCENTER | GUI_TA_HCENTER,	alloc_win_id(), " ");

			TEXT_SetBkColor(printStopDlgText, gCfgItems.state_background_color);
			TEXT_SetTextColor(printStopDlgText, gCfgItems.state_text_color);
			
			if((DialogType == DIALOG_TYPE_M80_FAIL)
				||(DialogType == DIALOG_TYPE_FILAMENT_LOAD_COMPLETED)
				||(DialogType == DIALOG_TYPE_FILAMENT_UNLOAD_COMPLETED))
			{
				buttonOk.btnHandle= BUTTON_CreateEx((LCD_WIDTH-140)/2,(imgHeight-40)/2, 140, 50,hStopDlgWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
			}
			else if(DialogType == DIALOG_TYPE_FILAMENT_LOAD_HEAT)
			{
				buttonCancle.btnHandle= BUTTON_CreateEx((LCD_WIDTH-140)/2,(imgHeight-40)/2,140, 50,hStopDlgWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
				filament_temper = TEXT_CreateEx(0,(imgHeight-40)/2-30, LCD_WIDTH, 30, hStopDlgWnd, WM_CF_SHOW, GUI_TA_TOP | GUI_TA_HCENTER,  alloc_win_id(), " ");
				TEXT_SetTextColor(filament_temper, gCfgItems.state_text_color);
				TEXT_SetBkColor(filament_temper, gCfgItems.state_background_color);
			}
			else if(DialogType == DIALOG_TYPE_FILAMENT_UNLOAD_HEAT)
			{
				buttonCancle.btnHandle= BUTTON_CreateEx((LCD_WIDTH-140)/2,(imgHeight-40)/2,140, 50,hStopDlgWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
				filament_temper = TEXT_CreateEx(0,(imgHeight-40)/2-30, LCD_WIDTH, 30, hStopDlgWnd, WM_CF_SHOW, GUI_TA_TOP | GUI_TA_HCENTER,  alloc_win_id(), " ");
				TEXT_SetTextColor(filament_temper, gCfgItems.state_text_color);
				TEXT_SetBkColor(filament_temper, gCfgItems.state_background_color);
			}
			else if((DialogType == DIALOG_TYPE_FILAMENT_LOADING)||(DialogType == DIALOG_TYPE_FILAMENT_UNLOADING))
			{
				FilamentBar = PROGBAR_CreateEx((LCD_WIDTH-400)/2, (imgHeight-40)/2-30, 400, 25, hStopDlgWnd, WM_CF_SHOW, 0, 0);
				PROGBAR_SetBarColor(FilamentBar, 0, GUI_GREEN);
				PROGBAR_SetValue(FilamentBar,filament_rate);
				PROGBAR_SetText(FilamentBar," ");
			}				
			else
			{
				buttonOk.btnHandle= BUTTON_CreateEx((LCD_WIDTH-320)/2,(imgHeight-40)/2,140,50,hStopDlgWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
				buttonCancle.btnHandle= BUTTON_CreateEx((LCD_WIDTH-320)/2+40+140,(imgHeight-40)/2,140,50,hStopDlgWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
			}
			//TEXT_SetBkColor(printStopDlgText,gCfgItems.state_background_color);
			//TEXT_SetTextColor(printStopDlgText,gCfgItems.state_text_color);
			
			//BUTTON_SetBkColor(buttonOk.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.dialog_btn_color);
			//BUTTON_SetBkColor(buttonOk.btnHandle,BUTTON_CI_PRESSED,gCfgItems.dialog_btn_color);
			//BUTTON_SetBkColor(buttonCancle.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.dialog_btn_color);
			//BUTTON_SetBkColor(buttonCancle.btnHandle,BUTTON_CI_PRESSED,gCfgItems.dialog_btn_color);
			
			//BUTTON_SetTextColor(buttonOk.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.dialog_btn_textcolor);
			//BUTTON_SetTextColor(buttonOk.btnHandle,BUTTON_CI_PRESSED,gCfgItems.dialog_btn_textcolor);
			//BUTTON_SetTextColor(buttonCancle.btnHandle,BUTTON_CI_UNPRESSED,gCfgItems.dialog_btn_textcolor);
			//BUTTON_SetTextColor(buttonCancle.btnHandle,BUTTON_CI_PRESSED,gCfgItems.dialog_btn_textcolor);

			if(DialogType == DIALOG_TYPE_STOP)
			{
				TEXT_SetText(printStopDlgText, print_file_dialog_menu.cancle_print);
				BUTTON_SetText(buttonOk.btnHandle, print_file_dialog_menu.confirm);
				BUTTON_SetText(buttonCancle.btnHandle, print_file_dialog_menu.cancle);
			}
			else if(DialogType == DIALOG_TYPE_PRINT_FILE)
			{
				print_start_flg = 1;
				
				if(gCfgItems.pwd_reprint_flg == 1)
				{
					TEXT_SetText(printStopDlgText,  print_file_dialog_menu.print_from_breakpoint);
					BUTTON_SetText(buttonOk.btnHandle, print_file_dialog_menu.confirm);
					BUTTON_SetText(buttonCancle.btnHandle, print_file_dialog_menu.cancle);			
				}
				else
				{
					printStopDlgText = TEXT_CreateEx(0,(imgHeight-40)/2-120, LCD_WIDTH, 40, hStopDlgWnd, WM_CF_SHOW, GUI_TA_VCENTER | GUI_TA_HCENTER,	alloc_win_id(), NULL);
					printfilename = TEXT_CreateEx(0,(imgHeight-40)/2-60, LCD_WIDTH, 30, hStopDlgWnd, WM_CF_SHOW, TEXT_CF_HCENTER|TEXT_CF_TOP,  alloc_win_id(), NULL);

					TEXT_SetBkColor(printfilename, gCfgItems.state_background_color);
					TEXT_SetTextColor(printfilename, gCfgItems.state_text_color );
					TEXT_SetBkColor(printStopDlgText, gCfgItems.state_background_color);
					TEXT_SetTextColor(printStopDlgText, gCfgItems.state_text_color);

					TEXT_SetText(printStopDlgText, print_file_dialog_menu.print_file);
					BUTTON_SetText(buttonOk.btnHandle, print_file_dialog_menu.confirm);
					BUTTON_SetText(buttonCancle.btnHandle, print_file_dialog_menu.cancle);
					
					GUI_Exec();
					GUI_UC_SetEncodeNone();
					TEXT_SetFont(printfilename,&GUI_FontHZ16);
					memset(codebuff,0,sizeof(codebuff));
					strcpy((char*)codebuff,&curFileName[3]);
					TEXT_SetText(printfilename, (char*)codebuff);
					GUI_Exec();
					GUI_UC_SetEncodeUTF8();
					
				}
			}
			else if(DialogType == DIALOG_TYPE_REPRINT_NO_FILE)
			{
				TEXT_SetText(printStopDlgText, file_menu.no_file_and_check);
				BUTTON_SetText(buttonOk.btnHandle, print_file_dialog_menu.confirm);
				BUTTON_SetText(buttonCancle.btnHandle, print_file_dialog_menu.cancle);
			}
			else if(DialogType == DIALOG_TYPE_M80_FAIL)
			{
				TEXT_SetText(printStopDlgText, print_file_dialog_menu.close_machine_error);
				BUTTON_SetText(buttonOk.btnHandle, print_file_dialog_menu.confirm);
			}
			else if(DialogType == DIALOG_TYPE_UNBIND)
			{
				TEXT_SetText(printStopDlgText, common_menu.unbind_printer_tips);
				BUTTON_SetText(buttonOk.btnHandle, print_file_dialog_menu.confirm);
				BUTTON_SetText(buttonCancle.btnHandle, print_file_dialog_menu.cancle);
			}

			else if(DialogType == DIALOG_TYPE_FILAMENT_LOAD_HEAT)
			{
				TEXT_SetText(printStopDlgText, filament_menu.filament_dialog_load_heat);
				BUTTON_SetText(buttonCancle.btnHandle, print_file_dialog_menu.cancle);			
			}
			else if(DialogType == DIALOG_TYPE_FILAMENT_HEAT_LOAD_COMPLETED)
			{
				TEXT_SetText(printStopDlgText, filament_menu.filament_dialog_load_heat_confirm);
				BUTTON_SetText(buttonOk.btnHandle, print_file_dialog_menu.confirm);	
	      		BUTTON_SetText(buttonCancle.btnHandle, print_file_dialog_menu.cancle);
			}
			else if(DialogType == DIALOG_TYPE_FILAMENT_LOADING)	
			{
				TEXT_SetText(printStopDlgText, filament_menu.filament_dialog_loading);
			}
			else if(DialogType == DIALOG_TYPE_FILAMENT_LOAD_COMPLETED)	
			{
				TEXT_SetText(printStopDlgText, filament_menu.filament_dialog_load_completed);
				BUTTON_SetText(buttonOk.btnHandle, print_file_dialog_menu.confirm);		
			}	
			else if(DialogType == DIALOG_TYPE_FILAMENT_UNLOAD_HEAT)
			{
				TEXT_SetText(printStopDlgText, filament_menu.filament_dialog_unload_heat);
				BUTTON_SetText(buttonCancle.btnHandle, print_file_dialog_menu.cancle);			
			}
			else if(DialogType == DIALOG_TYPE_FILAMENT_HEAT_UNLOAD_COMPLETED)
			{
				TEXT_SetText(printStopDlgText, filament_menu.filament_dialog_unload_heat_confirm);
				BUTTON_SetText(buttonOk.btnHandle, print_file_dialog_menu.confirm);	
	      		BUTTON_SetText(buttonCancle.btnHandle, print_file_dialog_menu.cancle);
			}
			else if(DialogType == DIALOG_TYPE_FILAMENT_UNLOADING)	
			{
				TEXT_SetText(printStopDlgText, filament_menu.filament_dialog_unloading);
			}
			else if(DialogType == DIALOG_TYPE_FILAMENT_UNLOAD_COMPLETED)	
			{
				TEXT_SetText(printStopDlgText, filament_menu.filament_dialog_unload_completed);
				BUTTON_SetText(buttonOk.btnHandle, print_file_dialog_menu.confirm);		
			}
		}

		
		//BUTTON_SetTextAlign(buttonOk, GUI_TA_VCENTER | GUI_TA_HCENTER);
		//BUTTON_SetTextAlign(buttonCancle, GUI_TA_VCENTER | GUI_TA_HCENTER);

		//∂‘∞¥≈•◊ˆ≤¡≥˝±Í÷æ…Ë÷√°£
		//BUTTON_SetBmpFileName(buttonOk,NULL,1);
		//BUTTON_SetBmpFileName(buttonCancle,NULL,1);

#if 1
		if(buttonOk.btnHandle)
		{
			BUTTON_SetBkColor(buttonOk.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.dialog_btn_color);
			BUTTON_SetBkColor(buttonOk.btnHandle, BUTTON_CI_PRESSED, gCfgItems.dialog_btn_color);
			BUTTON_SetTextColor(buttonOk.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.dialog_btn_textcolor);
			BUTTON_SetTextColor(buttonOk.btnHandle, BUTTON_CI_PRESSED, gCfgItems.dialog_btn_textcolor);
			BUTTON_SetTextAlign(buttonOk.btnHandle, GUI_TA_VCENTER | GUI_TA_HCENTER);
	
			//ÂØπÊåâÈíÆÂÅöÊì¶Èô§Ê†áÂøóËÆæÁΩÆ„ÄÇ
			BUTTON_SetBmpFileName(buttonOk.btnHandle,NULL,1);
		}
		if(buttonCancle.btnHandle)
		{
			BUTTON_SetBkColor(buttonCancle.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.dialog_btn_color);
			BUTTON_SetBkColor(buttonCancle.btnHandle, BUTTON_CI_PRESSED, gCfgItems.dialog_btn_color);
			BUTTON_SetTextColor(buttonCancle.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.dialog_btn_textcolor);
			BUTTON_SetTextColor(buttonCancle.btnHandle, BUTTON_CI_PRESSED, gCfgItems.dialog_btn_textcolor);
			BUTTON_SetTextAlign(buttonCancle.btnHandle, GUI_TA_VCENTER | GUI_TA_HCENTER);
	
			//ÂØπÊåâÈíÆÂÅöÊì¶Èô§Ê†áÂøóËÆæÁΩÆ„ÄÇ
			BUTTON_SetBmpFileName(buttonCancle.btnHandle,NULL,1);
		}		
#endif	
}



void filament_sprayer_temp()
{
	int8_t buf[50] = {0};
	int8_t buf1[30] = {0};

	TEXT_SetTextColor(filament_temper, gCfgItems.state_text_color);
	TEXT_SetBkColor(filament_temper, gCfgItems.state_background_color);

	sprintf((char*)buf,"E%d: ",gCfgItems.curSprayerChoose+1);
	sprintf((char *)buf1, filament_menu.stat_temp,(int)gCfgItems.curSprayerTemp[gCfgItems.curSprayerChoose],(int)gCfgItems.desireSprayerTemp[gCfgItems.curSprayerChoose]);
	strcat((char*)buf,(char*)buf1);
	TEXT_SetText(filament_temper, (char *)buf);
}
void filament_dialog_handle(void)
{			
		
			
			if((temp_update_flag == 1)
				&&((DialogType == DIALOG_TYPE_FILAMENT_LOAD_HEAT)
				||(DialogType == DIALOG_TYPE_FILAMENT_UNLOAD_HEAT)))
			{
				temp_update_flag = 0;
				filament_sprayer_temp();
			}
			if(((abs((int)gCfgItems.curSprayerTemp[gCfgItems.curSprayerChoose] - gCfgItems.filament_limit_temper)<=1)
				||((int)gCfgItems.curSprayerTemp[gCfgItems.curSprayerChoose] >= gCfgItems.filament_limit_temper))
				&&(filament_load_heat_flg==1))
			{
				filament_load_heat_flg = 0;
				Clear_dialog();
				draw_dialog(DIALOG_TYPE_FILAMENT_HEAT_LOAD_COMPLETED);				
			}

			if(filament_loading_completed==1)
			{
				filament_rate = 0;
				filament_loading_completed = 0;

				Clear_dialog();
				draw_dialog(DIALOG_TYPE_FILAMENT_LOAD_COMPLETED);	

				if(printerStaus == pr_pause)
				{
					positionSaveFlag = 1;
				}
			}
			if(((abs((int)gCfgItems.curSprayerTemp[gCfgItems.curSprayerChoose] - gCfgItems.filament_limit_temper)<=1)
				||((int)gCfgItems.curSprayerTemp[gCfgItems.curSprayerChoose] >= gCfgItems.filament_limit_temper))
				&&(filament_unload_heat_flg==1))
			{
				filament_unload_heat_flg = 0;
				Clear_dialog();
				draw_dialog(DIALOG_TYPE_FILAMENT_HEAT_UNLOAD_COMPLETED);				
			}

			if(filament_unloading_completed==1)
			{
				filament_rate = 0;
				filament_unloading_completed = 0;

				Clear_dialog();
				draw_dialog(DIALOG_TYPE_FILAMENT_UNLOAD_COMPLETED);

				if(printerStaus == pr_pause)
				{
					positionSaveFlag = 1;
				}

			}
			
			if((DialogType == DIALOG_TYPE_FILAMENT_LOADING)||(DialogType == DIALOG_TYPE_FILAMENT_UNLOADING))
			{

				PROGBAR_SetBarColor(FilamentBar, 0, GUI_GREEN);
				PROGBAR_SetValue(FilamentBar,filament_rate);
			}				
	
}


void Clear_dialog()
{
	GUI_SetBkColor(gCfgItems.background_color);	
	if(WM_IsWindow(hStopDlgWnd))
	{
		WM_DeleteWindow(hStopDlgWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}
