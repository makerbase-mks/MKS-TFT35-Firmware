/********************   (C) COPYRIGHT 2014 www.makerbase.com.cn   ********************
 * 文件名  ：mks_tft_com.h
 * 描述    ：通信模块接口定义
 * 作者    : skyblue/menson
 1.NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x7000);
 2.Start 0x8007000  size 0x39000 
 3.LEVEL-3 
 4.fromelf  --bin  -o   ./out/mkstft28.bin  ./out/mkstft28.axf
**********************************************************************************/
#ifndef MKS_TFT_COM_H
#define MKS_TFT_COM_H

#ifdef __cplusplus
 extern "C" {
#endif

#define debug_flg	0			//���ڲ��Ե������������

#define TESTMODE 0		//1 测试模式；0 工作模式

/* Includes ------------------------------------------------------------------*/
//**#include "stm32f10x.h"
#include <stdio.h>
#include "mks_tft_fifo.h"
#include "ff.h"
#include "mks_tft_gcode.h"
#include "MKS_USART2_IT.h"
#include "mks_tft_protocol.h"
#include "mks_tft_function.h"
#include "mks_tft_reprint.h"
#include "mks_tft_test.h"
#include "mks_tft_adc.h"
//**#include "Printer.h"

// #define NVIC_VectTab_MKSTFT28 0x08007000	 
/* data type ------------------------------------------------------------------*/	 
typedef enum
{
	pr_idle = 0,			//打印机空闲		
	pr_working,					//打印机忙			
	pr_pause,					//打印机暂停
	pr_stop,					//打印机停止
	pr_reprint,				//暂停续打或断电续打
	breakpoint_reprint,//�ϵ�������
} PR_STATUS;

typedef struct
{
	unsigned int bedTemp;		//热床目标温度
	unsigned int t0Temp;		//打印头1目标温度
	unsigned int t1Temp;		//打印头2目标温度
	unsigned int t2Temp;		//打印头3目标温度
}TARGER_TEMP;


extern PR_STATUS printerStaus;		//打印机工作状态
extern TARGER_TEMP targetTemp; 		//打印机热床、打印头目标温度

extern FIL *srcfp;	 							//U盘或SD卡文件指针
extern TFT_FIFO gcodeCmdTxFIFO;		//gcode 指令发送队列
extern TFT_FIFO gcodeCmdRxFIFO;		//gcode	指令接收队列

extern unsigned char positionSaveFlag;	// 1: save    0 : none

extern uint8_t Get_Temperature_Flg;

/* function ------------------------------------------------------------------*/
extern void mksUsart2RepeatTx(void);		//USART2	没有收到回复，定时重发，放在SysTick_Handler_User函数中
extern void mksUsart2Init(void);			//USART2 初始化补充，在SZ_STM32_COMInit(COM2, 115200),之后执行一次
extern void mksUsart2Polling(void);		//轮询函数，为保证实时性，放在 n ms 的定时中断中
extern void mksUsart2IrqHandlerUser(void);	//USART2中断服务函数，放入void USART2_IRQHandler(void) ，并将原中断服务函数屏蔽

/* note ------------------------------------------------------------------
1. 打印触发
		打印开始，设置
									printerStaus = pr_working;
									srcfp = fopen();
		打印结束，返回 
									printerStaus = pr_idle;

2. 发送指令
						pushFIFO(&gcodeCmdTxFIFO,&cmdTxBuf[0]);
	 返回
						if(popFIFO(&gcodeCmdRxFIFO,&cmdRxBuf[0]) == fifo_ok)
*/

#define TICK_CYCLE		1 //ms   

#ifdef __cplusplus
}
#endif

#endif
