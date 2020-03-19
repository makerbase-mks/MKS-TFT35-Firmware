/******************** (C) COPYRIGHT 2009 www.armjishu.com ************************
* File Name          : ARMJISHU_TouchScreen_ADS7843.c
* Author             : www.armjishu.com Team
* Version            : V3.0.1
* Date               : 03/20/2010
* Description        : 
                        ADS7843_CS   is PB1
                        ADS7843_INT  is PC1
*******************************************************************************/
#include "mks_touch_screen.h"
//#include "stm32f10x.h"
#include "stm32f4xx.h" //skyblue 2006-12-13
#include <stdio.h>
//#include "stm32f10x_exti.h"   //skyblue 2006-12-13
#include "stm32f4xx_it.h"
#include "ili9320.h"
//#include "stm32f10x_tim.h"    //skyblue 2006-12-13
#include "tim.h"
#include "stm32f4xx_spi.h"
#include "spi_flash.h"

extern u16 DeviceCode;

/*#define  EVENT_FIFO_DEPTH	20
typedef struct
{	
	TOUCH_EVENT event[EVENT_FIFO_DEPTH];
	int8_t  r_idx;
	int8_t  w_idx;
	
} EVENT_FIFO;

static EVENT_FIFO  touch_event_fifo;*/

static int16_t x_touch,  y_touch;

static int32_t touch_time = 0;

static uint8_t lastTouchState = PEN_UP;

//static TOUCH_EVENT  TouchEvent;

#define  times  8


// A/D 通道选择命令字和工作寄存器
#define	CHX 	0x90//0x90 	//通道Y+的选择控制字	//0x94
#define	CHY 	0xD0//0xd0	//通道X+的选择控制字	//0xD4

//#define ADS7843_WrCmd  SPI1_SendByte
//#define ADS7843_Read   SPI1_RecvByte

void ADS7843_CS_config(void)
{
#if 0   //skyblue 2016-12-13  
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable GPIOB, GPIOC and AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_ADS7843_CS , ENABLE);  //RCC_APB2Periph_AFIO
  
  /* LEDs pins configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_ADS7843_CS;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIO_ADS7843_CS_PORT, &GPIO_InitStructure);
#endif    //skyblue 2016-12-13  
}

static void ADS7843_INT_config(void)
{
  #if 0   //skyblue 2016-12-13  
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable GPIOB, GPIOC and AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_ADS7843_INT , ENABLE);  //RCC_APB2Periph_AFIO
  
  /* LEDs pins configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_ADS7843_INT;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIO_ADS7843_INT_PORT, &GPIO_InitStructure);
  #endif    //skyblue 2016-12-13  
}

static void ADS7843_INT_EXIT_Init(void)
{
 #if 0   //skyblue 2016-12-13  
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Connect Button EXTI Line to Button GPIO Pin */
    GPIO_EXTILineConfig(GPIO_ADS7843_EXTI_PORT_SOURCE, GPIO_ADS7843_EXTI_PIN_SOURCE);  

    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = GPIO_ADS7843_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
#endif    //skyblue 2016-12-13  
}


/*******************************************************************************
* Function Name  : InterruptConfig
* Description    : Configures the used IRQ Channels and sets their priority.NVIC_Configuration
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void ADS7843_InterruptConfig(void)
{ 
 #if 0   //skyblue 2016-12-13   
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Set the Vector Table base address at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);
  
  /* Configure the Priority Group to 2 bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* Enable the EXTI5 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = GPIO_ADS7843_EXTI_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
#endif    //skyblue 2016-12-13    
}


static void LCD_BIG_POINT(u16 xScreen, u16 yScreen)
 {
   ili9320_SetPoint(xScreen, yScreen, Magenta);
   ili9320_SetPoint(xScreen-1, yScreen, Magenta);
   ili9320_SetPoint(xScreen+1, yScreen, Magenta);
   ili9320_SetPoint(xScreen, yScreen-1, Magenta);
   ili9320_SetPoint(xScreen, yScreen+1, Magenta);
   ili9320_SetPoint(xScreen-1, yScreen-1, Magenta);
   ili9320_SetPoint(xScreen-1, yScreen+1, Magenta);
   ili9320_SetPoint(xScreen+1, yScreen-1, Magenta);
   ili9320_SetPoint(xScreen+1, yScreen+1, Magenta);

  }

/*=====================================================================*/
#if 0
u16 _AD2Y(u16 adx) //240
{
  u16 sx=0;
  int r = adx - 200;
  r *= 240;
  sx=r / (4000 - 280);
  if (sx<=0 || sx>240)
    return 0;
  return sx;
}


