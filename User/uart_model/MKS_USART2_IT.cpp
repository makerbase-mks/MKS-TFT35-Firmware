/********************   (C) COPYRIGHT 2014 www.makerbase.com.cn   ********************
 * 文件名  ：MKS_USART2_IT.c
 * 描述    ：Marlin通信处理模块
						 1. printerStaus = idle ,将PUSH到gcodeCmdTxFIFO的命令从usart2发出,并将usart2收到的应答Push到gcodeCmdRxFIFO；
						 2. printerStaus = working，
						 		a) 实时发送gcodeTxFIFO的打印数据；
						 		b) 发送数据后，超过5s未收到应答，重复发送该数据，直到收到应答；
						 		c) 收到 Error:Line Number is not Last Line Number+1, Last Line: n，发送Nn+1数据；
						 		d) 收到 Error:checksum mismatch, Last Line: n，发送Nn+1数据。
						 		e) 当gcodeCmdTxFIFO有命令时，优先发送gcodeCmdTxFIFO的命令,并将应答Push到gcodeCmdRxFIFO；
						 3. 任何时候发送命令后，超过5s未收到应答，重复发送该命令，直到收到应答；
						 4. printerStaus状态转移图见《状态转移图_pr》
 * 作者    ：skyblue
**********************************************************************************/


//**#include "draw_ui.h"
#include "mks_tft_com.h"
#include "mks_cfg.h"
//**#include "SZ_STM32F107VC_LIB.h"
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
#include "mks_tft_reprint.h"
#include "draw_printing.h"
#include"at24cxx.h"
//#include "repetier.h"
#include "draw_ui.h"
//#include "HAL.h"

USART2DATATYPE usart2Data;

TFT_FIFO gcodeTxFIFO;			//gcode 数据发送队列
//TFT_FIFO gcodeRxFIFO;			//gcode	数据接收队列

TFT_FIFO gcodeCmdTxFIFO;		//gcode 指令发送队列
TFT_FIFO gcodeCmdRxFIFO;		//gcode	指令接收队列

__IO u16 tftDelayCnt = 0;
__IO u16 fileEndCnt = 0;

unsigned char pauseFlag = 0;
FIREWARE_TYPE firmwareType = marlin;
unsigned char wait_cnt = 0;

unsigned char positionSaveFlag = 0;
unsigned char recover_flag = 0;
extern volatile uint8_t get_temp_flag;

unsigned char SendOneTime = 0;
unsigned char pBuf[4];

extern uint8_t repetier_repint_flag;
static uint8_t M105REC_OK_FLG = 0;

extern uint8_t FanSpeed_bak;

extern CFG_ITMES gCfgItems;
extern unsigned char breakpoint_homeFlag;

void mksUsart2Resend(void);

//**
#define USART_REC_LEN  			200  	
u16 USART_RX_STA=0;      
u8 USART_RX_BUF[USART_REC_LEN];
extern "C" void USART3_IRQHandler(void);   //**

