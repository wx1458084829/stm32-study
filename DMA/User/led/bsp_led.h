#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"
 
 
//LED1 - PB5 
#define LED1_GPIO_PIN GPIO_Pin_5
#define LED1_GPIO_PORT GPIOB
#define LED1_GPIO_CLK RCC_APB2Periph_GPIOB

//LED2 - PD12 
#define LED2_GPIO_PIN GPIO_Pin_12
#define LED2_GPIO_PORT GPIOD
#define LED2_GPIO_CLK RCC_APB2Periph_GPIOD


/** 
  * @brief  LED枚举定义
  */

typedef enum
{ LED1 = 1,
  LED2 = 2
} LED_N;


void LED_GPIO_Config(void);
void LED_ON(LED_N LedVal);
void LED_OFF(LED_N LedVal);


#endif /*__BSP_LED_H*/
