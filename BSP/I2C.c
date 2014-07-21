#include "I2C.h"

static void I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd  (RCC_APB2Periph_GPIOB, ENABLE ); 
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
}

static void I2C_Mode_Configu(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 


  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 =MPU_ADDRESS7; 
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  

  I2C_Cmd(I2C2, ENABLE);

 
  I2C_Init(I2C2, &I2C_InitStructure);

   
}
void I2C_MPU_Init()
{
	I2C_GPIO_Config();
	I2C_Mode_Configu();
}

void I2C_MPU_ByteWrite(u8 WriteAddr,u8 pBuffer)
{
  /*wait until I2C bus is not busy*/
  while(I2C_GetFlagStatus(I2C2,I2C_FLAG_BUSY));
    
	/* Send START condition */
  I2C_GenerateSTART(I2C2, ENABLE);
  
    /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)); 
  
   /* Send MMA address for write */
  I2C_Send7bitAddress(I2C2, MPU_ADDRESS7, I2C_Direction_Transmitter);
    
	/* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
   
    /* Send the MMA's Register address to write to */    
  I2C_SendData(I2C2, WriteAddr); 
  
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
   
    /* Send the byte to be written */
  I2C_SendData(I2C2, pBuffer);
  
   /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));  
   
   /* Send STOP condition */
  I2C_GenerateSTOP(I2C2, ENABLE);

}

u8 I2C_MPU_ByteRead(u8 ReadAddr)
{
	  	u8 RxData;
	/*wait until I2C bus is not busy*/
  while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));

	 /* Send START condition */
  I2C_GenerateSTART(I2C2, ENABLE);
 
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send MMA address for write */
  I2C_Send7bitAddress(I2C2, MPU_ADDRESS7, I2C_Direction_Transmitter);
   
    /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2C2, ENABLE);

   /* Send the MMA's Register address to write to */
  I2C_SendData(I2C2, ReadAddr);  

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(I2C2, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
  
  /* Send MMA address for read */
  I2C_Send7bitAddress(I2C2, MPU_ADDRESS7, I2C_Direction_Receiver);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  I2C_AcknowledgeConfig(I2C2, DISABLE);
	I2C_GenerateSTOP(I2C2, ENABLE);
   /* Test on wait for EV7 */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	/* Read a byte from the MMA Register */
	RxData = I2C_ReceiveData(I2C2);

	/* Disable Acknowledgement */
    
	/* Send STOP Condition */
    

	/*Retrun Data*/
	return RxData;
}

void I2C_MPU_BurstRead(u8 *RxData,u8 ReadAddr,u8 Num)
{
	/*wait until I2C bus is not busy*/
  while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));

	 /* Send START condition */
  I2C_GenerateSTART(I2C2, ENABLE);
 
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send MMA address for write */
  I2C_Send7bitAddress(I2C2, MPU_ADDRESS7, I2C_Direction_Transmitter);
   
    /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2C2, ENABLE);

   /* Send the MMA's Register address to write to */
  I2C_SendData(I2C2, ReadAddr);  

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(I2C2, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
  
  /* Send MMA address for read */
  I2C_Send7bitAddress(I2C2, MPU_ADDRESS7, I2C_Direction_Receiver);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
//	*RxData = I2C_ReceiveData(I2C2);
//	RxData++;
//	Num = Num-1;
//  for(int i=0;i<Num-1;i++)
//	{
		
//   /* Test on wait for EV7 */
//  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	/* Read a byte from the MMA Register */
//	*RxData = I2C_ReceiveData(I2C2);
//	RxData++;
		
//	if (i < (Num-1))
//		I2C_AcknowledgeConfig(I2C2, ENABLE);
///	}
	/* Disable Acknowledgement */
//	u8 len = Num;
	while(Num)
    {
        if(Num==1)
        {
            I2C_AcknowledgeConfig(I2C2, DISABLE);	        
            /* Send STOP Condition */
            I2C_GenerateSTOP(I2C2, ENABLE);
        } 
        /* Test on EV7 and clear it */
        while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
            *RxData = I2C_ReceiveData(I2C2);
            RxData++;
            Num--;
        
//				if(Num==1)
//				{
//					I2C_AcknowledgeConfig(I2C2, DISABLE);
//					I2C_GenerateSTOP(I2C2, ENABLE);
//				}
//				for(int i=0;i<5;i++);
    }
//    I2C_AcknowledgeConfig(I2C2, DISABLE);
//	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	/* Send STOP Condition */
//    I2C_GenerateSTOP(I2C2, ENABLE);

}
