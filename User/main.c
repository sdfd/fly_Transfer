#include "main.h"

void Sys_Init()
{
	NVIC_Config();
	Usart1_Config();
	DMA_Config();
	SPI1_Init();
	Nrf24l01_Init(3,40);
	LED_Config();
	LED_OFF();
//	I2C_MPU_Init();
//	MPU6050_Init();
}

int main()
{
	u8 Rx_Sta,abc;
	Sys_Init();
		
	if(Nrf24l01_Check() == SUCCESS)
		abc = 1;
	while(abc)
	{
//		MPU6050_Read();
		Rx_Sta = NRF_Rxpacket(NRF24L01_RXDATA);
/*		if (TX_Data_OK)
		{
			NRF_TxPacket_AP(Receive_Data, 23);
			TX_Data_OK = 0;
			if(test == 0)
			{
				LED_ON();
				test++;
			}
			else
			{
				LED_OFF();
				test = 0;
			}
		}*/
		if(Rx_Sta)
		{
			LED_ON();
//			printf("%s",NRF24L01_RXDATA);
		}
		else
			LED_OFF();
	}
}
