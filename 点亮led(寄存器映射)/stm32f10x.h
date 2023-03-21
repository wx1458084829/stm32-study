
typedef unsigned int unit32_t;

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


#define GPIOB_CRL *(unsigned int *)(GPIOB_BASE+0X00)
#define GPIOB_CRH *(unsigned int *)(GPIOB_BASE+0X04)
#define GPIOB_ODR *(unsigned int *)(GPIOB_BASE+0X0C)
