#ifndef XMEM_H
#define XMEM_H

#include <avr/io.h>
#include <stdlib.h>

#define  BASE_ADDRESS 0x1000

void XMEM_init();
void XMEM_write(uint8_t data, uint16_t addr);
uint8_t XMEM_read(uint16_t addr);
void SRAM_test(void);

#endif
