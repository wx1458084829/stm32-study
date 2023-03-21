#include "bsp_systick.h"

void SysTick_Delay_us(uint32_t us)
{
	uint32_t i;
	// 初始化SysTick
	SysTick_Config(72);
	for(i=0;i<us;i++)
	{
		while(!((SysTick->CTRL)& SysTick_CTRL_COUNTFLAG_Msk ));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_ms(uint32_t ms)
{
	uint32_t i;
	SysTick_Config(72000);
	for(i=0;i<ms;i++)
	{
		// 与第16位(16位为计数标志)相与，判断是否已经到达一个计数周期
		while(!((SysTick->CTRL) & SysTick_CTRL_COUNTFLAG_Msk ));
	}
	// 关掉定时器
	SysTick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

// 使用原型的函数作为参考
#if 0 
/**
 * @brief  Initialize and start the SysTick counter and its interrupt.
 *
 * @param   ticks   number of ticks between two interrupts
 * @return  1 = failed, 0 = successful
 *
 * Initialise the system tick timer and its interrupt and start the
 * system tick timer / counter in free running mode to generate 
 * periodical interrupts.
 */
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
	// 判断输入值是否大于最大值 2^24
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */
  // 设置reload寄存器的初始值
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
  //配置中断优先级为 1<<4 -1 = 15,优先级为最低  
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */
  // 配置Counter计数器的值
  SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
    // 配置SysTick的时钟为72M
    //使能中断
    // 使能SysTick
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                   SysTick_CTRL_TICKINT_Msk   | 
                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
  return (0);                                                  /* Function successful */
}
#endif
