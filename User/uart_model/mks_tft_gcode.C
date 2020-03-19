/********************   (C) COPYRIGHT 2014 www.makerbase.com.cn   ********************
 * 文件名  ：mks_tft_gcode.c
 * 描述    ：1.从u盘读取源文件，每次读取1k字节，轮流写入udiskBuffer.buffer[0]和udiskBuffer.buffer[1]；
 						2. 当udiskBuffer.buffer[n]非空时，提取出有效gcode指令，加上前/后缀后,Push到gcodeTxFIFO队列。
 * 作者    ：skyblue
**********************************************************************************/


#include <stdio.h>
#include <string.h>
#include "ff.h"
#include "mks_tft_fifo.h"
#include "mks_tft_gcode.h"
//#include "main.h"
#include "mks_tft_com.h"
//**#include "printer.h"
//**#include "draw_ui.h"
#include "mks_cfg.h"
//#include "others.h"
#include "GUI.h"
#include "draw_dialog.h"




extern void Btn_putdown_close_machine();
extern uint8_t IsChooseAutoShutdown;
extern uint8_t close_fail_flg;
extern uint16_t close_fail_cnt;
/***************************add******************/
extern CFG_ITMES gCfgItems;
/***************************end******************/

struct position Gcode_current_position[30];

uint8_t Chk_close_machine_flg = 0;

UDISK_DATA_BUFFER udiskBuffer;

unsigned char note_flag=1;	//注释标志 init : 1
unsigned long gcodeLineCnt=0;	//指令行号编号 Nxxxxx


UDISK_FILE_STAUS udiskFileStaus;			//文件状态

TARGER_TEMP targetTemp;
TEMP_STATUS	tempStatus;
void getFanStatus(unsigned char *gcode,unsigned char *end)
{
	unsigned char tempBuf[30];
	unsigned char i;
	unsigned char *p;
	
		if(*gcode == 'M' && *(gcode+1) == '1' && *(gcode+2) == '0'&& (*(gcode+3) == '6' || *(gcode+3) == '7' ))	//M106 M107
		{
			p = gcode;
			i=0;
			while(p<end)
			{
				tempBuf[i++]=*p++;
			}
			tempBuf[i] = '\n';
			
			pushFIFO(&gcodeCmdRxFIFO,&tempBuf[0]);
		}
		
}

