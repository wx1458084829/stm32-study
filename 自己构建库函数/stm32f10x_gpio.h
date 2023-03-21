#ifndef __STM32F10X_GPIO_H
#define __STM32F10X_GPIO_H

#include "stm32f10x.h"

typedef enum
{
    GPIO_Speed_10MHZ = 1,
    GPIO_Speed_20MHZ = 2,
    GPIO_Speed_50MHZ = 3
} GPIOSpeed_TypeDef;


typedef enum
{
    GPIO_Mode_AIN = 0X00, //模拟输入

    GPIO_Mode_IN_FLOATING = 0X04, //浮空输入

    GPIO_Mode_IPD = 0X28, //下拉输入
    GPIO_Mode_IPU = 0X48, //上拉输入

    GPIO_Mode_OUT_OD = 0X14, //开漏输出
    GPIO_Mode_OUT_PP = 0X10, //推挽输出

    GPIO_Mode_AF_OD = 0X1C, //复用开漏输出 
    GPIO_Mode_AP_PP = 0X18, //复用推挽输出

}GPIOMode_TypeDef;

typedef struct
{
    unit16_t GPIO_Pin; //要配置的GPIO脚

    unit16_t GPIO_Speed; //选择GPIO速率

    unit16_t GPIO_Mode; //选择GPIO工作模式
}GPIO_InitTypeDef;


#define GPIO_Pin_0 ((unit16_t)0x0001) /*选择Pin0*/
#define GPIO_Pin_1 ((unit16_t)0x0002) /*选择Pin1*/
#define GPIO_Pin_2 ((unit16_t)0x0004) /*选择Pin2*/
#define GPIO_Pin_3 ((unit16_t)0x0008) /*选择Pin3*/
#define GPIO_Pin_4 ((unit16_t)0x0010) /*选择Pin4*/
#define GPIO_Pin_5 ((unit16_t)0x0020) /*选择Pin5*/
#define GPIO_Pin_6 ((unit16_t)0x0040) /*选择Pin6*/
#define GPIO_Pin_7 ((unit16_t)0x0080) /*选择Pin7*/

#define GPIO_Pin_8 ((unit16_t)0x0100) /*选择Pin8*/
#define GPIO_Pin_9 ((unit16_t)0x0200) /*选择Pin9*/
#define GPIO_Pin_10 ((unit16_t)0x0400) /*选择Pin10*/
#define GPIO_Pin_11 ((unit16_t)0x0800) /*选择Pin11*/
#define GPIO_Pin_12 ((unit16_t)0x1000) /*选择Pin12*/
#define GPIO_Pin_13 ((unit16_t)0x2000) /*选择Pin13*/
#define GPIO_Pin_14 ((unit16_t)0x4000) /*选择Pin14*/
#define GPIO_Pin_15 ((unit16_t)0x8000) /*选择Pin15*/
#define GPIO_Pin_All ((unit16_t)0xFFFF) /*选择所有Pin*/

void GPIO_SetBits(GPIO_TypeDef *GPIOx,unit16_t GPIO_Pin);
void GPIO_REsetBits(GPIO_TypeDef *GPIOx,unit16_t GPIO_Pin);

/**
 * 函数功能：初始化引脚模式
 * 参数说明： GPIOx，该参数为 GPIO_TypeDef 类型的指针，指向 GPIO 端口的地址
 * GPIO_InitTypeDef:GPIO_InitTypeDef 结构体指针，指向初始化变量
 */
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
#endif /*__STM32F10X_GPIO_H*/


