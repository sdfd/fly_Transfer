#include "MPU6050.h"

Acc_XYZ Acc;
Gyr_XYZ Gyr;

void MPU6050_Init()
{

	I2C_MPU_ByteWrite(MPU6050_RA_PWR_MGMT_1,0x01);
	I2C_MPU_ByteWrite(MPU6050_RA_GYRO_CONFIG,0x18);
	I2C_MPU_ByteWrite(MPU6050_RA_ACCEL_CONFIG,0x08);
	I2C_MPU_ByteWrite(MPU6050_RA_CONFIG,0x03);

}

void MPU6050_Read()
{
	u8 Buffer[14];
	for(int i=0;i<14;i++)
	{
		Buffer[i]=I2C_MPU_ByteRead(0x3B+i);
		for(int j;j<100;j++);
	}
//	I2C_MPU_BurstRead(Buffer,MPU6050_RA_ACCEL_XOUT_H,14);
	Acc.X = (u16)(Buffer[0] << 8) + Buffer[1];
	Acc.Y = (u16)(Buffer[2] << 8) + Buffer[3];
	Acc.Z = (u16)(Buffer[4] << 8) + Buffer[5];
	Gyr.X = (u16)(Buffer[8] << 8) + Buffer[9];
	Gyr.Y = (u16)(Buffer[10] << 8) + Buffer[11];
	Gyr.Z = (u16)(Buffer[12] << 8) + Buffer[13];
}
