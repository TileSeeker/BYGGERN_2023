#include "uart_lib.h"

#define F_CPU 4915200UL //4.9152MHz
#define BAUD 9600
#define BAUD_PRESCALE ((F_CPU / (BAUD * 16UL)) - 1)
volatile uint8_t transmissionComplete = 1;

static int UART_transmit(char message, FILE *stream) {
	//Wait for prev transmission to complete
	while (!transmissionComplete);
	//Set TXC flag to indicate busy
	transmissionComplete = 0;
	
	//Put data into UDR buffer, sends the data
	UDR0 = message;
	if (message == '\n') {
		UART_transmit('\r', stream);
	}
	return 0;
}

char UART_recive() {
	//Wait for unread data in UDR buffer
	while (!(UCSR0A & (1 << RXC0)));
	
	//Return received data from buffer
	return UDR0;
}

void UART_init() {
	//Set baud rate
	UBRR0H = (BAUD_PRESCALE >> 8);
	UBRR0L = BAUD_PRESCALE;
	
	//Enable receiver and transmitter + TX complete interrupt
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << TXCIE0);
	
	//Set frame format: 8-bit data, stop bit = 2_bit
	UCSR0C |= (1 << URSEL0) | (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00); //UCSZ10 -> UCSZ01
	
	fdevopen(&UART_transmit, &UART_recive);
}

//UART transmission complete interrupt handler
ISR(USART0_TXC_vect) {
	//Set flag to indicate completion
	transmissionComplete = 1;
}