#include "bsp_rcc_clk_config.h"
void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	//初始化RCC
	RCC_DeInit();
	
	//使能HSE
	RCC_HSEConfig(RCC_HSE_ON);
	
	//等待HSE使能成功
	do
	{
			HSEStatus = RCC_WaitForHSEStartUp();
			StartUpCounter++;  
	}while((HSEStatus == ERROR ) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
	
	
	if(HSEStatus == SUCCESS){
		//使能预取址
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//设置两个等待周期
		FLASH_SetLatency(FLASH_Latency_2);
		//设置AHB分频因子
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		//设置APB1分频因子
		RCC_PCLK1Config(RCC_HCLK_Div2);
		//设置APB2分频因子
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//配置锁相环
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_x);
		//使能锁相环
		RCC_PLLCmd(ENABLE);
		//等待锁相环稳定
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//设置系统时钟为锁相环
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//等待配置为PLL
		while( RCC_GetSYSCLKSource() != 0x08);
	}else{
		//启动失败
	}
}

void MCO_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		//使能时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		//配置初始化结构体
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
}
