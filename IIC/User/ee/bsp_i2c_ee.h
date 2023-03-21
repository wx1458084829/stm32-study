#ifndef __BSP_I2C_EE_H
#define __BSP_I2C_EE_H

#include "stm32f10x.h"
#include "bsp_i2c_gpio.h"
#include <stdio.h>
#define EEPROM_DEV_ADDR 0xA0

 /* 24xx02 的页面大小 */
#define EEPROM_PAGE_SIZE 8

#define EEPROM_SIZE 20

uint8_t ee_CheckDevice(uint8_t _Address);

uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress,uint16_t _usSize);
uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress,uint16_t _usSize);
 
 uint8_t ee_Test(void);

#endif
