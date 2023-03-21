#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

//led1 pb5
#define LED_1_GPIO_PIN GPIO_Pin_5
#define LED_1_GPIO_PORT GPIOB

//led2 pd12
#define LED_2_GPIO_PIN GPIO_Pin_12
#define LED_2_GPIO_PORT GPIOD

#define ON   1
#define OFF   0

#define LED_1(a) if(a) GPIO_ResetBits(LED_1_GPIO_PORT, LED_1_GPIO_PIN);\
else GPIO_SetBits(LED_1_GPIO_PORT, LED_1_GPIO_PIN);

#define LED_2(a) if(a) GPIO_ResetBits(LED_2_GPIO_PORT, LED_2_GPIO_PIN);\
else GPIO_SetBits(LED_2_GPIO_PORT, LED_2_GPIO_PIN);

void LED_GPIO_Config(void);

#endif
