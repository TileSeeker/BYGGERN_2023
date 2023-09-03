/*
 * uart_lib.h
 *
 * Created: 31-Aug-23 2:22:08 PM
 *  Author: peter
 */ 
#pragma once

#include <stdbool.h>

struct FIFO{
	char *buffer;
	uint16_t size;
	uint16_t head;
	uint16_t tail;
};

void uart_init(void);				//Set Baudrate, Enable Tx and Rx, Configure Frame
void uart_send_byte(char data);	
void uart_send_string(char* str);
char uart_read_byte(void);		

//Declare FIFO functions
void init_fifo(struct FIFO* fifo_object, char* array, uint16_t size);
bool fifo_full(struct FIFO* fifo_object);
bool fifo_empty(struct FIFO* fifo_object);
void fifo_push(struct FIFO* fifo_object, char data);
char fifo_pop(struct FIFO* fifo_object);