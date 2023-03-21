#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"
int main(void)
{
		LED_GPIO_Config();
		LED_1(OFF);
		LED_2(OFF);
		LED_1(ON);
		Key_Init();
    while(1){
		}
}
