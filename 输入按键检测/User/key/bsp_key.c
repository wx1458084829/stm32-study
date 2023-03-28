#include "bsp_key.h"

void KEY_GPIO_Config(void){
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(KEY1_CLK,ENABLE);

    GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    // 输入speed没有意义
    // GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(KEY1_PORT,&GPIO_InitStruct);
}

//读取电平
void Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
    if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0){
        
    }
}
