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
#include "MCP2515_lib.h"

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
	//printf("Uart Init\n");
	XMEM_init();
	joystick_calibrate();
	init_joystick_button();
	uint8_t trigger;
	
	//OLED setup
	oled_init();
	oled_reset();
	oled_set_brigthness(255);
	
	mcp2515_init();
	
	uint8_t can_data;
	while(1) {	
		//Menu
		mcp2515_load_tx_buffer('H', 0);
		mcp2515_can_send(0);
		_delay_ms(1000);
		can_data = mcp2515_read_rx_buffer(0);
		printf("%c\r\n", can_data);
		
		
		/*
		menu_print();		
		move_arrow();
		menu_choice();
		
		//Joystick button test
		trigger = (PINB >> PB1) & (1); //Read Joystick Value
		if (!trigger) {
			printf("Button pres");
		}
		*/
	}
}

