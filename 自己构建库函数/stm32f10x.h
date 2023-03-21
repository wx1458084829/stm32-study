#ifndef __STM32F10X_H 
#define __STM32F10X_H


typedef unsigned int unit32_t;
typedef unsigned short int unit16_t;
//结构体地址对应表里面的内存地址
typedef struct
{
	unit32_t CRL;
	unit32_t CRH;
	unit32_t IDR;
	unit32_t ODR;
	unit32_t BSRR;
	unit32_t BRR;
	unit32_t LCKR;
}GPIO_TypeDef;

typedef struct
{
	unit32_t CR;
	unit32_t CFGR;
	unit32_t CIR;
	unit32_t APB2RSTR;
	unit32_t APB1RSTR;
	unit32_t AHBENR;
	unit32_t APB2ENR;
	unit32_t APB1ENR;
	unit32_t BDCR;
	unit32_t CSR;
	unit32_t AHBRSTR1;
	unit32_t AHBRSTR2;
}RCC_TypeDef;



//外设基地址
#define PERIPH_BASE  (unit32_t )0X40000000
//APB1地址等于外设基地址
#define APB1PERIPH_BASE  PERIPH_BASE
//APB2地址等于外设基地址+0x1000
#define APB2PERIPH_BASE  (PERIPH_BASE+0x10000)
//AHB外设地址
#define AHBPERIPH_BASE (PERIPH_BASE+0x20000)

//RCC地址
#define RCC_BASE (AHBPERIPH_BASE+0X1000)

//GPIOB地址
#define GPIOB_BASE (APB2PERIPH_BASE+0X0C00)

#define RCC_APB2ENR *(unsigned int *)(RCC_BASE+0x18)


//#define GPIOB_CRL *(unsigned int *)(GPIOB_BASE+0X00)
//#define GPIOB_CRH *(unsigned int *)(GPIOB_BASE+0X04)
//#define GPIOB_ODR *(unsigned int *)(GPIOB_BASE+0X0C)
//	通过强制类型转换指向了GPIO_TypeDef这个结构体
#define GPIOB ((GPIO_TypeDef*)GPIOB_BASE)
#define RCC ((RCC_TypeDef*)RCC_BASE)	


#endif 
