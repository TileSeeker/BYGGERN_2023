#pragma once

void XMEM_init();
void XMEM_write(uint8_t data, uint16_t addr);
uint8_t XMEM_read(uint16_t addr);
void SRAM_test(void);
