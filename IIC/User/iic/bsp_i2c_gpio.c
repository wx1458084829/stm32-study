#include "bsp_i2c_gpio.h"
void i2c_CfgGpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 打开 GPIO 时钟 */
	RCC_APB2PeriphClockCmd(EEPROM_RCC_I2C_PORT, ENABLE);
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN | EEPROM_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; /* 开漏输出 */
	GPIO_Init(EEPROM_GPIO_PORT_I2C, &GPIO_InitStructure);
}

static void i2c_Delay(void)
{
	uint8_t i;
	for (i = 0; i < 10; i++);
}

void i2c_Start(void)
{
	EEPROM_I2C_SDA_1();
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	EEPROM_I2C_SDA_0();
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();
}

void i2c_Stop(void)
{
	EEPROM_I2C_SDA_0();
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	EEPROM_I2C_SDA_1();
}

void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;
	for (i = 0; i < 8; i++) 
	{
	if (_ucByte & 0x80) 
	{
		EEPROM_I2C_SDA_1();
	} else {
		EEPROM_I2C_SDA_0();
	}
	 i2c_Delay();
	 EEPROM_I2C_SCL_1();
	 i2c_Delay();
	 EEPROM_I2C_SCL_0();
	 if (i == 7) {
		 EEPROM_I2C_SDA_1(); // 释放总线
		 }
		 _ucByte <<= 1; /* 左移一个 bit */
		 i2c_Delay();
		}
}

uint8_t i2c_ReadByte(void)
{
 uint8_t i;
 uint8_t value;

	 /* 读到第 1 个 bit 为数据的 bit7 */
	 value = 0;
	 for (i = 0; i < 8; i++) {
	 value <<= 1;
	 EEPROM_I2C_SCL_1();
	 i2c_Delay();
	 if (EEPROM_I2C_SDA_READ()) {
	 value++;
	 }
	 EEPROM_I2C_SCL_0();
	 i2c_Delay();
	 }
	 return value;
}
	
uint8_t i2c_WaitAck(void)
{
	uint8_t re;
	EEPROM_I2C_SDA_1(); /* CPU 释放 SDA 总线 */
	 i2c_Delay();
	 EEPROM_I2C_SCL_1(); /* CPU 驱动 SCL = 1,
	 此时器件会返回 ACK 应答 */
	 i2c_Delay();
	 if (EEPROM_I2C_SDA_READ()) { /* CPU 读取 SDA 口线状态 */
	 re = 1;
	 } else {
	 re = 0;
	 }
	 EEPROM_I2C_SCL_0();
	 i2c_Delay();
	 return re;
}


void i2c_Ack(void)
{
 EEPROM_I2C_SDA_0(); /* CPU 驱动 SDA = 0 */
 i2c_Delay();
 EEPROM_I2C_SCL_1(); /* CPU 产生 1 个时钟 */
 i2c_Delay();
 EEPROM_I2C_SCL_0();
 i2c_Delay();
 EEPROM_I2C_SDA_1(); /* CPU 释放 SDA 总线 */
}

 void i2c_NAck(void)
 {
 EEPROM_I2C_SDA_1(); /* CPU 驱动 SDA = 1 */
 i2c_Delay();
 EEPROM_I2C_SCL_1(); /* CPU 产生 1 个时钟 */
 i2c_Delay();
 EEPROM_I2C_SCL_0();
 i2c_Delay();
 }