void getTargetTemp(unsigned char *gcode,unsigned char *end)
{
	int8_t *tmpStr_1 = 0;
	
	unsigned char tempBuf[80]="ok T:0 /210 B:0 /45 @:0 B@:0";
	unsigned char count;
	unsigned char *p;
	if(tempStatus == temp_ok )		return;
	
	p = &tempBuf[0];
	//获取单位 mm or inch ,默认mm

	if(*gcode == 'G' && *(gcode+1) == '2' && *(gcode+2) == '0' )
		RePrintData.unit = 1;	//0 mm,1 inch
/*	
//20151019
	if(*gcode == 'M' && *(gcode+1) == '1' && (*(gcode+2) == '9' ||*(gcode+2) == '4' )&& *(gcode+3) == '0')	//M190 or M140
	{
		gcode += 4;
		count = 0;
		while(*gcode++ != 'S')
			if(count++ > 10) break;

		while(gcode < end)
		{
			if(*gcode == '.')break;
			*p++ = *gcode++;
			if(p >=&tempBuf[0]+10) break;
		}
		*p = '\0';
		targetTemp.bedTemp = atoi(&tempBuf[0]);
	}

	if(*gcode == 'M' && *(gcode+1) == '1' && *(gcode+2) == '0'&& (*(gcode+3) == '9' || *(gcode+3) == '4'))	//M109 or M104
	{
		gcode += 4;
		count = 0;
		while(*gcode++ != 'S')
			if(count++ > 10) break;

		while(gcode < end)
		{
			if(*gcode == '.') break;
			*p++ = *gcode++;
			if(p >=&tempBuf[0]+10) break;
		}
		*p = '\0';
		targetTemp.t0Temp = atoi(&tempBuf[0]);
	}
*/
	if(*gcode == 'M' && *(gcode+1) == '1' && (*(gcode+2) == '9' ||*(gcode+2) == '4' )&& *(gcode+3) == '0')	//M190 or M140
	{
		gcode += 4;
		count = 0;
		while(*gcode++ != 'S')
			if(count++ > 10) break;

		while(gcode < end)
		{
			if(*gcode == '.')break;
			*p++ = *gcode++;
			if(p >=&tempBuf[0]+10) break;
		}
		*p = '\0';
		targetTemp.bedTemp = atoi(&tempBuf[0]);
	}

	if(gCfgItems.sprayerNum == 1)
	{
		if(*gcode == 'M' && *(gcode+1) == '1' && *(gcode+2) == '0'&& (*(gcode+3) == '9' || *(gcode+3) == '4'))	//M109 or M104
		{
			gcode += 4;
			count = 0;
			while(*gcode++ != 'S')
				if(count++ > 10) break;

			while(gcode < end)
			{
				if(*gcode == '.') break;
				*p++ = *gcode++;
				if(p >=&tempBuf[0]+10) break;
			}
			*p = '\0';
			targetTemp.t0Temp = atoi(&tempBuf[0]);
		}
	}
	else
	{
		if(*gcode == 'M' && *(gcode+1) == '1' && *(gcode+2) == '0'&& (*(gcode+3) == '9' || *(gcode+3) == '4'))	//M109 or M104
		{
			if((int8_t *)strstr(gcode, "T0"))
			{
					tmpStr_1 = (int8_t *)strstr(gcode, "S");	
					if(tmpStr_1)
					{
						gcode = tmpStr_1+1;
						while(gcode < end)
						{
							if(*gcode == '.') break;
							*p++ = *gcode++;
							if(p >=&tempBuf[0]+10) break;
						}
						*p = '\0';
						targetTemp.t0Temp = atoi(&tempBuf[0]);						
					}
			}
			else if((int8_t *)strstr(gcode, "T1"))
			{
					tmpStr_1 = (int8_t *)strstr(gcode, "S");	
					if(tmpStr_1)
					{
						gcode = tmpStr_1+1;
						while(gcode < end)
						{
							if(*gcode == '.') break;
							*p++ = *gcode++;
							if(p >=&tempBuf[0]+10) break;
						}
						*p = '\0';
						targetTemp.t1Temp = atoi(&tempBuf[0]);						
					}			
			}
			else
			{
					tmpStr_1 = (int8_t *)strstr(gcode, "S");	
					if(tmpStr_1)
					{
						gcode = tmpStr_1+1;
						while(gcode < end)
						{
							if(*gcode == '.') break;
							*p++ = *gcode++;
							if(p >=&tempBuf[0]+10) break;
						}
						*p = '\0';
						if(RePrintData.spayerchoose == 1)
						{
							targetTemp.t1Temp = atoi(&tempBuf[0]);
						}
						else
						{
							targetTemp.t0Temp = atoi(&tempBuf[0]);						
						}		
					}
			}		

		}

	}
/*
	if((targetTemp.bedTemp > 0 && targetTemp.t0Temp >0) ||( gcodeLineCnt> 50))
	{
		//tempBuf[40]="ok T:0 /210 B:0 /45 @:0 B@:0";
		p = &tempBuf[0];	
		*p++ = 'o';*p++ = 'k';*p++ = ' ';*p++ = 'T';*p++ = ':';*p++ = '0';*p++ = ' ';*p++ = '/';
		*p++ = targetTemp.t0Temp/100+48;
		*p++ = (targetTemp.t0Temp/10)%10 + 48;
		*p++ = targetTemp.t0Temp%10 + 48;
		
		*p++ = ' ';	*p++ = 'B';*p++ = ':';*p++ = '0';*p++ = ' ';*p++ = '/';
		*p++ = targetTemp.bedTemp/10+48;
		*p++ = targetTemp.bedTemp%10 + 48;
		*p++ = ' ';*p++ = '@';*p++ = ':';*p++ = '0';*p++ = ' ';*p++ = 'B';*p++ = '@';*p++ = ':';*p++ = '0';*p++ = '\n';
		
		pushFIFO(&gcodeCmdRxFIFO,&tempBuf[0]);
		tempStatus = temp_ok;
	}
*/
	if((targetTemp.bedTemp > 0)||(targetTemp.t0Temp >0)||(targetTemp.t1Temp >0))
	{
		if(gCfgItems.sprayerNum == 1)
		{
			//tempBuf[40]="ok T:0 /210 B:0 /45 @:0 B@:0";
			p = &tempBuf[0];	
			*p++ = 'o';*p++ = 'k';*p++ = ' ';*p++ = 'T';*p++ = ':';
			// *p++ = '0';
			*p++ = ((uint32_t)(gCfgItems.curSprayerTemp[0]))/100+48;
			*p++ = (((uint32_t)(gCfgItems.curSprayerTemp[0]))/10)%10 + 48;
			*p++ = ((uint32_t)(gCfgItems.curSprayerTemp[0]))%10 + 48;
			*p++ = ' ';*p++ = '/';
			*p++ = targetTemp.t0Temp/100+48;
			*p++ = (targetTemp.t0Temp/10)%10 + 48;
			*p++ = targetTemp.t0Temp%10 + 48;
			
			*p++ = ' ';	*p++ = 'B';*p++ = ':';
			// *p++ = '0';
			*p++ = ((uint32_t)(gCfgItems.curBedTemp))/100+48;
			*p++ = (((uint32_t)(gCfgItems.curBedTemp))/10)%10+48;
			*p++ = ((uint32_t)(gCfgItems.curBedTemp))%10 + 48;
			*p++ = ' ';*p++ = '/';
			*p++ = targetTemp.bedTemp/100+48;
			*p++ = (targetTemp.bedTemp/10)%10+48;
			*p++ = targetTemp.bedTemp%10 + 48;
			*p++ = ' ';*p++ = '@';*p++ = ':';*p++ = '0';*p++ = ' ';*p++ = 'B';*p++ = '@';*p++ = ':';*p++ = '0';*p++ = '\n';
			
			pushFIFO(&gcodeCmdRxFIFO,&tempBuf[0]);
		}
		else
		{
			//ok T:0 /210 B:0 /45 T0:0/210 T1:0 /210 @:0 B@:0
			p = &tempBuf[0];	
			*p++ = 'o';*p++ = 'k';*p++ = ' ';*p++ = 'T';*p++ = ':';
			// *p++ = '0';
			*p++ = ((uint32_t)(gCfgItems.curSprayerTemp[0]))/100+48;
			*p++ = (((uint32_t)(gCfgItems.curSprayerTemp[0]))/10)%10 + 48;
			*p++ = ((uint32_t)(gCfgItems.curSprayerTemp[0]))%10 + 48;
			*p++ = ' ';*p++ = '/';
			*p++ = targetTemp.t0Temp/100+48;
			*p++ = (targetTemp.t0Temp/10)%10 + 48;
			*p++ = targetTemp.t0Temp%10 + 48;
			//B
			*p++ = ' ';	*p++ = 'B';*p++ = ':';
			// *p++ = '0';
			*p++ = ((uint32_t)(gCfgItems.curBedTemp))/100+48;
			*p++ = (((uint32_t)(gCfgItems.curBedTemp))/10)%10+48;
			*p++ = ((uint32_t)(gCfgItems.curBedTemp))%10 + 48;
			*p++ = ' ';*p++ = '/';
			*p++ = targetTemp.bedTemp/100+48;
			*p++ = (targetTemp.bedTemp/10)%10+48;
			*p++ = targetTemp.bedTemp%10 + 48;
			//T0
			*p++ = ' ';*p++ = 'T';*p++ = '0';*p++ = ':';
			// *p++ = '0';
			*p++ = ((uint32_t)(gCfgItems.curSprayerTemp[0]))/100+48;
			*p++ = (((uint32_t)(gCfgItems.curSprayerTemp[0]))/10)%10 + 48;
			*p++ = ((uint32_t)(gCfgItems.curSprayerTemp[0]))%10 + 48;			
			*p++ = ' ';*p++ = '/';
			*p++ = targetTemp.t0Temp/100+48;
			*p++ = (targetTemp.t0Temp/10)%10 + 48;
			*p++ = targetTemp.t0Temp%10 + 48;
			//T1
			*p++ = ' ';*p++ = 'T';*p++ = '1';*p++ = ':';
			// *p++ = '0';
			*p++ = ((uint32_t)(gCfgItems.curSprayerTemp[1]))/100+48;
			*p++ = (((uint32_t)(gCfgItems.curSprayerTemp[1]))/10)%10 + 48;
			*p++ = ((uint32_t)(gCfgItems.curSprayerTemp[1]))%10 + 48;			
			*p++ = ' ';*p++ = '/';
			*p++ = targetTemp.t1Temp/100+48;
			*p++ = (targetTemp.t1Temp/10)%10 + 48;
			*p++ = targetTemp.t1Temp%10 + 48;

			
			*p++ = ' ';*p++ = '@';*p++ = ':';*p++ = '0';*p++ = ' ';*p++ = 'B';*p++ = '@';*p++ = ':';*p++ = '0';*p++ = '\n';

			pushFIFO(&gcodeCmdRxFIFO,&tempBuf[0]);			
		}
		
	}

	if(gcodeLineCnt> 50)
	{
		tempStatus = temp_ok;
	}

}


