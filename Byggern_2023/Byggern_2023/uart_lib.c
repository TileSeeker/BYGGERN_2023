/*
 * uart_lib.c
 *
 * Created: 31-Aug-23 2:22:41 PM
 *  Author: peter
 */ 
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "uart_lib.h"
#define F_CPU 16000000UL
#define BAUD_RATE 9800
#define MYUBBR (F_CPU/16/BAUD_RATE-1)


void uart_init(void){
	//Configure baud rate
	UBRR0H = (unsigned char)(MYUBBR >> 8);
	UBRR0L = (unsigned char)(MYUBBR);
	
	//Configure Control andStatus Register A
	UCSR0A = 0x00|	(0<<RXC0)	|	//USART Receive Complete Indicator
					(0<<TXC0)	|	//USART Transmit Complete Indicator
					(0<<UDRE0)	|	//USART Data Register Empty Indicator.
					(0<<FE0)	|	//Frame Error Indicator. Always write to 0 when writing to UCSR0A
					(0<<DOR0)	|	//Data OverRun Indicator. Always write to 0 when writing to UCSR0A
					(0<<UPE0)	|	//Parity Error Indicator. Always write to 0 when writing to UCSR0A
					(0<<U2X0)	|	//Double the USART Transmission Speed Disabled
					(0<<MPCM0);		//Multi-processor Communication Mode Disabled
	
	//Configure Control andStatus Register B
	UCSR0B = 0x00|	(1<<RXCIE0)	|	//RX Complete Enable
					(1<<TXCIE0)	|	//TX Complete Enable
					(1<<UDRIE0)	|	//DATA-REGISTER-EMPTY interrupt Enable
					(1<<RXEN0)	|	//RX enabled
					(1<<TXEN0)	|	//TX enabled
					(0<<UCSZ02)	|	//8-bit Frame size
					(0<<RXB80)	|	//RX data bit. Not used during init
					(0<<TXB80);		//TX data bit. Not used during init
					
	//Configure Control andStatus Register B
	UCSR0C = 0x00|	(1<<URSEL0)	|	//URSEL0 set to 1 to write to UCSR0C
					(0<<UMSEL0)	|	//Asynchronous Operation
					(0<<UPM00)	|	//Parity Mode Disabled
					(0<<USBS0)	|	//1-bit stop bit
					(3<<UCSZ00)	|	//8-bit Frame size
					(0<<UCPOL0);	//UCPOL Not available in UART mode
					
}