u16 _AD2X(u16 ady) //320
{
  u16 sy=0;
  int r = ady - 260;
  r *= 320;
  sy=r/(3960 - 360);
  if (sy<=0 || sy>320)
    return 0;
  return sy;
}
#else
#if defined(TFT70)
u16 _AD2Y(u16 adx) //240
{
  u16 sx=0;
  int r = adx - 183;
  r *= 480;
  sx=r / (3699 - 200);
  if (sx<=0 || sx>480)
    return 0;
  return sx;
}


u16 _AD2X(u16 ady) //320
{
  u16 sy=0;
  int r = ady - 242;
  r *= 800;
  sy=r/(3847 - 360);
  if (sy<=0 || sy>800)
    return 0;
  return sy;
}
#elif defined(TFT35)
u16 _AD2Y(u16 adx) //240
{
  u16 sx=0;
  int r = adx - 183;
  r *= 320;
  sx=r / (3699 - 200);
  if (sx<=0 || sx>320)
    return 0;
  return sx;
}


u16 _AD2X(u16 ady) //320
{
  u16 sy=0;
  int r = ady - 242;
  r *= 480;
  sy=r/(3847 - 360);
  if (sy<=0 || sy>480)
    return 0;
  return sy;
}

#endif
#endif




/*=====================================================================*/
/*=====================================================================*/
/*=====================================================================*/
/*=====================================================================*/
// A/D 通道选择命令字和工作寄存器
//#define	CHX 	0x90 	//通道Y+的选择控制字	//0x94
//#define	CHY 	0xd0	//通道X+的选择控制字	//0xD4



//读ADS7843的IO控制口
	
/*=====================================================================*/

void ADS7843_Init(void)
{
 #if 0   //skyblue 2016-12-13    
    ADS7843_CS_config();     // 使能LCD
    ADS7843_CS_HIGH() ;     // 关闭LCD
    SPI1_Config();
    SPI1_Init_For_Byte();
    SPI1_MOSI_HIGH();
    SPI1_SCK_LOW();
   // ADS7843_INT_config();
   // ADS7843_INT_EXIT_Init();
   // ADS7843_InterruptConfig();

	// touch_event_fifo.r_idx = 0;
  //  touch_event_fifo.w_idx = 0;
  //  memset(touch_event_fifo.event, 0, sizeof(touch_event_fifo.event));

   lastTouchState = PEN_UP;
#endif    //skyblue 2016-12-13      
}
/*=====================================================================*/
/*=====================================================================*/


void SPI1_Config(void)
{
 #if 0   //skyblue 2016-12-13  
  GPIO_InitTypeDef GPIO_InitStructure;
    
  // Set as Output push-pull - SCK and MOSI
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MOSI;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SPI1_PORT, &GPIO_InitStructure);
  
  //SPI_MISO
  GPIO_InitStructure.GPIO_Pin = SPI1_MISO;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SPI1_PORT, &GPIO_InitStructure);
#endif    //skyblue 2016-12-13    

}

/*=====================================================================*/
void SPI1_Init_For_Byte(void)
{

}

/*=====================================================================*/
static void ADS7843_SPI_Start( void )
{
 #if 0   //skyblue 2016-12-13   
    ADS7843_CS_HIGH();
    SPI1_MOSI_HIGH();
    SPI1_SCK_LOW();
    ADS7843_CS_LOW();	      		//芯片允许
#endif    //skyblue 2016-12-13     
}

/*=====================================================================*/
static void SPI_MOSI(u8 data)
{
 #if 0   //skyblue 2016-12-13    
    if(data)
        SPI1_MOSI_HIGH();
    else
        SPI1_MOSI_LOW();
#endif    //skyblue 2016-12-13     
}

/*=====================================================================*/
/*
#define ShortDelayTime 1
#define LongDelayTime (ShortDelayTime*2)
SPI1_Delay_Short()
{
    __IO uint32_t nCount;
    
    for( nCount= 0; nCount < ShortDelayTime; nCount++ );
}
*/
/*=====================================================================*/


/*=====================================================================*/
static void ADS7843_WrCmd(u8 cmd)
{
#if 0   //skyblue 2016-12-13    
    u8 buf, i;

    for( i = 0; i < 8; i++ )
    {
        buf = (cmd >> (7-i)) & 0x1 ;	//MSB在前,LSB在后
        SPI_MOSI(buf);	 	//时钟上升沿锁存DIN
        SPI1_SCK_HIGH();			//时钟脉冲，一共8个
        SPI1_SCK_LOW();			//开始发送命令字
    }
#endif    //skyblue 2016-12-13 	
}

