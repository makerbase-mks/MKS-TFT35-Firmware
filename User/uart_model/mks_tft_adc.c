
#include "mks_tft_com.h"



/* STM32芯片ADC转换结果DR寄存器基地址 */
#define DR_ADDRESS      ((uint32_t)0x4001244C) 

/* 存放ADC为12位模数转换器结果的变量，只有ADCConvertedValue的低12位有效 */
__IO uint16_t ADCConvertedValue;     // 

/**-------------------------------------------------------
  * @函数名 ADC_GPIO_Configuration
  * @功能   ADC模数转换的GPIO配置初始化函数
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void ADC_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 使能GPIOC时钟      */
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /*PC0 作为模拟通道11输入引脚 */                       
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       //管脚0
		//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;       //管脚8
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
   // GPIO_Init(GPIOC, &GPIO_InitStructure);   
		GPIO_Init(GPIOA, &GPIO_InitStructure); 	
}

/**-------------------------------------------------------
  * @函数名 SZ_STM32_ADC_Configuration
  * @功能   ADC模数转换的参数配置函数
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void SZ_STM32_ADC_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;        //DMA初始化结构体声明  
	ADC_InitTypeDef ADC_InitStructure;        //ADC初始化结构体声明   

    /* 使能ADC1、DMA1时钟*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		 //使能DMA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	  //使能ADC时钟


    /*对DMA进行配置*/
    DMA_DeInit(DMA1_Channel1);		  //开启DMA1的第一通道
    DMA_InitStructure.DMA_PeripheralBaseAddr = DR_ADDRESS;		  //DMA对应的外设基地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;   //内存存储基地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	//DMA的转换模式为SRC模式，由外设搬移到内存
    DMA_InitStructure.DMA_BufferSize = 1;		   //DMA缓存大小，1个
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//接收一次数据后，设备地址禁止后移
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;	//关闭接收一次数据后，目标内存地址后移
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //定义外设数据宽度为16位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  //DMA搬移数据尺寸，HalfWord就是为16位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   //转换模式，循环缓存模式。
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMA优先级高
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;		  //M2M模式禁用
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);          
    /* Enable DMA1 channel1 */
    DMA_Cmd(DMA1_Channel1, ENABLE);

    /* 对ADC进行配置*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//独立的转换模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;		  //关闭扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   //开启连续转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//本实验使用的是软件触发方式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;   //对齐方式,ADC为12位中，右对齐方式
    ADC_InitStructure.ADC_NbrOfChannel = 1;	 //开启通道数，1个
    ADC_Init(ADC1, &ADC_InitStructure);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
    //ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);  //ADC通道组， 第1个通道 采样顺序1，转换时间 
     ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);  //ADC通道组， 第1个通道 采样顺序1，转换时间                     
    ADC_DMACmd(ADC1, ENABLE); //使能ADC1 DMA传输 
    ADC_Cmd(ADC1, ENABLE);   //使能ADC1

    ADC_ResetCalibration(ADC1);	   //重置ADC校准寄存器  	  
    while(ADC_GetResetCalibrationStatus(ADC1));  //等待重置完成
		 
    ADC_StartCalibration(ADC1);	    //开始校准 
    while(ADC_GetCalibrationStatus(ADC1));	// 等待校准完成
		   
    /*连续转换开始，ADC通过DMA方式不断的更新RAM区*/ 
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/**-------------------------------------------------------
  * @函数名 GetADCConvertedValue
  * @功能   获取ADC模数转换的结果
  * @参数   无
  * @返回值 ADC转换结果的变量，只有的低12位有效
***------------------------------------------------------*/
uint16_t GetADCConvertedValue(void)
{
    return ADCConvertedValue;
}




