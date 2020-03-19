#include "gui.h"
#include "button.h"
#include "PROGBAR.h"
#include "draw_ui.h"
#include "fontLib.h"
#include "LISTBOX.h"
#include "text.h"
#include "draw_FileTransfer_ui.h"
#include "draw_ready_print.h"

#ifndef GUI_FLASH
#define GUI_FLASH
#endif

extern uint8_t WifiFileProcess;
extern uint32_t WifiFileUnzipSize;


static GUI_HWIN hFileTransferWnd;
static PROGBAR_Handle fileTransferBar;

static GUI_HWIN hWifiFileDlgWnd;

static TEXT_Handle WifiFilestateDlgText,FileTransferText;
static BUTTON_STRUCT buttonReturn;

extern uint8_t  Get_Temperature_Flg;


static void cbWifiFileDlgWin(WM_MESSAGE * pMsg) {

	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			//GUI_SetBkColor(GUI_BLUE);
			//GUI_Clear();
			//GUI_DispString("window");
			break;
		case WM_TOUCH:
		 	
			break;
		case WM_TOUCH_CHILD:
			
			break;
			
		case WM_NOTIFY_PARENT:
			if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
			{
				if(pMsg->hWinSrc == buttonReturn.btnHandle)
				{
					
					Clear_WifiFileTransferdialog();
					Get_Temperature_Flg = 0;
					draw_ready_print();

				}
				
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
		}
	}


void draw_dialog_filetransfer(uint8_t WifiTransferDialogType)
{
	
	int i;
	
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != FILETRANSFERSTATE_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = FILETRANSFERSTATE_UI;
	}
	disp_state = FILETRANSFERSTATE_UI;

	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
	
	GUI_SetFont(&FONT_TITLE);
	if(gCfgItems.language == LANG_ENGLISH)
	{
		if(WifiTransferDialogType == 0)
		{
			GUI_DispStringAt("file transfer fail!", 80, titleHeight  + 75);

		}
		else if(WifiTransferDialogType == 1)
		{
			GUI_DispStringAt("file transfer success!", 80, titleHeight  + 75);
		}
		else if(WifiTransferDialogType == 2)
		{
			GUI_DispStringAt("please check \nwether memory device insert!", 40, titleHeight  + 70);
		}
		
	}
	else
	{
		if(WifiTransferDialogType == 0)
		{
			GUI_DispStringAt("文件传输失败!", 80, titleHeight  + 75);

		}
		else if(WifiTransferDialogType == 1)
		{
			GUI_DispStringAt("文件传输成功!", 80, titleHeight  + 75);
		}
		else if(WifiTransferDialogType == 2)
		{	
			GUI_DispStringAt("请检查是否插入存储设备!", 40, titleHeight  + 75);
		}

	}
	
	GUI_SetFont(&FONT_TITLE);
	
	hWifiFileDlgWnd = WM_CreateWindow(LCD_WIDTH * 3 / 4 , titleHeight + imgHeight / 2, LCD_WIDTH / 4 - 1, imgHeight / 2 - 1, WM_CF_SHOW, cbWifiFileDlgWin, 0);

	BUTTON_SetDefaultTextAlign(GUI_TA_VCENTER | GUI_TA_HCENTER);
	BUTTON_SetDefaultFont(&FONT_BUTTON);

	buttonReturn.btnHandle = BUTTON_CreateEx(0 , 0, LCD_WIDTH / 4 - 2, imgHeight / 2 - 1, hWifiFileDlgWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	TEXT_SetDefaultFont(&FONT_STATE_INF);	

	if(gCfgItems.language == LANG_ENGLISH)
	{
		BUTTON_SetText(buttonReturn.btnHandle, "Back");
	}
	else
	{
		BUTTON_SetText(buttonReturn.btnHandle, "返回\n");
	}	

	BUTTON_SetBkColor(buttonReturn.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.background_color);
	BUTTON_SetBkColor(buttonReturn.btnHandle, BUTTON_CI_PRESSED, gCfgItems.background_color);

	
	//GUI_Exec();

}

void Clear_WifiFileTransferdialog()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hWifiFileDlgWnd))
	{
		WM_DeleteWindow(hWifiFileDlgWnd);
		//GUI_Exec();
	}
	//GUI_Clear();
}


static void cbFileTransferWin(WM_MESSAGE * pMsg) {

struct PressEvt *press_event;
switch (pMsg->MsgId)
{
	case WM_PAINT:

				
		break;
	case WM_TOUCH:
	 	press_event = (struct PressEvt *)pMsg->Data.p;
		
		break;
	case WM_TOUCH_CHILD:
		press_event = (struct PressEvt *)pMsg->Data.p;

		break;
		
	case WM_NOTIFY_PARENT:

		break;
		
	default:
		WM_DefaultProc(pMsg);
	}
}


void draw_filetansfer(uint8_t file_unzip_flg)
{
	int8_t buf[50] = {0};
	int i;
	
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != FILETRANSFER_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = FILETRANSFER_UI;
	}
	disp_state = FILETRANSFER_UI;

	GUI_SetBkColor(gCfgItems.background_color);
	GUI_SetColor(gCfgItems.title_color);
	GUI_Clear();
	GUI_SetFont(&FONT_TITLE);

	hFileTransferWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbFileTransferWin, 0);

	FileTransferText = TEXT_CreateEx(0,120, LCD_WIDTH, 30, hFileTransferWnd, WM_CF_SHOW, TEXT_CF_LEFT,  alloc_win_id(), "");
	
	TEXT_SetBkColor(FileTransferText, gCfgItems.background_color);
#if 1
    if(gCfgItems.fileSysType == FILE_SYS_SD)
	{
		if(gCfgItems.language == LANG_ENGLISH)
		{
			TEXT_SetText(FileTransferText,"Recieving file");
		}
		else
		{
			TEXT_SetText(FileTransferText,"接收文件中");
		}
	}
	else if(gCfgItems.fileSysType == FILE_SYS_USB)
	{
		if(gCfgItems.language == LANG_ENGLISH)
		{
			if(file_unzip_flg == 1)
			{
				TEXT_SetText(FileTransferText,"unziping file");
			}
			else
			{
				TEXT_SetText(FileTransferText,"Recieving file");
			}
		}
		else
		{
			if(file_unzip_flg == 1)
			{
				TEXT_SetText(FileTransferText,"文件解压中");
			}
			else
			{
				TEXT_SetText(FileTransferText,"文件接收中");
			}
		}		
	}
#endif
	TEXT_SetTextColor(FileTransferText, gCfgItems.title_color);
	TEXT_SetTextAlign(FileTransferText, GUI_TA_VCENTER | GUI_TA_HCENTER);

	//GUI_Exec();
}



void Clear_fileTransfer()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hFileTransferWnd))
	{
		WM_DeleteWindow(hFileTransferWnd);
		//GUI_Exec();
	}
	
	//GUI_Clear();
}
/*
void Clear_WifiFileTransferdialog()
{
	GUI_SetBkColor(gCfgItems.background_color);	
	if(WM_IsWindow(hWifiFileDlgWnd))
	{
		WM_DeleteWindow(hWifiFileDlgWnd);
		GUI_Exec();
	}
	
	GUI_Clear();
}
*/

