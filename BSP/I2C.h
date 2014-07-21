#ifndef __I2C_H
#define __I2c_H

#include "stm32f10x.h"

#define I2C_Speed            400000
#define MPU_ADDRESS7    0x68*2

void I2C_MPU_ByteWrite(u8 WriteAddr,u8 pBuffer);
u8 I2C_MPU_ByteRead(u8 ReadAddr);
void I2C_MPU_BurstRead(u8 *RxData,u8 ReadAddr,u8 Num);
void I2C_MPU_Init(void);

#endif
