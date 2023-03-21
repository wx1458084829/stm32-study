#include "stm32f10x.h"
//pb5
int main(void)
{
//	使能APB2外设时钟
	* (unsigned int *) 0x40021018 |= (1<<3);
//	设置输出模式和速率
	* (unsigned int *) 0x40010c00 |= ~((0x0001)<<(4*5));
//	设置IO口电平
	* (unsigned int *) 0x40010c0c &= ~(1<<5);
	return 0;
}
void SystemInit(void)
{
	//函数体为空，为了不报错
}
