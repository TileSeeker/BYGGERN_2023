#include <avr/io.h>

#define F_CPU 4915200UL //4.9152MHz
#include <util/delay.h>
#include <stdio.h>
#include "uart_lib.h"



int main(void)
{
    UART_init();
	//Enable global interrupts
	sei();
	stdout = &uart_stream;
	
	//LED
	DDRA |= (1 << PA0);	//Configure PA0 as output
	PORTA |= (1 << PA0); //PA0 -> D1 high
	PORTA &= ~(1 << PA0); //PA0 -> D1 low
	
	
	while(1) {
		//UART testing:
		//printf("Hello World \n Test");
		//char recived = UART_recive();
		//_delay_ms(10);
		//printf("%c", recived);
	}
}
	
