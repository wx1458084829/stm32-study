#ifndef __BSP_RCC_CLK_CONFIG_H
#define __BSP_RCC_CLK_CONFIG_H
#include "stm32f10x.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x);
void MCO_GPIO_Config(void);
#endif
