#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_lib.h"
#include "xmem.h"

#define F_CPU 4915200UL //4.9152MHz
#include <util/delay.h>
#define BAUD 9600
#define BAUD_PRESCALE ((F_CPU / (BAUD * 16UL)) - 1)

int main(void)
{
    //Enable global interrupts	
	sei();
	UART_init();
	XMEM_init();
	//SRAM_test();
			
	//LED test
	//DDRE = 0b10;  //Set ALE as output		//or use 0b10
	//PORTE =  0b10; //Set ALE as high		//or use 0b10

	//DDRA = (1 << DDA0) | (1 << DDA1) | (1 << DDA2);	//Configure PA0 as output
	//PORTA = 0b0000000; //PA0 -> D1 
	//_delay_ms(2000);
	
	//PORTE = 0b00; //Set ALE low (saves value in latch)
	//_delay_ms(2000);
	
	//PORTA = 0b1111111;
	//_delay_ms(2000);
	
	//PORTE = 0b10;  //ALE is high and LEDs should update
		
	while(1) {
		//ADC test
		volatile char *adc = (char *) 0x1400; //ADC start address
		adc[0] = 0x04; //Output of channel 1
		uint8_t value = adc[0]; //8 bit value
		printf("ADC: %02X\n\n", value);
		_delay_ms(200);
		
		//NAND test
		//XMEM_write(1, 0x401);
		//_delay_ms(10);
		//XMEM_write(1, 0x800);
		
		//UART:
		//printf("Hello World\n Test");
		//UART_tr('B');
		//char recived = UART_recive();
		//_delay_ms(10);
		//printf("%c", recived);
	}
}