void udiskBufferInit(void)
{
	memset(udiskBuffer.buffer[0],'\n',sizeof(udiskBuffer.buffer[0]));
	memset(udiskBuffer.buffer[1],'\n',sizeof(udiskBuffer.buffer[1]));
	udiskBuffer.current = 0;
	udiskBuffer.p = udiskBuffer.buffer[udiskBuffer.current];
	udiskBuffer.state[udiskBuffer.current] = udisk_buf_full;
	udiskBuffer.state[(udiskBuffer.current+1)%2] = udisk_buf_empty;

	note_flag = 1;
	gcodeLineCnt = 0;
	RePrintData.record_line = 0;
	
	udiskFileStaus = udisk_file_ok;
	/*----------------*/
	targetTemp.bedTemp = 0;
	targetTemp.t0Temp = 0;
	targetTemp.t1Temp = 0;
	targetTemp.t2Temp = 0;
	tempStatus = temp_fail;
	/*----------------*/

	RePrintData.saveEnable = 0;
	
	initFIFO(&gcodeTxFIFO);
//	initFIFO(&gcodeRxFIFO);
	initFIFO(&gcodeCmdTxFIFO);
	initFIFO(&gcodeCmdRxFIFO);
}


void udiskFileR(FIL *srcfp)		//读取u盘文件，写入udiskBuffer
{		
		unsigned int readByteCnt=0;
	
		if((udiskBuffer.state[(udiskBuffer.current+1)%2] == udisk_buf_full) && (udiskFileStaus == udisk_file_ok))
			return;
	
		switch(udiskFileStaus)
		{
			case udisk_file_ok:
					f_read(srcfp,udiskBuffer.buffer[(udiskBuffer.current+1)%2],UDISKBUFLEN,&readByteCnt);
					udiskBuffer.state[(udiskBuffer.current+1)%2] = udisk_buf_full;
					if(readByteCnt < UDISKBUFLEN)
					{
						udiskFileStaus = udisk_file_end;
						fileEndCnt = 30000;	
					}
				
				break;
			case udisk_file_end:
					
					if((udiskBuffer.state[0] == udisk_buf_empty && udiskBuffer.state[1] == udisk_buf_empty && checkFIFO(&gcodeTxFIFO)== fifo_empty)) //打印结束
					{
						tftDelay(3);
						printerInit();
						tftDelay(3);

						//**I2C_EE_Init(100000);
						MX_I2C1_Init();   //**

						HAL::AT24CXX_Read(BAK_REPRINT_INFO, (uint8_t *)&dataToEeprom,  4); 
						dataToEeprom &= 0x00ffffff;
						dataToEeprom |= (uint32_t)(printer_normal << 24 ) & 0xff000000;
						HAL::AT24CXX_Write(BAK_REPRINT_INFO,(uint8_t *)&dataToEeprom ,  4); 		// 续打标志(uint8_t) | 单位unit (uint8_t) | saveFlag(uint8_t)| null(uint8_t)
						
						printerStaus = pr_idle;		//打印结束
						usart2Data.printer = printer_idle;
						usart2Data.prWaitStatus = pr_wait_idle;
						usart2Data.timer = timer_stop;						//清除定时器

						if((gCfgItems.print_finish_close_machine_flg == 1)&&(IsChooseAutoShutdown == 1))
						{
							//Print_finish_close_machine();
							Btn_putdown_close_machine();
							IsChooseAutoShutdown = 0;
							clear_cur_ui();
							#if 0
							//GUI_SetFont(&FONT_TITLE);
							if(gCfgItems.language == LANG_COMPLEX_CHINESE)
							{
								GUI_SetFont(&GUI_FontHZ16);
							}
							else
							{
								GUI_SetFont(&FONT_TITLE);
							}

							if(gCfgItems.language == LANG_ENGLISH)
							{
								GUI_DispStringAt("Print end! Closing Machine...", 50, 120);
							}
							else 	if(gCfgItems.language == LANG_COMPLEX_CHINESE)
							{
								GUI_DispStringAt("打印完成!正在關機...", 50, 120);
							}
							else
							{
								GUI_DispStringAt("打印完成! 正在关机...", 50, 120);
							}
							#endif
							GUI_DispStringAt(common_menu.close_machine_tips, 320, 210);
							close_fail_flg = 1;
							close_fail_cnt = 0;
							while(close_fail_flg);
							clear_cur_ui();
							draw_dialog(DIALOG_TYPE_M80_FAIL);
						}
					}

					if(udiskBuffer.state[udiskBuffer.current] == udisk_buf_empty)
					{
							udiskBuffer.current = (udiskBuffer.current+1)%2;
							udiskBuffer.p = udiskBuffer.buffer[udiskBuffer.current];
					}

				break;
				default : break;
		}
}