void get_zoffset_value()
{
	uint8_t i,size;
	//chen 8.31 触屏发M851获得zoffset数值echo:Z Offset : -0.15
	if((usart2Data.usart2Txbuf[0] == 'M') 
		&& ((usart2Data.usart2Txbuf[1] == '2' || usart2Data.usart2Txbuf[1] == '8'))
		&& ((usart2Data.usart2Txbuf[2] == '9') ||(usart2Data.usart2Txbuf[2] == '5')) 
		&& ((usart2Data.usart2Txbuf[3] == '0' ) || (usart2Data.usart2Txbuf[3] == '1' ))
		&& (usart2Data.usart2Txbuf[4]=='\n' ||usart2Data.usart2Txbuf[5] == 'Z'))
	{
		if(usart2Data.usart2Rxbuf[0] == 'e' && usart2Data.usart2Rxbuf[1] == 'c' && usart2Data.usart2Rxbuf[2] == 'h' 
			&& usart2Data.usart2Rxbuf[3] == 'o' && usart2Data.usart2Rxbuf[4] == ':' ) //&& usart2Data.usart2Rxbuf[5] == 'Z')
		{
			#if 0
			//换行符号或者超过10个字节则跳出for循环
			//数值在数组下标为16的字节开始
			
			//回复echo:Z Offset : -0.15
			if(usart2Data.usart2Txbuf[4]=='\n')
			{
				for(i=0;i<=10 && usart2Data.usart2Rxbuf[i+16] != '\n' ;i++)
				{
					gCfgItems.disp_zoffset_buf[i] = usart2Data.usart2Rxbuf[i+16];
				}
			}
			//回复echo:Z Offset 0.15
			else
			{
				for(i=0;i<=10 && usart2Data.usart2Rxbuf[i+14] != '\n' ;i++)
				{
					gCfgItems.disp_zoffset_buf[i] = usart2Data.usart2Rxbuf[i+14];
				}
			}
			
			//获得Zoffset数值
			//gCfgItems.zoffsetValue = atof(disp_zoffset_buf);
			//DecStr2Float(disp_zoffset_buf,&gCfgItems.zoffsetValue);
			//加标志位在main中刷新显示
			#else
			size = sizeof(gCfgItems.disp_zoffset_buf)-1;
			for(i=0;i<size && usart2Data.usart2Rxbuf[i+5] != '\n' ;i++)
			{
				gCfgItems.disp_zoffset_buf[i] = usart2Data.usart2Rxbuf[i+5];
			}
			gCfgItems.disp_zoffset_buf[i] = 0;
			#endif
			gCfgItems.zoffset_disp_flag = ENABLE;
			
		}
	}
}
void USART3_IRQHandler(void) 
{

	u8 Res;
	//pBuf[0]=USART_ReceiveData(USART3);
	//if(pBuf[0]==0xff)
	//**USART_SendData(USART3,0xee);

	__disable_irq(); 
	mksUsart2IrqHandlerUser();
	__enable_irq();
	/*if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  
	{
		Res =USART_ReceiveData(USART3);
		
		if((USART_RX_STA&0x8000)==0)
		{
			if(USART_RX_STA&0x4000)
			{
				if(Res!=0x0a)USART_RX_STA=0;
				else USART_RX_STA|=0x8000;	
			}
			else 
			{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;  
				}		 
			}
		}   		 
       } */
	
}



void mksUsart2Resend(void)
{
	//return;									//10s
		//if(usart2Data.timerCnt>(10000/TICK_CYCLE)) 
		//sean 1.15
		if(usart2Data.timerCnt>(15000/TICK_CYCLE)) 
		{
			//if(printerStaus == pr_idle)
			if(printerStaus == pr_idle || printerStaus == pr_reprint)
			{
				usart2Data.timerCnt = 0;	
				usart2Data.prWaitStatus = pr_wait_idle;
				usart2Data.timer = timer_stop;
				return;
			}
			
			if(usart2Data.timer == timer_running && usart2Data.prWaitStatus != pr_wait_idle)	//timer_running=1
			{
				switch(printerStaus)
					{
						case pr_working:	//pr_working = 1
						case pr_pause:		//pr_pause = 2
								//USART2_SR |= 0x0040;	//触发一次发送中断
								usart2TxStart();	
							break;
						case pr_idle:		//pr_idle = 0
								usart2TxStart();	//0303
							break;							//0303
						case pr_stop:		//pr_stop = 3
								//usart2CmdTxStart();
							break;
						default : break;
					}
				}
			usart2Data.timerCnt = 0;	
		}
}

void mksUsart2RepeatTx(void)		
{
		usart2Data.timerCnt++;
	
		if(tftDelayCnt != 0)	tftDelayCnt--;
	
		if(fileEndCnt != 0)		fileEndCnt--;
	
		//mksUsart2Resend();
	/*
		if(ADCConvertedValue < 0x0B60)  //4.7V
		{
			if(printerStaus == pr_working)	
			{
				BACKLIGHT = BACKLIGHT_OFF;	
				__set_PRIMASK(1);				//关闭总中断
				__set_FAULTMASK(1);
				rePrintSaveData();
				__set_PRIMASK(0);			//开放总中断
				__set_FAULTMASK(0);
				BACKLIGHT = BACKLIGHT_ON;				
				
			}
		}
	*/
}

