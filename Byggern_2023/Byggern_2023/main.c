/*
 * Byggern_2023.c
 *
 * Created: 31-Aug-23 2:03:29 PM
 * Author : peter
 */ 

#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include "uart_lib.h"




int main(void)
{
    /* Replace with your application code */
	uart_init();
	char s[] = "Hello World";
	DDRB = 0x1;
    while (1) 
    {
		uart_send_byte(s[0]);
		_delay_ms(100);
		
		//PORTB = 0x01;
		//_delay_ms(20);
		//PORTB = 0x00;
		//_delay_ms(20);	
    }
}

void uart_send_byte(uint8_t data){
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}
	