void pushTxGcode(void)		//从udiskBuffer数据中提取出有效的gcode指令，并加上行号，push到gcodeTxFIFO
{
	static unsigned char position_cnt = 0;
	unsigned char numb_cnt = 0;
	
	unsigned char gcode[FIFO_SIZE];		//存储从udiskBuffer提取的一条gcode
	unsigned char *p=gcode;				//指向gcode的指针
	unsigned char gcode_tx[FIFO_SIZE];	//可发送的gcode指令，加了行号和校验码
	unsigned char *p_tx=gcode_tx;		//指向gcode_tx的指针
	unsigned long gcodeLineCnt_b;		//暂存gcodeLineCnt
	unsigned char lineCntBuf[20];		//存储行号字符串
	unsigned char *p_cnt=lineCntBuf;	
	unsigned char checkSum=0;			//校验和
	unsigned char ulockCnt=0;			//长注释 计数，防止 搜索长数据，导致不能从udisk读取文件，造成死锁

	if(checkFIFO(&gcodeTxFIFO)== fifo_full)			//队列满
		return;

	if(udiskBuffer.state[udiskBuffer.current] == udisk_buf_empty)	//buffer空
		return;

			while(*udiskBuffer.p != '\n'  && *udiskBuffer.p != '\r')	//行结束
			{
				if(p-gcode > (FIFO_SIZE-10))	//一行指令太长，结束，并注释掉后续字符
				{
					*(udiskBuffer.p +1)= ';';
					break;
				}

				//if(ulockCnt++ > FIFO_SIZE && p == gcode)		//防止长注释 造成死锁
				//{
				//	return;
				//}

				

				if(*udiskBuffer.p == ';')	//去掉 ';' 后面的注释
					note_flag =  0;

				if(note_flag)
					*p++ = *udiskBuffer.p++;	//提取有效gcode指令
				else
					udiskBuffer.p++;

				if(udiskBuffer.p == udiskBuffer.buffer[udiskBuffer.current]+ UDISKBUFLEN)	//当前buffer 读取结束,转换到另一buffer
				{
					memset(udiskBuffer.buffer[udiskBuffer.current],'\n',sizeof(udiskBuffer.buffer[0]));		//buffer 数据置'\n'
					udiskBuffer.state[udiskBuffer.current] = udisk_buf_empty;								//buffer 状态置empty
					udiskBuffer.current = (udiskBuffer.current+1)%2;										//转下一个buffer
					udiskBuffer.p = udiskBuffer.buffer[udiskBuffer.current];								//地址指向下一个buffer
				}

				if(ulockCnt++ > FIFO_SIZE && p == gcode)		//防止长注释 造成死锁
				{
					return;
				}


			}
			udiskBuffer.p++;	//跳过'\n'字符
			if(udiskBuffer.p == udiskBuffer.buffer[udiskBuffer.current]+ UDISKBUFLEN)	//当前buffer 读取结束,转换到另一buffer
				{
					memset(udiskBuffer.buffer[udiskBuffer.current],'\n',sizeof(udiskBuffer.buffer[0]));		//buffer 数据置'\n'
					udiskBuffer.state[udiskBuffer.current] = udisk_buf_empty;								//buffer 状态置empty
					udiskBuffer.current = (udiskBuffer.current+1)%2;										//转下一个buffer
					udiskBuffer.p = udiskBuffer.buffer[udiskBuffer.current];								//地址指向下一个buffer
				}

			note_flag = 1;		

			if(p > gcode)		//读取到了gcode指令
			{
				while(*(--p) == 32);	//去掉gcode指令后多余的空格
					p++;
				
				*p_tx++ = 'N';					//加'N'	
				
				gcodeLineCnt_b = gcodeLineCnt;			//加行号
				
			
				*p_cnt++=gcodeLineCnt_b%10 + 48;
				gcodeLineCnt_b /= 10;
				while(gcodeLineCnt_b!=0)
				{
					*p_cnt++=gcodeLineCnt_b%10 + 48;
					gcodeLineCnt_b /= 10;
				}


				while(p_cnt>lineCntBuf)
					*p_tx++ = *--p_cnt;
				
				*p_tx++ = 32;							//加空格

				gcodeLineCnt++;
				//单双喷头挤出判断
				if((gcode[0]=='T')&&(gcode[1]=='0'))
				{
					RePrintData.spayerchoose = 0;
				}
				if((gcode[0]=='T')&&(gcode[1]=='1'))
				{
					RePrintData.spayerchoose = 1;
				}
				//
				getTargetTemp(&gcode[0],p);			//获取目标温度
				getFanStatus(&gcode[0],p);				//获取风扇状态
				
				p_cnt=gcode;								//加gcode指令,临时使用p_cnt
				while(p_cnt<p)								
				{
				*p_tx++ = *p_cnt++;
				}
				*p_tx++ = '*';										//加'*'

															//加校验
				p_cnt= gcode_tx;
				while(*p_cnt != '*')
					checkSum ^= *p_cnt++;
				
				if(checkSum/100 != 0)				
				{
					*p_tx++ = checkSum/100 + 48;
					*p_tx++ = (checkSum/10)%10 + 48;
					*p_tx++ = checkSum%10 + 48;
				}
				else if(checkSum/10 != 0)
				{
					*p_tx++ = checkSum/10 + 48;
					*p_tx++ = checkSum%10 + 48;
				}
				else
					*p_tx++ = checkSum%10 + 48;
				
				*p_tx++ = '\n';								//加'\n'

				//USART2_CR1 &= 0xff9f;
				pushFIFO(&gcodeTxFIFO,&gcode_tx[0]);			//入队列

				RePrintData.offset =  f_tell(srcfp)-UDISKBUFLEN;
				if(udiskBuffer.state[(udiskBuffer.current+1)%2] == udisk_buf_full)
					RePrintData.offset -= UDISKBUFLEN;
				RePrintData.offset += udiskBuffer.p - udiskBuffer.buffer[udiskBuffer.current];
				//USART2_CR1 |= 0x0060;

				//20151012
				Gcode_current_position[position_cnt].Gcode_LineNumb= gcodeLineCnt;
				Gcode_current_position[position_cnt++].Gcode_fileOffset= RePrintData.offset;
				if(position_cnt >= 30)
				{
					position_cnt = 0;
				}
				

			}
}



