#ifndef __BSP_DMA_M2M_H
#define __BSP_DMA_M2M_H

#include "stm32f10x.h"


// DMA RCC时钟
#define DMA_M2M_CLK RCC_AHBPeriph_DMA1


// 要发送的数据大小
#define BUFFER_SIZE 32

#define DMA_M2M_CHANEL DMA1_Channel6

#define DMA_M2M_FLAG_TC DMA1_FLAG_TC6


 

 
extern uint32_t aDST_Buffer[BUFFER_SIZE];
 
 
extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
void M2M_DMA_Config(void);
uint8_t Buffercmp(const uint32_t* pBuffer,uint32_t* pBuffer1, uint16_t BufferLength);

#endif  /** __BSP_DMA_M2M_H */
