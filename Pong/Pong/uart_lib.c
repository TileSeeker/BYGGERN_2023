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
#include <string.h>
#include <stdio.h>

#include "uart_lib.h"
#define F_CPU 4915200UL
#define BAUD_RATE 9600
#define MYUBBR (F_CPU/16/BAUD_RATE-1)

//FIFO Declarations
#define buffer_size 50
char uart_rx_buffer[buffer_size];
struct FIFO fifo_rx;

char uart_tx_buffer[buffer_size];
struct FIFO fifo_tx;

//Configure stdio output stream
//static FILE mystdout = FDEV_SETUP_STREAM(uart_send_byte(), NULL, _FDEV_SETUP_WRITE);
static FILE mystdout = FDEV_SETUP_STREAM(uart_send_byte_printf, NULL, _FDEV_SETUP_WRITE);

/*
struct FIFO{
	char *buffer;
	uint16_t size;
	uint16_t head;
	uint16_t tail;
};
*/


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
	UCSR0B = 0x00|	(1<<RXCIE0)	|	//RX Complete Interrupt Enable
					(1<<TXCIE0)	|	//TX Complete Interrupt Enable
					(1<<UDRIE0)	|	//DATA-REGISTER-EMPTY Interrupt Enable
					(1<<RXEN0)	|	//RX enabled
					(1<<TXEN0)	|	//TX enabled
					(0<<UCSZ02)	|	//8-bit Frame size
					(0<<RXB80)	|	//RX data bit. Not used during init
					(0<<TXB80);		//TX data bit. Not used during init
					
	//Configure Control andStatus Register B
	UCSR0C = 0x00|	(1<<URSEL0)	|	//URSEL0 set to 1 to write to UCSR0C
					(0<<UMSEL0)	|	//Asynchronous Operation
					(0<<UPM00)	|	//Parity Mode Disabled
					(1<<USBS0)	|	//2-bit stop bit
					(3<<UCSZ00)	|	//8-bit Frame size
					(0<<UCPOL0);	//UCPOL Not available in UART mode
					
	//struct FIFO fifo_rx;
	init_fifo(&fifo_rx, uart_rx_buffer, buffer_size);
	
	//struct FIFO fifo_tx;
	init_fifo(&fifo_tx, uart_tx_buffer, buffer_size);
}

void uart_send_byte(char data){
	if (UCSR0A & (1<<UDRE0)){ //If Transmit Register is empty-> Load data to TXR
		UDR0 = data;
	}
	else{ //IF TX Register is not empty -> store the data in fifo.
		fifo_push(&fifo_tx, data);
	}
}

int uart_send_byte_printf(char var, FILE *stream){
    if (var == '\n') uart_send_byte('\r');
    uart_send_byte(var);
    return 0;
}


void uart_send_string(char* str){
	int length = strlen(str);
	for (int i=0; i<length;i++){
		uart_send_byte(str[i]);
	}
}


char uart_read_byte(void){
	return fifo_pop(&fifo_rx);
}

ISR (USART0_RXC_vect){
	char data = UDR0;
	fifo_push(&fifo_rx, data);
}

ISR (USART0_TXC_vect){
	if (!(fifo_empty(&fifo_tx))){
		UDR0 = fifo_pop(&fifo_tx);
	}
}

	
void init_fifo(struct FIFO* fifo_object, char* array, uint16_t size){
	fifo_object->buffer = array;
	fifo_object->size = size;
	fifo_object->head = 0;
	fifo_object->tail = 0;
	
}

bool fifo_full(struct FIFO* fifo_object){
	bool buffer_is_full = false;
	if (fifo_object->head == fifo_object->size){
		buffer_is_full = true;
	}
	return buffer_is_full;
}

bool fifo_empty(struct FIFO* fifo_object){
	bool buffer_is_empty = false;
	if (fifo_object->head == 0){
		buffer_is_empty = true;
	}
	return buffer_is_empty;
}

void fifo_push(struct FIFO* fifo_object, char data){
	if (!(fifo_full(fifo_object))){
		fifo_object->buffer[fifo_object->head] = data;
		fifo_object->head++;
	}
}

char fifo_pop(struct FIFO* fifo_object){
	char data = 0;
	if (!(fifo_empty(fifo_object))){
		data = fifo_object->buffer[fifo_object->tail];
		fifo_object->tail++;

		if (fifo_object->tail == fifo_object->head){
			fifo_object->tail = 0;
			fifo_object->head = 0;
		}
	}
	return data;
}

