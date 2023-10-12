#include "MCP2515_lib.h"
#include <stdio.h>
#define F_CPU 4915200UL //4.9152MHz
#include <util/delay.h>

void mcp2515_reset() {
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	spi_write(MCP_RESET);	// Send reset instruction
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller
	_delay_ms(10);
}

//lab forelesning powerpoint
void mcp2515_init() {
	uint8_t value ;
	spi_init () ; // Initialize SPI
	mcp2515_reset () ; // Send reset - command

	// Self - test
	value = mcp2515_read(MCP_CANSTAT);	
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf ("MCP2515 is NOT in configuration mode after reset !\r\n");
	}
	
	//CAN bus timing | something aint right ¯\_(?)_/¯
	mcp2515_write(MCP_CNF1, SJW1 | BRP);
	mcp2515_write(MCP_CNF2, BTLMODE | SAMPLE_1X | (PS1 << 3) | PROPSEG);
	mcp2515_write(MCP_CNF3, WAKFIL_DISABLE | PS2);
}

//lab forelesning powerpoint
uint8_t mcp2515_read(uint8_t addres) {
	uint8_t result ;
	PORTB &= ~(1 << CAN_CS); // Select CAN - controller
	spi_write (MCP_READ); // Send read instruction
	spi_write (addres); // Send address
	result = spi_read() ; // Read result
	PORTB |= (1 << CAN_CS); // De-select CAN - controller
	return result;
}

void mcp2515_write(uint8_t addres, uint8_t data) {
	PORTB &= ~(1 << CAN_CS); // Select CAN - controller
	spi_write (MCP_WRITE); // Send write instruction
	spi_write (addres); // Send address
	spi_write(data); // Send data
	PORTB |= (1 << CAN_CS); // De-select CAN - controller
}

uint8_t mcp2515_read_status() {
	uint8_t status;
	PORTB &= ~(1 << CAN_CS); // Select CAN - controller
	spi_write(MCP_READ_STATUS);
	status = spi_read();
	PORTB |= (1 << CAN_CS); // De-select CAN - controller
	return status;
}

void mcp2515_bit_modify(uint8_t addres, uint8_t mask,  uint8_t mode) {
	PORTB &= ~(1 << CAN_CS); // Select CAN - controller
	spi_write(MCP_BITMOD);
	spi_write(addres);
	spi_write(mask);
	spi_write(mode);
	PORTB |= (1 << CAN_CS); // De-select CAN - controller
}

void mcp2515_mode_select(uint8_t mode) {
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, mode);
	
	// Self - test
	uint8_t value ;
	value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != mode) {
		printf ("MCP2515 is NOT in right mode !\r\n");
	}
}

void mcp2515_rts(int buffer) {
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	switch (buffer) {
		case 0:
			spi_write(MCP_RTS_TX0);
			break;
		case 1:
			spi_write(MCP_RTS_TX1);
			break;
		case 2:
			spi_write(MCP_RTS_TX2);
			break;
		default:
			spi_write(MCP_RTS_TX0);
	}	
	PORTB |= (1 << CAN_CS ); // De-select CAN - controller
}

void can_init() {
	mcp2515_init();
	mcp2515_mode_select(MODE_LOOPBACK); // ->Change mode to normal for NODE2
	//Generate interrupt when message is transmitted from buffer 0
	mcp2515_bit_modify(MCP_CANINTE, 0b00000100, MCP_TX01_INT);
	//Generate interrupt when message is received from buffer 0
	mcp2515_bit_modify(MCP_CANINTE, 0b00000001, MCP_RX_INT);
	//Clear the interrupt for received buffer at initiation
	mcp2515_bit_modify(MCP_CANINTF, 0b00000100, MCP_NO_INT);
}

void can_send_message(can_message_t* message) {
	//wait for the transmission to finish
	while (MCP_TXB0CTRL & (1 << 3)) {}
	
	//For buffer 0
	//Set message id, 11 bits -> 8 highest to SIDH and 3 lowest to SIDL
	mcp2515_write(MCP_TXB0SIDH, (message->id >> 3)); //8 High bits of id
	mcp2515_write(MCP_TXB0SIDL, ((message->id & 0x07) << 5)); //3 Low bits of id
	//Set message length, 4 bits
	mcp2515_write(MCP_TXB0DLC, message->length);
	
	//Set message into buffer
	for (int i = 0; i < message->length; i++) {
		mcp2515_write(MCP_TXB0D0 + i, message->data[i]);
	}
	//After the message data is loaded in buffer, it sends request to send message
	mcp2515_rts(0);
}

can_message_t can_recieve_message() {
	can_message_t message = {};
		
	//For buffer 0
	//Read message id
	uint8_t idh = mcp2515_read(MCP_RXB0SIDH);
	uint8_t idl = mcp2515_read(MCP_RXB0SIDL);
	message.id = (idh << 3) + ((0b11100000 & idl) >> 5);
	//Read message length
	message.length = mcp2515_read(MCP_RXB0DLC);
	//Read message
	for (int i = 0; i < message.length; i++) {
		message.data[i] += mcp2515_read(MCP_RXB0D0 + i);
	}
	//Clear receive buffer interrupt after the message is received
	mcp2515_bit_modify(MCP_CANINTF, 0b00000001, MCP_NO_INT);
	
	return message;
}