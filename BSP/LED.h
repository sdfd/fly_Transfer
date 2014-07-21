#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED_ON() GPIO_ResetBits(GPIOE,GPIO_Pin_12)
#define LED_OFF() GPIO_SetBits(GPIOE,GPIO_Pin_12)

void LED_Config(void);

#endif
