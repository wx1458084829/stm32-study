#ifndef __BSP_I2C_GPIO_H
#define __BSP_I2C_GPIO_H

#include "stm32f10x.h"

#define EEPROM_GPIO_PORT_I2C GPIOA /* GPIO 端口 */
#define EEPROM_RCC_I2C_PORT RCC_APB2Periph_GPIOA /* GPIO 端口时钟 */
#define EEPROM_I2C_SCL_PIN GPIO_Pin_2 /* 连接到 SCL 时钟线的 GPIO */
#define EEPROM_I2C_SDA_PIN GPIO_Pin_3 /* 连接到 SDA 数据线的 GPIO */



#define EEPROM_I2C_SCL_1() GPIO_SetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SCL_PIN)
#define EEPROM_I2C_SCL_0() GPIO_ResetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SCL_PIN)
#define EEPROM_I2C_SDA_1() GPIO_SetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SDA_PIN)
#define EEPROM_I2C_SDA_0() GPIO_ResetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SDA_PIN)

#define EEPROM_I2C_SDA_READ() GPIO_ReadInputDataBit(EEPROM_GPIO_PORT_I2C,EEPROM_I2C_SDA_PIN)

#define EEPROM_I2C_WR 0 /* 写控制 bit */
#define EEPROM_I2C_RD 1 /* 读控制 bit */

void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
void i2c_CfgGpio(void);



#endif
