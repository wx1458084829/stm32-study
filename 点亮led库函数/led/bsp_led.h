#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"
 
#define LED_G_GPIO_PIN GPIO_Pin_5
#define LED_G_GPIO_PORT GPIOB

#define ON   1
#define OFF   0

#define LED_G(a) if(a) GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);\
else GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);

void LED_GPIO_Config(void);

#endif /*__BSP_LED_H*/
