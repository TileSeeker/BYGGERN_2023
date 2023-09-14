/*
 * Byggern_2023.c
 *
 * Created: 31-Aug-23 2:03:29 PM
 * Author : peter
 */ 

#include <avr/io.h>

#define F_CPU 4915200UL
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "uart_lib.h"



int main(void)
{
	uart_init();
	char s[] = "Hello World";
	//sei();
    while (1){
		uart_send_byte(s[0]);
		//printf("Hello!");
		_delay_ms(100);
		
		//PORTB = 0x01;
		//_delay_ms(20);
		//PORTB = 0x00;
		//_delay_ms(20);	
    }
}
	