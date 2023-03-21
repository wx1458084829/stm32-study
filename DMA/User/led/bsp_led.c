#include "bsp_led.h"
void LED_GPIO_Config(void)
{ 
		GPIO_InitTypeDef GPIO_InitStruct;
		
		//初始化LED1
    RCC_APB2PeriphClockCmd(LED1_GPIO_CLK,ENABLE);
    GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStruct);
		//初始化LED2
    RCC_APB2PeriphClockCmd(LED2_GPIO_CLK,ENABLE);	
	  GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED2_GPIO_PORT,&GPIO_InitStruct);
	
		// 设置默认高电平
		GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);
		GPIO_SetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);
}
/**
  * @brief  开启LED
  * @param  LED_N
  * @retval  None
  */
void LED_ON(LED_N LedVal)
{
		if(LedVal == LED1)
		{
				GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);
		}else if(LedVal == LED2)
		{
				GPIO_ResetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);
		}
}
/**
  * @brief  关闭LED
  * @param  LED_N
  * @retval  None
  */
void LED_OFF(LED_N LedVal)
{
		if(LedVal == LED1)
		{
				GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);
		}else if(LedVal == LED2)
		{
				GPIO_SetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);
		}
}
