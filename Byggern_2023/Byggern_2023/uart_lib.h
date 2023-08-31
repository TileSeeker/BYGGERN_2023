/*
 * uart_lib.h
 *
 * Created: 31-Aug-23 2:22:08 PM
 *  Author: peter
 */ 
#pragma once

void uart_init(void);				//Set Baudrate, Enable Tx and Rx, Configure Frame
void uart_send_byte(uint8_t data);	
uint8_t uart_read_byte(void);		