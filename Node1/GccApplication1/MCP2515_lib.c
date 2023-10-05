#include "MCP2515_lib.h"
#include <stdio.h>
#define F_CPU 4915200UL //4.9152MHz
#include <util/delay.h>

void mcp2515_reset() {
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	spi_write(MCP_RESET);	// Send reset instruction
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller
}

//lab forelesning powerpoint
uint8_t mcp2515_init() {
	uint8_t value ;
	spi_init () ; // Initialize SPI
	mcp2515_reset () ; // Send reset - command
	//mcp2515_bit_modify(MCP_CANCTRL, 0x8, 0x8);
	
	_delay_ms(1);
	
	// Self - test
	value = mcp2515_read(MCP_CANSTAT);
	
	_delay_ms(1);
	
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf ("MCP2515 is NOT in configuration mode after reset !\r\n");
	}
}

//lab forelesning powerpoint
uint8_t mcp2515_read(uint8_t addres) {
	uint8_t result ;
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	spi_write ( MCP_READ ); // Send read instruction
	spi_write ( addres ); // Send address
	result = spi_read () ; // Read result
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller
	return result;
}

void mcp2515_write(uint8_t addres, uint8_t data) {
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	spi_write ( MCP_WRITE ); // Send write instruction
	spi_write ( addres ); // Send address
	spi_write(data); // Send data
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller
}

uint8_t mcp2515_read_status() {
	uint8_t status;
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	spi_write(MCP_READ_STATUS);
	status = spi_read();
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller
	return status;
}

void mcp2515_bit_modify(uint8_t addres, uint8_t mask,  uint8_t data) {
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	spi_write(MCP_BITMOD);
	spi_write(addres);
	spi_write(mask);
	spi_write(data);
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller
}

void mcp2515_mode_select(uint8_t mode) {
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, mode);
}

void mcp2515_rts(int buffer) {
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	if (buffer == 0) {
		spi_write(MCP_RTS_TX0);
	} else if (buffer == 1) {
		spi_write(MCP_RTS_TX1);
	} else if (buffer == 2) {
		spi_write(MCP_RTS_TX2);
	} else {
		spi_write(MCP_RTS_ALL);
	}	
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller
}