/**
  ******************************************************************************
  * @file    stm3210e_eval_lcd.c
  * @author  ARMJISHU Application Team
  * @version 
  * @date    
  * @brief   This file includes the LCD driver for AM-240320L8TNQW00H 
  *          (LCD_ILI9320) and AM-240320LDTNQW00H (LCD_SPFD5408B) Liquid Crystal
  *          Display Module of STM3210E-EVAL board.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x.h"
#include "stm32f4xx.h" //skyblue 2006-12-13
#include "stm32f4xx_fsmc.h"   //skyblue
//#include "fsmc.h"       //skyblue 2006-12-13
#include "ili9320.h"
#include "ili9320_font.h"
#include <stdio.h>
#include "gpio.h"    //**
#include "mks_cfg.h"

u16 DeviceCode;



/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  vu16 LCD_REG;
  vu16 LCD_RAM;
} LCD_TypeDef;

/* LCD is connected to the FSMC_Bank1_NOR/SRAM4 and NE4 is used as ship select signal */
//**#define LCD_BASE        ((u32)(0x6C000000 | 0x0000007E))	//skyblue       //A6,NE4
//**#define LCD_BASE           ((uint32_t)(0x60000000 | 0x0C000000))                //A0,NE4
#define LCD_BASE           ((uint32_t)(0x60000000 | 0x0003FFFE))              //A17,NE1

#define LCD         ((LCD_TypeDef *) LCD_BASE)

#define SetCs  
#define ClrCs  

//#define SetCs  GPIO_SetBits(GPIOG, GPIO_Pin_12);
//#define ClrCs  GPIO_ResetBits(GPIOG, GPIO_Pin_12);

//#define SetCs  GPIO_SetBits(GPIOB, GPIO_Pin_8);
//#define ClrCs  GPIO_ResetBits(GPIOB, GPIO_Pin_8);


#define  HDP  799  //Horizontal Display Period     //**
#define  HT   1000 //Horizontal Total
#define  HPS  51  //LLINE Pulse Start Position
#define  LPS  3   //	Horizontal Display Period Start Position
#define  HPW  8   //	LLINE Pulse Width


#define  VDP  479	//Vertical Display Period
#define  VT   530	//Vertical Total
#define  VPS  24	//	LFRAME Pulse Start Position
#define  FPS  23	//Vertical Display Period Start Positio
#define  VPW  3 	// LFRAME Pulse Width     //**

#define MAX_HZ_POSX HDP+1
#define MAX_HZ_POSY VDP+1 


//LCD分辨率设置
#define SSD_HOR_RESOLUTION		800		//LCD水平分辨率
#define SSD_VER_RESOLUTION		480		//LCD垂直分辨率
//LCD驱动参数设置
#define SSD_HOR_PULSE_WIDTH		1		//水平脉宽
#define SSD_HOR_BACK_PORCH		46		//水平前廊
#define SSD_HOR_FRONT_PORCH		210		//水平后廊

#define SSD_VER_PULSE_WIDTH		1		//垂直脉宽
#define SSD_VER_BACK_PORCH		23		//垂直前廊
#define SSD_VER_FRONT_PORCH		22		//垂直前廊
//如下几个参数，自动计算
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

//skyblue add begin
void RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB1_CLOCK_PERIPH(RCC_AHB1Periph));

  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->AHB1ENR |= RCC_AHB1Periph;
  }
  else
  {
    RCC->AHB1ENR &= ~RCC_AHB1Periph;
  }
}

void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}

void RCC_AHB3PeriphClockCmd(uint32_t RCC_AHB3Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB3_PERIPH(RCC_AHB3Periph));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHB3ENR |= RCC_AHB3Periph;
  }
  else
  {
    RCC->AHB3ENR &= ~RCC_AHB3Periph;
  }
}

void GPIO_Init_TFT(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef_TFT* GPIO_InitStruct)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

  /* ------------------------- Configure the port pins ---------------- */
  /*-- GPIO Mode Configuration --*/
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

    if (currentpin == pos)
    {
      GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
      GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

      if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
        /* Check Speed mode parameters */
        assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

        /* Speed mode configuration */
        GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
        GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

        /* Check Output mode parameters */
        assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

        /* Output mode configuration*/
        GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos)) ;
        GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
      }

      /* Pull-up Pull down resistor configuration*/
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
      GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
    }
  }
}
#if 0
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
  uint32_t temp = 0x00;
  uint32_t temp_2 = 0x00;
  
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  assert_param(IS_GPIO_AF(GPIO_AF));
  
  temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
  GPIOx->AFR[GPIO_PinSource >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
  temp_2 = GPIOx->AFR[GPIO_PinSource >> 0x03] | temp;
  GPIOx->AFR[GPIO_PinSource >> 0x03] = temp_2;
}
#endif
//skyblue add end
////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
* Description    : Configures LCD Control lines (FSMC Pins) in alternate function
                   Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CtrlLinesConfig(void)
{
	vu32 i=0;
	volatile unsigned long delayCnt=0;
	
  GPIO_InitTypeDef_TFT  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG, ENABLE);//使能PD,PE,PF,PG时钟  
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);//使能FSMC时钟  
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;//PB15 推挽输出,控制背光
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init_TFT(GPIOD, &GPIO_InitStructure);//初始化 //PB15 推挽输出,控制背光
  
  /*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PA6 推挽输出  //////**
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init_TFT(GPIOA, &GPIO_InitStructure);//初始化 //PA6 推挽输出*/
	//**Lcd_Light_ON;

	Lcd_RESET();
        //PAout(6)=0;
	//HAL_Delay(50);
        for(delayCnt=0;delayCnt<10000;delayCnt++);
        //HAL_Delay(500);
	Lcd_SET();
	
  GPIO_InitStructure.GPIO_Pin = (3<<0)|(3<<4)|(7<<8)|(3<<14);//PD0,1,4,5,8,9,10,14,15 AF OUT
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init_TFT(GPIOD, &GPIO_InitStructure);//初始化  
	
  GPIO_InitStructure.GPIO_Pin = (0X1FF<<7);//PE7~15,AF OUT
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init_TFT(GPIOE, &GPIO_InitStructure);//初始化
  // HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);

	//**GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PF12,FSMC_A6
        //**GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PF0,FSMC_A0
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PD12,FSMC_A17
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  //**GPIO_Init_TFT(GPIOF, &GPIO_InitStructure);//初始化
  GPIO_Init_TFT(GPIOD, &GPIO_InitStructure);//初始化    //**


	//**GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PG12,FSMC_NE4
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PD7,FSMC_NE1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init_TFT(GPIOD, &GPIO_InitStructure);//初始化 

  GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);//PD0,AF12
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);//PD1,AF12
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC); 
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC); 
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);//PD15,AF12
 
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);//PE7,AF12
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);//PE15,AF12
  //**GPIO_PinAFConfig(GPIOF,GPIO_PinSource12,GPIO_AF_FSMC);//PF12,AF12
  //**GPIO_PinAFConfig(GPIOF,GPIO_PinSource0,GPIO_AF_FSMC);//PF0,AF0
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_FSMC);//PD12,AF17     //**
  //**GPIO_PinAFConfig(GPIOG,GPIO_PinSource12,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource7,GPIO_AF_FSMC);          //NE1      //**
#if 0	
#endif //#if 0


  
}

