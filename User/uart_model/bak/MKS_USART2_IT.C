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


#include "draw_ui.h"
#include "mks_tft_com.h"

USART2DATATYPE usart2Data;

TFT_FIFO gcodeTxFIFO;			//gcode 数据发送队列
//TFT_FIFO gcodeRxFIFO;			//gcode	数据接收队列

TFT_FIFO gcodeCmdTxFIFO;		//gcode 指令发送队列
TFT_FIFO gcodeCmdRxFIFO;		//gcode	指令接收队列

__IO u16 tftDelayCnt = 0;
 
unsigned char pauseFlag = 0;
FIREWARE_TYPE firmwareType = marlin;
unsigned char wait_cnt = 0;

unsigned char positionSaveFlag = 0;


void mksUsart2Resend(void);

void mksUsart2Resend(void)
{
	//return;									//10s
		if(usart2Data.timerCnt>(10000/TICK_CYCLE)) 
		{
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
	unsigned char i;  //???

	mksBeeperAlarm();

	if(positionSaveFlag == 1 && printerStaus == pr_pause)		//移动后保存位置
		{
		positionSaveFlag = 0;
		positionSaveProcess();
		}
	
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
				
				
				switch(usart2Data.printer)
				{
					case printer_idle:				//printer_idle 0
								udiskBufferInit();
								usart2Data.printer = printer_working;
								while(checkFIFO(&gcodeTxFIFO)!= fifo_full)
								{
									udiskFileR(srcfp);												//读文件
									pushTxGcode();
									if(udiskFileStaus == udisk_file_end) 
									{
										while(printerStaus != pr_idle)
										{
											udiskFileR(srcfp);
										}
										break;
									}

								}
								printerInit();
								break;
					case printer_waiting:			//printer_waiting 2
								//relocalZ();
								usart2Data.printer = printer_working;
								while(checkFIFO(&gcodeTxFIFO)!= fifo_full)
								{
									udiskFileR(srcfp);												//读文件
									pushGcode();
									if(udiskFileStaus == udisk_file_end) 
									{
										while(printerStaus != pr_idle)
										{
											udiskFileR(srcfp);
										}
										break;
									}	
								}
								if(popFIFO(&gcodeTxFIFO,&usart2Data.usart2Txbuf[0]) != fifo_empty)	//发送数据
								{
									usart2Data.prWaitStatus = pr_wait_data;
									usart2TxStart();
								}
						break;
					case printer_working:	//printer_working  1
									udiskFileR(srcfp);
									pushGcode();			
						break;
					default :break;
				}
			break;
		case pr_pause:	//pr_pause = 2
				usart2Data.timer = timer_stop;
		
				if(homeXY()) 	pauseFlag = 1;
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
					I2C_EE_BufferRead(&dataToEeprom, BAK_REPRINT_INFO,  4);
					dataToEeprom &= 0x00ffffff;
					dataToEeprom |= (uint32_t)(printer_normal << 24 ) & 0xff000000;
					I2C_EE_BufferWrite(&dataToEeprom, BAK_REPRINT_INFO,  4); 		// 续打标志(uint8_t) | 单位unit (uint8_t) | saveFlag(uint8_t)| null(uint8_t)
		
					printerStop();

					break;
		
		case pr_reprint:		//续打
				rePrintProcess();
				//printerStaus = pr_working;		//print test
				//usart2Data.printer = printer_waiting;
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
							if(firmwareType != repetier)
								usart2Data.timerCnt = 0; //定时器清零
							switch(printerStaus)
							{
								case pr_working:	//打印中 pr_working = 1
								case pr_pause:  //暂停 pr_pause = 2
										switch(usart2Data.prWaitStatus)
										{
											case pr_wait_idle:			//0
												pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);	//reretier
												break;
											case pr_wait_cmd:			//pr_wait_cmd=1 	命令队列等待回应
												pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);
												//M105:
												if(usart2Data.usart2Rxbuf[0] =='o' &&  usart2Data.usart2Rxbuf[1] =='k')
												{
													usart2Data.prWaitStatus = pr_wait_idle;
													prTxNext();
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
				USART2_DR = *(usart2Data.txP++);

			if(*usart2Data.txP =='\n')
				*(usart2Data.txP+1) = '\r';
			
		}
	
}
