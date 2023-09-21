#pragma once


void UART_init(void);
static int UART_transmit(char message, FILE *stream);
char UART_recive(void);