/* Includes ------------------------------------------------------------------*/
#include "mks_test.h"
/*---------------------AT24C16 TEST BEGIN--------------------------*/
void mksEeprom_test()
{
  uint8_t eeprom_data_uint8_t[4] = {0,0,0,0};
  int16_t eeprom_data_int16_t = 0;
  int32_t eeprom_data_int32_t = 0;
  long eeprom_data_long = 0;
  float eeprom_data_float = 0;
  
  int16_t eeprom_addr1;
  int16_t eeprom_addr2;
  int16_t eeprom_addr3;
  int16_t eeprom_addr4;
  int16_t eeprom_addr5;
  
  eeval_t eeprom_data_eeval;
  
  int datalength=0;
  
    eeprom_addr1=1000;  
    eeprom_addr2 = eeprom_addr1+4;
    eeprom_addr3 = eeprom_addr1+8;
    eeprom_addr4 = eeprom_addr1+12;
    eeprom_addr5 = eeprom_addr1+16;
    
      
    datalength = sizeof(eeprom_data_uint8_t);
    HAL::eprSetByte(eeprom_addr5,0x12);
    eeprom_data_uint8_t[0] = HAL::eprGetByte(eeprom_addr5);
    HAL::AT24CXX_Read(eeprom_addr5,&eeprom_data_uint8_t[0],1);
    printf("uint8_t=0x%02X \r\n", eeprom_data_uint8_t[0]);
    eeprom_data_eeval=HAL::eprGetValue(eeprom_addr5, 1);
    printf("eeval_uint8_t=0x%02X \r\n", eeprom_data_eeval.b[0]);

    datalength = sizeof(eeprom_data_int16_t);
    HAL::eprSetInt16(eeprom_addr2,0x1234);
    eeprom_data_int16_t = HAL::eprGetInt16(eeprom_addr2);
    HAL::AT24CXX_Read(eeprom_addr2,&eeprom_data_uint8_t[0],2);
    eeprom_data_int16_t = eeprom_data_uint8_t[0]|(eeprom_data_uint8_t[1]<<8);
    printf("int16_t=0x%02X \r\n", eeprom_data_int16_t);
    eeprom_data_eeval=HAL::eprGetValue(eeprom_addr2, 2);
    printf("eeval_int16_t=0x%02X \r\n", eeprom_data_eeval.s);
    
    
    datalength = sizeof(eeprom_data_int32_t);
    HAL::eprSetInt32(eeprom_addr3,0x12345678);
    eeprom_data_int32_t = HAL::eprGetInt32(eeprom_addr3);
    HAL::AT24CXX_Read(eeprom_addr3,&eeprom_data_uint8_t[0],4);  
    eeprom_data_int32_t = eeprom_data_uint8_t[0]|(eeprom_data_uint8_t[1]<<8)|(eeprom_data_uint8_t[2]<<16)|(eeprom_data_uint8_t[3]<<24);
    printf("int32_t=0x%02X \r\n", eeprom_data_int32_t);
    eeprom_data_eeval=HAL::eprGetValue(eeprom_addr3, 4);
    printf("eeval_int32_t=0x%02X \r\n", eeprom_data_eeval.i);

    
    
    datalength = sizeof(eeprom_data_long);
    HAL::eprSetLong(eeprom_addr4,0x12345678);
    eeprom_data_long = HAL::eprGetLong(eeprom_addr4);
    HAL::AT24CXX_Read(eeprom_addr4,&eeprom_data_uint8_t[0],4);     
    eeprom_data_long = eeprom_data_uint8_t[0]|(eeprom_data_uint8_t[1]<<8)|(eeprom_data_uint8_t[2]<<16)|(eeprom_data_uint8_t[3]<<24);
    printf("long=0x%02X \r\n", eeprom_data_long);
    eeprom_data_eeval=HAL::eprGetValue(eeprom_addr4, 4);
    printf("eeval_long=0x%02X \r\n", eeprom_data_eeval.l);

    
    
    datalength = sizeof(eeprom_data_float);
    HAL::eprSetFloat(eeprom_addr5,32.53);
    eeprom_data_float = HAL::eprGetFloat(eeprom_addr5);
    HAL::AT24CXX_Read(eeprom_addr5,&eeprom_data_uint8_t[0],4);   
    //eeprom_data_float = eeprom_data_uint8_t[0]|(eeprom_data_uint8_t[1]<<8)|(eeprom_data_uint8_t[2]<<16)|(eeprom_data_uint8_t[3]<<24);
    //printf("float=0x%f \r\n", eeprom_data_float);
    eeprom_data_eeval=HAL::eprGetValue(eeprom_addr5, 4);
    printf("eeval_float=0x%f \r\n", eeprom_data_eeval.f);
    
   // while(1);
}
/*---------------------AT24C16 TEST END--------------------------*/