/*=====================================================================*/
static u16 ADS7843_Read(void)
{
#if 0   //skyblue 2016-12-13    
	u16 buf = 0 ;
	u8 i;

    SPI1_SCK_HIGH(); //wait busy
	SPI1_SCK_LOW();	
	for( i = 0; i < 12; i++ )
	{
		buf = buf << 1 ;
		SPI1_SCK_HIGH();
		if ( SPI1_MISO_READ() )	
		{
			buf = buf + 1 ;
		}
		SPI1_SCK_LOW();			
	}

	for( i = 0; i < 3; i++ )
	{
		SPI1_SCK_HIGH();
		SPI1_SCK_LOW();			
	}
    
	return( buf ) ;
#endif    //skyblue 2016-12-13 	        
}

/*=====================================================================*/

static void ADS7843_Rd_Addata(u16 *X_Addata,u16 *Y_Addata)
{

	u16		i,j,k,x_addata[times],y_addata[times];
    int result;

        
	for(i=0;i<times;i++)					//采样4次.
	{
	#if 0
	    ADS7843_SPI_Start();
		ADS7843_WrCmd( CHX ) ;
		y_addata[i] = ADS7843_Read() ;
        ADS7843_CS_HIGH(); 

	    ADS7843_SPI_Start();
		ADS7843_WrCmd( CHY ) ;
		x_addata[i] = ADS7843_Read() ;
        ADS7843_CS_HIGH(); 
	#else
	     
            SPI1_SetSpeed(SPI_BaudRatePrescaler_256);
	     W25QXX_CS=1;//**
            ADS7843_CS = 0;	
            SPI1_ReadWriteByte(CHX);
            y_addata[i] = SPI1_ReadWrite2Bytes();
            SPI1_ReadWriteByte(CHY);
            x_addata[i] = SPI1_ReadWrite2Bytes(); 
            ADS7843_CS = 1;
            SPI1_SetSpeed(SPI_BaudRatePrescaler_4);
	     
        
/*        
	SPI2_SetSpeed(SPI_BaudRatePrescaler_64);
				ADS7843_CS_LOW();
	
				SPI2_ReadWriteByte(CHX);
				y_addata[i] = SPI2_ReadWrite2Bytes();
        ADS7843_CS_HIGH(); 

	    	ADS7843_CS_LOW();
				SPI2_ReadWriteByte(CHY);
				x_addata[i] = SPI2_ReadWrite2Bytes(); 
        ADS7843_CS_HIGH(); 
	SPI2_SetSpeed(SPI_BaudRatePrescaler_2);
*/        
	#endif
	}

	result = x_addata[0];
	for(i=0;i<times;i++)					
	{
		for(j = i + 1; j < times; j++)
		{
			if(x_addata[j] > x_addata[i])
			{
				k = x_addata[j];
				x_addata[j] = x_addata[i];
				x_addata[i] = k;
			}
		}
	}
	if(x_addata[times / 2 -1] - x_addata[times / 2 ] > 30)
	{
            *X_Addata = 0;
            *Y_Addata = 0;
            return ;
        }

	*X_Addata = (x_addata[times / 2 -1] + x_addata[times / 2 ]) /2;

	
	result = y_addata[0];
	for(i=0;i<times;i++)					
	{
		for(j = i + 1; j < times; j++)
		{
			if(y_addata[j] > y_addata[i])
			{
				k = y_addata[j];
				y_addata[j] = y_addata[i];
				y_addata[i] = k;
			}
		}
	}

	
	if(y_addata[times / 2 -1] - y_addata[times / 2 ] > 30)
	{
            *X_Addata = 0;
            *Y_Addata = 0;
            return ;
        }

	*Y_Addata = (y_addata[times / 2 -1] + y_addata[times / 2 ]) /2;
	
	
}

/*=====================================================================*/
/*=====================================================================*/
/*=====================================================================*/
u16 distence(u16 data1,u16 data2)
{
    if((data1 > data2) && (data1 > data2 + 10))
    {
        return 0;
    }

    if((data2 > data2) && (data2 > data2 + 10))
    {
        return 0;
    }

    return 1;    
}

/*=====================================================================*/
extern uint32_t TSC_Value_X;
extern uint32_t TSC_Value_Y;
void ARMJISHU_TouchScreen_ADS7843(void)
{
#if 0   //skyblue 2016-12-13    
  u16 xdata, ydata;
  u32 xScreen, yScreen;

    static u16 sDataX,sDataY;
    
 // printf("\n\r ARMJISHU_TouchScreen_ADS7843 \n\r");
  ADS7843_Rd_Addata(&xdata, &ydata);
  xScreen = _AD2X(ydata);
  yScreen = _AD2Y(xdata);

   //xScreen = 320 - ((ydata*320)>>12);
   //yScreen = (xdata*240)>>12;

 
  //printf("\n\r (0x%x, 0x%x), (%d, %d)", xdata, ydata, xScreen, yScreen);
  if((xScreen>1)&&(yScreen>1)&&(xScreen<320-1)&&(yScreen<240-1))
  {
       printf("\n\r%d,%d", xScreen, yScreen);
      if((GPIO_ADS7843_INT_VALID) && distence(sDataX,xScreen) && distence(sDataY,yScreen))
        {
//             LCD_BIG_POINT(xScreen, yScreen);
//			 printf("\n\r%d,%d", xScreen, yScreen);
		        TSC_Value_X = xScreen;
				if(DeviceCode==0x9325)
					TSC_Value_Y = 240-yScreen;
				else
					TSC_Value_Y = yScreen;
        }
      sDataX = xScreen;
      sDataY = yScreen;
  }
#endif    //skyblue 2016-12-13     
}

