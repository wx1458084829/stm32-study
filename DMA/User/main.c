#include "stm32f10x.h"
#include "bsp_dma_m2m.h"
#include "bsp_led.h"

//extern uint32_t aDST_Buffer[BUFFER_SIZE];



int main(void)
{
		uint8_t status = 0;
		LED_GPIO_Config();
		M2M_DMA_Config();
	
		extern uint32_t aDST_Buffer[BUFFER_SIZE];
		status = Buffercmp(aSRC_Const_Buffer,aDST_Buffer,BUFFER_SIZE);
		
		while(DMA_GetFlagStatus(DMA_M2M_FLAG_TC) == RESET);
	
		LED_ON(LED1);
	
		if(status != 0){
			LED_OFF(LED1);
			LED_ON(LED2);

		}
		while(1){
		
		}
}
