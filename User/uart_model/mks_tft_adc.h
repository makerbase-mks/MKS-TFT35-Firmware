#ifndef MKS_TFT_ADC_H
#define MKS_TFT_ADC_H

extern __IO uint16_t ADCConvertedValue;

extern void ADC_GPIO_Configuration(void);
extern void SZ_STM32_ADC_Configuration(void);
extern uint16_t GetADCConvertedValue(void);


#endif