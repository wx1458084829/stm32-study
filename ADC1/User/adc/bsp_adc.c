#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue;

static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_GPIO_APBxClock_FUN(ADC_GPIO_CLK,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = ADC_PIN;
	
	GPIO_Init(ADC_PORT, &GPIO_InitStruct);
	
}
	


static void ADC_config(void)
 {
	 ADC_InitTypeDef ADC_InitStruct;
	 //打开ADC时钟
	 ADC_APBxClock_FUN(ADC_CLK,ENABLE);
	//ADC模式，只使用一个ADC，独立模式
	 ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	 //禁止扫描模式，多通道才需要
	 ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	 //连续转换模式
	 ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	 //不使用外部触发转换，软件开启即可
	 ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	 //结果右对齐
	 ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	 //转换通道1个
	 ADC_InitStruct.ADC_NbrOfChannel = 1;
	 
	 
	 //初始化ADC
	 ADC_Init(ADC_x,&ADC_InitStruct);
	 
	 //配置8分频，即9M
	 RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	 
	 // 配置 ADC 通道转换顺序为 1，第一个转换，采样时间为 55.5 个时钟周期
	 ADC_RegularChannelConfig(ADC_x,ADC_CHANNEL,1,ADC_SampleTime_55Cycles5);
	 
	 // ADC 转换结束产生中断，在中断服务程序中读取转换值
	 ADC_ITConfig(ADC_x,ADC_IT_EOC,ENABLE);
	 
	 //开启ADC
	 ADC_Cmd(ADC_x, ENABLE);


	 // 初始化 ADC 校准寄存器
	 ADC_ResetCalibration(ADC_x);
	 // 等待校准寄存器初始化完成
	 while (ADC_GetResetCalibrationStatus(ADC_x));

 // ADC 开始校准
	 ADC_StartCalibration(ADC_x);
	 // 等待校准完成
	 while (ADC_GetCalibrationStatus(ADC_x));

	// 由于没有采用外部触发，所以使用软件触发 ADC 转换
	 ADC_SoftwareStartConvCmd(ADC_x,ENABLE);

 }

static void ADC_NVIC_Config(void)
 {
	 NVIC_InitTypeDef NVIC_InitStructure;
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	 NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);
}
 
void ADCx_Init(void)
{

	ADC_GPIO_Config();
	ADC_config();
		ADC_NVIC_Config();
}
