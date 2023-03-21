#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_i2c_gpio.h"
#include "bsp_i2c_ee.h"


#include <stdio.h>
int main(void)
{
		USART_Config();
		i2c_CfgGpio();
		LED_GPIO_Config();
		LED_1(OFF);
		LED_2(OFF);
		printf("eeprom 软件模拟 i2c 测试例程 \r\n");

	 if (ee_Test() == 1) {
		LED_1(OFF);
	 } else {
		LED_1(ON);
	 }
    while(1)
		{
		}
}
