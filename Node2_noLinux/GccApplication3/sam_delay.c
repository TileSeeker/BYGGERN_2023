#include "sam_delay.h"

void SysTick_Handler() {
}

void sysTick_init(){
	SysTick->LOAD = (84000000U / 1000000U) - 1;																//84Mhz clock and 1 us period -> 1MHz => 84 ticks per us
	SysTick->VAL = 0;																						//Current value of SysTick counter
	SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);		//use MCK clock source, counting down to zero to asserts the SysTick exception request and enable counter
}

void delay_us(uint32_t us) {
	SysTick->LOAD =(84000000U / 1000000U) * us - 1;
	SysTick->VAL = 0;
	while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0) {
		asm("NOP");
	}
}