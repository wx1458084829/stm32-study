#include "stm32f10x.h"
#include "bsp_rcc_clk_config.h"
int main(void)
{
//		HSE_SetSysClk(RCC_PLLMul_16);
		MCO_GPIO_Config();
		RCC_MCOConfig(RCC_MCO_SYSCLK);
    return 0;
}
