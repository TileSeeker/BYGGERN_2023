#include <avr/io.h>

#define nSS  PB4
#define MOSI PB5
#define MISO PB6
#define SCK  PB7

void spi_init(){
	DDRB |=	((1<<MOSI) | (1<<SCK) | (1<<nSS));	//Set MOSI, CLK, and SS to OUTPUT
	DDRB &= ~(1<<MISO);							//Set MISO as INPUT
	
	PORTB |= (1<<nSS);							//Enable pull-up to set SS to active LOW
		
	SPCR |= ((1<<SPE)  |	// Enable SPI
			 (1<<MSTR) |	// Set to Master Mode
			 (1<<SPR0));	// CLK set to Fosc/16
			 
	SPSR &=	 ~(1<<SPI2X);	//Disable SPI double  speed
}

void spi_write(char data){
	char buffer;
	SPDR = data;
	
	while (!(SPSR & (1<<SPIF))); //Wait until serial transfer is complete	
	buffer = SPDR; //Atmega162 requires the SPDE reg to be accessed directly after the SPSR reg to reset the SPIF indicator
}