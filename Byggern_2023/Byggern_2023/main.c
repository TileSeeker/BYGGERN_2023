
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_lib.h"
#include "xmem.h"
#include "adc_lib.h"
#include "joystick_lib.h"
#include "slider_lib.h"
#include "oled_lib.h"

#define F_CPU 4915200UL //4.9152MHz
#include <util/delay.h>
#define BAUD 9600
#define BAUD_PRESCALE ((F_CPU / (BAUD * 16UL)) - 1)

// joystick-x -> channel 0
// joystick-y -> channel 1

// left slider: PWM PB4 -> AIN2 / channel 2
// right slider: PWM PD1 -> AIN3 / channel 3

int main(void)
{

	sei();  //Enable global interrupts	
	UART_init();
	XMEM_init();
	joystick_calibrate();
				
	while(1) {
		//ADC & joystick test
		//printf("ADC: x: %d\t y: %d\t dir-x: %d\t dir-y: %d \n\n", joystick_position_read().x_pos, joystick_position_read().y_pos, joystick_direction_read().x_dir, joystick_direction_read().y_dir);

		
		//Slider test
		printf("Slider: %d \n\n", read_slider_position(channel_2));
		
		_delay_ms(100);
	}
}

