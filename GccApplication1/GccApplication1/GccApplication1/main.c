#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_lib.h"
#include "xmem.h"
#include "adc_lib.h"
#include "OLED_Lib.h"

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
	adc_offset_callibrate();
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
		//volatile char *adc = (char *) 0x1400; //ADC start address
		
		//adc[0] = 0x04;
		//adc[0] = 0x00; //measure all channels
		//_delay_ms(1);
		//uint8_t x_pos = adc[0x00]; //Read Ch 0
		//uint8_t y_pos = adc[0x01]; //Read Ch 1
		
		//_delay_ms(1);
		//adc[0] = 0x80; 
		//_delay_ms(200);
		
		
		//printf("ADC: x:%02i\t y:%02i \n\n", x_pos, y_pos);
		//printf("ADC: x:%02X\t y:%02X \n\n", read_channel(channel_0), read_channel(channel_1));
		printf("ADC: x:%i\t y:%i \n\n", read_angle(channel_0), read_angle(channel_1));
		printf("ADC: x:%s\t y:%s \n\n", read_dirrection(channel_0), read_dirrection(channel_1));
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