/*******************************************************************************
* Function Name  : LCD_FSMCConfig
* Description    : Configures the Parallel interface (FSMC) for LCD(Parallel mode)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_FSMCConfig(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
  
  readWriteTiming.FSMC_AddressSetupTime = 0XF;	 //地址建立时间（ADDSET）为16个HCLK 1/168M=6ns*16=96ns	
  readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
  readWriteTiming.FSMC_DataSetupTime = 60;			//数据保存时间为60个HCLK	=6*60=360ns
  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
  readWriteTiming.FSMC_CLKDivision = 0x00;
  readWriteTiming.FSMC_DataLatency = 0x00;
  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
    

	writeTiming.FSMC_AddressSetupTime =9;	      //地址建立时间（ADDSET）为9个HCLK =54ns 
  writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（A		
  writeTiming.FSMC_DataSetupTime = 8;		 //数据保存时间为6ns*9个HCLK=54ns
  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
  writeTiming.FSMC_CLKDivision = 0x00;
  writeTiming.FSMC_DataLatency = 0x00;
  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 

 
  //**FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;                                                  //**
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // 不复用数据地址
  FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit   
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  存储器写使能
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // 读写使用不同的时序
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //读写时序
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //写时序

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

  //**FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK1 
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  // 使能BANK1 
}


void LCD_X_Init(void)
{
 /* Configure the LCD Control pins --------------------------------------------*/
  LCD_CtrlLinesConfig();

/* Configure the FSMC Parallel interface -------------------------------------*/
  LCD_FSMCConfig();


  
  
}

u16 ILI9488_ReadRAM()
{
  u16 data;	  /* Write 16-bit Index (then Read Reg) */
  data = LCD->LCD_RAM; 
  return    data;
}
u16 ILI9488_WriteData(u16 data)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_RAM = data; 
}
void ILI9488_WriteCmd(u16 LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  LCD->LCD_REG = LCD_RegValue;
}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  ClrCs
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD->LCD_RAM = LCD_RegValue;
  SetCs
}
void LCD_WrtReg(u16 LCD_Reg)
{
  /* Write 16-bit Index, then Write Reg */
  //ClrCs
  LCD_Reg=LCD_Reg;
  LCD->LCD_REG = LCD_Reg;
  //SetCs
}
/*******************************************************************************
* Function Name  : LCD_ReadReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
*******************************************************************************/
u16 LCD_ReadReg(u8 LCD_Reg)
{
  u16 data;	  /* Write 16-bit Index (then Read Reg) */
  ClrCs
  //LCD->LCD_REG = LCD_Reg;
  data = LCD->LCD_RAM; 
    SetCs
     return    data;
}

u16 LCD_ReadSta(void)
{
  u16 data;
  /* Write 16-bit Index, then Write Reg */
  ClrCs
  data = LCD->LCD_REG;
  SetCs
  return    data;
}

void LCD_WriteCommand(u16 LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  ClrCs
  LCD->LCD_REG = LCD_RegValue;
  SetCs
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM_Prepare
* Description    : Prepare to write to the LCD RAM.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
  //**ClrCs
  //**LCD->LCD_REG = R34;
  //**SetCs
  if((DeviceCode==0x9325)||(DeviceCode==0x9328)||(DeviceCode==0x8989))
	{
  	ClrCs
  	LCD->LCD_REG = R34;
  	SetCs
	}
	else
	{
  	LCD_WrtReg(0x002C);
	}
}                                //**

/*******************************************************************************
* Function Name  : LCD_WriteRAM
* Description    : Writes to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM(u16 RGB_Code)					 
{
  ClrCs
  /* Write 16-bit GRAM Reg */
  LCD->LCD_RAM = RGB_Code;
  SetCs
}
void LCD_WrtRAM(u16 LCD_Ram)         //**
{

  LCD_Ram=LCD_Ram;
  LCD->LCD_RAM = LCD_Ram;
  
}



/*******************************************************************************
* Function Name  : LCD_ReadRAM
* Description    : Reads the LCD RAM.
* Input          : None
* Output         : None
* Return         : LCD RAM Value.
*******************************************************************************/
u16 LCD_ReadRAM(void)
{
  //**u16 dummy;
  //**u16 data;
  /* Write 16-bit Index (then Read Reg) */
  //**ClrCs
  //**LCD->LCD_REG = R34; /* Select GRAM Reg */
  /* Read 16-bit Reg */
  //**dummy = LCD->LCD_RAM; 
  //**dummy++;
  //**data = LCD->LCD_RAM; 
  //**SetCs
  //**return    data;
  //return LCD->LCD_RAM;
  u16 temp;	   //**
  temp = LCD->LCD_RAM;
  temp = LCD->LCD_RAM;
  return temp;
}

/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : Sets the cursor position.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position. 
* Output         : None
* Return         : None
*******************************************************************************/


void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
  LCD_WriteReg(0x06,Ypos>>8);
  LCD_WriteReg(0x07,Ypos);
  
  LCD_WriteReg(0x02,Xpos>>8);
  LCD_WriteReg(0x03,Xpos);  
}			 
void LCD_setWindowArea(uint16_t StartX, uint16_t StartY, uint16_t Width, uint16_t Height)
{
  int8_t s_h,s_l, e_h, e_l;
	
  uint16_t xEnd, yEnd;
	
	xEnd = StartX + Width-1;
	yEnd = StartY + Height-1;   
	if((DeviceCode==0x9325)||(DeviceCode==0x9328))
   {
            LCD_WriteReg(0x0050,StartY);        //Specify the start/end positions of the window address in the horizontal direction by an address unit
            LCD_WriteReg(0x0051,StartY + Height -1);        //Specify the start positions of the window address in the vertical direction by an address unit 
            LCD_WriteReg(0x0052,320 - StartX - Width); 
            LCD_WriteReg(0x0053,320 - StartX - 1 );        //Specify the end positions of the window address in the vertical direction by an address unit
	 }    
    else  if(DeviceCode==0x5761)    //** 
    {
          LCD_WrtReg(0X2A);
          LCD_WrtRAM(StartX>>8);
          LCD_WrtRAM(StartX&0XFF);
          LCD_WrtRAM(xEnd>>8);
          LCD_WrtRAM(xEnd&0XFF);
		
          LCD_WrtReg(0X2B);	
          LCD_WrtRAM(StartY>>8);	
          LCD_WrtRAM(StartY&0XFF);
          LCD_WrtRAM(yEnd>>8);	
          LCD_WrtRAM(yEnd&0XFF);                   
    }
		else if(DeviceCode == 0X9488)
		{
			s_h = (StartX >> 8) & 0Xff;
			s_l = StartX & 0Xff;
			e_h = ((StartX + Width - 1) >> 8) & 0Xff;
			e_l = (StartX + Width - 1) & 0Xff;
			
			ILI9488_WriteCmd(0x2A);
			ILI9488_WriteData(s_h);
			ILI9488_WriteData(s_l);
			ILI9488_WriteData(e_h);
			ILI9488_WriteData(e_l);
		
			s_h = (StartY >> 8) & 0Xff;
			s_l = StartY & 0Xff;
			e_h = ((StartY + Height - 1) >> 8) & 0Xff;
			e_l = (StartY + Height - 1) & 0Xff;
			
			ILI9488_WriteCmd(0x2B);
			ILI9488_WriteData(s_h);
			ILI9488_WriteData(s_l);
			ILI9488_WriteData(e_h);
			ILI9488_WriteData(e_l); 	
		}  


}	

void Delay_nms(int n)
{
  
  u32 f=n,k;
  for (; f!=0; f--)
  {
    for(k=0xFFF; k!=0; k--);
  }
  
}

void Delay(u32 nCount)
{
 u32 TimingDelay; 
 while(nCount--)
   {
    for(TimingDelay=0;TimingDelay<10000;TimingDelay++);
   }
}

