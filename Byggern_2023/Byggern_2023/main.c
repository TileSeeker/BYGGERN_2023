#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_lib.h"
#include "xmem.h"
#include "adc_lib.h"
#include "joystick_lib.h"

#define F_CPU 4915200UL //4.9152MHz
#include <util/delay.h>
#define BAUD 9600
#define BAUD_PRESCALE ((F_CPU / (BAUD * 16UL)) - 1)

int main(void)
{
	sei();  //Enable global interrupts	
	UART_init();
	XMEM_init();
	joystick_calibrate();
				
	while(1) {
		//ADC test
		printf("ADC x:%d\t y:%d \n\n", joystick_position_x(),  joystick_position_y());
		//printf("ADC y:%02X \n\n", joystick_position_y());
		_delay_ms(500);
	}
}

