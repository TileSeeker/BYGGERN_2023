#ifndef SPI_LIB_H
#define SPI_LIB_H

#include <avr/io.h>

#define DD_MOSI DDB5
#define DD_SCK DDB7
#define DD_SS DDB4
#define DD_MISO DDB6
#define SS PB4

void spi_init(void);
char spi_read(void);
void spi_write(char data);

#endif