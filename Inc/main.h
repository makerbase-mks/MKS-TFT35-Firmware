/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

/******************增加部分**************/
#define debug_flg 	0			//用于测试调试输出方波。
typedef enum 
{
	printer_pause_reprint = 0xa7,		//暂停续打
	printer_pwdwn_reprint,					//断电续打
	printer_normal,									//无续打
} RE_PRINT_STATUS;

void clock_run();
void get_cur_temp();
void get_cmd_ack();

void PB0_PB1_pwrdn_mtrdn();
void PB4_Close_machine();
void PowerOff_Filament_Check();



typedef enum
{
	PRINTER_NOT_CONNECT = 0,
	PRINTER_CONNECT_OK,	
	PRINTER_OPERATING,
	PRINTER_OPERATE_OK,
} PRINTER_STATE;

#define	GET_CUR_TEM_COMMAND			"M105\n"
/**********************结束*****************/
#define Y_DIR_Pin GPIO_PIN_2
#define Y_DIR_GPIO_Port GPIOE
#define Y_STEP_Pin GPIO_PIN_3
#define Y_STEP_GPIO_Port GPIOE
#define Y_ENA_Pin GPIO_PIN_4
#define Y_ENA_GPIO_Port GPIOE
#define X_DIR_Pin GPIO_PIN_5
#define X_DIR_GPIO_Port GPIOE
#define X_STEP_Pin GPIO_PIN_6
#define X_STEP_GPIO_Port GPIOE
#define X_ENA_Pin GPIO_PIN_13
#define X_ENA_GPIO_Port GPIOC
#define FAN_Pin GPIO_PIN_1
#define FAN_GPIO_Port GPIOF
#define HEATER2_Pin GPIO_PIN_2
#define HEATER2_GPIO_Port GPIOF
#define HEATER1_Pin GPIO_PIN_3
#define HEATER1_GPIO_Port GPIOF
#define BED_Pin GPIO_PIN_4
#define BED_GPIO_Port GPIOF
#define TB_Pin GPIO_PIN_0
#define TB_GPIO_Port GPIOC
#define TH1_Pin GPIO_PIN_2
#define TH1_GPIO_Port GPIOC
#define TH2_Pin GPIO_PIN_3
#define TH2_GPIO_Port GPIOC
#define FALA_CTRL_Pin GPIO_PIN_0
#define FALA_CTRL_GPIO_Port GPIOA
#define EXT_IRQ_Pin GPIO_PIN_0
#define EXT_IRQ_GPIO_Port GPIOA
#define EXT_CTR_Pin GPIO_PIN_6
#define EXT_CTR_GPIO_Port GPIOA
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define BEEPER_Pin GPIO_PIN_11
#define BEEPER_GPIO_Port GPIOF
#define MT_DET2_Pin GPIO_PIN_13
#define MT_DET2_GPIO_Port GPIOF
#define MT_DET1_Pin GPIO_PIN_14
#define MT_DET1_GPIO_Port GPIOF
#define PW_DET_Pin GPIO_PIN_0
#define PW_DET_GPIO_Port GPIOG
#define PW_OFF_Pin GPIO_PIN_1
#define PW_OFF_GPIO_Port GPIOG
#define TX0_Pin GPIO_PIN_10
#define TX0_GPIO_Port GPIOB
#define RX0_Pin GPIO_PIN_11
#define RX0_GPIO_Port GPIOB
#define WIFI_CS_Pin GPIO_PIN_12
#define WIFI_CS_GPIO_Port GPIOB
#define WIFI_RST_Pin GPIO_PIN_2
#define WIFI_RST_GPIO_Port GPIOG
#define TH_CS_Pin GPIO_PIN_11
#define TH_CS_GPIO_Port GPIOD
#define BLACK_LIGHT_Pin GPIO_PIN_12
#define BLACK_LIGHT_GPIO_Port GPIOD
#define FSMC_RESET_Pin GPIO_PIN_13
#define FSMC_RESET_GPIO_Port GPIOD
#define Z__Pin GPIO_PIN_3
#define Z__GPIO_Port GPIOG
#define Z_G4_Pin GPIO_PIN_4
#define Z_G4_GPIO_Port GPIOG
#define Y__Pin GPIO_PIN_5
#define Y__GPIO_Port GPIOG
#define Y_G6_Pin GPIO_PIN_6
#define Y_G6_GPIO_Port GPIOG
#define X__Pin GPIO_PIN_7
#define X__GPIO_Port GPIOG
#define X_G8_Pin GPIO_PIN_8
#define X_G8_GPIO_Port GPIOG
#define WIFI_TX_Pin GPIO_PIN_6
#define WIFI_TX_GPIO_Port GPIOC
#define WIFI_RX_Pin GPIO_PIN_7
#define WIFI_RX_GPIO_Port GPIOC
#define E1_DIR_Pin GPIO_PIN_15
#define E1_DIR_GPIO_Port GPIOA
#define E1_STEP_Pin GPIO_PIN_3
#define E1_STEP_GPIO_Port GPIOD
#define E1_ENA_Pin GPIO_PIN_6
#define E1_ENA_GPIO_Port GPIOD
#define E0_DIR_Pin GPIO_PIN_9
#define E0_DIR_GPIO_Port GPIOG
#define E0_STEP_Pin GPIO_PIN_10
#define E0_STEP_GPIO_Port GPIOG
#define FL_CS_Pin GPIO_PIN_15
#define FL_CS_GPIO_Port GPIOG
#define E0_ENA_Pin GPIO_PIN_8
#define E0_ENA_GPIO_Port GPIOB
#define Z_DIR_Pin GPIO_PIN_9
#define Z_DIR_GPIO_Port GPIOB
#define Z_STEP_Pin GPIO_PIN_0
#define Z_STEP_GPIO_Port GPIOE
#define Z_ENA_Pin GPIO_PIN_1
#define Z_ENA_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */       //**增加部分
#define EXT_IRQ_Pin GPIO_PIN_0
#define EXT_IRQ_GPIO_Port GPIOA
#define WIFI_IO0_Pin GPIO_PIN_1
#define WIFI_IO0_GPIO_Port GPIOA
#define T_CS_Pin GPIO_PIN_4
#define T_CS_GPIO_Port GPIOC
#define T_PEN_Pin GPIO_PIN_5
#define T_PEN_GPIO_Port GPIOC
#define PB0_Pin GPIO_PIN_0
#define PB4_Pin GPIO_PIN_4
#define PB0_GPIO_Port GPIOB
#define PB1_Pin GPIO_PIN_1
#define PB1_GPIO_Port GPIOB
#define PB12_Pin GPIO_PIN_12
#define PB12_GPIO_Port GPIOB
#define WIFI_RST_Pin GPIO_PIN_8
#define WIFI_RST_GPIO_Port GPIOA
#define SW_DIO_Pin GPIO_PIN_13
#define SW_DIO_GPIO_Port GPIOA
#define SW_CLK_Pin GPIO_PIN_14
#define SW_CLK_GPIO_Port GPIOA
#define SDIO_CD_Pin GPIO_PIN_3
#define SDIO_CD_GPIO_Port GPIOD
#define F_CS_Pin GPIO_PIN_9
#define F_CS_GPIO_Port GPIOB
#define GPIO_Mode_Out_OD 0x14
#define GPIO_Pin_0    ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_Pin_1    ((uint16_t)0x0002)  /* Pin 1 selected */
#define  GPIO_Speed_50MHz  0x02
//tan 20171008
#define TFT_WIFI_TX_Pin GPIO_PIN_9
#define TFT_WIFI_TX_GPIO_Port GPIOA
#define TFT_WIFI_RX_Pin GPIO_PIN_10
#define TFT_WIFI_RX_GPIO_Port GPIOA

/* USER CODE END Private defines */

/**
  * @}
  */ 
/****************************************add***********************************/

/****************************************end***********************************/
/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
