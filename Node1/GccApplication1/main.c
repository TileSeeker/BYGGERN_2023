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
	XMEM_init();
	joystick_calibrate();
	init_joystick_button();
	
	//OLED setup
	oled_init();
	oled_reset();
	oled_set_brigthness(255);
	
	//CAN test 2
	can_init();
	printf("Status: %x \r\n", mcp2515_read_status());
	
	can_message_t test = {
		.id = 2,
		.length = 2,
		.data = "ab"
	};
	
	can_send_message(&test);
	_delay_ms(10);
	//Usikker om den fungere fortsatt, siden vi leste fra TX buffer og ikke fra RX når vi testa den ¯\_(?)_/¯
	can_message_t test_r = can_recieve_message();
	printf("Data %s \r\n", test_r.data);
	
		
	while(1) {	
		//Menu
		menu_print();		
		move_arrow();
		menu_choice();
	}
}

