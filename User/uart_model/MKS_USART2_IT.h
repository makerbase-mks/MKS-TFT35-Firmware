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

#ifndef MKS_USART2_IT_H
#define MKS_USART2_IT_H
/* Includes ------------------------------------------------------------------*/
//**#include "stm32f10x.h"
#include <stdio.h>
#include "mks_tft_fifo.h"
//#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

//#define USART2_SR		*(__IO uint16_t *)0x40004400
//#define USART2_SR		*(__IO uint16_t *)&USART3->SR
#define USART2_SR		*(__IO uint16_t *)0x40004800
//#define USART2_DR		*(__IO uint16_t *)0x40004404
//#define USART2_DR		*(__IO uint16_t *)&USART3->DR
#define USART2_DR		*(__IO uint16_t *)0x40004804
//#define USART2_CR1	       *(__IO uint16_t *)0x4000440C
//#define USART2_CR1	       *(__IO uint16_t *)&USART3->CR1
#define USART2_CR1	       *(__IO uint16_t *)0x4000480C
	 
#define USART2BUFSIZE	FIFO_SIZE
//20150912
#define FIFO_NODE_CNT	10

#define usart2PreTxStart()	do{\
													usart2Data.txP = &usart2Data.usart2Txbak[0];\
													usart2Data.timerCnt=1;\
													usart2Data.timer = timer_running;\
													USART2_DR = *(usart2Data.txP++);\
													}while(0)

													
/*	 
#define usart2TxStart()	do{\
													if(usart2Data.uart2Staus == uart2_idle){\
													usart2Data.txP = &usart2Data.usart2Txbuf[0];\
													usart2Data.txBase = &usart2Data.usart2Txbuf[0];\
													usart2Data.uart2Staus = uart2_busy;\
													usart2Data.timerCnt=1;\
													usart2Data.timer = timer_running;\
													USART2_DR = *(usart2Data.txP++);}\
													}while(0)
*/	
/*
#define usart2CmdTxStart()	do{\
													usart2Data.txP = &usart2Data.usart2CmdTxbuf[0];\
													usart2Data.txBase = &usart2Data.usart2CmdTxbuf[0];\
													usart2Data.timerCnt=1;\
													usart2Data.timer = timer_running;\
													USART2_DR = *(usart2Data.txP++);\
													}while(0)
*/	 

#define pushGcode() do{\
										switch(udiskFileStaus){\
												case udisk_file_ok:\
												case udisk_file_end:\
													for(i=0;i<FIFO_NODE_CNT;i++)\
															pushTxGcode();break;\
												default :break;}\
											}while(0)
/*		
#define printerInit() do{\
								usart2Data.usart2Txbuf[0]='N';usart2Data.usart2Txbuf[1]='-';usart2Data.usart2Txbuf[2]='1';usart2Data.usart2Txbuf[3]=' ';\
								usart2Data.usart2Txbuf[4]='M';usart2Data.usart2Txbuf[5]='1';usart2Data.usart2Txbuf[6]='1';usart2Data.usart2Txbuf[7]='0';\
								usart2Data.usart2Txbuf[8]='*';usart2Data.usart2Txbuf[9]='1';usart2Data.usart2Txbuf[10]='5';usart2Data.usart2Txbuf[11]='\n';\
								usart2TxStart();\
								}while(0)
*/											
typedef enum
{
	timer_stop = 0,		// 	usart2 定时器停止
	timer_running,		//	usart2 定时器运行
} UART2_TIMER_STATUS;

typedef enum
{
	uart2_idle = 0,		// 	usart2 空闲
	uart2_busy,				//	usart2 正在发送数据
} UART2_STATUS;
	 
typedef enum
{
	ok_waiting = 0,		// 	
	ok_received,
} OK_STATUS;



typedef enum
{
	pr_wait_idle = 0,		// 	
	pr_wait_cmd,
	pr_wait_data,
} PR_WAIT_STATUS;


typedef enum
{
	printer_idle = 0,				// 	 打印机空闲
	printer_working,					//	 打印机工作中
	printer_waiting,				//	  打印中，发送队列空，等待
} PRINTER_STATUS;

typedef enum
{
	receive_ok = 0,				// 	 接收信令正常
	receive_Resend,				//	 接收到Resend
	receive_ErrLin,				//	   Error:Line Number is not Last Line Number+1, Last Line: 1
	receive_ErrChk,					//		 Error:checksum mismatch, Last Line: 3
	receive_Unknown,
	receive_PreTx,
} RECEIVE_STATUS;

typedef enum
{
	resend_idle = 0,
	resend_ready,
	resend_end,
}RESEND_STATUS;

typedef enum
{
	marlin = 0,
	smoothie,
	repetier,
}FIREWARE_TYPE;



typedef struct 
{
	unsigned char usart2Rxbuf[USART2BUFSIZE];		//串口接收缓存区
	unsigned char *rxP;				//串口接收指针
	unsigned char usart2Txbuf[USART2BUFSIZE];		//串口发送数据缓存区
	unsigned char *txP;				//串口发送指针
	unsigned char *txBase;
	unsigned char usart2Txbak[USART2BUFSIZE];		//保存串口发送的上一帧数据
	UART2_TIMER_STATUS timer;	
	unsigned int	timerCnt;
	unsigned char resendLine;
	unsigned char curLine;
	unsigned char resendCnt;
	PRINTER_STATUS printer;		// 打印机工作状态
	RESEND_STATUS resendFlag;
	PR_WAIT_STATUS prWaitStatus;

	//sean 12.17
	unsigned char HasSendHomeG28;
	unsigned char HasStopPrintSendG28;
	uint32_t tick1;
}USART2DATATYPE;

extern void mksUsart2RepeatTx(void);
extern void mksUsart2Polling(void);
extern void mksUsart2Init(void);
extern void mksUsart2IrqHandlerUser(void);	 


extern USART2DATATYPE usart2Data;
extern __IO u16 tftDelayCnt;
extern __IO u16 fileEndCnt;
extern TFT_FIFO gcodeTxFIFO;			//gcode 数据发送队列
//extern TFT_FIFO gcodeRxFIFO;			//gcode	数据接收队列

extern TFT_FIFO gcodeCmdTxFIFO;		//gcode 指令发送队列
extern TFT_FIFO gcodeCmdRxFIFO;		//gcode	指令接收队列

extern FIREWARE_TYPE firmwareType;


#ifdef __cplusplus
}
#endif


#endif
