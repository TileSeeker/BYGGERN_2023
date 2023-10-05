#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "MCP2515_lib.h"
#include "SPI_lib.h"

typedef struct Message{
	uint8_t data[7];
	uint8_t data_length = 0;
	uint8_t priority = 0;
	uint16_t ID = 0;
}message_t;


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
	_delay_ms(100);
	
	// Self - test
	bool mcp_in_config_mode;
	
	for (uint8_t i = 0; i<10; i++){
		_delay_ms(10);
		value = mcp2515_read(MCP_CANSTAT);
		mcp_in_config_mode = ((value & MODE_MASK) == MODE_CONFIG);
		if(mcp_in_config_mode){
			break;
		}
	}
	if (!mcp_in_config_mode) {
		printf (" MCP2515 is NOT in configuration mode after reset !\r\n");
		return 1;
	}else{
		printf("MCP2515 in config mode\r\n");
	}
	
	mcp2515_set_mode(MODE_LOOPBACK);
	return 0;
}

void mcp2515_set_mode(uint8_t mode){
	/*mcp2515_reset();
	_delay_ms(100);
	uint8_t value = mcp2515_read(MCP_CANSTAT);
	bool mcp_in_config_mode = ((value & MODE_MASK) == MODE_CONFIG);
	if (!mcp_in_config_mode){
		printf("Mode Error\r\n");
	}else{
		printf("Set to mode: %i\r\n", mode);
		mcp2515_write(MCP_CANCTRL, mode);
	}
	*/
	uint8_t mode_r=0;
	printf("Set to mode: %x\r\n", mode);
	mcp2515_write(MCP_CANCTRL, mode);
	mode_r = mcp2515_read(MCP_CANCTRL) & (0b111<<5);
	printf("Mode: %x\r\n", mode_r);
}


//lab forelesning powerpoint
uint8_t mcp2515_read(uint8_t address) {
	uint8_t result ;
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	spi_write ( MCP_READ ); // Send read instruction
	spi_write ( address ); // Send address
	result = spi_read () ; // Read result
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller
	return result;
}

void mcp2515_write(uint8_t address, uint8_t data) {
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	spi_write ( MCP_WRITE ); // Send read instruction
	spi_write ( address ); // Send address
	spi_write( data);
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller
}

void mcp2515_load_tx_buffer(uint8_t data, uint8_t buffer){
	uint8_t instruction = 0;
	switch (buffer) {
		case(0):
			instruction = MCP_LOAD_TX0 | 1;
			break;
		case(1):
			instruction = MCP_LOAD_TX1 | 1;
			break;
		case(2):
			instruction = MCP_LOAD_TX2 | 1;
			break;
	}
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	spi_write ( instruction ); // Send read instruction
	spi_write( data);
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller	
}

uint8_t mcp2515_read_rx_buffer(uint8_t buffer){
	uint8_t instruction = 0;
	switch (buffer) {
		case(0):
		instruction = MCP_READ_RX0+1;
		break;
		case(1):
		instruction = MCP_READ_RX1+1;
		break;
	}
	uint8_t result ;
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	spi_write ( instruction ); // Send read instruction
	result = spi_read() ; // Read result
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller
	
	mcp2515_write(0x35, 1); //Write to TX DLC
	return result;
}

void mcp2515_can_send(uint8_t buffer){
	uint8_t address = 0;
	
	switch (buffer) { //Write to TX CTRL Reg
		case(0):
			address = 0x30;
			break;
		case(1):
			address = 0x40;
			break;
		case(2):
			address = 0x50;
			break;
	}
	mcp2515_write(address, (1<<3));
	//PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	//spi_write (); // Send read instruction
	//spi_write( (1<<3)); //set TXREQ to 1
	//PORTB |= (1 << CAN_CS ); // De-select CAN - controller
}