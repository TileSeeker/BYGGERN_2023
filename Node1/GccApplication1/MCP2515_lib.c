#include "MCP2515_lib.h"

void mcp2515_reset() {
	PORTB &= ~(1 < < CAN_CS ); // Select CAN - controller
	spi_write(MCP_RESET);	// Send reset instruction
	PORTB |= (1 < < CAN_CS ); // De-select CAN - controller
}

//lab forelesning powerpoint
uint8_t mcp2515_init() {
	uint8_t value ;
	spi_init () ; // Initialize SPI
	mcp2515_reset () ; // Send reset - command
	
	// Self - test
	mcp2515_read(MCP_CANSTAT , &value);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf (" MCP2515 is NOT in configuration mode after reset !\n");
		return 1;
	}
	// More initialization
	return 0;
}

//lab forelesning powerpoint
uint8_t mcp2515_read(uint8_t address) {
	uint8_t result ;
	PORTB &= ~(1 < < CAN_CS ); // Select CAN - controller
	spi_write ( MCP_READ ); // Send read instruction
	spi_write ( address ); // Send address
	result = spi_read () ; // Read result
	PORTB |= (1 < < CAN_CS ); // De-select CAN - controller
	return result;
}

void mcp2515_write(uint8_t address, uint8_t data) {
	PORTB &= ~(1 < < CAN_CS ); // Select CAN - controller
	spi_write ( MCP_WRITE ); // Send read instruction
	spi_write ( address ); // Send address
}