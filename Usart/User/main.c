#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include <stdio.h>
int main(void)
{
	  USART_Config();
		LED_GPIO_Config();
		uint8_t ch;
	

		//Usart_SendByte(DEBUG_USARTx,'A');
	
		//Usart_SendHalfWord(DEBUG_USARTx,0xff56);
	
//		uint8_t a[] = {1,2,3,4,5,6};
//		Usart_SendArrays(DEBUG_USARTx,a,3);
		
//		Usart_SendStr(DEBUG_USARTx,"换源");
	
//		printf("测试%d%c\n",2,'x');
//		putchar('c');
	USART_SendData(DEBUG_USARTx,'a');
	
//		char buf[] = {'a'};
		
	
	
//err
//			uint8_t buf;
//			scanf("%d",&buf);
//			printf("%d",buf);
    while(1)
		{
			ch = getchar();
			printf("%c",ch);
			
		}
}
