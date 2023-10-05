#include "SPI_lib.h"

void spi_init() {
	//set MOSI, SCK and SS as output
	DDRB |= (1 << DD_MOSI) |(1 << DD_SCK) | (1 << DD_SS); 
	//set MISO as input
	DDRB &= ~(1 << DD_MISO); 
	//enable SPI, master and set clock rate fck/16
	SPCR = |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);  
	//disable SPI double speed
	SPSR &= ~(1 << SPI2X);
}

char spi_read() {
	//write dummy data to SPDR to generate SCK for transfer
	SPDR = 0xFF;
	//SPSR: SPI status register -> SPIF: SPI interrupt flag 
	//waits until the interrupt flag is set to high, aka when transfer is completed
	while (!(SPSR & (1 << SPIF))) {}
	
	return SPDR
}

void spi_write(char data) {
	SPDR = data;
	while (!(SPSR & (1 << SPIF))) {}
}