void mksUsart2Polling(void)
{
	unsigned char G28Gode[5]="G28\n";
	unsigned char G92Gode[14]="G92 X0 Y0 Z0\n";
	unsigned char buf[20];

	unsigned char i;  //???

	mksBeeperAlarm();

	if(positionSaveFlag == 1 && printerStaus == pr_pause)		//移动后保存位置
	{
		positionSaveFlag = 0;
		positionSaveProcess();
	}

	//获取Z轴坐标
	if((gCfgItems.getzpos_flg == 1)&&(disp_state == MOVE_MOTOR_UI))
	{
		gCfgItems.getzpos_flg = 0;
		Get_Z_Pos_display_value();
	}

	//chen 10.29
	#if 1
	if(gCfgItems.restart_data_init == 1)
	{
		gCfgItems.restart_data_init = 0;
		Restart_data_init();
	}
	#endif
	mksUsart2Resend();
	
	switch(printerStaus)
	{
		case pr_working:		//pr_working = 1
/*--------------reprint test--------------------*/	
				//if(mksReprintTest()) return;		
/*--------------reprint test--------------------*/	
				RePrintData.printerStatus = printer_normal;
				usart2Data.timer = timer_running;
				heatFlag = 0;
				if(pauseFlag == 1)
				{
					pauseFlag = 0;
					if(RePrintData.saveFlag == SAVE_DIS)
						relocalZ();
					else
						relacalSave();
				}
				//sean 12.24 指令发完，进入printer_waiting状态,可以开始打印
				if((usart2Data.HasSendHomeG28 || usart2Data.HasStopPrintSendG28) &&(usart2Data.printer == printer_waiting))
				{
					usart2Data.printer = printer_idle;
					usart2Data.tick1=0;
					usart2Data.HasStopPrintSendG28 = 0;
					usart2Data.HasSendHomeG28 = 0;
				}
				
				
				switch(usart2Data.printer)
				{
					case printer_idle:				//printer_idle 0
					
								if(usart2Data.HasSendHomeG28==1 || usart2Data.HasStopPrintSendG28==1) //G28回零动作未结束,会返回两个ok,打印状态下指令发送出错
								{
									tftDelay(5);
									usart2Data.tick1++;
									if(usart2Data.tick1 >= 4000)//20s开始打印
									{
										usart2Data.tick1=0;
										usart2Data.HasStopPrintSendG28 = 0;
										usart2Data.HasSendHomeG28 = 0;
									}
									break;
								}
								else
								{
									//sean 12.17 
									usart2Data.tick1 = 0;
									usart2Data.HasSendHomeG28 = 0;
									usart2Data.HasStopPrintSendG28 = 0;
 
									udiskBufferInit();

									//sean 12.17 
									gCfgItems.printSpeed = 100;
									SET_MOVE_SPEED_COMMAND((char *)buf, gCfgItems.printSpeed);
									pushFIFO(&gcodeCmdTxFIFO, buf);
									gCfgItems.printExtSpeed0 = 100;
									SET_EXTRU_SPEED_COMMAND((char *)buf, gCfgItems.printExtSpeed0);
									pushFIFO(&gcodeCmdTxFIFO, buf);
									
									usart2Data.printer = printer_working;
									if(gCfgItems.pwd_reprint_flg == 1)
									{
										gCfgItems.pwd_reprint_flg = 0;
										BreakPointReGcode();
									}
									while(checkFIFO(&gcodeTxFIFO)!= fifo_full)
									{
										//由于repetier固件的原因，发送下面的
										//命令保证在零点位置时坐标为(0,0,0)，
										//但只适用于普通机型。
										if((firmwareType == repetier)&&(gCfgItems.machineType != 2)&&(SendOneTime == 1)&&(repetier_repint_flag == 1))
										{
											repetier_repint_flag = 0;
											SendOneTime = 0;
											pushFIFO(&gcodeTxFIFO,G28Gode);
											pushFIFO(&gcodeTxFIFO,G92Gode);
										}
									
										udiskFileR(srcfp);												//读文件
										pushTxGcode();

										if((srcfp->fsize)<2046)
										{
											break;
										}
										#if debug_flg == 1
										T_function(1200,1);
										#endif
										
									} 
									printerInit();
								}
								break;
					case printer_waiting:			//printer_waiting 2
								//relocalZ();
								usart2Data.printer = printer_working;
								//while(checkFIFO(&gcodeTxFIFO)!= fifo_full)
								for(i=0;i<FIFO_NODE;i++)
								{
									udiskFileR(srcfp);												//读文件
									pushTxGcode();
									if(checkFIFO(&gcodeTxFIFO)== fifo_full) break;
								}
								
								if(popFIFO(&gcodeTxFIFO,&usart2Data.usart2Txbuf[0]) != fifo_empty)	//发送数据
								{	
									usart2Data.prWaitStatus = pr_wait_data;
									usart2TxStart();
								}
						break;
					case printer_working:	//printer_working  1
									udiskFileR(srcfp);
									pushTxGcode();
		
						break;
					default :break;
				}

			break;
		case pr_pause:	//pr_pause = 2
				usart2Data.timer = timer_stop;
		
				if(homeXY()) 	
				{
					pauseFlag = 1;
				}
				rePrintSaveData();     
				if(checkFIFO(&gcodeCmdTxFIFO) !=fifo_empty && usart2Data.prWaitStatus == pr_wait_idle)
				{
					popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]);
					usart2Data.prWaitStatus = pr_wait_cmd;
					usart2TxStart();
				}
				break;
		case pr_idle:		//pr_idle = 0
					if(checkFIFO(&gcodeCmdTxFIFO) !=fifo_empty && usart2Data.prWaitStatus == pr_wait_idle)
						{
							popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]);
							usart2Data.prWaitStatus = pr_wait_cmd;
							usart2Data.timer = timer_running;	//0303
							usart2TxStart();
						}				
					break;
		case pr_stop:		//pr_stop = 3
					
					
					udiskFileStaus = udisk_file_end;
					printerStaus = pr_idle;		//打印结束
					usart2Data.printer = printer_idle;
					usart2Data.prWaitStatus = pr_wait_idle;
					usart2Data.timer = timer_stop;						//清除定时器
					
					//tftDelay(3);
					//printerInit();
					//tftDelay(2);

					//**I2C_EE_Init(100000);
					MX_I2C1_Init(100000);
					HAL::AT24CXX_Read(BAK_REPRINT_INFO, (uint8_t *)&dataToEeprom,  4);
					dataToEeprom &= 0x00ffffff;
					dataToEeprom |= (uint32_t)(printer_normal << 24 ) & 0xff000000;
					HAL::AT24CXX_Write(BAK_REPRINT_INFO, (uint8_t *)&dataToEeprom,  4); 		// 续打标志(uint8_t) | 单位unit (uint8_t) | saveFlag(uint8_t)| null(uint8_t)
		
					printerStop();
					//sean 12.20
					usart2Data.HasStopPrintSendG28 = 1;

					break;
		
		case pr_reprint:		//续打
				//if(checkFIFO(&gcodeCmdTxFIFO) !=fifo_empty && usart2Data.prWaitStatus == pr_wait_idle)
				//{
				//	popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]);
				//	usart2Data.prWaitStatus = pr_wait_cmd;
				//	usart2Data.timer = timer_running;	//**
				//	usart2TxStart();
				//}
				break;
		case breakpoint_reprint:
				if(breakpoint_homeXY()) 	
				{
					gcodeLineCnt = 0;
				}
				if(checkFIFO(&gcodeCmdTxFIFO) !=fifo_empty && usart2Data.prWaitStatus == pr_wait_idle)
				{
					popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]);
					usart2Data.prWaitStatus = pr_wait_cmd;
					usart2TxStart();
				}				
				if(gCfgItems.findpoint_start == 1)
				{
					if(breakpoint_fixPositionZ())
					{
						gCfgItems.findpoint_start = 0;
						breakpoint_homeFlag = 0;
						//BreakPointReGcode();
						Get_Temperature_Flg = 1;
						get_temp_flag = 1;
						MX_I2C1_Init(400000);
						start_print_time();
						reset_print_time();
						usart2Data.printer = printer_idle;
						printerStaus = pr_working;			
						//gCfgItems.pwd_reprint_flg = 0;
						
					}
				}
			break;
			
		default : break;
			
	}
}


