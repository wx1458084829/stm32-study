#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_i2c_gpio.h"
#include "bsp_i2c_ee.h"


#include <stdio.h>
int main(void)
{
		USART_Config(); //初始化串口
		i2c_CfgGpio(); //初始化IIC设备
		LED_GPIO_Config(); //初始化GPIO
		LED_1(OFF); //关闭led1
		LED_2(OFF); //关闭led1
		printf("eeprom 软件模拟 i2c 测试例程 \r\n"); //输出串口数据
		//判断读写数据是否一致
	 if (ee_Test() == 1) {
		LED_1(OFF);
	 } else {
		LED_1(ON);
	 }
    while(1)
		{
		}
}
