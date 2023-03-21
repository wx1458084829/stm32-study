#include "stm32f10x_gpio.h"

void GPIO_SetBits(GPIO_TypeDef *GPIOx, unit16_t GPIO_Pin)
{
    // 选择Pin
    //     BSy: 设置端口x的位y (y = 0…15) (Port x Set bit y)
    // 这些位只能写入并只能以字(16位)的形式操作。
    // 0：对对应的ODRy位不产生影响
    // 1：设置对应的ODRy位为1
    GPIOx->BSRR |= GPIO_Pin;
}

void GPIO_REsetBits(GPIO_TypeDef *GPIOx, unit16_t GPIO_Pin)
{
    // BRy: 清除端口x的位y (y = 0…15) (Port x Reset bit y)
    // 这些位只能写入并只能以字(16位)的形式操作。
    // 0：对对应的ODRy位不产生影响
    // 1：清除对应的ODRy位为0
    GPIOx->BRR |= GPIO_Pin;
}

/**
 * 函数功能：初始化引脚模式
 * 参数说明： GPIOx，该参数为 GPIO_TypeDef 类型的指针，指向 GPIO 端口的地址
 * GPIO_InitTypeDef:GPIO_InitTypeDef 结构体指针，指向初始化变量
 */
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
    unit32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
    unit32_t tmpreg = 0x00, pinmask = 0x00;

    /*---------------- GPIO 模式配置 -------------------*/
    // 把输入参数 GPIO_Mode 的低四位暂存在 currentmode
    currentmode = ((unit32_t)GPIO_InitStruct->GPIO_Mode) &
                  ((unit32_t)0x0F);

    // bit4 是 1 表示输出， bit4 是 0 则是输入
    // 判断 bit4 是 1 还是 0，即首选判断是输入还是输出模式
    if ((((unit32_t)GPIO_InitStruct->GPIO_Mode) &
         ((unit32_t)0x10)) != 0x00)
    {
        // 输出模式则要设置输出速度
        currentmode |= (unit32_t)GPIO_InitStruct->GPIO_Speed;
    }
    /*-----GPIO CRL 寄存器配置 CRL 寄存器控制着低 8 位 IO- ----*/
    // 配置端口低 8 位，即 Pin0~Pin7
    if (((unit32_t)GPIO_InitStruct->GPIO_Pin &
         ((unit32_t)0x00FF)) != 0x00)
    {
        // 先备份 CRL 寄存器的值
        tmpreg = GPIOx->CRL;
        //循环，从 Pin0 开始配对，找出具体的 Pin 
        for (pinpos = 0x00; pinpos < 0x08; pinpos++){
            // pos 的值为 1 左移 pinpos 位
            pos = ((unit32_t)0x01) << pinpos;
            // 令 pos 与输入参数 GPIO_PIN 作位与运算
            currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
            //若 currentpin=pos, 则找到使用的引脚
            if (currentpin == pos)
            {
                // pinpos 的值左移两位 (乘以 4), 因为寄存器中 4 个位配置一个引脚
                pos = pinpos << 2;
                //把控制这个引脚的 4 个寄存器位清零，其它寄存器位不变
                pinmask = ((unit32_t)0x0F) << pos;
                tmpreg &= ~pinmask;
                // 向寄存器写入将要配置的引脚的模式
                tmpreg |= (currentmode << pos);
                // 判断是否为下拉输入模式
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    // 下拉输入模式, 引脚默认置 0, 对 BRR 寄存器写 1 对引脚置 0
                    GPIOx->BRR = (((unit32_t)0x01) << pinpos);
                }
                else
                {
                    // 判断是否为上拉输入模式
                    if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)

                    {
                        // 上拉输入模式, 引脚默认值为 1, 对 BSRR 寄存器写 1 对引脚置 1
                        GPIOx->BSRR = (((unit32_t)0x01) << pinpos);
                    }
                }
            }
        }
        // 把前面处理后的暂存值写入到 CRL 寄存器之中
        GPIOx->CRL = tmpreg;
    }
    /*--------GPIO CRH 寄存器配置 CRH 寄存器控制着高 8 位 IO- -----*/
    // 配置端口高 8 位，即 Pin8~Pin15
    if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
    {
        // // 先备份 CRH 寄存器的值
        tmpreg = GPIOx->CRH;

        // 循环，从 Pin8 开始配对，找出具体的 Pin
        for (pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            pos = (((unit32_t)0x01) << (pinpos + 0x08));

            // pos 与输入参数 GPIO_PIN 作位与运算
            currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);

            //若 currentpin=pos, 则找到使用的引脚
            if (currentpin == pos)
            {
                // pinpos 的值左移两位 (乘以 4), 因为寄存器中 4 个位配置一个引脚
                pos = pinpos << 2;

                //把控制这个引脚的 4 个寄存器位清零，其它寄存器位不变
                pinmask = ((unit32_t)0x0F) << pos;
                tmpreg &= ~pinmask;

                // 向寄存器写入将要配置的引脚的模式
                tmpreg |= (currentmode << pos);

                // 判断是否为下拉输入模式
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    // 下拉输入模式, 引脚默认置 0, 对 BRR 寄存器写 1 可对引脚置 0
                    GPIOx->BRR = (((unit32_t)0x01) << (pinpos + 0x08));
                }
                // 判断是否为上拉输入模式
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                {
                    // 上拉输入模式, 引脚默认值为 1, 对 BSRR 寄存器写 1 可对引脚置

                    GPIOx->BSRR = (((unit32_t)0x01) << (pinpos + 0x08));
                }
            }
        }
        // 把前面处理后的暂存值写入到 CRH 寄存器之中
        GPIOx->CRH = tmpreg;
    }
}