/*---------------------W25Q64 TEST BEGIN--------------------------*/


#define  sFLASH_ID              0xEF3015
#define  W25Q64_FLASH_ID        0xEF4017
#define  FLASH_WriteAddress     0x000000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress

#define countof(a) (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)

uint8_t Tx_Buffer[] = "\r\n www.makerbase.com STM32F407ZET6 SPI1 Flash DMA Mode Test Example:\r\n communication with an Winbond W25X64 W25Q64 SPI FLASH.";
uint8_t Rx_Buffer[BufferSize];
uint16_t Index;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = PASSED;
void SPI_FLASH_TEST(void);
TestStatus Buffercmp(u8* pBuffer1, u8* pBuffer2, u16 BufferLength);

void mksW25Q64Test(void)
{
   __IO uint32_t FlashID = 0;
   __IO uint32_t DeviceID = 0;
   __IO uint16_t W25QXX_TYPE = 0;
  
  W25QXX_TYPE = W25QXX_ReadID();	//0xEF16
  /* Get SPI Flash Device ID */
  DeviceID = SPI_FLASH_ReadDeviceID(); //0x16
  /* Get SPI FlashID */
  FlashID = SPI_FLASH_ReadID();	//0xEF4017

  /* Check the SPI Flash ID */
  if ((FlashID == sFLASH_ID) || (FlashID == W25Q64_FLASH_ID)) 
  {
    /* Perform a write in the Flash followed by a read of the written data */
    /* Erase SPI FLASH Sector to write on */
    SPI_FLASH_SectorErase(FLASH_SectorToErase);

    //delay_ms(10);//printf("\r\n SPI FLASH Write:\n\r%s\r\n ", Tx_Buffer);
    
    /* Write Tx_Buffer data to SPI FLASH memory */
    
    SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
     

     
    //delay_ms(10);
    /* Read data from SPI FLASH memory */
    SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
    for (Index = 0; Index < BufferSize; Index++) Rx_Buffer[Index]=0;
    SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_128);
    SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
    for (Index = 0; Index < BufferSize; Index++) Rx_Buffer[Index]=0;
    SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_4);
    SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
    for (Index = 0; Index < BufferSize; Index++) Rx_Buffer[Index]=0;
    
    SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
    
    /* Check the corectness of written dada */
    TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
    /* TransferStatus1 = PASSED, if the transmitted and received data by SPI1
       are the same */
    /* TransferStatus1 = FAILED, if the transmitted and received data by SPI1
       are different */

    /* Perform an erase in the Flash followed by a read of the written data */
    /* Erase SPI FLASH Sector to write on */
    SPI_FLASH_SectorErase(FLASH_SectorToErase);

    /* Read data from SPI FLASH memory */
    SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);

    /* Check the corectness of erasing operation dada */
    for (Index = 0; Index < BufferSize; Index++)
    {
      if (Rx_Buffer[Index] != 0xFF)
      {
        TransferStatus2 = FAILED;
      }
      //delay_ms(10);//printf(".");
    }
    
    /* TransferStatus2 = PASSED, if the specified sector part is erased */
    /* TransferStatus2 = FAILED, if the specified sector part is not well erased */

    if((PASSED == TransferStatus1) && (PASSED == TransferStatus2))
    {
      HAL_Delay(10);    //ok
    }
    else
    {
      HAL_Delay(10);    //err
    }
  }
  else
  {
    HAL_Delay(10);    //err
  }
  SPI_Flash_PowerDown();  

}
/*******************************************************************************
* Function Name  : Buffercmp
* Description    : Compares two buffers.
* Input          : - pBuffer1, pBuffer2: buffers to be compared.
*                : - BufferLength: buffer's length
* Output         : None
* Return         : PASSED: pBuffer1 identical to pBuffer2
*                  FAILED: pBuffer1 differs from pBuffer2
*******************************************************************************/
TestStatus Buffercmp(u8* pBuffer1, u8* pBuffer2, u16 BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}


/*---------------------W25Q64 TEST END--------------------------*/

/*---------------------SDIO+FATFS TEST BEGIN--------------------------*/
  FATFS SDFatFs;  /* File system object for SD card logical drive */
  FIL MyFile;     /* File object */
