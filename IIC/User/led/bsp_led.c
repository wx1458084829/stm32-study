#include "bsp_led.h"

void LED_GPIO_Config(void)
{
    // 开启APB2总线时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD,ENABLE);
    //初始化第一个LED
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = LED_1_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_1_GPIO_PORT,&GPIO_InitStruct);
	 //初始化第二个LED
	  GPIO_InitStruct.GPIO_Pin = LED_2_GPIO_PIN;
		GPIO_Init(LED_2_GPIO_PORT,&GPIO_InitStruct);
}
