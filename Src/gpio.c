/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  *
  * Copyright (c) 2016 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PC1   ------> ETH_MDC
     PA1   ------> ETH_REF_CLK
     PA2   ------> ETH_MDIO
     PA7   ------> ETH_CRS_DV
     PC4   ------> ETH_RXD0
     PC5   ------> ETH_RXD1
     PG11   ------> ETH_TX_EN
     PG13   ------> ETH_TXD0
     PG14   ------> ETH_TXD1
*/
void LED1_int(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  HAL_GPIO_WritePin(GPIOA, X_STEP_Pin, GPIO_PIN_SET); 
}
void LED1_ONOFF(void)
{
  int i;
  HAL_GPIO_WritePin(GPIOA, X_STEP_Pin, GPIO_PIN_RESET);
  HAL_Delay(1000);
  //for(i=0;i<1000000;i++);
  HAL_GPIO_WritePin(GPIOA, X_STEP_Pin, GPIO_PIN_SET);
  HAL_Delay(1000);
  //for(i=0;i<1000000;i++);
}
void MX_GPIO_Init(void)    //**修改函数内容及头文件定义
{

    GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();


 #if defined(TFT70) 
  /*Configure GPIO pin : EXT_IRQ_Pin */
  GPIO_InitStruct.Pin = EXT_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(EXT_IRQ_GPIO_Port, &GPIO_InitStruct);
#endif
  /*Configure GPIO pins : WIFI_IO0_Pin WIFI_RST_Pin SW_DIO_Pin SW_CLK_Pin */
  //**GPIO_InitStruct.Pin = WIFI_IO0_Pin|WIFI_RST_Pin|SW_DIO_Pin|SW_CLK_Pin;
  //**GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  //**GPIO_InitStruct.Pull = GPIO_NOPULL;
  //**GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  //**HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : T_CS_Pin T_PEN_Pin */
  GPIO_InitStruct.Pin = T_CS_Pin|T_PEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
#if defined(TFT70)
  /*Configure GPIO pin : PtPin */   //SSD1963复位
  GPIO_InitStruct.Pin = GPIO_PIN_6;       
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
#endif
  GPIO_InitStruct.Pin = GPIO_PIN_2;       //蜂鸣器
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

#if defined(TFT35)
	GPIO_InitStruct.Pin = GPIO_PIN_1; 			//背光灯
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

#endif
  /*GPIO_InitStruct.Pin = GPIO_PIN_15;       //蜂鸣器
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);*/

  #if (debug_flg != 1)
  /*Configure GPIO pins : PB0_Pin PB1_Pin PB4_Pin */
  GPIO_InitStruct.Pin = PB0_Pin|PB1_Pin|PB4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  #endif

  /*Configure GPIO pins :PB12_Pin F_CS_Pin *///GPIO_PIN_2|
  GPIO_InitStruct.Pin = F_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   /*Configure GPIO pins :PB12_Pin */
  GPIO_InitStruct.Pin = PB12_Pin ;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SDIO_CD_Pin */
  GPIO_InitStruct.Pin = SDIO_CD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SDIO_CD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  //HAL_GPIO_WritePin(GPIOA, WIFI_IO0_Pin|WIFI_RST_Pin|SW_DIO_Pin|SW_CLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, T_CS_Pin|T_PEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level *///GPIO_PIN_2|
  HAL_GPIO_WritePin(GPIOB, PB12_Pin 
                          |F_CS_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOB,PB12_Pin, GPIO_PIN_RESET);

   /*Configure GPIO pin Output Level */
  //HAL_GPIO_WritePin(GPIOB, PB4_Pin, GPIO_PIN_SET);
  

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SDIO_CD_GPIO_Port, SDIO_CD_Pin, GPIO_PIN_RESET);
  
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);//蜂鸣器

  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);//TE
 #if defined(TFT70)
  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	#endif
//悬空管脚配置文件输入模式，减少功耗
#if 0//defined(TFT35)
GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_15;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_PULLDOWN;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_8;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_PULLDOWN;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_13;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_PULLDOWN;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_13;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_PULLDOWN;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_PULLDOWN;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

#endif
 }
void exit_PA0_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();	

	/*Configure GPIO pin : EXT_IRQ_Pin */
  GPIO_InitStruct.Pin = EXT_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;//GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(EXT_IRQ_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);	
}
/* USER CODE BEGIN 2 */

  /*Configure GPIO pin : PB0/PB1 */


/* USER CODE END 2 */

/**
  * @}
  */
/**************************add************************/
//测试输出口PB0/PB1初始化。
void T_GPIO_init()
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	
       __HAL_RCC_GPIOB_CLK_ENABLE();
	   
  	GPIO_InitStruct.Pin = GPIO_Pin_0|GPIO_Pin_1;//PB0 PB1
	GPIO_InitStruct.Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.Speed = GPIO_Speed_50MHz;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**************************add_end************************/
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
