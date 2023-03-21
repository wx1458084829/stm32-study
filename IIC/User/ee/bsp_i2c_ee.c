#include "bsp_i2c_ee.h"

uint8_t ee_CheckDevice(uint8_t _Address)
 {
 uint8_t ucAck;

 i2c_Start(); /* 发送启动信号 */

 /* 发送设备地址 + 读写控制 bit（0 = w， 1 = r) bit7
 先传 */
 i2c_SendByte(_Address | EEPROM_I2C_WR);
 ucAck = i2c_WaitAck(); /* 检测设备的 ACK 应答 */

 i2c_Stop(); /* 发送停止信号 */

 return ucAck;
 }
 
 
 
 uint8_t ee_WaitStandby(void)
 {
		uint32_t wait_count = 0;

		while (ee_CheckDevice(EEPROM_DEV_ADDR)) {
			 //若检测超过次数，退出循环
			 if (wait_count++>0xFFFF) {
			 //等待超时
			 return 1;
			 }
		}
		 //等待完成
		 return 0;
 }
 
 
uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress,uint16_t _usSize)
 {
 uint16_t i,m;
 uint16_t usAddr;

 /*
 写串行 EEPROM 不像读操作可以连续读取很多字节，每次写操作只能在同一个 page。
 对于 24xx02， page size = 8
 简单的处理方法为：按字节写操作模式，每写 1 个字节，都发送地址
 为了提高连续写的效率: 本函数采用 page wirte 操作。
 */

 usAddr = _usAddress;
 for (i = 0; i < _usSize; i++) {
 /* 当发送第 1 个字节或是页面首地址时，需要重新发起启动信号和地址 */
 if ((i == 0) || (usAddr & (EEPROM_PAGE_SIZE - 1)) == 0) {
 /* 　第０步：发停止信号，结束上一页的通讯，准备下一次通讯　 */
 i2c_Stop();

 /* 通过检查器件应答的方式，判断内部写操作是否完成, 一般小于 10ms
 CLK 频率为 200KHz 时，查询次数为 30 次左右
 原理同 ee_WaitStandby 函数，但该函数检查完成后会产生停止信号，不适用于此处
 */
 for (m = 0; m < 1000; m++) {
 /* 第 1 步：发起 I2C 总线启动信号 */
 i2c_Start();

 /* 第 2 步：发起控制字节，高 7bit 是地址， bit0 是读写控制位， 0 表示写， 1
表示读 */
 i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_WR); /* 此处是写指
令 */

 /* 第 3 步：发送一个时钟，判断器件是否正确应答 */
 if (i2c_WaitAck() == 0) {
 break;
 }
 }
 if (m == 1000) {
 goto cmd_fail; /* EEPROM 器件写超时 */
 }

 /* 第 4 步：发送字节地址， 24C02 只有 256 字节，因此 1 个字节就够了，
 如果是 24C04 以上，那么此处需要连发多个地址 */
 i2c_SendByte((uint8_t)usAddr);

 /* 第 5 步：等待 ACK */
 if (i2c_WaitAck() != 0) {
 goto cmd_fail; /* EEPROM 器件无应答 */
 }
 }

 /* 第 6 步：开始写入数据 */
 i2c_SendByte(_pWriteBuf[i]);

 /* 第 7 步：发送 ACK */
 if (i2c_WaitAck() != 0) {
 goto cmd_fail; /* EEPROM 器件无应答 */
 }

 usAddr++; /* 地址增 1 */
 }

 /* 命令执行成功，发送 I2C 总线停止信号 */
 i2c_Stop();

 //等待最后一次 EEPROM 内部写入完成
 if (ee_WaitStandby() == 1)
 goto cmd_fail;

 return 1;

 cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响 I2C 总线上其他设备 */
 /* 发送 I2C 总线停止信号 */
 i2c_Stop();
 return 0;
}
 
