#ifndef SAM_DELAY_H
#define SAM_DELAY_H

#include <stdlib.h>
#include <inttypes.h>
#include "sam.h"

void SysTick_Handler(void);
void sysTick_init(void);
void delay_us(uint32_t us);

#endif