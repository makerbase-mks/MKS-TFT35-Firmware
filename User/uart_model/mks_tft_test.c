
#include "mks_tft_com.h"
#include "stm32f4xx_rcc.h"
#include "repetier.h"
//#include "HAL.h"
#include "mks_cfg.h"

unsigned long mksTestCnt = 1;
unsigned char testTxBuf[10]={'M','1','0','5','\n'};
unsigned char testRxBuf[100];

/*
void mksCmdTest(void)
{
		if(mksTestCnt%100 == 0 )		//5s
		{
			pushFIFO(&gcodeCmdTxFIFO,&testTxBuf[0]);
			memset(&testRxBuf[0],0,sizeof(testRxBuf));
			
			while(popFIFO(&gcodeCmdRxFIFO,&testRxBuf[0]) == fifo_ok);		
				

		}
		mksTestCnt++;	
}
*/
void mksPB01Test(void)
{
	unsigned char inData=0;
//#define MKS_PWRDN PBin(0)
//#define MKS_MTRDN PBin(1)
	inData = MKS_PWRDN;
	inData = MKS_MTRDN;

	inData = MKS_PWRDN;
	inData = MKS_MTRDN;

	inData = MKS_PWRDN;
	inData = MKS_MTRDN;
	
}

/*void mksLEDTest(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	tftGPIOCfg();
	
	BACKLIGHT = BACKLIGHT_ON;
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOD, ENABLE );	 //PORTAÊ±ÖÓÊ¹ÄÜ 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_7;		//LED1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	MKSLED1 = MKSLED2 =MKSLED3 =MKSLED4 = 1;
	
}*/



unsigned char mksReprintTest(void)
{
		uint32_t dataFrEeprom=0xc1c2c3c4;
		unsigned long eepromTest;	
	
		HAL::AT24CXX_Read(BAK_REPRINT_INFO,(uint8_t *)&dataFrEeprom,4);
		eepromTest = dataFrEeprom;

		HAL::AT24CXX_Read(BAK_REPRINT_X,(uint8_t *)&dataFrEeprom,4);
		eepromTest = dataFrEeprom;
		HAL::AT24CXX_Read(BAK_REPRINT_Y,(uint8_t *)&dataFrEeprom,4);
		eepromTest = dataFrEeprom;	
		HAL::AT24CXX_Read(BAK_REPRINT_Z,(uint8_t *)&dataFrEeprom,4);
		eepromTest = dataFrEeprom;

		return 0;
			
		if(RePrintData.printerStatus	!= 0xff) 
			return 0;
	
		HAL::AT24CXX_Read(BAK_REPRINT_INFO,(uint8_t *)&dataFrEeprom,4);
	
		dataFrEeprom >>= 24;
		dataFrEeprom &= 0xff;
		if(dataFrEeprom == 0xa7 | dataFrEeprom == 0xa8)
		{
			printerStaus = pr_reprint;
			return 1;
		}
		else
			return 0;
}