/*
 ****************************************************
 * 函 数 名: ee_ReadBytes
 * 功能说明: 从串行 EEPROM 指定地址处开始读取若干数据
 * 形 参： _usAddress : 起始地址
 * _usSize : 数据长度，单位为字节
 * _pReadBuf : 存放读到的数据的缓冲区指针
 * 返 回 值: 0 表示失败， 1 表示成功
 ****************************************************
 */
 uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress,uint16_t _usSize)
 {
 uint16_t i;

 /* 采用串行 EEPROM 随即读取指令序列，连续读取若干字节 */

 /* 第 1 步：发起 I2C 总线启动信号 */
 i2c_Start();

 /* 第 2 步：发起控制字节，高 7bit 是地址， bit0 是读写控制位，
 0 表示写， 1 表示读 */
i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_WR); /* 此处是写方向 */

 /* 第 3 步：等待 ACK */
 if (i2c_WaitAck() != 0) {
 goto cmd_fail; /* EEPROM 器件无应答 */
 }

 /* 第 4 步：发送字节地址， 24C02 只有 256 字节，因此 1 个字节就够了，
 如果是 24C04 以上，那么此处需要连发多个地址 */
 i2c_SendByte((uint8_t)_usAddress);

 /* 第 5 步：等待 ACK */
 if (i2c_WaitAck() != 0) {
 goto cmd_fail; /* EEPROM 器件无应答 */
 }

 /* 第 6 步：重新启动 I2C 总线。
 前面的代码的目的向 EEPROM 传送地址，下面开始读取数据 */
 i2c_Start();

 /* 第 7 步：发起控制字节，高 7bit 是地址， bit0 是读写控制位，
 0 表示写， 1 表示读 */
 i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_RD); /* 此处是读指令 */

 /* 第 8 步：发送 ACK */
 if (i2c_WaitAck() != 0) {
 goto cmd_fail; /* EEPROM 器件无应答 */
 }

 /* 第 9 步：循环读取数据 */
 for (i = 0; i < _usSize; i++) {
 _pReadBuf[i] = i2c_ReadByte(); /* 读 1 个字节 */

 /* 每读完 1 个字节后，需要发送 Ack， 最后一个字节不需要 Ack，发 Nack */
 if (i != _usSize - 1) {
 i2c_Ack(); /* 中间字节读完后， CPU 产生 ACK 信号 (驱动 SDA = 0) */
 } else {
 i2c_NAck(); /* 最后 1 个字节读完后， CPU 产生 NACK 信号 (驱动 SDA = 1) */

 }
 }
 /* 发送 I2C 总线停止信号 */
 i2c_Stop();
 return 1; /* 执行成功 */

 cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响 I2C 总线上其他设备 */
 /* 发送 I2C 总线停止信号 */
 i2c_Stop();
 return 0;
 }

 
 
 /*
 * eeprom AT24C02 读写测试
 * 正常返回 1，异常返回 0
 */
 uint8_t ee_Test(void)
 {
 uint16_t i;
 uint8_t write_buf[EEPROM_SIZE];
 uint8_t read_buf[EEPROM_SIZE];

 /*----------------------------------------------------*/
 
 
if (ee_CheckDevice(EEPROM_DEV_ADDR) == 1) {
 /* 没有检测到 EEPROM */
 printf("没有检测到串行 EEPROM!\r\n");

 return 0;
 }
 /*----------------------------------------------------*/
 /* 填充测试缓冲区 */
 for (i = 0; i < EEPROM_SIZE; i++) {
 write_buf[i] = i;
 }
 /*----------------------------------------------------*/
 if (ee_WriteBytes(write_buf, 0, EEPROM_SIZE) == 0) {
 printf("写 eeprom 出错！ \r\n");
 return 0;
 } else {
 printf("写 eeprom 成功！ \r\n");
 }

 /*----------------------------------------------------*/
 if (ee_ReadBytes(read_buf, 0, EEPROM_SIZE) == 0) {
 printf("读 eeprom 出错！ \r\n");
 return 0;
 } else {
 printf("读 eeprom 成功，数据如下： \r\n");
 }
 /*----------------------------------------------------*/
 for (i = 0; i < EEPROM_SIZE; i++) {
 if (read_buf[i] != write_buf[i]) {
 printf("0x%02X ", read_buf[i]);
// printf("错误:EEPROM 读出与写入的数据不一致");
 return 0;
 }
 printf(" %02X", read_buf[i]);

 if ((i & 15) == 15) {
 printf("\r\n");
 }
 }
 printf("eeprom 读写测试成功\r\n");
 return 1;
 }
 
 
	
	