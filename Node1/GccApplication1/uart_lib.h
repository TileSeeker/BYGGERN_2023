#ifndef UART_LIB_H
#define UART_LIB_H

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>


void UART_init(void);
int UART_transmit(char message);
char UART_recive(void);


#endif