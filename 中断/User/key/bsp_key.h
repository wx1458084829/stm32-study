#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "stm32f10x.h"

//引脚定义
#define KEY1_GPIO_PORT GPIOC
#define KEY1_GPIO_PIN GPIO_Pin_13
#define KEY1_GPIO_CLK (RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO) //要开启AFIO和本身GPIO

#define KEY1_EXTI_PORTSOURCE GPIO_PortSourceGPIOC
#define KEY1_EXTI_PINSOURCE GPIO_PinSource13
#define KEY1_EXTI_LINE EXTI_Line13
#define KEY1_EXTI_IRQ EXTI15_10_IRQn //5-10都是连在一起的



#define KEY1_IRQHandler EXTI15_10_IRQHandler


void Key_Init(void);


#endif