void mksUsart2Init(void)
{
		firmwareType = marlin;
		wait_cnt = 0;

		usart2Data.rxP = &usart2Data.usart2Rxbuf[0];
		usart2Data.txP = &usart2Data.usart2Txbuf[0];
		usart2Data.txBase = usart2Data.txP;
		usart2Data.printer = printer_idle;
		usart2Data.timer = timer_stop;
		usart2Data.prWaitStatus = pr_wait_idle;
		USART2_SR &= 0xffbf;		//清除中断标志位
		USART2_SR &= 0xffdf;
		USART2_CR1 |= 0x40;			//发送完成中断允许
		USART2_SR &= 0xffbf;		//清除中断标志位

		RePrintData.saveFlag = SAVE_DIS;
		
		udiskBufferInit();
	
		rePrintInit();

		//sean 12.17
		usart2Data.HasSendHomeG28 = 0;
		usart2Data.HasStopPrintSendG28 = 0;
		usart2Data.tick1 = 0;
		
}

void mksUsart2IrqHandlerUser(void)
{
		unsigned char i;
		if( USART2_SR & 0x0020)	//rx 
		{
				*(usart2Data.rxP++) = USART2_DR & 0xff;
				USART2_SR &= 0xffdf;
			
				if(*(usart2Data.rxP-1) == '\n')		//0x0A 收到结束符
				{				
					if(RePrintData.saveEnable)	getSavePosition();
					if(gCfgItems.getzpos_enable == 1) getZPosition();//移动界面的Z轴显示值
					if(usart2Data.usart2Rxbuf[0] =='w' &&  usart2Data.usart2Rxbuf[1] =='a' && usart2Data.usart2Rxbuf[2] =='i' &&  usart2Data.usart2Rxbuf[3] =='t')
					{	//repetier 去掉接收到的 wait 字符
						usart2Data.rxP = &usart2Data.usart2Rxbuf[0];
						wait_cnt++;
						if(wait_cnt > 2)
							firmwareType = repetier;
					}
					else
						{
							wait_cnt = 0;
							//if(firmwareType != repetier)
								usart2Data.timerCnt = 0; //定时器清零
							switch(printerStaus)
							{
								case pr_reprint:
								case pr_working:	//打印中 pr_working = 1
								case pr_pause:  //暂停 pr_pause = 2
										switch(usart2Data.prWaitStatus)
										{
											case pr_wait_idle:			//0
												pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);	//reretier
												break;
											case pr_wait_cmd:			//pr_wait_cmd=1 	命令队列等待回应
												if((firmwareType == repetier))
												{
													//在repetier固件里，对下面命令做接收完成响应之后才发
													//下一条命令。
													//M105
													if((usart2Data.usart2Txbuf[0] == 'M')&&(usart2Data.usart2Txbuf[1] == '1')\
													&&(usart2Data.usart2Txbuf[2] == '0')&&(usart2Data.usart2Txbuf[3] == '5'))
													{
															pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);
															//防止在加热的时候不断发下一条命令
															if(usart2Data.usart2Rxbuf[0] =='o' &&  usart2Data.usart2Rxbuf[1] =='k')
															{
																	M105REC_OK_FLG=1;
															}
															//M105:
															if((M105REC_OK_FLG == 1)&&(usart2Data.usart2Rxbuf[0] =='T' &&  usart2Data.usart2Rxbuf[1] ==':'))
															{
																M105REC_OK_FLG=0;
																usart2Data.prWaitStatus = pr_wait_idle;
																prTxNext();
															}												
													}
													//M104/M109/M140/M190
													else if((usart2Data.usart2Txbuf[0] == 'M')&&(usart2Data.usart2Txbuf[1] == '1')\
													&&((usart2Data.usart2Txbuf[2] == '0')||(usart2Data.usart2Txbuf[2] == '4')\
													||(usart2Data.usart2Txbuf[2] == '9'))\
													&&((usart2Data.usart2Txbuf[3] == '0')||(usart2Data.usart2Txbuf[3] == '4')\
													||(usart2Data.usart2Txbuf[3] == '9')))
													{
														pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);
														if((usart2Data.usart2Rxbuf[0] =='T')&&(usart2Data.usart2Rxbuf[1] =='a'))
														{
																usart2Data.prWaitStatus = pr_wait_idle;
																prTxNext();
														}
													}
													//M106/M107
													else if((usart2Data.usart2Txbuf[0] == 'M')&&(usart2Data.usart2Txbuf[1] == '1')\
													&&(usart2Data.usart2Txbuf[2] == '0')&&((usart2Data.usart2Txbuf[3] == '7')\
													||(usart2Data.usart2Txbuf[3] == '6'))&&(FanSpeed_bak != gCfgItems.fanSpeed))
													{
														pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);
														if(usart2Data.usart2Rxbuf[0] =='F' &&  usart2Data.usart2Rxbuf[1] =='a')
														{
															usart2Data.prWaitStatus = pr_wait_idle;
															prTxNext();
														}
													}
													else
													{	
														pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);
														//M105:
														if(usart2Data.usart2Rxbuf[0] =='o' &&  usart2Data.usart2Rxbuf[1] =='k')
														{
															usart2Data.prWaitStatus = pr_wait_idle;
															prTxNext();
														}
													}
													
												}
												else
												{
													get_zoffset_value();
													pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);
													//M105:
													if(usart2Data.usart2Rxbuf[0] =='o' &&  usart2Data.usart2Rxbuf[1] =='k')
													{
														usart2Data.prWaitStatus = pr_wait_idle;
														prTxNext();
													}
												}												
												break;
											case pr_wait_data:

												if(firmwareType != repetier)
												{
													if(resendProcess()) break;
												}
												else
												{
													if(resendProcess_repetier()) break;
												}
												
												if(usart2Data.usart2Rxbuf[0] =='o' &&  usart2Data.usart2Rxbuf[1] =='k')	
												{
													if(recOkProcess()) 
													{
														usart2Data.resendCnt = 0;
														usart2Data.prWaitStatus = pr_wait_idle;
														prTxNext();
													}
													else	//ok : T xxx
														pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);
												}
												else //收到其他，push 到CMD队列 非OK
													pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);
												
												break;
											default : break;
										} //switch(usart2Data.prWaitStatus) 
									break;
								case pr_idle:		//	pr_idle=0				//非打印中 ,发送命令由外部查询gcodeCmdTxFIFO非空，启动发送
								case pr_stop:		//	pr_stop=3
										if(usart2Data.usart2Rxbuf[0] =='o' &&  usart2Data.usart2Rxbuf[1] =='k')
										{
											usart2Data.prWaitStatus = pr_wait_idle;
											usart2Data.timer = timer_stop;		//0303
											//sean 12.17
											if((usart2Data.usart2Txbuf[0] =='G' &&  usart2Data.usart2Txbuf[1] =='2' && usart2Data.usart2Txbuf[2] =='8' && usart2Data.HasSendHomeG28 ==1)
												|| (usart2Data.usart2Txbuf[0] =='N' &&  usart2Data.usart2Txbuf[1] =='-' && usart2Data.usart2Txbuf[2] =='1' && usart2Data.HasStopPrintSendG28 == 1))
											{
												usart2Data.HasStopPrintSendG28 = 0;
												usart2Data.HasSendHomeG28 = 0;
											}
										}
										pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);
										break;							
								default :break;															
								}//switch(printerStaus)

								usart2Data.rxP = &usart2Data.usart2Rxbuf[0];
							//memset(&usart2Data.usart2Rxbuf[0],0,sizeof(usart2Data.usart2Rxbuf));		//test_add
						}
				}
				if(usart2Data.rxP >= &usart2Data.usart2Rxbuf[0] + USART2BUFSIZE-1)
					usart2Data.rxP = &usart2Data.usart2Rxbuf[0];
			
		}

		
		if(USART2_SR & 0x0040)	//tx
		{
			USART2_SR &= 0xffbf;

			if(usart2Data.txP >= usart2Data.txBase + USART2BUFSIZE-1)
			{
				usart2Data.txP = usart2Data.txBase;
				return;
			}
			
			if(*usart2Data.txP != '\r')
			{
				USART2_DR = *(usart2Data.txP++);
				while(!(USART2_SR & 0x0040));
			}

			if(*usart2Data.txP =='\n')
				*(usart2Data.txP+1) = '\r';
			
		}		

		if(USART2_SR & 0x0008)
		{
				*(usart2Data.rxP++) = USART2_DR & 0xff;
				USART2_SR &= 0xffdf;			
		}
	
}