#define ADC_VALID_OFFSET	10
//#define ADC_VALID_OFFSET	750

static uint8_t	TOUCH_PressValid(uint16_t _usX, uint16_t _usY)
{
	if ((_usX <= ADC_VALID_OFFSET) || (_usY <= ADC_VALID_OFFSET)
		|| (_usX >= 4095 - ADC_VALID_OFFSET)
		|| (_usY >= 4095 - ADC_VALID_OFFSET))
		//|| (_usX >=8000 - ADC_VALID_OFFSET)
		//|| (_usY >= 8000 - ADC_VALID_OFFSET))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

#if 1
void getTouchEvent(TOUCH_EVENT *pTouchEvent)
{
	uint32_t tmpTime, diffTime = 0;
	int16_t x, y;
	
	tmpTime = getTick();

	diffTime = getTickDiff(tmpTime, touch_time);

	if(diffTime > 20)
	{
		x = x_touch;
		y = y_touch;
		W25QXX_CS=1;
		ADS7843_Rd_Addata(&x_touch, &y_touch);
		if(TOUCH_PressValid(x_touch, y_touch))
		{			
			//if(abs(x - x_touch) > 50 || abs(y-y_touch) > 50)
			if(abs(x - x_touch) > 30 || abs(y-y_touch) > 30)
			{
				//pTouchEvent->state = PEN_NONE;
				return;
			}
		
			pTouchEvent->x  = (x + x_touch) >> 1;
			pTouchEvent->y = (y + y_touch) >> 1;
			pTouchEvent->state = PEN_DOWN;
			
			touch_time = tmpTime;
			
		}
		else
		{
			pTouchEvent->state = PEN_UP;
			touch_time = tmpTime;
		}
	}
	else
	{
		//pTouchEvent->state = PEN_NONE;
	}
	

	#if 0
			
	tmpTime = getTick();

	diffTime = getTickDiff(tmpTime, touch_time);
		
	//if(diffTime > 10 && diffTime < 2000)	//按下时间限制在10ms到2s
	if(diffTime > 20)
	{
		x = x_touch;
		y = y_touch;

		ADS7843_Rd_Addata(&x_touch, &y_touch);
	//	x_touch = ADS_Read_X();
	//	y_touch = ADS_Read_Y();

		
		if(TOUCH_PressValid(x_touch, y_touch))
		{
			//if(x - x_touch >50 || x_touch - x >50 || y - y_touch >50 || y_touch - y >50)
			if(abs(x - x_touch) > 50 || abs(y-y_touch) > 50)
			{
				return 0;
			}
		
			TouchEvent.x  = (x + x_touch) >> 1;
			TouchEvent.y = (y + y_touch) >> 1;
			
			touch_time = tmpTime;
		}
		else
			return 0;

	}
	else
	{
		return 0;
	}
	
	return &TouchEvent;
#endif
}
#else
TOUCH_EVENT *getTouchEvent()
{
	uint32_t tmpTime, diffTime = 0;
	int16_t x, y;

	
	//tan 20160830
	ADS7843_Init();

	tmpTime = getTick();

	diffTime = getTickDiff(tmpTime, touch_time);
		
	//if(diffTime > 10 && diffTime < 2000)	//
	if(diffTime > 20)
	{
		x = x_touch;
		y = y_touch;

		ADS7843_Rd_Addata(&x_touch, &y_touch);
	//	x_touch = ADS_Read_X();
	//	y_touch = ADS_Read_Y();

		touch_time = tmpTime;
		
		//if(x - x_touch >50 || x_touch - x >50 || y - y_touch >50 || y_touch - y >50)
		if(abs(x - x_touch) > 50 || abs(y-y_touch) > 50)
		{
			return 0;
		}

		TouchEvent.x  = (x + x_touch) >> 1;
		TouchEvent.y = (y + y_touch) >> 1;

	}
	else
	{
		return 0;
	}
	
	return &TouchEvent;

}
#endif
/*=====================================================================*/
/*=====================================================================*/
/*=====================================================================*/
/*=====================================================================*/
/*=====================================================================*/
/*=====================================================================*/
/*=====================================================================*/
/*=====================================================================*/

