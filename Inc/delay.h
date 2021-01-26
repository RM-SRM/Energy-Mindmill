#ifndef _DELAY_H
#define _DELAY_H

#include "stm32f4xx_hal.h"

void delay_init(uint8_t SYSCLK);
void delay_us(uint32_t nus);
void delay_ms(int32_t nms);

#endif
