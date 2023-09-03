#pragma once

#include <stdbool.h>


void UART_init();
static int UART_transmit(char message, FILE *stream);
char UART_recive();