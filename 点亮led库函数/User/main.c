#include "stm32f10x.h"
#include "bsp_led.h"
int main(void)
{
	LED_GPIO_Config();
    // 设置端口高电平
    // GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);

    // 设置端口为低电平
    // GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
    LED_G(ON);
    return 0;
}
