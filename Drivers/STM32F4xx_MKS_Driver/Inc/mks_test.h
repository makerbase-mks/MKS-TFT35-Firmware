/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MKS_TEST_H_
#define __MKS_TEST_H_
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "w25qxx.h"
#include "spi_flash.h"
void mksEeprom_test();   
void mksW25Q64Test(void);
void mksSdCardTest();
void mksUSBTest();
#ifdef __cplusplus
}
#endif

#endif