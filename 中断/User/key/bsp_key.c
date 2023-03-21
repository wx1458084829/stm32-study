#include "bsp_key.h"


//stctic 设置为当前文件调用(静态函数的作用域仅限于本文件，不能被其它文件调用。)
/**
  * @brief  初始化NVIC
  * @param  None
  * @retval  None
  */
static void EXTI_NVIC_Config(void)
{
	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// 设置优先级分组（分到了第1组）
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	// 设置IRQ通道,即配置中断的来源，这里是来自EXTI
	NVIC_InitStruct.NVIC_IRQChannel = KEY1_EXTI_IRQ;
	// 设置中断主优先级
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	// 设置中断次优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	// 使能中断
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

/**
  * @brief  初始化按键
  * @param  None
  * @retval  None
  */
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	// 调用上述代码初始化EXTI
	EXTI_NVIC_Config();
	
	// 初始化GPIO
	GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;  //设置为上拉输入模式
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStruct);
	// 开启GPIO时钟（包含AFIO）
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);	// 开启时钟
	
	// 选择EXTI的输入线
	GPIO_EXTILineConfig(KEY1_EXTI_PORTSOURCE,KEY1_EXTI_PINSOURCE);

	// 设置EXTI的输入线
	EXTI_InitStruct.EXTI_Line = KEY1_EXTI_LINE;
	EXTI_InitStruct.EXTI_LineCmd =ENABLE;
	// 设置模式为中断
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	// 设置触发模式
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
}