//#define countof(a) (sizeof(a) / sizeof(*(a)))
#define sdBufferSize (countof(wtext)-1)
  uint8_t wtext[] = "www.makerbase.com STM32F407ZET6 SDIO+FATFS DMA Mode Test Example:\r\nThis is mksRobinPro STM32F407ZET6 working with FatFs\r\n"; /* File write buffer */
  uint8_t rtext[sdBufferSize];                                   /* File read buffer */
  volatile TestStatus TransferStatusSD = FAILED;
void mksSdCardTest()
{

  FRESULT res;                                          /* FatFs function common result code */
  uint32_t byteswritten, bytesread;                     /* File write/read counts */

  /*##-1- Link the micro SD disk I/O driver ##################################*/
  //链接 SD 底层驱动函数到 FATFS 文件系统，这个在 MX_FATFS_Init()函数中已经完成
  //if(FATFS_LinkDriver(&SD_Driver, SD_Path) == 0)
  {
    /*##-2- Register the file system object to the FatFs module ##############*/
    if(f_mount(&SDFatFs, (TCHAR const*)SD_Path, 0) != FR_OK)
    {
      /* FatFs Initialization Error */
      Error_Handler();
    }
    else
    {
      /*##-3- Create a FAT file system (format) on the logical drive #########*/
      /* WARNING: Formatting the uSD card will delete all content on the device */
      //对 SD 卡进行格式化
#if 0
      if(f_mkfs((TCHAR const*)SD_Path, 0, 0) != FR_OK)
      {
        /* FatFs Format Error */
        Error_Handler();
      }
      else
#endif        
      {       
        /*##-4- Create and Open a new text file object with write access #####*/
        if(f_open(&MyFile, "1:\STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
        {
          /* 'STM32.TXT' file Open for write Error */
          Error_Handler();
        }
        else
        {
          /*##-5- Write data to the text file ################################*/
          res = f_write(&MyFile, wtext, sizeof(wtext), (uint32_t *)&byteswritten);
          
          if((byteswritten == 0) || (res != FR_OK))
          {
            /* 'STM32.TXT' file Write or EOF Error */
            Error_Handler();
          }
          else
          {
            /*##-6- Close the open text file #################################*/
            f_close(&MyFile);
            
            /*##-7- Open the text file object with read access ###############*/
            if(f_open(&MyFile, "1:\STM32.TXT", FA_READ) != FR_OK)
            {
              /* 'STM32.TXT' file Open for read Error */
              Error_Handler();
            }
            else
            {
              /*##-8- Read data from the text file ###########################*/
              res = f_read(&MyFile, rtext, sizeof(rtext), (UINT*)&bytesread);
              
              if((bytesread == 0) || (res != FR_OK))
              {
                /* 'STM32.TXT' file Read or EOF Error */
                Error_Handler();
              }
              else
              {
                /*##-9- Close the open text file #############################*/
                f_close(&MyFile);
                
                /*##-10- Compare read data with the expected data ############*/
                TransferStatusSD = Buffercmp(wtext, rtext, sdBufferSize);
                if(PASSED == TransferStatusSD)
                {                
                  /* Success of the demo: no error occurrence */
                  HAL_Delay(10);    //ok
                }
                else
                {
                  Error_Handler();
                }
              }
            }
          }
        }
      }
    }
  }

}
/*---------------------SDIO+FATFS TEST END--------------------------*/

/*---------------------USB+FATFS TEST BEGIN------------------------*/
extern ApplicationTypeDef Appli_state;
FATFS USBDISKFatFs;           /* File system object for USB disk logical drive */
FIL usbFile;                   /* File object */
//char USBDISKPath[4];          /* USB Host logical drive path */
USBH_HandleTypeDef hUSB_Host; /* USB Host handle */
volatile TestStatus TransferStatusUSB = FAILED;
void usbFileReadTest(void);
void MSC_Application();
void mksUSBTest()
{
  static ApplicationTypeDef pre_state = APPLICATION_IDLE;
  volatile FRESULT fr;
  FATFS fs;
  FIL fil;
  UINT off = 0;
  uint8_t buff[20];
  int i;  
  while (1)
  {
    MX_USB_HOST_Process();

      switch(Appli_state)
      {
      //case APPLICATION_START:
      case APPLICATION_READY:
        MSC_Application();
        usbFileReadTest();
        Appli_state = APPLICATION_IDLE;
        break;
        
      case APPLICATION_IDLE:
      default:
       break;      
      }    
  }
}

static void MSC_Application(void)
{
  #define usbBufferSize (countof(usbwtext)-1)
  FRESULT res;                                          /* FatFs function common result code */
  uint32_t byteswritten, bytesread;                     /* File write/read counts */
  //uint8_t usbwtext[] = "This is mksRobinPro working with USB-FatFs."; /* File write buffer */
  uint8_t usbwtext[] = "This is mksRobinPro working with USB-FatFs Start. 1. Redistribution of source code must retain the above copyright notice,2. Redistributions in binary form must reproduce the above copyright notice,and/or other materials provided with the distribution.3. Neither the name of STMicroelectronics nor the names of other contributors to this software may be used to endorse or promote products derived from this software without specific written permission. 4. This software, including modifications and/or derivative works of this software, must execute solely and exclusively on microcontroller or microprocessor devices manufactured by or for STMicroelectronics. 5. Redistribution and use of this software other than as permitted under this license is void and will automatically terminate your rights under  this license. 6.Redistribution and use in source and binary forms, with or without modification, are permitted, provided that the following conditions are met. This is mksRobinPro working with USB-FatFs End.";
  uint8_t usbrtext[usbBufferSize];                                   /* File read buffer */
  
  /* Register the file system object to the FatFs module */
  if(f_mount(&USBDISKFatFs, (TCHAR const*)USBH_Path, 0) != FR_OK)
  {
    /* FatFs Initialization Error */
    Error_Handler();
  }
  else
  {
    HAL_Delay(10);
    /* Create and Open a new text file object with write access */
    //if(f_open(&usbFile, "STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) 
    if(f_open(&usbFile, "0:/STM32_USB.TXT", FA_READ | FA_WRITE | FA_CREATE_ALWAYS) != FR_OK) 
    {   
      /* 'STM32.TXT' file Open for write Error */
      Error_Handler();
    }
    else
    {
      /* Write data to the text file */
      res = f_write(&usbFile, usbwtext, sizeof(usbwtext), &byteswritten);
      
      if((byteswritten == 0) || (res != FR_OK))
      {
        /* 'STM32.TXT' file Write or EOF Error */
        Error_Handler();
      }
      else
      {
        /* Close the open text file */
        f_close(&usbFile);
        
        /* Open the text file object with read access */
        if(f_open(&usbFile, "0:/STM32_USB.TXT", FA_READ) != FR_OK)
        {
          /* 'STM32.TXT' file Open for read Error */
          Error_Handler();
        }
        else
        {
          /* Read data from the text file */
          res = f_read(&usbFile, usbrtext, sizeof(usbrtext), &bytesread);
          
          if((bytesread == 0) || (res != FR_OK))
          {
            /* 'STM32.TXT' file Read or EOF Error */
            Error_Handler();
          }
          else
          {
            /* Close the open text file */
            f_close(&usbFile);
            
            /* Compare read data with the expected data */
                TransferStatusUSB = Buffercmp(usbwtext, usbrtext, usbBufferSize);
                if(PASSED == TransferStatusUSB)
                {                
                  /* Success of the demo: no error occurrence */
                  HAL_Delay(10);    //ok
                }
                else
                {
                  Error_Handler();
                }

          }
        }
      }
    }
  }
/*-------------  usbFileReadTest --------------*/
    volatile long usbReadCnt=0;
    while(usbReadCnt++ < 10000)
    {
      if(f_open(&usbFile, "0:/STM32_USB.TXT", FA_READ) != FR_OK) Error_Handler();
      res = f_read(&usbFile, usbrtext, sizeof(usbrtext), &bytesread);
      if((bytesread == 0) || (res != FR_OK))   Error_Handler();
      f_close(&usbFile);
      TransferStatusUSB = Buffercmp(usbwtext, usbrtext, usbBufferSize);
      if(PASSED != TransferStatusUSB)  Error_Handler();
      memcpy(&usbrtext,0,usbBufferSize); 
    }
    HAL_Delay(10);
/*-------------  usbFileReadTest --------------*/  
  /* Unlink the USB disk I/O driver */
  //FATFS_UnLinkDriver(USBH_Path);
}

static void usbFileReadTest(void)
{
}
/*---------------------USB+FATFS TEST END--------------------------*/

/*---------------------TFT-LCD TEST BEGIN--------------------------*/
void mksTFTLCDTest()
{
  
}
/*---------------------TFT-LCD TEST END--------------------------*/





/* USER CODE END 0 */