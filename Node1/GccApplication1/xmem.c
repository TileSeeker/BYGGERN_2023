#include "xmem.h"

void XMEM_init(void) {
	MCUCR |= (1 << SRE);	//Enable SRAM
	SFIOR |= (1 << XMM2);	//Masks PC4 - PC7
}

//lab forelesning powerpoint
void XMEM_write(uint8_t data, uint16_t addr) {
	volatile char *ext_mem = (char *) BASE_ADDRESS;
	ext_mem[addr] = data;
}

//lab forelesning powerpoint
uint8_t XMEM_read(uint16_t addr) {
	volatile char *ext_mem = (char *) BASE_ADDRESS;
	uint8_t ret_val = ext_mem[addr];
	return ret_val;
}

//lab forelesning powerpoint
void SRAM_test(void) {
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}