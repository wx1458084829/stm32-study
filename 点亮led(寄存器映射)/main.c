#include "stm32f10x.h"

int main(void)
{
	RCC_APB2ENR |= ((1)<<3);
	GPIOB_CRL |= (1)<<(4*5);
//	IO清零
	GPIOB_ODR &= ~((0x0f)<<(5*4));
	
//	开启
	GPIOB_ODR &= ~(1<<5);
	//	关闭
//	GPIOB_ODR |= (1<<5);
	return 0;
}
void SystemInit(void)
{
	//函数体为空，为了不报错
}
