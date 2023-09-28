#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_lib.h"
#include "xmem.h"
#include "adc_lib.h"
#include "joystick_lib.h"
#include "slider_lib.h"
#include "oled_lib.h"
#include "menu_system.h"

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
	
	//OLED setup
	oled_init();
	oled_reset();
	oled_set_brigthness(255);
	
	//OLED print test
	//oled_arrow_at_pos(1, 0);
	//oled_print("Hello", 1, font_size);
	//oled_print("Hello 2", 2, 1);
	 DDRB	&= ~(1 << DDB1);
	 PORTB	|= (1 << PB1); 
	 uint8_t trigger;
	
	
		
	while(1) {	
		menu_print();		
		move_arrow();
		menu_choice();
		trigger = (PINB >>PB1) & (1);
		//printf("%i\t", trigger);
	}
}