/**
  * @brief  Draws a chinacharacter on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
void LCD_DrawChinaChar(u8 Xpos, u16 Ypos, const u8 *c)
{
  u32 index = 0, i = 0, j = 0;
  u8 Xaddress = 0;
   
  Xaddress = Xpos;
  
  //ili9320_SetCursor(Xaddress, Ypos);
  ili9320_SetCursor(Ypos,Xaddress);

  for(index = 0; index < 24; index++)
  {
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    for(j = 0; j < 3; j++)
    {
        for(i = 0; i < 8; i++)
        {
          if((c[3*index + j] & (0x80 >> i)) == 0x00)
          {
              LCD_WriteRAM(0xF800);
          }
          else
          {
            LCD_WriteRAM(0xFFE0);
          }
        }   
     }
    Xaddress++;
    ili9320_SetCursor(Ypos, Xaddress);
  }
}
u16 LCD_RD_DATA(void)       //读回数据
{
	u16 ram;			//防止被优化
	ram=LCD->LCD_RAM;	
	return ram;	 
}

u16 Read_ID(void)      //**读取SSD1963ID    
{
    u16 Lcd_ID;
    LCD_WrtReg(0XA1); 
    Lcd_ID=LCD_RD_DATA(); 
    Lcd_ID=LCD_RD_DATA();  //读回0X57 
    Lcd_ID<<=8;     
    Lcd_ID|=LCD_RD_DATA();  //读回0X61
    return Lcd_ID;
}

//获得当前的时钟频率
u16 get_lshift_freq(void)
{	
	u16 data;
	LCD_WrtReg(0xE7);
	data=LCD_RD_DATA();
	data=LCD_RD_DATA();
	data=LCD_RD_DATA();
	return data;
}

/****************************************************************************
* 名    称：void LCD_Initializtion()
* 功    能：初始化 神舟TFT LCD液晶屏的控制器
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：LCD_Initializtion();
****************************************************************************/
//test start//
u16 volatile par1,par2,par3;
//test end//
void LCD_Initializtion(void)
{
   volatile u16 i;
   volatile u16 data1,data2,data3;
   
   LCD_X_Init();  //初始化连接LCD彩色液晶屏上的管脚，比如这里连接的是FSMC总线
   //Delay(5); /* delay 50 ms */
   #if defined(TFT70)
   for(i=0;i<10;i++)
	 #endif
   {
	   HAL_Delay(50);
	   LCD_WriteReg(0x0000,0x0001);  
	   HAL_Delay(50);//Delay(5); /* delay 50 ms */			//start internal osc
	   DeviceCode = LCD_ReadReg(0x0000);
	   HAL_Delay(50);//Delay(5); /* delay 50 ms */
   	 DeviceCode=Read_ID();                                        //**读SSD1963ID

			#if defined(TFT70)
		 if(DeviceCode==0x5761)
		 {
	       break;
	   }
	   else
		 {
	      RESET_1963=0;
    		RESET_1963=1;
	      continue;
	   }
		 #endif
		 
   }
   if(DeviceCode!=0x5761)DeviceCode = LCD_ReadReg(0x0000);  

	 if(DeviceCode<0XFF||DeviceCode==0XFFFF||DeviceCode==0)//读到ID不正确,新增lcddev.id==0X9300判断，因为9341在未被复位的情况下会被读成9300
	 {
			LCD_WriteCommand(0XD3);				   
			DeviceCode=ILI9488_ReadRAM();	//dummy read 	
 			DeviceCode=ILI9488_ReadRAM();	//读到0X00
  		DeviceCode=ILI9488_ReadRAM();   	//读取93								   
 			DeviceCode<<=8;
			DeviceCode|=ILI9488_ReadRAM();  	//读取41 		 		
	 }	
	 

   if(DeviceCode==0x9320||DeviceCode==0x9300)
   {
		LCD_WriteReg(0x00,0x0000);
		LCD_WriteReg(0x01,0x0100);	//Driver Output Contral.
		LCD_WriteReg(0x02,0x0700);	//LCD Driver Waveform Contral.
		LCD_WriteReg(0x03,0x1018);	//Entry Mode Set.
	
		LCD_WriteReg(0x04,0x0000);	//Scalling Contral.
		LCD_WriteReg(0x08,0x0202);	//Display Contral 2.(0x0207)
		LCD_WriteReg(0x09,0x0000);	//Display Contral 3.(0x0000)
		LCD_WriteReg(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		LCD_WriteReg(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		LCD_WriteReg(0x0d,0x0000);	//Frame Maker Position.
		LCD_WriteReg(0x0f,0x0000);	//Extern Display Interface Contral 2.
	
		for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
		LCD_WriteReg(0x07,0x0101);	//Display Contral.
		for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
	
		LCD_WriteReg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		LCD_WriteReg(0x11,0x0007);								//Power Control 2.(0x0001)
		LCD_WriteReg(0x12,(1<<8)|(1<<4)|(0<<0));					//Power Control 3.(0x0138)
		LCD_WriteReg(0x13,0x0b00);								//Power Control 4.
		LCD_WriteReg(0x29,0x0000);								//Power Control 7.
	
		LCD_WriteReg(0x2b,(1<<14)|(1<<4));
		
		LCD_WriteReg(0x50,0);		//Set X Start.
		LCD_WriteReg(0x51,239);	//Set X End.
		LCD_WriteReg(0x52,0);		//Set Y Start.
		LCD_WriteReg(0x53,319);	//Set Y End.
	
		LCD_WriteReg(0x60,0x2700);	//Driver Output Control.
		LCD_WriteReg(0x61,0x0001);	//Driver Output Control.
		LCD_WriteReg(0x6a,0x0000);	//Vertical Srcoll Control.
	
		LCD_WriteReg(0x80,0x0000);	//Display Position? Partial Display 1.
		LCD_WriteReg(0x81,0x0000);	//RAM Address Start? Partial Display 1.
		LCD_WriteReg(0x82,0x0000);	//RAM Address End-Partial Display 1.
		LCD_WriteReg(0x83,0x0000);	//Displsy Position? Partial Display 2.
		LCD_WriteReg(0x84,0x0000);	//RAM Address Start? Partial Display 2.
		LCD_WriteReg(0x85,0x0000);	//RAM Address End? Partial Display 2.
	
		LCD_WriteReg(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
		LCD_WriteReg(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
		LCD_WriteReg(0x93,0x0001);	//Panel Interface Contral 3.
		LCD_WriteReg(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
		LCD_WriteReg(0x97,(0<<8));	//
		LCD_WriteReg(0x98,0x0000);	//Frame Cycle Contral.	
		LCD_WriteReg(0x07,0x0173);	//(0x0173)
	}
	else if(DeviceCode==0x9331)
	{
		LCD_WriteReg(0x00E7, 0x1014);
		LCD_WriteReg(0x0001, 0x0100); // set SS and SM bit   0x0100
		LCD_WriteReg(0x0002, 0x0200); // set 1 line inversion
		LCD_WriteReg(0x0003, 0x1030); // set GRAM write direction and BGR=1.     0x1030
		LCD_WriteReg(0x0008, 0x0202); // set the back porch and front porch
		LCD_WriteReg(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
		LCD_WriteReg(0x000A, 0x0000); // FMARK function
		LCD_WriteReg(0x000C, 0x0000); // RGB interface setting
		LCD_WriteReg(0x000D, 0x0000); // Frame marker Position
		LCD_WriteReg(0x000F, 0x0000); // RGB interface polarity*/
		//*************Power On sequence ****************//
		LCD_WriteReg(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
		LCD_WriteReg(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
		LCD_WriteReg(0x0012, 0x0000); // VREG1OUT voltage
		LCD_WriteReg(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
		ili9320_Delay(200); // Dis-charge capacitor power voltage
		LCD_WriteReg(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
		LCD_WriteReg(0x0011, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
		ili9320_Delay(50); // Delay 50ms
		LCD_WriteReg(0x0012, 0x000C); // Internal reference voltage= Vci;
		ili9320_Delay(50); // Delay 50ms
		LCD_WriteReg(0x0013, 0x0800); // Set VDV[4:0] for VCOM amplitude
		LCD_WriteReg(0x0029, 0x0011); // Set VCM[5:0] for VCOMH
		LCD_WriteReg(0x002B, 0x000B); // Set Frame Rate
		ili9320_Delay(50); // Delay 50ms
		LCD_WriteReg(0x0020, 0x0000); // GRAM horizontal Address
		LCD_WriteReg(0x0021, 0x0000); // GRAM Vertical Address
		// ----------- Adjust the Gamma Curve ----------//
		LCD_WriteReg(0x0030, 0x0000);
		LCD_WriteReg(0x0031, 0x0106);
		LCD_WriteReg(0x0032, 0x0000);
		LCD_WriteReg(0x0035, 0x0204);
		LCD_WriteReg(0x0036, 0x160A);
		LCD_WriteReg(0x0037, 0x0707);
		LCD_WriteReg(0x0038, 0x0106);
		LCD_WriteReg(0x0039, 0x0707);
		LCD_WriteReg(0x003C, 0x0402);
		LCD_WriteReg(0x003D, 0x0C0F);
		//------------------ Set GRAM area ---------------//
		LCD_WriteReg(0x0050, 0x0000); // Horizontal GRAM Start Address
		LCD_WriteReg(0x0051, 0x00EF); // Horizontal GRAM End Address
		LCD_WriteReg(0x0052, 0x0000); // Vertical GRAM Start Address
		LCD_WriteReg(0x0053, 0x013F); // Vertical GRAM Start Address
		LCD_WriteReg(0x0060, 0x2700); // Gate Scan Line
		LCD_WriteReg(0x0061, 0x0001); // NDL,VLE, REV
		LCD_WriteReg(0x006A, 0x0000); // set scrolling line
		//-------------- Partial Display Control ---------//
		LCD_WriteReg(0x0080, 0x0000);
		LCD_WriteReg(0x0081, 0x0000);
		LCD_WriteReg(0x0082, 0x0000);
		LCD_WriteReg(0x0083, 0x0000);
		LCD_WriteReg(0x0084, 0x0000);
		LCD_WriteReg(0x0085, 0x0000);
		//-------------- Panel Control -------------------//
		LCD_WriteReg(0x0090, 0x0010);
		LCD_WriteReg(0x0092, 0x0600);
		LCD_WriteReg(0x0007,0x0021);		
		ili9320_Delay(50);
		LCD_WriteReg(0x0007,0x0061);
		ili9320_Delay(50);
		LCD_WriteReg(0x0007,0x0133);  // 262K color and display ON
		ili9320_Delay(50);
	}
	else if(DeviceCode==0x8989)
	{   
          LCD_WriteReg(0x0000,0x0001);   //打开晶振         
          LCD_WriteReg(0x0010,0x0000);                     
          Delay(5); // Wait 30ms            
          LCD_WriteReg(0x0007,0x0233);                
          LCD_WriteReg(0x0011,0x6078); //定义数据格式  16位色 		横屏 0x6058           
          LCD_WriteReg(0x0002,0x0600);       
          LCD_WriteReg(0x0003,0xA8A4);//0x0804  
          LCD_WriteReg(0x000C,0x0000);
          LCD_WriteReg(0x000D,0x080C);       
          LCD_WriteReg(0x000E,0x2900);       
          LCD_WriteReg(0x001E,0x00B8);       
          LCD_WriteReg(0x0001,0x293F);
          LCD_WriteReg(0x0010,0x0000);       
          LCD_WriteReg(0x0005,0x0000);       
          LCD_WriteReg(0x0006,0x0000);       
          LCD_WriteReg(0x0016,0xEF1C);     
          LCD_WriteReg(0x0017,0x0003);     
          LCD_WriteReg(0x0007,0x0233);		//0x0233       
          LCD_WriteReg(0x000B,0x0000|(3<<6));     
          LCD_WriteReg(0x000F,0x0000);		//扫描开始地址
	  LCD_WriteReg(0x0041,0x0000);     
	  LCD_WriteReg(0x0042,0x0000);     
	  LCD_WriteReg(0x0048,0x0000);     
	  LCD_WriteReg(0x0049,0x013F);     
	  LCD_WriteReg(0x004A,0x0000);     
	  LCD_WriteReg(0x004B,0x0000);     
	  LCD_WriteReg(0x0044,0xEF00);     
	  LCD_WriteReg(0x0045,0x0000);     
	  LCD_WriteReg(0x0046,0x013F);     
	  LCD_WriteReg(0x0030,0x0707);     
	  LCD_WriteReg(0x0031,0x0204);     
	  LCD_WriteReg(0x0032,0x0204);     
	  LCD_WriteReg(0x0033,0x0502);     
	  LCD_WriteReg(0x0034,0x0507);     
	  LCD_WriteReg(0x0035,0x0204);     
	  LCD_WriteReg(0x0036,0x0204);     
	  LCD_WriteReg(0x0037,0x0502);     
	  LCD_WriteReg(0x003A,0x0302);     
	  LCD_WriteReg(0x003B,0x0302);     
	  LCD_WriteReg(0x0023,0x0000);     
	  LCD_WriteReg(0x0024,0x0000);     
	  LCD_WriteReg(0x0025,0x8000);     
	  LCD_WriteReg(0x004e,0);        //列(X)首址0
	  LCD_WriteReg(0x004f,0);        //行(Y)首址0*/
	}else if(DeviceCode==0x9325||DeviceCode==0x9328)
	{
          LCD_WriteReg(0x00e3,0x3008);
          LCD_WriteReg(0x00e7,0x0012);
          LCD_WriteReg(0x00ef,0x1231);        //Set the internal vcore voltage
          // LCD_WriteReg(0x00e7,0x0010);      
          LCD_WriteReg(0x0000,0x0001);        //start internal osc
          LCD_WriteReg(0x0001,0x0100);     
          LCD_WriteReg(0x0002,0x0700);        //Driving Wave Control                   
          LCD_WriteReg(0x0003,(1<<12)|(0<<5)|(1<<4)|(1<<3) );// );    (1<<12)|(1<<4)|(1 << 3) //65K 
          LCD_WriteReg(0x0004,0x0000);                                   
          LCD_WriteReg(0x0008,0x0207);               
          LCD_WriteReg(0x0009,0x0000);         
          LCD_WriteReg(0x000a,0x0000);        //display setting         
          LCD_WriteReg(0x000c,0x0001);        //display setting          
          LCD_WriteReg(0x000d,0x0000);        //0f3c          
          LCD_WriteReg(0x000f,0x0000);
          //Power On sequence //
          LCD_WriteReg(0x0010,0x0000);   
          LCD_WriteReg(0x0011,0x0007);
          LCD_WriteReg(0x0012,0x0000);                                                                 
          LCD_WriteReg(0x0013,0x0000);                 
          for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
          LCD_WriteReg(0x0010,0x1590);   
          LCD_WriteReg(0x0011,0x0227);
          for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
          LCD_WriteReg(0x0012,0x009c);                  
          for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
          LCD_WriteReg(0x0013,0x1900);   
          LCD_WriteReg(0x0029,0x0023);
          LCD_WriteReg(0x002b,0x000e);
          for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
          LCD_WriteReg(0x0020,0x0000);                                                            
          LCD_WriteReg(0x0021,0x0000);           
///////////////////////////////////////////////////////      
          for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
          LCD_WriteReg(0x0030,0x0007); 
          LCD_WriteReg(0x0031,0x0707);   
          LCD_WriteReg(0x0032,0x0006);
          LCD_WriteReg(0x0035,0x0704);
          LCD_WriteReg(0x0036,0x1f04); 
          LCD_WriteReg(0x0037,0x0004);
          LCD_WriteReg(0x0038,0x0000);        
          LCD_WriteReg(0x0039,0x0706);     
          LCD_WriteReg(0x003c,0x0701);
          LCD_WriteReg(0x003d,0x000f);
          for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
          LCD_WriteReg(0x0050,0x0000);        
          LCD_WriteReg(0x0051,0x00ef);   
          LCD_WriteReg(0x0052,0x0000);     
          LCD_WriteReg(0x0053,0x013f);
          LCD_WriteReg(0x0060,0xa700);        
          LCD_WriteReg(0x0061,0x0001); 
          LCD_WriteReg(0x006a,0x0000);
          LCD_WriteReg(0x0080,0x0000);
          LCD_WriteReg(0x0081,0x0000);
          LCD_WriteReg(0x0082,0x0000);
          LCD_WriteReg(0x0083,0x0000);
          LCD_WriteReg(0x0084,0x0000);
          LCD_WriteReg(0x0085,0x0000);
      
          LCD_WriteReg(0x0090,0x0010);     
          LCD_WriteReg(0x0092,0x0600);  
          if(DeviceCode==0x9328)
          {   
            LCD_WriteReg(0x0093,0x0003);
            LCD_WriteReg(0x0095,0x0110);
            LCD_WriteReg(0x0097,0x0000);        
            LCD_WriteReg(0x0098,0x0000);  
          }
          //display on sequence     
          LCD_WriteReg(0x0007,0x0133);
    
          LCD_WriteReg(0x0020,0x0000);                                                            
          LCD_WriteReg(0x0021,0x0000);
          }else if(DeviceCode==0x5761){                              //**SSD1963
          #if 1
	   for(i=0;i<100;i++)
	   {
	          LCD_WrtReg(0x002b);	
	          LCD_WrtRAM(0);

	          //for(i=50000;i>0;i--); // delay 50 ms 
	          HAL_Delay(50);
	          LCD_WrtReg(0x00E2);					//PLL multiplier, set PLL clock to 120M
	          //**LCD_WrtRAM(0x0023);					//N=0x36 for 6.5M, 0x23 for 10M crystal
	          LCD_WrtRAM(0x002C);
	          //LCD_WrtRAM(0x0024);
	          LCD_WrtRAM(0x0002);
	          LCD_WrtRAM(0x0004);
		   HAL_Delay(50);
		   
	          LCD_WrtReg(0x00E0);					//PLL enable
	          LCD_WrtRAM(0x0001);
	          HAL_Delay(1);
	          LCD_WrtReg(0x00E0);
	          LCD_WrtRAM(0x0003);
	          HAL_Delay(7);
	          LCD_WrtReg(0x0001);  					//软复位
	          HAL_Delay(12);
	          LCD_WrtReg(0x00E6);					//设置像素频率
	  //	  LCD_WriteRAM(0x0001);
	  //	  LCD_WriteRAM(0x0033);
	  //	  LCD_WriteRAM(0x0032);
	          LCD_WrtRAM(0x0004);
	          //LCD_WrtRAM(0x0005);
	          LCD_WrtRAM(0x0093);
	          LCD_WrtRAM(0x00E0);
		   HAL_Delay(50);
		   
	          LCD_WrtReg(0x00B0);					//设置 LCD模式 
	          LCD_WrtRAM(0x0020);                                   //24 位模式
	          //**LCD_WrtRAM(0x0000);                                   
	          LCD_WrtRAM(0x0000);                                   //TFT  模式
	          LCD_WrtRAM((HDP>>8)&0X00FF);			//设置 LCD水平像素
	          LCD_WrtRAM(HDP&0X00FF);
	          LCD_WrtRAM((VDP>>8)&0X00FF);			//设置 LCD垂直像素
	          LCD_WrtRAM(VDP&0X00FF);
	          LCD_WrtRAM(0x0000);
		   HAL_Delay(5);
	          LCD_WrtReg(0x00B4);					//Set horizontal period
	          LCD_WrtRAM((HT>>8)&0X00FF); 			//Set HT
	          LCD_WrtRAM(HT&0X00FF);
	          LCD_WrtRAM((HPS>>8)&0X00FF);			//Set HPS
	          LCD_WrtRAM(HPS&0X00FF);
	          LCD_WrtRAM(HPW);						//Set HPW
	          LCD_WrtRAM((LPS>>8)&0X00FF); 			//Set HPS
	          LCD_WrtRAM(LPS&0X00FF);
	          LCD_WrtRAM(0x0000);

	          LCD_WrtReg(0x00B6);					//Set vertical period 
	          LCD_WrtRAM((VT>>8)&0X00FF);   		//Set VT
	          LCD_WrtRAM(VT&0X00FF);
	          LCD_WrtRAM((VPS>>8)&0X00FF); 			//Set VPS
	          LCD_WrtRAM(VPS&0X00FF);
	          LCD_WrtRAM(VPW);						//Set VPW
	          LCD_WrtRAM((FPS>>8)&0X00FF);			//Set FPS
	          LCD_WrtRAM(FPS&0X00FF);
		   HAL_Delay(5);
	          //=============================================

	          //=============================================
	          LCD_WrtReg(0x00BA);
	          LCD_WrtRAM(0x0005);//0x000F);    //GPIO[3:0] out 1

	          LCD_WrtReg(0x00B8);
	          LCD_WrtRAM(0x0007);    //GPIO3=input, GPIO[2:0]=output
	          LCD_WrtRAM(0x0001);    //GPIO0 normal

	          LCD_WrtReg(0x0036); //rotation
	          //chen 11.8
		   if(gCfgItems.overturn_180 != 0xEE)
		   {
		  	LCD_WrtRAM(0x0000);
		   }
		   else
		   {
			LCD_WrtRAM(0x0003);
		   }
	          HAL_Delay(50);
		   //ili9320_Clear(0x000000);

	          LCD_WrtReg(0x00BE); //set PWM for B/L
	          LCD_WrtRAM(0x0006);
	          LCD_WrtRAM(0x0080);
		
	          LCD_WrtRAM(0x0001);
	          LCD_WrtRAM(0x00f0);
	          LCD_WrtRAM(0x0000);
	          LCD_WrtRAM(0x0000);

	          LCD_WrtReg(0x00d0); 
	          LCD_WrtRAM(0x000d);
	   
	          LCD_WrtReg(0x00F0); //设置 SSD1963与 CPU接口为 16bit
	          LCD_WrtRAM(0x0003); //16-bit(565 format) data for 16bpp 
		   ili9320_Clear(0x000000);	                            //显示
	          LCD_WrtReg(0x0029); //开启显示

	          //lcd_data_bus_test();
	          ili9320_Clear(0x000000);	                            //显示
	          //chen 11.9
	          //test start // 2c 02 04
	                LCD_WrtReg(0xE3);
			  par1=LCD_RD_DATA();
			  par2=LCD_RD_DATA();
			  par3=LCD_RD_DATA();
			  //测试值为以下两种情况，显示正常
			  if(par1!=0x002C && par1!=0x002D)
			  {
			  	RESET_1963=0;
				HAL_Delay(500);
    				RESET_1963=1;
			         continue;
				
			  }
			 
	          //test end //
	                 LCD_WrtReg(0xE7);
			   data1=LCD_RD_DATA();
			   data2=LCD_RD_DATA();
			   data3=LCD_RD_DATA();
			   if(data1==0x0004 && data2==0x0093 && data3==0x00E0){
			   	  break;
			   }
			   else{
			   	  /*_LCD_WrtReg(0x00E6);					//设置像素频率
			         LCD_WrtRAM(0x0004);
			         LCD_WrtRAM(0x0093);
			         LCD_WrtRAM(0x00E0);*/
			         RESET_1963=0;
				  HAL_Delay(500);
    				  RESET_1963=1;
			         continue;
			   }
	   }
	   #else
	   	LCD_WrtReg(0xE2);		//Set PLL with OSC = 10MHz (hardware),	Multiplier N = 35, 250MHz < VCO < 800MHz = OSC*(N+1), VCO = 300MHz
		LCD_WrtRAM(0x1D);		//2?êy1 
		LCD_WrtRAM(0x02);		//2?êy2 Divider M = 2, PLL = 300/(M+1) = 100MHz
		LCD_WrtRAM(0x04);		//2?êy3 Validate M and N values   
		HAL_Delay(1);
		LCD_WrtReg(0xE0);		// Start PLL command
		LCD_WrtRAM(0x01);		// enable PLL
		HAL_Delay(10);
		LCD_WrtReg(0xE0);		// Start PLL command again
		LCD_WrtRAM(0x03);		// now, use PLL output as system clock	
		HAL_Delay(12);  
		LCD_WrtReg(0x01);		//èí?′??
		HAL_Delay(10);
		
		LCD_WrtReg(0xE6);		//éè???????μ?ê,33Mhz
		LCD_WrtRAM(0x2F);
		LCD_WrtRAM(0xFF);
		LCD_WrtRAM(0xFF);
		
		LCD_WrtReg(0xB0);		//éè??LCD?￡ê?
		LCD_WrtRAM(0x20);		//24???￡ê?
		LCD_WrtRAM(0x00);		//TFT ?￡ê? 
	
		LCD_WrtRAM((SSD_HOR_RESOLUTION-1)>>8);//éè??LCD????????
		LCD_WrtRAM(SSD_HOR_RESOLUTION-1);		 
		LCD_WrtRAM((SSD_VER_RESOLUTION-1)>>8);//éè??LCD′1?±????
		LCD_WrtRAM(SSD_VER_RESOLUTION-1);		 
		LCD_WrtRAM(0x00);		//RGBDòáD 
		
		LCD_WrtReg(0xB4);		//Set horizontal period
		LCD_WrtRAM((SSD_HT-1)>>8);
		LCD_WrtRAM(SSD_HT-1);
		LCD_WrtRAM(SSD_HPS>>8);
		LCD_WrtRAM(SSD_HPS);
		LCD_WrtRAM(SSD_HOR_PULSE_WIDTH-1);
		LCD_WrtRAM(0x00);
		LCD_WrtRAM(0x00);
		LCD_WrtRAM(0x00);
		LCD_WrtReg(0xB6);		//Set vertical period
		LCD_WrtRAM((SSD_VT-1)>>8);
		LCD_WrtRAM(SSD_VT-1);
		LCD_WrtRAM(SSD_VPS>>8);
		LCD_WrtRAM(SSD_VPS);
		LCD_WrtRAM(SSD_VER_FRONT_PORCH-1);
		LCD_WrtRAM(0x00);
		LCD_WrtRAM(0x00);
		
		LCD_WrtReg(0xF0);	//éè??SSD1963ó?CPU?ó?ú?a16bit  
		LCD_WrtRAM(0x03);	//16-bit(565 format) data for 16bpp 

		LCD_WrtReg(0x29);	//?a????ê?
		//éè??PWMê?3?  ±31aí¨1y????±è?éμ÷ 
		LCD_WrtReg(0xD0);	//éè??×??ˉ°×??oaDBC
		LCD_WrtRAM(0x00);	//disable
	
		LCD_WrtReg(0xBE);	//????PWMê?3?
		LCD_WrtRAM(0x05);	//1éè??PWM?μ?ê
		LCD_WrtRAM(0xFE);	//2éè??PWM????±è
		LCD_WrtRAM(0x01);	//3éè??C
		LCD_WrtRAM(0x00);	//4éè??D
		LCD_WrtRAM(0x00);	//5éè??E 
		LCD_WrtRAM(0x00);	//6éè??F 
		
		LCD_WrtReg(0xB8);	//éè??GPIO????
		LCD_WrtRAM(0x03);	//2??IO?úéè??3éê?3?
		LCD_WrtRAM(0x01);	//GPIOê1ó??y3￡μ?IO1|?ü 
		LCD_WrtReg(0xBA);
		LCD_WrtRAM(0X01);	//GPIO[1:0]=01,????LCD·??ò
		
		//LCD_SSD_BackLightSet(100);//±31aéè???a×?áá
		LCD_WrtReg(0xBE);	//????PWMê?3?
		LCD_WrtRAM(0x05);	//1éè??PWM?μ?ê
		LCD_WrtRAM(100*2.55);//2éè??PWM????±è
		LCD_WrtRAM(0x01);	//3éè??C
		LCD_WrtRAM(0xFF);	//4éè??D
		LCD_WrtRAM(0x00);	//5éè??E
		LCD_WrtRAM(0x00);	//6éè??F
			 
	//LCD_Display_Dir(0);		//??è??aêú?á
			//lcddev.dir=1;	//oá?á
			/*lcddev.wramcmd=0X2C;	//éè??D′è?GRAMμ???á? 
			lcddev.setxcmd=0X2A;	//éè??D′X×?±ê??á?
			lcddev.setycmd=0X2B;	//éè??D′Y×?±ê??á?
			lcddev.width=800;		//éè???í?è800
			lcddev.height=480;		//éè?????è480*/
	//LCD_LED=1;				//μ?áá±31a
	//LCD_Clear(WHITE);
	   LCD_WrtReg(0x0029); //开启显示
          //lcd_data_bus_test();
          ili9320_Clear(0x000000);
	#endif
	}
		else if(DeviceCode==0x9488)
		{
			//************* Start Initial Sequence **********//
			ILI9488_WriteCmd(0xE0); 
			ILI9488_WriteData(0x00); 
			ILI9488_WriteData(0x07); 
			ILI9488_WriteData(0x0f); 
			ILI9488_WriteData(0x0D); 
			ILI9488_WriteData(0x1B); 
			ILI9488_WriteData(0x0A); 
			ILI9488_WriteData(0x3c); 
			ILI9488_WriteData(0x78); 
			ILI9488_WriteData(0x4A); 
			ILI9488_WriteData(0x07); 
			ILI9488_WriteData(0x0E); 
			ILI9488_WriteData(0x09); 
			ILI9488_WriteData(0x1B); 
			ILI9488_WriteData(0x1e); 
			ILI9488_WriteData(0x0f);  

			ILI9488_WriteCmd(0xE1); 
			ILI9488_WriteData(0x00); 
			ILI9488_WriteData(0x22); 
			ILI9488_WriteData(0x24); 
			ILI9488_WriteData(0x06); 
			ILI9488_WriteData(0x12); 
			ILI9488_WriteData(0x07); 
			ILI9488_WriteData(0x36); 
			ILI9488_WriteData(0x47); 
			ILI9488_WriteData(0x47); 
			ILI9488_WriteData(0x06); 
			ILI9488_WriteData(0x0a); 
			ILI9488_WriteData(0x07); 
			ILI9488_WriteData(0x30); 
			ILI9488_WriteData(0x37); 
			ILI9488_WriteData(0x0f); 

			ILI9488_WriteCmd(0xC0); 
			ILI9488_WriteData(0x10); 
			ILI9488_WriteData(0x10); 

			ILI9488_WriteCmd(0xC1); 
			ILI9488_WriteData(0x41); 

			LCD_WriteCommand(0xC5); 
			ILI9488_WriteData(0x00); 
			ILI9488_WriteData(0x22); 
			ILI9488_WriteData(0x80); 

			ILI9488_WriteCmd(0x36); 
			if(gCfgItems.overturn_180 != 0xEE)
			{
			ILI9488_WriteData(0x68); 
			}
			else
			{
				ILI9488_WriteData(0xA8);
			}

			ILI9488_WriteCmd(0x3A); //Interface Mode Control
			ILI9488_WriteData(0x55);

			ILI9488_WriteCmd(0XB0);  //Interface Mode Control  
			ILI9488_WriteData(0x00); 
			ILI9488_WriteCmd(0xB1);   //Frame rate 70HZ  
			ILI9488_WriteData(0xB0); 
			ILI9488_WriteData(0x11); 
			ILI9488_WriteCmd(0xB4); 
			ILI9488_WriteData(0x02);   
			ILI9488_WriteCmd(0xB6); //RGB/MCU Interface Control
			ILI9488_WriteData(0x02); 
			ILI9488_WriteData(0x42); 

			ILI9488_WriteCmd(0xB7); 
			ILI9488_WriteData(0xC6); 

			//WriteComm(0XBE);
			//WriteData(0x00);
			//WriteData(0x04);

			ILI9488_WriteCmd(0xE9); 
			ILI9488_WriteData(0x00);

			ILI9488_WriteCmd(0XF7);    
			ILI9488_WriteData(0xA9); 
			ILI9488_WriteData(0x51); 
			ILI9488_WriteData(0x2C); 
			ILI9488_WriteData(0x82);

			ILI9488_WriteCmd(0x11); 
			Delay(120); 
			ILI9488_WriteCmd(0x29); 		
		}
		else
    {
      //**  printf("\n\r ###### Err: Unknow DeviceCode 0x%x ###### ", DeviceCode);
    }
      //**Lcd_Light_ON  
      //**Delay(1200); 
      
}

/****************************************************************************
* 名    称：void ili9320_SetCursor(u16 x,u16 y)
* 功    能：设置屏幕座标
* 入口参数：x      行座标
*           y      列座标
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetCursor(10,10);
****************************************************************************/
//inline void ili9320_SetCursor(u16 x,u16 y)
void ili9320_SetCursor(u16 x,u16 y)
{
	if(DeviceCode==0x8989)
	{
	 	LCD_WriteReg(0x004e,y);        //行
    	LCD_WriteReg(0x004f,x);  //列
	}
	else if((DeviceCode==0x9919))
	{
		LCD_WriteReg(0x004e,x); // 行
  		LCD_WriteReg(0x004f,y); // 列	
	}
  else if((DeviceCode==0x5761))      //SSD1963
	{
		LCD_WrtReg(0x002A);	
                LCD_WrtRAM(x>>8);	    
                LCD_WrtRAM(x&0x00ff);
                LCD_WrtRAM(HDP>>8);	    
                LCD_WrtRAM(HDP&0x00ff);
                LCD_WrtReg(0x002b);	
                LCD_WrtRAM(y>>8);	    
                LCD_WrtRAM(y&0x00ff);
                LCD_WrtRAM(VDP>>8);	    
                LCD_WrtRAM(VDP&0x00ff);	
	}
	else if(DeviceCode == 0x9488)
		{
			ILI9488_WriteCmd(0X2A); 
			ILI9488_WriteData(x>>8); 
			ILI9488_WriteData(x&0XFF);         
			ILI9488_WriteCmd(0X2B); 
			ILI9488_WriteData(y>>8); 
			ILI9488_WriteData(y&0XFF);
		}				
	else
	{
  		LCD_WriteReg(0x0020,y); // 行
  		LCD_WriteReg(0x0021,0x13f-x); // 列
	}
  
  
      	
}
/****************************************************************************
* 名    称：void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
* 功    能：设置窗口区域
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetWindows(0,0,100,100)；
****************************************************************************/
//inline void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
void ili9320_SetWindows(u16 StartX,u16 StartY,u16 width,u16 heigh)
{
	int8_t s_h,s_l, e_h, e_l;
	
	u16 xEnd, yEnd;
	xEnd = StartX + width;
        yEnd = StartY + heigh-1;
  if(DeviceCode==0x8989)
  {
  	
	/*LCD_WriteReg(0x0044, (StartX & 0xff) | (xEnd << 8));
	 LCD_WriteReg(0x0045, StartY);
	 LCD_WriteReg(0x0046, yEnd);*/
	 LCD_WriteReg(0x0044, (StartY& 0xff) | (yEnd << 8));
	 LCD_WriteReg(0x0045, StartX);
	 LCD_WriteReg(0x0046, xEnd);
    
  }
	else if(DeviceCode == 0X9488)
	{
	 	s_h = (StartX >> 8) & 0Xff;
		s_l = StartX & 0Xff;
		e_h = ((StartX + width - 1) >> 8) & 0Xff;
		e_l = (StartX + width - 1) & 0Xff;
		
		ILI9488_WriteCmd(0x2A);
		ILI9488_WriteData(s_h);
		ILI9488_WriteData(s_l);
		ILI9488_WriteData(e_h);
		ILI9488_WriteData(e_l);

		s_h = (StartY >> 8) & 0Xff;
		s_l = StartY & 0Xff;
		e_h = ((StartY + heigh - 1) >> 8) & 0Xff;
		e_l = (StartY + heigh - 1) & 0Xff;
		
		ILI9488_WriteCmd(0x2B);
		ILI9488_WriteData(s_h);
		ILI9488_WriteData(s_l);
		ILI9488_WriteData(e_h);
		ILI9488_WriteData(e_l);		
	}	
  else
  {
	 /* LCD_WriteReg(0x0050, StartX);
	  LCD_WriteReg(0x0052, StartY);
	  LCD_WriteReg(0x0051, xEnd);
	  LCD_WriteReg(0x0053, yEnd);*/
	  	//**LCD_WriteReg(0x0050,StartY);        //Specify the start/end positions of the window address in the horizontal direction by an address unit
		//**LCD_WriteReg(0x0051,yEnd);        //Specify the start positions of the window address in the vertical direction by an address unit 
		//**LCD_WriteReg(0x0052,320 - xEnd); 
		//**LCD_WriteReg(0x0053,320 - StartX - 1);        //Specify the end positions of the window address in the vertical direction by an address unit
    	LCD_WrtReg(0X002A);
	LCD_WrtRAM(StartX>>8);
	LCD_WrtRAM(StartX&0X00FF);
	LCD_WrtRAM(xEnd>>8);
	LCD_WrtRAM(xEnd&0X00FF);
		
	LCD_WrtReg(0X002B);	
	LCD_WrtRAM(StartY>>8);	
	LCD_WrtRAM(StartY&0X00FF);
	LCD_WrtRAM(yEnd>>8);	
	LCD_WrtRAM(yEnd&0X00FF);      //**
	
  }
}

/****************************************************************************
* 名    称：void ili9320_Clear(u16 dat)
* 功    能：将屏幕填充成指定的颜色，如清屏，则填充 0xffff
* 入口参数：dat      填充值
* 出口参数：无
* 说    明：
* 调用方法：ili9320_Clear(0xffff);
****************************************************************************/
void ili9320_Clear(u16 Color)
{
  u32 index=0;
  //**ili9320_SetCursor(0,0); 
  //**LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */    
  //**for(index=0;index<76800;index++)
  //**{
     //**LCD->LCD_RAM=Color;
  //**}
  
  unsigned int count; 
	
	if(DeviceCode ==0x9488)
	{
  	for(index=0;index<76800*2;index++)
  	{
     	LCD->LCD_RAM=Color;
  	}
	}
	else
	{
	    LCD_WrtReg(0x002a);	
	    LCD_WrtRAM(0);	    
	    LCD_WrtRAM(0);
	    LCD_WrtRAM(HDP>>8);	    
	    LCD_WrtRAM(HDP&0x00ff);
	    LCD_WrtReg(0x002b);	
	    LCD_WrtRAM(0);	    
	    LCD_WrtRAM(0);
	    LCD_WrtRAM(VDP>>8);	    
	    LCD_WrtRAM(VDP&0x00ff);
	    LCD_WrtReg(0x002c);	
	    LCD_WrtReg(0x002c);
	    for(count=0;count<(HDP+1)*(VDP+1);count++)
			{
	       LCD_WrtRAM(Color);
			}
	}
}    //**

/****************************************************************************
* 名    称：u16 ili9320_GetPoint(u16 x,u16 y)
* 功    能：获取指定座标的颜色值
* 入口参数：x      行座标
*           y      列座标
* 出口参数：当前座标颜色值
* 说    明：
* 调用方法：i=ili9320_GetPoint(10,10);
****************************************************************************/
u16 ili9320_GetPoint(u16 x,u16 y)
{
  ili9320_SetCursor(x,y);
  return (ili9320_BGR2RGB(LCD_ReadRAM()));
}
/****************************************************************************
* 名    称：void ili9320_SetPoint(u16 x,u16 y,u16 point)
* 功    能：在指定座标画点
* 入口参数：x      行座标
*           y      列座标
*           point  点的颜色
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetPoint(10,10,0x0fe0);
****************************************************************************/
void ili9320_SetPoint(u16 x,u16 y,u16 point)
{
	if(DeviceCode == 0x9488)
	{
		if ( (x>480)||(y>320) ) return;
	}
  //**if ( (x>320)||(y>240) ) return;
  ili9320_SetCursor(x,y);    /*设置光标位置*/

  LCD_WriteRAM_Prepare();     /* 开始写入GRAM*/
  LCD_WriteRAM(point);
}


/****************************************************************************
* 名    称：void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
* 功    能：在指定座标范围显示一副图片
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
            pic        图片头指针
* 出口参数：无
* 说    明：图片取模格式为水平扫描，16位颜色模式
* 调用方法：ili9320_DrawPicture(0,0,100,100,(u16*)demo);
* 作    者： www.armjishu.com
****************************************************************************/
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
{
  u32  i, total;
  u16 data1,data2,data3;
  u16 *picturepointer = pic;
  u16 x,y;
  
  printf("ili9320_DrawPicture StartX %d StartY %d EndX %d EndY %d \n\r", StartX, StartY, EndX, EndY);

  x=StartX;
  y=StartY;
  
  total = (EndX - StartX + 1)*(EndY - StartY + 1 )/2;

  for (i=0;i<total;i++)
  {
      data1 = *picturepointer++;
      data2 = *picturepointer++;
      data3 = ((data1 >>3)& 0x001f) |((data1>>5) & 0x07E0) | ((data2<<8) & 0xF800);
      ili9320_SetPoint(x,y,data3);
      y++;
      if(y > EndY)
      {
          x++;
          y=StartY;
      }


      data1 = data2;
      data2 = *picturepointer++;
      data3 = ((data1 >>11)& 0x001f) |((data2<<3) & 0x07E0) | ((data2) & 0xF800);
      ili9320_SetPoint(x,y,data3);
      y++;
      if(y > EndY)
      {
          x++;
          y=StartY;
      }
  }

}

/****************************************************************************
* 名    称：void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
* 功    能：在指定座标显示一个8x16点阵的ascii字符
* 入口参数：x          行座标
*           y          列座标
*           charColor  字符的颜色
*           bkColor    字符背景颜色
* 出口参数：无
* 说    明：显示范围限定为可显示的ascii码
* 调用方法：ili9320_PutChar(10,10,'a',0x0000,0xffff);
****************************************************************************/
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)  // Lihao
{
  u16 i=0;
  u16 j=0;
  
  u8 tmp_char=0;
  
  if(HyalineBackColor == bkColor)
  {
    for (i=0;i<16;i++)
    {
      tmp_char=ascii_8x16[((c-0x20)*16)+i];
      for (j=0;j<8;j++)
      {
        if ( (tmp_char >> 7-j) & 0x01 == 0x01)
          {
            ili9320_SetPoint(x+j,y+i,charColor); // 字符颜色
          }
          else
          {
            // do nothing // 透明背景
          }
      }
    }
  }
  else
  {
        for (i=0;i<16;i++)
    {
      tmp_char=ascii_8x16[((c-0x20)*16)+i];
      for (j=0;j<8;j++)
      {
        if ( (tmp_char >> 7-j) & 0x01 == 0x01)
          {
            ili9320_SetPoint(x+j,y+i,charColor); // 字符颜色
          }
          else
          {
            ili9320_SetPoint(x+j,y+i,bkColor); // 背景颜色
          }
      }
    }
  }			
}

/****************************************************************************
* 名    称：void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
* 功    能：在指定座标显示一个8x16点阵的ascii字符
* 入口参数：x          行座标
*           y          列座标
*           charColor  字符的颜色
*           bkColor    字符背景颜色
* 出口参数：无
* 说    明：显示范围限定为可显示的ascii码
* 调用方法：ili9320_PutChar(10,10,'a',0x0000,0xffff);
****************************************************************************/
void ili9320_PutChar_16x24(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{

  u16 i=0;
  u16 j=0;
  
  u16 tmp_char=0;

  if(HyalineBackColor == bkColor)
  {
    for (i=0;i<24;i++)
    {
      tmp_char=ASCII_Table_16x24[((c-0x20)*24)+i];
      for (j=0;j<16;j++)
      {
        if ( (tmp_char >> j) & 0x01 == 0x01)
          {
            ili9320_SetPoint(x+j,y+i,charColor); // 字符颜色
          }
          else
          {
              // do nothing // 透明背景
          }
      }
    }
  }
  else
  {
    for (i=0;i<24;i++)
    {
      tmp_char=ASCII_Table_16x24[((c-0x20)*24)+i];
      for (j=0;j<16;j++)
      {
        if ( (tmp_char >> j) & 0x01 == 0x01)
          {
            ili9320_SetPoint(x+j,y+i,charColor); // 字符颜色
          }
          else
          {
            ili9320_SetPoint(x+j,y+i,bkColor); // 背景颜色
          }
      }
    }
  }
}
/****************************************************************************
* 名    称：u16 ili9320_BGR2RGB(u16 c)
* 功    能：RRRRRGGGGGGBBBBB 改为 BBBBBGGGGGGRRRRR 格式
* 入口参数：c      BRG 颜色值
* 出口参数：RGB 颜色值
* 说    明：内部函数调用
* 调用方法：
****************************************************************************/
u16 ili9320_BGR2RGB(u16 c)
{
  u16  r, g, b, rgb;

  b = (c>>0)  & 0x1f;
  g = (c>>5)  & 0x3f;
  r = (c>>11) & 0x1f;
  
  rgb =  (b<<11) + (g<<5) + (r<<0);

  return( rgb );
}

/****************************************************************************
* 名    称：void ili9320_BackLight(u8 status)
* 功    能：开、关液晶背光
* 入口参数：status     1:背光开  0:背光关
* 出口参数：无
* 说    明：
* 调用方法：ili9320_BackLight(1);
****************************************************************************/
void ili9320_BackLight(u8 status)
{
//#if 0 //skyblue 2016-12-13 
  if ( status >= 1 )
  {
    Lcd_Light_ON;
  }
  else
  {
    Lcd_Light_OFF;
  }
//#endif  //skyblue 2016-12-13   
}

/****************************************************************************
* 名    称：void ili9320_Delay(vu32 nCount)
* 功    能：延时
* 入口参数：nCount   延时值
* 出口参数：无
* 说    明：
* 调用方法：ili9320_Delay(10000);
****************************************************************************/
void ili9320_Delay(vu32 nCount)
{
   Delay(nCount);
  //for(; nCount != 0; nCount--);
}
void LCD_WindowMax (unsigned int xsta,unsigned int ysta,unsigned int xend,unsigned int yend)  //**
{
	LCD_WrtReg(0X002A);
	LCD_WrtRAM(xsta>>8);
	LCD_WrtRAM(xsta&0X00FF);
	LCD_WrtRAM(xend>>8);
	LCD_WrtRAM(xend&0X00FF);
		
	LCD_WrtReg(0X002B);	
	LCD_WrtRAM(ysta>>8);	
	LCD_WrtRAM(ysta&0X00FF);
	LCD_WrtRAM(yend>>8);	
	LCD_WrtRAM(yend&0X00FF);			
}


void LCD_Fill2(uint8_t xsta, uint16_t ysta, uint8_t xend, uint16_t yend, uint16_t colour)   //**
{                    
    u32 n;
    LCD_WindowMax (xsta, ysta, xend, yend); 
    LCD_WriteRAM_Prepare();         	   	   
    n=(u32)(yend-ysta+1)*(xend-xsta+1);    
    while(n--){LCD_WrtRAM(colour);}  
}
