#ifndef __DMA_H
#define __DMA_H

#include "stm32f10x.h"
#include "NRF24L01.h"
#define USART1_DR_Base  (&(USART1->DR))

void DMA_Config(void);
#endif
