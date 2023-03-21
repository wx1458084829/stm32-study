#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_systick.h"
int main(void)
{
	//初始化LED
	  LED_GPIO_Config();
		
	//设置LED交替闪烁
		while(1)
		{
			LED_1(OFF);
			LED_2(ON);
			SysTick_Delay_ms(1000);
			LED_1(ON);
			LED_2(OFF);
			SysTick_Delay_ms(1000);
		}
}

