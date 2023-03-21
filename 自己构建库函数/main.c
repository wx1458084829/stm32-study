#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;

	RCC->APB2ENR |= ((1) << 3);

	

	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIOB->CRL |= (1) << (4 * 5);
	//	IO清零
	GPIOB->ODR &= ~((0x0f) << (5 * 4));

	//	开启
	// GPIOB->ODR &= ~(1<<5);

	//	关闭
	// GPIO_SetBits(GPIOB,GPIO_Pin_5);
	//	开启
	GPIO_REsetBits(GPIOB, GPIO_Pin_5);

	return 0;
}
void SystemInit(void)
{
	//函数体为空，为了不报错
}
