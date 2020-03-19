/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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
#include "usart.h"

#include "gpio.h"
#include "dma.h"
#include "wifi_module.h"


/* USER CODE BEGIN 0 */

uint8_t mksRxBuffer[20];
uint8_t mksUsart1Rx;

uint8_t mksUsart3Rx;


/* USER CODE END 0 */
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart6_rx;
DMA_HandleTypeDef hdma_usart6_tx;

/* USART1 init function */

void MX_USART1_UART_Init(int readId_1)
{

  huart1.Instance = USART1;
	switch(readId_1)
	{
		case 1:huart1.Init.BaudRate = 9600;break;
		case 2:huart1.Init.BaudRate = 57600;break;
		case 3:huart1.Init.BaudRate = 115200;break;
		case 4:huart1.Init.BaudRate = 250000;break;
		case 5:huart1.Init.BaudRate = 1958400;break;
		default:huart1.Init.BaudRate = 115200;break;			
	}
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

/* USART3 init function */

void MX_USART3_UART_Init(int readId)
{

  huart3.Instance = USART3;
  if(readId==1){
  	huart3.Init.BaudRate = 9600;
  }
  else if(readId==2){
  	huart3.Init.BaudRate = 57600;
  }
  else if(readId==3){
  	huart3.Init.BaudRate = 115200;
  }
  else{
  	huart3.Init.BaudRate = 250000;
  }
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }

}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;

	if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = TFT_WIFI_TX_Pin|TFT_WIFI_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		if(huart1.Init.BaudRate == 1958400)
		{
	    /* Peripheral DMA init*/
	  
	    hdma_usart1_rx.Instance = DMA2_Stream2;
	    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
	    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
	    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
	    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
	    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
	    {
	      Error_Handler();
	    }

	    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);
		#if 0
	    hdma_usart1_tx.Instance = DMA2_Stream7;
	    hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
	    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
	    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
	    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
	    hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
	    {
	      Error_Handler();
	    }

	    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);
		#endif
		}
		else
		{
    /* Peripheral interrupt init */
   		HAL_NVIC_SetPriority(USART1_IRQn, 3, 0);
    	HAL_NVIC_EnableIRQ(USART1_IRQn);
		}
		
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else
  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = TX0_Pin|RX0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(USART3_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspInit 0 */

  /* USER CODE END USART6_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();
  
    /**USART6 GPIO Configuration    
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX 
    */
    GPIO_InitStruct.Pin = WIFI_TX_Pin|WIFI_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* Peripheral DMA init*/
  
    hdma_usart6_rx.Instance = DMA2_Stream1;
    hdma_usart6_rx.Init.Channel = DMA_CHANNEL_5;
    hdma_usart6_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart6_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart6_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart6_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart6_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart6_rx.Init.Mode = DMA_NORMAL;
    hdma_usart6_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart6_rx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    hdma_usart6_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
    hdma_usart6_rx.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_usart6_rx.Init.PeriphBurst = DMA_PBURST_SINGLE;
    if (HAL_DMA_Init(&hdma_usart6_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart6_rx);

    hdma_usart6_tx.Instance = DMA2_Stream7;
    hdma_usart6_tx.Init.Channel = DMA_CHANNEL_5;
    hdma_usart6_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart6_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart6_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart6_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart6_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart6_tx.Init.Mode = DMA_NORMAL;
    hdma_usart6_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart6_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart6_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart6_tx);

    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspInit 1 */

  /* USER CODE END USART6_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

		if(uartHandle->Instance==USART1)
		{
		/* USER CODE BEGIN USART1_MspDeInit 0 */
	
		/* USER CODE END USART1_MspDeInit 0 */
			/* Peripheral clock disable */
			__HAL_RCC_USART1_CLK_DISABLE();
		
			/**USART3 GPIO Configuration		
			PA9	 ------> USART1_TX
			PA10		 ------> USART1_RX 
			*/
			HAL_GPIO_DeInit(GPIOA, TFT_WIFI_TX_Pin|TFT_WIFI_RX_Pin);
	
			/* Peripheral interrupt Deinit*/
			HAL_NVIC_DisableIRQ(USART1_IRQn);
	
		/* USER CODE BEGIN USART1_MspDeInit 1 */
	
		/* USER CODE END USART1_MspDeInit 1 */
		}
		else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    HAL_GPIO_DeInit(GPIOB, TX0_Pin|RX0_Pin);

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(USART3_IRQn);

  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspDeInit 0 */

  /* USER CODE END USART6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART6_CLK_DISABLE();
  
    /**USART6 GPIO Configuration    
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX 
    */
    HAL_GPIO_DeInit(GPIOC, WIFI_TX_Pin|WIFI_RX_Pin);

    /* Peripheral DMA DeInit*/
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(USART6_IRQn);

  /* USER CODE BEGIN USART6_MspDeInit 1 */

  /* USER CODE END USART6_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

int i=0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance==USART3)
  {
    mksRxBuffer[i++] = mksUsart3Rx;
    HAL_UART_Receive_IT(&huart3,&mksUsart3Rx,1);
  }
	else if(huart->Instance==USART1)
	{
    //mksRxBuffer[i++] = mksUsart1Rx;
		HAL_UART_Receive_IT(&huart1,&mksUsart1Rx,1);
		//if(i>30)
		//{
		//	i=0;
		//	return;
		//}
	}
}


/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
